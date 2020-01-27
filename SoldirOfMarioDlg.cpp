// SoldirOfMarioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoldirOfMario.h"
#include "SoldirOfMarioDlg.h"
#include "MY.LIB/Total.h"

#include "ddraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void WizOnInitialUpdate();
void WizCloseDirectX();

void vvvv()
{
//SoldirOfMarioDlg.cpp
}

void vvvv222()
{
//SoldirOfMarioDlg.cpp
}


#define EXITTOOS_CANNOT			1
#define EXITTOOS_CAN			2
#define EXITTOOS_AUTOMATIC		3
volatile int ExitToOS=EXITTOOS_CAN;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoldirOfMarioDlg dialog

CSoldirOfMarioDlg::CSoldirOfMarioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoldirOfMarioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoldirOfMarioDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoldirOfMarioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoldirOfMarioDlg)
	DDX_Control(pDX, IDC_BUTTON_ABOUT, m_about);
	DDX_Control(pDX, IDC_BUTTON_HELP, m_help);
	DDX_Control(pDX, IDC_BUTTON_START_GAME, m_start);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSoldirOfMarioDlg, CDialog)
	//{{AFX_MSG_MAP(CSoldirOfMarioDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_START_GAME, OnButtonStartGame)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_WM_HELPINFO()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoldirOfMarioDlg message handlers

BOOL CSoldirOfMarioDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	OnButtonStartGame();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoldirOfMarioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSoldirOfMarioDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting

		RECT rt;
		GetClientRect(&rt);

		char r=0,g=0,b=0;

		for(int i=0; i<127; i++)
		{
			dc.FillSolidRect(&rt, RGB(r,g,b));

			rt.top++;

			rt.left++;

			rt.bottom--;

			rt.right--;

			r++;
			g++;
			b++;
		}

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSoldirOfMarioDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//**********************************************************************************

#include "my.lib\level.h"
#include "my.lib\keyboard.h"
#include "my.lib\screen.h"
#include "my.lib\sprite.h"
#include "my.lib\mario.h"
#include "my.lib\timer.h"
#include "my.lib\mouse.h"	

extern SUPERMARIO Supermario;
extern TIMER Timer;
extern MOUSE Mouse;

void WizCreatePalette();


LPDIRECTDRAW m_pDirectDrawObj;
LPDIRECTDRAWSURFACE m_pPrimarySurface;
LPDIRECTDRAWSURFACE m_pBackBuffer;
LPDIRECTDRAWPALETTE m_pDirDrawPalette;
BOOL m_dDrawOK;


//создаем предопределенный объект
KEYBOARD Keyb;

//int DISPLAY_HORIZONTAL=1024,
//	DISPLAY_VERTICAL=768;

int DISPLAY_HORIZONTAL=640	,
	DISPLAY_VERTICAL=480;


//int DISPLAY_HORIZONTAL=1024,
//	DISPLAY_VERTICAL=768;

RECT WindowRect; //текущее положение окна

DWORD WINAPI TimerFunction(LPVOID param)
{

	while(1)
	{
		Sleep(10);
		
		Timer.TotalCounter++;
		Timer.Counter++;

		if (ExitToOS==EXITTOOS_AUTOMATIC) return 32768;
	}
}

	COLORREF screendata_smoth[320*200*4];

