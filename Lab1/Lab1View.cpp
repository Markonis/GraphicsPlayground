
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
	ON_WM_KEYDOWN()
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


	// Setup coordinate system
	GetClientRect(&clientRect);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(clientRect.right, clientRect.bottom);
	pDC->SetViewportExt(clientRect.right, clientRect.bottom);
	pDC->SetWindowOrg(0, 0);

	bufferDC.DeleteDC();
	bufferDC.CreateCompatibleDC(pDC);

	// Create buffer
	bufferBmp.DeleteObject();
	bufferBmp.CreateCompatibleBitmap(pDC, clientRect.right, clientRect.bottom);
	bufferDC.SelectObject(&bufferBmp);

	// Lab 1
	DrawCockpitWall(&bufferDC);
	DrawWindows(&bufferDC);
	DrawDashboard(&bufferDC);
	DrawScreen(&bufferDC, false);
	DrawScreen(&bufferDC, true);

	// Lab 2
	DrawWatches(&bufferDC);

	// Lab 3
	DrawSky(&bufferDC, tilt);

	AdjustBitmap(&bufferBmp, brightness, contrast);
	pDC->BitBlt(0, 0, clientRect.right, clientRect.bottom, &bufferDC, 0, 0, SRCCOPY);
}

// Lab 1
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

	CreateSideWindowPath(pDC, m);
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::CreateSideWindowPath(CDC* pDC, bool m) {
	POINT points[3];

	pDC->BeginPath();

	pDC->MoveTo(MirrorX(0, m), clientRect.bottom * 0.085);
	points[0].x = MirrorX(clientRect.right * 0.05, m); points[0].y = clientRect.bottom * 0.088;
	points[1].x = MirrorX(clientRect.right * 0.08, m); points[1].y = clientRect.bottom * 0.11;
	points[2].x = MirrorX(clientRect.right * 0.096, m); points[2].y = clientRect.bottom * 0.16;
	pDC->PolyBezierTo(points, 3);

	pDC->LineTo(MirrorX(clientRect.right * 0.17, m), clientRect.bottom * 0.58);

	points[0].x = MirrorX(clientRect.right * 0.177, m); points[0].y = clientRect.bottom * 0.624;
	points[1].x = MirrorX(clientRect.right * 0.167, m); points[1].y = clientRect.bottom * 0.681;
	points[2].x = MirrorX(clientRect.right * 0.14, m); points[2].y = clientRect.bottom * 0.71;
	pDC->PolyBezierTo(points, 3);

	pDC->LineTo(MirrorX(0, m), clientRect.bottom * 0.83);

	pDC->EndPath();
}

void CLab1View::DrawCenterWindow(CDC* pDC){
	CRgn reg;
	CPen newPen(PS_SOLID, VariablePenWidth(5), RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&newPen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 224, 255));
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);

	CreateCenterWindowPath(pDC);
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::CreateCenterWindowPath(CDC* pDC){
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
}

void CLab1View::DrawWindows(CDC* pDC){
	DrawSideWindow(pDC, false);
	DrawSideWindow(pDC, true);
	DrawCenterWindow(pDC);
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
CPen newPen(PS_SOLID, VariablePenWidth(1), RGB(192, 192, 192));
CPen* oldPen = pDC->SelectObject(&newPen);

CBrush brush;
brush.CreateSolidBrush(RGB(0, 0, 0));
CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);

int outerWidth = clientRect.right * 0.18;
int outerHeight = clientRect.bottom * 0.18;

int x = clientRect.right * 0.315;
x = right ? MirrorX(x, true) - outerWidth : x;
int y = clientRect.bottom * 0.81;

CRect square = Inside(x, y, x + outerWidth, y + outerHeight, right ? 0 : 1, 1);

pDC->RoundRect(
	square.left,
	square.top,
	square.right,
	square.bottom,
	square.Width() * 0.1,
	square.Height() * 0.1
	);

