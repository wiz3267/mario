//Mario3.cpp
#include "stdafx.h"
#include "total.h"
#include "SpriteEditor.h"

//������ ������� �����
int SUPERMARIO::MarioKeyUp(int i, PERSON &rk)
{
	double BaseSpeed;
	if ( LevelStatus &  LEVEL_UNDERWATER)
	{
		BaseSpeed=-2;
	}
	else
	{
		BaseSpeed=-6.7;
	}

	//���� ��� �����, ���������� �������
	if (LevelStatus & LEVEL_UNDERWATER)
	{
		Keyb.Set(player[i].Up, 2);
	}

	//���� ����� ��������� � �����
	if (rk.Status & MARIO_CLAMMY)
	{
		//���� ������ �����
		if (chk_up(rk,0))
		{
			rk.Speedy=BaseSpeed-abs(rk.Speedx)/6;

			//rk.Speedy=-4.2-abs(rk.Speedx)/6;
			rk.Speedx=Cleverobj[rk.Link].Go.Speed_x;
			rk.Status ^= MARIO_CLAMMY;
		}
	}
	//����� ����� ������� � �����
	else
	//Keyb.Set(KEY_UP,2);	//����� ���������
	//���� ������ ����� �
	//� ( ���� ��������� ���, ���� ��� �����)
	if (rk.Status&MARIO_WIZ)
	{
		if ( chk_up(rk,0) )
		{
		//�������� �� Y ������� �� �������� �� X
		rk.Speedy=-2;
		rk.Acceleraty=0.1;
		}
	}
	else

	if ( chk_up(rk,0) && (!rk.Acceleraty || LevelStatus & LEVEL_UNDERWATER))
	{
		//Sound.play(SND_FINGER);

		if (Keyb[player[i].Left] || Keyb[player[i].Right])
		{
			//BaseSpeed=-6;
		}

		//�������� �� Y ������� �� �������� �� X
		rk.Speedy=BaseSpeed-abs(rk.Speedx)/6;

		//���� ��������� � ������� (������� ������)
		//�� ������� ��������
		if (rk.y<24*4) rk.Speedy=-5;

		//26 jan 2008 4:39
		{
			//���� ������ SHIFT �� ������� ��������
			//(����� ������� ��� ������� ������ ����� �������!)
			if (Keyb[KEY_LEFTSHIFT])
			{
				rk.Speedy=-4.5;
			}
		}
	}
	else
	{
		//Debug("Cant't up move");
	}

	return 0;
}

