//Moveobj.cpp
/////////////////////////////////////////////
#include "stdafx.h"

#include <math.h>
#include "screen.h"
#include "sprite.h"
#include "moveobj.h"
#include "debug.h"

///////////////////////////////////////////////////////////////////////////
//		   	  Класс MOVEOBJ					 //
///////////////////////////////////////////////////////////////////////////
//   Класс MOVEOBJ опеспечивает передвижение спрайтов по экрану в произвольном
//направление c заданной скоростью и ускорением по каждой оси в двухмерном
//пространстве OXY. Cкорость автоматически изменяется, если задано ускорение.
//   В каждом объекте определено так называемое горячее пятно Hot, т.е. прямо-
//угольная область внутри спрайта, эадающая фактическое расположение
//видимых точек спрайта относительно его начала. При перемещении объекта
//область, которую он занимает на экране, отслеживается в структуре Rect,
//используемой при обработки коллизий
//   Существует понятии границы перемещений. Если объект выходит за границу,
//он самоуничтожается
//   Как правило, один уровень в видеоигре может значительно превосходить
//размеры экрана, поэтому для всех объектов существуют общие переменные
//WindowX,WindowY, хранящие  координаты текущего окна, поэтому объекты
//отображаются на экране с учетом этих переменных.
//   Особенностью класса является то, что сущесвуют два
//совершенно разных по значению, но одинаковых по структуре объекта типа
//MOVEOBJ. Первый, так называемый супервизор, создается конструктором
//с параметром - необходимо передать указатель на объект класса SPRITE
//хранящий сами спрайты. После того, как создан супервизор, к нему
//можно добавлять,удалять, получать ссылку на объекты, образующие двусвязный
//список. Таким образом можно создавать классы(в прямом смысле этого слова)
//объектов, объединенных под одним именем переменной. К любому
//объекту из списка можно обратиться просто с помощью операции [] - обращение
//к элементу массива.Это значительно облегчает программирование. Второй
//объект создается конструктором по умолчанию, который обнуляет почти все поля
//структуры MOVEOBJ, что очень удобно, т.к. не надо всякий раз при создании
//объекта задавать все поля, достаточно задать только то, что надо в конкретной
//ситуации. Каждый такой объект хранится в списке, он отслеживает один спрайт,
//   Конечно, такой системе присуще некоторые недостатки, например,
//включение в каждый объект переменных, нужных только для супервизора.
//Например, переменные First,Last - указатели на начало и конец списка,
// Supervisor - чтобы отличать обычный объект от объекта-супервизора,
// Но главный недостаток, не в том, что тратятся лишнии десятки
//байт - необходимо программно запрещать вызов функций, недоступных для
//супервизора и спрайта. Например, супервизору нельзя сказать 'RenewRect',
//а спрайту - 'operator+=',или 'Animate'. Первая функция должна вызываться
//только для спрайта, а вторая и третья только для супервизора.
//   Необходимо все время помнить о том, что в данном случае означает
//эта переменная - это супервизор или это спрайт, а при использовании ссылок
//на супервизоры и спрайты, имеющих короткие имена, вероятность ошибок
//еще более может возрасти. Если программист  позаботится об разгра-
//ничении доступа в к функциям, о котором я только что говорил, тогда система
//будет работать стабильно, то есть во время будут появляться сообщения
//об ошибках и программист успешно будет их исправлять.
//   На первый взгляд кажется, что проще придумать два класса: класс
//супервизор и класс объект. Действительно, возможные ошибки по обращению
//к функциям, недопустимым для данного класса станут известны
//еще на этапе компиляции, не будет "сжираться" лишняя память. НО...возникает
//новая,куда более серьезная проблема - проблема иерархии классов, или
//наследования.
//   Возможно, я ошибаюсь, и существует более простой и надежный, способ
//создать аналогичный класс, но ничего другого на данный момент придумать
//не могу, и приходиться пользоваться тем, что есть.

//************************************************************************//
//***************** Функции-члены класса MOVEOBJ     *********************//
//************************************************************************//

int		MOVEOBJ::SupervisorCounter=0;		//число объектов-супервизоров
int		MOVEOBJ::WindowX=0;
int		MOVEOBJ::WindowY=0;
double	MOVEOBJ::SPEED_UNIT=1;
int		MOVEOBJ::TotalAnimatedObject;
MYRECT	MOVEOBJ::Lim(-24,-24,320+24,200+24);

//обнуляет все элементы классы
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

