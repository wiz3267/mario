//Mario.cpp
//примечание:
//в проекте перед файлом mario.cpp должен быть включены файлы KEYBOARD, TIMER
//чтобы создались предопределенные объекты

#include "stdafx.h"
//=================хедеры стандартных библиотек=================
#include <fcntl.H>

//======================мои хедеры==================
#include "Sound.h"
#include "IDSound.h"
#include "Keyboard.h"
#include "Timer.h"
#include "Mario.h"
#include "IDSprite.h"
#include "Mouse.h"
#include "SpriteEditor.h"
#include "Total.h"
//==================================================================

CString _S="";

/*******************************************
/**         Глобальные переменные       /**/
/******************************************/
/**/    SOUND   Sound;					/**/	//цифровой звук
/**/	SPRITE  Sprite(&scr,110);		/**/	//обычные спрайты
/**/	SPRITE  LvSpr(&scr,112);		/**/	//чем строится картинка
/**/	SPRITE  BigFont(&scr,28);		/**/	//большие буквы
/**/	LEVEL	Level(100,50,&LvSpr);	/**/	//уровень
/**/	SUPERMARIO Supermario;			/**/	//все об игре
/**/	MOUSE	Mouse;					/**/	//мышка
/******************************************/

int random(int n)
{
	return rand()%n;
}

int SUPERMARIO::InitForStartGame(int param)
{
//LevelNumber=0;

	//это randomize - инициализация генератора случайных чисел
	srand(GetTickCount());

	char str[7]="SOLDIR";

	/*int 
			LevelNumber,	//уровень, на который следует переместиться
			x,				//код кубика, который нужно искать на уровне
			Status;			//флаги
	*/
	//создаем таблицу перемещений
	SHUFFLE ShuffleTable[]=
	{
			{0,0,	SHUFFLE::ALWAYS},	//0
			{0,17,	SHUFFLE::CHGLEVEL}, //1
			{0,5,	SHUFFLE::ALWAYS},	//2
			{0,15,	SHUFFLE::ALWAYS},	//3
			{0,3,	SHUFFLE::ALWAYS},	//4
			{0,2,	SHUFFLE::ALLMAP},	//5
			{0,16,	SHUFFLE::ALWAYS},	//6
			{0,6,	SHUFFLE::ALWAYS},   //7
			{10,15,	SHUFFLE::CHGLEVEL},	//8
			{10,15,	SHUFFLE::BOSSLIVE | SHUFFLE::CHGLEVEL},//9
			{0,0,  SHUFFLE::ALWAYS}, //10
			{0,0,  SHUFFLE::ALWAYS}, //11
			{0,0,  SHUFFLE::ALWAYS}, //12
			{0,0,  SHUFFLE::ALWAYS}, //13
			{0,0,  SHUFFLE::ALWAYS}, //14
			{0,0,  SHUFFLE::ALWAYS}, //15
			{0,0,  SHUFFLE::ALWAYS}, //16
			{0,0,  SHUFFLE::ALWAYS}, //17
			{0,0,  SHUFFLE::ALWAYS}, //18
			{0,0,  SHUFFLE::NEXTLEVEL} //19
	};

	//2 -> 5
	//3 -> 15
	//4 -> 3
	//5 -> 2
	//6 -> 16
	//7 -> 6
	//8 -> 15 (с изменением уровня на 10)
	//9 -> 15 (с изменением уровня на 10 и флаг "BOSSLIVE")
	//10 -> 0
	//11 -> 0

	//как можно сделать
	// (1) <-> (2)
	// (3) -> (4)
	// (4) -> нельзя


	for(int i=0; i<SHUFFLE_COUNT; i++)
	  Shuffle[i]=ShuffleTable[i];

	ManymoneyCounter=0;	//счечик для многих монеток

	//устанавливаем атрибуты вывода текста
	{
		scr.setbkcolor(0);
		scr.setcolor(15);
	}

	//инициализируем классовые переменные
	{
		OldMarioX=0, OldMarioY=0;	//старые координаты марио
					//(используется при рестарте уровня)

		DoorOpenCounter=0,
		GAMECYCLE=TRUE;		//если GAME=FALSE, игра прекращается

		LevelStatus=LEVEL_UNDERWATER;
		BossLive=TRUE;		//босс пока жив
		MapCounter=0;		//число собранных карт
		Arms=ARROW;  		//оружие - кегли
		ArrowPower=1;		//сила стрелы - 1
		DaggerPower=2;		//сила ножичка - 2
		AxePower=3;			//сила топорика - 3
		SalivaPower=20;		//сила сопел
		ArmsPower=ArrowPower;//сила оружия - как у стрелы
		ProtectedCounter=0;	//счетчик, используем для организации защиты
		Lives=20;			//начальное число жизней
		Score=0;			//число набранных очков
		MoneyCounter=0;		//число собранных монеток (кристаллов)
		Time=Level.Time;	//текущее время
		GameMode=GAMEMODE_RESTARTLEVEL | GAMEMODE_LOADLEVEL;
		GAMEEXIT=FALSE;

		Timer1=0,
		Timer2=0;

		ShowExit=0;		//не показывать ексит
	}

	// идея - объединить все супервизоры в цепочку
	//создаем объекты-супервизоры чужих
	//{
		Rick.MakeSupervisor(&Sprite);		//марио
		Bullet.MakeSupervisor(&Sprite);		//оружие
		HeadSaliva.MakeSupervisor(&Sprite);	//кегли, которые пускает башка
		Toothflower.MakeSupervisor(&Sprite);//цветки
		Lift.MakeSupervisor(&Sprite);		//лифты
		Door.MakeSupervisor(&Sprite);		//двери
		Door1.MakeSupervisor(&Sprite);		//дверь перед Марио
		Different.MakeSupervisor(&Sprite);	//разное, никак не обрабатываемое
		Cleverobj.MakeSupervisor(&Sprite);	//дескриптор клевых объектов
		CleverAlien.MakeSupervisor(&Sprite);//умные чужие
		Boss.MakeSupervisor(&Sprite);		//босс (голова)
		Skeleton.MakeSupervisor(&Sprite);	//скелеты
		Movetxt.MakeSupervisor(&Sprite);
		Answer.MakeSupervisor(&LvSpr);
		SCORES.MakeSupervisor(&Sprite);
		Brick.MakeSupervisor(&Sprite);
		Money.MakeSupervisor(&Sprite);
		Prize.MakeSupervisor(&Sprite);
		Alien.MakeSupervisor(&Sprite);
		FireLine.MakeSupervisor(&Sprite);

	//}
	//создаем Mario
	{
		//уничтожаем рика
		Rick.DelAll();

		MARIO  ob;
//		PERSON  ob;

		ob.FrameFirst=SPRITE_RICKSTART;
		ob.FrameLast=SPRITE_RICKEND;

		ob.FrameSpeed=0.4;
		ob.SpriteIndex=SPRITE_RICKSTART;
		ob.RenewFrame();
		ob.x=Level.MarioX;
		ob.y=Level.MarioY;
		ob.Hot.Set(3,0,21,23);
		ob.Movement=PERSON::RIGHT;

		//создаем марио
		for(UINT TT=0;TT<PlayerCounter;TT++)
		{
			Rick += ob;
			ob.x+=20;
		}
	}

	//запускаем таймер
	{
		//Timer.Restart(50);
	}

	return 0;
}

