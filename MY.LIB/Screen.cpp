//Screen.cpp

#include "stdafx.h"

//********************************************************
//******* SCREEN.CPP - функции-члены класса SCREEN *******
//********************************************************
#include <fstream.h>
#include "screen.h"
#include "debug.h"
#include "rects.h"
#include "keyboard.h"
#include "timer.h"

extern	KEYBOARD	Keyb;
extern	TIMER		Timer;

//создаем предопределенный объект
SCREEN  scr;

static unsigned char Font8x8[2048];

void WizGetPaletteRegisters(DWORD startRegister, int count, PALETTEENTRY * values);
void WizSetPaletteRegister(DWORD startRegister, int size, PALETTEENTRY * value);
//гасит плавно экран
void SCREEN::DecrementPalette()
{
	PALETTEENTRY pal[256];
	WizGetPaletteRegisters(0,256, pal);
	for(int i=0; i<256;i++)
	{
		if (pal[i].peRed) pal[i].peRed--;
		if (pal[i].peGreen) pal[i].peGreen--;
		if (pal[i].peBlue) pal[i].peBlue--;
	}
	WizSetPaletteRegister(0,256, pal);
}

static COLORREF Palette[256];


//конструктор 
SCREEN::SCREEN(void)
{
	//загружаем шрифт
	for(int i=0; i<2048; i++) Font8x8[i]=i;

	ifstream ifl;
	ifl.open("graph\\font.fnt", ios::binary);
	ifl.read(Font8x8,2048);
	ifl.close();

	//инициализируем переменные
	x=0;		//координаты пера - левый верхний угол экрана
	y=0;

	color=15;	//цвет - ярко белый
	bkcolor=0;	//фон прозрачен

	clear();	//очистка экрана

	LoadPaletteFromFile("graph\\pallete.dat");
}

//деструктор
SCREEN::~SCREEN(void)
{
	#if DEBUGMESSAGES
	Debug("Run SCREEN destructor");
	#endif
}

