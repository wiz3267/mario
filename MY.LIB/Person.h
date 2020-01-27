//Person.h
#ifndef _PERSON__H
#define _PERSON__H

#include "moveobj.h"
#include "sprite.h"
#include "screen.h"
/////////////////
// PERSON.H    //
/////////////////

//наследуем класс ANIM
class PERSON: public ANIM
{
public:
	enum 
	{
        UNUSED=8,	//не использовать эту переменную
        LEFT=SCREEN::FLIP_HORZ,		//объект движется влево
		RIGHT=0,	//объект движется вправо
        FLIP_VERT=SCREEN::FLIP_VERT	//перевернуть по горизонатли
	};

	char Movement;	//направление движения
	double ClammyX;	//используется,когда персона прилипла к чему-то

public:
	PERSON(SPRITE *s) : ANIM(s) {;}
	PERSON() : Movement(UNUSED), ClammyX(0) {;}
	void operator+=(PERSON& pn) { New( &pn,sizeof(PERSON)); };
    PERSON& operator[](int i) { return (PERSON&)ANIM::operator[](i);}
	void Show();
//	void Animation();
};

#endif