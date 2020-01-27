//Mario.h
#ifndef _MARIO__H
#define _MARIO__H

#include "sprite.h"
#include "level.h"
#include "moveobj.h"
#include "person.h"
#include "string.h"
#include <math.h>

//============= возвращает знак ===============
template <class T>
inline T sign(T a)
{
	if (!a) return 0;
	return a>0 ? 1 :-1;
}

//========= возвращает абсолютное значение =========
template <class T>
inline T abs(T a)
{
	return a>0 ? a : -a;
}

//====================класс SUPERMARIO=======================
class SUPERMARIO
{
public:

	//класс BRICK - перечесление кирпичиков
	struct BRICK
	{
		enum {
			MONEY		=	16,		//монетка
			CRYSTAL		=	75,		//кристалл
			BREAK		=	6,     	//разбивающийся кирпич
			SMALLBREAK	=	11,		//маленький разбивающийся кирпич
			ANSWER		=	7,		//знак вопроса
			ANSWERMUSHROOM=	3,		//гриб в знаке вопроса
			MANYMONEY	=	18,		//приз 'много монеток'
			BRICKSTAR	=	21,		//в кирпичике звезда
//			MUSHROOMLIVE=	2,		//невидимая жизнь
			ARROW		=	87,		//пуля
			DAGGER		=	88,		//кинжал
			AXE			=	89,		//топорик
			MAP			=	78,		//карта
			DOOR		=	105		//кирпичик-дверь
		};
	};

	//чужие - разные объекты
	class ALIEN: public PERSON
	{
	public:
		enum {  
			DEATH=		0x01,	//чужой погиб
			DEATHOFFIRE=0x02	//чужой погиб из-из огня
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
		
		//коды некоторых чужих и безопасных объектов (мостики и лифты)
		enum {
			CHANGELEVEL	=19,	//перемещение при котором меняется уровень(следующий кубик - номер уровня)
			PIG			=20,	//свинья
			LIZARD		=21,	//динозаврик
			MASHA		=22,	//ходячий грибок
			TURTLE		=23,	//черепашка
			TOOTHFLOWER	=24,	//зубастый цветок
			FIRELINE	=25,	//крутящаяся огненная линия
			HEDGEHOG	=26,	//ежик
			ABORIGINE	=27,	//туземец
			BRIDG_LR1	=29,	//мостик влево-вправо
			LIFT		=30,	//лифт
			BRIDG_UD1	=31,	//мостик вверх-вниз (много )
			BRIDG_UD2	=32,	//мостик вверх-вниз (немного )
			EAGLE_LR1	=33,	//орел влево - вправо
			BRIDG_RL2	=34,	//водяной мостик вправо-влево на 6
			BRIDG_LR2	=35,	//водяной мостик влево-вправо на 6
			BRIDG_UD3	=36,	//мостик вверх-вниз (на 4 с паузой)
			BRIDG_LR_DIAG1=37,	//мостик (движение сложное)
			BRIDG_UR_LU1=38,	//мостик (движение сложное)
			BRIDG_UL_RU1=39,	//мостик (движение сложное)
			HEAD1		=40,	//первая голова
			COSMONAUT	=41,	//космонавт
			BRIDG_R16_D3_R16=42,//мостик на 2 уровне( начало )
			BRIDG_P_DN9	=43,	//мостик вниз-вверх на 9
			BRIDG_DU_5P	=44,	//мостик вниз-вверх на 5 с паузой
			BRIDG_UD_4P	=45,	//мостик вверх-вниз на 4 c паузой
			BRIDG_UD_2P	=46,	//мостик вверх-вниз на 2 с паузой
			BRIDG_DU_6P	=47,	//мостик вниз-вверх на 6 с паузой
			WBRIDG_LR_16=48,	//водный мостик влево-вправо на 16
			SKELETON1	=49,	//скелет, просто за него дают очки
			SKELETON2	=50, 	//скелет открывает дверь
			BIRD		=51,	//птичка
			FISH		=52,	//рыбка
			HELIX		=53,	//улитка
			SHARK		=54,	//акула (босс)
			NEXTLEVEL	=55,	//следующий уровень(автомат)
			MUSHROOMLIVE=56,	//невидимая жизнь
			CIRCLEBRIGDE=57
		};
	};

	//класс FIRELINE - его объекты вращаются вокруг центра
	class FIRELINE : public ANIM
	{
	public:
		int xc,yc;		//центр
		int Radius;		//радиус
		double Angle;	//угол

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
		
		//конструктор по умолчанию
		FIRELINE() 
		{
			xc=0;
			yc=0;
			Radius=0;
			Angle=0;
		}
		
		FIRELINE(SPRITE *s) : ANIM(s) {;}
	};

    //сам марио
	class MARIO : public PERSON
	{
	public:
		MARIO(SPRITE*s) : PERSON(s) {;}
		MARIO() {;}
		void RenewXY();
	};

