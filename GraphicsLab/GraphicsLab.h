
// GraphicsLab.h : main header file for the GraphicsLab application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Lab1:
// See GraphicsLab.cpp for the implementation of this class
//

class Lab1 : public CWinApp
{
public:
	Lab1();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Lab1 theApp;
