#include "stdafx.h"
#include "DbSynSvr.h"
#include <time.h>
#include "CSMSClient2000.h"
#include "..\Comfiles\comutils.h"

#include "..\Comfiles\CardControl.h"
#include "..\Comfiles\CardDef.h"
#include "..\Comfiles\LogForMe.h"
#include <afxtempl.h>



inline void TESTHR(HRESULT x) {if FAILED(x) _com_issue_error(x);};

CDbSynSvr::CDbSynSvr(void)
{

	//服务线程句柄
	m_hThread = INVALID_HANDLE_VALUE;
	//定期清除线程退出事件
	m_hEvtExit = INVALID_HANDLE_VALUE;

	//数据库连接参数
	memset(&DBConParam, 0, sizeof(DBConParam));
	//数据库连接
	m_pConnection = NULL;

	m_nCheckPeriod = 60;
	m_nValidTime = 24;


	
	
}

CDbSynSvr::~CDbSynSvr(void)
{   

}

void CDbSynSvr::ClearSelectVar()
{

	
}
	


/********************************************************************
purpose:    	初始化服务线程
Parameters:		
Return Value:
*********************************************************************/
bool CDbSynSvr::Init()
{

	m_Params.InitParam();
	bool bProxyOff;
	ULONG MaxJnl;
	if (!TA_Init(m_Params.params.ProxyAddr, m_Params.params.ProxyPort, m_Params.params.SysCode, m_Params.params.TerNo,
		&bProxyOff, &MaxJnl)){
			DebugLog("初始化失败,请关闭程序，检查参数!");
			PrintDebugLog("调用TA_Init进行初始化失败,IP:%s, Port:%d, SysCode:%d, TerminalNo:%d",
				m_Params.params.ProxyAddr, m_Params.params.ProxyPort, m_Params.params.SysCode, m_Params.params.TerNo);
			FiniLogFile();
			return false;
			//while (1)
			//{
			//	Sleep(1000);
			//}

		}
		if (bProxyOff) {
			DebugLog("代理处于脱机状态!");
			DebugLog("代理处于脱机状态!");
		}
		DebugLog("调用TA_Init初始化SIOS第三方库成功");


		char filepath[255];
		memset(filepath,0,255);
		::GetModuleFileName(NULL, filepath, 255);
		CString strModuleName = filepath;
		int nPos = strModuleName.ReverseFind('\\');
		if (nPos == -1) {
			return 0;
		}
		m_strModulePath = strModuleName.Left(nPos+1); 
		m_strListFile =  m_strModulePath + "Memberlist.dat";
		m_strControlFile = m_strModulePath + "Control.dat";


		m_strDbPath.Format("%s", m_Params.params.DBName);
		m_strBlackPath.Format("%s", m_Params.params.BLName);

	if (!GetLocalParam()) {
		ErrorLog("读取参数失败,请检查参数文件");
		return false;
	}
	m_hEvtExit = CreateEvent(NULL, false, false, NULL);
	DWORD dwTheadId;
	m_hThread = CreateThread(NULL, 0, ThreadFunction, this, 0, &dwTheadId);
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		SysErrLog("创建服务线程失败!");
		CloseHandle(m_hEvtExit);
		return false;
	}
	return true;
}

/********************************************************************
purpose:    	关闭服务线程
Parameters:		
Return Value:
*********************************************************************/
void CDbSynSvr::Destroy()
{
	SetEvent(m_hEvtExit);
	if (WaitForSingleObject(m_hThread, 5000) == WAIT_TIMEOUT)
	{
		ErrorLog("关闭专家抽取服务线程失败,强行关闭!");
		TerminateThread(m_hThread, -1);
	}
	CloseHandle(m_hThread);
	CloseHandle(m_hEvtExit);
}

/********************************************************************
purpose:    	线程入口函数
Parameters:		
Return Value:
*********************************************************************/
DWORD WINAPI CDbSynSvr::ThreadFunction(LPVOID param)
{
	CDbSynSvr *pThis = (CDbSynSvr*)param;
	return pThis->DbSynSvrFun();
}