//bitblt_part выполняет копирование части спрайта на экран
//x,y координаты вывода
//x_in,y_in координаты внутри спрайта
//Len,Hei длина спрайта
//FactLen, FactHei размеры выводимого блока спрайта
//Data адрес данных
//State как выводить спрайт
void SCREEN::bitblt_part(int x,int y,int x_in, int y_in,int Len, int Hei,
int FactLen,int FactHei, char far* Data, char State)
{
  //проверка параметров на допустимость
  if (x<0 || y<0 || x>320-FactLen || y>200-FactHei)
  {
    Debug("bitblt_part x,y is bad");
    return;
  }

  if (x_in<0 || y_in<0)
  {
    Debug("bitblt_part x_in,y_in <0");
    return;
  }

  if (x_in>=Len || y_in>=Hei)
  {
    Debug("bitblt_part x_in>=Len or y_in>=Hei");
    return;
  }

  if (FactLen>Len || FactHei>Hei)
  {
    Debug("bitblt_part FactLen>Len or FactHei>Hei");
    return;
  }

  if (FactLen<0 || FactHei<0)
  {
    Debug("bitblt_part FactLen<0 || FactHei<0");
    return;
  }

  if (State & FLIP_HORZ){
    if (x_in==0) x_in=Len-FactLen;
    else x_in=0;
  }

  int ONELINE=320;  //длина одной линии

  if (State & FLIP_VERT)
  {
//                State ^= FLIP_VERT;
    ONELINE=-320;
    if (y_in==0) y_in=Hei-FactHei;
    else y_in=0;

  }



  char  *Sour=Data;
  BYTE  *Dest=DoubleBuffer;

  Dest+=y*320+x;  //вычисляем адреса назначения
  Sour+=y_in*Len+x_in;  //вычисляем адрес внутри спрайта


  switch (State)
  {

	  //вывод обычного спрайта
		case 0:
		{
		  for(int i=0; i<FactHei; i++)
		  {
			  memcpy(Dest,Sour,FactLen);
			  Dest+=ONELINE;
			  Sour+=Len;
		  }

		  break;
		}

		//есть прозрачность
		case TRANSP:
		{
			for(int i=0; i<FactHei;i++)
			{
			
				for(int j=0; j<FactLen;j++)
				{
				
					if (Sour[j]) Dest[j]=Sour[j];
				}
				Dest+=ONELINE;
				Sour+=Len;
			}
			break;
		}

		//перевернут по горизонтали
		case FLIP_HORZ:
		{
			for(int i=0; i<FactHei;i++)
			{
			
				for(int j=0; j<FactLen;j++)
				{
				
					Dest[j]=Sour[FactLen-j-1];
				}
				Dest+=ONELINE;
				Sour+=Len;
			}

			break;
		}

		
		case TRANSP|FLIP_HORZ:
		{
			for(int i=0; i<FactHei;i++)
			{
			
				for(int j=0; j<FactLen;j++)
				{
				
					if (Sour[FactLen-j-1]) Dest[j]=Sour[FactLen-j-1];
				}
				Dest+=ONELINE;
				Sour+=Len;
			}

			break;
		}


  }

  /*
  switch (State)
  {
    case 0:

  asm {
    push ds
    push es

    lds si,Sour
    les di,Dest
  }
  loop1:
  asm {
    cld
    mov cx,FactLen
    rep movsb

    sub di,FactLen
    sub si,FactLen

    add di,ONELINE
    add si,Len

    dec FactHei
    jnz loop1

    pop es
    pop ds
  }
    break;

    //есть прозрачные пикселы
    case TRANSP:
    asm {
      push ds
      push es

      lds si,Sour
      les di,Dest

      mov cx,FactLen
      cld
    }
      l2:
    asm {
      lodsb
      or al,al
      jz l3
      mov es:[di],al
    }

      l3:
      asm { inc di
      dec cx
      jnz l2

      sub si,FactLen
      add si,Len

      sub di,FactLen
      add di,ONELINE

      mov cx,FactLen

      dec FactHei
      jnz l2

      pop es
      pop ds
    }
      break;

    //спрайт надо повернуть по горизонтали
    case FLIP_HORZ | TRANSP:
    asm {
      push ds
      push es

      lds si,Sour
      les di,Dest
      add di,FactLen
      dec di

      mov cx,FactLen

      mov dx,FactHei

      cld }
      l4:
    asm {
      lodsb

      or al,al
      jz lopsi
      mov es:[di],al }
    lopsi:
    asm {
      dec di

      dec cx
      jnz l4

      sub si,FactLen
      add si,Len

      add di,ONELINE
      add di,FactLen


      mov cx,FactLen

      dec dx
      jnz l4

      pop es
      pop ds
    }
      break;

    //спрайт надо повернуть по горизонтали
    case FLIP_HORZ:
    asm {
      push ds
      push es

      lds si,Sour
      les di,Dest
      add di,FactLen
      dec di

      mov cx,FactLen

      mov dx,FactHei

      cld }
      l6:
    asm {
      lodsb

      mov es:[di],al
      dec di

      dec cx
      jnz l6

      sub si,FactLen
      add si,Len

      add di,ONELINE
      add di,FactLen


      mov cx,FactLen

      dec dx
      jnz l6

      pop es
      pop ds
    }
      break;



  } //конец switch
  */
}
//========================= end of 'bitblt_part' ============================

