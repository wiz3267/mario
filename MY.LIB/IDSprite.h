//IDSprite.h
#ifndef __IDSPRITE__H
#define __IDSPRITE__H


//============= ���� �������� ==============
enum {
	SPRITE_DIGITAL0,		//����� ����
	SPRITE_DIGITAL9=SPRITE_DIGITAL0+9,  //����� ������

	SPRITE_TEST,		//����������� ����, ��� ��� ����������� ������

	SPRITE_SHARK1,		//�����
	SPRITE_SHARK2,

	SPRITE_BUBBLE1,		//�������
	SPRITE_BUBBLE2,
	SPRITE_BUBBLE3,
	SPRITE_BUBBLE4,
	SPRITE_HELIX1,		//������
	SPRITE_HELIX2,

	SPRITE_FISH1,		//�����
	SPRITE_FISH2,

	SPRITE_BIRD1,		//������
	SPRITE_BIRD2,

	SPRITE_SALIVA1,		//�����
	SPRITE_SALIVA2,

    SPRITE_COSMONAUT0,	//���������
    SPRITE_COSMONAUT1,
    SPRITE_COSMONAUT2,
    SPRITE_COSMONAUT3,

    SPRITE_EXPLODESTART,//�����
    SPRITE_EXPLODEEND=SPRITE_EXPLODESTART+3,

    SPRITE_SKELETON,	//������

    SPRITE_HEAD1,		//������ - ����
    SPRITE_HEAD2,
    SPRITE_HEAD3,		//�������� �����

	SPRITE_TROLLEYSTART,//�������
    SPRITE_TROLLEYEND,

    SPRITE_TIDESTART,	//������ ���������
    SPRITE_TIDEEND=SPRITE_TIDESTART+3,

    SPRITE_EAGLESTART,	//����
	SPRITE_EAGLEEND,

    SPRITE_DOOROPEN,	//���������� �����
    SPRITE_DOORCLOSE=SPRITE_DOOROPEN+4,

    SPRITE_SMALLBRICK,	//��������� ������(������������ ��� ����������
        				//�������� �������)


    SPRITE_ARROW,		//������ ������
    SPRITE_DAGGER,		//������ ������
    SPRITE_AXE,			//������ �������

    SPRITE_ARROWDESTROYEDSTART,	//���������� ������
    SPRITE_ARROWDESTROYEDEND=SPRITE_ARROWDESTROYEDSTART+2,

    SPRITE_BRIDG,		//������(�� S.FORTUNE)
    SPRITE_WATERBRIDG,	//������ ��� ����
    SPRITE_LIFT,		//����
	SPRITE_POINTER,		//��������� � ����
    SPRITE_MARIOFLY,	//������� �����
    SPRITE_BULLET,		//����

    SPRITE_HEDGEHOGSTART,
    SPRITE_HEDGEHOGEND,  	//���� ����

    SPRITE_FIRESTART,		//��� ��������
    SPRITE_FIREEND,

    SPRITE_SMALLMONEY,		//��������� �������

    SPRITE_TURTLESTART,		//���������
    SPRITE_TURTLEEND,

    SPRITE_TURTLEHOUSE,		//������� ��������

    SPRITE_MUSHROOM_LIVE,	//����, ������ �����
    SPRITE_MUSHROOM_BIG,	//����, ������ ����������
    SPRITE_STAR,			//������ ������
    SPRITE_FLOWER,			//������

    SPRITE_MONEYSTART,		//������� ���������
    SPRITE_MONEYEND=SPRITE_MONEYSTART+5,

    SPRITE_LIZARDFLY,		//�������� ������
    SPRITE_LIZARDSTART,		//������
    SPRITE_LIZARDEND=SPRITE_LIZARDSTART+3,

    SPRITE_TOOTHFLOWERSTART,//�������� ������
    SPRITE_TOOTHFLOWEREND,

    SPRITE_MARIODEATH,		//������� �����
	SPRITE_RICKSTART,
	SPRITE_RICKEND=SPRITE_RICKSTART+3,	//�����

    SPRITE_ABORIGINESTART,	//�������
    SPRITE_ABORIGINEEND=SPRITE_ABORIGINESTART+3,

    SPRITE_MASHASTART,		//������� ����
    SPRITE_MASHAEND=SPRITE_MASHASTART+1,
    SPRITE_MASHASMALL,

	SPRITE_PIGSTART,		//������
	SPRITE_PIGEND=SPRITE_PIGSTART+3,

	SPRITE_LEVELSPRITESTART,		//������ ������
	SPRITE_LEVELSPRITEEND=SPRITE_LEVELSPRITESTART+115
};

#endif