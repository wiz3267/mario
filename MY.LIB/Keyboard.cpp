//Keyboard.cpp

//*********************************************************************
//**** 'KEYBOARD.CPP' - ������ ������ KEYBOARD ******************
//*********************************************************************

#include "stdafx.h"

//enum {FALSE,TRUE };

//��� �����
//#include "process.h"
#include "debug.h"
#include "keyboard.h"
#include "screen.h"



//==========����������� (�� ���� � �������� ������) ����������==============
//����� �������� ��������
int KEYBOARD::CountObject=0;

static const TableSize=26+10+12+4+4+3+10+4+2+2;
char TranslateTable[TableSize][2]=
{

	//��������� ������� (26)
	{KEY_A, 'A'},
	{KEY_B, 'B'},
	{KEY_C, 'C'},
	{KEY_D, 'D'},
	{KEY_E, 'E'},
	{KEY_F, 'F'},
	{KEY_G, 'G'},
	{KEY_H, 'H'},
	{KEY_I, 'I'},
	{KEY_J, 'J'},
	{KEY_K, 'K'},
	{KEY_L, 'L'},
	{KEY_M, 'M'},
	{KEY_N, 'N'},
	{KEY_O, 'O'},
	{KEY_P, 'P'},
	{KEY_Q, 'Q'},
	{KEY_R, 'R'},
	{KEY_S, 'S'},
	{KEY_T, 'T'},
	{KEY_U, 'U'},
	{KEY_V, 'V'},
	{KEY_W, 'W'},
	{KEY_X, 'X'},
	{KEY_Y, 'Y'},
	{KEY_Z, 'Z'},

	//�������� ������� (10)
	{KEY_0, '0'},
	{KEY_1, '1'},
	{KEY_2, '2'},
	{KEY_3, '3'},
	{KEY_4, '4'},
	{KEY_5, '5'},
	{KEY_6, '6'},
	{KEY_7, '7'},
	{KEY_8, '8'},
	{KEY_9, '9'},

	//�������������� ������� (12)
	{KEY_F1, VK_F1},
	{KEY_F2, VK_F2},
	{KEY_F3, VK_F3},
	{KEY_F4, VK_F4},
	{KEY_F5, VK_F5},
	{KEY_F6, VK_F6},
	{KEY_F7, VK_F7},
	{KEY_F8, VK_F8},
	{KEY_F9, VK_F9},
	{KEY_F10, VK_F10},
	{KEY_F11, VK_F11},
	{KEY_F12, VK_F12},

	//������� (4)
	{KEY_LEFT,	VK_LEFT},
	{KEY_RIGHT, VK_RIGHT},
	{KEY_DOWN,	VK_DOWN},
	{KEY_UP,	VK_UP},
	
	{KEY_ESC,		VK_ESCAPE},
	{KEY_SPACE,		VK_SPACE},
	{KEY_ENTER,		VK_RETURN},
	{KEY_CAPSLOCK,	VK_CAPITAL},

	{KEY_TAB,		VK_TAB},
	{KEY_LEFTSHIFT, VK_SHIFT},	//!!!!
	{KEY_LEFTCTRL,	VK_CONTROL},

	//������� � ������ ����� ���������� (10)
	{KEY_PAD0, VK_NUMPAD0},
	{KEY_PAD1, VK_NUMPAD1},
	{KEY_PAD2, VK_NUMPAD2},
	{KEY_PAD3, VK_NUMPAD3},
	{KEY_PAD4, VK_NUMPAD4},
	{KEY_PAD5, VK_NUMPAD5},
	{KEY_PAD6, VK_NUMPAD6},
	{KEY_PAD7, VK_NUMPAD7},
	{KEY_PAD8, VK_NUMPAD8},
	{KEY_PAD9, VK_NUMPAD9},

	{KEY_PADADD, VK_ADD},
	{KEY_PADDIV, VK_DIVIDE},
	{KEY_PADMUL, VK_MULTIPLY},
	{KEY_PADSUB, VK_SUBTRACT},
	
	{KEY_DELETE, VK_DELETE},
	{KEY_INSERT, VK_INSERT},

	{KEY_PAGEUP,	33},
	{KEY_PAGEDOWN,	34}
	
};

//����� ����������
struct KEYBOARD_BUFFER
{
	enum {len=20};
	int buffer[len];
	int pos;
	KEYBOARD_BUFFER() : pos(0) {};
	void Put(int sym)
	{
		static DWORD time;
		
		//��� ��������� �������� (������-�� ��� ���� ���� �������)
		if (GetTickCount() - time <10) 
		{
			time=GetTickCount();
			return;
		}
		time=GetTickCount();

		if (pos!=len)
		{
			buffer[pos]=sym;
			pos++;
		}
	}

	int Get()
	{
		if (pos!=0)
		{
			pos--;
			return buffer[pos];
		}
		else return ' ';
	}

	bool kbhit()
	{
		if (pos==0) return false;
		else return true;
	}


} KeyBuffer;


