// SoldirOfMarioDlg.cpp : implementation file
//
//TODO - ЧТО СДЕЛАТЬ 26 февраля 2020
//РАЗМЕР БУФЕРА ЭКРАНА БОЛЬШЕ ЧЕМ 320x200 ! ! !
//CTRL+O   открытие окна с файлом проекта, редакированием и перезапуск игры

//с возможностью отмены

//музыку загрузить (+)

//убрать мерцание экрана

//проработать меню, регулировка уровеня звука

//FPS - иногда FPS работает в два раза медленней

//подумать над ускорением загрузки/декодирования звука
//или использовать библиотеку BASS для проигрывания звуков *.mp3

//изменить название игры, и классов, и переменных
//посмотреть инструмент для этого



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

//
CPoint CurrentWindowPosition;


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
	ON_WM_MOVE()
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

/*void CSoldirOfMarioDlg::OnPaint() 
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


		dc.FillSolidRect(&rt, RGB(r,g,127));

		//CDialog::OnPaint();
	}
}*/


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
		Sleep(15);
		
		Timer.TotalCounter++;
		Timer.Counter++;

		if (ExitToOS==EXITTOOS_AUTOMATIC) return 32768;
	}
}

//содержит экран 320x200 в два раза больше
//COLORREF screendata_smoth[320*2 * 200*2];
COLORREF *screendata_smoth = NULL;

long	*screendata_1x1 = NULL;
long	*screendata_transform = NULL;
long	*screendata_forCopy;
long	*screendata_trans = NULL;
long	**screendata_ref = NULL;
char	*loadArray = NULL;
int		sizeOfLoadArray = 1000;

int		*arrX = NULL;
int		*arrY = NULL;
bool	useTransparent = true;
bool	useLowResTransform = false;
bool	useScrollMode = true;
bool	useLoadEffect = false;

int		borderW = 20;
int		borderH = 20;
int		borderSeg = 300;
long	borderColor0 = 0x0000ffL;
//long	borderColor1 = 0xffff00L;
long	borderColor1 = 0x00ffffL;
//long	borderColor1 = 0xff00ffL;
long	borderOffset = 0;

bool	useWideBorderScreen = true;
bool	useWideBorderScreenSmooth = false;
bool	useExtendedBorder = true;
bool	useExtendedBorderTransparent = false;

int		*borderScreenOffset = NULL;
int		*borderScreenOffset1 = NULL;
int		*borderScreenOffset2 = NULL;
int		*borderScreenOffset3 = NULL;
int		*borderScreenOffset4 = NULL;

int		screenEffectType = 1;
int		screenEffectCount = 6;

double getAtEdgeY( double x1, double y1, double x2, double y2, double x )
{
	// ({x1, y1} + ({x2, y2} - {x1, y1}) * t).x = x
	// x1 + (x2 - x1) * t = x
	// t = (x - x1) / (x2 - x1)
	// y1 + (y2 - y1) * t

	double	t = (x - x1) / (x2 - x1);
	double	y = y1 + (y2 - y1) * t;

	return y;
}

double uFunc1 (double t)
{
	double v = 0.5 + asin( -1 + 2 * t ) / 3.14159;

	if (v < 0) v = 0;
	if (v > 1) v = 1;

	return v;
}

double uFunc2 (double t)
{
//	double points[11] = { 0.0, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.85, 1.0 };	
	double points[11] = { 0.0, 0.2, 0.3, 0.35, 0.45, 0.5, 0.6, 0.65, 0.7, 0.8, 1.0 };		
	int	   k = (int)(t / 0.1);

	double x1 = 0.1 * k;
	double x2 = 0.1 * (k + 1);
	double y1 = points[k];
	double y2 = points[k + 1];
	double x = t;
	double y = getAtEdgeY( x1, y1, x2, y2, x );
	double v = y;
	
	if (v < 0) v = 0;
	if (v > 1) v = 1;

	return v;
}

int eFunc1( int k, int n )
{
	double	t = ((double)k) / (n - 1);
	int		r = (int)(uFunc1( t ) * (n - 1));

	if (r < 0) r = 0;
	if (r >= n) r = n - 1;

	return r;
}

