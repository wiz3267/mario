//Level.cpp

#include "stdafx.h"
#include "total.h"

#include <fstream.h>

#include "SpriteEditor.h"

static int LevelModify=0;

//����������� ����� num � ������ ��������,
//num - �����
//width - ������ ��������������
//dest - ����� ������, ���� ����� ����������� �����
void LEVEL::ConvertNumber(int num, char width, char * dest)
{
	if (width>10 || width<1) Debug("ConvertNumber - width incorrect");
	dest[0]=9;
	char * str = new char[width];
	for (int i=0; i<width; i++)
	{
		str[i]=num % 10;
		num/=10;
	}
	int k;
	for (i=width-1,k=0; k<width; k++,i--)
	{
		dest[k]=str[i]+'0';
	}
	delete str;
}

static	int 
		x=0,y=0,		//���������� ������ ������
		CurrentSprite=6,//����� �������� �������
		xcur=0,ycur=0,	//���������� ������ �������
		LOOP=TRUE;		//���� LOOP=FALSE, �� ����� �� ���������

//�������� ������ LevelNumber
int LEVEL::Editor(int LevelNumber)
{

	int bkcolor=scr.bkcolor;
	int textcolor=scr.color;

	LOOP=TRUE;

	int ShowMap=1;		//���������� �����

	int *SaveBlock=0;	//������ ����, ����������� <CTRL>+<INS>
	unsigned int BlockLen, BlockHei;

	
	x=this->x;
	y=this->y;

	Load(LevelNumber);

	//������� ����
	//MOUSE Mouse(&scr);

	//�������� �����
	//Timer.Restart(19);

	//���� ��������� �������
	while (LOOP)
	{
		//������ ���
		scr.rectangle(0,0,320,200,BackgroundColor);


		//������ �������
		this->x=x;
		this->y=y;
		Show(x,y, SHOW_DEBUG | SHOW_BACKGROUND | SHOW_FOREGROUND);

		//������ �������
		{
			int a;
			if (x/24 % 2 ) a=24;
			else a=0;
			for(int x=a; x<320; x+=48)
			{
				scr.linedown(x,0,200, 15);
			}

			for(int y=0; y<200; y+=24)
			{
				scr.lineright(0,y,320, 7);
			}
		}

		//������������� ���� ������ � ����
		{
			scr.setcolor(15);
			scr.setbkcolor(16);
		}

		//������ ����� ������
		//if (Timer.GetTotalCounter()%40>1)
        {
			scr.rectangle(xcur*BoxLen+3, ycur*BoxHei+3,
						BoxLen-6, BoxHei-6, 9);
        }

		//������� ������� ������
		{
			scr.setbkcolor(16);
			scr.rectangle(320-BoxLen-4-1,200-BoxLen-4-1,BoxLen+4,BoxLen+4,0);
			if (CurrentSprite)
			{
				spr->Show(320-BoxLen-2-1,200-BoxLen-2-1, CurrentSprite);
			}
		}

		//���������� ����� ������ ����������
		{
            //������� ����� �������� �������
			scr << cur(34,24) << CurrentSprite;
			//���������� ��������� ����������
			scr << cur(0,24) << "CUR " << xcur << ':' << ycur;
			//���������� ���������� ����
			scr << cur(9,24)<< "WIN "<< x/BoxLen << ':' << y/BoxHei;
			//���������� ���������� ����������
			scr << cur(19,24)<< "GLOBAL  "<< (x/BoxLen + xcur) << ':' << (y/BoxHei+ycur);

			//���������� ����� ������
   	        scr << cur(0,23) << "LEVEL " << LevelNumber;
			//������� ������� ������
   	        scr << cur(9,23) << Len << 'x' << Hei;

			//���������� ����� ������ mario
            scr.locateXY(MarioX-x,MarioY-y);
            scr<<"Mario";

			//���������� �����
			scr << cur(17,23) << "TIME=" << Time;

            if (BackgroundColor & FLAG_UNDERWATER)
			scr << cur(26,23) << "��������";
		}


		//������ ����� ������ (������� � ����������� ��������)
        if (ShowMap & 1)
        {
            for(int y=0;y<Hei; y++)
			for(int x=0; x<Len; x++)
            {
                int a=Read(x,y);
				if (a) a=8+a%8;
                    
                scr.putpixel(x,y,a);

				if (!a && x<this->x/24+13 && x>=this->x/24
                && y>=this->y/24 && y<this->y/24+8)
				{
					scr.putpixel(x,y,15);
				}
            }
       }

         // *** ������������ ������� ������ *****

		//�������� ��������� �����
		if ( Keyb[KEY_TAB] )
		{
			//������������ ������
			Keyb.Set(KEY_TAB,0);

			ShowMap++;
		}

		//�������� ���� � ����������
		if ( Keyb[KEY_RIGHTCTRL] || Keyb[KEY_LEFTCTRL] )
		{
			if ( Keyb[KEY_LEFT]  && x>=BoxLen) x-=BoxLen;
			if ( Keyb[KEY_RIGHT] && x<BoxLen*Len-320) x+=BoxLen;
			if ( Keyb[KEY_UP]    && y>=BoxHei) y-=BoxHei;
			if ( Keyb[KEY_DOWN]  && y<BoxHei*Hei-200)  y+=BoxHei;
		}


		//�������� ���� � ������� ����
		/*{
			if (Mouse.x>318 && x<BoxLen*Len-320)
				x+=BoxLen;
			if (Mouse.x<3 && x>BoxLen)
				x-=BoxLen;
			if (Mouse.y>198 && y<BoxHei*Hei-200)
				y+=BoxHei;
			if (Mouse.y<3 && y>BoxHei)
				y-=BoxHei;
		}*/


		//run Sprite Editor from Level Editor
		if (Keyb[KEY_S] && Keyb[KEY_E])
		{
			SPRITEEDITOR SprEditor;
			SprEditor.Editor(spr,CurrentSprite);
			Supermario.LoadSprites();	
		}

		//����� ������� �������� (S - SELECT)
		if (Keyb[KEY_S])
		{
			int current=CurrentSprite;

			int timecounter=0;
			while(1)
			{
				scr.clear();

				int nspr=1;

				if (Keyb[KEY_ENTER]) break;

				if (current>13*6) nspr=13*4;

				for(int ys=0;ys<10;ys++)
				{
					for(int xs=0;xs<13;xs++)
					{
						if (spr->find(nspr))
						spr->Show(xs*24,ys*24, nspr);
						if (current==nspr)
						{
							//�� ������� ������ ����� �������
							if ((timecounter%10) <5)
							{
								scr.rectangle(xs*24,ys*24,24,24, 15);							
								scr.locateXY(xs*24, ys*24);
								scr<<nspr;
							}
						}

						nspr++;
						if (nspr==112) break;
					}
					if (nspr==112) break;
				}
				scr.update();
				scr.pause(10);

				timecounter++;
				if (Keyb[KEY_DOWN])
				{
					current+=13;
					if (spr->find(current)==-1) current-=13;
					else timecounter=0;
				}
				if (Keyb[KEY_UP])
				{
					current-=13;
					if (spr->find(current)==-1) current+=13;
					else timecounter=0;
				}
				if (Keyb[KEY_LEFT] && current>0) current--,timecounter=0;
				if (Keyb[KEY_RIGHT] && current<112) current++,timecounter=0;
				if (Keyb[KEY_ENTER]) {CurrentSprite=current;break;}
			}	

			Keyb.clear();
		}

		

		//���������� ��������
		if ( ! Keyb[KEY_RIGHTCTRL] && ! Keyb[KEY_LEFTCTRL] )
		{
 		    #define PS 4
			if ( Keyb[KEY_LEFT] && xcur>=1 ) { xcur--;scr.pause(PS); }
			if ( Keyb[KEY_RIGHT] && xcur<320/BoxLen-1 ) { xcur++;scr.pause(PS); }
			if ( Keyb[KEY_UP] && ycur>=1 ) { ycur--;scr.pause(PS); }
			if ( Keyb[KEY_DOWN] && ycur<200/BoxHei-1 ) { ycur++;scr.pause(PS); }
		}

                //��������� �����������
        if ( Keyb[KEY_LEFTSHIFT] )
		{
			Keyb^KEY_UP;
			Keyb^KEY_DOWN;
			Keyb^KEY_LEFT;
			Keyb^KEY_RIGHT;
		}


		if (Keyb[KEY_F1] && Keyb[KEY_RIGHTCTRL])
		{
			char help[]=
			"{0,0, ALWAYS}, 0\n"
			"{0,17, CHGLEVEL}, 1\n"
			"{0,5, ALWAYS}, 2\n"
			"{0,15, ALWAYS}, 3\n"
			"{0,3, ALWAYS}, 4\n"
			"{0,2, ALLMAP}, 5\n"
			"{0,16, ALWAYS}, 6\n"
			"{0,6, ALWAYS}, 7\n"
			"{10,15,CHGLEVEL}, 8\n"
			"{10,15,BOSSLIVE | CHGLEVEL}, 9\n"
			"{1,17, BOSSDEATH | CHGLEVEL} 10\n";

			scr.clear();
			scr<<cur(0,0);
			scr.color=4;
			scr<<"������� ����������\n";
			scr.color=7;
			scr<<help;
			scr.update();
			Keyb.ReadScan();
		}

		if (Keyb[KEY_F1] && Keyb[KEY_LEFTCTRL])
		{
			char help1[]=
			"20 ������\n21 ����������\n22 ������� ������\n"
			"23 ���������\n24 �������� ������\n"
			"25 ���������� �������� �����\n"
			"26 ����\n27 �������\n29 ������ �����-������\n"
			"30 ����\n"
			"31 ������ �����-���� (����� )\n"
			"32 ������ �����-���� (������� )\n"
			"33 ���� ����� - ������\n"
			"34 ������� ������ ������-����� �� 6\n"
			"35 ������� ������ �����-������ �� 6\n"
			"36 ������ �����-���� (�� 4 � ������)\n"
			"37 ������ (�������� �������)\n"
			"38 ������ (�������� �������)\n"
			"39 ������ (�������� �������)\n"
			"40 ������ ������\n41 ���������\n"
			"42 ������ �� 2 ������( ������ )\n";
			char help2[]=
			"43 ������ ����-����� �� 9\n"
			"44 ������ ����-����� �� 5 � ������\n"
			"45 ������ �����-���� �� 4 c ������\n"
			"46 ������ �����-���� �� 2 � ������\n"
			"47 ������ ����-����� �� 6 � ������\n"
			"48 ������ ������ �����-������ �� 16\n"
			"49 ������, ������ �� ���� ���� ����\n"
			"50 ������ ��������� �����\n"
			"51 ������\n52 �����\n53 ������\n"
			"54 ����� (����)\n"
			"55 ��������� �������(�������)\n"
			"56 ��������� �����\n";

			scr.clear();
			scr<<cur(0,0);
			scr.color=4;
			scr<<"���� �����\n";
			scr.color=15;
			scr<<help1;
			scr.update();
			Keyb.ReadScan();
			scr.clear();
			scr<<cur(0,0);
			scr.color=4;
			scr<<"���� �����\n";
			scr.color=15;

			scr<<help2;
			scr.update();
			Keyb.ReadScan();
		}

		// <F1> - ������
		if ( Keyb[KEY_F1] )
		{
			char help[]=
			"<F1>, <LEFTCTRL+F1> ������\n"
			"<F2> ��������� �������\n"
			"<F3> ��������� �������\n"
			"<TAB> ��������/������ �����\n"
			"<CTRL>+<N> ����� �������\n"
			"<CTRL>+<T> ���������� ����� ����\n"
			"<CTRL>+<B> ���� ������� ����\n"
			"<CTRL>+<L> ��������� ������� N\n"
			"<CTRL>+<M> ������� �����������\n"
			"<B> ������� (���)\n"
			"<F> ������� (�� �������� ����)\n"
			"<C> ������� (������������ ��� �����)\n"
			"<D> ������� (������������� �������)\n"
			"<A> ������� (�����)\n"
			"<T> ������� (��� ������������)\n"
            "<U> ��������� ������� (����� �������)\n"
			"<PAGE UP> ��������� �������\n"
			"<PAGE DOWN> ���������� �������\n"
			"<+><1> <-><2> ����� ����������\n"
			"<ENTER> �������� ��� ��������\n"
			"<SPACE> ��������\n"
			"<M> ������� Mario\n"
			"<CTRL>+<INS> ����������\n"
			"<SHIFT>+<INS> ��������\n"
			"<DELETE> ������� \n";

			scr.clear();
			scr<<cur(0,0);
			scr<<help;
			scr.update();
			Keyb.ReadScan();

			char help2[]=
			"<SHIFT> ����������� ����� ������������\n��������\n"
			"<E>+<S> �������� ��������(Sprite Editor)\n"
			"<S> ����� ������� (Select)\n"
			;
			
			scr.clear();
			scr<<cur(0,0);
			scr<<help2;
			scr.update();
			Keyb.ReadScan();
			
		}

		// <LEFTCTRL> + <INSERT> ��������� ���� �������
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_INSERT])
		{
			scr.bkcolor=9;
			Msg(" ������ =     ",9);
			BlockLen=scr.InputNumber(3);
			Msg(" ������ =     ",9);
			BlockHei=scr.InputNumber(3);

			if ( !(BlockLen*BlockHei) || (long(BlockLen)*BlockHei)>10*1024*1024)
			{
				Debug(" ���� ������� �����! ");
			}
			else
			{
				//���� ���� ��� ����, ������ ���
				if ( SaveBlock ) delete SaveBlock;

				//�������� ������ ��� ����
				if( !(SaveBlock = new int[BlockLen*BlockHei]) )
				{
					Debug(" ��������� ������ ");
				}
				//����� �������� ���� � ������ � ������
				else
				{
					for(unsigned y=0; y<BlockHei; y++)
					for(unsigned x=0; x<BlockLen; x++)
					SaveBlock[y*BlockLen+x]=
					Read(this->x/24+xcur+x,this->y/24+ycur+y);
				}
			}
		}

		//������� �����
        if ( Keyb[KEY_LEFTSHIFT] && Keyb[KEY_INSERT])
        {
            //���� ���� ����� ��� �������
            if ( SaveBlock )
            {
                for(UINT y=0; y<BlockHei; y++)
				for(UINT x=0; x<BlockLen; x++)
				{
					Write(this->x/24+xcur+x,this->y/24+ycur+y,
					SaveBlock[y*BlockLen+x]);
				}

			}
        }

		// <ENTER> ������ ��� �������
		if ( Keyb[KEY_ENTER] )
		{
			CurrentSprite=Read(x/BoxLen+xcur,y/BoxHei+ycur) & MASK;
		}

		// <SPACE> ������
		if ( Keyb[KEY_SPACE] )
		{
			//����� � ������
			Write(x/BoxLen+xcur,  y/BoxHei+ycur, CurrentSprite);
		}

		// <B> (Background) ���������� ������� ���� ��� �������
		if ( Keyb[KEY_B] && !Keyb[KEY_LEFTCTRL] )
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=BACKGROUND;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_B;
		}

		// <D> (Destroyed) ���������� ������� ������������� ���������
		if ( Keyb[KEY_D])
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=DESTROYED;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_D;
		}

		// <C> (Collapse) ���������� ������� ������������
		// ��������� ��� ������
		if ( Keyb[KEY_C])
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=COLLAPSE;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_C;
		}


		// <T> (Transparant) ���������� ������� ���������� �������� � �������
		if ( Keyb[KEY_T] && !Keyb[KEY_LEFTCTRL])
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=TRANSPARENTPIXELS;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_T;
		}


		// <F> (Foreground) ���������� ������� '������ ����� ��������'
		if ( Keyb[KEY_F] )
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=FOREGROUND;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_F;
		}

		// <M> (Mario) ���������� ����� ������ ����
		if ( Keyb[KEY_M] )
		{
			MarioX=x+xcur*24;
			MarioY=y+ycur*24;
		}

		// <A> (Alien) ���������� ������� ������
		if ( Keyb[KEY_A] )
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=ALIEN;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_A;
		}

		// <DELETE> ������� �������
		if ( Keyb[KEY_DELETE] )
		{
			//����� � ������
			Write(x/BoxLen+xcur, y/BoxLen+ycur,0);
		}

		// <U> - Underwater - ��������� �������
		if (Keyb[KEY_U])
		{
			BackgroundColor^=FLAG_UNDERWATER;
			Keyb^KEY_U;
		}

		// ������ �����
		/*if ( Mouse.Buttons & MOUSE::BUTTON_LEFT)
		{
			//���� ���� ��������������� ���� � ������� ����
			if (ShowMap & 1 && Mouse.x<Len && Mouse.y<Hei)
			{
				if (Mouse.x>Len-12) Mouse.x=Len-12;
				if (Mouse.y>Hei-7) Mouse.y=Hei-7;
				x=Mouse.x*24;
				y=Mouse.y*24;
			}
			else
			{
				Write(x/BoxLen+Mouse.x/BoxLen, y/BoxHei+Mouse.y/BoxHei, CurrentSprite);
			}
		}*/

		//������� � ������� ����
		if ( Mouse.Buttons & MOUSE::BUTTON_RIGHT)
		{
			Write(x/BoxLen+Mouse.x/BoxLen, y/BoxHei+Mouse.y/BoxHei, 0);
		}
		

		// <F3> �������� ������
		if ( Keyb[KEY_F3] )
		{
			Msg(" ������������� ������� ? (Y,N) ", 9);
			if (Keyb.ReadScan() == KEY_Y)
			{

				Load(LevelNumber);
				x=this->x;
				y=this->y;
			}
			else
			{
				Msg("      ������� �� �������� !       ");
				Keyb.ReadScan();
			}

		}

		// <F2> ������ ������
		if ( Keyb[KEY_F2] )
		{
			Msg(" ��������� ������� ?! (Y,N)",2);
			if (Keyb.ReadScan() == KEY_Y)
			{
				Msg(" ��������� �������� � ���� ",9);
				Save(LevelNumber);
				Keyb.ReadScan();
//				Debug("OK");
			}
			else
			{
				Msg(" ��������, ������� �� ��������! ",10);
				Keyb.ReadScan();
//				Debug("OK");

			}
		}

		//<PAGE UP> ����� ������
		if ( Keyb[KEY_PAGEUP] && LevelNumber<50)
		{
			if (LevelModify) {Msg(" ������� �������! "); Keyb.ReadScan();}
			else
			{

					LevelNumber++;
					Load(LevelNumber);
					x=this->x;
					y=this->y;
			}

			scr.pause(15);
		}

		//<CTRL>+<L> ��������� ������� (����� �������� � ����������)
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_L] )
		{
			scr.bkcolor=9;
			Msg(" ��������� ������� =      ",9);
			LevelNumber=WORD(scr.InputNumber(4));
			Load(LevelNumber);
		}

		//<CTRL>+<T> ���������� �����
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_T] )
		{
			scr.bkcolor=9;
			Msg(" Time =      ",9);
			Time=WORD(scr.InputNumber(4));
			LevelModify=1;
		}

		//<ALT>+<B> ���������� ���� ������� �����
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_B] )
		{
			int t=0;
			scr.bkcolor=2;
			do
			{
				Msg(" BACKGROUNDCOLOR =     ",2);
				t=scr.InputNumber(3);
			}	while (t>255);
			BackgroundColor=t;
			LevelModify=1;
		}

		//<PAGE DOWN> ����� ������
		if ( Keyb[KEY_PAGEDOWN] && LevelNumber>0 )
		{
			if (LevelModify) {Msg(" ������� �������! "); Keyb.ReadScan();}
			else
			{

					LevelNumber--;
						Load(LevelNumber);
					x=this->x;
					y=this->y;
			}

			scr.pause(15);
		}

		// <+><1> ����� �������
		if ( Keyb[KEY_PADADD] || Keyb[KEY_1] )//&& CurrentSprite<SUPERMARIO::NUMBER_LEVELBOX)
		{	
			//scr.pause(30);
			CurrentSprite++;
			if (spr->find(CurrentSprite) == -1)
			{
				CurrentSprite--;
			}
			Keyb^KEY_PADADD;
			Keyb^KEY_1;


		}

		// <-><2> ����� �������
		if ( (Keyb[KEY_PADSUB] || Keyb[KEY_2]) && CurrentSprite>1)
		{
			//scr.pause(30);
			CurrentSprite--;
			if (spr->find(CurrentSprite) == -1)
			{
				CurrentSprite++;
			}
			Keyb^KEY_PADSUB;
			Keyb^KEY_2;

		}

		// <ESC> ����� �� ���������
		if ( Keyb[KEY_ESC] )
		{
			//���� ������� ��� �������
			if (LevelModify)
			{
				Msg(" ��������! ���� �� �������� !");
				scr.clear();
				Keyb.ReadScan();
			}
			else
			{
				scr.clear(0);
				LOOP=FALSE;
			}
		}

		// <ALT>+<N> �������� ������ ������
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_N] )
		{
  			scr.bkcolor=9;
			Msg(" ������ =     ",9);
			int len=scr.InputNumber(3);
			Msg(" ������ =     ",9);
			int hei=scr.InputNumber(3);

			New(len,hei);
			x=this->x;
			y=this->y;
		}

		//���������� ������� �����������
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_M])
		{
			scr.clear();

			scr.setcolor(12);

			scr.center(0,"������� �����������");

			scr.setcolor(13);
			scr<<cur(0,1)<<"���";
			scr<<cur(6,1)<<"����";
			scr.setcolor(15);
			for(int i=0; i<SUPERMARIO::SHUFFLE_COUNT; i++)
			{
				SUPERMARIO::SHUFFLE &shuffle=Supermario.Shuffle[i];
				scr<<cur(0,i+2)<<i;
				scr<<cur(3,i+2)<<"-> "<<shuffle.BoxCode<<" ";

				//ALWAYS	=	0x00,	//������������ ����� ������
				//ALLMAP	=	0x01,	//������������ ����� ������ ���� ������� ��� �����	
				//BOSSLIVE	=	0x02,	//������������ ����� ���� ��� ����(������)
				//BOSSDEATH	=	0x04,	//������������ ����� ���� ���� �������
				//CHGLEVEL	=	0x08	//���� ����� �����
				int Status=shuffle.Status;

				if (Status & shuffle.ALLMAP)	scr<<"�������� ";
				if (Status & shuffle.BOSSLIVE)	scr<<"������ ";
				if (Status & shuffle.BOSSDEATH) scr<<"�������� ";
				if (Status & shuffle.CHGLEVEL) 
				{
					scr<<"���������["<<Supermario.Shuffle[i].LevelNumber<<"]";
				}
				if (Status & shuffle.NEXTLEVEL) 
				{
					scr<<"�����������";
				}

			}

			scr.update();
			Keyb.ReadScan();
		}

		//������ ������ ����
		//Mouse.Draw();

		scr.locateXY(Mouse.x,Mouse.y);
		scr.putpixel();

		//������������� �� �������
		while (Timer.Counter<1);
		Timer.Counter=0;

		//���������� ������
		scr.update();
		
		Sleep(1);
	}

	//������� ����
	if (SaveBlock) delete SaveBlock;

	scr.bkcolor=bkcolor;
	scr.color=textcolor;

	return LevelNumber;
}