//bitblt общая процедура вывода спрайта 
//xc,yc координаты вывода
//Len, Hei размеры спрайта
//Data данные
//State флаг вывода
void SCREEN::bitblt(int xc,int yc,int Len,int Hei, char * Data, char State)
{
	int ONELINE=320;
	//если спрайт полностью вышел за пределы экрана
	if ( xc<=-Len || yc<=-Hei || xc>=320 || yc>=200)
	{
		//Debug("'bitblt' - x or y out of side");
		//ничего не рисуем
		return;
	}

	//вычисление адреса вывода
	BYTE * vb=DoubleBuffer+xc+yc*320;

	//если спрайт полностью помещается на экране
	if ( xc>=0 && yc>=0 && xc<=320-Len && yc<=200-Hei)
	{

		if (State & FLIP_VERT) 
		{
			vb+=(Hei-1)*320; ONELINE=-320;
			State ^= FLIP_VERT;
		}

		switch (State)
		{
 	
			//вывод обычного спрайта.Нет прозрачности
			case 0:
			{
				_asm {
				  mov esi,Data
				  mov edi,vb
				  mov edx,Hei
				  cld
				  mov eax,ONELINE
			 l1:
				  mov ecx,Len
				  mov ebx,ecx
				  shr ecx,2

				  and ebx,3

				  or ebx,ebx
				  jz l1_cont
				  movsb
				  dec ebx

				  or ebx,ebx
				  jz l1_cont
				  movsb
				  dec ebx

				  or edx,edx
				  jz l1_cont
				  movsb
				  dec ebx

			 l1_cont:
				  rep movsd

				  add edi,eax
				  sub edi,Len
				  dec edx
				  jnz l1
				}
			break;
			}
			//-------------------------------------------------------------------
			//Вывод обычного спрайт есть прозрачные пикселы
			case TRANSP:
			{
				
				_asm {

				  mov esi,Data
				  mov edi,vb
				  mov ecx,Len
				  mov edx,Hei
				  cld 
				  l2:
				  lodsb
				  or al,al
				  jz l3
				  mov [edi],al
				  l3:
				  inc edi
				  dec ecx
				  jnz l2

				  add edi,ONELINE
				  mov ecx,Len
				  sub edi,ecx
				  dec edx
				  jnz l2
				  
				}
				break;

			} //end case

			case FLIP_HORZ:
			{
				for(int i=0; i<Hei; i++)
				{
					for(int j=0;j<Len;j++)
					{
						vb[j]=Data[Len-j-1];
					}

					Data+=Len;
					vb+=ONELINE;
				}
				break;
			}

			//перевернутый по горизонтали прозрачный
			case FLIP_HORZ | TRANSP:
			{
				for(int i=0; i<Hei; i++)
				{
					for(int j=0;j<Len;j++)
					{
						if (Data[Len-j-1]) vb[j]=Data[Len-j-1];
					}

					Data+=Len;
					vb+=ONELINE;
				}

				break;
			} //end case
			

		
		} //end  switch
		return;
	}//end if

	//иначе спрайт помещается на экране не полностью - необходимо выполнить
	//отсечение
	//если спрайт по оси y поместился полностью
	if (yc>=0 && yc<=200-Hei)
	{
		if (xc<0)
		bitblt_part(0,yc,
		0-xc, 0,  //координаты внутри спрайта
		Len,Hei,  //настоящая длина
		Len+xc, Hei,  //факт. длина
		Data, State);
		else
		bitblt_part(xc,yc,
		0, 0, //координаты внутри спрайта
		Len,Hei,  //настоящая длина
		320-xc, Hei,  //факт. длина
		Data, State);

		return;
	}//конец if



	//если спрайт по оси Ox поместился полностью
	if (xc>=0 && xc<=320-Len)
	{
		if (yc<0)
		bitblt_part(xc,0,
			0, 0-yc,  //координаты внутри спрайта
			Len,Hei,  //настоящая длина
			Len, Hei+yc,  //факт. длина
			Data, State);
						else
		bitblt_part(xc,yc,
			0, 0, //координаты внутри спрайта
			Len,Hei,  //настоящая длина
			Len, 200-yc,  //факт. длина
			Data, State);
		return;
	}

	//если спрайт в левом верхнем углу
	if (xc<0 && yc<0)
	{
		bitblt_part(0,0,
		-xc, -yc, //координаты внутри спрайта
		Len,Hei,  //настоящая длина
		Len+xc, Hei+yc, //факт. длина
		Data, State);
		return;
	}

	//если спрайт в левом нижнем углу
	if (xc<0 && yc>200-Hei)
	{
		bitblt_part(0,yc,
		-xc, 0, //координаты внутри спрайта
		Len,Hei,  //настоящая длина
		Len+xc, 200-yc, //факт. длина
		Data, State);
		return;
	}

	//если спрайт в правом нижнем углу
	if (xc>320-Len && yc>200-Hei)
	{
		bitblt_part(xc,yc,  //коорд. вывода на экран
		0, 0,   //координаты внутри спрайта
		Len,Hei,  //настоящая длина
		320-xc, 200-yc, //факт. длина
		Data, State);
		return;
	}

	//если спрайт в правом верхнем углу
	if (xc>320-Len && yc<0)
	{
		bitblt_part(xc,0, //коорд. вывода на экран
		0, -yc,   //координаты внутри спрайта
		Len,Hei,  //настоящая длина
		320-xc, Hei+yc, //факт. длина
		Data, State);
		return;
	}
}

