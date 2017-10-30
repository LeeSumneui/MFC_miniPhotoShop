
// 2014111624Doc.cpp : CMy2014111624Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "2014111624.h"
#include "math.h"
#endif

#include "2014111624Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy2014111624Doc

IMPLEMENT_DYNCREATE(CMy2014111624Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy2014111624Doc, CDocument)
END_MESSAGE_MAP()


// CMy2014111624Doc 생성/소멸

CMy2014111624Doc::CMy2014111624Doc()
	//: m_InImg(0)
	//: m_OutImg(0)
	//: m_InImg1(0)
	//, m_InImg2(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMy2014111624Doc::~CMy2014111624Doc()
{
}

BOOL CMy2014111624Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy2014111624Doc serialization

void CMy2014111624Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar.Write(m_OutImg, 256*256);
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		CFile *infile = ar.GetFile();
		if(infile->GetLength()!=256*256)
		{
			AfxMessageBox((LPCTSTR)"파일 크기 오류");
			return;
		}
		ar.Read(m_InImg,(unsigned int)infile->GetLength());
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy2014111624Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMy2014111624Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy2014111624Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMy2014111624Doc 진단

#ifdef _DEBUG
void CMy2014111624Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy2014111624Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy2014111624Doc 명령


void CMy2014111624Doc::TwoImgLoad(void)
{
	CFileDialog opendlg1(TRUE);
	CFile file;

	if(opendlg1.DoModal()==IDOK)
	{
		file.Open(opendlg1.GetPathName(),CFile::modeRead);
		file.Read(m_InImg1,sizeof(m_InImg1));
		file.Close();
	}

	CFileDialog opendlg2(TRUE);
	CFile file2;

	if(opendlg2.DoModal()==IDOK)
	{
		file2.Open(opendlg2.GetPathName(),CFile::modeRead);
		file2.Read(m_InImg2,sizeof(m_InImg2));
		file2.Close();
	}
}

void CMy2014111624Doc::ImgHisto(int height, int width)
{
	for(int i=0;i<256;i++) m_HistoArr[i] = 0;
	for(int i=0;i<height;i++)
	{
		for(int j = 0; j<width; j++)
		{
			int gv = (int) m_InImg[i][j];
			m_HistoArr[gv]++;
		}
	}

	int vmin = 1000000; int vmax = 0;
		for(int i = 0; i<256; i++)
			{
				if(m_HistoArr[i] <= vmin) vmin = m_HistoArr[i];
				if(m_HistoArr[i] >= vmax) vmax = m_HistoArr[i];
			}
		float vd = (float)(vmax - vmin);

		for(int i = 0; i<256; i++)
			{
				m_HistoArr[i] = (int)(((float) m_HistoArr[i] - vmin)*255.0/vd);
			}

		for(int i = 0; i < height; i++)
			{
				for(int j=0; j< width; j++) 
				{ m_OutImg[i][j] = 255; }
			}
		for(int j = 0;j<width; j++)
			{
				for(int i = 0; i<m_HistoArr[j];i++)
					m_OutImg[255-i][j] = 0;
			}
}

void CMy2014111624Doc::BinThresh(int height, int width, int threshVal)
{
	for(int i = 0; i<height; i++)
		for(int j = 0; j < width; j++)
		{
			if(m_InImg[i][j] > threshVal) m_OutImg[i][j] = 255;
			else m_OutImg[i][j] = 0;
		}
}


void CMy2014111624Doc::HistoEqual(int height, int width)
{
	unsigned int *histogram = new unsigned int[256];
	unsigned int *sum_hist = new unsigned int[256];

	for(int i = 0; i<256; i++) histogram[i] = 0;

	for(int i=0; i< height; i++)
	{
		for(int j = 0; j<width; j++)
			histogram[m_InImg[i][j]]++;
	}
	int sum =0;
	float scale_factor = 255.0f/(float)(height*width);

	for(int i = 0; i <256; i++)
	{
		sum += histogram[i];
		sum_hist[i]=(int)((sum*scale_factor)+0.5);
	}

	for(int i = 0; i<height; i++)
	{
		for(int j = 0; j<width; j++)
			m_OutImg[i][j] = sum_hist[m_InImg[i][j]];
	}

	delete []histogram;
	delete []sum_hist;
}