//конструктор объекта, использующегося в качестве структуры
//(конструктор по умолчанию)
MOVEOBJ::MOVEOBJ()
{
	//обнуляем все переменные
	//ЗДЕСЬ ВОЗМОЖЕН БАГ!!!
	NullAllData();

	Supervisor=NO;	//говорим о том, что это не супервизор
	ShootCounter=1;

}

//========= 'MOVEOBJ' констурктор объекта-супервизора ==============
MOVEOBJ::MOVEOBJ(SPRITE *Spr)
{
	#if DEBUGMESSAGES
		Debug("Run MOVEOBJ-supervisor constructor");
	#endif

	//обнуляем структуру
	NullAllData();

	//инициализация переменных
	SupervisorCounter++;  //увеличиваем число созданных объектов-супервизоров
	//Lim.Left=-24;
	//Lim.Top=-24;
	//Lim.Right=320+24;
	//Lim.Bottom=200+24;
	Supervisor=YES;	//даем знать всем, что этот объект - супервизор
	Sprite = Spr;  	//сохраняем указатель на спрайт
}

//=================== '~MOVEOBJ' деструктор =================
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

	//если удаляется объект-супервизор, надо удалить
	//цепочку объектов, привязанных к нему
	if ( Supervisor == YES )
	{
		//уничтожение созданных объектов
		int t=Counter;
		for (int i=0; i<t; i++)
		{
			Del(0);
		}
	}

}

//================= 'Show' - показать объект на экране
void MOVEOBJ::Show()
{
	if (Supervisor== YES)
	{
		Debug("MOVEOBJ::Show - illegal start");
	}
	Sprite -> Show( int(x-WindowX), int(y-WindowY), SpriteIndex );
}

//================= 'ShowAll' - показать все объекты на экране
void MOVEOBJ::ShowAll()
{
	for(int i=0; i<Counter; i++)
	{
		MOVEOBJ *ob=&operator[](i);
		ob -> Show();
	}
}


//==================анимация объектов=====================
void MOVEOBJ::Animate(void)
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::Animate - illegal start");
		return;
	}

	MOVEOBJ *ob = First;

	//перемещение обьектов
	for ( int i=0; i<Counter; i++ )
	{
		int x=int(ob->x);
		//если этот объект надо всегда анимировать
		// или объект в полосе близкой от окна

		if ( ob->AlwaysAnimate ||
			( x>(WindowX-100) && x<(WindowX+320+100) )
		   )
		{
			ob->Show();	//показываем объект
			ob->RenewXY();  //обновляем координаты X и Y
			ob->RenewRect();//обновляем структуру Rect
		}
		else
		{
			//ob->Show();	//показываем объект
		}

		TotalAnimatedObject++;

		//получаем адрес следующего объекта
		ob = ob->Next;
	}

restart:
	ob = First;
	//удаление вышедших за экран
	for ( i=0; i<Counter; i++ )
	{
		//обработка ситуации выхода спрайта за экран
		if ( (ob->y > Lim.Bottom) || (ob->y < Lim.Top) ||
			(ob->x < Lim.Left) || (ob->x > Lim.Right) )
		{
			//вызываем функцию-член удаления объекта
			Del( ob );
			goto restart;
		}

		ob = ob->Next;
	}

}

//==================анимация объектов=====================
void MOVETXT::Animate(void)
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::Animate - illegal start");
		return;
	}

	MOVEOBJ *ob = First;

	//перемещение обьектов
	for ( int i=0; i<Counter; i++ )
	{
		int x=int(ob->x);
		//если этот объект надо всегда анимировать
		// или объект в полосе близкой от окна
		ob->Show();	//показываем объект
		ob->RenewXY();  //обновляем координаты X и Y
		ob->RenewRect();//обновляем структуру Rect

		TotalAnimatedObject++;

		//получаем адрес следующего объекта
		ob = ob->Next;
	}

restart:
	ob = First;
	//удаление вышедших за экран
	for ( i=0; i<Counter; i++ )
	{
		//обработка ситуации выхода спрайта за экран
		if ( (ob->y > Lim.Bottom) || (ob->y < Lim.Top) ||
			(ob->x < Lim.Left) || (ob->x > Lim.Right) )
		{
			//вызываем функцию-член удаления объекта
			Del( ob );
			goto restart;
		}

		ob = ob->Next;
	}
	ANIM::Animate();
}



//============== 'DelAll' - удалить все объекты из списка =========
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

