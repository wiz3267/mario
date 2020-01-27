//Rects.h
#ifndef __RECTS_H
#define __RECTS_H

#define BIG_HORZ 0x02	//больше горизонтальная
#define BIG_VERT 0x04	//больше вертикальная

//---------- 'MYRECT' - описывает прямоугольную область -------------
struct MYRECT {

public:
    MYRECT(int x1,int y1,int x2,int y2) :
    	 Left(x1), Top(y1), Right(x2), Bottom(y2) {;}
    MYRECT() {;}
    void Set(int x,int y,int x1,int y1) { Left=x,Top=y,Right=x1,Bottom=y1; }
    int Left;
    int Top;
    int	Right;
    int	Bottom;
};
//-------------------------------------------------------------------


int CheckUnionRects(MYRECT& rect1, MYRECT & rect2);
int DetermineSystem(MYRECT&,MYRECT&,MYRECT&);

#endif