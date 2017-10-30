
// 2014111624View.cpp : CMy2014111624View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "2014111624.h"
#endif

#include "BinCtrlDlg.h"

#include "2014111624Doc.h"
#include "2014111624View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2014111624View

IMPLEMENT_DYNCREATE(CMy2014111624View, CScrollView)

BEGIN_MESSAGE_MAP(CMy2014111624View, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy2014111624View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_REVERSE_IMG, &CMy2014111624View::OnReverseImg)
	ON_COMMAND(IDM_CONST_ADD, &CMy2014111624View::OnConstAdd)
	ON_COMMAND(IDM_CONST_SUB, &CMy2014111624View::OnConstSub)
	ON_COMMAND(IDM_CONST_MUL, &CMy2014111624View::OnConstMul)
	ON_COMMAND(IDM_CONST_DIV, &CMy2014111624View::OnConstDiv)
	ON_COMMAND(IDM_FRM_ADD, &CMy2014111624View::OnFrmAdd)
	ON_COMMAND(IDM_FRM_SUB, &CMy2014111624View::OnFrmSub)
	ON_COMMAND(IDM_FRM_MUL, &CMy2014111624View::OnFrmMul)
	ON_COMMAND(IDM_IMGHISTO, &CMy2014111624View::OnImghisto)
	ON_COMMAND(IDM_BINARIZATION, &CMy2014111624View::OnBinarization)
	ON_COMMAND(IDM_BIN_DYNAMIC, &CMy2014111624View::OnBinDynamic)
	ON_COMMAND(IDM_HISTO_EQUAL, &CMy2014111624View::OnHistoEqual)
	ON_COMMAND(IDM_HISTO_STRETCH, &CMy2014111624View::OnHistoStretch)
	ON_COMMAND(IDM_HISTO_UPSTRETCH, &CMy2014111624View::OnHistoUpstretch)
	ON_COMMAND(IDM_HISTO_SPEC, &CMy2014111624View::OnHistoSpec)
	ON_COMMAND(IDM_BINAR_OTZU, &CMy2014111624View::OnBinarOtzu)
	ON_COMMAND(IDM_BINAR_ADAP, &CMy2014111624View::OnBinarAdap)
	ON_COMMAND(IDM_EDGE_PREWITT, &CMy2014111624View::OnEdgePrewitt)
	ON_COMMAND(IDM_EDGE_SOBEL, &CMy2014111624View::OnEdgeSobel)
	ON_COMMAND(IDM_SHARPENING_LAPlACIAN, &CMy2014111624View::OnSharpeningLaplacian)
END_MESSAGE_MAP()

// CMy2014111624View ����/�Ҹ�

CMy2014111624View::CMy2014111624View()
	: BmInfo(NULL)
	, height(0)
	, width(0)
	//, m_RevImg(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	height = width = 256;
	int rwsize = (((width*8)+31)/32*4);
	BmInfo = (BITMAPINFO*) malloc(sizeof(BITMAPINFO)+256*sizeof(RGBQUAD));

	BmInfo->bmiHeader.biBitCount = 8;
	BmInfo->bmiHeader.biClrUsed = 256;
	BmInfo->bmiHeader.biHeight = 256;
	BmInfo->bmiHeader.biWidth = 256;
	BmInfo->bmiHeader.biSize = 40;
	BmInfo->bmiHeader.biSizeImage = 256*256*8; //rwsize*BmInfo->bmiHeader.biHeight;
	BmInfo->bmiHeader.biPlanes = 1;
	BmInfo->bmiHeader.biClrImportant = 256;
	BmInfo->bmiHeader.biCompression = 0;
	BmInfo->bmiHeader.biXPelsPerMeter = 0;
	BmInfo->bmiHeader.biYPelsPerMeter = 0;
	
	for(int i = 0; i <256; i++)
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbBlue = BmInfo->bmiColors[i].rgbGreen = i;
}



CMy2014111624View::~CMy2014111624View()
{
	free(BmInfo);
}

BOOL CMy2014111624View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMy2014111624View �׸���

void CMy2014111624View::OnDraw(CDC* pDC)
{
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	for(int i =  0; i<height; i++)
		for(int j = 0; j<width; j++)
			m_RevImg[i][j] = pDoc->m_InImg[height-i-1][j];
	SetDIBitsToDevice(pDC->GetSafeHdc(),0,0,width,height,0,0,0,height,m_RevImg,BmInfo,DIB_RGB_COLORS);

	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			m_RevImg[i][j] = pDoc->m_OutImg[height-i-1][j];
	SetDIBitsToDevice(pDC->GetSafeHdc(),300,0,width,height,0,0,0,height,m_RevImg,BmInfo,DIB_RGB_COLORS);

	/*	for(int i = 0; i< 256; i++)
		{
			for(int j = 0; j<256; j++)
			{
				unsigned char InVal = pDoc->m_InImg[i][j]; 
				unsigned char OutVal = pDoc->m_OutImg[i][j]; 
				pDC->SetPixel(j,i,RGB(InVal,InVal,InVal));
				pDC->SetPixel(j+300,i,RGB(OutVal,OutVal,OutVal));
			}
		}*/
}

void CMy2014111624View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMy2014111624View �μ�


void CMy2014111624View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy2014111624View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy2014111624View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy2014111624View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMy2014111624View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy2014111624View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy2014111624View ����

#ifdef _DEBUG
void CMy2014111624View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy2014111624View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy2014111624Doc* CMy2014111624View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2014111624Doc)));
	return (CMy2014111624Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2014111624View �޽��� ó����


void CMy2014111624View::OnReverseImg()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	for(int i = 0; i<256; i++)
		for(int j = 0; j<256; j++)
		{
			pDoc->m_OutImg[i][j] = 255-pDoc->m_InImg[i][j];
		}
	Invalidate(FALSE);
}


void CMy2014111624View::OnConstAdd()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for(int i = 0; i< height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			int tempVal = pDoc -> m_InImg[i][j] + 60;
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char) tempVal;
		}
	}
	Invalidate(FALSE);
}


void CMy2014111624View::OnConstSub()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for(int i = 0; i< height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			int tempVal = pDoc -> m_InImg[i][j] - 60;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char) tempVal;
		}
	}
	Invalidate(FALSE);
}


void CMy2014111624View::OnConstMul()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for(int i = 0; i< height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			int tempVal = pDoc -> m_InImg[i][j] * 1.4;
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char) tempVal;
		}
	}
	Invalidate(FALSE);
}


void CMy2014111624View::OnConstDiv()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for(int i = 0; i< height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			int tempVal = pDoc -> m_InImg[i][j] / 1.4;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char) tempVal;
		}
	}
	Invalidate(FALSE);
}


void CMy2014111624View::OnFrmAdd()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc-> TwoImgLoad();

	for(int i = 0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			int tempVal = pDoc -> m_InImg1[i][j] + pDoc-> m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char) tempVal;
		}
	}

	Invalidate(FALSE);
}


void CMy2014111624View::OnFrmSub()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc-> TwoImgLoad();

	for(int i = 0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			int tempVal = pDoc -> m_InImg1[i][j] - pDoc-> m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char) tempVal;
		}
	}

	Invalidate(FALSE);
}


void CMy2014111624View::OnFrmMul()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc-> TwoImgLoad();

	for(int i = 0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			int tempVal = pDoc -> m_InImg1[i][j] & pDoc-> m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char) tempVal;
		}
	}

	Invalidate(FALSE);
}


void CMy2014111624View::OnImghisto()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->ImgHisto(256,256);
	Invalidate(FALSE);
}


void CMy2014111624View::OnBinarization()
{
	CMy2014111624Doc* pDoc = GetDocument();

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	for(int i =0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
		{
			if(pDoc->m_InImg[i][j] > 100)
				pDoc-> m_OutImg[i][j] = 255;
			else
			pDoc->m_OutImg[i][j] = 0;
		}

	}
		Invalidate(FALSE);
}


void CMy2014111624View::OnBinDynamic()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CBinCtrlDlg pbinCtrlDlg;
	pbinCtrlDlg.DoModal();
}


void CMy2014111624View::OnHistoEqual()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->HistoEqual(256,256);

	Invalidate(FALSE);
}


void CMy2014111624View::OnHistoStretch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->HistoStretch(256,256);

	Invalidate(FALSE);
}


void CMy2014111624View::OnHistoUpstretch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->HistoUpstretch(256,256,20,20);

	Invalidate(FALSE);
}


void CMy2014111624View::OnHistoSpec()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFileDialog opendlg1(TRUE); CFile file;
		if(opendlg1.DoModal()==IDOK)
		{ // ���� ������׷��� ���� �Է�
			file.Open(opendlg1.GetPathName(), CFile::modeRead);
			file.Read(pDoc->m_InImg1, sizeof(pDoc->m_InImg1));
			file.Close();
		}
			pDoc->HistoSpec(256, 256) ;
			Invalidate(FALSE); //ȭ�� ����
}


void CMy2014111624View::OnBinarOtzu()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int height = 256, width = 256;
	unsigned char* orgImg = new unsigned char [height*width];
	unsigned char* outImg = new unsigned char [height*width];
		for(int i=0; i<height; i++)
			for(int j=0; j<width; j++)
			orgImg[i*width+j] = pDoc->m_InImg[i][j] ;
			
		pDoc->Otzu_Threshold(orgImg, outImg, height, width);

		for(int i=0; i<height; i++) 
			for(int j=0; j<width; j++)
				pDoc-> m_OutImg[i][j] = outImg[i*width+j];
	Invalidate(FALSE); //ȭ�� ����
}


void CMy2014111624View::OnBinarAdap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int height = 256, width = 256;
	unsigned char* orgImg = new unsigned char [height*width];
	unsigned char* outImg = new unsigned char [height*width];
	for(int i=0; i<height; i++) 
		for(int j=0; j<width; j++)
			orgImg[i*width+j] = pDoc->m_InImg[i][j];
	pDoc->AdaptiveBinarization(orgImg, outImg, height, width);
	for(int i=0; i<height; i++) 
		for(int j=0; j<width; j++)
			pDoc-> m_OutImg[i][j] = outImg[i*width+j];
	Invalidate(FALSE); //ȭ�� ����
}


void CMy2014111624View::OnEdgePrewitt()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->EdgePrewitt(256,256);
	Invalidate(FALSE);
}


void CMy2014111624View::OnEdgeSobel()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->EdgeSobel(256,256);
	Invalidate(FALSE);
}


void CMy2014111624View::OnSharpeningLaplacian()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMy2014111624Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->SharpeningLaplacian(256,256);
	Invalidate(FALSE);
}