void SUPERMARIO::prPuziri()
{
	//Марио пускают пузыри если флаг уровня - подводный
	if (LevelStatus & LEVEL_UNDERWATER)
	for(int i=0; i<Rick.Counter; i++)
	{
		ANIM &mr=Rick[i];
		if (mr.Status & MARIO_DEATH) continue;
		if ( random(30+int(abs(mr.Speedx)*2) ) > 28 )
		{
			MINDOBJ ob;
			MINDOBJ::GOING go[]=
			{
				{1,0,5+random(5)},
				{-1,0,5+random(5)}
			};

			MINDOBJ::FRAMING fr[]=
			{
				{SPRITE_BUBBLE1+random(3), 4},
				{SPRITE_BUBBLE1+random(3), 4},
				{SPRITE_BUBBLE1+random(3), 4}
			};

			ob.x=mr.x+5+random(10);
			ob.y=mr.y+7;
			ob.SpriteIndex=SPRITE_BUBBLE1+random(3);
			ob.Speedy=-1;
			ob.Acceleraty=-0.01-0.01*random(5);
			ob.AlwaysAnimate=TRUE;
			ob.TimeLive=200;
			CleverAlien.Add(ob, 2, go, 3, fr);
		}
	}
}

void SUPERMARIO::BirdsOtSten()
{
for(int i=0; i<CleverAlien.Counter; i++)
{
	MINDOBJ &br=CleverAlien[i];
	if  (br.SpriteIndex != SPRITE_BIRD1) continue;
	int c=0;	//была ли коллизия
	if (!chk_left(br,0)) br.Speedx=2+0.1*random(10),c=1;
	else if (!chk_right(br,0)) br.Speedx=-2-0.1*random(10),c=1;

	int x=int(br.x+12);
	int y1=int(br.y+br.Hot.Top-3);
	int y2=int(br.y+br.Hot.Bottom+3);
	if (Level.ReadXY(x,y1)) br.Speedy=0.7+0.1*random(10),c=1;
	else if (Level.ReadXY(x,y2)) br.Speedy=-0.7-0.1*random(10) ,c=1;

	if (br.x<0) br.Speedx=3.4,c=1;
	if (br.y<0) br.Speedy=1.7,c=1;
	if (br.x>Level.MaxX+320) br.Speedx=-3.4,c=1;
	if (br.y>Level.MaxY+200) br.Speedy=-1.7;

	//если была коллизия
	//if (c)
	//{
	//	if ( !random(6) ) br.Acceleraty=0.2;
	//else

	br.Acceleraty=0;
	//}

	if (br.Speedy>0)
	{
		br.SpriteIndex=SPRITE_BIRD1;
		br.FrameSpeed=0;
		//br.frame_num=0;
		br.Frame=br.framing[br.frame_num];
	}
	else
	{
		br.FrameSpeed=0;
	}
}
}

