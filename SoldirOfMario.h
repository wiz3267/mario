// SoldirOfMario.h : main header file for the SOLDIROFMARIO application
//

#if !defined(AFX_SOLDIROFMARIO_H__18E0C114_E9C5_4927_AF06_41D7BE94AAD1__INCLUDED_)
#define AFX_SOLDIROFMARIO_H__18E0C114_E9C5_4927_AF06_41D7BE94AAD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoldirOfMarioApp:
// See SoldirOfMario.cpp for the implementation of this class
//

class CSoldirOfMarioApp : public CWinApp
{
public:
	CSoldirOfMarioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoldirOfMarioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSoldirOfMarioApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLDIROFMARIO_H__18E0C114_E9C5_4927_AF06_41D7BE94AAD1__INCLUDED_)
