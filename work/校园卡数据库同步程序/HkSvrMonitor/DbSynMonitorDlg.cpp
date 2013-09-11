// HkSvrMonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GsccsMonitor.h"
#include "GsccsMonitorDlg.h"
#include ".\Gsccsmonitordlg.h"
#include "..\ComFiles\ComUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHkSvrMonitorDlg �Ի���

inline BOOL StartSrv(char * srvname)
{
	SC_HANDLE hSCMgr = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if( !hSCMgr )
	{
		AfxMessageBox("���ӷ��������ʧ�ܣ�");
		return FALSE;
	}

	SC_HANDLE hSvr = OpenService( hSCMgr ,_T(srvname),SERVICE_START );
	if( !hSvr )
	{
		CloseServiceHandle( hSCMgr );
		AfxMessageBox("�򿪷���ʱʧ�ܣ�");
		return FALSE;
	}
	if ( StartService( hSvr , 0 , NULL ) )
	{
		CloseServiceHandle( hSvr );
		CloseServiceHandle( hSCMgr );
		return TRUE;
	}
	else
	{

		if ( GetLastError() == ERROR_SERVICE_ALREADY_RUNNING )
			AfxMessageBox("�����Ѿ����У�");
		else
		{
			CString temp;
			temp.Format ("��������ʧ�ܣ�",GetLastError());
			AfxMessageBox(temp);
		}
	}
	CloseServiceHandle( hSvr );
	CloseServiceHandle( hSCMgr );
	return FALSE;
}
// 1 �ɹ�ֹͣ
// 0 ����û������
// 2 ֹͣʧ��
int StopSrv(char * srvname) 
{
	SC_HANDLE hSCMgr = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if( !hSCMgr )
	{
		AfxMessageBox("���ӷ��������ʧ�ܣ�");
		return 2;
	}

	SC_HANDLE hSvr = OpenService( hSCMgr ,_T(srvname),SERVICE_ALL_ACCESS);
	if( !hSvr )
	{
		CloseServiceHandle( hSCMgr );
		AfxMessageBox("�򿪷���ʱʧ�ܣ�");
		return 2;
	}


	SERVICE_STATUS status;
	memset(&status, 0, sizeof(status));
	if ( QueryServiceStatus ( hSvr , &status ) )
	{
		if ( status.dwCurrentState  == SERVICE_RUNNING )
		{
			if ( ControlService( hSvr , SERVICE_CONTROL_STOP , &status ) )
			{
				CloseServiceHandle( hSvr );
				CloseServiceHandle( hSCMgr );
				if (status.dwCurrentState != SERVICE_STOP_PENDING &&
					status.dwCurrentState != SERVICE_STOPPED)
					return 2;
				else
					return 1;
			}
			else
			{
				CloseServiceHandle( hSvr );
				CloseServiceHandle( hSCMgr );
				return 2;
			}
		}
		else
		{
			CloseServiceHandle( hSvr );
			CloseServiceHandle( hSCMgr );
			return 0;
		}
	}
	else
	{
		AfxMessageBox("��ѯ����״̬ʧ�ܣ�");
		CloseServiceHandle( hSvr );
		CloseServiceHandle( hSCMgr );
		return 2;
	}	
}
// 1 ���ڲ�����  2���ڵ���û������ 3������ 4����ʧ��
int ExistsSrv(char * srvname)
{
	SC_HANDLE hSCMgr = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hSCMgr)
	{
		ErrorLog("�жϷ����Ƿ���ڲ���ȡ����״̬ʱ�����ӷ��������ʧ�ܣ�");
		return 4;
	}

	SC_HANDLE hSvr = OpenService(hSCMgr ,_T(srvname), SERVICE_ALL_ACCESS);
	if ( hSvr )
	{
		SERVICE_STATUS status;
		if ( QueryServiceStatus ( hSvr , &status ) )
		{
			if ( status.dwCurrentState == SERVICE_RUNNING )
			{
				CloseServiceHandle( hSvr );
				CloseServiceHandle( hSCMgr );
				//g_LogReport.ErrorReport("������������");
				return 1;
			}
			else
			{
				CloseServiceHandle( hSvr );
				CloseServiceHandle( hSCMgr );
				//g_LogReport.ErrorReport("������ڵ���û������");
				return 2;
			}

		}
		else
		{
			CloseServiceHandle( hSvr );
			CloseServiceHandle( hSCMgr );
			//g_LogReport.ErrorReport("��ѯ����״̬ʧ�ܣ�");
			return 2;
		}
	}
	else
	{
		//g_LogReport.ErrorReport("û�з��ָ÷���");
		CloseServiceHandle( hSCMgr );
		return 3;
	}
}

