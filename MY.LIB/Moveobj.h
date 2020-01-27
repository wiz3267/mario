//Moveobj.h
#ifndef __MOVEOBJ_H
#define __MOVEOBJ_H

#include "rects.h"
#include "debug.h"


class SPRITE;		//��������������� ���������� ������

class MOVEOBJ 
{

	void NullAllData();
	//YES - ������ ����������, NO - ������ ������
public:	enum { YES=1, NO=-1 };	//�������� ���������� Supervisor

//*********************** �����-������ ************************
protected:
static	int SupervisorCounter;//����� ��������� ��������-������������
	SPRITE* Sprite;		//��������� �� ������ ���� SPRITE
	int	Supervisor;	//���� �����������
	MOVEOBJ* First;   	//��������� �� ������ ������ c�����
	MOVEOBJ* Last;		//��������� �� ��������� ������ ������
public:
static	int TotalAnimatedObject;
	double	Acceleratx;	//��������� �� ����
	double	Acceleraty;
	int	Counter;	//����� ��������� �������� � ������
	MYRECT	Hot;		//���������� ������� ����� �������
       MOVEOBJ* Next;		//��������� �� ��������� ������. ���� ��� ��������� ����� Next=NULL
       MOVEOBJ* Prev;		//��������� �� ���������� �����.���� ��� ������ ������ Prev=NULL
	int	Link;		//�������� �������
static	MYRECT	Lim;		//�������, ����� �� ������� ������� ���������
	MYRECT	Rect;		//���������� ������ �� ������
	double	Speedx;		//�������� �������� �� ���
	double	Speedy;
	int	SpriteIndex;	//������ �������
	double	Speed;		//������ ������� ��������
	int	Status;		//��������� �������
static	double	SPEED_UNIT;	//������� ��������
static	int	WindowX;	//���������� X ���� ������
static	int	WindowY;	//���������� Y ���� ������
	double	x,y;		//������� ���������� �������
	int	ShootCounter;	//����� ���������, ����� ���� ������
	int	AlwaysAnimate;	//������ �� ���� ����������� ������� ?
				//���������
//********************** �������-����� ***************************
//(������� YES - ������ ������� ������������� ������ ��� �����������
// NO - ������� �� ������������� ��� �����������, �� ���� �������������
// ������ ��� �������)
public:
	void Animate();				//YES �������� �������
virtual	void Del (MOVEOBJ *Obj);		//YES �������� ������� �� ������ �� ��� ������,
	void Del (int n) { Del(&operator[](n));}//YES �������� ������� � ������� n
	void DelAll();				//YES �������� ���� ��������
virtual void Destroy(int who) {}		//���������� ����� ������ ���-�� �������
	void MakeSupervisor(SPRITE*spr)		//������ ������ ������������
	{
		Supervisor=YES;
		Sprite=spr;
	}
	     MOVEOBJ(SPRITE *Sprite);		//YES ����������� �����������
	     MOVEOBJ();				//NO ����������� move-�������
	    ~MOVEOBJ();                     	//YES, NO ����������
	int  New( MOVEOBJ *Obj, int size);	//YES �������� ������ �������
	MOVEOBJ& operator[] (int i);		//YES �������� ������ �� ������ i
	void operator+= (MOVEOBJ &);		//YES �������� ������ � ������
virtual void RenewFrame() {}
	void RenewRect();			//NO  �������� ��������� Rect
virtual int RenewTimeLive() {return 1;}
virtual	void RenewXY();				//NO  �������� ���������� X,Y
	void Set(double x=0,double y=0,double sx=0,double sy=0,double acx=0,double acy=0);    //NO ���������� �������� ������ ����������
virtual	void Show();				//NO ���������� ������
	void ShowAll();				//YES �������� ��� �������
};


//****************************************************
//************* class ANIM - �������� �������� *******
//****************************************************
//����� ����������� MOVEOBJ ����� �������, ��� ����� �������
//����� ���������������� (���������� TimeLive) � ��������
//��������������� c ������ ��������� ������ �������� (� ������������
//������� ��������)