int *aFunc1( int n )
{
	int		*arr = new int[n];

	for( int i = 0; i < n; i++ )
	{
		arr[i] = eFunc1( i, n );
	}
	return arr;
}

void DrawBorder ( int bufW, int bufH )
{
	static	long *wideScreen = NULL;
	static  long **ws_screendata_ref = NULL;
	int		wideScreenW = 320 + borderW * 2;
	int		wideScreenH = 200 + borderH * 2;
	int		gx, gy;
	
	if (wideScreen == NULL)
	{
		wideScreen = new long [wideScreenW * wideScreenH];
	}

	for( gy = 0; gy < wideScreenH; gy++ )
	{
		for( gx = 0; gx < wideScreenW; gx++ )
		{
			long	color = 0;			
			
			if (gx < borderW || gx > borderW + 319 || gy < borderH || gy > borderH + 199)
			{
				int		borderCount = gy * wideScreenW + gx;
				int		seg = borderCount / borderSeg;
				int		borderIndex = (borderOffset + seg) % sizeOfLoadArray;
				char	borderBit = loadArray [ borderIndex ];

				if (borderBit == 0) 
					color = borderColor0;
				else
					color = borderColor1;
			}
			else
			{
				int		x = gx - borderW;
				int		y = gy - borderH;

				color = screendata_1x1[ y * 320 + x ];
			}
			wideScreen[ wideScreenW * gy + gx ] = color;
		}
	}

	for( gy = 0; gy < wideScreenH; gy++ )
	{
		for( gx = 0; gx < wideScreenW; gx++ )
		{
			int		x, y;

			if (useExtendedBorderTransparent)
			{
				x = (gx * 319) / wideScreenW;
				y = (gy * 199) / wideScreenH;
			}
			else
			{
				x = gx - borderW;
				y = gy - borderH;
			}

			long	color1 = wideScreen[ gy * wideScreenW + gx ];		
			long	color2 = screendata_trans[y * 320 + x];
			int		t = (((unsigned char*)&color2)[3]);

			int		r1 = ((unsigned char*)&color1)[0];
			int		g1 = ((unsigned char*)&color1)[1];			
			int		b1 = ((unsigned char*)&color1)[2];			

			int		r2 = ((unsigned char*)&color2)[0];
			int		g2 = ((unsigned char*)&color2)[1];			
			int		b2 = ((unsigned char*)&color2)[2];			

			int		r = r1 + ((r2 - r1) * t) / 255;
			int		g = g1 + ((g2 - g1) * t) / 255;
			int		b = b1 + ((b2 - b1) * t) / 255;

			if (r < 0) r = 0;
			if (r > 255) r = 255;
			if (g < 0) g = 0;
			if (g > 255) g = 255;
			if (b < 0) b = 0;
			if (b > 255) b = 255;

			long			color = 0;

			((char*)&color)[0] = r;
			((char*)&color)[1] = g;
			((char*)&color)[2] = b;

			if (useExtendedBorderTransparent)
				wideScreen[gy * wideScreenW + gx] = color;
			else
			{
				if (gx >= borderW && gx <= borderW + 319 && gy >= borderH && gy <= borderH + 199)
					wideScreen[gy * wideScreenW + gx] = color;
			}
		}
	}

	if (ws_screendata_ref == NULL)
	{
		ws_screendata_ref = new long* [bufW * bufH];

		for( gy = 0; gy < bufH; gy++ )
		{
			for( gx = 0; gx < bufW; gx++ )
			{
				int	newGx = (gx * (wideScreenW - 1)) / (bufW - 1);
				int newGy = (gy * (wideScreenH - 1)) / (bufH - 1);

				ws_screendata_ref[ gy * bufW + gx ] = &wideScreen[ newGy * wideScreenW + newGx ];
			}
		}
	}

	long **pDatSrc = ws_screendata_ref;
	long *pDat = screendata_forCopy;

	for( gy = 0; gy < bufH; gy++ )
	{
		for( gx = 0; gx < bufW; gx++ )
		{
			*pDat++ = **pDatSrc;
			pDatSrc++;
		}
	}
}

