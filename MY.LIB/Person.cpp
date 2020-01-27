//Person.cpp
#include "stdafx.h"

#include "person.h"
#include "sprite.h"
#include "moveobj.h"
#include "screen.h"
/////////////////
// PERSON.CPP  //
/////////////////

void PERSON::Show()
{
	//показываем спрайт

        if (Movement & UNUSED)
        {
                int Movem = Movement ^ UNUSED;
		if (Speedx>0)
			Sprite -> Show( int(x-WindowX), int(y-WindowY), SpriteIndex , Movem);
		else
			Sprite -> Show( int(x-WindowX), int(y-WindowY), SpriteIndex, PERSON::LEFT | Movem);
        }

        else
        {
                	Sprite -> Show( int(x-WindowX), int(y-WindowY), SpriteIndex, Movement );
        }


}