//====================== ����������� ==================
//Sprite - ����� ������� ����������� ��������, ������������
//��� ���������

LEVEL::LEVEL(int len, int hei,SPRITE *spr1)
{
		SIGNATURE=0xF0E0D0C0L;
        sizeofLevel=sizeof(*this);

	//���������� ����c �������-������
	spr=spr1;

	//����� ������
	Len=len;
	Hei=hei;

	//������� ����� ���������(�� ���������)
	BoxLen=24;
	BoxHei=24;

	//��������� New ������� ��, ��� ���� �� ������ Data
	Data=NULL;
	New(len,hei);
}
//=========================== ���������� ============================
LEVEL::~LEVEL()
{
	//������� �������
	delete [] Data;
	Data=NULL;
}



//������� ����� �������
void LEVEL::New(int len,int hei)
{
	delete Data;	//������� ������� �������

	Data=new WORD[len*hei];	//�������� ������ ��� ����� �������
	if (!Data)
	{
		Fatal("LEVEL::New Can't allocate memory!");
		len=1;
		hei=1;
	}

	x=0;
	y=0;
	Len=len;
	Hei=hei;
	MaxX=(Len-14)*24+(24-8);
	MaxY=(Hei-9)*24+(24-8);

	//������� ������
	for (int i=0; i<len*hei; i++)
		Data[i]=0;

}

