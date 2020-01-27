//Moveobj.cpp
/////////////////////////////////////////////
#include "stdafx.h"

#include <math.h>
#include "screen.h"
#include "sprite.h"
#include "moveobj.h"
#include "debug.h"

///////////////////////////////////////////////////////////////////////////
//		   	  ����� MOVEOBJ					 //
///////////////////////////////////////////////////////////////////////////
//   ����� MOVEOBJ ������������ ������������ �������� �� ������ � ������������
//����������� c �������� ��������� � ���������� �� ������ ��� � ����������
//������������ OXY. C������� ������������� ����������, ���� ������ ���������.
//   � ������ ������� ���������� ��� ���������� ������� ����� Hot, �.�. �����-
//�������� ������� ������ �������, �������� ����������� ������������
//������� ����� ������� ������������ ��� ������. ��� ����������� �������
//�������, ������� �� �������� �� ������, ������������� � ��������� Rect,
//������������ ��� ��������� ��������
//   ���������� ������� ������� �����������. ���� ������ ������� �� �������,
//�� ����������������
//   ��� �������, ���� ������� � ��������� ����� ����������� ������������
//������� ������, ������� ��� ���� �������� ���������� ����� ����������
//WindowX,WindowY, ��������  ���������� �������� ����, ������� �������
//������������ �� ������ � ������ ���� ����������.
//   ������������ ������ �������� ��, ��� ��������� ���
//���������� ������ �� ��������, �� ���������� �� ��������� ������� ����
//MOVEOBJ. ������, ��� ���������� ����������, ��������� �������������
//� ���������� - ���������� �������� ��������� �� ������ ������ SPRITE
//�������� ���� �������. ����� ����, ��� ������ ����������, � ����
//����� ���������,�������, �������� ������ �� �������, ���������� ����������
//������. ����� ������� ����� ��������� ������(� ������ ������ ����� �����)
//��������, ������������ ��� ����� ������ ����������. � ������
//������� �� ������ ����� ���������� ������ � ������� �������� [] - ���������
//� �������� �������.��� ����������� ��������� ����������������. ������
//������ ��������� ������������� �� ���������, ������� �������� ����� ��� ����
//��������� MOVEOBJ, ��� ����� ������, �.�. �� ���� ������ ��� ��� ��������
//������� �������� ��� ����, ���������� ������ ������ ��, ��� ���� � ����������
//��������. ������ ����� ������ �������� � ������, �� ����������� ���� ������,
//   �������, ����� ������� ������� ��������� ����������, ��������,
//��������� � ������ ������ ����������, ������ ������ ��� �����������.
//��������, ���������� First,Last - ��������� �� ������ � ����� ������,
// Supervisor - ����� �������� ������� ������ �� �������-�����������,
// �� ������� ����������, �� � ���, ��� �������� ������ �������
//���� - ���������� ���������� ��������� ����� �������, ����������� ���
//����������� � �������. ��������, ����������� ������ ������� 'RenewRect',
//� ������� - 'operator+=',��� 'Animate'. ������ ������� ������ ����������
//������ ��� �������, � ������ � ������ ������ ��� �����������.
//   ���������� ��� ����� ������� � ���, ��� � ������ ������ ��������
//��� ���������� - ��� ���������� ��� ��� ������, � ��� ������������� ������
//�� ����������� � �������, ������� �������� �����, ����������� ������
//��� ����� ����� ��������. ���� �����������  ����������� �� ������-
//������� ������� � � ��������, � ������� � ������ ��� �������, ����� �������
//����� �������� ���������, �� ���� �� ����� ����� ���������� ���������
//�� ������� � ����������� ������� ����� �� ����������.
//   �� ������ ������ �������, ��� ����� ��������� ��� ������: �����
//���������� � ����� ������. �������������, ��������� ������ �� ���������
//� ��������, ������������ ��� ������� ������ ������ ��������
//��� �� ����� ����������, �� ����� "���������" ������ ������. ��...���������
//�����,���� ����� ��������� �������� - �������� �������� �������, ���
//������������.
//   ��������, � ��������, � ���������� ����� ������� � ��������, ������
//������� ����������� �����, �� ������ ������� �� ������ ������ ���������
//�� ����, � ����������� ������������ ���, ��� ����.

