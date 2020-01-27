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

//�������� ��������
int SPRITEEDITOR::Editor(SPRITE * sprZZZ, int current)
{
	/*���������� �������� �����
	��� ������� ������ ������� ���������
	������ ������� ���� ���������
	����� ����� �� ���������
	��� ��������� ���������� ��� ����������
	�� ����������� ������ ��������
	*/

	//������� ����������
	int onelen=6;
	int onehei=6;
	
	bool Reload=true;

	//������� ����
	BYTE CurrentColor=15;
	
	//������ ������� ������
	int heiclr=16;

	SPRITE CurSprite(&scr);
	SPRITE::IMAGE img;
	img.Hei=24;
	img.Len=24;
	img.Attribute=0;
	img.ID=1;
	CurSprite.Create(img);

	SPRITE SpriteCopy(&scr);	//���� ����������� ������ ��� ����������� � �������	
	const int IDSPRCOPY=1;
	SPRITE::IMAGE imgsprcopy;
	imgsprcopy.Len=24;
	imgsprcopy.Hei=24;
	imgsprcopy.Attribute=0;
	imgsprcopy.ID=IDSPRCOPY;
	SpriteCopy.Create(imgsprcopy); //������� ������

	try
	{

	bool Modify=false;	//���� �� ������� ��������� � ����
	while(1)
	{
		scr.clear();

		if (Keyb[KEY_F7])
		{
			if (Modify)
			{
					Msg("������ �������! <C> ��� �����������.");
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
					Msg("������ �������! <C> ��� �����������.");
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
					Msg("������ �������! <C> ��� �����������.");
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
			"F1 ������\n"
			"F2 ���������\n"
			"F7 ����� ����� 'sprite.dat'\n"
			"F8 ����� ����� 'levelbox.dat'\n"
			"F9 ����� ����� 'fontbig.dat'\n"
			"<ESC> ����� �� ���������\n"
			"<CTRL>+<C>,F5 ���������\n"
			"<CTRL>+<V> ��������\n"
			"<LEFT><RIGHT> �������� ������� ����\n"
			"<PAGEUP><PAGEDOWN> �������� ������������� ������\n"
			"<SPACE><LBUTTONMOUSE> �������� �����\n"
			"<DELETE> ������� �����\n"
			"<ENTER><RBUTTONMOUSE> �������� ���� ����� ��� ��������\n"
			;

			scr.clear();
			scr<<cur(0,0);
			scr<<help;
			scr.update();
			Keyb.WaitKey();
		}	

		//���������m ����� ������
		{
			int x=320-imgsprcopy.Len;
			int y=200-imgsprcopy.Hei-60;
			SpriteCopy.Show(x-1,y,IDSPRCOPY);
			scr.border(x-2,y-1,imgsprcopy.Len+2,imgsprcopy.Hei+2,15);
		}

		//SPRITE::IMAGE imgCur=CurSprite.GetImage(1);
		{
			//���������� ������ � ����������� ����
			scr.border(0,0,onelen*img.Len, onehei*img.Hei,3);
			for(int x=0; x<img.Len; x++)
			for(int y=0; y<img.Hei; y++)
			{
				BYTE color=img.Read(x,y);
				scr.rectangle(x*onelen, y*onehei,onelen-1,onehei-1,color);	
			}
		}

		//���������� ������ ���� ����� ������ ���� �����
		CurSprite.Show(320-img.Len-5, 200-115, 1);

		scr.locateXY(0,onehei*img.Hei);
		scr<<SpriteIndex;

		{
			//���������� ���� ������ ����� �������
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
				//Msg(" ����������� ",9);
				//Keyb.WaitKey();
			}
			else
			{
				Msg(" �������� �����! ���������� ����������! ",9);
				Keyb.WaitKey();
			}
			
		}

		//F7
		//�������
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
				//" ��������� ",9);
				//yb.WaitKey();
			}
			else
			{
				Msg(" �������� �����! ���������� ��������! ",12);
				Keyb.WaitKey();
			}

		}


		if (Keyb[KEY_PAGEUP]) 
		{
			if (Modify)
			{
					Msg("������ �������! <C> ��� �����������.");
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
					Msg("������ �������! <C> ��� �����������.");
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


		
		//������ ������ ������
		for(int i=0; i<256; i++)
		{
			scr.linedown(i,200-heiclr, heiclr,i);
		}

		//������ ������� ����
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

		//������ ���� ��� ��������
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

		//������ ������ �����
		{
			int x=Mouse.x;
			int y=Mouse.y;
			int c=15;
			scr.putpixel(x,y-1,c);
			scr.putpixel(x,y+1,c);
			scr.putpixel(x-1,y,c);
			scr.putpixel(x+1,y,c);
		}

		//������ ������ �����
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
			Msg(" ��������. ������� ? ");
			Keyb.clear();
			if (Keyb.ReadScan() == KEY_Y)
			{
				//������ � ����

				CFile file;
				if (!file.Open(filename, file.modeWrite))
				{
					Msg ("�� ���� ������� graph\\sprite.dat!");
					Keyb.getch();
					continue;
				}


				file.Seek(SpriteIndex*24*24,0);
				file.Write(img.Datacolor,24*24);
				file.Close();
				Msg( "       �������� !       ", 9 );
				Keyb.WaitKey();

				Modify=false;
			}
			Modify=0;
		}

		//����� �� ���������
		if (Keyb[KEY_ESC]) 
		{
			Keyb^KEY_ESC;
			if (Modify)
			{
				Msg(" ������� ���������, ����� ? ");
				if (Keyb.WaitKey() == KEY_Y) return 0;
			}
			else return 1;
		}



		//��������� ����� ��� ��������
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

		//���������
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

			//����� �����
			if (x<256 && y>200-heiclr)
			{
				CurrentColor=x;
			}
		}

		if (Keyb[KEY_LEFT]) CurrentColor--, Keyb^KEY_LEFT;
		if (Keyb[KEY_RIGHT]) CurrentColor++, Keyb^KEY_RIGHT;

		//����� �����

	}
	}
	catch (...)
	{
		Msg ("Exception");		
		Keyb.ReadScan();
	}

	return 0;
}