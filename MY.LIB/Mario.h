//Mario.h
#ifndef _MARIO__H
#define _MARIO__H

#include "sprite.h"
#include "level.h"
#include "moveobj.h"
#include "person.h"
#include "string.h"
#include <math.h>

//============= ���������� ���� ===============
template <class T>
inline T sign(T a)
{
	if (!a) return 0;
	return a>0 ? 1 :-1;
}

//========= ���������� ���������� �������� =========
template <class T>
inline T abs(T a)
{
	return a>0 ? a : -a;
}

//====================����� SUPERMARIO=======================
class SUPERMARIO
{
public:

	//����� BRICK - ������������ ����������
	struct BRICK
	{
		enum {
			MONEY		=	16,		//�������
			CRYSTAL		=	75,		//��������
			BREAK		=	6,     	//������������� ������
			SMALLBREAK	=	11,		//��������� ������������� ������
			ANSWER		=	7,		//���� �������
			ANSWERMUSHROOM=	3,		//���� � ����� �������
			MANYMONEY	=	18,		//���� '����� �������'
			BRICKSTAR	=	21,		//� ��������� ������
//			MUSHROOMLIVE=	2,		//��������� �����
			ARROW		=	87,		//����
			DAGGER		=	88,		//������
			AXE			=	89,		//�������
			MAP			=	78,		//�����
			DOOR		=	105		//��������-�����
		};
	};

	//����� - ������ �������
	class ALIEN: public PERSON
	{
	public:
		enum {  
			DEATH=		0x01,	//����� �����
			DEATHOFFIRE=0x02	//����� ����� ��-�� ����
		};

		ALIEN(SPRITE*s) : PERSON(s) {;}
		
		ALIEN() 
		{
		}
		
		ALIEN& operator[](int i)
		{
			return (ALIEN&)PERSON::operator[](i);
		}
		
		void RenewFrame()
		{
			if (!Speedy) ANIM::RenewFrame();
		}
		
		void	RenewXY();
		
		//���� ��������� ����� � ���������� �������� (������� � �����)
		enum {
			CHANGELEVEL	=19,	//����������� ��� ������� �������� �������(��������� ����� - ����� ������)
			PIG			=20,	//������
			LIZARD		=21,	//����������
			MASHA		=22,	//������� ������
			TURTLE		=23,	//���������
			TOOTHFLOWER	=24,	//�������� ������
			FIRELINE	=25,	//���������� �������� �����
			HEDGEHOG	=26,	//����
			ABORIGINE	=27,	//�������
			BRIDG_LR1	=29,	//������ �����-������
			LIFT		=30,	//����
			BRIDG_UD1	=31,	//������ �����-���� (����� )
			BRIDG_UD2	=32,	//������ �����-���� (������� )
			EAGLE_LR1	=33,	//���� ����� - ������
			BRIDG_RL2	=34,	//������� ������ ������-����� �� 6
			BRIDG_LR2	=35,	//������� ������ �����-������ �� 6
			BRIDG_UD3	=36,	//������ �����-���� (�� 4 � ������)
			BRIDG_LR_DIAG1=37,	//������ (�������� �������)
			BRIDG_UR_LU1=38,	//������ (�������� �������)
			BRIDG_UL_RU1=39,	//������ (�������� �������)
			HEAD1		=40,	//������ ������
			COSMONAUT	=41,	//���������
			BRIDG_R16_D3_R16=42,//������ �� 2 ������( ������ )
			BRIDG_P_DN9	=43,	//������ ����-����� �� 9
			BRIDG_DU_5P	=44,	//������ ����-����� �� 5 � ������
			BRIDG_UD_4P	=45,	//������ �����-���� �� 4 c ������
			BRIDG_UD_2P	=46,	//������ �����-���� �� 2 � ������
			BRIDG_DU_6P	=47,	//������ ����-����� �� 6 � ������
			WBRIDG_LR_16=48,	//������ ������ �����-������ �� 16
			SKELETON1	=49,	//������, ������ �� ���� ���� ����
			SKELETON2	=50, 	//������ ��������� �����
			BIRD		=51,	//������
			FISH		=52,	//�����
			HELIX		=53,	//������
			SHARK		=54,	//����� (����)
			NEXTLEVEL	=55,	//��������� �������(�������)
			MUSHROOMLIVE=56,	//��������� �����
			CIRCLEBRIGDE=57
		};
	};

