// BinCtrlDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "2014111624.h"
#include "BinCtrlDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "2014111624Doc.h"
#include "2014111624View.h"

// CBinCtrlDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBinCtrlDlg, CDialog)

CBinCtrlDlg::CBinCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBinCtrlDlg::IDD, pParent)
	, m_binValDisp(0)
{

}

CBinCtrlDlg::~CBinCtrlDlg()
{
}

void CBinCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_binValDisp);
	DDV_MinMaxInt(pDX, m_binValDisp, 0, 255);
	DDX_Control(pDX, IDC_SLIDER1, m_ctrlSlider);
}


BEGIN_MESSAGE_MAP(CBinCtrlDlg, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBinCtrlDlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_EDIT1, &CBinCtrlDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CBinCtrlDlg �޽��� ó�����Դϴ�.


BOOL CBinCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ctrlSlider.SetRange(0,255);
	m_ctrlSlider.SetPos(128);

	m_binValDisp = m_ctrlSlider.GetPos();
	UpdateData(FALSE);

	return TRUE;  
	// return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CBinCtrlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame *pChild = (CChildFrame*) pFrame->GetActiveFrame() ;
	ASSERT(pChild);
	CMy2014111624Doc *pDoc = (CMy2014111624Doc*) pChild->GetActiveDocument() ;
	ASSERT(pDoc);
	CMy2014111624View *pView = (CMy2014111624View *) pChild->GetActiveView() ;
	ASSERT(pView);

	//�����̴��� ������ġ�� ������
	m_binValDisp = m_ctrlSlider.GetPos();
	UpdateData(FALSE);

	pDoc->BinThresh(256, 256, m_binValDisp);

	pView->Invalidate(FALSE);

	*pResult = 0;
}


void CBinCtrlDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
