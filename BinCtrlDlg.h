#pragma once
#include "afxcmn.h"


// CBinCtrlDlg ��ȭ �����Դϴ�.

class CBinCtrlDlg : public CDialog
{
	DECLARE_DYNAMIC(CBinCtrlDlg)

public:
	CBinCtrlDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBinCtrlDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	
	int m_binValDisp;
	CSliderCtrl m_ctrlSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
};
