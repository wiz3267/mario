//Mario.cpp
//����������:
//� ������� ����� ������ mario.cpp ������ ���� �������� ����� KEYBOARD, TIMER
//����� ��������� ���������������� �������

#include "stdafx.h"
//=================������ ����������� ���������=================
#include <fcntl.H>

//======================��� ������==================
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
/**         ���������� ����������       /**/
/******************************************/
/**/    SOUND   Sound;					/**/	//�������� ����
/**/	SPRITE  Sprite(&scr,110);		/**/	//������� �������
/**/	SPRITE  LvSpr(&scr,112);		/**/	//��� �������� ��������
/**/	SPRITE  BigFont(&scr,28);		/**/	//������� �����
/**/	LEVEL	Level(100,50,&LvSpr);	/**/	//�������
/**/	SUPERMARIO Supermario;			/**/	//��� �� ����
/**/	MOUSE	Mouse;					/**/	//�����
/******************************************/

int random(int n)
{
	return rand()%n;
}

int SUPERMARIO::InitForStartGame(int param)
{
//LevelNumber=0;

	//��� randomize - ������������� ���������� ��������� �����
	srand(GetTickCount());

	char str[7]="SOLDIR";

	/*int 
			LevelNumber,	//�������, �� ������� ������� �������������
			x,				//��� ������, ������� ����� ������ �� ������
			Status;			//�����
	*/
	//������� ������� �����������
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
	//8 -> 15 (� ���������� ������ �� 10)
	//9 -> 15 (� ���������� ������ �� 10 � ���� "BOSSLIVE")
	//10 -> 0
	//11 -> 0

	//��� ����� �������
	// (1) <-> (2)
	// (3) -> (4)
	// (4) -> ������


	for(int i=0; i<SHUFFLE_COUNT; i++)
	  Shuffle[i]=ShuffleTable[i];

	ManymoneyCounter=0;	//������ ��� ������ �������

	//������������� �������� ������ ������
	{
		scr.setbkcolor(0);
		scr.setcolor(15);
	}

	//�������������� ��������� ����������
	{
		OldMarioX=0, OldMarioY=0;	//������ ���������� �����
					//(������������ ��� �������� ������)

		DoorOpenCounter=0,
		GAMECYCLE=TRUE;		//���� GAME=FALSE, ���� ������������

		LevelStatus=LEVEL_UNDERWATER;
		BossLive=TRUE;		//���� ���� ���
		MapCounter=0;		//����� ��������� ����
		Arms=ARROW;  		//������ - �����
		ArrowPower=1;		//���� ������ - 1
		DaggerPower=2;		//���� ������� - 2
		AxePower=3;			//���� �������� - 3
		SalivaPower=20;		//���� �����
		ArmsPower=ArrowPower;//���� ������ - ��� � ������
		ProtectedCounter=0;	//�������, ���������� ��� ����������� ������
		Lives=20;			//��������� ����� ������
		Score=0;			//����� ��������� �����
		MoneyCounter=0;		//����� ��������� ������� (����������)
		Time=Level.Time;	//������� �����
		GameMode=GAMEMODE_RESTARTLEVEL | GAMEMODE_LOADLEVEL;
		GAMEEXIT=FALSE;

		Timer1=0,
		Timer2=0;

		ShowExit=0;		//�� ���������� �����
	}

	// ���� - ���������� ��� ����������� � �������
	//������� �������-����������� �����
	//{
		Rick.MakeSupervisor(&Sprite);		//�����
		Bullet.MakeSupervisor(&Sprite);		//������
		HeadSaliva.MakeSupervisor(&Sprite);	//�����, ������� ������� �����
		Toothflower.MakeSupervisor(&Sprite);//������
		Lift.MakeSupervisor(&Sprite);		//�����
		Door.MakeSupervisor(&Sprite);		//�����
		Door1.MakeSupervisor(&Sprite);		//����� ����� �����
		Different.MakeSupervisor(&Sprite);	//������, ����� �� ��������������
		Cleverobj.MakeSupervisor(&Sprite);	//���������� ������ ��������
		CleverAlien.MakeSupervisor(&Sprite);//����� �����
		Boss.MakeSupervisor(&Sprite);		//���� (������)
		Skeleton.MakeSupervisor(&Sprite);	//�������
		Movetxt.MakeSupervisor(&Sprite);
		Answer.MakeSupervisor(&LvSpr);
		SCORES.MakeSupervisor(&Sprite);
		Brick.MakeSupervisor(&Sprite);
		Money.MakeSupervisor(&Sprite);
		Prize.MakeSupervisor(&Sprite);
		Alien.MakeSupervisor(&Sprite);
		FireLine.MakeSupervisor(&Sprite);

	//}
	//������� Mario
	{
		//���������� ����
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

		//������� �����
		for(UINT TT=0;TT<PlayerCounter;TT++)
		{
			Rick += ob;
			ob.x+=20;
		}
	}

	//��������� ������
	{
		//Timer.Restart(50);
	}

	return 0;
}