//=============== 'Del' удаление объекта obj из списка =====================
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

	//проверка исключительной ситуации
	if ( Obj == NULL )
	{
		Debug("'MOVEOBJ::Del' - Obj==NULL!");
		return;
	}

        //проверка исключительной ситуации
	if ( Counter == 0 )
	{
		Debug("'MOVEOBJ::Del' - Counter == NULL!");
		return;
	}



	//был создан только один объект ?
	if ( Counter == 1 )
	{
		delete Obj;
		First = NULL;
		Last  = NULL;
		Counter = 0;
		return;
	}


	//удаляется первый обьект ?
	if ( First == Obj )
	{
		First = Obj -> Next;
		Obj -> Next -> Prev = NULL;
		delete Obj;
		Counter--;
		return;
	}

	//удаляется последний объект
	if ( Last == Obj )
	{
		Obj -> Prev -> Next = NULL;
		Last = Obj -> Prev;
		delete Obj;
		Counter--;
		return;
	}

	//удаляется объект где-то в середине
	Obj -> Prev -> Next = Obj -> Next;
	Obj -> Next -> Prev = Obj -> Prev;
	delete Obj;
	Counter--;

}

//================создание нового объекта==================
// int size - количество памяти для этого объекта
int MOVEOBJ ::New(MOVEOBJ  *Fallobj, int size)
{
	if (Supervisor != YES)
	{
		Debug("MOVEOBJ::New - illegal start");
		return FALSE;
	}


    //адрес экрана туда-же
    Fallobj->Sprite=Sprite;

	//выделяем память под объект
	MOVEOBJ *NewObj = (MOVEOBJ *) new char[size];

	//обработка нехватки памяти
	if ( NewObj == NULL)
	{
		Debug("'MOVEOBJ::New' not enough memory");
		return FALSE;
	}

	//копируем объект в выделенную память
	memcpy( NewObj, Fallobj, size );

	//обработка создания первого объекта
	if ( Counter == 0)
	{
		NewObj -> Prev = NULL;	// он первый и ...
		NewObj -> Next = NULL;  // ... последний
		First = NewObj;
		Last =  NewObj;
	}

	//иначе 'подклеиваем' объект в конец списка
	else
	{
		NewObj -> Prev = Last;
		NewObj -> Next = NULL;	// ... он же последний
		Last->Next = NewObj;
		Last = NewObj;
	}

	Counter++;
	return TRUE;
}

//==============обновление структуры Rect====================
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

//================ 'RenewXY' обновляет координаты X и Y ============
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

//================ 'Set' - установка переменных ============
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

//============== 'operator[]' возвращает ссылку на объект =================
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

	//создаем указатель на объект
	MOVEOBJ *Obj = First;


	//последовательно перебираем все указатели
	for (int k=0; k<i; k++)
	{
		Obj = Obj->Next;
	}

	//возвращаем ссылку ( Но не само значение ! )
	return *Obj;
}

//============== 'oprator+=' добавление объекта в список ============
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
//******************* ФУНКЦИИ-ЧЛЕНЫ КЛАССА ANIM ****************
//**************************************************************

//конструктор
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

		//когда кадры идут вперед
		if ( FrameSpeed>0)
		{

			//если вышла за рамки - на начало
			if ((FrameCurrent<FrameFirst) || int(FrameCurrent)>FrameLast)
			{
				FrameCurrent = FrameFirst;
			}
		}
		//когда кадры идут назад
		else
		{

		//если вышла за рамки - на начало
		if (int(FrameCurrent)>FrameFirst || int(FrameCurrent)<FrameLast)
		{
			FrameCurrent = FrameFirst;
		}
	}
		SpriteIndex = int(FrameCurrent);
	}
}

//анимация объектов
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

		//Если время жизни изначально неравнялись
		//нулю уменьшаем время жизни объекта
		if ( ob->TimeLive>=2 ) ob->TimeLive--;

		//Если время жизни объекта закончилось,
		//удаляем объект
		if ( ob->TimeLive==1 )
		{
			Del (ob);
			i--;
			continue;
		}

                /*
                //удаляем объект который ушел далеко назад
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
/*		класс MINDOBJ					*/
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

    //инициализации
    ob.go_num=StartGo;
    ob.frame_num=StartFrame;
    ob.go_max=NumGo;	//число элементов в массиве
    ob.frame_max=NumFrame;

    if (StartGo>=ob.go_max)
    {
        Fatal("MINDOBJ::Add - StartGo too big");
    }
    if (StartFrame>=ob.frame_max)
    {
        Fatal("MINDOBJ::Add - StartFrame too big");
    }

    //выделяем память под массив способа движение
    ob.going=new GOING[ob.go_max];
    if (!ob.going) Fatal("MINDOBJ - out of memory for going");
    ob.framing=new FRAMING[ob.frame_max];
    if (!ob.framing) Fatal("MINDOBJ::MINDOBJ - out of memory for framing");

    //копируем в выделенную память то, что надо
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

