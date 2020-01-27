//SpriteEditor.cpp
#ifndef __SPRITEEDITOR__H
#define __SPRITEEDITOR__H

#include "Screen.h"
#include "Sprite.h"
//класс редактора спрайтов
class SPRITEEDITOR
{
public:
	SPRITEDITOR();
	//~SPRITEEDITOR();
	int Editor(SPRITE * spr, int current);
};

#endif