void CMy2014111624Doc::HistoStretch(int height, int width)
{
	int lowvalue = 255;
	int highvalue = 0;

	for(int i = 0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(m_InImg[i][j]<lowvalue) lowvalue = m_InImg[i][j];
			if(m_InImg[i][j]>highvalue) highvalue = m_InImg[i][j];
		}
	}
	float mult = 255.0f/(float)(highvalue-lowvalue);
	for(int i = 0; i<height; i++)
		for(int j = 0; j<width; j++)
			m_OutImg[i][j] = (unsigned char)((m_InImg[i][j] - lowvalue)*mult);
}


void CMy2014111624Doc::HistoUpstretch(int height, int width, int lowPercent, int highPercent)
{	
	unsigned int *histogram = new unsigned int [256];
	for(int i = 0; i<256;i++) histogram[i] = 0;

	for(int i = 0; i<height; i++)
		for(int j = 0; j<width; j++) 
			histogram[m_InImg[i][j]]++;

	unsigned int runsum = 0;
	int lowthresh = 0;
	int highthresh = 255;

	for(int i = 0; i< 256; i++)
	{
		runsum += histogram[i];
		if((runsum*100.0/(float)(height*width)) >= lowPercent)
		{
			lowthresh = i;
			break;
		}
	}
	runsum = 0;
	for(int i = 255; i>=0; i--)
	{
		runsum += histogram[i];
		if((runsum*100.0/(float)(height*width)) >= highPercent)
		{
			highthresh = i;
			break;
		}
	}

	unsigned char *LUT=new unsigned char [256];

	for(int i=0; i<lowthresh; i++) LUT[i]=0;
	for(int i=255; i>highthresh; i--) LUT[i]=255;
	
	float scale = 255.0f/(float) (highthresh-lowthresh);
	for(int i=lowthresh; i<=highthresh; i++)
		LUT[i] = (unsigned char) ((i-lowthresh) * scale);

	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			m_OutImg[i][j] = LUT[m_InImg[i][j]];

	delete []histogram; delete []LUT;

}


void CMy2014111624Doc::HistoSpec(int height, int width)
{
	unsigned int *histogram = new unsigned int [256];
	unsigned int *sum_hist = new unsigned int [256];
	unsigned int *desired_histogram = new unsigned int [256];
	unsigned int *desired_sum_hist = new unsigned int [256];

	// histogram배열을 초기화
	for(int i=0; i<256; i++) 
		histogram[i]=desired_histogram[i]=0;
	for(int i=0; i<height; i++) // 영상의 histogram 계산
		for(int j=0; j<width; j++) 
		{
			histogram[m_InImg[i][j]]++; // 입력 영상
			desired_histogram[m_InImg1[i][j]]++; // 지정 영상
		}
	// histogram의 정규화된 합을 계산
	int sum=0;
	float scale_factor=255.0f/(float)(height*width);
	for(int i=0; i<256; i++) 
	{
		sum += histogram[i];
		sum_hist[i] =(int)((sum*scale_factor) + 0.5);
	}
	// desired histogram에 대한 정규화된 합을 계산
	sum=0;

	for(int i=0; i<256; i++) 
	{
		sum += desired_histogram[i];
		desired_sum_hist[i] =(int)(sum * scale_factor);
	}
		// 가장 가까운 정규화합 히스토그램값을 주는 index를 찾음
		int *inv_hist = new int [256];
		int hist_min, hist_index, hist_diff;

		for(int i=0; i<256; i++) 
		{
			hist_min = 1000;

			for(int j=0; j<256; j++) 
			{
				hist_diff = labs(sum_hist[i]-desired_sum_hist[j]);
				if(hist_diff < hist_min) 
				{
					hist_min = hist_diff;
					hist_index = j;
				}
			}
			inv_hist[i] = hist_index; // 찾은 인덱스를 저장함
		}
			// 역 히스토그램 변환
			for(int i=0; i<height; i++)
			for(int j=0; j<width; j++)
			m_OutImg[i][j]=inv_hist[m_InImg[i][j]];
			// 메모리해제
			delete []inv_hist;
			delete []histogram;
			delete []desired_histogram;
			delete []sum_hist;
			delete []desired_sum_hist;
		}