if (right) {
	
	DrawMap(pDC, square, CString("Map.png"));
}else {
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

// Lab 2
void CLab1View::DrawWatch(
	CDC* pDC, int cX, int cY, int radius, int nNotch, CString arsValues[], int nValues,
	double dAngleStart, double dAngleStop, int typeNeedle, double dAngleNeedle){

	CPen thickPen(PS_SOLID, 2, RGB(192, 192, 192));
	CPen thinPen(PS_SOLID, 1, RGB(192, 192, 192));
	CPen* oldPen = pDC->SelectObject(&thickPen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(32, 32, 32));
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(&brush);

	CRect rect;
	rect.left = cX - radius;
	rect.right = cX + radius;
	rect.top = cY - radius;
	rect.bottom = cY + radius;
	pDC->Ellipse(rect.left, rect.top, rect.right, rect.bottom);

	// Draw notches
	double dNotchAngle = (dAngleStop - dAngleStart) / (double) nNotch;

	for (int i = 0; i < nNotch; i += 2){
		pDC->MoveTo(cX + cos(dAngleStart + dNotchAngle * i) * radius, cY - sin(dAngleStart + dNotchAngle * i) * radius);
		pDC->LineTo(cX + cos(dAngleStart + dNotchAngle * i) * radius * 0.8, cY - sin(dAngleStart + dNotchAngle * i) * radius * 0.8);
	}

	pDC->SelectObject(&thinPen);
	for (int i = 1; i < nNotch; i += 2){
		pDC->MoveTo(cX + cos(dAngleStart + dNotchAngle * i) * radius, cY - sin(dAngleStart + dNotchAngle * i) * radius);
		pDC->LineTo(cX + cos(dAngleStart + dNotchAngle * i) * radius * 0.85, cY - sin(dAngleStart + dNotchAngle * i) * radius * 0.85);
	}


	// Draw values
	double dValueAngle = (dAngleStop - dAngleStart) / (double)nValues;

	int nHeight = (rect.bottom - rect.top) * 0.1;
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
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_CENTER);

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM Xform, XformOld;
	GetWorldTransform(pDC->m_hDC, &XformOld);

	pDC->SetViewportOrg(cX,cY);
	for (int i = 0; i < nValues; i++){
		double textAngle = dAngleStart + i * dValueAngle;
		Xform.eM11 = (FLOAT)sin(textAngle);
		Xform.eM12 = (FLOAT)cos(textAngle);
		Xform.eM21 = (FLOAT)-cos(textAngle);
		Xform.eM22 = (FLOAT)sin(textAngle);
		Xform.eDx = (FLOAT) 0.0;
		Xform.eDy = (FLOAT) 0.0;
		SetWorldTransform(pDC->m_hDC, &Xform);

		pDC->TextOut(0, -radius * 0.75, arsValues[i]);
	}
	pDC->SetViewportOrg(0, 0);


	pDC->SelectObject(pOldFont);
	font.DeleteObject();

	SetWorldTransform(pDC->m_hDC, &XformOld);
	SetGraphicsMode(pDC->m_hDC, prevMode);


	pDC->SelectObject(oldPen);
	thickPen.DeleteObject();
	thinPen.DeleteObject();

	pDC->SelectObject(oldBrush);
	oldBrush->DeleteObject();
}