void SUPERMARIO::prMarioDeathOnShipah()
{
	for(int i=0; i<Rick.Counter; i++)
	{
		ANIM &rk=Rick[i];
		if (rk.Status & MARIO_DEATH) continue;
		if (chk_down(rk, PRICKLES))
		{
			//гасим марио
			rk.Speedx=0;
			rk.Speedy=-5;
			rk.Acceleratx=0;
			rk.Acceleraty=0.2;
			rk.FrameSpeed=0;
			rk.Status|=MARIO_DEATH;
			Sound.play(SND_EXORCISM);
			//Sound.play(SND_LAUGHT);
		}
	}
}

void SUPERMARIO::prMonetsChangePhase()
{
	//меняем образы монеток
	SPRITE::IMAGE src,dst;
	dst=LvSpr.GetImage(BRICK::MONEY);
	src=Sprite.GetImage(SPRITE_MONEYSTART+(Timer.GetTotalCounter()%20)/4);
	for(int i=0; i<24; i++)
	for(int j=0; j<24; j++)
	{
		dst.Write(i,j, src.Read(i,j) );
	}
}

void SUPERMARIO::prBricksRestore()
{
	//восстанавливаем кирпичи
	for(int i=0; i<Answer.Counter; i++)
	{
	ANIM & ar=Answer[i];

    if ( ar.TimeLive<3)
    {
	   switch(ar.SpriteIndex)
	   {
		case BRICK::BREAK:
        {
			Level.WriteXY(int(ar.x),int(ar.y),BRICK::BREAK);
			break;
		}

        case BRICK::BRICKSTAR:
		{
		//Level.WriteXY(ar.x,ar.y,5)
		//Level.WriteXY(ar.x,ar.y,72);
		Level.WriteXY(int(ar.x),int(ar.y),BRICK::ANSWER);
		break;
		}

		case BRICK::ANSWERMUSHROOM:
		case BRICK::ANSWER:
		{
			Level.WriteXY(int(ar.x),int(ar.y),5);
			break;
		}

		case BRICK::MANYMONEY:
		{

			if (!ManymoneyCounter) ManymoneyCounter=Time-14;
			if (ManymoneyCounter< Time)
				Level.WriteXY(int(ar.x),int(ar.y),BRICK::MANYMONEY);
			else
			{
				ManymoneyCounter=0;
				Level.WriteXY(int(ar.x),int(ar.y),5);
			}
		}
	}
	}
}
}

void SUPERMARIO::prShowDebugInfo()
{
	//если нужно выводить отладочную информация - расскоментируй
	/*
	scr<<cur(1,10)<<CleverAlien.Counter<<" - clever";
	scr<<cur(1,11)<<MOVEOBJ::TotalAnimatedObject<<" - total";
	scr<<cur(1,12)<<SCORES.Counter<<" - scores";
	scr<<cur(1,13)<<Different.Counter<<" - different";
	scr<<cur(1,14)<<Bullet.Counter<<" - bullet";
	scr<<cur(1,15)<<HeadSaliva.Counter<<" - HeadSaliva";
	*/	
}


void SUPERMARIO::prTurtleCikAlien()
{
	for (int i=0;i<Alien.Counter; i++)
    {
		ANIM& Tur=Alien[i];
        //если это не панцирь или панцирь стоит на месте
        if (Tur.SpriteIndex != SPRITE_TURTLEHOUSE ||
			Tur.Status & ALIEN::DEATH || !Tur.Speedx)
        {
            //продолжать
			continue;
        }

        for (int j=0; j<Alien.Counter; j++)
        {
			//панцирь сам себя убить не может!
            if (i==j) continue;

            //получаем ссылку на объект
            ANIM& al=Alien[j];

            //загашенный объект еще раз загасить нельзя
            if (al.Status & ALIEN::DEATH) continue;

            //если панцирь сбил чужого
            if ( CheckUnionRects(Tur.Rect, al.Rect) )
            {
				al.Status|=ALIEN::DEATH;
				al.FrameSpeed=0;
				al.Speedx=0;
				al.Speedy=-7;
                al.Acceleraty=0.3;
                Sound.play(SND_POP);
			}
		}
	}
}