//========== 'Save' - ���������� ������ ===================
int LEVEL::Save(int LevelNumber)
{
	MaxX=(Len-14)*24+(24-8);
	MaxY=(Hei-9)*24+(24-8);

	//�������� �����
	//char * name="levels\\level???.dat";
	char name[]="levels\\level???.dat";
	ConvertNumber(LevelNumber, 3, name+12);
	

	ofstream ofl(name, ios::binary);

	if ( !ofl ) {
		Debug("LEVEL::SAVE - can't create file");
		return 0;
	}
	//����� � ����
	//����� ��� ������

	ofl.write((char*)&SIGNATURE,4);
	ofl.write((char*)&sizeofLevel,2);
	ofl.write((char*)&spr,4);
	ofl.write((char*)&x,2);
	ofl.write((char*)&y,2);
	ofl.write((char*)&MaxX,2);
	ofl.write((char*)&MaxY,2);
	ofl.write((char*)&Len,2);
	ofl.write((char*)&Hei,2);
	ofl.write((char*)&BoxLen,2);
	ofl.write((char*)&BoxHei,2);
	ofl.write((char*)Data,4);
	ofl.write((char*)&MarioX,2);
	ofl.write((char*)&MarioY,2);
	ofl.write((char*)&BackgroundColor,2);
	ofl.write((char*)&Time,2);

	
	ofl.write( (char*)Data, Len*Hei*2);

	ofl.close();
	LevelModify=0;
	return 1;
}