//��������� ������� �������
void KEYBOARD::OnWM_KEYDOWN(int nVirtKey)
{
	for(int i=0; i<TableSize; i++)
		if (TranslateTable[i][1]==nVirtKey)
		{
			if (Keys[TranslateTable[i][0]]==0)
			Keys[TranslateTable[i][0]]=1;
		}

	KeyBuffer.Put(nVirtKey);

}

char KEYBOARD::getch()
{
	return KeyBuffer.Get();
}

bool KEYBOARD::kbhit()
{
	return KeyBuffer.kbhit();
}

//��������� ���������� �������
void KEYBOARD::OnWM_KEYUP(int nVirtKey)
{
	for(int i=0; i<TableSize; i++)
		if (TranslateTable[i][1]==nVirtKey)
		{
			Keys[TranslateTable[i][0]]=0;
		}
}



char * KEYBOARD::KEY[]={
// ���� 00-0F
"WHAT?","ESC", "NUM1", "NUM2", "NUM3", "NUM4", "NUM5", "NUM6", "NUM7",
"NUM8", "NUM9", "NUM0", "DASH",
"EQUAL", "BACK SPACE","TAB",
// ���� 10-1F
"Q","W","E","R","T","Y","U","I","O","P","{","}","ENTER","LEFT CTRL", "A","S",
// ���� 20-2F
"D","F","G","H","J","K","L","SEMICOLON","RQUOTE", "LQUTE",
"LEFT SHIFT", "BACK SLASH", "Z","X","C", "V",
// ���� 30-3F
"B","N","M", "COMMA", "PERIOD", "SLASH", "RIGHT SHIFT", "PADMUL", "LEFT ALT", "SPACE",
"CAPS LOCK", "F1", "F2", "F3", "F4", "F5",
// ���� 40-4F
"F6","F7","F8","F9","F10","NUM LOCK", "SCROLL LOCK", "PAD7", "PAD8", "PAD9",
"PADSUB", "PAD4", "PAD5", "PAD6", "PADADD", "PAD1",
// ���� 50-5F
"PAD2", "PAD3", "PAD0", "PADDEL","0x54", "0x55", "0x56", "F11", "F12",
"0x59", "0x5a", "0x5b", "0x5c", "0x5d", "0x5e", "0x5f",

// ���� 60-6F	//��� �����������
"UP", "DOWN", "LEFT", "RIGHT", "INSERT", "DELETE", "HOME", "END","PAGE UP","PAGE DOWN",
"RIGHT ALT", "RIGHT CTRL", "PRINT SCREEN", "PAUSE", "PADENTER", "PADDIV"
};

//-------------'Check' - ��������, ������ �� ������� -------------------
// key - ����-��� ����������� �������
// �������:
//   1 TRUE  - ������
//   0 FALSE - �� ������
int KEYBOARD::Check(unsigned char key)
{
	return Keys[key];
}
//------------------------------------------------------------------------

// ������� 1 - ���� ������ ����� �������
//         0 - ���� ������ �� ������
int KEYBOARD::AnyKey()		
{
	for(int i=1; i<127; i++)
	{
		if (Keyb[i]) return 1;
	}
	return 0;
}


//------------'ReadScan' - ��������� ����-��� ---------------------
char KEYBOARD::ReadScan()
{
	//������� ����� ����������
	clear();

	for(int i=0;;i++, i&=127)
		if (Check(i)) break;

	while (Check(i));
	return i;
}

//============== 'Clear' - ������� ������ ������� ���������� ===========
//��� ������� ������� �������� ����� "������ �����",
//��� ��� �������� �������� ���������� ������, � ������ ��� ����� ���������
//� ���� �������
void KEYBOARD::clear(void)
{
	for (int i=0; i<256; i++)
	{
		Keys[i]=0;
	}
	KeyBuffer.pos=0;
}

//====================== ����������� ===================
KEYBOARD::KEYBOARD(void)
{
	#if DEBUGMESSAGES
		Debug("Run KEYBOARD constructor");
	#endif

	//������ ���� ���������� ����� ������� ������ ���� ���
	if (CountObject!=0)
	{
		Fatal("KEYBOARD-object already exist!");
		return;
	}

	//����������� ����� �������� ��������
	CountObject++;

	//������� ����� ������� ������ ����������
	clear();

	//�� ����������� ������� ���� �� ��������...
	ExtendedKey=FALSE;

	//������������� ����� ����� - ��� ������� ����������� ����������
	InputMode = KEYBOARD_NOOLDINTERRUPT;

	//��������� ����� ���������� �������.
	//�� ����������� � ����������� ����������,
	//��� ��� ��� �� ���������� ��������� �� ������ this
}

//================= '~KEYBOARD' ���������� ������� ====================
KEYBOARD::~KEYBOARD(void)
{
	#if DEBUGMESSAGES
		Debug("Run KEYBOARD - destructor");
	#endif
}


//��������� ��������� �������
//0 - ��������
//1 - ������
//2 - �������������(��� ��������,
//��� ���������� WM_KEYDOWN �� ����� �������� ��������)

void KEYBOARD::Set(char keycode,char what)
{
	Keys[keycode & 0x7f]=what;
}

char KEYBOARD::WaitKey()	//����� ������� ����� �������
{
	clear();
	return ReadScan();
}