//рисует рамку (x,y) (len,hei)
void SCREEN::border(int x,int y,int len,int hei, int color) 
{
	linedown(x,y,hei, color);
	linedown(x+len-1,y,hei,color);
	lineright(x,y,len,color);
	lineright(x,y+hei-1,len,color);
}

//выводит текст надпись по центру
//задается только y координата
void SCREEN::center(int y, char *str)
{
	scr.locateXY( (320-strlen(str)*8)/2, y);
	scr<<str;
}


//очистка экрана 
//color - цвет заполнения по умолчанию ноль
void SCREEN::clear(int color)
{
	BYTE * d=DoubleBuffer;
	_asm {
		mov edi,d
		cld
		mov eax,color
		mov ecx,320*200/4
		rep stosd
	}
}


//вод числа, возврат - уже переведенное число
//DigitCounter (0,10) - число цифр
unsigned long SCREEN::InputNumber(unsigned int DigitCounter)
{
	if (!DigitCounter || DigitCounter>10)
	{
		Debug("SCREEN::InputNumber - bad DigitCounter");
		return 0;
	}

	char *str=new char[DigitCounter+1];
	if (!str)
	{
		Debug("SCREEN::InputNumber - out of memory");
		return 0;
	}

	//вводим строку
	InputString(DigitCounter+1, str, ONLY_DIGIT);

	//переводим её в число

	unsigned long number=atol(str);

	delete str;

	return number;
}



//ввод строки в массив str, длиной len, начиная с текущих координат
//если flag==ONLY_DIGIT - тогда вводятся только цифры
void SCREEN::InputString(int len, char * str, int flag)
{

	Keyb.clear();

	int x=scr.x;
	int y=scr.y;

	int i=0;	// i - указывает на элемент массива, в который должен
				// быть осуществлен ввод
	while (1)
	{
		unsigned char s;
		if (Keyb.kbhit()) s=Keyb.getch();
		else s=1;

		if ( (Timer.GetTotalCounter() % 5) <2)
		{
		  scr.rectangle(x+i*8,y+6,8,2,scr.color);
		  scr.update();
		}
		else
		{
		  scr.rectangle( x+i*8,y+6,8,2,scr.bkcolor);
		  scr.update();
		}

		if (!s)
		{
		  Keyb.getch();
		  continue;
		}

		//интер - ввели
		if ( s==13 )
		{
			str[i]=0;

			//делаем клавишу <ENTER> ненажатой
			Keyb.Set(Keyb[KEY_ENTER], 0);

			break;
		}

		if ( s==8 && i)   //забой
		{
		  //удаляем курсор
		  scr.rectangle( x+i*8,y+6,8,2,scr.bkcolor);

		  str[i]=0;
		  i--;
		  locateXY(x+i*8,y);
		  putSymbol(' ');
		  update();
		}

		int yes=0;
		if (flag & ONLY_DIGIT)
		{
		  if (s>='0' && s<='9') yes=1;
		}
		else
		{
		  if (s>=' ') yes=1;
		}

		if ( yes && i<(len-1) )
		{
		  //удаляем курсор
		  scr.rectangle( x+i*8,y+6,8,2,scr.bkcolor);

		  locateXY(x+i*8,y);
		  putSymbol(s);
		  update();
		  str[i]=s;
		  i++;
		}

	} //end of while(1)
}