//������� ������� "�����"
int SUPERMARIO::MarioKeyFire(int i, PERSON &rk)
{
	//����������� ����������� ��������
	int MarioCanFire=0;
	if
	(
	   (Bullet.Counter<4  //������� ������������ ����� ���� ������� �������� (������, ������, ��������) 
	     || 
	   abs(Bullet[Bullet.Counter-1].x-rk.x)>100)
				&&
		//� ����� ��������
		rk.Status & MARIO_CANFIRE
	) MarioCanFire=TRUE;

	else MarioCanFire=FALSE;

	//���� ������ ������ <�������>
	if (Keyb[player[i].Fire] == 1  && MarioCanFire)
	{
		Keyb.Set(player[i].Fire,2);
		//������� ������� ������
		MINDOBJ ob;
		ob.x=rk.x+3;
		ob.y=rk.y+10;
		ob.TimeLive=50;
		ob.State = MINDOBJ::PERSON;

		double Speedx,Speedy;

		//�������� - ������� �������������
		//if (rk.Speedx)
		//Speedx=rk.Speedx+sign(rk.Speedx)*2.5;
		//else
		//���������� ����������� ������� ����
		{
			if (rk.Movement==PERSON::LEFT)
			Speedx=-5.5;
			else
			Speedx=5.5;
		}

		Speedy=rk.Speedy;

		//Speedx=0;
		Speedy=0;

		//������ ����� ������
		switch ( Arms)
		{

			//������
			case ARROW:
			{

				MINDOBJ::GOING go[]=
				{ {Speedx,Speedy, 1} };

				MINDOBJ::FRAMING fr[]=
				{ {SPRITE_ARROW,1} };

				ob.Hot.Set(7,1,20,6);

				Bullet.Add(ob, 1, go, 1, fr);

				Sound.play(SND_POP);

				break;
			}

			//�������
			case DAGGER:
			{

				Sound.play(SND_BELL);

				MINDOBJ::GOING go[]=
				{ {Speedx,1+Speedy, 7}
				, { Speedx, -1+Speedy, 7} };

				MINDOBJ::FRAMING fr[]=
				{ {SPRITE_DAGGER, 1} };

				ob.Hot.Set(0,1,24,9);
				ob.y=rk.y+5;

				Bullet.Add(ob, 2, go, 1, fr);

				break;
			}

			//�������
			case AXE:
			{
				Sound.play(SND_GFX3);

				int k=int(Speedx);

				int r=1;

				MINDOBJ::GOING go[]=
				{
				{k,0,r },
				{k,-2,r },
				{0,-2,r },
				{ -k,-2,r},
				{-k,0,5},
				{ -k, 2, r},
				{ 0, 2, r },
				{ k, 0, 400 }
				};

				MINDOBJ::FRAMING fr[]=
				{ {SPRITE_AXE, 1} };

				ob.Hot.Set(0,1,24,15);
				ob.y=rk.y+5;
				ob.x=rk.x+24*sign(Speedx);

				ob.State=0;
				ob.TimeLive=100;
				Bullet.Add(ob, 8, go, 1, fr);


				break;
			}

			//�����
			case SALIVA:
			{
				Sound.play(SND_POP1);

				MINDOBJ::GOING go[]=
				{ {5*sign(Speedx),0, 1} };

				MINDOBJ::FRAMING fr[]=
				{ {SPRITE_SALIVA1, 2},
				{SPRITE_SALIVA2, 2} };

				ob.Hot.Set(0,1,24,15);
				ob.y=rk.y+5;
				ob.x=rk.x;

				ob.State=MINDOBJ::PERSON;
				ob.TimeLive=100;
				Bullet.Add(ob, 1, go, 2, fr);
				break;
			}
		}
	}
	return 0;
}

