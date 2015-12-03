
// Lab1View.h : interface of the CLab1View class
//

#pragma once
#include "DImage.h"
#define PI (3.14159265359)

class CLab1View : public CView
{
protected: // create from serialization only
	CLab1View();
	DECLARE_DYNCREATE(CLab1View)

// Attributes
public:
	CLab1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CLab1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect clientRect;
	CFont* currentFont;
	double tilt = 0.25 * PI;
	bool initialized = false;
	CDC bufferDC;
	CBitmap bufferBmp;
	float brightness = 0;
	float contrast = 0;
	

	// Lab 1
	void DrawCockpitWall(CDC*);
	void DrawSideWindow(CDC*, bool);
	void CreateSideWindowPath(CDC*, bool);
	void DrawCenterWindow(CDC*);
	void CreateCenterWindowPath(CDC*);
	void DrawWindows(CDC*);
	void DrawScreen(CDC*, bool);
	void DrawDashboard(CDC*);
	void DrawScreenText(CDC*, RECT);
	void AdjustBitmap(CBitmap*, float, float);

	//Lab2
	void DrawWatch(
		CDC* pDC, int cX, int cY, int radius, int nNotch, CString arsValues[], int nValues,
		double dAngleStart, double dAngleStop, int typeNeedle, double dAngleNeedle);
	void DrawWatchTilt(CDC* pDC, int cX, int cY, int radius, double dAngleTilt);
	void DrawFuelWatch(CDC* pDC, CRect rcView, CRect rcWatch, int nNotch, double dAngleStart, double dAngleStop, double ardProportion[],
		int nParts, COLORREF arClrProportion[], double dAngleNeedle);
	void DrawWatches(CDC*);

	// Lab 3
	void DrawMap(CDC* pDC, CRect rcMap, CString strImage);
	void DrawSky(CDC*, double);
	void DrawPlane(CDC*);

	// Helpers
	int MirrorX(int x, bool m) { return m ? clientRect.right - x : x; }
	int MirrorY(int y, bool m) { return m ? clientRect.bottom - y : y; }
	int VariablePenWidth(float w) {
		int newW = w * clientRect.right / 640 * clientRect.bottom / 480;
		newW = newW > 2 ? newW : 2;
		return newW; 
	}
	CRect Inside(int, int, int, int, double, double);

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Lab1View.cpp
inline CLab1Doc* CLab1View::GetDocument() const
   { return reinterpret_cast<CLab1Doc*>(m_pDocument); }
#endif