//деструктор
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
            //загружаем новый элемент
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
        //загружаем новый элемент
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
        //загружаем новый элемент
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
        //загружаем новый элемент
        Go = going[go_num];
    }


	MOVEOBJ::RenewXY();
}

//удаление объекта из списка
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
		//в первую очередь смотрится переменная из Go
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
//******************** класс LIST - список *******************************
//************************************************************************
/*
//конструктор списка
LIST::LIST(SPRITE* Spr)
{
	Sprite=Spr;	//запоминаем адрес объекта типа спрайт

	Counter=0;	//пока число объектов в списке равно нулю

	First=NULL;
        Last=NULL;
}

//добавление объекта в список
//obj - адрес MOVEOBJ-та или производного от него
// size - размер объекта
// возврат: TRUE - объект включен в список
//	    FALSE - нехватка памяти для объекта
int LIST::Add(MOVEOBJ  *obj, int size)
{
        //адрес экрана туда-же
        obj->Sprite=Sprite;

	//выделяем память под объект
	MOVEOBJ *NewObj = (MOVEOBJ *) new char[size];

	//обработка нехватки памяти
	if ( NewObj == NULL)
	{
		Debug("'MOVEOBJ::New' not enough memory");
		return FALSE;
	}

	//копируем объект в выделенную память
	_fmemcpy( NewObj, obj, size );

	//обработка создания первого объекта
	if ( Counter == 0)
	{
		NewObj -> Prev = NULL;	// он первый и ...
		NewObj -> Next = NULL;  // ... последний
		First = NewObj;
		Last =  NewObj;
	}

	//иначе 'подклеиваем' объект в конец списка
	else
	{
		NewObj -> Prev = Last;
		NewObj -> Next = NULL;	// ... он же последний
		Last->Next = NewObj;
		Last = NewObj;
	}

	Counter++;
	return TRUE;
}


/*
//==================анимация объектов=====================
void LIST::Animate()
{

	ANIM *ob = (ANIM*) First;

	//так называемая "анимация" объектов
	for ( int i=0; i<Counter; i++ )
	{
			ob->RenewXY();  //обновляем координаты X и Y
			ob->RenewRect();//обновляем структуру Rect
                        ob->RenewFrame();
	                ob->Show();	//показываем объект

			//получаем адрес следующего объекта
			ob = (ANIM*)ob->Next;
	}

restart:
	ob = (ANIM*)First;
	//удаление вышедших за экран
	for ( i=0; i<Counter; i++ )
	{
		//обработка ситуации выхода спрайта за экран
		if ( (ob->y > ob->Lim.Bottom) || (ob->y < ob->Lim.Top) ||
			(ob->x < ob->Lim.Left) || (ob->x > ob->Lim.Right) ||
			!ob->RenewTimeLive() )
		{
			//вызываем функцию-член удаления объекта
			Del( ob );
			goto restart;
		}

		ob = (ANIM*)ob->Next;
	}

}


//получаем адрес i-го элемента
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

//=============== 'Del' удаление объекта obj из списка =====================
void LIST::Del(MOVEOBJ *Obj)
{
	//проверка исключительной ситуации
	if ( Obj == NULL )
	{
		Debug("'MOVEOBJ::Del' - Obj==NULL!");
		return;
	}

        //проверка исключительной ситуации
	if ( Counter == 0 )
	{
		Debug("'MOVEOBJ::Del' - Counter == NULL!");
		return;
	}


	//был создан только один объект ?
	if ( Counter == 1 )
	{
		delete Obj;
		First = NULL;
		Last  = NULL;
		Counter = 0;
		return;
	}


	//удаляется первый обьект ?
	if ( First == Obj )
	{
		First = Obj -> Next;
		Obj -> Next -> Prev = NULL;
		delete Obj;
		Counter--;
		return;
	}

	//удаляется последний объект
	if ( Last == Obj )
	{
		Obj -> Prev -> Next = NULL;
		Last = Obj -> Prev;
		delete Obj;
		Counter--;
		return;
	}

	//удаляется объект где-то в середине
	Obj -> Prev -> Next = Obj -> Next;
	Obj -> Next -> Prev = Obj -> Prev;
	delete Obj;
	Counter--;

}


//=================== '~MOVEOBJ' деструктор =================
LIST::~LIST(void)
{

	#if DEBUGMESSAGES
		Debug("Run MOVEOBJ destructor");
	#endif

	//уничтожение созданных объектов

        int t=Counter;

	for (int i=0; i<t; i++)
        {
        	Del(First);
	}

}
*/