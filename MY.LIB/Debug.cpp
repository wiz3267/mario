//Debug.cpp

#include "stdafx.h"

#include <conio.h>
#include <stdlib.h>
#include <iostream.h>
#include <string.h>

#include "screen.h"
#include "debug.h"
#include "total.h"
//#include "keyboard.h"

#define TRUE  1
#define FALSE 0

//#define DEBUGMESSAGES 1


//выводит сообщение
void Msg(char far *text,int color, int flag)
{
	int x,y,len,hei;

	len=strlen(text);

	//если сообщение полностью помещается на экране
	if (len<=40)
	{
		x=20-len/2;
       	hei=8*3;
		y=11;
	}
	//иначе оно займет несколько строк
	else
	{	x=0;
		len=40;
		hei=8*2+(len/40)*8;
		y=11;
	}

	scr.locate(x,y+1);

	int oldbkcolor=scr.bkcolor;
	int oldcolor=scr.color;;

	scr.color=15;
	scr.bkcolor=color;

	scr.rectangle(8*x, 8*y, len*8, hei, color );
	scr.border(8*x-1,8*y-1,len*8+2, hei+2, 15);
	
	scr.putText(text);
	
	int i=strlen(text)-1;
	
	while (text[i]==' ' && i)
	{
		scr.x-=8;
		i--;
	}
	scr.x+=8;

	//если нужно обновить экран
	if (flag==MSG_UPDATE)
	{
		scr.update();
	}

	scr.color=oldcolor;
	scr.bkcolor=oldbkcolor;

}


//выводит на экран сообщение и ждет нажатия клавиши для продолжения работы
void Debug(char far * str)
{
	//MessageBox(NULL,str,"Debug message!",MB_OK);
	Msg(str,0);
	Keyb.clear();
	Keyb.ReadScan();

/*	static int create=0;
	static CStdioFile log;
	log.Open("mario.log", log.modeWrite);
	log.SeekToEnd();
	log.WriteString(str);
	log.WriteString("\r\n");
	log.Close();*/
 }



//== 'fatal' - выдача сообщения об ошибке и завершение работы программы ===
void Fatal(char far * str)
{
	Msg(" ***** Fatal Error ***** ");

	Keyb.clear();
	Keyb.ReadScan();

	Msg(str);

	Keyb.clear();
	Keyb.ReadScan();

	MessageBox(NULL,str,"Fatal error!",MB_OK);
	exit(-1);
	
	//_asm int 3
	/*SCREEN sc;
	//asm int 3;
	//cout<<str<<"\n"<<(char) 7;
	//cout<<"*** PLEASE CALL TO (831-30) 5-29-87 Ewgeny, and tell my this message ***\n";

	scr.textmode();
	exit(-1);
	*/

}

/*
//================= 'Debug' - выдача сообщение об ошибке =================
void Debug(char far * text)
{
	Msg(text);
	extern KEYBOARD Keyb;
	if (Keyb.ReadScan() == KEY_Q) exit(1);
//	asm int 3;
}
*/
//====================== end of 'fatal' ===========================