void SUPERMARIO::prPuziri()
{
	//����� ������� ������ ���� ���� ������ - ���������
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
	int c=0;	//���� �� ��������
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

	//���� ���� ��������
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
			//����� �����
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
	//������ ������ �������
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
	//��������������� �������
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
	//���� ����� �������� ���������� ���������� - ��������������
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
        //���� ��� �� ������� ��� ������� ����� �� �����
        if (Tur.SpriteIndex != SPRITE_TURTLEHOUSE ||
			Tur.Status & ALIEN::DEATH || !Tur.Speedx)
        {
            //����������
			continue;
        }

        for (int j=0; j<Alien.Counter; j++)
        {
			//������� ��� ���� ����� �� �����!
            if (i==j) continue;

            //�������� ������ �� ������
            ANIM& al=Alien[j];

            //���������� ������ ��� ��� �������� ������
            if (al.Status & ALIEN::DEATH) continue;

            //���� ������� ���� ������
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
		//�� �����
		!rk.Speedy							&&
                        //��� �� ����� �����
		!rk.Acceleraty						&&
		 //����� ��� ��� �����
		!chk_down(rk, PRICKLES)				&&
        //���� ����� ��� ������
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
    //���� ����������� ��� �����
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


	//���� ��� ����� ������������
	if (AllMarioDeath(Rick))
	{
		//��������� �����
		 Lives--;

		//���� ����� �������, ��� ���� ������������
		//�������

		//���� ���� �������� ������, �����
		//���������
		if (GameMode & GAMEMODE_SHOWEFFECT_IFDEATH)
		{
			GameMode ^= GAMEMODE_SHOWEFFECT_IFDEATH;
			//���������� ������
			ColorEffect();
		}

		//���� ���� ������������ �������, �����
		//���������
		if (GameMode & GAMEMODE_LOADLEVEL_IFDEATH)
		{
			GameMode ^= GAMEMODE_LOADLEVEL_IFDEATH;
			GameMode |= GAMEMODE_LOADLEVEL;
		}

		GameMode|=GAMEMODE_RESTARTLEVEL;

		//������ ������ �����
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
			//���� ����� ��������� �����
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

				//���������� �����
			bool k=ob.x<-20 || ob.y> ob.Lim.Bottom;
			if ( ! chk_all(ob,0) || k)
			{
				//����������, ��� ����������� �����
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

		//����� ���� ������ � �����
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

			//������ ������� �����
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
	//������� ����� ������������ �����
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
		//���� ����� ������� � ����� ����������, ������� ������
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
			//���� ������� ����� ������������ ����� � ������
			//������ ��� 24*2 � ������ ��������� � ������ �����
			//����������� ���
			if ( (abs(Rick[0].x-tf.x) < 38 ) && tf.Speedy>=0)
			{
				tf.Speedy=0;
			}
			//����� ������ ���� �����
			else
			{
				tf.Speedy*=-1;
				//���� �������� ����� ����
				//��������� �� �����
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
        //���� ����� ���������
        if (rk.Status & MARIO_CLAMMY)
        {
            MINDOBJ& cl=Cleverobj[rk.Link];

            //���������� ������ ��������� �����
            int xOld=int(rk.x);
            int yOld=int(rk.y);

			//������������� ��� ����� ����������
            // (������ �� ������)
			rk.x=cl.x+rk.ClammyX;
            rk.y=cl.y-rk.Hot.Bottom+cl.Hot.Top;
			rk.Speedy=0;
            rk.Acceleraty=0;

            rk.RenewRect();

            //���� �� ������ ���������
            if ( !chk_all(rk,0) )
            {
                rk.x=xOld;
                rk.y=yOld;

                rk.RenewRect();

                //������ ����� �� ������
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
        //���� ����� ������� ����������
        if (rk.Status & MARIO_DEATH) continue;

        for(int j=0; j<Lift.Counter; j++)
        {
            ANIM &lf=Lift[j];
            int deltay=int(lf.y-rk.y);
            int deltax=int(abs(rk.x-lf.x));
            //���� ������ ���� � ���� �������� �� �����
            //� ����� � �������
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

//���� ��� ������ ����� ������������ ������ - �������� ���
void SUPERMARIO::prMarioDownsBrickDestroy()
{
	for(int i=0; i<Rick.Counter; i++)
	{
        MOVEOBJ &rk=Rick[i];
		if (rk.Status & MARIO_DEATH) continue;

        int x=int(rk.x+12),
			y=int(rk.y+27),
			a=Level.ReadXY(x,y);
         //���������� ��������
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

			//�������� ������ �� ����
			rk.Speedy=0;
			//��������� ������ �� ����
            rk.Acceleraty=0;
         }
	}
}


//���������� ������ �� ������
void SUPERMARIO::prChangeEffect()
{
	//��������� ��������� ������ �������� �� ������ �����?
	if (ChangeEffect)
	{
		ChangeEffect++;

		if (ChangeEffect>2)
		{
			BYTE screen_old[320*200]; //������ �����

			//���������� �������� ������� ������ �������� � screen_old
			memcpy(screen_old, scr.SavedDoubleBuffer,320*200);

			//������� �������� �� ������������ ������ �������� � SavedDoubleBuffer
			scr.SaveScreen();	//�� ���� ����� ����� ���������

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

//��������� ��� � ����� ��������
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
	//��������� ���������� Mario
	for (int i=0; i<Rick.Counter; i++)
	{
		Rick[i].RenewXY();
	}
}

//***************************************************
//���������������� (���� ����� �������-������ 
//�������� �� ��������� 0 � ��������� 1)
//���� ������� �������������� ������ �����
//***************************************************
void SUPERMARIO::prSynhronization()
{
	//scr<<cur(10,11)<<Timer.Counter;
	//���� �� ������
	if (Timer.Counter)
	{
		//������� ���� ������� (�������)
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

//��������� ��� (������� ���� � ����)
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


void SUPERMARIO::prShowFPS() //�������� FPS
{
	//��������� �����
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

//============= 'game' ���, ����������, ���� ���� ==================
void SUPERMARIO::Game()
{
	InitForStartGame(0);
	//music(NORMAL_MUSIC);
	while (GAMECYCLE)	//���� ����
	{
	//I. ���������� ����������� 
	MOVEOBJ::TotalAnimatedObject=0;
	prMonetsChangePhase();
	prPuziri();
	prBuildGamePicture();
	prShowDebugInfo();
	//II. ������ ����
	BirdsOtSten();			//������ ������������� �� ����
	SkeletonCollect();		//�������� ��������
	prCleverobjRefresh();	//��������� ��� � ����� ��������
	prMarioDeathOnShipah();	//����� ������� �� �����
	prForMarioProtected();	//����� ����� ��� ����������
	prPrizeCatch(Rick, Prize);//����� �� �������� ������ ������ � ����� ����� �����
	prBricksNudgePrize();	//������� ����� ������������ �����
	prBricksRestore();		//��������������� �������
	prTurtleCikAlien();		//�������� ������� ������ �����
	prMonetsTimeEndTimeLiveAndScoreCreate();//���� ������� ���� ����� ������� ���������
	prIfGameOver();			//���� ����� ���� 
	prBossSalivaDeathMario();// ����� ����� ����� ����� � �� ��������� ����� �����
	prBossSendSaliveAndKeepAtMario();//����� ������� "�����" � ��������� ������ �� �����
	ArmsKillAlien();		// ������ ������� �����
	prLiftUpDown();			//������ ����������� ����� � ��������� ��� ����������
	prMarioDeathOnFlower();//����� ������� �� �������� �������
	prFlowersUpDown();		//��������� � �������� �������� ������
	MindobjFunctions(Rick, Cleverobj);//��������� �������
	MindobjFunctions(Rick, CleverAlien);//��������������� ��� Mindobj
	prMarioFlyDownCleverobj();	//����� ������� � ������ ��������
	prMarioPositionerOnCleverobject();//������������� Mario  �� ������ ������
	prMarioRenewXY();//��������� ���������� Mario
	//���� ���� ����� ������ � �����, ����� ������
	prMarioClammyToLift();	//�� ���� � ��� ��������� ���������� � ����
	prMarioDownsBrickDestroy();//���������� ������� ��� ������ � �����
	prArmsCollisionWithWall();//������ ������������ �� ������� *
	prRememberOldMarioCoordinates();//���������� ������ ���������� Mario
	prKeyboardProcess();		//��������� ������� ������ 
	GameModesTreat();		//������������ �������� �������� � �������� ������ ������ ����
	if (DoorOpenCounter) DoorOpenCounter--;	//����� ����� ������ ���������
	prScrollBricks();		//��������� ��� (������� ���� � ����)
	prChangeEffect();		//������ �������� �� ������ �����
	prShowFPS();			//�������� FPS
	prSynhronization();		//���������������� (���� ����� ������ ������ ������ 1)
	
	ShowLevelNumberTimeCounter++;

	if (ShowLevelNumberTimeCounter<100)
	{
		
		Msg("  �������    ", 9, MSG_NOUPDATE);
		

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
	//������� ����������� �� ����� �� DoubleBuffer
	if (Keyb[KEY_L] && Keyb[KEY_LEFTCTRL]) 
	{
		Keyb^KEY_L;
		ShowLog^=1;
	}
	
	if (ShowLog) 
	{
		//������� ��������
		for(int i=0; i<100; i++)
		{
			memcpy(scr.DoubleBuffer+i*320, scr.DoubleBuffer+i*2*320,320);
		}
		
		scr.rectangle(0,100,320,100,0);
		Log.Show();
	}
	scr.update();			
	} //����� ����� while
}//����� ������� game

//������� main() ������
//����: ��������� ������� ���������� �� ������������ ������ SUPERMARIO (��� ��� DOS)
//      � ������ ������ �������� �� ������� (��������� ����� � �� ���� ���)
void main()
{
	Sleep(1000);
}


void SUPERMARIO::DrawMenu()
{
	Sound.InitDirectSound();

	//����� ������ - �������� (��� �����!!!)
	//����� ���� ����� �� ������������ �� �����, ���� ���������� ���������
	//������ ����� ����� (��� �� �����)
	//�� ���� ��������� ��� ��������� ��� ������ ��� Windows
	//��� DOS'a ����� ����� � ���������
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


	LoadSprites();		//��������� �������
	LoadSounds();		//�����
	LoadMusic();		//������
	


	//��������� �� ��������� ������� ��� �������
	//������ �����
	player[0].Left	= KEY_LEFT;
	player[0].Right	= KEY_RIGHT;
	player[0].Up	= KEY_UP;
	player[0].Down	= KEY_DOWN;
	player[0].Fire	= KEY_SPACE;
	player[0].Run	= KEY_LEFTCTRL;

	//������ �����
	player[1].Left	= KEY_Z;
	player[1].Right	= KEY_C;
	player[1].Up	= KEY_S;
	player[1].Down	= KEY_X;
	player[1].Fire	= KEY_A;
	player[1].Run	= KEY_LEFTSHIFT;

	//������ �����
	player[2].Left	= KEY_PAD4;
	player[2].Right	= KEY_PAD6;
	player[2].Up	= KEY_PAD8;
	player[2].Down	= KEY_PAD5;
	player[2].Fire	= KEY_PAD0;
	player[2].Run	= KEY_PAD7;

	//��������� �������� ����������
	/*
	{
		FunctionSpeed();
		return;
	}
	*/
	scr.clear();

	//��������� ������������ ������
	//MidiStop();

	Sound.play(SND_ZASTAVKA);
	//Sound.play(SND_GHOTIC_FAST);

	//��������� ����, ��� ���������� ����
	while (1) 
	{
		if (GAMEEXIT==TRUE) return;

		int menu_index=MenuMain();
		//ONE PLAYER
		if (menu_index==1)	
		{
			PlayerCounter=1;	//���� �����
			
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
			PlayerCounter=2;	//��� ������
			Game();
			Sound.play(SND_ZASTAVKA);
			continue;
		}

		//THREE PLAYER
		if (menu_index==3)	
		{
			PlayerCounter=3;	//��� ������
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
			scr << "������� ������";

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
				Msg("  ������ ������� ",2);
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
			//Msg(" �������� � ������ ���������� ",3);
			//scr.update();
			SPRITEEDITOR se;
			se.Editor(&Sprite, 1);
			LoadSprites();
			
			//Keyb.ReadScan();
		}

		//EXIT 
		if (menu_index==7)
		{
			//����� ������� ���������� ����� �� ����!!!
			//� ������ ������ �� �� ����������� DirectX
			//exit(1);
			//break;
			return;
		}
	}

}