void CLab1View::DrawWatchTilt(CDC* pDC, int cX, int cY, int radius, double dAngleTilt) {

	CRect rcWatch(cX - radius, cY - radius, cX + radius, cY + radius);
	CPen newPen(PS_SOLID, 2, RGB(210, 210, 210));
	CPen newPenThin(PS_SOLID, 1, RGB(210, 210, 210));
	CPen* penP = pDC->SelectObject(&newPen);
	CBrush newBrushBlue(RGB(48, 176, 224));
	CBrush newBrushSand(RGB(208, 176, 128));
	CBrush* brushP = pDC->SelectObject(&newBrushSand);

	pDC->Ellipse(rcWatch);

	CPoint oldOrg = pDC->SetViewportOrg(rcWatch.CenterPoint());

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);

	XFORM Xform, XformOld;

	bool b = GetWorldTransform(pDC->m_hDC, &XformOld);

	double angle = dAngleTilt;

	Xform.eM11 = cos(angle);
	Xform.eM12 = sin(angle);
	Xform.eM21 = -sin(angle);
	Xform.eM22 = cos(angle);
	Xform.eDx = 0.0;
	Xform.eDy = 0.0;

	b = SetWorldTransform(pDC->m_hDC, &Xform);

	// drawing

	pDC->MoveTo((rcWatch.right - rcWatch.left) / 2, 0);
	pDC->LineTo((rcWatch.left - rcWatch.right) / 2, 0);

	// sand

	int r = (rcWatch.right - rcWatch.left) * 0.75 * 0.5;

	for (int i = 0; i < 5; i++)
	{
		double ang = 3.14 * (i + 1) / 6;
		int y = sin(ang) * r;
		int x = -cos(ang) * r;
		pDC->MoveTo(0, 0);
		pDC->LineTo(x, y);
	}

	// sky

	r = (rcWatch.right - rcWatch.left) * 0.5;

	int r1 = r * 0.8;

	for (int i = 0; i < 5; i++)
	{
		double ang = 3.14 * (i + 1) / 6;
		int y1 = -sin(ang) * r;
		int x1 = -cos(ang) * r;
		int y2 = -sin(ang) * r1;
		int x2 = -cos(ang) * r1;
		pDC->MoveTo(x1, y1);
		pDC->LineTo(x2, y2);
	}

	pDC->SelectObject(newPenThin);

	double ang = 3.14 / 3;
	r1 *= 1.09;

	for (int i = 0; i < 6; i++)
	{
		int y1 = -sin(ang) * r;
		int x1 = -cos(ang) * r;
		int y2 = -sin(ang) * r1;
		int x2 = -cos(ang) * r1;
		pDC->MoveTo(x1, y1);
		pDC->LineTo(x2, y2);
		ang += 3.14 / 18;
	}

	pDC->SelectObject(newBrushBlue);
	pDC->FloodFill(r*0.9, -rcWatch.Height() * 0.1, RGB(210, 210, 210));

	b = SetWorldTransform(pDC->m_hDC, &XformOld);
	SetGraphicsMode(pDC->m_hDC, prevMode);

	pDC->SetViewportOrg(oldOrg);

	pDC->SelectObject(penP);
	pDC->SelectObject(brushP);
	newPen.DeleteObject();
	newPenThin.DeleteObject();
	newBrushBlue.DeleteObject();
	newBrushSand.DeleteObject();
}