void SUPERMARIO::prRememberOldMarioCoordinates()
{
	for(int i=0; i<Rick.Counter; i++)
	{
		ANIM &rk=Rick[i];
        if (rk.Status & MARIO_DEATH) continue;

        if  (
		!(GameMode & GAMEMODE_RESTARTLEVEL)	&&
		//не летит
		!rk.Speedy							&&
                        //его не тянет земля
		!rk.Acceleraty						&&
		 //внизу нет нет шипов
		!chk_down(rk, PRICKLES)				&&
        //есть земля под ногами
		Level.ReadXY(int(rk.x+12),int(rk.y+27))
		)
        {
			OldMarioX=int(rk.x);
			OldMarioY=int(rk.y);
        }
	}
}

void SUPERMARIO::prIfGameOver()
{
    //если закончились все жизни
	if (!Lives)
	{
		GAMECYCLE=FALSE;
		scr.clear();
		BIGSTRING s(&BigFont,"GAME OVER");
		s.Show(40,88);
		scr.update();
		scr.pause(70*5);

		//LevelNumber=0;
	}


	//если все марио уничтожились
	if (AllMarioDeath(Rick))
	{
		//уменьшаем жизни
		 Lives--;

		//даем знать системе, что надо рестартовать
		//уровень

		//если надо показать эффект, когда
		//загасится
		if (GameMode & GAMEMODE_SHOWEFFECT_IFDEATH)
		{
			GameMode ^= GAMEMODE_SHOWEFFECT_IFDEATH;
			//показываем эффект
			ColorEffect();
		}

		//если надо рестартовать уровень, когда
		//загасится
		if (GameMode & GAMEMODE_LOADLEVEL_IFDEATH)
		{
			GameMode ^= GAMEMODE_LOADLEVEL_IFDEATH;
			GameMode |= GAMEMODE_LOADLEVEL;
		}

		GameMode|=GAMEMODE_RESTARTLEVEL;

		//музыка играет снова
		//music(NORMAL_MUSIC);
	}
}


void SUPERMARIO::prBossSalivaDeathMario()
{
	for(int j=0; j<Rick.Counter; j++)
	{
		ANIM &rk = Rick[j];
		for(int i=0; i<HeadSaliva.Counter; i++)
		{
			ANIM &ob = HeadSaliva[i];
			//если кегли коснулись марио
			if
			(
				~rk.Status & MARIO_DEATH &&
				~rk.Status & MARIO_PROTECTED &&
				CheckUnionRects(rk.Rect, ob.Rect)
			)

			{
				rk.Status |= MARIO_DEATH;
				rk.Set(rk.x,rk.y,0,-5,0,0.2);
				Sound.play(SND_LAUGHT);

				GameMode |= GAMEMODE_LOADLEVEL_IFDEATH
				| GAMEMODE_SHOWEFFECT_IFDEATH;

				break;
			}

				//уничтожаем кегли
			bool k=ob.x<-20 || ob.y> ob.Lim.Bottom;
			if ( ! chk_all(ob,0) || k)
			{
				//показываем, как разрушаются кегли
				if (!k)
				{
				
				ANIM ib;
				ib=ob;
				ib.Set(ob.x,ob.y,0,0,0,0);
				ib.FrameFirst=SPRITE_ARROWDESTROYEDSTART;
				ib.FrameLast=SPRITE_ARROWDESTROYEDEND;
				ib.FrameSpeed=0.2;
				ib.TimeLive=15;
				Different+=ib;


				Sound.play(SND_FIRE);
				}
				
				HeadSaliva.Del(i);
				i--;
				continue;
			}
		}
	}
}


void SUPERMARIO::prBossSendSaliveAndKeepAtMario()
{
	for(int i=0; i<Boss.Counter; i++)
	{
		MINDOBJ &al=Boss[i];
		ANIM &rk=Rick[0];

		//чтобы была близка к марио
		if ( al.x-rk.x<90 )
		{
			al.x+=3;
		}
		if ( al.x-rk.x>144 )
		{
			al.x-=3;
		}

		if ( al.Frame.Fase == SPRITE_HEAD1)
		{

			//иногда пускает кегли
			if (!HeadSaliva.Counter)
			{

				Sound.play(SND_POP);

				PERSON ob;
				ob.x=al.x;
				ob.y=al.y+10;
				ob.FrameFirst=SPRITE_SALIVA1;
				ob.FrameLast=SPRITE_SALIVA2;
				ob.FrameSpeed=0.3;
				ob.SpriteIndex=SPRITE_SALIVA1;
				ob.Speedx=-2.5;
				ob.Speedy=1.2;

				ob.Hot.Set(5,8,14,11);

				ob.Movement=PERSON::LEFT;
				ob.AlwaysAnimate=true;

				HeadSaliva+=ob;

				ob.Speedx=-1.5;
				ob.Speedy=1.2;
				HeadSaliva+=ob;

				if (random(2))
				{
					ob.Speedx=-1.7;
					ob.Speedy=1.4;
					HeadSaliva+=ob;
				}
			}
		}
	}
}

