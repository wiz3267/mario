//IDSound.h
#ifndef __IDSound__h_
#define __IDSound__h_

//================ коды звуков ======================
enum
{
	SND_POP,		//звук соударения шарика со стенкой или кирпич
	SND_XPLODE,		//звук взрыва
	SND_NEWLIVE,	//звук при улавливании новой жизни
	SND_LAUGHT,		//звук смеха
	SND_NEWLEVEL,	//новый уровень
	SND_EXPLODE,	//взрыв
	SND_EXORCISM,	//страшный звук
	SND_APPLE,
	SND_BELL,
	SND_FINGER,
	SND_HEALTH,
	SND_RESTART,
	SND_MENUSEL,	//звук выбора пункта меню
	SND_FIRE,		//звук сгорания чего-либо
	SND_SPRING,		//звук колеблющегося тела
	SND_POP1,
	SND_GFX3,
	SND_PIGEGRIN,	//детский смех
	SND_GHOTIC,
	SND_GHOTIC_FAST, //тоже что готик, только частота 44100 звук играет быстрее
	SND_ZASTAVKA,
	SND_LEVEL1
};
#endif