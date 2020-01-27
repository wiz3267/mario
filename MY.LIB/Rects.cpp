//Rects.cpp

#include "stdafx.h"

#include "rects.h"
#include "debug.h"


#define TRUE  1
#define FALSE 0

//обменивает две переменные
void swap(int& a,int& b)
{
	int c=a;
	a=b;
	b=c;
}

//решает задачу нахождения пересечения множеств натуральных чисел
//[a,b] и [c,d]
//возврат: 0 - нет решений
//число 1...32767 - длина общего отрезка
//Возврат:
//TRUE - если есть одно или мн-во решений, в переменные x1, x2 заносятся решения
//FALSE - если нет решений, тогда переменные x1 и x2 остаются без изменений

int DetermineSystem(int a,int b,int c, int d, int &x1, int &x2)
{
        //обрабатываем недопустимую ситуацию
        if (a>b)
        {
        	Fatal("DetermineSystem - a>b !");
        }

        if (c>d)
        {
        	Fatal("DetermineSystem - c>d !");
        }


        // случай (1)
	if ( b<c || d<a ) return FALSE;

        //делаем отрезок [a,b] большим или равным отрезку [c,d]
        if ( (b-a) < (d-c) )
        {
        	swap(a,c);
                swap(b,d);
        }

        // из условия (1) следует, что c<=b && a<=d
        // Cлучай (2) отрезок [c,d] внутри [a,b]
        if ( a<=c && d<=b) { x1=c; x2=d; return x2-x1+1; }

        // из (1) и (2) следует, что c<=b и a<=d
        // и либо c<a либо b<d и из того, что отрезок [c,d] не больше [a,b]
        // делаем такой вывод:
        // Если c<a
        if (c<a) { x1=a; x2=d; return x2-x1+1; }
        // иначе b<d
        else { x1=c; x2=b; return x2-x1+1; }

}


//Решает задачу пересечения мн-в [a,b] и [c,d]
//Возвращает длину общего отрезка, или 0, если нет решений
int DetermineSystem(int a,int b,int c, int d)
{

        int x1,x2;
        //обрабатываем недопустимую ситуацию
        if (a>b)
        {
        	Fatal("DetermineSystem - a>b !");
        }

        if (c>d)
        {
        	Fatal("DetermineSystem - c>d !");
        }


        // случай (1)
	if ( b<c || d<a ) return FALSE;

        //делаем отрезок [a,b] большим или равным отрезку [c,d]
        if ( (b-a) < (d-c) )
        {
        	swap(a,c);
                swap(b,d);
        }

        // из условия (1) следует, что c<=b && a<=d
        // Cлучай (2) отрезок [c,d] внутри [a,b]
        if ( a<=c && d<=b) { x1=c; x2=d; return x2-x1+1; }

        // из (1) и (2) следует, что c<=b и a<=d
        // и либо c<a либо b<d и из того, что отрезок [c,d] не больше [a,b]
        // делаем такой вывод:
        // Если c<a
        if (c<a) { x1=a; x2=d; return x2-x1+1; }
        // иначе b<d
        else { x1=c; x2=b; return x2-x1+1; }

}


//находит общий прямоугольник
int DetermineSystem(MYRECT &a, MYRECT &b, MYRECT &c)
{
	if (
	DetermineSystem(a.Left, a.Right, b.Left, b.Right, c.Left, c.Right) &&
	DetermineSystem(a.Top, a.Bottom, b.Top, b.Bottom, c.Top, c.Bottom)
           )

        return 1;

        else return 0;
}

//проверяет, пересеклись ли прямоугольники
//Возврат FALSE - не пересеклись
// BIG_HORZ - больше горизонтальная часть
// BIG_VERT - больше вертикальная часть
int	CheckUnionRects(MYRECT & rect1, MYRECT & rect2)
{
	int x1,y1,x2,y2,x3,y3,x4,y4;
	x1=rect1.Left;
	y1=rect1.Top;
	x2=rect1.Right;
	y2=rect1.Bottom;

	x3=rect2.Left;
	y3=rect2.Top;
	x4=rect2.Right;
	y4=rect2.Bottom;

	//подготовка к выполнению следующий условий:
	// x1<x2,y1<y2
	// x3<x4,y3<y4
	if ( x2<x1 )	swap(x2,x1);
	if ( x4<x3 )	swap(x4,x3);
	if ( y2<y1 )	swap(y2,y1);
	if ( y4<y3 )	swap(y4,y3);
	//чтобы выполнялось: x2-x1>=x4-x3
	//		     y2-y1>=y4-y3
	if ( x2-x1 < x4-x3 )
	{
		swap(x2,x4);
		swap(x1,x3);
	}

	if ( y2-y1 < y4-y3 )
	{
		swap(y2,y4);
		swap(y1,y3);
	}

	int horz,vert;
	if ( (horz=DetermineSystem(x1,x2,x3,x4)) == 0) return FALSE;
	if ( (vert=DetermineSystem(y1,y2,y3,y4)) == 0) return FALSE;
	if ( horz>vert ) return BIG_HORZ;
	if ( vert>horz ) return BIG_VERT;
	return BIG_HORZ | BIG_VERT; //равны
}