//установка позиции текстового курсора
//если координаты выходят за пределы экрана, позиция курсора не меняется
void SCREEN::locate(int x1,int y1)
{
	locateXY(x1*8, y1*8);
}

//установка позиции курсора
//если координаты выходят за пределы экрана, позиция курсора не меняется
void SCREEN::locateXY(int x1,int y1)
{
	//if (x1<0 || x1>319 || y1<0 || y1>199) return;
	x=x1;
	y=y1;
}

//рисование линии из (x1,y1) в (x2,y2)
void SCREEN::line(int x1,int y1,int x2,int y2, char color)
{
	//* * для рисования линии будем использовать алгоритм Брезенхема * *
	int i, dx, dy, nump,
	d, dinc1, dinc2,
	x, xinc1, xinc2,
	y, yinc1, yinc2;

	dx = abs(x2-x1);
	dy = abs(y2-y1);

	if (dx >= dy)
	{
		nump=dx+1;
		d=2*dy-dx;
		dinc1=dy<<1;
		dinc2=(dy-dx)<<1;
		xinc1=1;
		xinc2=1;
		yinc1=0;
		yinc2=1;
	}
	else
	{
		nump=dy+1;
		d=2*dx-dy;
		dinc1=dx<<1;
		dinc2=(dx-dy)<<1;
		xinc1=0;
		xinc2=1;
		yinc1=1;
		yinc2=1;
	}

	if (x1>x2)
	{
		xinc1*=-1;
		xinc2*=-1;
	}

	if (y1>y2)
	{
		yinc1*=-1;
		yinc2*=-1;
	}

	x=x1;
	y=y1;

	for(i=1; i<=nump; i++)
	{
		putpixel(x,y,color);
		if (d<0)
		{
			d+=dinc1;
			x+=xinc1;
			y+=yinc1;
		}
		else
		{
			d+=dinc2;
			x+=xinc2;
			y+=yinc2;
		}

	}
}

//рисует линию вниз от (x,y) высотой hei, цветом clr
void SCREEN::linedown(int x,int y,int hei, char clr)
{
	for(int i=y; i<y+hei; i++)
	{
		putpixel(x,i,clr);
	}
}

//рисует линию вправо от (x,y) длиной len, цветом clr
void SCREEN::lineright(int x,int y,int len, char clr)
{
	for(int i=x; i<x+len; i++)
	{
		putpixel(i,y,clr);
	}
}


//операция вывода << (строка)
SCREEN& SCREEN::operator<< (char *string)
{
	putText(string);
	return *this;
}

//операция вывода << (число)
SCREEN& SCREEN::operator<< (unsigned long n)
{
	putNumb(n);
	return *this;
}

//операция вывода << (число)
SCREEN& SCREEN::operator<< (unsigned n)
{
	putNumb(n);
	return *this;
}

//операция вывода << (число)
SCREEN& SCREEN::operator<< (int n)
{
	putNumb(n);
	return *this;
}

//операция вывода << (символ)
SCREEN& SCREEN::operator<< (char sym)
{
	putSymbol(sym);
	return *this;
}

//выдержка паузы (число тиков таймера N)
void SCREEN::pause(int N)
{
	Timer.Counter=0;
	while (Timer.Counter<N)
	{
		Sleep(1);
	}
}

