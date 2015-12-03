
// Col2012View.h : interface of the CCol2012View class
//

#pragma once
#define PI (3.14159265359)

class CCol2012View : public CView
{
protected: // create from serialization only
	CCol2012View();
	DECLARE_DYNCREATE(CCol2012View)

// Attributes
public:
	CCol2012Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCol2012View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect clientRect;
	CBitmap bufferBmp;
	CDC bufferDC;
	float rotation = 0;

	void Trapezoid(CDC*, int, int, int, int, int);
	void Translate(CDC*, float, float);
	void Rotate(CDC*, float);
	void ResetTransform(CDC*);
	void DrawGear(CDC*, int, int);
	void DrawScene(CDC*);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Col2012View.cpp
inline CCol2012Doc* CCol2012View::GetDocument() const
   { return reinterpret_cast<CCol2012Doc*>(m_pDocument); }
#endif

