// HkSvrMonitorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <string>
#include <vector>
#include "trayicon.h"
using namespace std;

typedef struct {
	string strName;
	string strValue;
}_RUN_PARAM;

// CHkSvrMonitorDlg 对话框
class CHkSvrMonitorDlg : public CDialog
{
// 构造
public:
	CHkSvrMonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HKSVRMONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	bool m_bDisplayPause;
	BOOL m_bShutdown;
	HICON m_hIcon;
	CTrayIcon m_trayIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListBox m_lstEvent;
	CListCtrl m_lstParam;
	bool InitMailSlot(void);
	afx_msg void OnTimer(UINT nIDEvent);
private:
	void ReadMailSlot(void);
	void ReadParamMailSlot(void);
	void GetParam(LPSTR strmsg);
	HANDLE m_hSlotEvent, m_hSlotParam;
	vector<_RUN_PARAM> m_Params;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnHdnGetdispinfoLstParam(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnGetdispinfoLstParam(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	void ReAlignControls(void);
	afx_msg void OnBnClickedBtnClear();
	void RefreshSvrStatus(void);
	afx_msg void OnBnClickedBtnStartsvr();
	afx_msg void OnBnClickedBtnStopsvr();
	afx_msg void OnDlgExit();
	afx_msg void OnDlgOpen();
	afx_msg LRESULT OnIconMessage(WPARAM wParam, LPARAM lParam);
	CString m_strStatus;
	CButton m_btnStartSvr;
	CButton m_btnStopSvr;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	CStatic m_IconStatus;
	afx_msg void OnLbnDblclkLbEvent();
	CTabCtrl m_TabDisType;
	afx_msg void OnLbnSelchangeLbEvent();
};