//======== 'Load' - �������� ������ =================
int LEVEL::Load(int LevelNumber)
{
	char name[]="levels\\level???.dat";
	ConvertNumber(LevelNumber, 3, name+12);

	//char * name="levels\\level000.dat";


	//�������� �����
	CFile ifl;
	
	
	//���� �� ������ ������� ���� - ������� ������ �������
	if ( !ifl.Open(name,ifl.modeRead) )
	{
                Debug("LEVEL::LOAD file not exist");
       			New(14,10);
				return 1;
	}



	//������� ������ ������� ������
	delete Data;
	Data=NULL;

	//������ �� �����:

        //���������� ��, ��� �� ����� ���� ������� ���������
	SPRITE *spr1=spr;


	//������ ���������
	ifl.Read( &SIGNATURE, sizeof(SIGNATURE) );

        //����������� ���������:
	//���� ��� �� ����� f0e0d0c0
        if (SIGNATURE != 0xF0E0D0C0L)
        {
                Debug("LEVEL::Load - bad file format");
				return 0;
        }
        else
        {
        	//��������� ������ �������
                ifl.Read( &sizeofLevel, sizeof(sizeofLevel) );

                /*if (sizeofLevel> sizeof(*this) )
                {
                        Debug("LEVEL::Load - sizeofLevel too big !)");
						return 0;
				}

                if ( sizeofLevel<sizeof(*this) )
                {
                        Debug("LEVEL::Load - sizeofLevel too small !)");
                        return 0;
                }*/

                //��������� ������
                //ifl.seekg(0);
                //ifl.read( (char*)this, sizeofLevel);

                //if (sizeofLevel<sizeof(*this))
	              // 	sizeofLevel=sizeof(*this);
				ifl.Read((char*)&spr, 4);
				ifl.Read((char*)&x, 2);
				ifl.Read((char*)&y, 2);

				ifl.Read((char*)&MaxX, 2);
				ifl.Read((char*)&MaxY, 2);

				ifl.Read((char*)&Len, 2);
				ifl.Read((char*)&Hei, 2);
				ifl.Read((char*)&BoxLen, 2);
				ifl.Read((char*)&BoxHei, 2);
				ifl.Read((char*)&Data, 4);

				ifl.Read((char*)&MarioX, 2);
				ifl.Read((char*)&MarioY, 2);
				ifl.Read((char*)&BackgroundColor, 2);
				ifl.Read((char*)&Time, 2);
        }

	//��������������� ����� �������-������
	spr=spr1;

	//�������� ������ ��� ������
	Data=new WORD[Len*Hei];

	if (!Data)	//���� �� ������ �������� ������ ��� ������
	{
		Fatal("LEVEL::Load() - can't allocate memory!");
		return 0;
	}

	//������ ������
	ifl.Read( (char*)Data, Hei*Len*2 );
/*	if (siz != Hei*Len)
	{
		fatal("LEVEL::Load - loading too smal!");
  }*/
	//��������� ����
	ifl.Close();

	//������������� ������� ����, ��� ������� �� �������
	LevelModify=0;

	return 1;
}