bool CopyDoubleBufferToScreen(LPDIRECTDRAWSURFACE pSurface)
{
	//проверка на "потерю" поверхности
	if (pSurface->IsLost())
	{
		//восстанавливаем поверхность в данном случае
		pSurface->Restore();
	}

	DDSURFACEDESC ddSDesc={0};
	bool ok=false;

	ddSDesc.dwSize=sizeof(DDSURFACEDESC);

	//блокируем поверхность, получая указатель на данные
	HRESULT result = pSurface->Lock(NULL, &ddSDesc,
		DDLOCK_SURFACEMEMORYPTR| DDLOCK_NOSYSLOCK,NULL);

	if (result==DD_OK)
	{
		UINT hei=ddSDesc.dwHeight;

		char *buf= (char*) ddSDesc.lpSurface;
		int z=0;

		//исходные данные (буфер 320x200 точек) 1 байт на точку
		BYTE *sourc=scr.DoubleBuffer;

		int add_pitch=ddSDesc.lPitch;


		COLORREF screendata[320*200];


		scr.ConvertDoubleBufferToTrueColor(screendata);

		for(int x=0; x<320; x++)
		for(int y=0; y<200; y++)
		{
			COLORREF clr=screendata[y*320+x];
			DWORD I=y*2*640+x*2;
			screendata_smoth[I]=clr;
			screendata_smoth[I+1]=clr;
			screendata_smoth[I+640]=clr;
			screendata_smoth[I+640+1]=clr;


			//screendata_smoth[y*640+x+1]=screendata[y*320+x];
		}

		//исходные данные - 4 байта на точку
		//sourc=(BYTE*) screendata;
		sourc=(BYTE*) screendata_smoth;

		//если установлено соотвествующее разрешение
		//корректируем расположение буфера
		if (DISPLAY_HORIZONTAL>= 640 && DISPLAY_VERTICAL>=400)
		{
			int ScaleX=3,ScaleY=3;

			//центровка oX
			buf+=(ddSDesc.dwWidth*4-320*4*ScaleX)/2;
			//buf+=WindowRect.left*4;

			//центровка oY
			buf+=(ddSDesc.dwHeight-200*ScaleY)/2*add_pitch;
			//buf+=ddSDesc.dwWidth*WindowRect.top;


			//ВНИМАНИЕ!! верно только для разрешения не ниже 640x400

			buf=(char*)screendata_smoth;
			
			
			for(int i=0; i<400-1;i++)
			{
				/*
				_asm 
				{
					pusha
					//lea edi,screendata_smoth
					mov edi,buf
				l2:
					mov esi,sourc

					mov ecx,640*4
					cld
				l1:
					xor ax,ax
					xor bx,bx

					mov bl,[esi]
					add ax,bx

					mov bl,[esi+4]
					add ax,bx

					mov bl,[esi+640*4]
					add ax,bx

					mov bl,[esi+640*4+4]
					add ax,bx


					shr ax,2
					
					inc esi
					
					mov [edi],al
					inc edi

				
					loop l1
					
				
					popa
				}
				sourc+=640*4;
				buf+=640*4;
				*/
			}
			


		buf= (char*) ddSDesc.lpSurface;
		//sourc=(BYTE*)screendata;
		sourc=(BYTE*)screendata_smoth;
		

		ScaleX=2;
		ScaleY=2;
		//центровка oX
		buf+=(ddSDesc.dwWidth*4-320*4*ScaleX)/2;
		//buf+=WindowRect.left*4;

		//центровка oY
		buf+=(ddSDesc.dwHeight-200*ScaleY)/2*add_pitch;
		//buf+=ddSDesc.dwWidth*WindowRect.top;


			for(i=0; i<400-1;i++)
			{
				{
				_asm 
				{
					pusha
					//lea edi,screendata_smoth
					mov edi,buf
					
				l2z:
					mov esi,sourc

					mov ecx,320*2
					cld
				l1z:
					lodsd
					stosd
					
					loop l1z
				
					popa
				}
				buf+=add_pitch;
				}
				sourc+=320*4*2;
			}
			


		pSurface->Unlock(ddSDesc.lpSurface);
		ok=true;
	}


	}

	return ok;

}

bool CreateSurfaces()
{
	DDSURFACEDESC ddSDesc={0};
	DDSCAPS ddsCaps;
	bool ok = false;

	ddSDesc.dwSize=sizeof(DDSURFACEDESC);
	ddSDesc.dwFlags= DDSD_CAPS| DDSD_BACKBUFFERCOUNT;
	ddSDesc.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE
		| DDSCAPS_FLIP | DDSCAPS_COMPLEX;
	ddSDesc.dwBackBufferCount =1;


	HRESULT result = m_pDirectDrawObj->CreateSurface
		(&ddSDesc, &m_pPrimarySurface, NULL);

	if (result == DD_OK)
	{
		ddsCaps.dwCaps= DDSCAPS_BACKBUFFER;
		result = m_pPrimarySurface->GetAttachedSurface(&ddsCaps,
			&m_pBackBuffer);

		if (result == DD_OK) ok=true;
			//m_pPrimarySurface->Flip(NULL,0);
	
	}

	return ok;

}

//функция работает как отдельный поток
DWORD WINAPI StartFunction(LPVOID param)
{
	ExitToOS=EXITTOOS_CANNOT;
	Supermario.DrawMenu();
//	Supermario.game();

	//для возможности повторного запуска игры без закрытия диалогового
	//окна здесь нужно освободить все спрайты
	WizCloseDirectX();

	ExitToOS=EXITTOOS_AUTOMATIC;
	return 65536;
}


