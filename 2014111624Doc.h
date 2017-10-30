
// 2014111624Doc.h : CMy2014111624Doc Ŭ������ �������̽�
//


#pragma once


class CMy2014111624Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMy2014111624Doc();
	DECLARE_DYNCREATE(CMy2014111624Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMy2014111624Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char m_InImg[256][256];
	unsigned char m_OutImg[256][256];
	unsigned char m_InImg1[256][256];
	unsigned char m_InImg2[256][256];
	void TwoImgLoad(void);
	void ImgHisto(int height, int width);

	protected:
	int m_HistoArr[256];
public:
	void BinThresh(int height, int width, int threshVal);
	void HistoEqual(int height, int width);
	void HistoStretch(int height, int width);
	void HistoUpstretch(int height, int width, int lowPercent, int highPercent);
	void HistoSpec(int height, int width);
	void Otzu_Threshold(unsigned char * orgImg, unsigned char * outImg, int height, int width);
	void AdaptiveBinarization(unsigned char* orgImg, unsigned char* outImg, int height, int width);
	void EdgePrewitt(int height, int width);
	void EdgeSobel(int height, int width);
	void SharpeningLaplacian(int height, int width);
};
