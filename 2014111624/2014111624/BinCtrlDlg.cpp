// BinCtrlDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "2014111624.h"
#include "BinCtrlDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "2014111624Doc.h"
#include "2014111624View.h"

// CBinCtrlDlg 대화 상자입니다.

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


// CBinCtrlDlg 메시지 처리기입니다.


BOOL CBinCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ctrlSlider.SetRange(0,255);
	m_ctrlSlider.SetPos(128);

	m_binValDisp = m_ctrlSlider.GetPos();
	UpdateData(FALSE);

	return TRUE;  
	// return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBinCtrlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame *pChild = (CChildFrame*) pFrame->GetActiveFrame() ;
	ASSERT(pChild);
	CMy2014111624Doc *pDoc = (CMy2014111624Doc*) pChild->GetActiveDocument() ;
	ASSERT(pDoc);
	CMy2014111624View *pView = (CMy2014111624View *) pChild->GetActiveView() ;
	ASSERT(pView);

	//슬라이더의 현재위치를 가져옴
	m_binValDisp = m_ctrlSlider.GetPos();
	UpdateData(FALSE);

	pDoc->BinThresh(256, 256, m_binValDisp);

	pView->Invalidate(FALSE);

	*pResult = 0;
}


void CBinCtrlDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
