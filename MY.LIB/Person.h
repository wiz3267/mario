//Person.h
#ifndef _PERSON__H
#define _PERSON__H

#include "moveobj.h"
#include "sprite.h"
#include "screen.h"
/////////////////
// PERSON.H    //
/////////////////

//��������� ����� ANIM
class PERSON: public ANIM
{
public:
	enum 
	{
        UNUSED=8,	//�� ������������ ��� ����������
        LEFT=SCREEN::FLIP_HORZ,		//������ �������� �����
		RIGHT=0,	//������ �������� ������
        FLIP_VERT=SCREEN::FLIP_VERT	//����������� �� �����������
	};

	char Movement;	//����������� ��������
	double ClammyX;	//������������,����� ������� �������� � ����-��

public:
	PERSON(SPRITE *s) : ANIM(s) {;}
	PERSON() : Movement(UNUSED), ClammyX(0) {;}
	void operator+=(PERSON& pn) { New( &pn,sizeof(PERSON)); };
    PERSON& operator[](int i) { return (PERSON&)ANIM::operator[](i);}
	void Show();
//	void Animation();
};

#endif