//вывод пиксела в заданных координатах (x,y) цветом color
void SCREEN::putpixel(int x,int y,int color)
{
	if (x<0 || x>319 || y<0 || y>199) return;
	DoubleBuffer[x+y*320]=color;
}

//вывод пиксела в текущих координатах текущим цветом
void SCREEN::putpixel()
{
	putpixel(x,y,color);
}

//putSymbol вывод символа
// x,y - пиксельные координаты
// s - код символа
void SCREEN::putSymbol(int x,int y,unsigned char s)
{
	//Font.Show(x,y,s, (color % 7)*16  );
	//если за пределами экрана
	if (x<0 || x>312 || y<0 || y>192)
	{
		return;
	}

	//преобразуем кодировку
	char zz[2]={s,0};
	CharToOem(zz,zz);
	s=zz[0];

	char far *dest=(char far *) (DoubleBuffer+y*320+x);
	unsigned char *sour=Font8x8;


	sour+=s*8;

	BYTE symbol[8];
	for(int M=0; M<8; M++)
	{
		symbol[M]=sour[M];
		//if (M>4) symbol[M]=symbol[M]|(symbol[M]<<1);
	}

	sour=symbol;
	
	unsigned char color=this->color;
	unsigned char bkcolor=this->bkcolor;

	_asm 
	{
		mov esi,sour
		mov edi,dest
		mov edx,8
		mov ecx,8
		cld
	}

l3:
	_asm lodsb

l2:
	_asm test al,0x80
	_asm jz l1
	_asm mov ah,color
	_asm mov [edi],ah
	_asm jmp l5
//рисовать фон
l1:
	_asm mov ah,bkcolor
	_asm or ah,ah
	_asm jz l5
	_asm mov [edi],ah
l5:
	_asm 
	{
	inc edi
	shl al,1
	loop l2
	mov ecx,8
	add edi,320-8
	dec edx
	jnz l3
	}
}

//вариант 2
void SCREEN::putSymbol(BYTE s)
{
	putSymbol(x,y,s);
	x+=8;

	/*if (x>320-8)
	{
		x=0;
		y+=8;
	}*/
}

//вывод ASCIIZ-строки str
//если встречается символ перевода строки '\n' курсор переходит на новую строку
//и каретка возвращается ;)
void SCREEN::putText(char * str)
{
	for(int i=0; str[i]; i++)
	{
		if (str[i] == '\n')
		{
			x=0;
			y+=8;
			continue;
		}
		
		putSymbol(str[i]);
	}
}

//печатает число
void SCREEN::putNumb(unsigned long n)
{
	unsigned t,k=0;
	do {
		t=n % 10 + '0';
		k++;
		_asm push t
		n/=10;
	} while (n);

	for (UINT i=0;i<k;i++)
	{
		_asm pop t
		putSymbol(t);
	}
}


PALETTEENTRY WizGetPaletteRegister(DWORD Register);
void WizSetPaletteRegister(DWORD Register,int, PALETTEENTRY*);
void WizGetPaletteRegisters(DWORD startRegister, int count, PALETTEENTRY * values);
//устанавливает значение одного регистра палитры
//nRegister номер регистра 0..255
void SCREEN::SetColorRegister(unsigned char nRegister,char r,char g,char b)
{
	PALETTEENTRY value;
	value.peRed=r;
	value.peGreen=g;
	value.peBlue=b;
	value.peFlags=0;
	WizSetPaletteRegister(nRegister,1, &value);
	
}

//получает значение одного регистра палитры
//nRegister номер регистра палитры 0..255
void SCREEN::GetColorRegister(unsigned char nRegister,char &r,char &g,char &b)
{
	PALETTEENTRY value;
	WizGetPaletteRegisters(nRegister,1, &value);
	r=value.peRed;
	g=value.peGreen;
	b=value.peBlue;

}