//PALETTEENTRY WizGetPaletteRegister(DWORD Register);
//void WizSetPaletteRegister(DWORD Register, PALETTEENTRY * value, int size);
//*******************************************************
//************** ��������� ������� ������ ***************
//*******************************************************
void SUPERMARIO::prKeyboardProcess()
{
	if (Keyb[KEY_LEFTSHIFT] && Keyb[KEY_E])
	{
		SPRITEEDITOR se;
		se.Editor(&Sprite,0);
		LoadSprites();
	}

	if (Keyb[KEY_LEFTCTRL] && Keyb[KEY_Q] && Keyb[KEY_Z]) 
		GAMECYCLE=FALSE,GAMEEXIT=TRUE;


	if (Keyb[KEY_F9])
	{
		//if (Sound.sound_enable)
		//{
			Sound.sound_enable=false;
			Sound.stop();
		//}
		//else
		//{
		//	Sound.sound_enable=true;
		//}
		
	}


	if (Keyb[KEY_F1])
	{
		scr.clear();
		scr<<cur(0,0);
		for(UINT i=0; i<PlayerCounter; i++)
		{
			scr.setcolor(11);
			scr<<"\n����� "<<i+1;
			scr.setcolor(15);
			const int xt=70;
			scr<<"\n����� ";   scr.x=xt;scr<<Keyb.KEY[player[i].Left];	
			scr<<"\n������ ";  scr.x=xt;scr<<Keyb.KEY[player[i].Right];
			scr<<"\n����� ";   scr.x=xt;scr<<Keyb.KEY[player[i].Up];		
			scr<<"\n����  ";   scr.x=xt;scr<<Keyb.KEY[player[i].Down];	
			scr<<"\n������ ";  scr.x=xt;scr<<Keyb.KEY[player[i].Run];
			scr<<"\n�������� ";scr.x=xt;scr<<Keyb.KEY[player[i].Fire];	
		}

		scr.setcolor(13);
		scr<<"\n<P> �����\n<CTRL+E> �������� �������\n<CTRL+Q+Z> ������� �����\n<SHIFT+E> �������� ��������\n<F9> ��������� ����\n";

		scr.update();
		Keyb.clear();
		Keyb.ReadScan();
	}

	char ks[]={ KEY_L, KEY_I, KEY_V, KEY_E, KEY_S};
	char ks2[]={ KEY_L, KEY_E, KEY_V,	KEY_ENTER};

	//����� ������ (��� "LIVES")
	int ManyLives=TRUE;
	{
		for(int i=0; i<sizeof(ks); i++)
		{
			if ( ! Keyb[ks[i]] ) ManyLives=FALSE;
		}
	}

	if (ManyLives)
	{
		MOVETXT ob;

		ob.y=100;
		ob.Message=" �� �������� 100 ������! ";
		ob.x=(40-strlen(ob.Message))/2*8;
		ob.Color=9;
		ob.TimeLive=160;
		Movetxt += ob;
		Lives=100u;
	}

	//������� �� ��������� ������� (��� "LEV<ENTER>")
	{
		int Yes=1;
		{
			for(int i=0; i<4; i++)
			{
				if ( ! Keyb[ks2[i]] ) Yes=0;
			}

			if (Yes)
			{
				LevelNumber++;
				GameMode |= GAMEMODE_RESTARTLEVEL;
				GameMode |= GAMEMODE_LOADLEVEL;
				ColorEffect();
			}
		}
	}

	//������ <ESC>
	if (Keyb[KEY_ESC]==1)
	{
		//��������� ���������� ������� �����
		//ShowExit=1;

		//����� ����� ���� ����� ������ �� �����
		//Keyb.Set(KEY_ESC,0);
		//���������� ����
		GAMECYCLE=FALSE;


		/*string s(&BigFont,"EXIT?");
		s.Show(90,88);
		Update();
		if (Keyb.ReadScan() == KEY_Y) GAME=FALSE;
		*/
	}

	//���� �� ������ ������������ ������� ����� � ������ Yes
	// Y == ��
	if (ShowExit && Keyb[KEY_Y])
	{
		//���������� ����
		GAMECYCLE=FALSE;

		//LevelNumber=0;
		for(int y=0; y<100; y++)
		{
			scr.lineright(0,100-y,320,0);
			scr.lineright(0,100+y,320,0);

			scr.pause(1);
			scr.update();

			scr.linedown(160+y,0,200,0);
			scr.linedown(160-y,0,200,0);

			scr.update();
			scr.pause(1);
		}

	}

	//���� �� ������ ������� ����� � ������ ���� �� ���� ������
	// Y == ���
	if (ShowExit && Keyb[KEY_N])
	{
		//������ ������� ����� � ������
		ShowExit=0;
	}

	//������ �����
	if (Keyb[KEY_P])
	{
		BIGSTRING s(&BigFont, "PAUSE");
		s.Show(90,70);
		scr.update();
		Keyb.ReadScan();
	}

	for (int i=0; i<Rick.Counter; i++)
	{
		//�������� �������� ������� (����� ������������)
		/*int k=rand()%32, t=rand()%2;
		switch (k)
		{
		case 10:
		Keyb.Set(player[i].Run, t);
		break;

		case 4:
		Keyb.Set(player[i].Down, t);
		break;

		case 6:
		Keyb.Set(player[i].Up,t);
		break;
		case 30:
		Keyb.Set(player[i].Left,t);
		break;

		case 15:
		case 20:
		case 7:
		Keyb.Set(player[i].Right,t);
		break;
		}*/

		PERSON &rk=(PERSON&)Rick[i];

		//���� ����� �������, �� ������ ����� ������� ��������� ������� ������
		if (rk.Status & MARIO_DEATH) continue;

		//���� ������ <�����>
		if ( Keyb[player[i].Up] == 1)
		{
			MarioKeyUp(i,rk); //������� ������� �����
		}

		if (Keyb[player[i].Fire]) MarioKeyFire(i,rk);

		//������������ ������������ ��������
		double SPMAX=2.6; //����. ��������
		if (Keyb[player[i].Run]) SPMAX=4.0;

		const double ACX=0.1;	    //���������

		//��������� ����� �� ��������� ����� ����
		rk.Acceleratx=0;
		
		//���� ������ ������ "�����"
		if (Keyb[player[i].Left] && rk.x>1.5 )
		{
			if ( rk.Speedx > -SPMAX )	rk.Acceleratx=-ACX;
			rk.Movement=PERSON::LEFT;
		}

		//���� ������ ������ "������"
		if (Keyb[player[i].Right] )
		{
			rk.Movement=PERSON::RIGHT;
			if ( rk.Speedx < SPMAX )	rk.Acceleratx=ACX;
	
		}

		//���� �� ������ �� "�����", �� "������"
		if ( !Keyb[player[i].Left] && !Keyb[player[i].Right])
		{
			rk.Acceleratx=0;

			//�������� �����
			if (abs(rk.Speedx) < 0.1 )
			{
				rk.Speedx=0;
			}

			//���� ����� ��������� � �� �������
			if (rk.Speedx && rk.Speedy==0)
			{
				//���������� ������������� ��������
				rk.Acceleratx=-sign(rk.Speedx)*1.2*ACX;
			}

			//���� ����� ��������� � �������
			//������������ ������ ������
			if (rk.Speedx && rk.Speedy)
			{
				//���������� ������������� ��������
				rk.Acceleratx=-sign(rk.Speedx)*0.6*ACX;
			}
		}

		//������������ ������������ ��������
		//���� �������� ������ ������������
		if ( abs(rk.Speedx) > SPMAX )
		{
			//rk.Speedx = sign(rk.Speedx) * SPMAX;
			//rk.Acceleratx=-sign(rk.Speedx)*1.5*ACX;
		}

		//*****************************************
		//******** ������� � ����������� **********
		//*****************************************
		if ( Keyb[player[i].Down] ) Teleport(i,rk);

		//���� ������ ������� <����>
		if ( Keyb[player[i].Down])
		{
			//���� ���� � �����
			ANIM rk1=rk;
			const int N=3;
			rk1.Rect.Left+=N;
			rk1.Rect.Right-=N;
			rk1.Rect.Top+=N;
			rk1.Rect.Bottom-=N;
	
			//������� ������� �� ����. �������
			if ( chk_all_transp(rk1,1) && (Level.ReadXY(int(rk.x),int(rk.y)) & LEVEL::MASK)==1)
			{
				Level.WriteXY(int(rk.x),int(rk.y),0);

				ANIM dr;
				dr.x=rk.x-int(rk.x)%24;
				dr.y=rk.y-int(rk.y)%24;
				dr.FrameFirst=SPRITE_DOOROPEN;
				dr.FrameLast=SPRITE_DOORCLOSE;
				dr.FrameSpeed=0.2;
				dr.TimeLive=30;
				Door+=dr;
				DoorOpenCounter=21;
			}
		}
	}


	//����� ��������� ��������� �� ����. �������
	if (DoorOpenCounter==1)
	{
		//���� ����� �����������
		if (!Door1.Counter)
		{
			MidiStop();
			Sound.play(SND_EXORCISM, SOUND::NOSTOP);

			//���� ������� ���, �����
			//��� �����������
			ANIM dr;
			dr.x=Door[0].x;
			dr.y=Door[0].y;
			dr.FrameLast=SPRITE_DOOROPEN;
			dr.FrameFirst=SPRITE_DOORCLOSE;
			dr.FrameSpeed=-0.2;
			dr.TimeLive=30;
			Door1+=dr;
			DoorOpenCounter=21;
		}
		//����� ��������� �� ��������� �������
		else 
		{
			//������ ��������
			for(int j=0; j<1024; j++)
			{
				//scr.pause(1);
				for(int i=0; i<256; i++)
				{
					scr.putpixel(rand()%320, rand()%240, 0);
				}
					
				scr.update();
			}
			
			scr.clear();
			scr.update();

			LevelNumber++;

			if (LevelNumber==49)
			{
				BIGSTRING s1(&BigFont,"THAT ALL");
				BIGSTRING s2(&BigFont,"FOLKS!");
				scr.clear();
				s1.Show(25,75);
				s2.Show(85+24*2,105);
				scr.center(21*8,"Copyright (C) 1997-2011 by Lapshin Ewgeny (Wiz)");
				scr.update();
				scr.pause(70*10);
				GAMECYCLE=FALSE;
				Keyb.ReadScan();
				//break;
			}
			else 
			{
				NORMAL_MUSIC=LevelNumber%2;
				GameMode|=GAMEMODE_RESTARTLEVEL | GAMEMODE_LOADLEVEL
				| GAMEMODE_ALIEN_SCAN;
			//break;
			}
		} //����� else
	} //if (DoorOpenCounter==1)

	//���� � �������� ( <CTRL> + <E>)
	if (Keyb[KEY_LEFTCTRL] && Keyb[KEY_E])
	{
		Msg("   ���� � �������� ...   ",9);
		scr.pause(35);\
		LevelNumber=Level.Editor(LevelNumber);
		Keyb.clear();
		InitForStartGame(0);
		GameMode|=GAMEMODE_RESTARTLEVEL | GAMEMODE_LOADLEVEL
		| GAMEMODE_ALIEN_SCAN;
	}
}