//=========== 'Read' - ������� ���� ������ ===========
//x,y - ���������� ����������
int LEVEL::Read(int xc,int yc)
{
	if (xc<0 || xc>=Len || yc<0 || yc>=Hei)
	{
//		Debug("LEVEL::Read - X or(and) Y is bad");
		return 0;
	}
	return Data[yc*Len+xc];
}

void LEVEL::Show()
{
	Show(x,y);
}

//===================== 'Show' - �������� ������� ================
//x,y - ���������� ����������
void LEVEL::Show(int x,int y,char how)
{
/*
	if (x>MaxX)
	{
		Debug("LEVEL::Show - X is too big");
                return;
	}
	if (x<0)
	{
		Debug("LEVEL::Show - X too small");
                return;
	}
	if (y<0)
	{
		Debug("LEVEL::Show - Y too small");
				return;
	}

	if ( y>MaxY)
	{
		Debug("LEVEL::Show - Y too big");
        	return;
	}
*/

	int xoff=-x%BoxLen;
	int yoff=-y%BoxHei;

	for (int j=0; j<=200+BoxHei; j+=BoxHei)
	{
		for(int i=0; i<320+BoxLen; i+=BoxLen)
		{
            unsigned t=ReadXY(x+i,y+j);

            int msk;
			if (t& TRANSPARENTPIXELS) msk=SPRITE::SPRITETRANSPARENT;
			else		    msk=0;

			if ( (t & MASK) && (~t & ALIEN)
							&& 
				( (t&FOREGROUND && how&SHOW_FOREGROUND) 
				|| (~t&FOREGROUND && how&SHOW_BACKGROUND))
				)
				spr->ShowDirect(xoff+i, yoff+j, (t & MASK) -1, msk);

		
			//���� �������� �������
			if (how & SHOW_DEBUG)
			{
			if ( t & TRANSPARENTPIXELS)
			{
				scr.locateXY(xoff+i+7+7, yoff+j);
				scr << setcolor(14) <<'T';
			}

			if ( t & DESTROYED)
			{
				scr.locateXY(xoff+i, yoff+j+8);
				scr << setcolor(15) <<'D';
			}

			if ( t & COLLAPSE)
			{
				scr.locateXY(xoff+i+8, yoff+j+8);
				scr << setcolor(11) <<'C';
			}


			if ( t & BACKGROUND)
			{
				scr.locateXY(xoff+i, yoff+j);
				scr<< setcolor(9) <<'B';
			}

			if ( t & FOREGROUND)
			{
				scr.locateXY(xoff+i+7, yoff+j);
				scr << setcolor(12) <<'F';
			}
			
			if (t & ALIEN)
			{
			scr.locateXY(xoff+i,
			yoff+j+8);
			scr << setcolor(15);

			int a=-1;

			switch ( t & MASK)
			{
			case SUPERMARIO::ALIEN::NEXTLEVEL:	//������������� �� ����. �������
			{
				scr<<"NEXTLEVEL";
				break;
			}

			case SUPERMARIO::ALIEN::PIG:         //������
			{
				a=SPRITE_PIGSTART;
				break;
			}

			case SUPERMARIO::ALIEN::LIZARD:     //����������
			a=		SPRITE_LIZARDSTART;			//������
			break;

			case  SUPERMARIO::ALIEN::MASHA:		//������� ������
			a=        SPRITE_MASHASTART;		//������� ����
			break;

	        case  SUPERMARIO::ALIEN::TURTLE:	//���������
            a=        SPRITE_TURTLESTART;		
            break;

			case  SUPERMARIO::ALIEN::TOOTHFLOWER:	//�������� ������
			a=        SPRITE_TOOTHFLOWERSTART;	//�������� ������
            break;

			case  SUPERMARIO::ALIEN::FIRELINE:    //���������� �������� �����
			scr<<"FIRELINE";
			break;

			case  SUPERMARIO::ALIEN::HEDGEHOG:	//����
            scr<<"HEDGEHOG";
            break;

			case  SUPERMARIO::ALIEN::ABORIGINE:	//�������
			a=SPRITE_ABORIGINESTART;			//�������
            break;

	        case  SUPERMARIO::ALIEN::LIFT:	//����
            scr<<"LIFT";
            break;

            default:
			scr.locateXY(xoff+i,
			yoff+j+8+8);
			scr << int(t & MASK);

			}
			if (a!=-1)
			{
                Sprite.Show(xoff+i,yoff+j, a, 0);//SCREEN::FLIP_HORZ);
            }
			} //if (t & ALIEN)
			} //if (how & DEBUG)
		} //for(i
	}//for(j
}


//����� � �������
void LEVEL::Write(int xc,int yc,int what)
{
	if (xc<0 || xc>=Len || yc<0 || yc>=Hei)
	{
		//Debug("LEVEL::Write X or(and) Y is bad");
		return;
	}

    if (Data[yc*Len+xc] != what)
    {
		Data[yc*Len+xc]=what;
		//������������� ������� ��������� ������
		LevelModify=1;
    }

}