//************************************************************************//
//***************** �������-����� ������ MOVEOBJ     *********************//
//************************************************************************//

int		MOVEOBJ::SupervisorCounter=0;		//����� ��������-������������
int		MOVEOBJ::WindowX=0;
int		MOVEOBJ::WindowY=0;
double	MOVEOBJ::SPEED_UNIT=1;
int		MOVEOBJ::TotalAnimatedObject;
MYRECT	MOVEOBJ::Lim(-24,-24,320+24,200+24);

//�������� ��� �������� ������
void MOVEOBJ::NullAllData()
{
	Sprite=NULL;
	Supervisor=0;
	First=Last=NULL;
	Acceleratx=Acceleraty=0;
	Counter=0;
	Hot.Set(0,0,0,0);
	Next=Prev=NULL;
	Link=0;
	Rect.Set(0,0,0,0);
	Speedx=Speedy=0;
	SpriteIndex=0;
	Speed=0;
	Status=0;
	x=y=0;
	ShootCounter=0;
	AlwaysAnimate=0;

}

//����������� �������, ��������������� � �������� ���������
//(����������� �� ���������)
MOVEOBJ::MOVEOBJ()
{
	//�������� ��� ����������
	//����� �������� ���!!!
	NullAllData();

	Supervisor=NO;	//������� � ���, ��� ��� �� ����������
	ShootCounter=1;

}

//========= 'MOVEOBJ' ����������� �������-����������� ==============
MOVEOBJ::MOVEOBJ(SPRITE *Spr)
{
	#if DEBUGMESSAGES
		Debug("Run MOVEOBJ-supervisor constructor");
	#endif

	//�������� ���������
	NullAllData();

	//������������� ����������
	SupervisorCounter++;  //����������� ����� ��������� ��������-������������
	//Lim.Left=-24;
	//Lim.Top=-24;
	//Lim.Right=320+24;
	//Lim.Bottom=200+24;
	Supervisor=YES;	//���� ����� ����, ��� ���� ������ - ����������
	Sprite = Spr;  	//��������� ��������� �� ������
}

//=================== '~MOVEOBJ' ���������� =================
MOVEOBJ::~MOVEOBJ(void)
{
	if ( !SupervisorCounter )
	{
		#if DEBUGMESSAGES
			Debug("MOVEOBJ-destructor: obj not exist!");
			return;
		#endif
	}

	#if DEBUGMESSAGES
		Debug("Run MOVEOBJ destructor");
	#endif

	//���� ��������� ������-����������, ���� �������
	//������� ��������, ����������� � ����
	if ( Supervisor == YES )
	{
		//����������� ��������� ��������
		int t=Counter;
		for (int i=0; i<t; i++)
		{
			Del(0);
		}
	}

}

//================= 'Show' - �������� ������ �� ������
void MOVEOBJ::Show()
{
	if (Supervisor== YES)
	{
		Debug("MOVEOBJ::Show - illegal start");
	}
	Sprite -> Show( int(x-WindowX), int(y-WindowY), SpriteIndex );
}

//================= 'ShowAll' - �������� ��� ������� �� ������
void MOVEOBJ::ShowAll()
{
	for(int i=0; i<Counter; i++)
	{
		MOVEOBJ *ob=&operator[](i);
		ob -> Show();
	}
}