void WizCloseDirectX()
{
	if (m_pDirDrawPalette) {
		m_pDirDrawPalette->Release();
		m_pDirDrawPalette=NULL;
	}
	
	if (m_pPrimarySurface)
	{
		m_pPrimarySurface->Release();
		m_pPrimarySurface=NULL;
	}
	
	if (m_pDirectDrawObj) 
	{
		m_pDirectDrawObj->Release();
		m_pDirectDrawObj=NULL;
	}
}

void WizOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	Keyb.OnWM_KEYDOWN(nChar);
}

void WizOnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	Keyb.OnWM_KEYUP(nChar);
}

void Mesg(char *s)
{
	HWND hwnd=0;
	MessageBox(hwnd, s, "Soldir of Mario", MB_OK);
}

void WizOnInitialUpdate() 
{
	m_dDrawOK=false;
	m_pPrimarySurface=NULL;
	m_pBackBuffer=NULL;

	HRESULT result= DirectDrawCreate(NULL,
		&m_pDirectDrawObj,NULL);

	if (result != DD_OK) return;

	HWND hWnd=AfxGetMainWnd()->m_hWnd;

	result=m_pDirectDrawObj->SetCooperativeLevel(hWnd,
		DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT);

	//result=m_pDirectDrawObj->SetCooperativeLevel(hWnd,
	//	DDSCL_NORMAL );
	
	//	result=m_pDirectDrawObj->SetCooperativeLevel(hWnd,
	//	DDSCL_EXCLUSIVE| DDSCL_ALLOWREBOOT);

	if (result != DD_OK) 
	{
		Mesg("SetCooperativeLevel error");
		return;
	}

	//result = m_pDirectDrawObj->SetDisplayMode(DISPLAY_HORIZONTAL,
	//	DISPLAY_VERTICAL,8);

	int xl=GetSystemMetrics(SM_CXSCREEN);
	int yl=GetSystemMetrics(SM_CYSCREEN);
	//int xl=DISPLAY_HORIZONTAL;
	//int yl=DISPLAY_VERTICAL;


	DISPLAY_HORIZONTAL=xl;
	DISPLAY_VERTICAL=yl;

	result = m_pDirectDrawObj->SetDisplayMode(DISPLAY_HORIZONTAL,
		DISPLAY_VERTICAL,32);


	if (result != DD_OK) 
	{
		Mesg("SetDisplayMode error");
		return;
	}
	
	BOOL success=CreateSurfaces();

	if (!success) 
	{
		Mesg("CreateSurface error");
		return;
	}

	//m_dDrawOK=CopyDoubleBufferToScreen(m_pBackBuffer);

	WizCreatePalette();
  
	//создаем поток
	DWORD threadid1;
	HANDLE hThread1=CreateThread(NULL, 1024*100, StartFunction,
	NULL, 0, &threadid1);

	//SetThreadPriority(hThread1, THREAD_PRIORITY_ABOVE_NORMAL);

	//создаем поток
	DWORD threadid2;
	HANDLE hThreadTimer=CreateThread(NULL, 1024*100, TimerFunction,
	NULL, 0, &threadid2);
	
	SetThreadPriority(hThreadTimer, THREAD_PRIORITY_HIGHEST);

	SetCursor(LoadCursor(NULL,IDC_NO));
}

void RedrawMarioWindow()
{
	if (m_pPrimarySurface!=NULL)
	{
		CopyDoubleBufferToScreen(m_pPrimarySurface);
	}
}

void WizGetPaletteRegisters(DWORD startRegister, int count, PALETTEENTRY * values)
{
	m_pDirDrawPalette->GetEntries(
	//m_pDirDrawPalette, 
	0, //must be zero
	startRegister,
	count,
	values);

}

//изменяет существущую палитру
PALETTEENTRY WizGetPaletteRegister(DWORD Register)
{
	PALETTEENTRY pl;
	DWORD dwStartingEntry=1;
	DWORD dwCount=3;
	m_pDirDrawPalette->GetEntries(
		//m_pDirDrawPalette, 
		0, //must be zero
		Register,
		1,
		&pl);
	return pl;
}


//изменяет существущую палитру
void WizSetPaletteRegister(DWORD startRegister, int size, PALETTEENTRY * value)
{
	/*HRESULT SetEntries(
  LPDIRECTDRAWPALETTE lpDDPalette,
  DWORD dwFlags,
  DWORD dwStartingEntry,
  DWORD dwCount,
  LPPALETTEENTRY lpEntries
  );*/

	if (m_pDirDrawPalette == NULL) return;
	DWORD dwStartingEntry=1;
	DWORD dwCount=3;
	m_pDirDrawPalette->SetEntries(
		//m_pDirDrawPalette, 
		0, //must be zero
		startRegister,
		size,
		value);
}