	//перемещение
	struct SHUFFLE 
	{
		//возможные значения флага Status
		enum {
		ALWAYS		=	0x00,	//перемещаться можно всегда
		ALLMAP		=	0x01,	//перемещаться можно только если собрана вся карта	
		BOSSLIVE	=	0x02,	//перемещаться можно если жив босс(голова)
		BOSSDEATH	=	0x04,	//перемещаться можно если босс мертвый
		CHGLEVEL	=	0x08,	//идет смена файла
		NEXTLEVEL	=	0x10	//на следующий уровень
		};

		int 
			LevelNumber,	//уровень, на который следует переместиться 
							//(если установлен флаг CHGLEVEL)
			BoxCode,		//код кубика, который нужно искать на уровне
			Status;			//флаги
	};


	//код опасных кирпичей
	enum { PRICKLES=74 };
	
	enum { DEATHPAUSE=40, PROTECTED_MUSIC=2 };
	
	enum { NUMBER_LEVELBOX=112 };	//число кубиков, доступных редактору уровней

	//виды скелетов
	enum { SKELET_DOOR, SKELET_SCORE };

	//класс PLAYER - клавиши для одного игрока
	struct PLAYER 
	{
		//коды клавиш для игрока
		BYTE Left,Right,Up,Down,Fire,Run;
	};

	//класс BIGSTRING - строка содержащая буквы громадного шрифта 
	struct BIGSTRING
	{
		SPRITE *spr;
		char *a;
		BIGSTRING(SPRITE *s,char *b) : a(b),spr(s) {};
		//прибавляет код n к данным спрайта Sprite
		void Add(int Sprite,int n);
		void Show(int x,int y);
		void Show(int y)
		{
			Show(160-strlen(a)*12, y);
		}
	};


//*********************перичисления-ЧЛЕНЫ*****************************
	enum mariostate
	{
		MARIO_DEATH		= 0x01,	//марио мертвый
		MARIO_CLAMMY	= 0x02,	//марио прилип
		MARIO_CANFIRE	= 0x04,	//может стрелять
		MARIO_BIG		= 0x08,	//марио очень большой(может разбивать) кирпичи
		MARIO_PROTECTED	= 0x10,	//на марио действует защита
		MARIO_WIZ		= 0x20	//марио выпил волшебную жидкость
	};

//================ режимы игры =========================
	enum gamemodes
	{
		GAMEMODE_LOADLEVEL			= 0x01,	//загрузить уровень
		GAMEMODE_RESTARTLEVEL		= 0x02,	//начать уровень с начала
		GAMEMODE_ALIEN_SCAN			= 0x04,	//просканировать уровень
		GAMEMODE_LOADLEVEL_IFDEATH	= 0x08,	//загрузить уровень если марио погиб
		GAMEMODE_SHOWEFFECT_IFDEATH = 0x10	//показать эффект (экран синеет)
	};

//================= коды меню ==================
	enum idmenu
	{
		MENU_1P,
		MENU_2P,
		MENU_3P,
		MENU_REDEFINEKEYS,
		MENU_LEVELEDITOR,
		MENU_EXIT
	};

//*********************ДАННЫЕ-ЧЛЕНЫ*****************************
public:
	enum { ARROW, DAGGER, AXE, SALIVA};	//возможное оружие

	enum { SHUFFLE_COUNT=20};

	SHUFFLE Shuffle[SHUFFLE_COUNT];

	enum { LEVEL_UNDERWATER=0x01};

	unsigned
		LevelStatus,	//статус этого уровеня
		SalivaPower,	//мощность слюнь
		ArrowPower,		//мощность стрелы
		DaggerPower,	//мощность ножика
		AxePower,		//мощность топорика
		OldArms,		//старое оружие
		Arms,			//текущее оружие
		ArmsPower,		//текущая сила оружия
		BossLive,		//флаг, говорящий о том, жив ли босс
		CurrentMusic,	//текущая мелодия
		MapCounter,		//число собранных карт
		GameMode,		//режим игры
		GAMECYCLE,		//надо ли продолжать цикл игры
		GAMEEXIT,		//надо ли выйти из игры
		LevelNumber,	//номер текущего уровня
		Lives,			//число жизней
		MoneyCounter,	//число собранных монеток
		Time,			//текущее время
		ProtectedCounter,//счетчик для организации защиты
		PlayerCounter,	//число игроков
		ShowExit,		//показывать надпись EXIT
		OldMarioX,		//старые координаты марио
		OldMarioY,
		Timer1,			//служебные переменные
		Timer2,
		DoorOpenCounter,//используется когда дверь закрывается
		NORMAL_MUSIC,	//номер обычной музыки
		ShowLevelNumberTimeCounter //для отображения номер уровня в самом начале
	;

	unsigned long Score;//текущее число очков

	//информация о мелодиях
	char *song[10];
	int	  song_start[10];//начальная позиция мелодии