//==================�������� ��������=====================
void MOVEOBJ::Animate(void)
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::Animate - illegal start");
		return;
	}

	MOVEOBJ *ob = First;

	//����������� ��������
	for ( int i=0; i<Counter; i++ )
	{
		int x=int(ob->x);
		//���� ���� ������ ���� ������ �����������
		// ��� ������ � ������ ������� �� ����

		if ( ob->AlwaysAnimate ||
			( x>(WindowX-100) && x<(WindowX+320+100) )
		   )
		{
			ob->Show();	//���������� ������
			ob->RenewXY();  //��������� ���������� X � Y
			ob->RenewRect();//��������� ��������� Rect
		}
		else
		{
			//ob->Show();	//���������� ������
		}

		TotalAnimatedObject++;

		//�������� ����� ���������� �������
		ob = ob->Next;
	}

restart:
	ob = First;
	//�������� �������� �� �����
	for ( i=0; i<Counter; i++ )
	{
		//��������� �������� ������ ������� �� �����
		if ( (ob->y > Lim.Bottom) || (ob->y < Lim.Top) ||
			(ob->x < Lim.Left) || (ob->x > Lim.Right) )
		{
			//�������� �������-���� �������� �������
			Del( ob );
			goto restart;
		}

		ob = ob->Next;
	}

}

//==================�������� ��������=====================
void MOVETXT::Animate(void)
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::Animate - illegal start");
		return;
	}

	MOVEOBJ *ob = First;

	//����������� ��������
	for ( int i=0; i<Counter; i++ )
	{
		int x=int(ob->x);
		//���� ���� ������ ���� ������ �����������
		// ��� ������ � ������ ������� �� ����
		ob->Show();	//���������� ������
		ob->RenewXY();  //��������� ���������� X � Y
		ob->RenewRect();//��������� ��������� Rect

		TotalAnimatedObject++;

		//�������� ����� ���������� �������
		ob = ob->Next;
	}

restart:
	ob = First;
	//�������� �������� �� �����
	for ( i=0; i<Counter; i++ )
	{
		//��������� �������� ������ ������� �� �����
		if ( (ob->y > Lim.Bottom) || (ob->y < Lim.Top) ||
			(ob->x < Lim.Left) || (ob->x > Lim.Right) )
		{
			//�������� �������-���� �������� �������
			Del( ob );
			goto restart;
		}

		ob = ob->Next;
	}
	ANIM::Animate();
}



//============== 'DelAll' - ������� ��� ������� �� ������ =========
void MOVEOBJ::DelAll()
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::DelAll - illegal start");
		return;
	}


	if ( Supervisor == YES )
	{
		int t=Counter;
		for (int k=0; k<t; k++) Del(First);
	}
	else
	{
		Debug("MOVEOBJ::DelAll this is'nt SuperVisor");
	}
}

//=============== 'Del' �������� ������� obj �� ������ =====================
void MOVEOBJ::Del(MOVEOBJ *Obj)
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::Del - illegal start");
		return;
	}


	if (Obj -> Supervisor == YES )
	{
		Debug("MOVEOBJ::Del - you want delete Supervisor !");
		return;
	}

	//�������� �������������� ��������
	if ( Obj == NULL )
	{
		Debug("'MOVEOBJ::Del' - Obj==NULL!");
		return;
	}

        //�������� �������������� ��������
	if ( Counter == 0 )
	{
		Debug("'MOVEOBJ::Del' - Counter == NULL!");
		return;
	}



	//��� ������ ������ ���� ������ ?
	if ( Counter == 1 )
	{
		delete Obj;
		First = NULL;
		Last  = NULL;
		Counter = 0;
		return;
	}


	//��������� ������ ������ ?
	if ( First == Obj )
	{
		First = Obj -> Next;
		Obj -> Next -> Prev = NULL;
		delete Obj;
		Counter--;
		return;
	}

	//��������� ��������� ������
	if ( Last == Obj )
	{
		Obj -> Prev -> Next = NULL;
		Last = Obj -> Prev;
		delete Obj;
		Counter--;
		return;
	}

	//��������� ������ ���-�� � ��������
	Obj -> Prev -> Next = Obj -> Next;
	Obj -> Next -> Prev = Obj -> Prev;
	delete Obj;
	Counter--;

}