void CMy2014111624Doc::Otzu_Threshold(unsigned char *orgImg, unsigned char *outImg, int height, int width)
{
	// Histogram set
	int hist[256];
	float prob[256];

	for(int i=0; i<256; i++)
		{hist[i]=0; prob[i] = 0.0f; }
	for(int i=0; i<height*width; i++) 
		hist[(int)orgImg[i]]++;
	for(int i=0; i<256; i++) 
		prob[i] = (float)hist[i]/(float)(height*width);

	float wsv_min = 1000000.0f;
	float wsv_u1, wsv_u2, wsv_s1, wsv_s2;
	int wsv_t;
	for(int t=0; t<256; t++)
		{
			// q1, q2 계산
			float q1 = 0.0f, q2 = 0.0f;
			for(int i=0; i<t; i++) q1 += prob[i];
			for(int i=t; i<256; i++) q2 += prob[i];

			if(q1==0 || q2==0) continue;
			// u1, u2 계산
			float u1=0.0f, u2=0.0f;

			for(int i=0; i<t; i++)
			u1 += i*prob[i];
			u1 /= q1;
			
			for(int i=t; i<256; i++)
			u2 += i*prob[i];
			u2 /= q2;

		// s1, s2 계산
	float s1=0.0f, s2=0.0f;
	
	for(int i=0; i<t; i++) 
		s1 += (i-u1)*(i-u1)*prob[i];
		
	s1 /= q1;

	for(int i=t; i<256; i++)
		s2 += (i-u2)*(i-u2)*prob[i];

	s2 /= q2;
	
	float wsv = q1*s1+q2*s2;
	
	if(wsv < wsv_min) 
	{
		wsv_min = wsv; wsv_t = t;
		wsv_u1 = u1; wsv_u2 = u2;
		wsv_s1 = s1; wsv_s2 = s2;
	}
	}
	
	for(int i=0; i<height*width; i++)
		if(orgImg[i] < wsv_t) outImg[i]=0;
		else outImg[i]=255;
}


void CMy2014111624Doc::AdaptiveBinarization(unsigned char *orgImg, unsigned char *outImg, int height, int width)
{
	int W = 20;
	
	for(int i=0; i<height*width; i++) outImg[i] = 255;
		for(int i=0; i<height; i++)
		{
			int index2 = i*width;
			for(int j=0; j<width; j++)
			{
				float gsum = 0.0f;
				float ssum = 0.0f;
				int count = 0;
			
				for(int k=i-W; k<=i+W; k++)
				{
					int index1 = k*width;
					if(k<0 || k >= height) continue;
					
					for(int l=j-W; l<=j+W; l++)
					{
						if(l<0 || l >= width) continue;
						int gval = orgImg[index1+l];
						gsum += gval;
						ssum += gval*gval;
						count++;
						}
				}
				double mean = gsum/(float)count;
				double vari = ssum/(float)count-mean*mean;

				if(vari<0) 
					vari = 0.0f;
				
				double thres = mean*(1.0f-0.02f*(1-(float)sqrt(vari)/128));

				if(orgImg[index2+j] < thres) 
					outImg[index2+j] = 0;
			}
		}
}


