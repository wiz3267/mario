//Keyboard.h
#ifndef __KEYBOARD_H
#define __KEYBOARD_H


//=============определени€: SCAN-коды клавиш=============

//--------------клавиши с латинискими буквами------------
#define KEY_TAB 0x0f

#define	KEY_A	0x1e
#define	KEY_B	0x30
#define	KEY_C	0x2e
#define	KEY_D	0x20
#define	KEY_E	0x12
#define	KEY_F	0x21
#define	KEY_G	0x22
#define	KEY_H	0x23
#define	KEY_I	0x17
#define	KEY_J	0x24
#define	KEY_K	0x25
#define	KEY_L	0x26
#define	KEY_M	0x32
#define	KEY_N	0x31
#define	KEY_O	0x18
#define	KEY_P	0x19
#define	KEY_Q	0x10
#define	KEY_R	0x13
#define	KEY_S	0x1f
#define	KEY_T	0x14
#define	KEY_U	0x16
#define	KEY_V	0x2f
#define	KEY_W	0x11
#define	KEY_X	0x2d
#define	KEY_Y	0x15
#define	KEY_Z	0x2c

//--------------------клавиши с цифрами--------------
#define	KEY_0	0x0b
#define	KEY_1	0x02
#define	KEY_2	0x03
#define	KEY_3	0x04
#define	KEY_4	0x05
#define	KEY_5	0x06
#define	KEY_6	0x07
#define	KEY_7	0x08
#define	KEY_8	0x09
#define	KEY_9	0x0a

//-----------------управл€ющие клавиши----------------
#define	KEY_CAPSLOCK	0x3a
#define	KEY_LEFTSHIFT	0x2a
#define	KEY_RIGHTSHIFT 	0x36
#define	KEY_LEFTCTRL	0x1d
#define	KEY_LEFTALT	0x38

#define	KEY_SCROLLLOCK	0x46

#define	KEY_ENTER       0x1c
#define	KEY_BACKSPACE	0x0e

#define	KEY_SPACE	0x39    //пробел

#define	KEY_ESC		0x01
#define	KEY_LQUOTE	0x29


//-------------цифровые клавиши----------------
#define	KEY_PAD0	0x52
#define	KEY_PAD1	0x4f
#define	KEY_PAD2	0x50
#define	KEY_PAD3	0x51
#define	KEY_PAD4	0x4b
#define	KEY_PAD5	0x4c
#define	KEY_PAD6	0x4d
#define	KEY_PAD7	0x47
#define	KEY_PAD8	0x48
#define	KEY_PAD9	0x49
#define	KEY_PADDEL	0x53
#define KEY_PADMUL	0x37
#define KEY_PADSUB	0x4a
#define KEY_PADADD	0x4e

//-----------функциональные клавиши------------
#define	KEY_F1	0x3b
#define	KEY_F2	0x3c
#define	KEY_F3	0x3d
#define	KEY_F4	0x3e
#define	KEY_F5	0x3f
#define	KEY_F6	0x40
#define	KEY_F7	0x41
#define	KEY_F8	0x42
#define	KEY_F9	0x43
#define	KEY_F10	0x44
#define	KEY_F11	0x57
#define	KEY_F12	0x58

#define	KEY_ESC		0x01
#define	KEY_LQUOTE	0x29

//----------мои собственные определени€-------------
#define KEY_UP		0x60
#define	KEY_DOWN	0x61
#define	KEY_LEFT	0x62
#define	KEY_RIGHT	0x63
#define	KEY_INSERT	0x64
#define	KEY_DELETE	0x65
#define	KEY_HOME	0x66
#define	KEY_END		0x67
#define	KEY_PAGEUP	0x68
#define	KEY_PAGEDOWN	0x69

#define KEY_RIGHTALT	0x6a
#define KEY_RIGHTCTRL	0x6b
#define KEY_PRINTSCREEN 0x6c
#define KEY_PAUSE	0x6d

#define KEY_PADENTER	0x6e
#define KEY_PADDIV	0x6f
//================ конец SCAN-кодов клавиш ====================


//=============== –ежимы ввода =============

//не вызывать старый обработчик прерывани€
#define KEYBOARD_NOOLDINTERRUPT	   0x00
//запуск старого обработчика прервани€
#define KEYBOARD_YESOLDINTERRUPT   0x01


class KEYBOARD
{
//закрытые члены
//private:
private:
	static int CountObject;		//число созданных объектов
								//вектор прерывани€
	unsigned char ExtendedKey;	//была ли нажата расширенна€ клавиша
	char NextKey;
	int InputMode;			//режим ввода
	char Keys[256];			//массив хран€щий информацию
							//о нажати€х клавиш

	int  Check(unsigned char  key);	//проверка, нажата ли клавиша
//открытые члены
public:
	bool kbhit();
	char getch();
	static char * KEY[];
	void clear();			//очистка буфера нажатий
	KEYBOARD ();			//конструктор
	~KEYBOARD();			//деструктор
	char operator[] (char k) { return Keys[k]; }
	void operator^  (char k) { Keys[k]=0; }//просьба клавишу отпустить
							//и нажать снова

	int AnyKey();			// возврат 1 - если нажата any key
					//         0 - если ничего не нажато

	//обработчики нажати€ клавиш
	void OnWM_KEYDOWN(int nVirtKey);
	void OnWM_KEYUP(int nVirtKey);

	char ReadScan();			//считывание Scan-кода клавиши
    void Set(char,char);
	char WaitKey();	//ждеат нажати€ любой клавиши
};

extern KEYBOARD Keyb;

#endif