//================�������� ������ �������==================
// int size - ���������� ������ ��� ����� �������
int MOVEOBJ ::New(MOVEOBJ  *Fallobj, int size)
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::New - illegal start");
		return FALSE;
	}


    //����� ������ ����-��
    Fallobj->Sprite=Sprite;

	//�������� ������ ��� ������
	MOVEOBJ *NewObj = (MOVEOBJ *) new char[size];

	//��������� �������� ������
	if ( NewObj == NULL)
	{
		Debug("'MOVEOBJ::New' not enough memory");
		return FALSE;
	}

	//�������� ������ � ���������� ������
	memcpy( NewObj, Fallobj, size );

	//��������� �������� ������� �������
	if ( Counter == 0)
	{
		NewObj -> Prev = NULL;	// �� ������ � ...
		NewObj -> Next = NULL;  // ... ���������
		First = NewObj;
		Last =  NewObj;
	}

	//����� '�����������' ������ � ����� ������
	else
	{
		NewObj -> Prev = Last;
		NewObj -> Next = NULL;	// ... �� �� ���������
		Last->Next = NewObj;
		Last = NewObj;
	}

	Counter++;
	return TRUE;
}

//==============���������� ��������� Rect====================
void MOVEOBJ::RenewRect()
{
	if (Supervisor != NO)
	{
		Debug("MOVEOBJ::RenewRect - illegal start");
		return;
	}

	int x=int(this->x);
	int y=int(this->y);
	Rect.Left   = x + Hot.Left;
	Rect.Right  = x + Hot.Right;
	Rect.Top    = y + Hot.Top;
	Rect.Bottom = y + Hot.Bottom;

}

//================ 'RenewXY' ��������� ���������� X � Y ============
void MOVEOBJ::RenewXY()
{
	if (Supervisor != NO)
	{
		Debug("MOVEOBJ::RenewXY - illegal start");
		return;
	}

	x += Speedx;
	y += Speedy;
	Speedx += Acceleratx;
	Speedy += Acceleraty;
}

//================ 'Set' - ��������� ���������� ============
void MOVEOBJ::Set(double a,double b,double c,double d,double e,double f)
{
	if (Supervisor != NO)
	{
		Debug("MOVEOBJ::Set - illegal start");
		return;
	}

	x=a;
	y=b;
	Speedx=c;
	Speedy=d;
	Acceleratx=e;
	Acceleraty=f;
}

//============== 'operator[]' ���������� ������ �� ������ =================
MOVEOBJ & MOVEOBJ::operator[] (int i)
{
	if (Supervisor != YES)
	{
		Fatal("MOVEOBJ::operator[] - illegal start");
	}


	if (Counter==0)	{
		while (1)
		{
		Fatal("MOVEOBJ::operator[] - Counter==0!");
		Debug("Can't continue program!");
		}
	}

	if ( i>=Counter || i<0 )
	{
		while(1)
		{
			Fatal("MOVEOBJ::operator[] - Index out of range");
			Debug("Can't continue program!");
		}
	}

	//������� ��������� �� ������
	MOVEOBJ *Obj = First;


	//��������������� ���������� ��� ���������
	for (int k=0; k<i; k++)
	{
		Obj = Obj->Next;
	}

	//���������� ������ ( �� �� ���� �������� ! )
	return *Obj;
}

//============== 'oprator+=' ���������� ������� � ������ ============
void MOVEOBJ::operator += (MOVEOBJ &Obj)
{
    if (Supervisor != YES)
    {
        Debug("MOVEOBJ::operator+= - illegal start");
            return;
    }

	New( &Obj , sizeof(MOVEOBJ) );
}


//**************************************************************
//******************* �������-����� ������ ANIM ****************
//**************************************************************