CHkSvrMonitorDlg::CHkSvrMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHkSvrMonitorDlg::IDD, pParent)
	, m_strStatus(_T("")),m_trayIcon(IDR_TRAYICON)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bShutdown = FALSE;
	m_bDisplayPause = false;
}

void CHkSvrMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LB_EVENT, m_lstEvent);
	DDX_Control(pDX, IDC_LST_PARAM, m_lstParam);
	DDX_Text(pDX, IDC_STATUS, m_strStatus);
	DDX_Control(pDX, IDC_BTN_STARTSVR, m_btnStartSvr);
	DDX_Control(pDX, IDC_BTN_STOPSVR, m_btnStopSvr);
	DDX_Control(pDX, IDC_BMP_STATUS, m_IconStatus);
	DDX_Control(pDX, IDC_TABDISPLAY, m_TabDisType);
}

BEGIN_MESSAGE_MAP(CHkSvrMonitorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LST_PARAM, OnLvnGetdispinfoLstParam)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_STARTSVR, OnBnClickedBtnStartsvr)
	ON_BN_CLICKED(IDC_BTN_STOPSVR, OnBnClickedBtnStopsvr)
	ON_WM_CREATE()
	ON_COMMAND(IDM_OPEN, OnDlgOpen)
	ON_COMMAND(IDM_EXIT, OnDlgExit)
	ON_MESSAGE(WM_MY_TRAY_MESSAGE, OnIconMessage)
	ON_WM_CLOSE()
	ON_LBN_DBLCLK(IDC_LB_EVENT, OnLbnDblclkLbEvent)	
	ON_LBN_SELCHANGE(IDC_LB_EVENT, OnLbnSelchangeLbEvent)
END_MESSAGE_MAP()


// CHkSvrMonitorDlg ��Ϣ�������

BOOL CHkSvrMonitorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_TabDisType.InsertItem(0,"��ȡ�¼�");
	SetTimer(0, 100, NULL);
	ReAlignControls();
	MoveWindow(0,0,800,600);
	m_lstParam.InsertColumn(0,"��������", LVCFMT_LEFT, 165);
	m_lstParam.InsertColumn(1,"����ֵ", LVCFMT_LEFT, 80);
	m_lstParam.SetExtendedStyle(LVS_EX_GRIDLINES);

	m_btnStartSvr.ShowWindow(TRUE);
	m_btnStopSvr.ShowWindow(TRUE);
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHkSvrMonitorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CHkSvrMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHkSvrMonitorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

bool CHkSvrMonitorDlg::InitMailSlot(void)
{
	LPSTR lpszSlotName = "\\\\.\\mailslot\\ExpertSMSMonitor_Event"; 

	// The mailslot handle "hSlot1" is declared globally. 

	m_hSlotEvent = CreateMailslot(lpszSlotName, 
		0,                             // no maximum message size 
		MAILSLOT_WAIT_FOREVER,         // no time-out for operations 
		(LPSECURITY_ATTRIBUTES) NULL); // no security attributes 

	if (m_hSlotEvent == INVALID_HANDLE_VALUE) 
	{ 		
		SysErrLog("�����ʲ�ʧ��");
		return false; 
	} 


	m_hSlotParam = CreateMailslot("\\\\.\\mailslot\\ExpertSMSMonitor_Param", 
		0,                             // no maximum message size 
		MAILSLOT_WAIT_FOREVER,         // no time-out for operations 
		(LPSECURITY_ATTRIBUTES) NULL); // no security attributes 

	if (m_hSlotEvent == INVALID_HANDLE_VALUE) 
	{ 		
		SysErrLog("�����ʲ�ʧ��");
		return false; 
	} 
	return true;
}

void CHkSvrMonitorDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	RefreshSvrStatus();
	ReadParamMailSlot();
	ReadMailSlot();
	
	CDialog::OnTimer(nIDEvent);
}