class ANIM: public MOVEOBJ
{
public:
	int FrameFirst, FrameLast;
	double FrameSpeed, FrameCurrent;
	int TimeLive;

public:
	ANIM ();
	ANIM(SPRITE *s) : MOVEOBJ(s) {;}
	//����������� [] ��� ����������� �������������� ����
	ANIM & operator[] (int i) {return (ANIM&) MOVEOBJ::operator[](i); }
	//��������, MOVEOBJ & operator+= ����� �������� !
	void operator+= (ANIM& ob) { New(&ob, sizeof(ob)); };
	void Animate(void);
virtual	void RenewFrame();
	int RenewTimeLive()
	{
        	if (TimeLive>3)
		{
			TimeLive--;
                	return 1;
                }
                else if (!TimeLive) return 1;
                else return 0;
	}

};


//************************************************************
//************* class MINDOBJ - �����, �������� ������� *******
//************************************************************
//����� ANIM ��������� ��������� ���������� ��������. ���� ��� �� ����������
//����������� ������ ANIM, ����������� ����� MINDOBJ

//0,-1,10, 0,1,10, 0	������ �����, ����
//

class MINDOBJ : public ANIM
{
public:
        //��������� "������" (����? - ����,��� �� ���)
        struct GOING
	{
		double Speed_x,Speed_y;	//����������� �� ���� �� ���� ���
//               	Accelerat_x,Accelerat_y;
		int  Time;	    //����� ����� ������������(����� �����)
        			   //���� Time==0, ������ ���� ��� ���������
        };
        //��� ������ �������� ����
        struct FRAMING
        {
        	int Fase,	//����� ����
				Time;	//������� �������� ��� ����� ���������
                    		//���������� GOING, ���� Time==0 - �� ������
	};

	GOING  * going;		//��������� �� ������ ��������
	FRAMING * framing;        //��������� �� ������ ����� �����

        int go_num, frame_num;	//������� ��������
        int go_max, frame_max;	//����� ���������

public:
	GOING  Go;		//������� ��������
	FRAMING Frame;


    //�������
    enum {
		SET_SPEED		= -1,	//���������� ��������
		SET_ACCELERAT   = -2,	//���������� ���������
        SET_INDEX		= -3	//������������ �� ������ �������
	};

        enum {
             PERSON=0x01,      //������ ������ ������� � ������� �����������
                               //(����� ������������ ���, ��� ���������)
             DANGER=0x02,	//������ �������
	     			//(����� ���������)
             SOLID=0x04,	//������ �������(������ ������ ����� ����)
             			//(����� ����������)
             LIFT=0x08,		//������ ����� ���������� �� ����(������,
	             		//�������, ����)
        	                //(����� �� �����)
        };

        unsigned State;		//��������� ��������

        void Add(MINDOBJ&, int NumGo,GOING *go_ptr, int NumFrame,
	FRAMING *frame_ptr,int StartGo=0, int StartFrame=0);


	void Del (MOVEOBJ *Obj);	//�������� ������� �� ������
	MINDOBJ(SPRITE *s) : ANIM(s) {;}
        MINDOBJ();
        ~MINDOBJ();         //����������
  	void operator+=(MINDOBJ&);
        MINDOBJ& operator[](int i) { return (MINDOBJ&) MOVEOBJ::operator[](i); }
        void RenewFrame();
        void RenewXY();
        void Show();

};



//�������������� �����
class MOVETXT : public ANIM
{
public:
	char* Message;		//���������
	char Color;			//���� ���������
	MOVETXT (SPRITE* spr) : ANIM(spr), Message(0) {}
	MOVETXT () : Message(0), Color(15) {;}
	void Animate();
	void operator+= (MOVETXT& ob) { New(&ob, sizeof(ob)); };
	void Show();
};



#endif