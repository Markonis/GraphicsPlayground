
// Lab1View.h : interface of the CLab1View class
//

#pragma once
#define LW (1000)
#define LH (1000)

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

	void DrawCockpitWall(CDC*);
	void DrawSideWindow(CDC*, bool);
	void DrawCenterWindow(CDC*);
	void DrawScreen(CDC*, bool);
	void DrawDashboard(CDC*);
	void DrawScreenText(CDC*, RECT);
	CRect Inside(int, int, int, int, double, double);


	int MirrorX(int x, bool m) { return m ? clientRect.right - x : x; }
	int MirrorY(int y, bool m) { return m ? clientRect.bottom - y : y; }
	int VariablePenWidth(int w) {
		int newW = w * clientRect.right / 640 * clientRect.bottom / 480;
		newW = newW > 2 ? newW : 2;
		return newW; 
	}

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Lab1View.cpp
inline CLab1Doc* CLab1View::GetDocument() const
   { return reinterpret_cast<CLab1Doc*>(m_pDocument); }
#endif

