//Screen.h
#ifndef __SCREEN_H
#define __SCREEN_H

#include "rects.h"

/*
	����� SCREEN ������������ ��� ������ ���������� �� ���������� �����,
����� ��������� ������. ����� ���� �����������, ���������� ������� update(),
� ����������� �� ����������� ������ ���������� � ����������� (�� �����)
	����������: ����� �������, ��� '����� �� �����', '������� ������'
��������� �� � ���������� VRAM, � � �������� ������ (DoubleBuffer, ����������� �����)
	����� ���������� ��������� �� ������ ���������� ������� ������� update() 
	��������� ���������� ������������ ������ ������ 320x200
*/
class SCREEN {

// ********************** ������-����� ******************************
public:

	BYTE	DoubleBuffer[320*200];	//������� �����

public:

	char	bkcolor;		//���� ������� ���� (��� ������ ������)
	char	color;			//���� ���������
	int		x,y;			//���������� �������

	//������ ����� ������ 
	BYTE	SavedDoubleBuffer[320*200]; 

// ********************** �������-����� *************************
public:
	void ConvertDoubleBufferToTrueColor(COLORREF * TrueColorBuffer);
	
	//�������� State ��� bitblt
	enum {
		FLIP_HORZ=0x01,	//����������� ������ �� �����������
		FLIP_VERT=0x02,	//����������� ������ �� ���������
		TRANSP=0x04	//���� ���������� �������
	};

	enum {
		ONLY_DIGIT=0x01	//������ InputString ����� ������� ������ �����
	};

	void bitblt(int X,int Y,int Len,int Hei, char far* Data, char State);
	void bitblt_part(int x,int y,int x_in, int y_in,int Len, int Hei,
					int FactLen,int FactHei, char far* Data, char State);
	void border(int x,int y,int len,int hei, int color);	
	void center(int y, char far*);	
	void clear(int=0);				
	void CreatePalette();			
	void DecrementPalette();		
	void IncrementPalette();		

	void LoadPaletteFromFile(char *fname);	//��������������� ������� �� �����
	void SavePaletteToFile(char *fname);	//���������� ������� ������� � ����

	//�������� ������ �������� ���������
	//void GetColorRegisters(int startReg, int count, RGB * values);
	
	//���������� ������ �������� ���������
	//void SetColorRegisters(int startReg, int count, RGB * values);

	//��������� ������ ��������� ��������
	void GetColorRegister(unsigned char nReg,char&r,char&g,char&b);

	//��������� ������ ��������� ��������
	void SetColorRegister(unsigned char nReg,char r,char g,char b);

	
	unsigned long InputNumber(unsigned int DigitCounter);	
	void InputString(int len, char far * str,int flag=0);
	void locate(int x,int y);	
	void locateXY(int x,int y);	
    void line(int x1,int y1,int x2,int y2, char color);	
	void lineright(int x,int y,int len, char color);	
	void linedown(int x,int y,int hei, char color);		

	SCREEN& operator << (char*);
	SCREEN& operator << (DWORD);
	SCREEN& operator << (unsigned);
	SCREEN& operator << (int);
	SCREEN& operator << (char);
	SCREEN& operator<< (SCREEN& (*_f)(SCREEN&))
	{
		return (*_f)(*this);
	}

	void pause(int n);
	void putpixel(int x,int y,int color); 
	void putpixel();					 

	void putSymbol(BYTE s);				
	void putSymbol(int x,int y, unsigned char s);	
	void putText(char far *);		
	void putNumb(unsigned long num);	
	void putNumb(unsigned long num,char width);	
	void rectangle(int x,int y,int len,int hei,int color);
	void rectangle(MYRECT &rt,int color);
	void setbkcolor(char c){bkcolor=c;};	//��������� ����� ������
	void setcolor(char c){color=c;};	//��������� ����� ������
	
	void Set320x240Mode();			//���������� ����� 320*240, 256 ������
	void update(void);			//���������� ������
	void update(RECT);			//���������� ������
//	void wait(void);			//���� ��������� ���� ����
	void SaveScreen();			//��������� ����� �� ���������� ������

	SCREEN(void);				
	~SCREEN(void);				

};
//================== end of class 'SCREEN' ==============================

inline        SCREEN& endl(SCREEN& ob) { return ob; }

class MANIPMY {
public:
	SCREEN& (*fun) (SCREEN& , int);
	int ag;

public:
	MANIPMY ( SCREEN& (*_f)(SCREEN&, int) , int _a)
	{
		fun=_f;
		ag=_a;
	}

        friend SCREEN& operator<< (SCREEN& obj, MANIPMY& _f)
        {
			(_f.fun) (obj, _f.ag);
			return obj;
		}
};

MANIPMY& setcolor(int);
MANIPMY& cur(int,int);


//extern SCREEN scr;


/*
class FONT
{
	//��������� ������������ �������� �����
	enum {
		FONT8x8,
		FONT8x14,
		FONT8x16
	};

	char * FontAddres;		//����� �����
	char SymHigh;			//������ ������ �������

public:
	FONT(int size=FONT8x8); //����������� size - ������ �����
	~FONT();  	//����������

	//�������� �� ������ ������ � �������������� ������ color
void	Show(int x,int y, int symbol, char color);
};

  */


#endif