//�����������
ANIM::ANIM () : FrameFirst(0), FrameLast(0), FrameSpeed(0), FrameCurrent(0),
	TimeLive(0)
{
}


void ANIM::RenewFrame()
{
	if (Supervisor != NO)
	{
		Debug("ANIM::RenewFrame - illegal start");
		return;
	}


	if( FrameSpeed)
	{
		FrameCurrent+=FrameSpeed;

		//����� ����� ���� ������
		if ( FrameSpeed>0)
		{

			//���� ����� �� ����� - �� ������
			if ((FrameCurrent<FrameFirst) || int(FrameCurrent)>FrameLast)
			{
				FrameCurrent = FrameFirst;
			}
		}
		//����� ����� ���� �����
		else
		{

		//���� ����� �� ����� - �� ������
		if (int(FrameCurrent)>FrameFirst || int(FrameCurrent)<FrameLast)
		{
			FrameCurrent = FrameFirst;
		}
	}
		SpriteIndex = int(FrameCurrent);
	}
}

//�������� ��������
void ANIM::Animate(void)
{
	if (Supervisor != YES)
	{
		Debug("ANIM::Animate - illegal start");
		return;
	}


	for (int i=0; i<Counter; i++)
	{
		ANIM* ob = &operator[](i);

		//���� ����� ����� ���������� �����������
		//���� ��������� ����� ����� �������
		if ( ob->TimeLive>=2 ) ob->TimeLive--;

		//���� ����� ����� ������� �����������,
		//������� ������
		if ( ob->TimeLive==1 )
		{
			Del (ob);
			i--;
			continue;
		}

                /*
                //������� ������ ������� ���� ������ �����
		if ( ob->x < WindowX-200 )
		{
			Del (ob);
                        i--;
                        continue;
		}
                */


//                scr.line(ob->x-WindowX+12, ob->y-WindowY+12, 160,100, 15);

        ob->RenewFrame();
	}

	MOVEOBJ::Animate();
}

/****************************************************************/
/*		����� MINDOBJ					*/
/****************************************************************/


void MINDOBJ::operator+=(MINDOBJ&)
{
	Fatal("'MINDOBJ::operator+=' - use 'Add' function");
}

void MINDOBJ::Add(MINDOBJ& ob, int NumGo,GOING *go_ptr, int NumFrame, FRAMING *frame_ptr,
int StartGo, int StartFrame)
{
	if (Supervisor == NO)
    {
        Debug("'MINDOBJ::Add' - illegal function call");
            return;
    }

    //�������������
    ob.go_num=StartGo;
    ob.frame_num=StartFrame;
    ob.go_max=NumGo;	//����� ��������� � �������
    ob.frame_max=NumFrame;

    if (StartGo>=ob.go_max)
    {
        Fatal("MINDOBJ::Add - StartGo too big");
    }
    if (StartFrame>=ob.frame_max)
    {
        Fatal("MINDOBJ::Add - StartFrame too big");
    }

    //�������� ������ ��� ������ ������� ��������
    ob.going=new GOING[ob.go_max];
    if (!ob.going) Fatal("MINDOBJ - out of memory for going");
    ob.framing=new FRAMING[ob.frame_max];
    if (!ob.framing) Fatal("MINDOBJ::MINDOBJ - out of memory for framing");

    //�������� � ���������� ������ ��, ��� ����
    for(int i=0; i<ob.go_max; i++)
    {
        ob.going[i]=go_ptr[i];
    }
    for(i=0; i<ob.frame_max; i++)
    {
        ob.framing[i]=frame_ptr[i];
    }

    ob.Go=ob.going[ob.go_num];
    ob.Frame=ob.framing[ob.frame_num];

    New(&ob, sizeof(MINDOBJ) );

}


MINDOBJ::MINDOBJ()
{
	State=0;
}

