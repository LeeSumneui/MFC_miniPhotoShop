#pragma once
#include "afxcmn.h"


// CBinCtrlDlg 대화 상자입니다.

class CBinCtrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CBinCtrlDlg)

public:
	CBinCtrlDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBinCtrlDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	
	int m_binValDisp;
	CSliderCtrl m_ctrlSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
};