void CHkSvrMonitorDlg::ReadMailSlot(void)
{
	DWORD cbMessage, cMessage, cbRead; 
	BOOL fResult; 
	LPSTR lpszBuffer; 
	CHAR achID[80]; 
	DWORD cAllMessages; 
	HANDLE hEvent;
	OVERLAPPED ov;

	cbMessage = cMessage = cbRead = 0; 

	hEvent = CreateEvent(NULL, FALSE, FALSE, "ExampleSlot");
	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = hEvent;

	// Mailslot handle "hSlot1" is declared globally. 

	fResult = GetMailslotInfo(m_hSlotEvent, // mailslot handle 
		(LPDWORD) NULL,               // no maximum message size 
		&cbMessage,                   // size of next message 
		&cMessage,                    // number of messages 
		(LPDWORD) NULL);              // no read time-out 

	if (!fResult) 
	{ 
		
		return ; 
	} 

	if (cbMessage == MAILSLOT_NO_MESSAGE) 
	{ 
		return ; 
	} 

	cAllMessages = cMessage; 
	
	UINT nCount = 0;
	while ((cMessage != 0) && (nCount<200))  // retrieve all messages
	{ 
		// Create a message-number string. 

		wsprintf((LPSTR) achID, 
			"\nMessage #%d of %d\n", cAllMessages - cMessage + 1, 
			cAllMessages); 

		// Allocate memory for the message. 

		lpszBuffer = (LPSTR) GlobalAlloc(GPTR, 
			lstrlen((LPSTR) achID) + cbMessage); 

		lpszBuffer[0] = '\0'; 

		fResult = ReadFile(m_hSlotEvent, 
			lpszBuffer, 
			cbMessage, 
			&cbRead, 
			&ov); 

		if (!fResult) 
		{ 
			GlobalFree((HGLOBAL) lpszBuffer); 
			return ; 
		} 

		// Concatenate the message and the message-number string. 

		//lstrcat(lpszBuffer, (LPSTR) achID); 

		// Display the message. 
		if(m_lstEvent.GetCount() > 100)
			m_lstEvent.DeleteString(0);
		
		m_lstEvent.AddString(lpszBuffer);
		m_lstEvent.SetCurSel(m_lstEvent.GetCount()-1);
		EventLog(lpszBuffer);
		nCount++;
		
		

		GlobalFree((HGLOBAL) lpszBuffer); 

		fResult = GetMailslotInfo(m_hSlotEvent, // mailslot handle 
			(LPDWORD) NULL,               // no maximum message size 
			&cbMessage,                   // size of next message 
			&cMessage,                    // number of messages 
			(LPDWORD) NULL);              // no read time-out 

		if (!fResult) 
		{ 
			return ; 
		} 
	} 
	return ; 
}

void CHkSvrMonitorDlg::GetParam(LPSTR strmsg)
{
	m_Params.clear();
	string strM = strmsg;
	string::size_type pos;
	while (strM.length() > 0) {
		_RUN_PARAM runparam;
		pos = strM.find("|");
		if (pos == string::npos) {
			break;
		}

		runparam.strName = strM.substr(0, pos++);
		strM = strM.substr(pos, string::npos);
		
		pos = strM.find("|");
		if (pos == string::npos) {
			break;
		}
		runparam.strValue = strM.substr(0, pos++);
		strM = strM.substr(pos, string::npos);


		m_Params.push_back(runparam);
	}
	m_lstParam.SetItemCount((int)m_Params.size());
	m_lstParam.Invalidate();

}

void CHkSvrMonitorDlg::ReadParamMailSlot(void)
{
	DWORD cbMessage, cMessage, cbRead; 
	BOOL fResult; 
	LPSTR lpszBuffer; 
	CHAR achID[80]; 
	DWORD cAllMessages; 
	HANDLE hEvent;
	OVERLAPPED ov;

	cbMessage = cMessage = cbRead = 0; 

	hEvent = CreateEvent(NULL, FALSE, FALSE, "ExampleSlot");
	ov.Offset = 0;
	ov.OffsetHigh = 0;
	ov.hEvent = hEvent;

	// Mailslot handle "hSlot1" is declared globally. 

	fResult = GetMailslotInfo(m_hSlotParam, // mailslot handle 
		(LPDWORD) NULL,               // no maximum message size 
		&cbMessage,                   // size of next message 
		&cMessage,                    // number of messages 
		(LPDWORD) NULL);              // no read time-out 

	if (!fResult) 
	{ 

		return ; 
	} 

	if (cbMessage == MAILSLOT_NO_MESSAGE) 
	{ 
		return ; 
	} 

	cAllMessages = cMessage; 

	while (cMessage != 0)  // retrieve all messages
	{ 
		// Create a message-number string. 

		wsprintf((LPSTR) achID, 
			"\nMessage #%d of %d\n", cAllMessages - cMessage + 1, 
			cAllMessages); 

		// Allocate memory for the message. 

		lpszBuffer = (LPSTR) GlobalAlloc(GPTR, 
			lstrlen((LPSTR) achID) + cbMessage); 

		lpszBuffer[0] = '\0'; 

		fResult = ReadFile(m_hSlotParam, 
			lpszBuffer, 
			cbMessage, 
			&cbRead, 
			&ov); 

		if (!fResult) 
		{ 
			GlobalFree((HGLOBAL) lpszBuffer); 
			return ; 
		} 

		// Concatenate the message and the message-number string. 

		//lstrcat(lpszBuffer, (LPSTR) achID); 

		// Display the message. 

		GetParam(lpszBuffer);


		GlobalFree((HGLOBAL) lpszBuffer); 

		fResult = GetMailslotInfo(m_hSlotParam, // mailslot handle 
			(LPDWORD) NULL,               // no maximum message size 
			&cbMessage,                   // size of next message 
			&cMessage,                    // number of messages 
			(LPDWORD) NULL);              // no read time-out 

		if (!fResult) 
		{ 
			return ; 
		} 
	} 
	return ; 
}

void CHkSvrMonitorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);
		PostMessage(WM_MY_TRAY_MESSAGE, 0, 0);
	}
	else
	{
		ReAlignControls();
	}
	
	// TODO: Add your message handler code here
}

//void CHkSvrMonitorDlg::OnHdnGetdispinfoLstParam(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHDDISPINFO pDispInfo = reinterpret_cast<LPNMHDDISPINFO>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}

void CHkSvrMonitorDlg::OnLvnGetdispinfoLstParam(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pDispInfo->item.iItem != -1)
	{
		if ((pDispInfo->item.mask&LVIF_IMAGE)
			||(pDispInfo->item.mask&LVIF_TEXT))
		{
			switch(pDispInfo->item.iSubItem) {
			case 0:
				sprintf(pDispInfo->item.pszText, "%s", m_Params[pDispInfo->item.iItem].strName.c_str());
				break;
			case 1:
				sprintf(pDispInfo->item.pszText, "%s", m_Params[pDispInfo->item.iItem].strValue.c_str());				
				break;
			}
		}
	}
	*pResult = 0;
}

void CHkSvrMonitorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
}

void CHkSvrMonitorDlg::ReAlignControls(void)
{
	CRect rect;
	GetClientRect(&rect);
	int cx,cy;
	cx = rect.Width();
	cy = rect.Height();
	if(m_lstParam.GetSafeHwnd())
		m_lstParam.MoveWindow(10, 10, 250, cy-20);
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC_BORDER);
	if(pWnd)
	{
		//pWnd->MoveWindow(265, 10, 350, 36);
		pWnd->MoveWindow(265, 10, 180, 36);
	}
	pWnd = GetDlgItem(IDC_STATUS_NAME);
	if(pWnd)
	{
		pWnd->MoveWindow(280, 20, 60, 15);
	}
	pWnd = GetDlgItem(IDC_BMP_STATUS);
	if(pWnd)
	{
		pWnd->MoveWindow(350, 12, 32, 32);
	}
	pWnd = GetDlgItem(IDC_STATUS);
	if(pWnd)
	{
		pWnd->MoveWindow(390, 20, 50, 15);
	}
	pWnd = GetDlgItem(IDC_BTN_STARTSVR);
	if(pWnd)
	{
		pWnd->MoveWindow(460, 13, 80, 30);
		//pWnd->MoveWindow(440, 100, 80, 30);
	}
	pWnd = GetDlgItem(IDC_BTN_STOPSVR);
	if(pWnd)
	{
		pWnd->MoveWindow(550, 13, 80, 30);
		//pWnd->MoveWindow(530, 100, 80, 30);
	}

	pWnd = GetDlgItem(IDC_BTN_CLEAR);
	if(pWnd)
	{
		if (cx > 710)
		{
			pWnd->MoveWindow(cx - 90, 13, 80, 30);
		}
		else
		{
			pWnd->MoveWindow(620, 13, 80, 30);
		}
		
	}
	
	if(m_TabDisType.GetSafeHwnd())
		m_TabDisType.MoveWindow(265, 50, cx - 275, 24);
	if(m_lstEvent.GetSafeHwnd())
		m_lstEvent.MoveWindow(265, 74, cx - 275, cy-84);
}

void CHkSvrMonitorDlg::OnBnClickedBtnClear()
{
	// TODO: Add your control notification handler code here
	m_lstEvent.ResetContent();
	if (m_bDisplayPause)
	{
		SetTimer(0, 100, NULL);
		m_bDisplayPause = false;
	}
}