//����������
MINDOBJ::~MINDOBJ()
{
	if (Supervisor == YES)
	{
		for(int i=0; i<Counter; i++)
		{
			MINDOBJ &ob=operator[](i);
			if (!ob.going || !ob.framing) 
				Fatal("MINDOBJ::~MINDOBJ - I want delete not exist memory!");
			delete ob.going;
			delete ob.framing;
		}
	}
}

void MINDOBJ::RenewFrame()
{
    Frame.Time--;

    if (!Frame.Time)
    {
            frame_num++;
            if (frame_num == frame_max)
            {
                    frame_num=0;
            }
            //��������� ����� �������
          Frame = framing[frame_num];
    }

    if (Frame.Time == SET_INDEX)
    {
        frame_num=Frame.Fase;
            Frame = framing[frame_num];
            return;
    }

}

void MINDOBJ::RenewXY()
{
    if (Go.Time == SET_INDEX)
    {
        go_num=int(Go.Speed_x);
            Go = going[go_num];
            return;
    }

    if (Go.Time == SET_SPEED)
    {
        Speedx=Go.Speed_x;
        Speedy=Go.Speed_y;

		go_num++;
        if (go_num == go_max)
        {
            go_num=0;
        }
        //��������� ����� �������
        Go = going[go_num];

		//MOVEOBJ::RenewXY();

        return;
    }

    if (Go.Time == SET_ACCELERAT)
    {
        Acceleratx=Go.Speed_x;
        Acceleraty=Go.Speed_y;

		go_num++;
        if (go_num == go_max)
        {
            go_num=0;
        }
        //��������� ����� �������
        Go = going[go_num];

		MOVEOBJ::RenewXY();

        return;
    }

    x+=Go.Speed_x;
    y+=Go.Speed_y;

    Go.Time--;

    if (!Go.Time)
    {
		go_num++;
        if (go_num == go_max)
        {
            go_num=0;
        }
        //��������� ����� �������
        Go = going[go_num];
    }


	MOVEOBJ::RenewXY();
}

//�������� ������� �� ������
void MINDOBJ::Del(MOVEOBJ*ob)
{
	delete ((MINDOBJ*)ob)->going;
    delete ((MINDOBJ*)ob)->framing;
    ANIM::Del(ob);
}

void MINDOBJ::Show()
{
	int k=FALSE;

	if ( State & PERSON )
	{
		//� ������ ������� ��������� ���������� �� Go
		if (Go.Speed_x<0) k=TRUE;
		else if (Go.Speed_x>0) k=FALSE;
		else if (Speedx<0) k=TRUE;
	}

	if ( k )
	{
		Sprite -> Show( int(x-WindowX), int(y-WindowY), 
			Frame.Fase, SCREEN::FLIP_HORZ);
	}
	else
	{
		Sprite -> Show( int(x-WindowX), int(y-WindowY), Frame.Fase );
	}
}


void MOVETXT::Show()
{
	SCREEN &sc=*(Sprite->scr);
	int oldx=sc.x;
	int oldy=sc.y;

	sc.x=int(x);
	sc.y=int(y);
	sc.color=Color;
	//sc.color=rand()%256;
	sc<<Message;

	sc.x=oldx;
	sc.y=oldy;
}