void CLab1View::DrawFuelWatch(CDC* pDC, CRect rcView, CRect rcWatch, int nNotch, double dAngleStart, double dAngleStop, double ardProportion[],
	int nParts, COLORREF arClrProportion[], double dAngleNeedle){
	CPen newPen(PS_SOLID | PS_JOIN_ROUND, 3, RGB(210, 210, 210));
	CPen* penP = pDC->SelectObject(&newPen);

	CBrush newBrush(RGB(32, 32, 32));
	CBrush* brushP = pDC->SelectObject(&newBrush);

	CPoint oldOrg = pDC->SetViewportOrg(rcWatch.left + (rcWatch.right - rcWatch.left) / 2, rcWatch.bottom);

	CPoint B((rcWatch.left - rcWatch.right) / 2 * (-1), (rcWatch.top - rcWatch.bottom) / 2);
	CPoint C((rcWatch.left - rcWatch.right) / 2, (rcWatch.top - rcWatch.bottom) / 2);

	CRect bigRect(CPoint(((rcWatch.left - rcWatch.right) / 2), rcWatch.top - rcWatch.bottom), CPoint((rcWatch.left - rcWatch.right) / 2 * (-1), 0));

	double ang1 = 3.14 / (180 / dAngleStart);
	double ctan1 = 1 / tan(ang1);
	double dAdd = C.y * ctan1;
	double ang2 = 3.14 / (180 / dAngleStop);
	double ctan2 = 1 / tan(ang2);
	double aSub = B.y * ctan2;
	CPoint A(bigRect.right + aSub, 0);
	CPoint D(bigRect.right*(-1) - dAdd, 0);

	CPoint **stopPoints;
	stopPoints = new CPoint*[nParts + 1];
	CPen **pens;
	pens = new CPen*[nParts];
	int c = 0;
	for (int i = 0; i < nNotch; i++)
		c += ardProportion[i];
	double step = A.x * 2 / c;

	stopPoints[0] = new CPoint(A.x, 0.5 * bigRect.top);

	for (int i = 1; i < nParts; i++){
		double x = stopPoints[i - 1]->x - step * ardProportion[i - 1];
		double y = (-1) * abs((long)((bigRect.top*0.6 / A.x)*sqrt((A.x - x)*(A.x + x)))) - 23;
		stopPoints[i] = new CPoint(x, y == 0 ? 0.5*bigRect.top : y);
	}

	stopPoints[nParts] = new CPoint(D.x, bigRect.top * 0.5);

	for (int i = 0; i < nParts; i++)
		pens[i] = new CPen(PS_SOLID | PS_GEOMETRIC, rcView.Height() * 0.01, arClrProportion[i]);

	pDC->Arc(bigRect, B, C);

	double k = (double)(A.x - D.x) / (double)(B.x - C.x);

	CPoint TLS(D.x, C.y * k);
	CPoint BRS(A.x, C.y * k * (-1));

	CRect littleRect(TLS, BRS);
	pDC->Arc(littleRect, A, D);

	pDC->MoveTo(A);
	pDC->LineTo(B);
	pDC->MoveTo(C);
	pDC->LineTo(D);

	CPoint TLV(D.x, 0.8 * bigRect.top);
	CPoint BRV(A.x, 0.2 * bigRect.top);

	CRect valueRect(TLV, BRV);

	pDC->FloodFill(A.x, A.y - 10, RGB(210, 210, 210));

	for (int i = 0; i < nNotch; i++){
		pDC->SelectObject(pens[i]);
		int x1 = stopPoints[i]->x;
		int y1 = stopPoints[i]->y;
		int x2 = stopPoints[i + 1]->x;
		int y2 = stopPoints[i + 1]->y;
		pDC->Arc(valueRect, *stopPoints[i], *stopPoints[i + 1]);
	}

	pDC->SetViewportOrg(oldOrg);

	pDC->SelectObject(brushP);
	pDC->SelectObject(penP);
	newPen.DeleteObject();
	newBrush.DeleteObject();
	for (int i = 0; i < nParts; i++)
		(*pens[i]).DeleteObject();
	for (int i = 0; i < nParts + 1; i++)
		delete stopPoints[i];
}

void CLab1View::DrawWatches(CDC* pDC){
	CString* compasValues = new CString[8];
	compasValues[0] = CString("N");
	compasValues[1] = CString("NW");
	compasValues[2] = CString("W");
	compasValues[3] = CString("SW");
	compasValues[4] = CString("S");
	compasValues[5] = CString("SE");
	compasValues[6] = CString("E");
	compasValues[7] = CString("NE");
	DrawWatch(pDC, 0.26 * clientRect.right, 0.9*clientRect.bottom, 0.065 * clientRect.bottom, 16, compasValues, 8, 0.5*PI, 2.5*PI, 0, 45);

	CString* rightWatchValues = new CString[7];
	rightWatchValues[0] = CString("3");
	rightWatchValues[1] = CString("2");
	rightWatchValues[2] = CString("1");
	rightWatchValues[3] = CString("0");
	rightWatchValues[4] = CString("-1");
	rightWatchValues[5] = CString("-2");
	rightWatchValues[6] = CString("-3");
	DrawWatch(pDC, 0.74 * clientRect.right, 0.9*clientRect.bottom, 0.065 * clientRect.bottom, 13, rightWatchValues, 7, 0.25*PI, 1.75*PI, 0, 45);

	CString* leftWatchValues = new CString[10];
	leftWatchValues[0] = CString("4");
	leftWatchValues[1] = CString("8");
	leftWatchValues[2] = CString("12");
	leftWatchValues[3] = CString("16");
	leftWatchValues[4] = CString("18");
	leftWatchValues[5] = CString("22");
	leftWatchValues[6] = CString("24");
	leftWatchValues[7] = CString("28");
	leftWatchValues[8] = CString("32");
	DrawWatch(pDC, 0.32 * clientRect.right, 0.77*clientRect.bottom, 0.065 * clientRect.bottom, 17, leftWatchValues, 9, 2.25*PI, 0.75*PI, 0, 45);

	DrawWatchTilt(pDC, 0.68 * clientRect.right, 0.77*clientRect.bottom, 0.065 * clientRect.bottom, tilt);

	double* arr = new double[3];
	arr[0] = 1;
	arr[1] = 6;
	arr[2] = 1;
	COLORREF* colors = new COLORREF[3];
	colors[0] = RGB(0, 255, 0);
	colors[1] = RGB(255, 0, 0);
	colors[2] = RGB(0, 0, 255);

	CRect fuelRect;
	fuelRect.left = 0.4 * clientRect.right;
	fuelRect.top = 0.66 * clientRect.bottom;
	fuelRect.right = 0.48 * clientRect.right;
	fuelRect.bottom = 0.74 * clientRect.bottom;

	DrawFuelWatch(pDC, clientRect, fuelRect, 3, 60, 60, arr, 3, colors, 3);

	fuelRect.left = 0.52 * clientRect.right;
	fuelRect.top = 0.66 * clientRect.bottom;
	fuelRect.right = 0.6 * clientRect.right;
	fuelRect.bottom = 0.74 * clientRect.bottom;

	DrawFuelWatch(pDC, clientRect, fuelRect, 3, 60, 60, arr, 3, colors, 3);

	//DrawFuelWatch(pDC, rectP, CRect(x1, y1, x2, y2), 3, 60, 60, arr, 3, colors, 3);
}