/********************************************************************
purpose:  服务函数
Parameters:		
Return Value:
*********************************************************************/
DWORD CDbSynSvr::DbSynSvrFun()
{
	CoInitialize(NULL);
	CString strMsg1,strMsg2;
	CString strtemp;

   

	while (WaitForSingleObject(m_hEvtExit, m_nCheckPeriod*1000)==WAIT_TIMEOUT){
		//读取参数
		GetLocalParam();
    

        if(!Download())
		{
		  continue;
		}
		ImportControlBin();
		ImportMemberList();
        CheckNewBList();



		EventLog("                                      ");
		EventLog("**************************************");
		EventLog("          检测到有人员更新          ");
		EventLog("**************************************");

	
	}
	CoUninitialize();
    return 0;
}



/********************************************************************
purpose:    	检查数据库有无更新，采集有变化的门控器号放入链表m_gateID中
Parameters:		
Return Value:
*********************************************************************/
bool CDbSynSvr::CheckNewBList()
{
    
	CString strBlack = "newblist.bin";

	CString strBFile = m_strBlackPath + strBlack;
	CString strBTempFile = m_strBlackPath + "Temp.bin";
    
	PrintTraceLog(m_strBlackPath);
	PrintTraceLog("黑名单文件%s", strBFile);

	WIN32_FIND_DATA FileData;
	HANDLE hSearch;
	hSearch = FindFirstFile(strBFile, &FileData); 
	if (hSearch == INVALID_HANDLE_VALUE) 
	{ 
		EventLog("未找到%s文件,无需同步", strBFile); 
		return 1;
	}	 

	if (FileData.nFileSizeHigh == 0 && FileData.nFileSizeLow == 0) {
		EventLog("newblist.bin文件长度为0,无需同步"); 
		return 1;
	}


	if (MoveFile(strBFile, strBTempFile) == FALSE) {
		EventLog("无法移动newblist.bin文件,文件被占用");
	}

	//打开文件,导入数据
	//CArray<ACCOUNT_MSG, ACCOUNT_MSG> lstAccount;		


	FILE *stream;
	char line[100];
	try
	{
		if ((stream = fopen(strBTempFile, "r" )) == NULL)
		{
			ErrorLog("无法打开临时文件!");
			return 1;
		}

		while(fgets( line, 100, stream ) != NULL)
		{
			if(strlen(line) == 0)
			{
				TraceLog("0长度");
				continue;
			}
			PrintTraceLog("line:%s", line);
			CString strline(line);

			ACCOUNT_MSG amsg={0};
			amsg.ID = strline.Left(strline.Find(' '));
			strline.Delete(0, strline.Find(' ') + 1);
			PrintDebugLog("amsg.ID:%s, strline:%s", amsg.ID, strline);


			amsg.CardID = strline.Left(strline.Find(' '));
			strline.Delete(0, strline.Find(' ') + 1);
			PrintDebugLog("amsg.ID:%s, strline:%s", amsg.CardID, strline);
		    PrintDebugLog("strline.Left(5): %s", strline.Left(5));
			//if (strline.Left(5) == "1 0 0") {
				//冻结
			//	amsg.status = 1;
			//	PrintTraceLog("acc:%s,status:%d",amsg.ID,amsg.status);
			//}else 
			if (strline.Left(5) == "1 0 0"){
                continue;
			}else if (strline.Left(5) == "0 1 0"){
				//挂失
				amsg.status = 1;
				PrintDebugLog("acc_ID(accountno):%s,status:%d",amsg.ID,amsg.status);
			}else if (strline.Left(5) == "0 0 0"){
				strline.Delete(0, 8);
				strline.Delete(0, strline.Find(' ') + 1);
				if (strline.Left(1) == "0")
				{
					amsg.status = 2;//新增
					PrintDebugLog("acc:%s,status:%d",amsg.ID,amsg.status);
				} 
				else if (strline.Left(1) == "1")
				{
					amsg.status = 3;//删除
					PrintDebugLog("acc:%s,status:%d",amsg.ID,amsg.status);
				} 
				else if (strline.Left(1) == "2" )
				{
					amsg.status = 0; //换卡解冻解挂
					PrintDebugLog("acc:%s,status:%d",amsg.ID,amsg.status);
				}
			
			}
			vMsg.push_front(amsg);
		}
		fclose( stream );						
	}	
	catch (...) {
		ErrorLog("发生异常!");
		fclose(stream);
	}
	DeleteFile(strBTempFile);

	PrintDebugLog("共发现%d条帐户变动信息",vMsg.size() );
	int j= vMsg.size();

	for (int i = 0; i<j ; i++) {
		
			//ResetStatus(vMsg.back().ID,vMsg.back().status);

	    if(!Connect())
		{
		 DebugLog("打开数据库错误!");
		 return 0;
		}

		try{
			_CommandPtr pCmdChange  = NULL;
			_RecordsetPtr	pRst  = NULL;
			char strSql[512];
			TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
			TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
			pCmdChange->ActiveConnection = m_pConnection;

			//
				_CommandPtr	cm("ADODB.Command");
			char strSql1[512];	
			try
			{	

				sprintf(strSql1, "use Gsccsserver");
				cm->CommandText = strSql1;
				cm->CommandType = adCmdText;
				cm->ActiveConnection = m_pConnection;
				cm->Execute(0,NULL, adExecuteNoRecords);

			}
			catch (_com_error &e) {
				PrintErrorLog("ImportMemberList()连接时出现异常,异常信息:%s", e.ErrorMessage());

			}
			catch (...) {
				ErrorLog("ImportMemberList()未知异常");
			}
			//
			CString CaNo = 0;
			UINT FLG = 0;
			sprintf(strSql, "select * from users where AccountNo = '%s'", vMsg.back().ID);
			TraceLog(strSql);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (!pRst->EndOfFile) {
				//插入人员SQL
				switch(vMsg.back().status)
				{
				case 0://换卡或解挂或解冻
					CaNo = pRst->Fields->Item["CardNo"]->Value;
	                FLG   = pRst->Fields->Item["Flag"]->Value;
					sprintf(strSql, "vMsg.back().ID= '%s'", vMsg.back().CardID);
					TraceLog(strSql);
					if( CaNo != vMsg.back().CardID )
					{sprintf(strSql, "Update users set CardNo  = '%s', Flag = 0 ,Curstate = 1 where AccountNo ='%s'" ,vMsg.back().CardID ,vMsg.back().ID);}
					else if (FLG == 1)
										{sprintf(strSql, "Update users set CardNo  = '%s', Flag = 0 ,Curstate = 1 where AccountNo ='%s'" ,vMsg.back().CardID ,vMsg.back().ID);}
					else{
						sprintf(strSql, " ");}
					break;
				case 1://挂失
					sprintf(strSql, "Update users set Flag = 1 ,Curstate = 1 where accountno = '%s'",vMsg.back().ID);
					break;
				case 2://新增
					//sprintf(strSql, "Update users set Flag = 2 ,Curstate = 1 where accountno = '%s'",vMsg.back().ID);
					sprintf(strSql, " " ); 
					break;
				case 3://删除
					sprintf(strSql, "Update users set Flag = 3 ,Curstate = 1 where accountno = '%s'",vMsg.back().ID);
					break;

				default:
					break;
				}

				TraceLog(strSql);
				pCmdChange->CommandText = strSql;				
				pCmdChange->Execute(NULL, NULL, adCmdText);
			}	
			pRst->Close();	

		}catch(_com_error err){
			PrintSysErrLog("导入人员列表线程出错:%s", err.ErrorMessage());
		}

		CloseConnect();	


			//sprintf("id:%s,status:%d", vMsg.back().ID, vMsg.back().status );
			vMsg.pop_back();

	}
	vMsg.clear();
	return 0;
}

