//Screen.h
#ifndef __SCREEN_H
#define __SCREEN_H

#include "rects.h"

/*
	Класс SCREEN предназначен для вывода информации во внутренний буфер,
копию экранного буфера. Когда кадр сформирован, вызывается функция update(),
и изображения из внутреннего буфера копируется в видеопамять (на экран)
	Примечание: такие понятия, как 'вывод на экран', 'очистка экрана'
относятся не к физической VRAM, а к теневому экрану (DoubleBuffer, дублирующиц буфер)
	Чтобы информация появилась на экране необходимо вызвать функцию update() 
	Настоящая реализация поддерживает размер экрана 320x200
*/
class SCREEN {

// ********************** ДАННЫЕ-ЧЛЕНЫ ******************************
public:

	BYTE	DoubleBuffer[320*200];	//теневой экран

public:

	char	bkcolor;		//цвет заднего фона (при выводе текста)
	char	color;			//цвет рисования
	int		x,y;			//координаты курсора

	//хранит копию экрана 
	BYTE	SavedDoubleBuffer[320*200]; 

// ********************** ФУНКЦИИ-ЧЛЕНЫ *************************
public:
	void ConvertDoubleBufferToTrueColor(COLORREF * TrueColorBuffer);
	
	//значение State для bitblt
	enum {
		FLIP_HORZ=0x01,	//перевернуть спрайт по горизонтали
		FLIP_VERT=0x02,	//перевернуть спрайт по вертикали
		TRANSP=0x04	//есть прозрачные пикселы
	};

	enum {
		ONLY_DIGIT=0x01	//фунция InputString будет вводить только цифры
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

	void LoadPaletteFromFile(char *fname);	//восстанавливает палитру из файла
	void SavePaletteToFile(char *fname);	//записывает текущую палитру в файл

	//получить массив цветовых регистров
	//void GetColorRegisters(int startReg, int count, RGB * values);
	
	//установить массив цветовых регистров
	//void SetColorRegisters(int startReg, int count, RGB * values);

	//получение одного цветового регистра
	void GetColorRegister(unsigned char nReg,char&r,char&g,char&b);

	//установка одного цветового регистра
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
	void setbkcolor(char c){bkcolor=c;};	//установка цвета вывода
	void setcolor(char c){color=c;};	//установка цвета вывода
	
	void Set320x240Mode();			//установить режим 320*240, 256 цветов
	void update(void);			//обновление экрана
	void update(RECT);			//обновление экрана
//	void wait(void);			//ждет обратного хода луча
	void SaveScreen();			//сохраняет экран во внутреннем буфере

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
	//возможные перечеслиния размеров фонта
	enum {
		FONT8x8,
		FONT8x14,
		FONT8x16
	};

	char * FontAddres;		//адрес фонта
	char SymHigh;			//высота одного символа

public:
	FONT(int size=FONT8x8); //конструктор size - размер фонта
	~FONT();  	//деструктор

	//показать на экране символ с дополнительным цветом color
void	Show(int x,int y, int symbol, char color);
};

  */


#endif