//*******************************************************
//************** ������ ������������ �� ������� *
//*******************************************************
void SUPERMARIO::prArmsCollisionWithWall()
{
	for(int i=0; i<Bullet.Counter; i++)
	{
		ANIM & bl = Bullet[i];

		//���� ����� ���-�� ����
		if (!chk_down(bl,0))
		{
			bl.Speedy=-0.7*abs(bl.Speedy);
			//if (bl.Speedy<-3) bl.Speedy=-3;
			bl.y+=2*bl.Speedy;
			bl.RenewRect();
		}

		//���� ����� ����������
		if (!chk_left(bl,0))
		{
			 int x=int(bl.x-3), y=int(bl.y+2);
			 int code=Level.ReadXY(x,y);

			 //���� �������� ������������
			 if (code & LEVEL::DESTROYED)
			 {
				int a;
				if (x/24 % 2) a=-24;
				else a=24;

				Level.WriteXY(x,y,0);
				Level.WriteXY(x+a,y,0);
				x=x-x%24;
				y=y-y%24;
				ANIM ob;
				ob.x=x;
				ob.y=y;
				ob.FrameFirst=SPRITE_TIDESTART;
				ob.FrameLast=SPRITE_TIDEEND;
				ob.FrameSpeed=0.22;
				ob.TimeLive=20;
				Different+=ob;

				ob.x+=a;
				Different+=ob;


				Sound.play(SND_FIRE);

				 //���� ���� �������� ��� ����
				 if ( code & LEVEL::FOREGROUND)
				 {
					for(; y>=24; y-=24)
					{
						int k=Level.ReadXY(x,y-24);
						Level.WriteXY(x,y, k);
						int k1=Level.ReadXY(x+a,y-24);
						Level.WriteXY(x+a,y, k1);

						if (!k || !k1) break;
					}
				}
			}

			//����� ������ �����������
			else
			{
				ANIM ob;
				ob=bl;
				ob.Set(bl.x,bl.y,0,0,0,0);
				ob.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
				ob.FrameLast=SPRITE_ARROWDESTROYEDEND;
				ob.FrameSpeed=0.2;
				ob.TimeLive=15;
				Different+=ob;
				
				//Sound.play(SND_FIRE);
			}


			//���������� ������
			Bullet.Del(&bl);
			continue;
		}
		//���� ������ ����������
		else if (!chk_right(bl,0))
        {
			int x=int(bl.x+26), y=int(bl.y+2);
			int code=Level.ReadXY(x,y);
			//���������� ��������
			if (code & LEVEL::DESTROYED)
			{
				int a;
				if (x/24 % 2) a=-24;
				else a=24;

				Level.WriteXY(x,y,0);
				Level.WriteXY(x+a,y,0);
				x=x-x%24;
				y=y-y%24;
				ANIM ob;
				ob.x=x;
				ob.y=y;
				ob.FrameFirst=SPRITE_TIDESTART;
				ob.FrameLast=SPRITE_TIDEEND;
				ob.FrameSpeed=0.22;
				ob.TimeLive=20;
				Different+=ob;

				ob.x+=a;
				Different+=ob;


				Sound.play(SND_FIRE);

				//���� ���� �������� ��� ����
				if ( code & LEVEL::FOREGROUND)
				{
					for( ; y>=24; y-=24)
					{
						int k=Level.ReadXY(x,y-24);
						Level.WriteXY(x,y, k);
						int k1=Level.ReadXY(x+a,y-24);
						Level.WriteXY(x+a,y, k1);
						if (!k || !k1) break;
					}
				}
			}
			//����� ��������� ������
			else
			{
				
				ANIM ob;
				ob=bl;
				ob.Set(bl.x,bl.y,0,0,0,0);
				ob.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
				ob.FrameLast=SPRITE_ARROWDESTROYEDEND;
				ob.FrameSpeed=0.2;
				ob.TimeLive=15;
				Different+=ob;
				

				//Sound.play(SND_FIRE);
			}
			Bullet.Del(&bl);
			continue;
		} //end else if
	} //end for
}


