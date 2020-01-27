//Moveobj.h
#ifndef __MOVEOBJ_H
#define __MOVEOBJ_H

#include "rects.h"
#include "debug.h"


class SPRITE;		//предварительное объявление класса

class MOVEOBJ 
{

	void NullAllData();
	//YES - значит супервизор, NO - значит объект
public:	enum { YES=1, NO=-1 };	//значение переменной Supervisor

//*********************** ЧЛЕНЫ-ДАННЫЕ ************************
protected:
static	int SupervisorCounter;//число созданных объектов-супервизоров
	SPRITE* Sprite;		//указатель на объект типа SPRITE
	int	Supervisor;	//флаг супервизора
	MOVEOBJ* First;   	//указатель на первый обьект cписка
	MOVEOBJ* Last;		//указатель на последний объект списка
public:
static	int TotalAnimatedObject;
	double	Acceleratx;	//ускорение по осям
	double	Acceleraty;
	int	Counter;	//число созданных объектов в списке
	MYRECT	Hot;		//определяет горячее пятно спрайта
       MOVEOBJ* Next;		//указатель на следующий обьект. Если это последний обект Next=NULL
       MOVEOBJ* Prev;		//указатель на предыдущий обект.Если это первый обьект Prev=NULL
	int	Link;		//привязка объекта
static	MYRECT	Lim;		//границы, выйдя за которые объекты удаляются
	MYRECT	Rect;		//определяет объект на экране
	double	Speedx;		//проекции скорости на оси
	double	Speedy;
	int	SpriteIndex;	//индекс спрайта
	double	Speed;		//модуль вектора скорости
	int	Status;		//состояние обьекта
static	double	SPEED_UNIT;	//единица скорости
static	int	WindowX;	//координата X окна вывода
static	int	WindowY;	//координата Y окна вывода
	double	x,y;		//текущие координаты обьекта
	int	ShootCounter;	//число выстрелов, после чего объект
	int	AlwaysAnimate;	//всегда ли надо анимировать объекты ?
				//убивается
//********************** ФУНКЦИИ-ЧЛЕНЫ ***************************
//(пометка YES - значит функция предназначена только для супервизора
// NO - функция не предназначена для супервизора, то есть предназначена
// только для объекта)
public:
	void Animate();				//YES анимация обектов
virtual	void Del (MOVEOBJ *Obj);		//YES удаление обьекта из списка по его адресу,
	void Del (int n) { Del(&operator[](n));}//YES удаление объекта с номером n
	void DelAll();				//YES удаление всех объектов
virtual void Destroy(int who) {}		//вызывается когда объект кто-то убивает
	void MakeSupervisor(SPRITE*spr)		//делает объект супервизором
	{
		Supervisor=YES;
		Sprite=spr;
	}
	     MOVEOBJ(SPRITE *Sprite);		//YES конструктор супервизора
	     MOVEOBJ();				//NO конструктор move-объекта
	    ~MOVEOBJ();                     	//YES, NO деструктор
	int  New( MOVEOBJ *Obj, int size);	//YES создание нового объекта
	MOVEOBJ& operator[] (int i);		//YES получить ссылку на объект i
	void operator+= (MOVEOBJ &);		//YES добавить объект в список
virtual void RenewFrame() {}
	void RenewRect();			//NO  обновить структуру Rect
virtual int RenewTimeLive() {return 1;}
virtual	void RenewXY();				//NO  обновить координаты X,Y
	void Set(double x=0,double y=0,double sx=0,double sy=0,double acx=0,double acy=0);    //NO установить наиболее важные переменные
virtual	void Show();				//NO показываем объект
	void ShowAll();				//YES показать все объекты
};


//****************************************************
//************* class ANIM - анимация объектов *******
//****************************************************
//класс надстривает MOVEOBJ таким образом, что новый объекты
//могут самоуничтожаться (переменная TimeLive) и изменять
//последовательно c нужной скоростью номера спрайтов (в определенном
//отрезке значений)

class ANIM: public MOVEOBJ
{
public:
	int FrameFirst, FrameLast;
	double FrameSpeed, FrameCurrent;
	int TimeLive;

public:
	ANIM ();
	ANIM(SPRITE *s) : MOVEOBJ(s) {;}
	//перегружаем [] для правильного преобразования типа
	ANIM & operator[] (int i) {return (ANIM&) MOVEOBJ::operator[](i); }
	//заметьте, MOVEOBJ & operator+= также остается !
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
//************* class MINDOBJ - умные, разумные объекты *******
//************************************************************
//класс ANIM позволяет создавать простейшую анимацию. Если вас не устраивают
//возможности класса ANIM, используйте класс MINDOBJ

//0,-1,10, 0,1,10, 0	мостик вверх, вниз
//

class MINDOBJ : public ANIM
{
public:
        //структура "хотьба" (кому? - ясно,что не мне)
        struct GOING
	{
		double Speed_x,Speed_y;	//перемещение по осям за один шаг
//               	Accelerat_x,Accelerat_y;
		int  Time;	    //время этого передвижения(число шагов)
        			   //если Time==0, значит этот шаг последний
        };
        //как должны меняться фазы
        struct FRAMING
        {
        	int Fase,	//какая фаза
				Time;	//сколько времение она будет держаться
                    		//аналогично GOING, если Time==0 - на начало
	};

	GOING  * going;		//указатель на способ движения
	FRAMING * framing;        //указатель на способ смены фазов

        int go_num, frame_num;	//текущие элементы
        int go_max, frame_max;	//число элементов

public:
	GOING  Go;		//текущие элементы
	FRAMING Frame;


    //команды
    enum {
		SET_SPEED		= -1,	//установить скорость
		SET_ACCELERAT   = -2,	//установить ускорение
        SET_INDEX		= -3	//перепрыгнуть на другой элемент
	};

        enum {
             PERSON=0x01,      //объект всегда смотрит в сторону перемещения
                               //(иначе отображается так, как нарисован)
             DANGER=0x02,	//объект опасный
	     			//(иначе неопасный)
             SOLID=0x04,	//объект твердый(нельзя пройти через него)
             			//(иначе прозрачный)
             LIFT=0x08,		//объект может переносить на себе(мостик,
	             		//тележка, лифт)
        	                //(иначе не может)
        };

        unsigned State;		//состояние элемента

        void Add(MINDOBJ&, int NumGo,GOING *go_ptr, int NumFrame,
	FRAMING *frame_ptr,int StartGo=0, int StartFrame=0);


	void Del (MOVEOBJ *Obj);	//удаление объекта из списка
	MINDOBJ(SPRITE *s) : ANIM(s) {;}
        MINDOBJ();
        ~MINDOBJ();         //деструктор
  	void operator+=(MINDOBJ&);
        MINDOBJ& operator[](int i) { return (MINDOBJ&) MOVEOBJ::operator[](i); }
        void RenewFrame();
        void RenewXY();
        void Show();

};



//перемещающийся текст
class MOVETXT : public ANIM
{
public:
	char* Message;		//сообщение
	char Color;			//цвет сообщения
	MOVETXT (SPRITE* spr) : ANIM(spr), Message(0) {}
	MOVETXT () : Message(0), Color(15) {;}
	void Animate();
	void operator+= (MOVETXT& ob) { New(&ob, sizeof(ob)); };
	void Show();
};



#endif