void SUPERMARIO::prBricksNudgePrize()
{
	//кирпичи могут подталкивать призы
	for(int i=0;i<Prize.Counter;i++)
	for(int j=0;j<Answer.Counter;j++)
	{
		ANIM & pr=Prize[i];
		ANIM & aw=Answer[j];
		if (aw.SpriteIndex != BRICK::ANSWERMUSHROOM &&
		CheckUnionRects(pr.Rect,aw.Rect) != FALSE)
		{
			pr.Speedy=-3;
		}
	}
}

void SUPERMARIO::prLiftUpDown()
{
	for(int i=0;i<Lift.Counter;i++)
	{
		ANIM &lf=Lift[i];
		lf.RenewXY();
		lf.RenewRect();
		lf.TimeLive--;
		if (lf.TimeLive<3)
		{
			lf.TimeLive=140;
			lf.Speedy*=-1;
			lf.Speedx*=-1;
		}
	}
}

void SUPERMARIO::prForMarioProtected()
{
	for(int i=0; i<Rick.Counter; i++)
	{
		ANIM & rk=Rick[i];
		//если время истекло И марио защищенный, снимаем защиту
		if (!ProtectedCounter && rk.Status & MARIO_PROTECTED)
		{
			rk.Status&=~MARIO_PROTECTED;
			if (Sound.GetCurrent() != SND_GHOTIC) Sound.play(SND_GHOTIC);
		}
	}
}

void SUPERMARIO::prMonetsTimeEndTimeLiveAndScoreCreate()
{
	for(int i=0; i<Money.Counter; i++)
	{
		ANIM & ob=Money[i];
        if (ob.TimeLive<3)
        {
			ANIM sc;
            sc.Set(ob.x, ob.y+12, 0, -1);
			CreateScore(200,SCORES,sc);
			//sc.TimeLive=70;
            Score+=200;
        }
	}
}


void SUPERMARIO::prMarioDeathOnFlower()
{
	for(int i=0;i<Toothflower.Counter;i++)
	{
		ANIM & tf=Toothflower[i];
		for(int j=0; j<Rick.Counter; j++)
		{
			PERSON & rk=Rick[j];
			if
				(
			~rk.Status & MARIO_DEATH &&
			~rk.Status & MARIO_PROTECTED &&
			CheckUnionRects(rk.Rect, tf.Rect)
			)
			{
				rk.Status |= MARIO_DEATH;
		
				rk.Movement=rk.FLIP_VERT;

				rk.Set(rk.x,rk.y,0,-5,0,0.2);
				rk.Speedy=-3;
				Sound.play(SND_LAUGHT);

			}
		}
    }
}

void SUPERMARIO::prFlowersUpDown()
{
	for(int i=0;i<Toothflower.Counter;i++)
	{
		ANIM & tf=Toothflower[i];
		if (Level.ReadXY(int(tf.x+12), int(tf.y+24)) )
		{
			tf.Speedy=-0.1*random(60);
			tf.Acceleraty=0.2;
		}

		/*
		if (tf.TimeLive<5)
		{
			tf.TimeLive=90;
			//если разница между координатами марио и цветка
			//меньше чем 24*2 и цветок находится в нижней точке
			//затормозить его
			if ( (abs(Rick[0].x-tf.x) < 38 ) && tf.Speedy>=0)
			{
				tf.Speedy=0;
			}
			//иначе цветок идет вверх
			else
			{
				tf.Speedy*=-1;
				//если скорость равна нулю
				//направить ее вверх
				if (!tf.Speedy)
					tf.Speedy=-0.5;
			}
		}*/
	}
}

void SUPERMARIO::prMarioFlyDownCleverobj()
{
	for(int i=0; i<Rick.Counter; i++)
	{
		PERSON &rk=(PERSON&)Rick[i];
		MYRECT Rt=rk.Rect;
		Rt.Bottom+=24;
		Rt.Top+=24;
		for(int j=0; j<Cleverobj.Counter; j++)
		{
			MINDOBJ &cl=Cleverobj[j];
			if ( !CheckUnionRects(Rt, cl.Rect) &&
			//abs(rk.x-cl.x)>20 &&
			rk.Status & MARIO_CLAMMY &&
			rk.Link==j)
			{
				rk.Status ^= MARIO_CLAMMY;
			}
		}
	}
}


void SUPERMARIO::prMarioPositionerOnCleverobject()
{
	for(int i=0; i<Rick.Counter; i++)
    {
        MARIO &rk=(MARIO&)Rick[i];
        //если марио прилеплен
        if (rk.Status & MARIO_CLAMMY)
        {
            MINDOBJ& cl=Cleverobj[rk.Link];

            //запоминаем старое положение марио
            int xOld=int(rk.x);
            int yOld=int(rk.y);

			//устанавливаем его новые координаты
            // (ставим на мостик)
			rk.x=cl.x+rk.ClammyX;
            rk.y=cl.y-rk.Hot.Bottom+cl.Hot.Top;
			rk.Speedy=0;
            rk.Acceleraty=0;

            rk.RenewRect();

            //если не смогли поставить
            if ( !chk_all(rk,0) )
            {
                rk.x=xOld;
                rk.y=yOld;

                rk.RenewRect();

                //теперь марио не прилип
                //rk.Status &= ~MARIO_CLAMMY;
                //Debug(" Ok ?");
			}
		}
	}
}