//печатает число
void SCREEN::putNumb(unsigned long n,char n1)
{
	const int k=15;
	char t[k];
	if (n1>6) n1=7;

	for (int i=n1-1;i>=0;i--)
	{
		t[i]=char( n % 10 + 48);
		n/=10;
	}

	for (i=0;i<n1;i++)
	{
		putSymbol(t[i]);
	}
}

//вывод прямоугольника
void SCREEN::rectangle(MYRECT &rt, int color)
{
	rectangle(rt.Left, rt.Top, rt.Right-rt.Left+1, rt.Bottom-rt.Top+1,color);
}

//вывод прямоугольника
void SCREEN::rectangle(int x,int y,int len,int hei, int color)
{
	int x1=x+len-1, y1=y+hei-1;
	if (x1<0 || y1<0 || x>319 || y>199) return;

	if (y<0 || x<0 || x1>319 || y1>199)
	{
		MYRECT rt1(0,0,319,199),
		rt2(x,y,x+len-1,y+hei-1),
		rt3;

		if (DetermineSystem(rt1,rt2,rt3))
		rectangle(rt3,color);
		//Debug("SCREEN::rectangle - parametrs erorr!");
		return;
	}

	unsigned char far * vb=DoubleBuffer;
	unsigned addr=320*y+x;
	_asm {
		cld
		mov edi,vb
		add edi,addr
		mov al,byte ptr color
		mov ah,al
		mov bx,ax
		shl eax,16  //shl eax,16
		mov ax,bx

		mov ebx,len
		and ebx,3

		mov edx,len
		shr edx,1
		shr edx,1
		cld
	}
	m:
	_asm{ 
		mov ecx,edx
		rep stosd
		mov ecx,ebx
		rep stosb
		add edi,320
		sub edi,len
		dec hei
		jnz m
	}
}

void RedrawMarioWindow();

//обновление экрана (теневой буфер копируется непосредственно в видео память
//через функции DirectX)
void SCREEN::update(void)
{
	RedrawMarioWindow();
	return;
}

SCREEN& _setlocate(SCREEN&ob, int coor)
{
	ob.y=(coor & 0xff)*8;
	ob.x=(coor>>8)*8;
	return ob;
}

SCREEN& _setcolor(SCREEN&ob, int _b)
{
	ob.color=_b;
	return ob;
}

MANIPMY manip(0,0);

MANIPMY& setcolor(int color)
{
	manip.fun=_setcolor;
	manip.ag=color;
	return manip;
}

MANIPMY& cur(int x,int y)
{
	manip.fun=_setlocate;
	manip.ag=(x<<8) + y;
	return manip;
}

//преобразует теневой буффер в TrueColor - buffer
void SCREEN::ConvertDoubleBufferToTrueColor(COLORREF *TrueColor)
{
	for(int i=0; i<320*200; i++)
	{
		TrueColor[i]=Palette[DoubleBuffer[i]];
	}
}

void SCREEN::SaveScreen()
{
	memcpy(SavedDoubleBuffer, DoubleBuffer,320*200);
}

//загружает палитру из файла
void SCREEN::LoadPaletteFromFile(char *fname)
{
	//загружаем палитру
	ifstream ifl;
	ifl.open(fname,ios::binary);

	//!!! СДЕЛАТЬ ПРОВЕРКУ НА ОТСУТСТВИЕ ФАЙЛА !!!

	for(int i=0; i<256; i++)  
	{
		BYTE r,g,b;
		ifl.read(&b,1);
		ifl.read(&g,1);
		ifl.read(&r,1);
		r<<=2;
		g<<=2;
		b<<=2;
		Palette[i]=RGB(r,g,b);
		SetColorRegister(i,r,g,b);
		
	}
	ifl.close();

}

//записывает текущую палитру в файл
void SCREEN::SavePaletteToFile(char *fname)
{
}