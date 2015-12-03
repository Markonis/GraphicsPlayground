
// Col2012.h : main header file for the Col2012 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCol2012App:
// See Col2012.cpp for the implementation of this class
//

class CCol2012App : public CWinApp
{
public:
	CCol2012App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCol2012App theApp;
