//Mario3.cpp
#include "stdafx.h"
#include "total.h"
#include "SpriteEditor.h"

//нажали клавишу вверх
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

	//если под водой, фикисируем клавишу
	if (LevelStatus & LEVEL_UNDERWATER)
	{
		Keyb.Set(player[i].Up, 2);
	}

	//если марио прилеплен к лифту
	if (rk.Status & MARIO_CLAMMY)
	{
		//если вверху пусто
		if (chk_up(rk,0))
		{
			rk.Speedy=BaseSpeed-abs(rk.Speedx)/6;

			//rk.Speedy=-4.2-abs(rk.Speedx)/6;
			rk.Speedx=Cleverobj[rk.Link].Go.Speed_x;
			rk.Status ^= MARIO_CLAMMY;
		}
	}
	//иначе марио прыгает с земли
	else
	//Keyb.Set(KEY_UP,2);	//чтобы отпустили
	//если вверху пусто и
	//и ( либо ускорения нет, либо под водой)
	if (rk.Status&MARIO_WIZ)
	{
		if ( chk_up(rk,0) )
		{
		//скорость по Y зависит от скорости по X
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

		//скорость по Y зависит от скорости по X
		rk.Speedy=BaseSpeed-abs(rk.Speedx)/6;

		//если находится в облаках (наверху уровня)
		//то прыгает невысоко
		if (rk.y<24*4) rk.Speedy=-5;

		//26 jan 2008 4:39
		{
			//если нажата SHIFT то прыгает невысоко
			//(нужно сделать для каждого игрока такую клавишу!)
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

//нажатие клавиши "огонь"
int SUPERMARIO::MarioKeyFire(int i, PERSON &rk)
{
	//определение возможности стрелять
	int MarioCanFire=0;
	if
	(
	   (Bullet.Counter<4  //сколько одновременно может быть летящих снарядов (стрелы, ножики, топорики) 
	     || 
	   abs(Bullet[Bullet.Counter-1].x-rk.x)>100)
				&&
		//и может стрелять
		rk.Status & MARIO_CANFIRE
	) MarioCanFire=TRUE;

	else MarioCanFire=FALSE;

	//если нажали кнопку <ВЫСТРЕЛ>
	if (Keyb[player[i].Fire] == 1  && MarioCanFire)
	{
		Keyb.Set(player[i].Fire,2);
		//создаем летящее оружие
		MINDOBJ ob;
		ob.x=rk.x+3;
		ob.y=rk.y+10;
		ob.TimeLive=50;
		ob.State = MINDOBJ::PERSON;

		double Speedx,Speedy;

		//скорость - понятие относительное
		//if (rk.Speedx)
		//Speedx=rk.Speedx+sign(rk.Speedx)*2.5;
		//else
		//определяем направление запуска пуль
		{
			if (rk.Movement==PERSON::LEFT)
			Speedx=-5.5;
			else
			Speedx=5.5;
		}

		Speedy=rk.Speedy;

		//Speedx=0;
		Speedy=0;

		//смотря какое оружие
		switch ( Arms)
		{

			//стрела
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

			//ножичек
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

			//топорик
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

			//слюни
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
//************** обработка НАЖАТИЙ клавиш ***************
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
			scr<<"\nИГРОК "<<i+1;
			scr.setcolor(15);
			const int xt=70;
			scr<<"\nВлево ";   scr.x=xt;scr<<Keyb.KEY[player[i].Left];	
			scr<<"\nВправо ";  scr.x=xt;scr<<Keyb.KEY[player[i].Right];
			scr<<"\nВверх ";   scr.x=xt;scr<<Keyb.KEY[player[i].Up];		
			scr<<"\nВниз  ";   scr.x=xt;scr<<Keyb.KEY[player[i].Down];	
			scr<<"\nБежать ";  scr.x=xt;scr<<Keyb.KEY[player[i].Run];
			scr<<"\nСтрелять ";scr.x=xt;scr<<Keyb.KEY[player[i].Fire];	
		}

		scr.setcolor(13);
		scr<<"\n<P> пауза\n<CTRL+E> редактор уровней\n<CTRL+Q+Z> быстрый выход\n<SHIFT+E> редактор спрайтов\n<F9> отключить звук\n";

		scr.update();
		Keyb.clear();
		Keyb.ReadScan();
	}

	char ks[]={ KEY_L, KEY_I, KEY_V, KEY_E, KEY_S};
	char ks2[]={ KEY_L, KEY_E, KEY_V,	KEY_ENTER};

	//много жизней (код "LIVES")
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
		ob.Message=" ВЫ ПОЛУЧИЛИ 100 ЖИЗНЕЙ! ";
		ob.x=(40-strlen(ob.Message))/2*8;
		ob.Color=9;
		ob.TimeLive=160;
		Movetxt += ob;
		Lives=100u;
	}

	//переход на следующий уровень (код "LEV<ENTER>")
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

	//нажали <ESC>
	if (Keyb[KEY_ESC]==1)
	{
		//разрешить отображать надпись ексит
		//ShowExit=1;

		//после этого надо опять нажать на ексит
		//Keyb.Set(KEY_ESC,0);
		//прекратить игру
		GAMECYCLE=FALSE;


		/*string s(&BigFont,"EXIT?");
		s.Show(90,88);
		Update();
		if (Keyb.ReadScan() == KEY_Y) GAME=FALSE;
		*/
	}

	//если на экране присутствует надпись ексит и нажали Yes
	// Y == Да
	if (ShowExit && Keyb[KEY_Y])
	{
		//прекратить игру
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

	//если на экране надпись ексит и нажали либо эн либо эскейп
	// Y == Нет
	if (ShowExit && Keyb[KEY_N])
	{
		//убрать надпись ексит с экрана
		ShowExit=0;
	}

	//нажали паузу
	if (Keyb[KEY_P])
	{
		BIGSTRING s(&BigFont, "PAUSE");
		s.Show(90,70);
		scr.update();
		Keyb.ReadScan();
	}

	for (int i=0; i<Rick.Counter; i++)
	{
		//случайно нажимаем клавиши (режим демонстрации)
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

		//если марио мертвый, не делаем далее никаких обработок нажатий клавиш
		if (rk.Status & MARIO_DEATH) continue;

		//если нажали <ВВЕРХ>
		if ( Keyb[player[i].Up] == 1)
		{
			MarioKeyUp(i,rk); //нажатие клавиши вверх
		}

		if (Keyb[player[i].Fire]) MarioKeyFire(i,rk);

		//ограничиваем максимальную скорость
		double SPMAX=2.6; //макс. скорость
		if (Keyb[player[i].Run]) SPMAX=4.0;

		const double ACX=0.1;	    //ускорение

		//ускорение марио по умолчанию равно нулю
		rk.Acceleratx=0;
		
		//если нажали кнопку "влево"
		if (Keyb[player[i].Left] && rk.x>1.5 )
		{
			if ( rk.Speedx > -SPMAX )	rk.Acceleratx=-ACX;
			rk.Movement=PERSON::LEFT;
		}

		//если нажали кнопку "вправо"
		if (Keyb[player[i].Right] )
		{
			rk.Movement=PERSON::RIGHT;
			if ( rk.Speedx < SPMAX )	rk.Acceleratx=ACX;
	
		}

		//если не нажали ни "влево", ни "вправо"
		if ( !Keyb[player[i].Left] && !Keyb[player[i].Right])
		{
			rk.Acceleratx=0;

			//тормозим марио
			if (abs(rk.Speedx) < 0.1 )
			{
				rk.Speedx=0;
			}

			//если марио двигается и не прыгает
			if (rk.Speedx && rk.Speedy==0)
			{
				//ускорениее противополжно скорости
				rk.Acceleratx=-sign(rk.Speedx)*1.2*ACX;
			}

			//если марио двигается в воздухе
			//кооэффициент трения меньше
			if (rk.Speedx && rk.Speedy)
			{
				//ускорениее противополжно скорости
				rk.Acceleratx=-sign(rk.Speedx)*0.6*ACX;
			}
		}

		//ограничиваем максимальную скорость
		//если скорость больше максимальной
		if ( abs(rk.Speedx) > SPMAX )
		{
			//rk.Speedx = sign(rk.Speedx) * SPMAX;
			//rk.Acceleratx=-sign(rk.Speedx)*1.5*ACX;
		}

		//*****************************************
		//******** заходим в перемещения **********
		//*****************************************
		if ( Keyb[player[i].Down] ) Teleport(i,rk);

		//если нажали кнопкку <ВНИЗ>
		if ( Keyb[player[i].Down])
		{
			//если весь в двери
			ANIM rk1=rk;
			const int N=3;
			rk1.Rect.Left+=N;
			rk1.Rect.Right-=N;
			rk1.Rect.Top+=N;
			rk1.Rect.Bottom-=N;
	
			//собрали переход на след. уровень
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


	//дверь открылась переходим на след. уровень
	if (DoorOpenCounter==1)
	{
		//если дверь открывается
		if (!Door1.Counter)
		{
			MidiStop();
			Sound.play(SND_EXORCISM, SOUND::NOSTOP);

			//надо сделать так, чтобы
			//она закрывалась
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
		//иначе переходим на следующий уровень
		else 
		{
			//эффект мерцания
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
		} //конец else
	} //if (DoorOpenCounter==1)

	//вход в редактор ( <CTRL> + <E>)
	if (Keyb[KEY_LEFTCTRL] && Keyb[KEY_E])
	{
		Msg("   ВХОД В РЕДАКТОР ...   ",9);
		scr.pause(35);\
		LevelNumber=Level.Editor(LevelNumber);
		Keyb.clear();
		InitForStartGame(0);
		GameMode|=GAMEMODE_RESTARTLEVEL | GAMEMODE_LOADLEVEL
		| GAMEMODE_ALIEN_SCAN;
	}
}


//*******************************************************
//************** оружие сталкивается со стенами *
//*******************************************************
void SUPERMARIO::prArmsCollisionWithWall()
{
	for(int i=0; i<Bullet.Counter; i++)
	{
		ANIM & bl = Bullet[i];

		//если внизу что-то есть
		if (!chk_down(bl,0))
		{
			bl.Speedy=-0.7*abs(bl.Speedy);
			//if (bl.Speedy<-3) bl.Speedy=-3;
			bl.y+=2*bl.Speedy;
			bl.RenewRect();
		}

		//если слева препятсвие
		if (!chk_left(bl,0))
		{
			 int x=int(bl.x-3), y=int(bl.y+2);
			 int code=Level.ReadXY(x,y);

			 //если кирпичик обрушивается
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

				 //если надо спустить все вниз
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

			//иначе стрела рассыпается
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


			//уничтожаем оружие
			Bullet.Del(&bl);
			continue;
		}
		//если справа препятсвие
		else if (!chk_right(bl,0))
        {
			int x=int(bl.x+26), y=int(bl.y+2);
			int code=Level.ReadXY(x,y);
			//обрушиваем кирпичик
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

				//если надо спустить все вниз
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
			//иначе разрушаем стрелу
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
//оружие уничтожает чужих
//******************************************
void SUPERMARIO::ArmsKillAlien()
{
 for(int i=0; i<Bullet.Counter; i++)
 {
	//уничтожаем босса
	for(int j=0; j<Boss.Counter; j++)
	{
		MINDOBJ &bl=Bullet[i];
		MINDOBJ &al=Boss[j];
		if ( CheckUnionRects(bl.Rect,al.Rect) )
		{
			al.ShootCounter-=1;

			//если уничтожили босса
			if (al.ShootCounter<=0)
			{
				Boss.Del(&al);

				//даем 32 тыс. очков
				Score+=32000;

				MOVETXT tx;
				tx.Message="БОНУС  32,000  !";
				tx.Color=7;
				tx.x=(320-strlen(tx.Message)*8)/2;
				tx.y=50;
				tx.TimeLive=100;
				Movetxt.DelAll();
				Movetxt+=tx;


				//создаем взрыв
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

				BossLive=FALSE;	//босс погиб
			}

			else
			{
				//башка трясется
				al.go_num=9;
				al.frame_num=7;
				al.Go=al.going[al.go_num];
				al.Frame=al.framing[al.frame_num];
				Sound.play(SND_BELL, SOUND::NOSTOP);
			}

			//прячем пулю
			bl.x=-24;
			bl.y=-24;
			//обязатольно обновляем прямоугольник
			bl.RenewRect();
		}
	}


	//уничтожаем умных чужих
	for(j=0; j<CleverAlien.Counter; j++)
	{
		MINDOBJ &bl=Bullet[i];
		MINDOBJ &al=CleverAlien[j];

		//если попали
		if ( CheckUnionRects(bl.Rect,al.Rect) )
		{
		al.ShootCounter-=ArmsPower;

		//если уничтожили чужого
		if (al.ShootCounter<=0)
		{
			Score+=200;
			//создаем взрыв
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
		//прячем пулю
		bl.x=-24;
		bl.y=-24;
		//i--;
		//break;
		}
	}


	//уничтожаем зубастые цветки
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

			//создаем взрыв
			ANIM exp;
			exp.x=bl.x+bl.Rect.Right-bl.Rect.Left-10;
			exp.y=bl.y+bl.Rect.Bottom-bl.Rect.Top-15;

			exp.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
			exp.FrameLast=SPRITE_ARROWDESTROYEDEND;
			exp.FrameSpeed=0.2;

			exp.TimeLive=16;
			Different+=exp;


			Log.Write("уничтожили цветок");
		}
	}

	//уничтожаем обычных чужих
	for(j=0; j<Alien.Counter; j++)
	{
		MINDOBJ &bl=Bullet[i];
		PERSON &al=Alien[j];

		//если
		if
		(
		//оружие попал в чужого И чужой еще не загашенный
	    CheckUnionRects(al.Rect,bl.Rect) && ~al.Status & ALIEN::DEATH)
		{

		//уменьшаем силу чужого
		al.ShootCounter-=ArmsPower;

		//если силы чужого истощились
		if (al.ShootCounter<=0)
		{
			//создаем взрыв
			ANIM exp;
			exp.x=al.x+al.Rect.Right-al.Rect.Left-10;
			exp.y=al.y+al.Rect.Bottom-al.Rect.Top-15;

			exp.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
			exp.FrameLast=SPRITE_ARROWDESTROYEDEND;
			exp.FrameSpeed=0.2;

			exp.TimeLive=16;
			Different+=exp;

			//создаем очки
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

			//подлетает вверх
			if (!al.Speedy)		al.Speedy=-3;
		}

		//уничтожаем пулю
		Bullet.Del(&bl);

		i--;
		break;
		} //if
	} //for(j=0; j<Alien.Counter; j++)
 
 }// for(int i=0; i<Bullet.Counter; i++)
}