// Lab 3
void CLab1View::DrawMap(CDC* pDC, CRect rcMap, CString strImage){
	DImage img;
	img.Load(strImage);
	int offset = 0.1 * rcMap.Width();
	CRect rect(rcMap.left + offset, rcMap.top + offset, rcMap.right - offset, rcMap.bottom - offset);
	img.Draw(pDC, CRect(0, 0, img.Width(), img.Height()), rect);
}
void CLab1View::DrawSky(CDC* pDC, double tilt){
	CRgn region1, region2, region3, defaultRegion;
	CreateSideWindowPath(pDC, false);
	region1.CreateFromPath(pDC);

	CreateSideWindowPath(pDC, true);
	region2.CreateFromPath(pDC);

	CreateCenterWindowPath(pDC);
	region3.CreateFromPath(pDC);

	region1.CombineRgn(&region1, &region2, RGN_OR);
	region1.CombineRgn(&region1, &region3, RGN_OR);
	pDC->SelectClipRgn(&region1);

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	XFORM Xform, XformOld;
	GetWorldTransform(pDC->m_hDC, &XformOld);

	Xform.eM11 = (FLOAT)cos(tilt);
	Xform.eM12 = (FLOAT)sin(tilt);
	Xform.eM21 = (FLOAT)-sin(tilt);
	Xform.eM22 = (FLOAT)cos(tilt);
	Xform.eDx = (FLOAT) 0.0;
	Xform.eDy = (FLOAT) 0.0;

	SetWorldTransform(pDC->m_hDC, &Xform);

	int cX = clientRect.right / 2, cY = clientRect.bottom / 2;
	pDC->SetViewportOrg(cX, cY);

	DImage img;
	img.Load(CString("Sky.jpg"));
	float scaleFactor = 2;
	CRect skyRect(-cX * scaleFactor, -cY * scaleFactor, (clientRect.right - cX) * scaleFactor, (clientRect.bottom - cY) * scaleFactor);
	img.Draw(pDC, CRect(0, 0, img.Width(), img.Height()), skyRect);

	DrawPlane(pDC);

	pDC->SetViewportOrg(0, 0);

	SetWorldTransform(pDC->m_hDC, &XformOld);
	SetGraphicsMode(pDC->m_hDC, prevMode);

	defaultRegion.CreateRectRgn(0, 0, clientRect.right, clientRect.bottom);
	pDC->SelectClipRgn(&defaultRegion);

	region1.DeleteObject();
	region2.DeleteObject();
	region3.DeleteObject();
	defaultRegion.DeleteObject();
}
void CLab1View::DrawPlane(CDC* pDC){
	DImage img;
	img.Load(CString("Suhoj.bmp"));

	CBitmap bmpPlane, bmpMask;
	bmpPlane.CreateCompatibleBitmap(pDC, img.Width(), img.Height());
	bmpMask.CreateBitmap(img.Width(), img.Height(), 1, 1, NULL);

	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextColor(RGB(0, 0, 0));

	CDC* srcDC = new CDC();
	srcDC->CreateCompatibleDC(pDC);
	srcDC->SelectObject(&bmpPlane);
	img.Draw(srcDC, CRect(0, 0, img.Width(), img.Height()), CRect(0, 0, img.Width(), img.Height()));

	CDC* destDC = new CDC();
	destDC->CreateCompatibleDC(pDC);
	destDC->SelectObject(&bmpMask);

	srcDC->SetBkColor(srcDC->GetPixel(0, 0));
	destDC->BitBlt(0, 0, img.Width(), img.Height(), srcDC, 0, 0, SRCCOPY);

	srcDC->SetBkColor(RGB(0, 0, 0));
	srcDC->SetTextColor(RGB(255, 255, 255));

	srcDC->BitBlt(0, 0, img.Width(), img.Height(), destDC, 0, 0, SRCAND);
	int x = -0.2 * clientRect.right, y = -0.3 * clientRect.bottom;
	float scaleFactor = 0.5;
	int width = img.Width() * scaleFactor;
	int height = img.Height() * scaleFactor;

	pDC->StretchBlt(x, y, width, height, destDC, 0, 0, img.Width(), img.Height(), SRCAND);
	pDC->StretchBlt(x, y, width, height, srcDC, 0, 0, img.Width(), img.Height(), SRCPAINT);

	srcDC->DeleteDC();
	delete srcDC;
	destDC->DeleteDC();
	delete destDC;
}
void CLab1View::AdjustBitmap(CBitmap* pBitmap, float fB, float fC) {
	DWORD count = clientRect.right * clientRect.bottom * 4;
	BYTE* bytes = new BYTE[count];
	pBitmap->GetBitmapBits(count, bytes);
	
	for (DWORD i = 0; i < count; i++){
		float value = bytes[i] / 256.0;
		
		if (fB <= 0){
			value = value * (1 + fB);
		}else{
			value = fB * (1.0 - value) + value;
		}

		value = (value - 0.5) * tan((fC + 1) * PI / 4) + 0.5;
		bytes[i] = value * 255.0;
	}

	pBitmap->SetBitmapBits(count, bytes);
	delete[] bytes;
}