void CHkSvrMonitorDlg::RefreshSvrStatus(void)
{
	// 1 ���ڲ�����  2���ڵ���û������ 3������ 4����ʧ��
	
	switch(ExistsSrv("ExpertSmsSvr")) {
	case 1:
		m_btnStartSvr.EnableWindow(FALSE);
		m_btnStopSvr.EnableWindow(TRUE);
		m_IconStatus.SetIcon(AfxGetApp()->LoadIcon(IDI_RUN));
		if(m_strStatus != "����")
		{
			m_strStatus = "����";
			PostMessage(WM_MY_TRAY_MESSAGE, 1, 0);
		}		
		m_trayIcon.SetIcon(IDI_RUN);
		break;
	case 2:
		m_btnStartSvr.EnableWindow(TRUE);
		m_btnStopSvr.EnableWindow(FALSE);
		m_IconStatus.SetIcon(AfxGetApp()->LoadIcon(IDI_STOP));
		if(m_strStatus != "ֹͣ")
		{
			m_strStatus = "ֹͣ";
			PostMessage(WM_MY_TRAY_MESSAGE, 2, 0);
		}	
		m_trayIcon.SetIcon(IDI_STOP);
		break;
	case 3:
		m_btnStartSvr.EnableWindow(FALSE);
		m_btnStopSvr.EnableWindow(FALSE);
		m_IconStatus.SetIcon( AfxGetApp()->LoadIcon(IDI_NOTINSTALL));
		if(m_strStatus != "δ��װ")
		{
			m_strStatus = "δ��װ";
			PostMessage(WM_MY_TRAY_MESSAGE, 3, 0);
		}
		m_trayIcon.SetIcon(IDI_NOTINSTALL);
		break;
	case 4:
		m_IconStatus.SetIcon( AfxGetApp()->LoadIcon(IDI_NOTINSTALL));
		m_btnStartSvr.EnableWindow(FALSE);
		m_btnStopSvr.EnableWindow(FALSE);
		if(m_strStatus != "δ֪����")
		{
			m_strStatus = "δ֪����";
			PostMessage(WM_MY_TRAY_MESSAGE, 4, 0);
		}
		m_trayIcon.SetIcon(IDI_NOTINSTALL);
		break;
	}
	UpdateData(FALSE);
}




void CHkSvrMonitorDlg::OnBnClickedBtnStartsvr()
{
	// TODO: Add your control notification handler code here
	if (MessageBox("ȷ��Ҫ����ר�ҳ�ȡ���ŷ�����?", "ȷ��",
		MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) == IDYES) {
			StartSrv("ExpertSmsSvr");
	}	
}

void CHkSvrMonitorDlg::OnBnClickedBtnStopsvr()
{
	// TODO: Add your control notification handler code here
	if (MessageBox("�رշ��񽫻�Ӱ��ר�ҳ�ȡ����֪ͨ,ȷ��Ҫ�رշ�����?", "ȷ��",
		MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) == IDYES) {
		StopSrv("ExpertSmsSvr");
	}
	
}

void CHkSvrMonitorDlg::OnDlgOpen()
{
	ShowWindow(SW_NORMAL);	
	SetForegroundWindow();
}

void CHkSvrMonitorDlg::OnDlgExit()
{	
	SendMessage(WM_CLOSE);
}

int CHkSvrMonitorDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_trayIcon.SetNotificationWnd(this, WM_MY_TRAY_NOTIFICATION);
	m_trayIcon.SetIcon(IDI_NOTINSTALL);

	return 0;
}

void CHkSvrMonitorDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();	
}

LRESULT CHkSvrMonitorDlg::OnIconMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam) {
	case 0:
		m_trayIcon.ShowBalloonTip("ר�ҳ�ȡ���ŷ�����ӳ���", "", 1000);
		break;
	case 1:
		m_trayIcon.ShowBalloonTip("��������", "", 100);
		break;
	case 2:
		m_trayIcon.ShowBalloonTip("����ֹͣ ","", 100);
		break;
	case 3:
		m_trayIcon.ShowBalloonTip("����δ��װ ","", 100);
		break;
	case 4:
		m_trayIcon.ShowBalloonTip("����δ֪���� ","", 100, NIIF_ERROR);
		break;
	}	
	return 0;
}
void CHkSvrMonitorDlg::OnLbnDblclkLbEvent()
{
	// TODO: Add your control notification handler code here
	m_bDisplayPause = !m_bDisplayPause;
	if (m_bDisplayPause)
	{
		KillTimer(0);
		m_lstEvent.AddString("��ʾ��ͣ,˫������");
	}
	else
	{
		SetTimer(0, 100, NULL);
		m_lstEvent.AddString("��ʼ��ʾ�������¼�");
	}
	m_lstEvent.SetCurSel(m_lstEvent.GetCount()-1);
}



void CHkSvrMonitorDlg::OnLbnSelchangeLbEvent()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