	//����� FIRELINE - ��� ������� ��������� ������ ������
	class FIRELINE : public ANIM
	{
	public:
		int xc,yc;		//�����
		int Radius;		//������
		double Angle;	//����

		void operator+=(FIRELINE & Obj)
		{
			New( &Obj, sizeof(FIRELINE) );
		}

		void RenewXY()
		{
			x=int(xc+cos(Angle)*Radius);
			y=yc+sin(Angle)*Radius;
			Angle+=Speed;
			if (Angle>2*3.14) Angle-=2*3.14;
		}
		
		//����������� �� ���������
		FIRELINE() 
		{
			xc=0;
			yc=0;
			Radius=0;
			Angle=0;
		}
		
		FIRELINE(SPRITE *s) : ANIM(s) {;}
	};

    //��� �����
	class MARIO : public PERSON
	{
	public:
		MARIO(SPRITE*s) : PERSON(s) {;}
		MARIO() {;}
		void RenewXY();
	};

	//�����������
	struct SHUFFLE 
	{
		//��������� �������� ����� Status
		enum {
		ALWAYS		=	0x00,	//������������ ����� ������
		ALLMAP		=	0x01,	//������������ ����� ������ ���� ������� ��� �����	
		BOSSLIVE	=	0x02,	//������������ ����� ���� ��� ����(������)
		BOSSDEATH	=	0x04,	//������������ ����� ���� ���� �������
		CHGLEVEL	=	0x08,	//���� ����� �����
		NEXTLEVEL	=	0x10	//�� ��������� �������
		};

		int 
			LevelNumber,	//�������, �� ������� ������� ������������� 
							//(���� ���������� ���� CHGLEVEL)
			BoxCode,		//��� ������, ������� ����� ������ �� ������
			Status;			//�����
	};


	//��� ������� ��������
	enum { PRICKLES=74 };
	
	enum { DEATHPAUSE=40, PROTECTED_MUSIC=2 };
	
	enum { NUMBER_LEVELBOX=112 };	//����� �������, ��������� ��������� �������

	//���� ��������
	enum { SKELET_DOOR, SKELET_SCORE };

	//����� PLAYER - ������� ��� ������ ������
	struct PLAYER 
	{
		//���� ������ ��� ������
		BYTE Left,Right,Up,Down,Fire,Run;
	};

	//����� BIGSTRING - ������ ���������� ����� ���������� ������ 
	struct BIGSTRING
	{
		SPRITE *spr;
		char *a;
		BIGSTRING(SPRITE *s,char *b) : a(b),spr(s) {};
		//���������� ��� n � ������ ������� Sprite
		void Add(int Sprite,int n);
		void Show(int x,int y);
		void Show(int y)
		{
			Show(160-strlen(a)*12, y);
		}
	};


//*********************������������-�����*****************************
	enum mariostate
	{
		MARIO_DEATH		= 0x01,	//����� �������
		MARIO_CLAMMY	= 0x02,	//����� ������
		MARIO_CANFIRE	= 0x04,	//����� ��������
		MARIO_BIG		= 0x08,	//����� ����� �������(����� ���������) �������
		MARIO_PROTECTED	= 0x10,	//�� ����� ��������� ������
		MARIO_WIZ		= 0x20	//����� ����� ��������� ��������
	};

//================ ������ ���� =========================
	enum gamemodes
	{
		GAMEMODE_LOADLEVEL			= 0x01,	//��������� �������
		GAMEMODE_RESTARTLEVEL		= 0x02,	//������ ������� � ������
		GAMEMODE_ALIEN_SCAN			= 0x04,	//�������������� �������
		GAMEMODE_LOADLEVEL_IFDEATH	= 0x08,	//��������� ������� ���� ����� �����
		GAMEMODE_SHOWEFFECT_IFDEATH = 0x10	//�������� ������ (����� ������)
	};

//================= ���� ���� ==================
	enum idmenu
	{
		MENU_1P,
		MENU_2P,
		MENU_3P,
		MENU_REDEFINEKEYS,
		MENU_LEVELEDITOR,
		MENU_EXIT
	};

//*********************������-�����*****************************
public:
	enum { ARROW, DAGGER, AXE, SALIVA};	//��������� ������

	enum { SHUFFLE_COUNT=20};

	SHUFFLE Shuffle[SHUFFLE_COUNT];

	enum { LEVEL_UNDERWATER=0x01};

	unsigned
		LevelStatus,	//������ ����� �������
		SalivaPower,	//�������� �����
		ArrowPower,		//�������� ������
		DaggerPower,	//�������� ������
		AxePower,		//�������� ��������
		OldArms,		//������ ������
		Arms,			//������� ������
		ArmsPower,		//������� ���� ������
		BossLive,		//����, ��������� � ���, ��� �� ����
		CurrentMusic,	//������� �������
		MapCounter,		//����� ��������� ����
		GameMode,		//����� ����
		GAMECYCLE,		//���� �� ���������� ���� ����
		GAMEEXIT,		//���� �� ����� �� ����
		LevelNumber,	//����� �������� ������
		Lives,			//����� ������
		MoneyCounter,	//����� ��������� �������
		Time,			//������� �����
		ProtectedCounter,//������� ��� ����������� ������
		PlayerCounter,	//����� �������
		ShowExit,		//���������� ������� EXIT
		OldMarioX,		//������ ���������� �����
		OldMarioY,
		Timer1,			//��������� ����������
		Timer2,
		DoorOpenCounter,//������������ ����� ����� �����������
		NORMAL_MUSIC,	//����� ������� ������
		ShowLevelNumberTimeCounter //��� ����������� ����� ������ � ����� ������
	;

	unsigned long Score;//������� ����� �����

	//���������� � ��������
	char *song[10];
	int	  song_start[10];//��������� ������� �������

	UINT ManymoneyCounter;	//������ ��� ������ �������


	//����������� ������� ��������

	MARIO	Rick;		//�����
	MINDOBJ	Bullet;		//������
	PERSON	HeadSaliva;	//�����, ������� ������� �����
	ANIM	Toothflower;//������
	ANIM	Lift;		//�����
	ANIM	Door;		//�����
	ANIM	Door1;		//����� ����� �����
	ANIM	Different;	//������, ����� �� ���������� ����
	MINDOBJ  Cleverobj;	//���������� ������ ��������
	MINDOBJ  CleverAlien;//����� �����
	MINDOBJ	 Boss;		//���� (������)
	ANIM	Skeleton;	//�������
	MOVETXT Movetxt;	//�����
	ANIM	Answer;		//���������� ����� �������
	ANIM	SCORES;		//����
	PERSON	Brick;		//�������
	ANIM	Money;		//�������
	ANIM	Prize;		//�����
	ALIEN	Alien;		//�����
	FIRELINE FireLine;	//�������� �����

	//������ ������ ��� ������� (������� ����� ���� ����� 3, ������ ������ �� ������)
	PLAYER  player[3];

	int ChangeEffect;	//��������� ��������� ������� �������� � ������ ������ �� ������
						//�� ����������� ������

//*********************�������-�����*****************************
public:
	int  AllMarioDeath(ANIM&ob);	//���� ��� ����� �������,������� TRUE
	void prArmsCollisionWithWall();	//������ ������������ �� �������
	void ArmsKillAlien();			//������ ������� �����
	void prBuildGamePicture();		//���������� ��������

	static int  chk_up(MOVEOBJ & ob, int what, int mask=LEVEL::MASK);
	static int  chk_down(MOVEOBJ&, int);
	static int  chk_left(MOVEOBJ&, int,int=1);
	static int  chk_right(MOVEOBJ&, int,int=1);
	static int  chk_all(MOVEOBJ&, int);
	static int  chk_all_transp(MOVEOBJ & ob, int what);
	static int  chk(MOVEOBJ & );
	static int  chk2(MOVEOBJ & );
	void ColorEffect();
	void CreateScore(int score, ANIM & svisor, ANIM & ob);
	void DrawStateline();	//�������� ������ ���������
	void FunctionSpeed();
	void Game();			//���� ����
	void GameModesTreat();	//��������� ������� ����
	int  get_up(MOVEOBJ & ob);
	void prKeyboardProcess();	//��������� ������� ������
	void LoadMusic();		//�������� ������
	void LoadSounds();		//�������� ������
	void LoadSprites();		//�������� ��������
	void MarioRenewXY(MARIO&);
	int  MenuMain();		//������� ����
	int  MenuConfiguration();//���� ������������
	void MindobjFunctions(PERSON&,MINDOBJ&);	//���������� ����� ��������
	void PlayMusic(int n);	//��������� ������ n
	void prPrizeCatch(ANIM &Rick, ANIM &Prize);	//����� �����
	static int ReadXY(int x,int y);
	static int ReadXY1(int x,int y);
	static int scanlevel_down(MOVEOBJ &ob, int n, int deltax=0);
	void SkeletonCollect();	//�������� ��������
	SUPERMARIO();
	void DrawMenu();
	void Teleport(int i,PERSON &rk);	//����������� �������� ����
	int MarioKeyUp(int i,PERSON &rk);	//������� ������� "�����"
	int MarioKeyFire(int i, PERSON &rk);//������� ������� "�����"
	int InitForStartGame(int param);
	//�������, ������������ ��������� ��������� ����� ����, ����� ������� pc (process)
	void prPuziri();	//����� ������� ������ (������ ��� �����)
	void BirdsOtSten(); //����� ������������� �� ����
	void prMarioDeathOnShipah(); //����� ������� �� �������-�����
	void prMonetsChangePhase();  //�������� ���� ������� (� ������� ������)
	void prShowDebugInfo();		 //�������� ���������� ����������
	void prBricksRestore();		//������������ �������
	void prTurtleCikAlien();	//�������� ������� ������ �����
	void prRememberOldMarioCoordinates();
	void prForMarioProtected();	//����� ����� ��� ����������
	void prBricksNudgePrize();	//������� ����� ������������ �����
	void prMonetsTimeEndTimeLiveAndScoreCreate();//����� � ������� ��������� ����� ����� ���� ������� ����
	void prIfGameOver();		//���� ����� ���� 
	void prBossSalivaDeathMario();// ����� ����� ����� ����� � �� ��������� ����� �����
	void prBossSendSaliveAndKeepAtMario();// ����� ������� "�����" � ��������� ������ �� �����
	void prLiftUpDown();
	void prMarioDeathOnFlower();
	void prMarioFlyDownCleverobj();
	void prFlowersUpDown();
	void prMarioPositionerOnCleverobject();
	void prMarioClammyToLift();
	void prChangeEffect();
	void prMarioDownsBrickDestroy();
	void prScrollBricks();		//��������� ��� (������� ���� � ����)
	void prShowFPS();			//�������� FPS
	void prSynhronization();	//���������������� (���� ����� �������-������ �������� � 1)
	void prCleverobjRefresh();
	void prMarioRenewXY();
};

#endif // _MARIO__H