void WizCreatePalette()
{
	LPDIRECTDRAWPALETTE palette;

	PALETTEENTRY pEntries[256];

	CFile file;
	if (file.Open("graph\\palette.dat", file.modeRead))
	{
		for(int i=0; i<256; i++)
		{
			file.Read(&pEntries[i].peRed,1);
			file.Read(&pEntries[i].peGreen,1);
			file.Read(&pEntries[i].peBlue,1);

			pEntries[i].peRed<<=2;
			pEntries[i].peGreen<<=2;
			pEntries[i].peBlue<<=2;
			pEntries[i].peFlags=0;


		}
		file.Close();
	}

	m_pDirectDrawObj->CreatePalette(DDPCAPS_8BIT,
		pEntries, &palette,NULL);


	m_pPrimarySurface->SetPalette(palette);

	m_pDirDrawPalette=palette;
}

void CSoldirOfMarioDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	WizOnKeyDown(nChar,nRepCnt, nFlags);
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSoldirOfMarioDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	WizOnKeyUp(nChar, nRepCnt, nFlags);	
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CSoldirOfMarioDlg::PreTranslateMessage(MSG* pMsg) 
{
	BYTE key=pMsg->wParam;

	if (key==VK_F12) return 0;

	if (pMsg->message==WM_KEYDOWN)
	{
		WizOnKeyDown(key,0,0);

		if (key==VK_RETURN) return TRUE;
		if (key!=VK_TAB) return FALSE;
	}

	if (pMsg->message==WM_KEYUP)
	{
		WizOnKeyUp(key,0,0);

		if (key==VK_RETURN) return TRUE;
		if (key!=VK_TAB) return FALSE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSoldirOfMarioDlg::OnClose() 
{
	if (ExitToOS == EXITTOOS_CAN) CDialog::OnClose();
}

void CSoldirOfMarioDlg::OnButtonStartGame() 
{
	SetWindowText("Mario");

	m_start.EnableWindow(false);
	m_help.EnableWindow(false);
	m_about.EnableWindow(false);

	ShowWindow(SW_HIDE);
	SetTimer(1,50,NULL);
	WizOnInitialUpdate();

}

void CSoldirOfMarioDlg::OnTimer(UINT nIDEvent) 
{
	GetWindowRect(&WindowRect);

	if (ExitToOS == EXITTOOS_CANNOT) 
	{
		SetCursor(NULL);	
	}
	else 
	{
		SetCursor(LoadCursor(NULL,IDC_ARROW));
	}

	if (ExitToOS == EXITTOOS_AUTOMATIC)
	{
		SendMessage(WM_CLOSE);
		exit(0);
	}

	//MoveWindow(0,0,400,400);
	CDialog::OnTimer(nIDEvent);
}

void CSoldirOfMarioDlg::OnButtonAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

BOOL CSoldirOfMarioDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{

	return FALSE;
	
//	return CDialog::OnHelpInfo(pHelpInfo);
}

void CSoldirOfMarioDlg::OnSize(UINT nType, int cx, int cy) 
{

}

void CSoldirOfMarioDlg::OnButtonExit() 
{
	CDialog::OnClose();	
}

void CSoldirOfMarioDlg::OnMouseMove(UINT nFlags, CPoint point) 
{

	Mouse.x=point.x/2;
	Mouse.y=point.y/2;
	
	CDialog::OnMouseMove(nFlags, point);
}

void CSoldirOfMarioDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//Mouse.Buttons^=~MOUSE::BUTTON_LEFT;
	Mouse.Buttons=0;
	CDialog::OnLButtonUp(nFlags, point);
}

void CSoldirOfMarioDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	Mouse.Buttons|=MOUSE::BUTTON_LEFT;
	CDialog::OnLButtonDown(nFlags, point);
}

void CSoldirOfMarioDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	Mouse.Buttons|=MOUSE::BUTTON_RIGHT;
	CDialog::OnRButtonDown(nFlags, point);
}

void CSoldirOfMarioDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{

	//Mouse.Buttons^=~MOUSE::BUTTON_RIGHT;
	Mouse.Buttons=0;
	CDialog::OnRButtonUp(nFlags, point);
}

int CSoldirOfMarioDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(1,100,NULL);
	return 0;
}

BOOL CSoldirOfMarioDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

BOOL CSoldirOfMarioDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
	return CDialog::PreCreateWindow(cs);
}