void CMy2014111624Doc::EdgePrewitt(int height, int width)
{
	int MaskPrewittX[3][3]={{-1,0,1}, {-1,0,1}, {-1,0,1}};
	int MaskPrewittY[3][3]={{1,1,1}, {0,0,0}, {-1,-1,-1}};
	int heightm1=height-1, widthm1=width-1; 
	int mr, mc, newValue, i,j;
	int min, max, where;
	float constVal1, constVal2;
	int *pImgPrewittX, *pImgPrewittY;

	pImgPrewittX=new int[height*width]; 
	pImgPrewittY=new int[height*width];

	//결과 이미지 0으로 초기화
	for(i=0;i<height;i++)
		for(j=0;j<width;j++) 
		{
			m_OutImg[i][j]=0;
			where=i*width+j;
			pImgPrewittX[where]= pImgPrewittY[where]= 0;
		}
	for(i=1; i<heightm1; i++) 
		for(j=1; j<widthm1; j++) 
		{
			newValue=0; //0으로 초기화
			for(mr=0;mr<3;mr++)
			for(mc=0;mc<3;mc++)
				newValue += (MaskPrewittX[mr][mc]*m_InImg[i+mr-1][j+mc-1]);
			pImgPrewittX[i*width+j]=newValue;
		}
	for(i=1; i<heightm1; i++) 
		for(j=1; j<widthm1; j++) 
		{
			newValue=0; //0으로 초기화
			for(mr=0;mr<3;mr++)
			for(mc=0;mc<3;mc++)
				newValue += (MaskPrewittX[mr][mc]*m_InImg[i+mr-1][j+mc-1]);
			pImgPrewittX[i*width+j]=newValue;
		}
		for(i=1;i<heightm1;i++) // pImgPrewittX[] = |x| + |y|
			for(j=1;j<widthm1;j++) 
			{
				where=i*width+j;
				constVal1=pImgPrewittX[where];
				constVal2=pImgPrewittY[where];
				if(constVal1<0) constVal1=-constVal1;
				if(constVal2<0) constVal2=-constVal2;
				pImgPrewittX[where]=constVal1+constVal2;
			}
		
			min=(int)10e10; max=(int)-10e10; // 최대, 최소값 구하기

		for(i=1; i<heightm1; i++) 
			for(j=1; j<widthm1; j++) 
			{
				newValue=pImgPrewittX[i*width+j];
				if(newValue<min) min=newValue;
				if(newValue>max) max=newValue;
			}

			constVal1=(float)(255.0/(max-min));
			constVal2=(float)(-255.0*min/(max-min));
		for(i=1; i<heightm1; i++)
			for(j=1; j<widthm1; j++)
			{
				//[min,max]사이의 값을 [0,255]값으로 변환
				newValue=pImgPrewittX[i*width+j];
				newValue=constVal1*newValue+constVal2;
				m_OutImg[i][j]=(BYTE)newValue;
			}
		
		//동적 할당 메모리 해제
		delete [] pImgPrewittX; delete [] pImgPrewittY;
}


