//Mouse.h
#ifndef __MOUSE_H__
#define __MOUSE_H__

class MOUSE
{
public:
	int x,y;
	int Buttons;
	enum { 
		BUTTON_LEFT		=	0x01,
		BUTTON_RIGHT	=	0x02
	};
};

#endif