//******************************************
//������ ���������� �����
//******************************************
void SUPERMARIO::ArmsKillAlien()
{
 for(int i=0; i<Bullet.Counter; i++)
 {
	//���������� �����
	for(int j=0; j<Boss.Counter; j++)
	{
		MINDOBJ &bl=Bullet[i];
		MINDOBJ &al=Boss[j];
		if ( CheckUnionRects(bl.Rect,al.Rect) )
		{
			al.ShootCounter-=1;

			//���� ���������� �����
			if (al.ShootCounter<=0)
			{
				Boss.Del(&al);

				//���� 32 ���. �����
				Score+=32000;

				MOVETXT tx;
				tx.Message="�����  32,000  !";
				tx.Color=7;
				tx.x=(320-strlen(tx.Message)*8)/2;
				tx.y=50;
				tx.TimeLive=100;
				Movetxt.DelAll();
				Movetxt+=tx;


				//������� �����
				ANIM exp;
				exp.x=al.x;
				exp.y=al.y;
				exp.FrameFirst=SPRITE_EXPLODESTART;
				exp.FrameLast=SPRITE_EXPLODEEND;
				exp.FrameSpeed=0.3;
				exp.TimeLive=16;
				Different+=exp;

				Sound.play(SND_EXPLODE, SOUND::NOSTOP);

				j--;

				BossLive=FALSE;	//���� �����
			}

			else
			{
				//����� ��������
				al.go_num=9;
				al.frame_num=7;
				al.Go=al.going[al.go_num];
				al.Frame=al.framing[al.frame_num];
				Sound.play(SND_BELL, SOUND::NOSTOP);
			}

			//������ ����
			bl.x=-24;
			bl.y=-24;
			//����������� ��������� �������������
			bl.RenewRect();
		}
	}


	//���������� ����� �����
	for(j=0; j<CleverAlien.Counter; j++)
	{
		MINDOBJ &bl=Bullet[i];
		MINDOBJ &al=CleverAlien[j];

		//���� ������
		if ( CheckUnionRects(bl.Rect,al.Rect) )
		{
		al.ShootCounter-=ArmsPower;

		//���� ���������� ������
		if (al.ShootCounter<=0)
		{
			Score+=200;
			//������� �����
			ANIM exp;
			exp.x=al.x;
			exp.y=al.y;

			exp.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
			exp.FrameLast=SPRITE_ARROWDESTROYEDEND;
			exp.FrameSpeed=0.2;
			exp.TimeLive=16;
			Different+=exp;

			CleverAlien.Del(&al);

			//Sound.play(SND_EXPLODE, NOSTOP);
			j--;
		}
		//������ ����
		bl.x=-24;
		bl.y=-24;
		//i--;
		//break;
		}
	}


	//���������� �������� ������
	for(j=0; j<Toothflower.Counter; j++)
	{
		PERSON &bl=(PERSON&)Bullet[i];
		ANIM &tf=Toothflower[j];
		if ( CheckUnionRects(bl.Rect,tf.Rect) )
		{
			ANIM ob;
			ob.x=tf.x;
			ob.y=tf.y;
			ob.Speedy=-1;
			ob.TimeLive=20+rand()%40;
			CreateScore(200,SCORES,ob);
			Score+=200;
			Toothflower.Del(&tf);
			j--;

			//������� �����
			ANIM exp;
			exp.x=bl.x+bl.Rect.Right-bl.Rect.Left-10;
			exp.y=bl.y+bl.Rect.Bottom-bl.Rect.Top-15;

			exp.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
			exp.FrameLast=SPRITE_ARROWDESTROYEDEND;
			exp.FrameSpeed=0.2;

			exp.TimeLive=16;
			Different+=exp;


			Log.Write("���������� ������");
		}
	}

	//���������� ������� �����
	for(j=0; j<Alien.Counter; j++)
	{
		MINDOBJ &bl=Bullet[i];
		PERSON &al=Alien[j];

		//����
		if
		(
		//������ ����� � ������ � ����� ��� �� ����������
	    CheckUnionRects(al.Rect,bl.Rect) && ~al.Status & ALIEN::DEATH)
		{

		//��������� ���� ������
		al.ShootCounter-=ArmsPower;

		//���� ���� ������ ����������
		if (al.ShootCounter<=0)
		{
			//������� �����
			ANIM exp;
			exp.x=al.x+al.Rect.Right-al.Rect.Left-10;
			exp.y=al.y+al.Rect.Bottom-al.Rect.Top-15;

			exp.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
			exp.FrameLast=SPRITE_ARROWDESTROYEDEND;
			exp.FrameSpeed=0.2;

			exp.TimeLive=16;
			Different+=exp;

			//������� ����
			ANIM ob;
			ob.x=al.x;
			ob.y=al.y;
			ob.Speedy=-1.4-0.1*(rand()%5);
			ob.TimeLive=30+rand()%30;
			CreateScore(350,SCORES,ob);
			Score+=350;

			Sound.play(SND_XPLODE);//, SOUND::NOSTOP);

			Log.Write(_S+"kill alien ("+itoc(al.FrameFirst)+")");

			Alien.Del(j);
			j--;

		}
		else
		{
			Sound.play(SND_POP);

			//��������� �����
			if (!al.Speedy)		al.Speedy=-3;
		}

		//���������� ����
		Bullet.Del(&bl);

		i--;
		break;
		} //if
	} //for(j=0; j<Alien.Counter; j++)
 
 }// for(int i=0; i<Bullet.Counter; i++)
}