/********************************************************************
purpose: 将临时表清空
Parameters:		
Return Value:
*********************************************************************/
/**void CDbSynSvr::ResetStatus( CString strID, INT status )
{
	if(!Connect())
		DebugLog("打开数据库错误!");
		return;

	try{
		_CommandPtr pCmdChange  = NULL;
		_RecordsetPtr	pRst  = NULL;
		char strSql[512];
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
		pCmdChange->ActiveConnection = m_pConnection;



		sprintf(strSql, "select * from users where AccountNo = '%s'", strID);
		TraceLog(strSql);
		pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
			adOpenStatic, adLockReadOnly, adCmdText);
		if (!pRst->EndOfFile) {
			//插入人员SQL
			switch(status)
			{
			case 0:
			    sprintf(strSql, "Update users set flag = 0 where accountno = '%s' Update users set InUse = 0 where accountno ='%s'",strID,strID);
				break;
			case 1:
			    sprintf(strSql, "Update users set InUse = 1 where accountno = '%s'",strID);
				break;
			case 2:
			    sprintf(strSql, "Update users set flag = 1 where accountno = '%s'",strID);
			    break;
			case 3:
				sprintf(strSql, "Update users set flag = 3 where accountno = '%s'",strID);
			    break;
			case 4:
				sprintf(strSql, "Update users set flag = 2 where accountno = '%s'",strID);
				break;
			default:
			    break;
			}
			
			TraceLog(strSql);
			pCmdChange->CommandText = strSql;				
			pCmdChange->Execute(NULL, NULL, adCmdText);
		}	
		pRst->Close();	



	//}catch(CException err){
	//	TCHAR   szCause[255];
	//	err.GetErrorMessage(szCause, 255);
	//	PrintSysErrLog("导入人员列表线程出错:%s", szCause);
	}catch(_com_error err){
		PrintSysErrLog("导入人员列表线程出错:%s", err.ErrorMessage());
	}

	return ;
	CloseConnect();	
}



*/

	/********************************************************************
	purpose: 针对每一个需要更新的门控器，将其对应的DISPATH结构体封装好，准备下发
	Parameters:		
	Return Value:
	*********************************************************************/
	bool CDbSynSvr::Download()
	{

			EventLog("开始下载人员列表,请稍等...");
		    
			int nRecNum ;
			char chFn[64] = {0};
            AccountMsg am = {0};
			int nResult = TA_HazyInqAcc(&am , &nRecNum , chFn, 600);
			CString strMsg;
			if (nResult == ERR_OK) {
				strMsg.Format("下载人员列表成功!共返回记录%d条", nRecNum);	
				CString strDest = m_strModulePath+"RecvTemp\\" + chFn;
				PrintDebugLog(strDest);
				CopyFile(strDest, m_strListFile, FALSE);
				DeleteFile(strDest);

			}else{	
				strMsg.Format("下载人员列表失败!返回(%d)",nResult);
				DebugLog(strMsg);
				return false;
			}

		

      
		EventLog("         开始下载控制参数,请稍等...         ");
	    nResult = TA_DownControlFile();
		if (nResult>0) {
			CString strDest = m_strModulePath+"ControlFile\\Control.bin";
			EventLog(strDest);
			CopyFile(strDest, m_strControlFile, FALSE);
			DeleteFile(strDest);
			strMsg.Format("下载控制参数结束!返回值(%d)",nResult);	
			EventLog(strMsg);
			return true;
		}else{
			strMsg.Format("下载控制参数失败!返回(%d)",nResult);
			DebugLog(strMsg);
			return false;

		}


	}