void SUPERMARIO::prMarioClammyToLift()
{
	for(int i=0;i<Rick.Counter;i++)
    {
		ANIM &rk=Rick[i];
        //если марио мертвый продолжать
        if (rk.Status & MARIO_DEATH) continue;

        for(int j=0; j<Lift.Counter; j++)
        {
            ANIM &lf=Lift[j];
            int deltay=int(lf.y-rk.y);
            int deltax=int(abs(rk.x-lf.x));
            //если падает вниз и ноги недалеко от лифта
            //и марио в пустоте
            if ( rk.y>=0 &&
				 deltay>=24-8 && deltay<24+4 && deltax<24 )
			{
                int old_y=int(rk.y);
				rk.y=lf.y-24;
                rk.RenewRect();
				if (chk_all(rk,0))
                {
	                rk.Speedy=0;
	                rk.Acceleraty=0;
                }
                else { rk.y=old_y; rk.RenewRect(); }
            }
        }
	}
}

//если под ногами Марио обрущиваюший кирпич - обрушаем его
void SUPERMARIO::prMarioDownsBrickDestroy()
{
	for(int i=0; i<Rick.Counter; i++)
	{
        MOVEOBJ &rk=Rick[i];
		if (rk.Status & MARIO_DEATH) continue;

        int x=int(rk.x+12),
			y=int(rk.y+27),
			a=Level.ReadXY(x,y);
         //обрушиваем кирпичик
         if (a & LEVEL::COLLAPSE)
         {
            int a;
            if (x/24 % 2) a=-24;
            else a=24;

            Level.WriteXY(x,y,0);
            Level.WriteXY(x+a,y,0);
            x=x-x%24;
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


            Sound.play(SND_FIRE, SOUND::NOSTOP);

			//скорость падает до нуля
			rk.Speedy=0;
			//ускорение падает до нуля
            rk.Acceleraty=0;
         }
	}
}


//визуальный эффект на экране
void SUPERMARIO::prChangeEffect()
{
	//требуется выполнить эффект перехода на другой экран?
	if (ChangeEffect)
	{
		ChangeEffect++;

		if (ChangeEffect>2)
		{
			BYTE screen_old[320*200]; //старый экран

			//записанную картинку старого уровня копируем в screen_old
			memcpy(screen_old, scr.SavedDoubleBuffer,320*200);

			//текущую картинку из дублирующего буфера копируем в SavedDoubleBuffer
			scr.SaveScreen();	//по идее новый экран сохраняем

			scr.clear();
			//memcpy(scr.DoubleBuffer, screen_old, 320*200);
			scr.update();
			for(int i=0; i<200;i++)
			{
				/*for(int i=0; i<100; i++)
				{
					int rnd=(rand()*2)%(320*200);
					scr.DoubleBuffer[rnd]=scr.SavedDoubleBuffer[rnd];
				}*/
				memcpy(scr.DoubleBuffer+i*320,scr.SavedDoubleBuffer+i*320,320);
				scr.update();
			
			}
			ChangeEffect=0;
		}
	}
}

//обновляем все у умных объектов
void SUPERMARIO::prCleverobjRefresh()
{
	for(int i=0; i<Cleverobj.Counter; i++)
	{
		MINDOBJ *cl=&Cleverobj[i];
		cl->RenewXY();
		cl->RenewRect();
		cl->RenewFrame();
	}
}

void SUPERMARIO::prMarioRenewXY()
{
	//обновляем координаты Mario
	for (int i=0; i<Rick.Counter; i++)
	{
		Rick[i].RenewXY();
	}
}

//***************************************************
//синхронизируемся (ждем когда счетчик-таймер 
//перейдет из состояния 0 в состояние 1)
//этот счетчик инкрементирует другой поток
//***************************************************
void SUPERMARIO::prSynhronization()
{
	//scr<<cur(10,11)<<Timer.Counter;
	//если не успели
	if (Timer.Counter)
	{
		//выводим знак вопроса (отладка)
		//scr<<cur(0,0)<<'?';
	}
	else
	{
		while(Timer.Counter==0)
		{
			Sleep(1);
		}
	}
	Timer.Counter=0;
}

//двигается фон (спрайты воды и огня)
void SUPERMARIO::prScrollBricks()
{
	static int W;
	W++;
	if (W&1)
	{
		LvSpr.Scroll(41, SPRITE::SCROLL_RIGHT);
		LvSpr.Scroll(50, SPRITE::SCROLL_RIGHT);
		LvSpr.Scroll(56, SPRITE::SCROLL_RIGHT,1);
		LvSpr.Scroll(57, SPRITE::SCROLL_RIGHT,1);
	}
}