	UINT ManymoneyCounter;	//счечик для многих монеток


	//дескрипторы списков объектов

	MARIO	Rick;		//марио
	MINDOBJ	Bullet;		//оружие
	PERSON	HeadSaliva;	//слюни, которые пускает башка
	ANIM	Toothflower;//цветки
	ANIM	Lift;		//лифты
	ANIM	Door;		//двери
	ANIM	Door1;		//дверь перед Марио
	ANIM	Different;	//разное, никак не обрабатыва емое
	MINDOBJ  Cleverobj;	//дескриптор клевых объектов
	MINDOBJ  CleverAlien;//умные чужие
	MINDOBJ	 Boss;		//босс (голова)
	ANIM	Skeleton;	//скелеты
	MOVETXT Movetxt;	//текст
	ANIM	Answer;		//выбиваемые знаки вопроса
	ANIM	SCORES;		//очки
	PERSON	Brick;		//кирпичи
	ANIM	Money;		//монетки
	ANIM	Prize;		//призы
	ALIEN	Alien;		//чужие
	FIRELINE FireLine;	//огненные линии

	//массив клавиш для игроков (игроков может быть более 3, только клавиш не хватит)
	PLAYER  player[3];

	int ChangeEffect;	//требуется выполнить эфффект перехода с одного экрана на другой
						//из записанного буфера

//*********************ФУНКЦИИ-ЧЛЕНЫ*****************************
public:
	int  AllMarioDeath(ANIM&ob);	//если все марио мертвые,возврат TRUE
	void prArmsCollisionWithWall();	//оружие сталкивается со стенами
	void ArmsKillAlien();			//оружие убивает чужих
	void prBuildGamePicture();		//построение картинки

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
	void DrawStateline();	//рисуется полоса состояния
	void FunctionSpeed();
	void Game();			//сама игра
	void GameModesTreat();	//обработка режимов игры
	int  get_up(MOVEOBJ & ob);
	void prKeyboardProcess();	//обработка нажатий клавиш
	void LoadMusic();		//загрузка музыки
	void LoadSounds();		//загрузка звуков
	void LoadSprites();		//загрузка спрайтов
	void MarioRenewXY(MARIO&);
	int  MenuMain();		//главное меню
	int  MenuConfiguration();//меню конфигурации
	void MindobjFunctions(PERSON&,MINDOBJ&);	//реализация умных объектов
	void PlayMusic(int n);	//проиграть музыку n
	void prPrizeCatch(ANIM &Rick, ANIM &Prize);	//ловим призы
	static int ReadXY(int x,int y);
	static int ReadXY1(int x,int y);
	static int scanlevel_down(MOVEOBJ &ob, int n, int deltax=0);
	void SkeletonCollect();	//собираем скелетов
	SUPERMARIO();
	void DrawMenu();
	void Teleport(int i,PERSON &rk);	//перемещение клавишей вниз
	int MarioKeyUp(int i,PERSON &rk);	//нажатие клавиши "вверх"
	int MarioKeyFire(int i, PERSON &rk);//нажатие клавиши "огонь"
	int InitForStartGame(int param);
	//функции, получившиеся разбивкой огромного цикла игра, имеет префикс pc (process)
	void prPuziri();	//марио пускает пузыри (только под водой)
	void BirdsOtSten(); //птицы отталкиваются от стен
	void prMarioDeathOnShipah(); //марио гасится на кубиках-шипах
	void prMonetsChangePhase();  //меняется фаза манетки (в массиве уровне)
	void prShowDebugInfo();		 //показать отладочную информацию
	void prBricksRestore();		//восстановить кирпичи
	void prTurtleCikAlien();	//черепаза сбивает других чужих
	void prRememberOldMarioCoordinates();
	void prForMarioProtected();	//чтобы марио был защищенным
	void prBricksNudgePrize();	//кирпичи могут подталкивать призы
	void prMonetsTimeEndTimeLiveAndScoreCreate();//когда у монетки кончается время жизни надо создать очки
	void prIfGameOver();		//если конец игры 
	void prBossSalivaDeathMario();// кегли башки гасят марио и не пролетают через стены
	void prBossSendSaliveAndKeepAtMario();// башка пускает "кегли" и находится вблизи от марио
	void prLiftUpDown();
	void prMarioDeathOnFlower();
	void prMarioFlyDownCleverobj();
	void prFlowersUpDown();
	void prMarioPositionerOnCleverobject();
	void prMarioClammyToLift();
	void prChangeEffect();
	void prMarioDownsBrickDestroy();
	void prScrollBricks();		//двигается фон (спрайты воды и огня)
	void prShowFPS();			//показать FPS
	void prSynhronization();	//синхронизируемся (ждем когда счетчик-таймер перейдет в 1)
	void prCleverobjRefresh();
	void prMarioRenewXY();
};

#endif // _MARIO__H