// Helpers
CRect CLab1View::Inside(int x1, int y1, int x2, int y2, double xOffset, double yOffset){
	CRect rect;
	int outerWidth = x2 - x1;
	int outerHeight = y2 - y1;

	int dim = outerWidth > outerHeight ? outerHeight : outerWidth;

	int offsetX = (double)(outerWidth - dim) * xOffset;
	int offsetY = (double)(outerHeight - dim) * yOffset;

	rect.left = x1 + offsetX;
	rect.top = y1 + offsetY;
	rect.right = rect.left + dim;
	rect.bottom = rect.top + dim;

	return rect;
}


// Events
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
void CLab1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'C'){
		tilt += 0.05*PI;
		Invalidate();
	} else if (nChar == 'V'){
		tilt -= 0.05*PI;
		Invalidate();
	}
	else if (nChar == 'D'){
		if (brightness > -0.9) brightness -= 0.1;
		Invalidate();
	}
	else if (nChar == 'F'){
		if (brightness < 0.9) brightness += 0.1;
		Invalidate();
	}
	else if (nChar == 'E'){
		if (contrast > -0.9) contrast -= 0.1;
		Invalidate();
	}
	else if (nChar == 'R')
	{
		if (contrast < 0.9) contrast += 0.1;
		Invalidate();
	}
	else if (nChar == 'S'){
		DImage img(bufferBmp);
		img.Save(CString("Cockpit.bmp"));
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
