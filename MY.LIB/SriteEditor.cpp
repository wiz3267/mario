//SpriteEditor.h
#include "stdafx.h"

#include "SpriteEditor.h"
#include "Sprite.h"
#include "Total.h"
#include <fstream.h>

/*SPRITEEDITOR::SPRITEEDITOR
{
}

*/
/*SPRITEEDITOR::~SPRITEEDITOR
{
}*/

static int SpriteIndex=0;
char * filename="graph\\levelbox.dat";

//редактор спрайтов
int SPRITEEDITOR::Editor(SPRITE * sprZZZ, int current)
{
	/*отображать название файла
	при встваке убрать надпись вставлено
	кнопку очистки поля рисования
	выбор файла со спрайтами
	при изменении спрашивать что изменилось
	не отображется плитка спрайтов
	*/

	//размеры увеличения
	int onelen=6;
	int onehei=6;
	
	bool Reload=true;

	//текущий цвет
	BYTE CurrentColor=15;
	
	//высота полоски цветов
	int heiclr=16;

	SPRITE CurSprite(&scr);
	SPRITE::IMAGE img;
	img.Hei=24;
	img.Len=24;
	img.Attribute=0;
	img.ID=1;
	CurSprite.Create(img);

	SPRITE SpriteCopy(&scr);	//сюда поместиться спрайт для копирования и вставки	
	const int IDSPRCOPY=1;
	SPRITE::IMAGE imgsprcopy;
	imgsprcopy.Len=24;
	imgsprcopy.Hei=24;
	imgsprcopy.Attribute=0;
	imgsprcopy.ID=IDSPRCOPY;
	SpriteCopy.Create(imgsprcopy); //создаем спрайт

	try
	{

	bool Modify=false;	//было ли внесено изменения в файл
	while(1)
	{
		scr.clear();

		if (Keyb[KEY_F7])
		{
			if (Modify)
			{
					Msg("Спрайт изменен! <C> для продолжения.");
					if (Keyb.ReadScan() != KEY_C)
					{
						continue;
					}
			}

			filename="graph\\sprite.dat";
			Keyb^KEY_PAGEUP;
			Reload=true;
			Modify=false;
		}

		if (Keyb[KEY_F8])
		{
			if (Modify)
			{
					Msg("Спрайт изменен! <C> для продолжения.");
					if (Keyb.ReadScan() != KEY_C)
					{
						continue;
					}
			}

			filename="graph\\levelbox.dat";
			Reload=true;
		}

		if (Keyb[KEY_F9])
		{
			if (Modify)
			{
					Msg("Спрайт изменен! <C> для продолжения.");
					if (Keyb.ReadScan() != KEY_C)
					{
						continue;
					}
			}

			filename="graph\\fontbig.dat";
			Reload=true;
		}


		if (Keyb[KEY_F1])
		{
			char *help=
			"F1 помощь\n"
			"F2 сохранить\n"
			"F7 выбор файла 'sprite.dat'\n"
			"F8 выбор файла 'levelbox.dat'\n"
			"F9 выбор файла 'fontbig.dat'\n"
			"<ESC> выход из редактора\n"
			"<CTRL>+<C>,F5 запомнить\n"
			"<CTRL>+<V> вставить\n"
			"<LEFT><RIGHT> изменить текущий цвет\n"
			"<PAGEUP><PAGEDOWN> изменить редактируемый спрайт\n"
			"<SPACE><LBUTTONMOUSE> рисовать точку\n"
			"<DELETE> удалить точку\n"
			"<ENTER><RBUTTONMOUSE> получить цвет точки под курсором\n"
			;

			scr.clear();
			scr<<cur(0,0);
			scr<<help;
			scr.update();
			Keyb.WaitKey();
		}	

		//показываеm буфер обмена
		{
			int x=320-imgsprcopy.Len;
			int y=200-imgsprcopy.Hei-60;
			SpriteCopy.Show(x-1,y,IDSPRCOPY);
			scr.border(x-2,y-1,imgsprcopy.Len+2,imgsprcopy.Hei+2,15);
		}

		//SPRITE::IMAGE imgCur=CurSprite.GetImage(1);
		{
			//отображаем спрайт в увеличенном виде
			scr.border(0,0,onelen*img.Len, onehei*img.Hei,3);
			for(int x=0; x<img.Len; x++)
			for(int y=0; y<img.Hei; y++)
			{
				BYTE color=img.Read(x,y);
				scr.rectangle(x*onelen, y*onehei,onelen-1,onehei-1,color);	
			}
		}

		//отображаем спрайт один чтобы вокруг было пусто
		CurSprite.Show(320-img.Len-5, 200-115, 1);

		scr.locateXY(0,onehei*img.Hei);
		scr<<SpriteIndex;

		{
			//отображаем этот спрайт рядом плиткой
			for(int x1=0; x1<3; x1++)
			for(int y1=0; y1<3; y1++)
			CurSprite.Show(320-24*x1,y1*24,1);
		}

		scr<<cur(0,19)<<filename;

		if ((Keyb[KEY_LEFTCTRL] && Keyb[KEY_C]) || Keyb[KEY_F5])
		{
			SPRITE::IMAGE img_src=CurSprite.GetImage(1);
			SPRITE::IMAGE img_dst=SpriteCopy.GetImage(IDSPRCOPY);

			int src_len=img_src.Len*img_src.Hei;
			int dst_len=img_dst.Len*img_dst.Hei;
			if (src_len == dst_len)
			{
				memcpy(img_dst.Datacolor, img_src.Datacolor, src_len);
				//Msg(" СКОПИРОВАНО ",9);
				//Keyb.WaitKey();
			}
			else
			{
				Msg(" НЕРАВНАЯ ДЛИНА! НЕВОЗМОЖНО КОПИРОВАТЬ! ",9);
				Keyb.WaitKey();
			}
			
		}

		//F7
		//вставка
		if (Keyb[KEY_LEFTCTRL] && Keyb[KEY_V])
		{
			SPRITE::IMAGE img_dst=CurSprite.GetImage(1);
			SPRITE::IMAGE img_src=SpriteCopy.GetImage(IDSPRCOPY);

			int src_len=img_src.Len*img_src.Hei;
			int dst_len=img_dst.Len*img_dst.Hei;
			if (src_len == dst_len)
			{
				memcpy(img_dst.Datacolor, img_src.Datacolor, src_len);
				Modify=true;
				//" ВСТАВЛЕНО ",9);
				//yb.WaitKey();
			}
			else
			{
				Msg(" НЕРАВНАЯ ДЛИНА! НЕВОЗМОЖНО ВСТАВИТЬ! ",12);
				Keyb.WaitKey();
			}

		}


		if (Keyb[KEY_PAGEUP]) 
		{
			if (Modify)
			{
					Msg("Спрайт изменен! <C> для продолжения.");
					if (Keyb.ReadScan() != KEY_C)
					{
						continue;
					}
			}


			Reload=true;
			SpriteIndex++;
			Keyb^KEY_PAGEUP;
		}

		if (Keyb[KEY_PAGEDOWN])
		{
			if (Modify)
			{
					Msg("Спрайт изменен! <C> для продолжения.");
					if (Keyb.ReadScan() != KEY_C)
					{
						continue;
					}
			}


			Reload=true;

			if (SpriteIndex) SpriteIndex--;
			Keyb^KEY_PAGEDOWN;
		}

		if (Reload)
		{
			CFile file;
			if (file.Open(filename,CFile::modeRead))
			{
				file.Seek(SpriteIndex*24*24,0);
				file.Read(img.Datacolor,24*24);
				file.Close();
			}

			Reload=false;
			Modify=false;
			
		}


		
		//рисует строку цветов
		for(int i=0; i<256; i++)
		{
			scr.linedown(i,200-heiclr, heiclr,i);
		}

		//рисуем текущий цвет
		{
			int cxl=15,cyl=10;
			scr.locateXY(320-8*3,200-cyl-8);
			scr<<CurrentColor;
			scr.rectangle(320-cxl,200-cyl,cxl,cyl,CurrentColor);

			int x=CurrentColor, y=200-heiclr-1;
			scr.line(x,y,x,y-8,15);
			scr.line(x,y,x-3,y-3,15);
			scr.line(x,y,x+3,y-3,15);
		}

		//рисуем цвет над курсором
		{
			SPRITE::IMAGE img=CurSprite.GetImage(1);

			int x=Mouse.x;
			int y=Mouse.y;

			if (x<img.Len*onelen && y<img.Hei*onehei)
			{
				int curclr=img.Read(x/onelen,y/onehei);


				int yoff=30;
				int cxl=15,cyl=10;
				scr.locateXY(320-8*3,200-cyl-8-yoff);
				scr<<curclr;
				scr.rectangle(320-cxl,200-cyl-yoff,cxl,cyl,curclr);

			}

		}

		//рисуем курсор мышки
		{
			int x=Mouse.x;
			int y=Mouse.y;
			int c=15;
			scr.putpixel(x,y-1,c);
			scr.putpixel(x,y+1,c);
			scr.putpixel(x-1,y,c);
			scr.putpixel(x+1,y,c);
		}

		//рисуем курсор мышки
		{
			int x=Mouse.x;
			int y=Mouse.y;
			int c=15;
			scr.putpixel(x,y-1,c);
			scr.putpixel(x,y+1,c);
			scr.putpixel(x-1,y,c);
			scr.putpixel(x+1,y,c);
		}

		scr.update();
		Sleep(1);


		if (Keyb[KEY_F2])
		{
			Msg(" Записать. Уверены ? ");
			Keyb.clear();
			if (Keyb.ReadScan() == KEY_Y)
			{
				//запись в файл

				CFile file;
				if (!file.Open(filename, file.modeWrite))
				{
					Msg ("НЕ МОГУ ОТКРЫТЬ graph\\sprite.dat!");
					Keyb.getch();
					continue;
				}


				file.Seek(SpriteIndex*24*24,0);
				file.Write(img.Datacolor,24*24);
				file.Close();
				Msg( "       ЗАПИСАНО !       ", 9 );
				Keyb.WaitKey();

				Modify=false;
			}
			Modify=0;
		}

		//выход из редактора
		if (Keyb[KEY_ESC]) 
		{
			Keyb^KEY_ESC;
			if (Modify)
			{
				Msg(" ВНЕСЕНЫ ИЗМЕНЕНИЯ, ВЫЙТИ ? ");
				if (Keyb.WaitKey() == KEY_Y) return 0;
			}
			else return 1;
		}



		//получение цвета над курсором
		if (Keyb[KEY_ENTER] || Mouse.Buttons & MOUSE::BUTTON_RIGHT)
		{
			SPRITE::IMAGE img=CurSprite.GetImage(1);

			int x=Mouse.x;
			int y=Mouse.y;

			if (x<img.Len*onelen && y<img.Hei*onehei)
			{
				CurrentColor=img.Read(x/onelen,y/onehei);
			}

		}

		//рисование
		if (Keyb[KEY_SPACE] || Keyb[KEY_DELETE] || Mouse.Buttons&MOUSE::BUTTON_LEFT)
		{
			SPRITE::IMAGE img=CurSprite.GetImage(1);

			int x=Mouse.x;
			int y=Mouse.y;

			BYTE clr=CurrentColor;
			if (Keyb[KEY_DELETE]) clr=0;

			if (x<img.Len*onelen && y<img.Hei*onehei)
			{
				img.Write(x/onelen,y/onehei,clr);
				Modify=true;
			}

			//выбор цвета
			if (x<256 && y>200-heiclr)
			{
				CurrentColor=x;
			}
		}

		if (Keyb[KEY_LEFT]) CurrentColor--, Keyb^KEY_LEFT;
		if (Keyb[KEY_RIGHT]) CurrentColor++, Keyb^KEY_RIGHT;

		//выбор цвета

	}
	}
	catch (...)
	{
		Msg ("Exception");		
		Keyb.ReadScan();
	}

	return 0;
}