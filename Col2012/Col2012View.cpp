
// Col2012View.cpp : implementation of the CCol2012View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Col2012.h"
#endif

#include "Col2012Doc.h"
#include "Col2012View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCol2012View

IMPLEMENT_DYNCREATE(CCol2012View, CView)

BEGIN_MESSAGE_MAP(CCol2012View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CCol2012View construction/destruction

CCol2012View::CCol2012View()
{
	// TODO: add construction code here

}

CCol2012View::~CCol2012View()
{
}

BOOL CCol2012View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCol2012View drawing

void CCol2012View::OnDraw(CDC* pDC)
{
	CCol2012Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	GetClientRect(&clientRect);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(clientRect.right, clientRect.bottom);
	pDC->SetViewportExt(clientRect.right, clientRect.bottom);

	bufferDC.DeleteDC();
	bufferDC.CreateCompatibleDC(pDC);

	bufferBmp.DeleteObject();
	bufferBmp.CreateCompatibleBitmap(pDC, clientRect.right, clientRect.bottom);
	bufferDC.SelectObject(&bufferBmp);

	// Drawing
	DrawScene(&bufferDC);
	
	ResetTransform(&bufferDC);
	pDC->BitBlt(0, 0, clientRect.right, clientRect.bottom, &bufferDC, 0, 0, SRCCOPY);
}

void CCol2012View::Trapezoid(CDC* pDC, int a, int b, int h, int x, int y){
	POINT points[4];
	points[0] = { -a / 2 + x, -h / 2 + y};
	points[1] = { a / 2 + x, -h / 2 + y};
	points[2] = { b / 2 + x, h / 2 + y};
	points[3] = { -b / 2 + x, h / 2 + y};
	pDC->Polygon(points, 4);
}

void CCol2012View::Translate(CDC* pDC, float x, float y){
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM Xform, XformOld;
	GetWorldTransform(pDC->m_hDC, &XformOld);

	Xform.eM11 = (FLOAT) 1.0;
	Xform.eM12 = (FLOAT) 0.0;
	Xform.eM21 = (FLOAT) 0.0;
	Xform.eM22 = (FLOAT) 1.0;
	Xform.eDx = (FLOAT) x;
	Xform.eDy = (FLOAT) y;

	ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_RIGHTMULTIPLY);
	SetGraphicsMode(pDC->m_hDC, prevMode);
}

void CCol2012View::Rotate(CDC* pDC, float a){
	a *= PI;
	a /= 180;

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);

	XFORM Xform, XformOld;

	// Translate back to origin
	GetWorldTransform(pDC->m_hDC, &XformOld);
	int oldX = XformOld.eDx, oldY = XformOld.eDy;
	XformOld.eDx = 0; XformOld.eDy = 0;
	SetWorldTransform(pDC->m_hDC, &XformOld);

	// Rotate around the origin
	Xform.eM11 = (FLOAT) cos(a);
	Xform.eM12 = (FLOAT)sin(a);
	Xform.eM21 = (FLOAT)-sin(a);
	Xform.eM22 = (FLOAT)cos(a);
	Xform.eDx = (FLOAT)0;
	Xform.eDy = (FLOAT)0;
	ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_RIGHTMULTIPLY);

	SetGraphicsMode(pDC->m_hDC, prevMode);

	// Translate to where it was
	Translate(pDC, oldX, oldY);
}

void CCol2012View::ResetTransform(CDC* pDC){
	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM Xform, XformOld;
	GetWorldTransform(pDC->m_hDC, &XformOld);

	Xform.eM11 = (FLOAT)1;
	Xform.eM12 = (FLOAT)0;
	Xform.eM21 = (FLOAT)0;
	Xform.eM22 = (FLOAT)1;
	Xform.eDx = (FLOAT)0;
	Xform.eDy = (FLOAT)0;

	SetWorldTransform(pDC->m_hDC, &Xform);
	SetGraphicsMode(pDC->m_hDC, prevMode);
}

void CCol2012View::DrawGear(CDC* pDC, int spokeCount, int spokeWidth){
	int eRadius = spokeCount * spokeWidth / (2 * PI) * 2;
	int radius = eRadius - spokeWidth / 2;
	float angleStep = 360 / spokeCount;

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM Xform, XformOld;
	GetWorldTransform(pDC->m_hDC, &XformOld);

	for (int i = 0; i < spokeCount; i++){
		Rotate(pDC, angleStep * i);
		Trapezoid(pDC, 1.4 * spokeWidth, spokeWidth / 1.4, spokeWidth, 0, eRadius);
		SetWorldTransform(pDC->m_hDC, &XformOld);
	}

	SetGraphicsMode(pDC->m_hDC, prevMode);
	
	pDC->Ellipse(-radius, -radius, radius, radius);
}

void CCol2012View::DrawScene(CDC* pDC){
	Rotate(pDC, rotation);
	Translate(&bufferDC, 300, 300);
	DrawGear(&bufferDC, 20, 20);
	ResetTransform(&bufferDC);

	Rotate(pDC, - rotation * 2);
	Translate(&bufferDC, 494, 300);
	DrawGear(&bufferDC, 10, 20);
	ResetTransform(&bufferDC);

	Rotate(pDC, - rotation * 2 - 8);
	Translate(&bufferDC, 164, 164);
	DrawGear(&bufferDC, 10, 20);
}

// CCol2012View printing

BOOL CCol2012View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCol2012View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCol2012View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCol2012View diagnostics

#ifdef _DEBUG
void CCol2012View::AssertValid() const
{
	CView::AssertValid();
}

void CCol2012View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCol2012Doc* CCol2012View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCol2012Doc)));
	return (CCol2012Doc*)m_pDocument;
}
#endif //_DEBUG


// CCol2012View message handlers


void CCol2012View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 38){
		rotation += 5;
		Invalidate();
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