/********************************************************************
purpose:   上电时检查临时表内是否有未下发完成的记录，有则装入m_gateID，无则入主循环
Parameters:		
Return Value:
*********************************************************************/
void CDbSynSvr::ImportControlBin()
{   

	if(!Connect()) return ;
	_RecordsetPtr pRst=NULL;
//
	char strSql[512];
	char strSql1[512];
	_CommandPtr	cm("ADODB.Command");
	try
	{	

		sprintf(strSql, "use Gsccsserver");
		cm->CommandText = strSql;
		cm->CommandType = adCmdText;
		cm->ActiveConnection = m_pConnection;
		cm->Execute(0,NULL, adExecuteNoRecords);
		TraceLog(strSql);

	}
	catch (_com_error &e) {
		PrintErrorLog("ImportControlBin()连接时出现异常,异常信息:%s", e.ErrorMessage());

	}
	catch (...) {
		ErrorLog("ImportControlBin()未知异常");
	}

	
   // 

	CFile f;
	CFileException ex;
	if (!f.Open(m_strControlFile, CFile::modeRead, &ex)){		
		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);		
		PrintSysErrLog("控制文件(Name:%s)打开错误:%s", m_strControlFile, szError);
		return ;
	}

	try{
		_CommandPtr pCmdChange  = NULL;
		_RecordsetPtr	pRst  = NULL;
		char strSql[512];
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
		pCmdChange->ActiveConnection =m_pConnection;		

		char fileId[8];
		struct tabCtrlHead head;
		struct t_department depart;
		struct t_area area;
		if (f.Read(fileId, 8) != 8)
		{
			throw new CFileException();
		}
		if(memcmp(fileId, CONTROL_STR, 8) !=0)
		{
			throw new CFileException();
		}
		//导入部门代码
		f.Seek(8+sizeof(head)*OFFSET_T_DEPARTMENT , CFile::begin);
		if(f.Read(&head, sizeof(head)) != sizeof(head))
		{
			throw new CFileException();
		}
		if(head.structlength != sizeof(depart)){
			throw new CFileException();
		}
		f.Seek(head.offset, CFile::begin);	
		int nCurCount = 0;
		int nTotalCount = head.count;

		while(WaitForSingleObject(m_hEvtExit,0) == WAIT_TIMEOUT)
		{
			if (f.Read(&depart, sizeof(depart)) != sizeof(depart)) {
				throw new CFileException();
			}
			sprintf(strSql, "select * from department where dept_code = 'A%s%s'", depart.area_code, depart.dept_code);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (pRst->EndOfFile) {
				//插入数据SQL语句
				sprintf(strSql, "insert into department(dept_code, dept_name , area_code, dept_flag, curstate)"
					" values('A%s%s','%s', 'A%s','1', '1')",
					depart.area_code, depart.dept_code, depart.dept_name, depart.area_code);
				PrintDebugLog(strSql);
				pCmdChange->CommandText = strSql;				
				pCmdChange->Execute(NULL, NULL, adCmdText);
			}
			pRst->Close();
			nCurCount++;			
            if(nCurCount == nTotalCount)
			break;
		    if(nCurCount % 100 ==0)
			{ sprintf(strSql1, "共有记录%d条,已完成%d条", nTotalCount,nCurCount);
			  PrintDebugLog(strSql1);
			}
				//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);
			//CString strState;
			//strState.Format("共有记录%d条,已完成%d条", nTotalCount,nCurCount);
			//DebugLog(strState);
		}


		//导入校区编码
		f.Seek(8+sizeof(head)*OFFSET_T_AREA , CFile::begin);
		if(f.Read(&head, sizeof(head)) != sizeof(head))
		{
			throw new CFileException();
		}
		if(head.structlength != sizeof(area)){
			throw new CFileException();
		}
		f.Seek(head.offset, CFile::begin);		
		nCurCount = 0;
		nTotalCount = head.count;
		while(WaitForSingleObject(m_hEvtExit,0) == WAIT_TIMEOUT)
		{
			if (f.Read(&area, sizeof(area)) != sizeof(area)) {
				throw new CFileException();
			}
			sprintf(strSql, "select * from department where area_code = 'A%s'", area.area_code);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (!pRst->EndOfFile) {
				//插入数据SQL语句
				sprintf(strSql, "update department set area_name= '%s' where area_code = 'A%s'",
					area.area_name, area.area_code);
				PrintDebugLog(strSql);
				pCmdChange->CommandText = strSql;				
				pCmdChange->Execute(NULL, NULL, adCmdText);
			}
			pRst->Close();
			nCurCount++;			
			if(nCurCount == nTotalCount)
				break;
			if(nCurCount % 100 ==0)
			{sprintf(strSql1, "共有记录%d条,已完成%d条", nTotalCount,nCurCount);
			 TraceLog(strSql1);}


				//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);	
		}
		//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);

	//}catch(CFileException err){
	//	TCHAR   szCause[255];
	//	err.GetErrorMessage(szCause, 255);
	//	PrintSysErrLog("导入机构线程出错:%s", szCause);
	}catch(_com_error err){
		PrintSysErrLog("导入人员列表线程出错:%s", err.ErrorMessage());
	}	
	//pThis->PostMessage(WM_SETPOS, 0, 0);
	f.Close();
	CloseConnect();
	return ;
	


}