void CMy2014111624Doc::EdgeSobel(int height, int width)
{
	int MaskPrewittX[3][3]={{-1,0,1}, {-2,0,2}, {-1,0,1}};
	int MaskPrewittY[3][3]={{-1,-2,-1}, {0,0,0}, {1,2,1}};
	int heightm1=height-1, widthm1=width-1; 
	int mr, mc, newValue, i,j;
	int min, max, where;
	float constVal1, constVal2;
	int *pImgPrewittX, *pImgPrewittY;

	pImgPrewittX=new int[height*width]; 
	pImgPrewittY=new int[height*width];

	//결과 이미지 0으로 초기화
	for(i=0;i<height;i++)
		for(j=0;j<width;j++) 
		{
			m_OutImg[i][j]=0;
			where=i*width+j;
			pImgPrewittX[where]= pImgPrewittY[where]= 0;
		}
	for(i=1; i<heightm1; i++) 
		for(j=1; j<widthm1; j++) 
		{
			newValue=0; //0으로 초기화
			for(mr=0;mr<3;mr++)
			for(mc=0;mc<3;mc++)
				newValue += (MaskPrewittX[mr][mc]*m_InImg[i+mr-1][j+mc-1]);
			pImgPrewittX[i*width+j]=newValue;
		}
	for(i=1; i<heightm1; i++) 
		for(j=1; j<widthm1; j++) 
		{
			newValue=0; //0으로 초기화
			for(mr=0;mr<3;mr++)
			for(mc=0;mc<3;mc++)
				newValue += (MaskPrewittX[mr][mc]*m_InImg[i+mr-1][j+mc-1]);
			pImgPrewittX[i*width+j]=newValue;
		}
		for(i=1;i<heightm1;i++) // pImgPrewittX[] = |x| + |y|
			for(j=1;j<widthm1;j++) 
			{
				where=i*width+j;
				constVal1=pImgPrewittX[where];
				constVal2=pImgPrewittY[where];
				if(constVal1<0) constVal1=-constVal1;
				if(constVal2<0) constVal2=-constVal2;
				pImgPrewittX[where]=constVal1+constVal2;
			}
		
			min=(int)10e10; max=(int)-10e10; // 최대, 최소값 구하기

		for(i=1; i<heightm1; i++) 
			for(j=1; j<widthm1; j++) 
			{
				newValue=pImgPrewittX[i*width+j];
				if(newValue<min) min=newValue;
				if(newValue>max) max=newValue;
			}

			constVal1=(float)(255.0/(max-min));
			constVal2=(float)(-255.0*min/(max-min));
		for(i=1; i<heightm1; i++)
			for(j=1; j<widthm1; j++)
			{
				//[min,max]사이의 값을 [0,255]값으로 변환
				newValue=pImgPrewittX[i*width+j];
				newValue=constVal1*newValue+constVal2;
				m_OutImg[i][j]=(BYTE)newValue;
			}
		
		//동적 할당 메모리 해제
		delete [] pImgPrewittX; delete [] pImgPrewittY;
}


void CMy2014111624Doc::SharpeningLaplacian(int height, int width)
{
	int MaskBox[3][3] = {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
	int *pTmpImg = new int[height*width];
	int heightm1=height-1, widthm1=width-1; 
	int mr, mc, newValue, i,j;
	int min, max;
	float constVal1, constVal2;

	for(i=0; i<height; i++)
		for(j=0; j<width; j++)
			m_OutImg[i][j] =  pTmpImg[i*width+j] = 0;

	for(i=1;i<heightm1; i++)
		for(j=1; j<widthm1; j++)
		{
			newValue = 0;
			for(mr = 0; mr<3; mr++)
				for(mc = 0; mc<3; mc++)
					newValue += (MaskBox[mr][mc]*m_InImg[i+mr-1][j+mc-1]);
			if(newValue < 0) newValue = -newValue;
			pTmpImg[i*width+j] = newValue;
		}
		
		min = (int)10e10;
		max = (int)-10e10;

		for(i = 1; i<heightm1; i++)
			for(j=1; j<widthm1; j++)
			{ 
				newValue = pTmpImg[i*width+j];
				if(newValue<min) min = newValue;
				if(newValue>max) max = newValue;
			}

		constVal1 = (float)(255.0/(max-min));
		constVal2 = (float)(-255.0*min/(max-min));

		for(i=1; i<heightm1; i++)
			for(j=1; j<widthm1; j++)
			{
				newValue=pTmpImg[i*width+j];
				newValue=constVal1*newValue+constVal2;
				m_OutImg[i][j]=(BYTE)newValue;
			}
			
		delete [] pTmpImg;
}
