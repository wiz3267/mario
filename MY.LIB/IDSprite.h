//IDSprite.h
#ifndef __IDSPRITE__H
#define __IDSPRITE__H


//============= коды спрайтов ==============
enum {
	SPRITE_DIGITAL0,		//цифра ноль
	SPRITE_DIGITAL9=SPRITE_DIGITAL0+9,  //цифра девять

	SPRITE_TEST,		//изображение того, что это тестируемая версия

	SPRITE_SHARK1,		//акула
	SPRITE_SHARK2,

	SPRITE_BUBBLE1,		//пузырек
	SPRITE_BUBBLE2,
	SPRITE_BUBBLE3,
	SPRITE_BUBBLE4,
	SPRITE_HELIX1,		//улитка
	SPRITE_HELIX2,

	SPRITE_FISH1,		//рыбка
	SPRITE_FISH2,

	SPRITE_BIRD1,		//птичка
	SPRITE_BIRD2,

	SPRITE_SALIVA1,		//слюна
	SPRITE_SALIVA2,

    SPRITE_COSMONAUT0,	//космонавт
    SPRITE_COSMONAUT1,
    SPRITE_COSMONAUT2,
    SPRITE_COSMONAUT3,

    SPRITE_EXPLODESTART,//взрыв
    SPRITE_EXPLODEEND=SPRITE_EXPLODESTART+3,

    SPRITE_SKELETON,	//скелет

    SPRITE_HEAD1,		//голова - босс
    SPRITE_HEAD2,
    SPRITE_HEAD3,		//подбитая башка

	SPRITE_TROLLEYSTART,//тележка
    SPRITE_TROLLEYEND,

    SPRITE_TIDESTART,	//кирпич осыпается
    SPRITE_TIDEEND=SPRITE_TIDESTART+3,

    SPRITE_EAGLESTART,	//орел
	SPRITE_EAGLEEND,

    SPRITE_DOOROPEN,	//открывание двери
    SPRITE_DOORCLOSE=SPRITE_DOOROPEN+4,

    SPRITE_SMALLBRICK,	//маленький кирпич(используется при разбивании
        				//большого кирпича)


    SPRITE_ARROW,		//оружие стрела
    SPRITE_DAGGER,		//оружие кинжал
    SPRITE_AXE,			//оружие топорик

    SPRITE_ARROWDESTROYEDSTART,	//разрушение стрелы
    SPRITE_ARROWDESTROYEDEND=SPRITE_ARROWDESTROYEDSTART+2,

    SPRITE_BRIDG,		//мостик(из S.FORTUNE)
    SPRITE_WATERBRIDG,	//мостик для воды
    SPRITE_LIFT,		//лифт
	SPRITE_POINTER,		//указатель в меню
    SPRITE_MARIOFLY,	//летящий марио
    SPRITE_BULLET,		//пуля

    SPRITE_HEDGEHOGSTART,
    SPRITE_HEDGEHOGEND,  	//злой ежик

    SPRITE_FIRESTART,		//чем стреляет
    SPRITE_FIREEND,

    SPRITE_SMALLMONEY,		//маленькая монетка

    SPRITE_TURTLESTART,		//черепашка
    SPRITE_TURTLEEND,

    SPRITE_TURTLEHOUSE,		//панцирь черепахи

    SPRITE_MUSHROOM_LIVE,	//гриб, дающий жизнь
    SPRITE_MUSHROOM_BIG,	//гриб, дающий увеличение
    SPRITE_STAR,			//звезда защита
    SPRITE_FLOWER,			//цветок

    SPRITE_MONEYSTART,		//монетка вращается
    SPRITE_MONEYEND=SPRITE_MONEYSTART+5,

    SPRITE_LIZARDFLY,		//летающий дракон
    SPRITE_LIZARDSTART,		//ДРАКОН
    SPRITE_LIZARDEND=SPRITE_LIZARDSTART+3,

    SPRITE_TOOTHFLOWERSTART,//зубастый цветок
    SPRITE_TOOTHFLOWEREND,

    SPRITE_MARIODEATH,		//мертвый марио
	SPRITE_RICKSTART,
	SPRITE_RICKEND=SPRITE_RICKSTART+3,	//марио

    SPRITE_ABORIGINESTART,	//туземец
    SPRITE_ABORIGINEEND=SPRITE_ABORIGINESTART+3,

    SPRITE_MASHASTART,		//ходячий гриб
    SPRITE_MASHAEND=SPRITE_MASHASTART+1,
    SPRITE_MASHASMALL,

	SPRITE_PIGSTART,		//свинья
	SPRITE_PIGEND=SPRITE_PIGSTART+3,

	SPRITE_LEVELSPRITESTART,		//данные уровня
	SPRITE_LEVELSPRITEEND=SPRITE_LEVELSPRITESTART+115
};

#endif