/********************************************************************
purpose:    	启动程序后检查有无临时表troommember_backup,有则将其整理下发，无则跳出
Parameters:		
Return Value:
*********************************************************************/
bool CDbSynSvr::ImportMemberList()
{
	if(!Connect())
		return false;


	_CommandPtr	cm("ADODB.Command");
//
	char strSql[512];
	char strSql1[512];	
	try
	{	

		sprintf(strSql, "use Gsccsserver");
		cm->CommandText = strSql;
		cm->CommandType = adCmdText;
		cm->ActiveConnection = m_pConnection;
		cm->Execute(0,NULL, adExecuteNoRecords);

	}
	catch (_com_error &e) {
		PrintErrorLog("ImportMemberList()连接时出现异常,异常信息:%s", e.ErrorMessage());

	}
	catch (...) {
		ErrorLog("ImportMemberList()未知异常");
	}

//	


	CFile f;
	CFileException ex;
	if (!f.Open(m_strListFile, CFile::modeRead, &ex)){		
		TCHAR szError[1024];
		//ex.GetErrorMessage(szError, 1024);		
		PrintSysErrLog("人员列表文件(Name:%s)打开错误:%s", m_strListFile, szError);
		return 1;
	}
	try{
		_CommandPtr pCmdChange  = NULL;
		_RecordsetPtr	pRst  = NULL;
		char strSql[512];
		HazyInqAccMsg accmsg;
		TESTHR(pRst.CreateInstance(__uuidof(Recordset)));
		TESTHR(pCmdChange.CreateInstance(__uuidof(Command)));
		pCmdChange->ActiveConnection = m_pConnection;

		int nCurCount = 0;
		int nTotalCount = f.GetLength() / sizeof(HazyInqAccMsg);
		while(WaitForSingleObject(m_hEvtExit,0) == WAIT_TIMEOUT)
		{
			UINT nCount = f.Read(&accmsg, sizeof(HazyInqAccMsg));
			if (nCount != sizeof(HazyInqAccMsg)) {
				break;
			}
			sprintf(strSql, "select * from users where AccountNo = '%d' ", accmsg.AccountNo);
			pRst->Open(strSql, _variant_t((IDispatch *)m_pConnection,true), 
				adOpenStatic, adLockReadOnly, adCmdText);
			if (pRst->EndOfFile) {
				//插入人员SQL
                    sprintf(strSql, "insert into users(AccountNo, Name, CardNo, DeptCode, StudentCode, IDCard, SexNo,Flag,curstate)"
					" values('%d','%s','%u','A%s','%s','%s','%s','2' ,'1') ",
					accmsg.AccountNo, accmsg.Name, accmsg.CardNo, accmsg.DeptCode, accmsg.StudentCode, accmsg.IDCard, accmsg.SexNo);
				    PrintDebugLog(strSql);
				    pCmdChange->CommandText = strSql;				
				    pCmdChange->Execute(NULL, NULL, adCmdText);

			 }
			pRst->Close();
			nCurCount++;
				
			if(nCurCount == nTotalCount)
				break;
            if(nCurCount % 1000 == 0 )
			{sprintf(strSql1, "共有记录改变%d条,已完成更新%d条", nTotalCount,nCurCount);
			 PrintDebugLog(strSql1);
			}
			//	pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);
		}		
		//pThis->PostMessage(WM_SETPOS, nCurCount, nTotalCount);
	}catch(_com_error err){
		PrintSysErrLog("导入人员列表线程出错:%s", err.ErrorMessage());
	}
	//pThis->PostMessage(WM_SETPOS, 0, 0);
	f.Close();
	CloseConnect();
	return 0;
}


