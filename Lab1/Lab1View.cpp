
// Lab1View.cpp : implementation of the CLab1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab1.h"
#endif

#include "Lab1Doc.h"
#include "Lab1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab1View

IMPLEMENT_DYNCREATE(CLab1View, CView)

BEGIN_MESSAGE_MAP(CLab1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLab1View construction/destruction

CLab1View::CLab1View()
{
	// TODO: add construction code here

}

CLab1View::~CLab1View()
{
}

BOOL CLab1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab1View drawing

void CLab1View::OnDraw(CDC* pDC)
{
	CLab1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	;
	GetClientRect(&clientRect);
	pDC->SetMapMode(MM_ISOTROPIC);

	pDC->SetWindowExt(clientRect.right, clientRect.bottom);
	pDC->SetViewportExt(clientRect.right, clientRect.bottom);

	pDC->SetWindowOrg(0, 0);
	DrawCockpitWall(pDC);
	DrawSideWindow(pDC, false);
	DrawSideWindow(pDC, true);
	DrawCenterWindow(pDC);
	DrawDashboard(pDC);
	DrawScreen(pDC, false);
	DrawScreen(pDC, true);
}

CRect CLab1View::Inside(int x1, int y1, int x2, int y2, double xOffset, double yOffset){
	CRect rect;
	int outerWidth = x2 - x1;
	int outerHeight = y2 - y1;

	int dim = outerWidth > outerHeight ? outerHeight : outerWidth;

	int offsetX = (double) (outerWidth - dim) * xOffset;
	int offsetY = (double) (outerHeight - dim) * yOffset;

	rect.left = x1 + offsetX;
	rect.top = y1 + offsetY;
	rect.right = rect.left + dim;
	rect.bottom = rect.top + dim;

	return rect;
}

void CLab1View::DrawCockpitWall(CDC* pDC) {
	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 128, 128));
	CBrush* oldBrush = (CBrush*) pDC->SelectObject(&brush);
	
	pDC->Rectangle(0, 0, clientRect.right, clientRect.bottom);
	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::DrawSideWindow(CDC* pDC, bool m) {
	CPen newPen(PS_SOLID, VariablePenWidth(5), RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&newPen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 224, 255));
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);

	POINT points[3];

	pDC->BeginPath();

	pDC->MoveTo(MirrorX(0, m), clientRect.bottom * 0.085);
	points[0].x = MirrorX(clientRect.right * 0.05, m); points[0].y = clientRect.bottom * 0.088;
	points[1].x = MirrorX(clientRect.right * 0.08, m); points[1].y = clientRect.bottom * 0.11;
	points[2].x = MirrorX(clientRect.right * 0.096, m); points[2].y = clientRect.bottom * 0.16;
	pDC->PolylineTo(points, 3);

	pDC->LineTo(MirrorX(clientRect.right * 0.17, m), clientRect.bottom * 0.58);

	points[0].x = MirrorX(clientRect.right * 0.177, m); points[0].y = clientRect.bottom * 0.624;
	points[1].x = MirrorX(clientRect.right * 0.167, m); points[1].y = clientRect.bottom * 0.681;
	points[2].x = MirrorX(clientRect.right * 0.14, m); points[2].y = clientRect.bottom * 0.71;
	pDC->PolylineTo(points, 3);

	pDC->LineTo(MirrorX(0, m), clientRect.bottom * 0.83);

	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::DrawCenterWindow(CDC* pDC){
	CPen newPen(PS_SOLID, VariablePenWidth(5), RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&newPen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 224, 255));
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);

	POINT points[3];

	pDC->BeginPath();

	pDC->MoveTo(clientRect.right * 0.5, clientRect.bottom * 0.112);

	points[0].x = clientRect.right * 0.374; points[0].y = clientRect.bottom * 0.112;
	points[1].x = clientRect.right * 0.244; points[1].y = clientRect.bottom * 0.107;
	points[2].x = clientRect.right * 0.175; points[2].y = clientRect.bottom * 0.102;
	pDC->PolyBezierTo(points, 3);

	points[0].x = clientRect.right * 0.136; points[0].y = clientRect.bottom * 0.102;
	points[1].x = clientRect.right * 0.125; points[1].y = clientRect.bottom * 0.134;
	points[2].x = clientRect.right * 0.131; points[2].y = clientRect.bottom * 0.178;
	pDC->PolyBezierTo(points, 3);

	pDC->LineTo(clientRect.right * 0.199, clientRect.bottom * 0.574);

	points[0].x = clientRect.right * 0.210; points[0].y = clientRect.bottom * 0.628;
	points[1].x = clientRect.right * 0.239; points[1].y = clientRect.bottom * 0.663;
	points[2].x = clientRect.right * 0.270; points[2].y = clientRect.bottom * 0.645;
	pDC->PolyBezierTo(points, 3);

	points[0].x = clientRect.right * 0.282; points[0].y = clientRect.bottom * 0.639;
	points[1].x = clientRect.right * 0.402; points[1].y = clientRect.bottom * 0.558;
	points[2].x = clientRect.right * 0.5; points[2].y = clientRect.bottom * 0.558;
	pDC->PolyBezierTo(points, 3);

	points[0].x = clientRect.right * 0.597; points[0].y = clientRect.bottom * 0.558;
	points[1].x = clientRect.right * 0.657; points[1].y = clientRect.bottom * 0.598;
	points[2].x = clientRect.right * 0.718; points[2].y = clientRect.bottom * 0.639;
	pDC->PolyBezierTo(points, 3);

	points[0].x = clientRect.right * 0.761; points[0].y = clientRect.bottom * 0.663;
	points[1].x = clientRect.right * 0.790; points[1].y = clientRect.bottom * 0.628;
	points[2].x = clientRect.right * 0.801; points[2].y = clientRect.bottom * 0.574;
	pDC->PolyBezierTo(points, 3);

	pDC->LineTo(clientRect.right * 0.869, clientRect.bottom * 0.178);

	points[0].x = clientRect.right * 0.875; points[0].y = clientRect.bottom * 0.134;
	points[1].x = clientRect.right * 0.863; points[1].y = clientRect.bottom * 0.104;
	points[2].x = clientRect.right * 0.825; points[2].y = clientRect.bottom * 0.102;
	pDC->PolyBezierTo(points, 3);

	points[0].x = clientRect.right * 0.756; points[0].y = clientRect.bottom * 0.107;
	points[1].x = clientRect.right * 0.625; points[1].y = clientRect.bottom * 0.112;
	points[2].x = clientRect.right * 0.5; points[2].y = clientRect.bottom * 0.112;

	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::DrawDashboard(CDC* pDC){
	CPen newPen(PS_SOLID, VariablePenWidth(3), RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&newPen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(64, 64, 64));
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);

	POINT points[3];

	pDC->BeginPath();

	pDC->MoveTo(clientRect.right * 0.201, clientRect.bottom);

	pDC->LineTo(clientRect.right * 0.201, clientRect.bottom * 0.769);

	points[0].x = clientRect.right * 0.201; points[0].y = clientRect.bottom * 0.735;
	points[1].x = clientRect.right * 0.210; points[1].y = clientRect.bottom * 0.713;
	points[2].x = clientRect.right * 0.221; points[2].y = clientRect.bottom * 0.708;
	pDC->PolyBezierTo(points, 3);

	pDC->LineTo(clientRect.right * 0.414, clientRect.bottom * 0.628);

	points[0].x = clientRect.right * 0.439; points[0].y = clientRect.bottom * 0.620;
	points[1].x = clientRect.right * 0.484; points[1].y = clientRect.bottom * 0.610;
	points[2].x = clientRect.right * 0.500; points[2].y = clientRect.bottom * 0.610;
	pDC->PolyBezierTo(points, 3);

	points[0].x = clientRect.right * 0.516; points[0].y = clientRect.bottom * 0.610;
	points[1].x = clientRect.right * 0.560; points[1].y = clientRect.bottom * 0.620;
	points[2].x = clientRect.right * 0.585; points[2].y = clientRect.bottom * 0.628;
	pDC->PolyBezierTo(points, 3);

	pDC->LineTo(clientRect.right * 0.779, clientRect.bottom * 0.708);

	points[0].x = clientRect.right * 0.789; points[0].y = clientRect.bottom * 0.713;
	points[1].x = clientRect.right * 0.798; points[1].y = clientRect.bottom * 0.735;
	points[2].x = clientRect.right * 0.799; points[2].y = clientRect.bottom * 0.769;
	pDC->PolyBezierTo(points, 3);

	pDC->LineTo(clientRect.right * 0.799, clientRect.bottom);


	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::DrawScreen(CDC* pDC, bool right){
	CPen newPen(PS_SOLID, VariablePenWidth(2), RGB(192, 192, 192));
	CPen* oldPen = pDC->SelectObject(&newPen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(32, 32, 32));
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);

	int outerWidth = clientRect.right * 0.25;
	int outerHeight = clientRect.bottom * 0.25;

	int x = clientRect.right * 0.24;
	x = right ? MirrorX(x, true) - outerWidth : x;
	int y = clientRect.bottom * 0.73;

	CRect square = Inside(x, y, x + outerWidth, y + outerHeight, right ? 0 : 1, 1);

	pDC->RoundRect(
		square.left,
		square.top,
		square.right,
		square.bottom,
		square.Width() * 0.1,
		square.Height() * 0.1
	);
	
	if (!right) {
		RECT textRect = { square.left, square.top, square.right, square.bottom };
		DrawScreenText(pDC, textRect);
	}

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::DrawScreenText(CDC* pDC, RECT rect){
	int height = (rect.bottom - rect.top);
	int width = rect.right - rect.left;

	int nHeight = height * 0.11;
	int nWidth = 0;
	int nEsc = 0;
	int nOrient = 0;
	int nWeight = 0;
	BYTE bItalic = 0;
	BYTE bUnderline = 0;
	BYTE cStrikeOut = 0;
	BYTE nCharSet = 0;
	BYTE nOutPrecision = 0;
	BYTE nClipPrecision = 0;
	BYTE nQuality = 0;
	BYTE nPitchAndFamily = 0;
	CString	sFaceName("Arial");
	CFont font;
		
	font.CreateFont(nHeight, nWidth, nEsc, nOrient, nWeight, bItalic, bUnderline, cStrikeOut, nCharSet, nOutPrecision, nClipPrecision, nQuality, nPitchAndFamily, sFaceName);
	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0, 255, 0));
	pDC->SetBkMode(TRANSPARENT);

	int offsetTop = height * 0.15;
	int lineHeight = height * 0.2;

	// Left column
	CString text("350mph");
	pDC->TextOut(rect.left + width * 0.05, rect.top + offsetTop, text);

	text = CString("H: 23°");
	pDC->TextOut(rect.left + width * 0.05, rect.top + offsetTop + lineHeight * 1, text);

	text = CString("A: 284°");
	pDC->TextOut(rect.left + width * 0.05, rect.top + offsetTop + lineHeight * 2, text);

	text = CString("1217fmp");
	pDC->TextOut(rect.left + width * 0.05, rect.top + offsetTop + lineHeight * 3, text);

	// Right column
	pDC->SetTextAlign(TA_RIGHT);

	text = CString("1285m");
	pDC->TextOut(rect.left + width * 0.95, rect.top + offsetTop, text);

	text = CString("43°19'29\"");
	pDC->TextOut(rect.left + width * 0.95, rect.top + offsetTop + lineHeight * 1, text);

	text = CString("21°54'11\"");
	pDC->TextOut(rect.left + width * 0.95, rect.top + offsetTop + lineHeight * 2, text);

	text = CString("08:54:29");
	pDC->TextOut(rect.left + width * 0.95, rect.top + offsetTop + lineHeight * 3, text);

	pDC->SelectObject(pOldFont);
	font.DeleteObject();
}

void CLab1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLab1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLab1View diagnostics

#ifdef _DEBUG
void CLab1View::AssertValid() const
{
	CView::AssertValid();
}

void CLab1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab1Doc* CLab1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab1Doc)));
	return (CLab1Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab1View message handlers
