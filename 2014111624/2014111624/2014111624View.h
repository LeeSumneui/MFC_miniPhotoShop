
// 2014111624View.h : CMy2014111624View Ŭ������ �������̽�
//

#pragma once


class CMy2014111624View : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMy2014111624View();
	DECLARE_DYNCREATE(CMy2014111624View)

// Ư���Դϴ�.
public:
	CMy2014111624Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy2014111624View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReverseImg();
	BITMAPINFO *BmInfo;
	int height;
	int width;
	unsigned char m_RevImg[256][256];
	afx_msg void OnConstAdd();
	afx_msg void OnConstSub();
	afx_msg void OnConstMul();
	afx_msg void OnConstDiv();
	afx_msg void OnFrmAdd();
	afx_msg void OnFrmSub();
	afx_msg void OnFrmMul();
	afx_msg void OnImghisto();
	afx_msg void OnBinarization();
	afx_msg void OnBinDynamic();
	afx_msg void OnHistoEqual();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistoUpstretch();
	afx_msg void OnHistoSpec();
	afx_msg void OnBinarOtzu();
	afx_msg void OnBinarAdap();
	afx_msg void OnEdgePrewitt();
	afx_msg void OnEdgeSobel();
	afx_msg void OnSharpeningLaplacian();
};

#ifndef _DEBUG  // 2014111624View.cpp�� ����� ����
inline CMy2014111624Doc* CMy2014111624View::GetDocument() const
   { return reinterpret_cast<CMy2014111624Doc*>(m_pDocument); }
#endif