//连接数据库
bool CDbSynSvr::Connect(void)     
{
	if (m_pConnection)
	{
		return true;
	}
	char constr[512];
	sprintf(constr, "Provider=%s;Persist Security Info=False;Data Source=%s;"
		"User ID=%s;Password=%s;PLSQLRSet=1",DBConParam.DRIVER,	
		DBConParam.DSN, DBConParam.USER, DBConParam.PASS);
	
	
	PrintDebugLog("数据库连接字符串%s",constr);

	try
	{
		TESTHR(m_pConnection.CreateInstance(__uuidof(Connection)));
		m_pConnection->CursorLocation = adUseServer;
		m_pConnection->Open(constr,"","",adModeUnknown);
	}
	catch (_com_error &e) {
		PrintErrorLog("CDbSynSvr数据库连接异常,异常信息:%s", e.ErrorMessage());	
		m_pConnection.Release();
		return false;
	}
	catch (...) {
		ErrorLog("CDbSynSvr数据库连接未知异常");
		return false;
	}
	EventLog("CDbSynSvr数据库连接成功");
	return true;
}
//断开数据库连接
void CDbSynSvr::CloseConnect(void)
{
	m_pConnection->Close();
	m_pConnection = NULL;
}

//获取本地参数
bool CDbSynSvr::GetLocalParam(void)
{


	char filepath[255];
	memset(filepath,0,255);
	::GetModuleFileName(NULL, filepath, 255);
	string strParamFileName = filepath;
	string::size_type nPos = strParamFileName.rfind("\\");
	if (nPos == (string::size_type)-1) {
		return false;
	}
	strParamFileName.resize(++nPos);
	//strParamFileName += strFileName;
	strParamFileName += "DbSyn.ini";
	PrintDebugLog("参数文件:%s", strParamFileName.c_str());	
	GetPrivateProfileString("DBPARAM", "DRIVER", "SQL Server", DBConParam.DRIVER,
		sizeof(DBConParam.DRIVER),strParamFileName.c_str());	
	GetPrivateProfileString("DBPARAM", "DSN", "EXPERTSELECT", DBConParam.DSN,
		sizeof(DBConParam.DSN),strParamFileName.c_str());	
	GetPrivateProfileString("DBPARAM", "USER", "root", DBConParam.USER,
		sizeof(DBConParam.USER),strParamFileName.c_str());
	GetPrivateProfileString("DBPARAM", "PWD", "poot", DBConParam.PASS,
		sizeof(DBConParam.PASS),strParamFileName.c_str());

	m_nCheckPeriod = GetPrivateProfileInt("RUNPARAM", "CHECKPERIOD", 60, 
		strParamFileName.c_str());	
	m_nValidTime = GetPrivateProfileInt("RUNPARAM", "VALIDTIME", 48, 
		strParamFileName.c_str());
	m_nWaitAnswer = GetPrivateProfileInt("RUNPARAM", "WAITTIME", 15, 
		strParamFileName.c_str());

	//CString strParam;
	//strParam.Format("检测任务周期(秒)|%d|任务最小有效时间(小时)|%d|等待短信回复时间(分钟)|%d|",
		//m_nCheckPeriod, m_nValidTime, m_nWaitAnswer);
	//WriteMailSlot("\\\\.\\mailslot\\ExpertSMSMonitor_Param", strParam);	


	//m_Com.nComNo = GetPrivateProfileInt("COMPARAM", "ComPort", 1, strParamFileName.c_str());
	//m_Com.nBaudrate = GetPrivateProfileInt("COMPARAM", "Baudrate", 9600, strParamFileName.c_str());
	return true;
}