bool CopyDoubleBufferToScreen(LPDIRECTDRAWSURFACE pSurface)
{
	static int keyYCount = 0;
	
	if (Keyb[KEY_Y])
	{
		keyYCount++;

		if (keyYCount > 10)
		{
			screenEffectType++;
			if (screenEffectType > screenEffectCount)
				screenEffectType = 1;

			keyYCount = 0;
		}
	}
	
	if (screenEffectType == 1)
	{
		useLowResTransform = false;
		useScrollMode = false;
		useLoadEffect = false;
		useWideBorderScreen = false;
		useWideBorderScreenSmooth = false;
		useExtendedBorder = true;
		useExtendedBorderTransparent = true;
		borderColor0 = 0x0000ffL;
		borderColor1 = 0x00ffffL;
		useTransparent = true;
	}
	if (screenEffectType == 2)
	{
		useLowResTransform = false;
		useScrollMode = false;
		useLoadEffect = false;
		useWideBorderScreen = false;
		useWideBorderScreenSmooth = false;
		useExtendedBorder = true;
		useExtendedBorderTransparent = false;
		borderColor0 = 0x0000ffL;
		borderColor1 = 0x00ffffL;
		useTransparent = true;
	}
	if (screenEffectType == 3)
	{
		useLowResTransform = true;
		useScrollMode = false;
		useLoadEffect = false;
		useWideBorderScreen = false;
		useWideBorderScreenSmooth = false;
		useExtendedBorder = false;
		useExtendedBorderTransparent = false;
		useTransparent = true;
	}
	if (screenEffectType == 4)
	{
		useLowResTransform = true;
		useScrollMode = true;
		useLoadEffect = false;
		useWideBorderScreen = false;
		useWideBorderScreenSmooth = false;
		useExtendedBorder = false;
		useExtendedBorderTransparent = false;
		useTransparent = true;
	}
	if (screenEffectType == 5)
	{
		useLowResTransform = false;
		useScrollMode = false;
		useLoadEffect = false;
		useWideBorderScreen = false;
		useWideBorderScreenSmooth = false;
		useExtendedBorder = false;
		useExtendedBorderTransparent = false;
		useTransparent = true;
	}
	if (screenEffectType == 6)
	{
		useLowResTransform = false;
		useScrollMode = false;
		useLoadEffect = false;
		useWideBorderScreen = false;
		useWideBorderScreenSmooth = false;
		useExtendedBorder = false;
		useExtendedBorderTransparent = false;
		useTransparent = false;
	}
	
	int		screenW;
	int		screenH;

	screenW = GetSystemMetrics( SM_CXSCREEN );
	screenH = GetSystemMetrics( SM_CYSCREEN );

	if (screendata_smoth == NULL) screendata_smoth = new COLORREF [screenW * screenH];
	
	if (CurrentWindowPosition.y < 0) return 0;

	//проверка на "потерю" поверхности
	if (pSurface->IsLost())
	{
		//восстанавливаем поверхность в данном случае
		pSurface->Restore();
	}

	DDSURFACEDESC ddSDesc1={0};
	bool okk = false;

	ddSDesc1.dwSize = sizeof(DDSURFACEDESC);

	//блокируем поверхность, получая указатель на данные
	HRESULT result = pSurface->Lock( NULL, &ddSDesc1, DDLOCK_SURFACEMEMORYPTR| DDLOCK_NOSYSLOCK,NULL );

	if (result == DD_OK)
	{
		char *buf= (char*)ddSDesc1.lpSurface;

		int add_pitch=ddSDesc1.lPitch;


		COLORREF screendata[320*200];

		int ScaleX=2,ScaleY=2;


		scr.ConvertDoubleBufferToTrueColor(screendata);

//		screendata_1x1 = (long*)screendata;

		if (screendata_1x1 == NULL)
		{
			screendata_1x1 = new long [320 * 200];
		}

		if (loadArray == NULL)
		{
			loadArray = new char [sizeOfLoadArray];

			for( int i = 0; i < sizeOfLoadArray; i++ )
			{
				int	k = rand() % 1000;
				
				if (k < 500)
					loadArray[i] = 0;
				else
					loadArray[i] = 1;
			}
		}

		int		gx, gy;

		if (borderScreenOffset == NULL)
		{
			borderScreenOffset = new int [320 * 200];
			borderScreenOffset1 = new int [320 * 200];
			borderScreenOffset2 = new int [320 * 200];
			borderScreenOffset3 = new int [320 * 200];
			borderScreenOffset4 = new int [320 * 200];

			int		x1 = borderW;
			int		x2 = 319 - borderW;
			int		y1 = borderH;
			int		y2 = 199 - borderH;
			
			for( gy = 0; gy < 200; gy++ )
			{
				for( gx = 0; gx < 320; gx++ )
				{
					int		valueOffset = 0;					
					int		valueOffset1 = 0;
					int		valueOffset2 = 0;
					int		valueOffset3 = 0;
					int		valueOffset4 = 0;
					
					if (gx >= x1 && gx <= x2 && gy >= y1 && gy <= y2)
					{
						double	tx, ty;
						int		nGX, nGY;
						
						// основное
						tx = ((double)(gx - x1)) / (x2 - x1);
						ty = ((double)(gy - y1)) / (y2 - y1);

						if (tx < 0) tx = 0;
						if (tx > 1) tx = 1;
						if (ty < 0) ty = 0;
						if (ty > 1) ty = 1;

						nGX = (int)319 * tx;
						nGY = (int)199 * ty;

						if (nGX < 0) nGX = 0;
						if (nGX > 319) nGX = 319;
						if (nGY < 0) nGY = 0;
						if (nGY > 199) nGY = 199;

						valueOffset = nGY * 320 + nGX;

						// пиксель 1
						tx = ((double)(gx + 0.25 - x1)) / (x2 - x1);
						ty = ((double)(gy + 0.25 - y1)) / (y2 - y1);

						if (tx < 0) tx = 0;
						if (tx > 1) tx = 1;
						if (ty < 0) ty = 0;
						if (ty > 1) ty = 1;

						nGX = (int)319 * tx;
						nGY = (int)199 * ty;

						if (nGX < 0) nGX = 0;
						if (nGX > 319) nGX = 319;
						if (nGY < 0) nGY = 0;
						if (nGY > 199) nGY = 199;

						valueOffset1 = nGY * 320 + nGX;

						// пиксель 2
						tx = ((double)(gx + 0.75 - x1)) / (x2 - x1);
						ty = ((double)(gy + 0.25 - y1)) / (y2 - y1);

						if (tx < 0) tx = 0;
						if (tx > 1) tx = 1;
						if (ty < 0) ty = 0;
						if (ty > 1) ty = 1;

						nGX = (int)319 * tx;
						nGY = (int)199 * ty;

						if (nGX < 0) nGX = 0;
						if (nGX > 319) nGX = 319;
						if (nGY < 0) nGY = 0;
						if (nGY > 199) nGY = 199;

						valueOffset2 = nGY * 320 + nGX;

						// пиксель 3
						tx = ((double)(gx + 0.25 - x1)) / (x2 - x1);
						ty = ((double)(gy + 0.75 - y1)) / (y2 - y1);

						if (tx < 0) tx = 0;
						if (tx > 1) tx = 1;
						if (ty < 0) ty = 0;
						if (ty > 1) ty = 1;

						nGX = (int)319 * tx;
						nGY = (int)199 * ty;

						if (nGX < 0) nGX = 0;
						if (nGX > 319) nGX = 319;
						if (nGY < 0) nGY = 0;
						if (nGY > 199) nGY = 199;

						valueOffset3 = nGY * 320 + nGX;

						// пиксель 4
						tx = ((double)(gx + 0.75 - x1)) / (x2 - x1);
						ty = ((double)(gy + 0.75 - y1)) / (y2 - y1);

						if (tx < 0) tx = 0;
						if (tx > 1) tx = 1;
						if (ty < 0) ty = 0;
						if (ty > 1) ty = 1;

						nGX = (int)319 * tx;
						nGY = (int)199 * ty;

						if (nGX < 0) nGX = 0;
						if (nGX > 319) nGX = 319;
						if (nGY < 0) nGY = 0;
						if (nGY > 199) nGY = 199;

						valueOffset4 = nGY * 320 + nGX;
					}
					borderScreenOffset[ gy * 320 + gx ] = valueOffset;
					borderScreenOffset1[ gy * 320 + gx ] = valueOffset1;
					borderScreenOffset2[ gy * 320 + gx ] = valueOffset2;
					borderScreenOffset3[ gy * 320 + gx ] = valueOffset3;
					borderScreenOffset4[ gy * 320 + gx ] = valueOffset4;
				}
			}
		}

		borderOffset++;
		for( gy = 0; gy < 200; gy++ )
		{
			for( gx = 0; gx < 320; gx++ )
			{
				long	pix = screendata[ gy * 320 + gx ];
				
				if (useLoadEffect)
				{
					if (gx < borderW || gx > 319 - borderW || gy < borderH || gy > 199 - borderH)
					{
						int		borderCount = gy * 320 + gx;
						int		seg = borderCount / borderSeg;
						int		borderIndex = (borderOffset + seg) % sizeOfLoadArray;
						char	borderBit = loadArray [ borderIndex ];

						if (borderBit == 0) 
							pix = borderColor0;
						else
							pix = borderColor1;

						borderCount++;
					}
					else
					{
						if (!useWideBorderScreen)
						{
							if (!useWideBorderScreenSmooth)
							{
								int	newOffset = borderScreenOffset[320 * gy + gx];
								pix = screendata[ newOffset ];
							}
							else
							{
								int offset = 320 * gy + gx;
								int newOffset1 = borderScreenOffset1[offset];
								int newOffset2 = borderScreenOffset2[offset];
								int newOffset3 = borderScreenOffset3[offset];
								int newOffset4 = borderScreenOffset4[offset];
								long pix1 = screendata[ newOffset1 ];
								long pix2 = screendata[ newOffset2 ];
								long pix3 = screendata[ newOffset3 ];
								long pix4 = screendata[ newOffset4 ];

								int r1 = ((unsigned char*)&pix1)[0];
								int g1 = ((unsigned char*)&pix1)[1];
								int b1 = ((unsigned char*)&pix1)[2];

								int r2 = ((unsigned char*)&pix2)[0];
								int g2 = ((unsigned char*)&pix2)[1];
								int b2 = ((unsigned char*)&pix2)[2];

								int r3 = ((unsigned char*)&pix3)[0];
								int g3 = ((unsigned char*)&pix3)[1];
								int b3 = ((unsigned char*)&pix3)[2];

								int r4 = ((unsigned char*)&pix4)[0];
								int g4 = ((unsigned char*)&pix4)[1];
								int b4 = ((unsigned char*)&pix4)[2];

								int		r = (r1 + r2 + r3 + r4) >> 2;
								int		g = (g1 + g2 + g3 + g4) >> 2;
								int		b = (b1 + b2 + b3 + b4) >> 2;

								pix = 0;

								((unsigned char*)&pix)[0] = r;
								((unsigned char*)&pix)[1] = g;
								((unsigned char*)&pix)[2] = b;
							}
						}
					}
				}
				
				screendata_1x1[ gy * 320 + gx ] = pix;
			}
		}

		int		bufW = screenW;
		int		bufH = screenH;

		if (screendata_trans == NULL)
		{
			screendata_trans = new long [320 * 200];

			FILE	*fp = fopen( "tvset.raw", "rb" );
			char	*pdat = (char*)screendata_trans;

			for( int i = 0; i < 320 * 200; i++ )
			{
				int		r = (unsigned char)fgetc(fp);
				int		g = (unsigned char)fgetc(fp);
				int		b = (unsigned char)fgetc(fp);
				int		t = 255 - (unsigned char)fgetc(fp);

				*pdat++ = b;
				*pdat++ = g;
				*pdat++ = r;
				*pdat++ = t;
			}
			
			fclose( fp );
		}

		if (!useExtendedBorder && useTransparent)
		{
			for( gy = 0; gy < 200; gy++ )
			{
				for( gx = 0; gx < 320; gx++ )
				{
					long	color1 = screendata_1x1[gy * 320 + gx];		
					long	color2 = screendata_trans[gy * 320 + gx];
					int		t = (((unsigned char*)&color2)[3]);

					int		r1 = ((unsigned char*)&color1)[0];
					int		g1 = ((unsigned char*)&color1)[1];			
					int		b1 = ((unsigned char*)&color1)[2];			

					int		r2 = ((unsigned char*)&color2)[0];
					int		g2 = ((unsigned char*)&color2)[1];			
					int		b2 = ((unsigned char*)&color2)[2];			

					int		r = r1 + ((r2 - r1) * t) / 255;
					int		g = g1 + ((g2 - g1) * t) / 255;
					int		b = b1 + ((b2 - b1) * t) / 255;

					if (r < 0) r = 0;
					if (r > 255) r = 255;
					if (g < 0) g = 0;
					if (g > 255) g = 255;
					if (b < 0) b = 0;
					if (b > 255) b = 255;

					long			color = 0;

					((char*)&color)[0] = r;
					((char*)&color)[1] = g;
					((char*)&color)[2] = b;

					screendata_1x1[gy * 320 + gx] = color;
				}
			}
		}

		if (useLowResTransform)
		{
			if (arrX == NULL || arrY == NULL)
			{
				arrX = aFunc1( 320 );
				arrY = aFunc1( 200 );
			}
			
			if (screendata_transform == NULL)
			{
				screendata_transform = new long [320 * 200];
			}

			for( gy = 0; gy < 200; gy++ )
			{
				for( gx = 0; gx < 320; gx++ )
				{
					int newGX = arrX[gx];
					int newGY = arrY[gy];

					if (useScrollMode)
					{
						newGX = gx;

						double	y1 = 199 * (0.1 - sin( gx / 319.0 * 3.14159 ) * 0.1);
						double	y2 = 199 * (0.9 + sin( gx / 319.0 * 3.14159 ) * 0.1);
						double	t = gy / 199.0;
						double	y = y1 + (y2 - y1) * t;

						newGY = (int)y;
						if (newGY < 0) newGY = 0;
						if (newGY > 199) newGY = 199;
					}

					screendata_transform[gy * 320 + gx] = screendata_1x1[newGY * 320 + newGX];
				}
			}

			for( gy = 0; gy < 200; gy++ )
			{
				for( gx = 0; gx < 320; gx++ )
				{
					screendata_1x1[gy * 320 + gx] = screendata_transform[gy * 320 + gx];
				}
			}
		}

		screendata_forCopy = (long*)screendata_smoth;

		
		if (screendata_ref == NULL)
		{
			screendata_ref = new long* [bufW * bufH];

			for( gy = 0; gy < bufH; gy++ )
			{
				for( gx = 0; gx < bufW; gx++ )
				{
					int	newGx = (gx * 319) / (bufW - 1);
					int newGy = (gy * 199) / (bufH - 1);

					screendata_ref[ gy * bufW + gx ] = &screendata_1x1[ newGy * 320 + newGx ];
				}
			}
		}

		if (useExtendedBorder)
		{
			DrawBorder( bufW, bufH );
		}
		else
		{

			long **pDatSrc = screendata_ref;
			long *pDat = screendata_forCopy;

			for( gy = 0; gy < bufH; gy++ )
			{
				for( gx = 0; gx < bufW; gx++ )
				{
					*pDat++ = **pDatSrc;
					pDatSrc++;
				}
			}
		}
	
		//если установлено соотвествующее разрешение
		//корректируем расположение буфера
		buf= (char*) ddSDesc1.lpSurface;
		BYTE* sourc=(BYTE*)screendata_smoth;
		
//		buf+=CurrentWindowPosition.x * 4;
//		buf+=CurrentWindowPosition.y * ddSDesc1.dwWidth*4;

		for( int i = 0; i < screenH-1; i++ )
		{
			{
			_asm 
			{
				pusha
				mov edi,buf
				mov esi,sourc
				mov ecx, [screenW]
				cld
			l1zz:
				lodsd
				stosd
				loop l1zz

				popa
			}
//			buf+=add_pitch;
			buf += screenW * 4;
			}
			sourc += screenW * 4;
		}


		pSurface->Unlock(ddSDesc1.lpSurface);
		okk=true;
	}

	return okk;
//------------------ oldCode ------------------------------

	if (CurrentWindowPosition.y<0) return 0;

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
	HRESULT result1 = pSurface->Lock(NULL, &ddSDesc, DDLOCK_SURFACEMEMORYPTR| DDLOCK_NOSYSLOCK,NULL);

	if (result1==DD_OK)
	{
		UINT hei=ddSDesc.dwHeight;

		char *buf= (char*) ddSDesc.lpSurface;
		int z=0;

		//исходные данные (буфер 320x200 точек) 1 байт на точку
		BYTE *sourc=scr.DoubleBuffer;

		int add_pitch=ddSDesc.lPitch;


		COLORREF screendata[320*200];

		int ScaleX=2,ScaleY=2;


		scr.ConvertDoubleBufferToTrueColor(screendata);

		for(int x=0; x<320; x++)
		for(int y=0; y<200; y++)
		{
			COLORREF clr=screendata[y*320+x];
			
			DWORD I=y*2*640+x*2;

			screendata_smoth[I]=clr;
			screendata_smoth[I+1]=clr;
			screendata_smoth[I+320*2]=clr;
			screendata_smoth[I+320*2+1]=clr;


			//screendata_smoth[y*640+x+1]=screendata[y*320+x];
		}

		//исходные данные - 4 байта на точку
		//sourc=(BYTE*) screendata;
		sourc=(BYTE*) screendata_smoth;

		//если установлено соотвествующее разрешение
		//корректируем расположение буфера
		if (DISPLAY_HORIZONTAL>= 640 && DISPLAY_VERTICAL>=400)
		{
			//центровка oX
			//buf+=(ddSDesc.dwWidth*4-320*4*ScaleX)/2;
			//buf+=WindowRect.left*4;

			//центровка oY
			//buf+=(ddSDesc.dwHeight-200*ScaleY)/2*add_pitch;
			//buf+=ddSDesc.dwWidth*WindowRect.top;


			//ВНИМАНИЕ!! верно только для разрешения не ниже 640x400

			//buf=(char*)screendata_smoth;
			
			
			//for(int i=0; i<400-1;i++)
			//{
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
			//}
			


		buf= (char*) ddSDesc.lpSurface;
		//sourc=(BYTE*)screendata;
		sourc=(BYTE*)screendata_smoth;
		

//		ScaleX=3;
//		ScaleY=3;
		//центровка oX
		//buf+=(ddSDesc.dwWidth*4-320*4*ScaleX)/2;
		
		buf+=CurrentWindowPosition.x * 4;

		//buf+=WindowRect.left*4;

		//центровка oY
		buf+=CurrentWindowPosition.y * ddSDesc.dwWidth*4;
		//buf+=(ddSDesc.dwHeight-200*ScaleY)/2*add_pitch;
		//buf+=ddSDesc.dwWidth*WindowRect.top;


			for(int i=0; i<400-1;i++)
			{
				{
				_asm 
				{
					pusha
					//lea edi,screendata_smoth
					mov edi,buf
					
				//l2z:
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
				sourc+=320*4 * 2;
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
	MessageBox(hwnd, s, "Mario", MB_OK);
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

//вызывается из метода Screen::Update()
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
		//SetCursor(NULL);	
	}
	else 
	{
		//SetCursor(LoadCursor(NULL,IDC_ARROW));
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

	//CurrentWindowPosition=point;
	
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
	
	return CDialog::Create(IDD, pParentWnd);
}

BOOL CSoldirOfMarioDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CREATESTRUCT *s;



	
	
	return CDialog::PreCreateWindow(cs);
}

void CSoldirOfMarioDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	CurrentWindowPosition.x=x;
	CurrentWindowPosition.y=y;
	
}