void SUPERMARIO::prShowFPS() //показать FPS
{
	//обновляем экран
	Timer.Counter=0;
	static int lastTick=0,frame=0,fps=0;

	frame++;

	if (frame==25)
	{
		double tick=GetTickCount()-lastTick;
		fps=int(frame*1000.0/(tick+0.00001));
		lastTick=GetTickCount();
		frame=0;

		//if (Keyb[KEY_1]) 
	}
	scr<<cur(0,24)<<"FPS="<<fps;
}

//============= 'game' это, собственно, сама игра ==================
void SUPERMARIO::Game()
{
	InitForStartGame(0);
	//music(NORMAL_MUSIC);
	while (GAMECYCLE)	//цикл игры
	{
	//I. построение изображения 
	MOVEOBJ::TotalAnimatedObject=0;
	prMonetsChangePhase();
	prPuziri();
	prBuildGamePicture();
	prShowDebugInfo();
	//II. логика игры
	BirdsOtSten();			//птички отталкиваются от стен
	SkeletonCollect();		//собираем скелетов
	prCleverobjRefresh();	//обновляем все у умных объектов
	prMarioDeathOnShipah();	//марио гасится на шипах
	prForMarioProtected();	//чтобы марио был защищенным
	prPrizeCatch(Rick, Prize);//призы не проходят сквозь стенки и марио ловит призы
	prBricksNudgePrize();	//кирпичи могут подталкивать призы
	prBricksRestore();		//восстанавливаем кирпичи
	prTurtleCikAlien();		//черепаха сбивает других чужих
	prMonetsTimeEndTimeLiveAndScoreCreate();//надо создать очки когда монетка пропадает
	prIfGameOver();			//если конец игры 
	prBossSalivaDeathMario();// кегли башки гасят марио и не пролетают через стены
	prBossSendSaliveAndKeepAtMario();//башка пускает "кегли" и находится вблизи от марио
	ArmsKillAlien();		// оружие убивает чужих
	prLiftUpDown();			//меняем направление лифта и обновляем его координаты
	prMarioDeathOnFlower();//марио гасится на зубастых цветках
	prFlowersUpDown();		//поднимаем и опускаем зубастые цветки
	MindobjFunctions(Rick, Cleverobj);//различные функции
	MindobjFunctions(Rick, CleverAlien);//предусмотренные для Mindobj
	prMarioFlyDownCleverobj();	//марио слетает с клевых объектов
	prMarioPositionerOnCleverobject();//позиционируем Mario  на клевый объект
	prMarioRenewXY();//обновляем координаты Mario
	//если ноги марио близко к лифту, марио падает
	prMarioClammyToLift();	//на лифт и его ускорение приравнять к нулю
	prMarioDownsBrickDestroy();//обрушиваем кирпичи под ногами у марио
	prArmsCollisionWithWall();//оружие сталкивается со стенами *
	prRememberOldMarioCoordinates();//запоминаем старые координаты Mario
	prKeyboardProcess();		//обработка НАЖАТИЙ клавиш 
	GameModesTreat();		//обрабатываем ситуацию загрузки и рестарта уровня режимы игры
	if (DoorOpenCounter) DoorOpenCounter--;	//чтобы дверь успела открыться
	prScrollBricks();		//двигается фон (спрайты воды и огня)
	prChangeEffect();		//эффект перехода на другой экран
	prShowFPS();			//показать FPS
	prSynhronization();		//синхронизируемся (ждем когда таймер станет равным 1)
	
	ShowLevelNumberTimeCounter++;

	if (ShowLevelNumberTimeCounter<100)
	{
		
		Msg("  УРОВЕНЬ    ", 9, MSG_NOUPDATE);
		

		/*if (LevelNumber<40)
		{
			scr.putNumb(LevelNumber/4+1,1);
			scr<< '-';
			scr.putNumb(LevelNumber%4+1,1);
		}
		else
		{
			scr.putNumb(LevelNumber);
		}*/
		scr.putNumb(LevelNumber);

	}
	
	static int ShowLog=0;
	//выводим изображение на экран из DoubleBuffer
	if (Keyb[KEY_L] && Keyb[KEY_LEFTCTRL]) 
	{
		Keyb^KEY_L;
		ShowLog^=1;
	}
	
	if (ShowLog) 
	{
		//сжимаем картинку
		for(int i=0; i<100; i++)
		{
			memcpy(scr.DoubleBuffer+i*320, scr.DoubleBuffer+i*2*320,320);
		}
		
		scr.rectangle(0,100,320,100,0);
		Log.Show();
	}
	scr.update();			
	} //конец цикла while
}//конец функции game

//функция main() пустая
//хинт: программа рантьше стартовала из конструктора класса SUPERMARIO (это под DOS)
//      в данной версии стартует по другому (создается поток и из него уже)
void main()
{
	Sleep(1000);
}