//************************************************************************
//******************** ����� LIST - ������ *******************************
//************************************************************************
/*
//����������� ������
LIST::LIST(SPRITE* Spr)
{
	Sprite=Spr;	//���������� ����� ������� ���� ������

	Counter=0;	//���� ����� �������� � ������ ����� ����

	First=NULL;
        Last=NULL;
}

//���������� ������� � ������
//obj - ����� MOVEOBJ-�� ��� ������������ �� ����
// size - ������ �������
// �������: TRUE - ������ ������� � ������
//	    FALSE - �������� ������ ��� �������
int LIST::Add(MOVEOBJ  *obj, int size)
{
        //����� ������ ����-��
        obj->Sprite=Sprite;

	//�������� ������ ��� ������
	MOVEOBJ *NewObj = (MOVEOBJ *) new char[size];

	//��������� �������� ������
	if ( NewObj == NULL)
	{
		Debug("'MOVEOBJ::New' not enough memory");
		return FALSE;
	}

	//�������� ������ � ���������� ������
	_fmemcpy( NewObj, obj, size );

	//��������� �������� ������� �������
	if ( Counter == 0)
	{
		NewObj -> Prev = NULL;	// �� ������ � ...
		NewObj -> Next = NULL;  // ... ���������
		First = NewObj;
		Last =  NewObj;
	}

	//����� '�����������' ������ � ����� ������
	else
	{
		NewObj -> Prev = Last;
		NewObj -> Next = NULL;	// ... �� �� ���������
		Last->Next = NewObj;
		Last = NewObj;
	}

	Counter++;
	return TRUE;
}


/*
//==================�������� ��������=====================
void LIST::Animate()
{

	ANIM *ob = (ANIM*) First;

	//��� ���������� "��������" ��������
	for ( int i=0; i<Counter; i++ )
	{
			ob->RenewXY();  //��������� ���������� X � Y
			ob->RenewRect();//��������� ��������� Rect
                        ob->RenewFrame();
	                ob->Show();	//���������� ������

			//�������� ����� ���������� �������
			ob = (ANIM*)ob->Next;
	}

restart:
	ob = (ANIM*)First;
	//�������� �������� �� �����
	for ( i=0; i<Counter; i++ )
	{
		//��������� �������� ������ ������� �� �����
		if ( (ob->y > ob->Lim.Bottom) || (ob->y < ob->Lim.Top) ||
			(ob->x < ob->Lim.Left) || (ob->x > ob->Lim.Right) ||
			!ob->RenewTimeLive() )
		{
			//�������� �������-���� �������� �������
			Del( ob );
			goto restart;
		}

		ob = (ANIM*)ob->Next;
	}

}


//�������� ����� i-�� ��������
void * LIST::Get(unsigned n)
{
        if ( n>=Counter )
        {
        	fatal("LIST::Get - bad index");
                return 0;
        }

	void *ob=First;
        for(int i=0; i<n; i++)
		ob=( (MOVEOBJ*) ob )->Next;

	return ob;

}

//=============== 'Del' �������� ������� obj �� ������ =====================
void LIST::Del(MOVEOBJ *Obj)
{
	//�������� �������������� ��������
	if ( Obj == NULL )
	{
		Debug("'MOVEOBJ::Del' - Obj==NULL!");
		return;
	}

        //�������� �������������� ��������
	if ( Counter == 0 )
	{
		Debug("'MOVEOBJ::Del' - Counter == NULL!");
		return;
	}


	//��� ������ ������ ���� ������ ?
	if ( Counter == 1 )
	{
		delete Obj;
		First = NULL;
		Last  = NULL;
		Counter = 0;
		return;
	}


	//��������� ������ ������ ?
	if ( First == Obj )
	{
		First = Obj -> Next;
		Obj -> Next -> Prev = NULL;
		delete Obj;
		Counter--;
		return;
	}

	//��������� ��������� ������
	if ( Last == Obj )
	{
		Obj -> Prev -> Next = NULL;
		Last = Obj -> Prev;
		delete Obj;
		Counter--;
		return;
	}

	//��������� ������ ���-�� � ��������
	Obj -> Prev -> Next = Obj -> Next;
	Obj -> Next -> Prev = Obj -> Prev;
	delete Obj;
	Counter--;

}


//=================== '~MOVEOBJ' ���������� =================
LIST::~LIST(void)
{

	#if DEBUGMESSAGES
		Debug("Run MOVEOBJ destructor");
	#endif

	//����������� ��������� ��������

        int t=Counter;

	for (int i=0; i<t; i++)
        {
        	Del(First);
	}

}
*/