void SUPERMARIO::DrawMenu()
{
	Sound.InitDirectSound();

	//режим чтения - двоичный (это важно!!!)
	//иначе файл может не дочитываться до конца, если встретится служебный
	//символ конца файла (код не помню)
	//не знаю насколько это актуально для версии под Windows
	//для DOS'a очень важно и актуально
	_fmode=O_BINARY;

	scr.LoadPaletteFromFile("graph\\palette.dat");

	SPRITE spr(&scr,1);
	SPRITE::IMAGE im;
	im.ID=2;
	im.Attribute=0;
	spr.LoadSpriteform("graph\\zast.sp0",im);
	im=spr.GetImage(2);
//	spr.Show( (320-im.Len)/2,(200-im.Hei)/2,2);
	scr.update();


	LoadSprites();		//загружаем спрайты
	LoadSounds();		//звуки
	LoadMusic();		//музыку
	


	//назначаем по умолчанию клавиши для игроков
	//первый игрок
	player[0].Left	= KEY_LEFT;
	player[0].Right	= KEY_RIGHT;
	player[0].Up	= KEY_UP;
	player[0].Down	= KEY_DOWN;
	player[0].Fire	= KEY_SPACE;
	player[0].Run	= KEY_LEFTCTRL;

	//второй игрок
	player[1].Left	= KEY_Z;
	player[1].Right	= KEY_C;
	player[1].Up	= KEY_S;
	player[1].Down	= KEY_X;
	player[1].Fire	= KEY_A;
	player[1].Run	= KEY_LEFTSHIFT;

	//третий игрок
	player[2].Left	= KEY_PAD4;
	player[2].Right	= KEY_PAD6;
	player[2].Up	= KEY_PAD8;
	player[2].Down	= KEY_PAD5;
	player[2].Fire	= KEY_PAD0;
	player[2].Run	= KEY_PAD7;

	//вычисляем скорость компьютера
	/*
	{
		FunctionSpeed();
		return;
	}
	*/
	scr.clear();

	//прерываем проигрывание музыки
	//MidiStop();

	Sound.play(SND_ZASTAVKA);
	//Sound.play(SND_GHOTIC_FAST);

	//обработка того, что возвратило меню
	while (1) 
	{
		if (GAMEEXIT==TRUE) return;

		int menu_index=MenuMain();
		//ONE PLAYER
		if (menu_index==1)	
		{
			PlayerCounter=1;	//один игрок
			
			/*for(int i=0; i<127; i++) 
			{
				//scr.wait();
				scr.DecrementPalette();
				scr.DecrementPalette();
				while (Timer.Counter==0) Sleep(1);
				Timer.Counter=0;
			}*/

			scr.clear();
			scr.update();
			//scr.LoadPaletteFromFile("graph\\palette.dat");
			Game();
			Sound.play(SND_ZASTAVKA);
			continue;
		}

		//TWO PLAYER
		if (menu_index==2)	
		{
			PlayerCounter=2;	//два игрока
			Game();
			Sound.play(SND_ZASTAVKA);
			continue;
		}

		//THREE PLAYER
		if (menu_index==3)	
		{
			PlayerCounter=3;	//два игрока
			Game();
			Sound.play(SND_ZASTAVKA);
			continue;
		}

		//CONFIGURATION
		if (menu_index==4)	
		{
			/*scr.clear();
			scr.update();

			char pass[]={ KEY_7, KEY_2,KEY_1,KEY_5,0 };

			int wrong=0;
			scr << cur(13,9);
			scr << "ВВЕДИТЕ ПАРОЛЬ";

			scr << cur(16, 12);
			scr.rectangle(15*8,11*8,9*8,3*8,9);
			scr.update();
			for(UINT i=0;i<strlen(pass); i++)
			{
				if (Keyb.ReadScan() != pass[i])
					wrong=1;
				scr << '*';
				scr.update();
			}
		
			if (wrong)
			{
				Msg("  Пароль неверен ",2);
				scr.update();
				scr.pause(70*3);
				continue;
			}
			*/
			int mn=MenuConfiguration();
			//continue;
		}


		//Level editor
		if (menu_index==5)
		{
			scr.clear();
			//Sound.play(SND_LEVEL1);
			LevelNumber=Level.Editor(LevelNumber);
			
			continue;
		}

		//Sprite editor
		if (menu_index==6)
		{
			//scr.clear();
			//Msg(" РЕДАКТОР В СТАДИИ РАЗРАБОТКИ ",3);
			//scr.update();
			SPRITEEDITOR se;
			se.Editor(&Sprite, 1);
			LoadSprites();
			
			//Keyb.ReadScan();
		}

		//EXIT 
		if (menu_index==7)
		{
			//нужно сделать корректный выход из игры!!!
			//в данном случае мы не освобождаем DirectX
			//exit(1);
			//break;
			return;
		}
	}

}
