//Total.h
#ifndef __TOTAL__H
#define __TOTAL__H

#include <FCNTL.H>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> //чтобы правильно работала функция randomize()

#include "Person.h"
#include "Screen.h"
#include "Mario.h"
#include "Sprite.h"
#include "Idsprite.h"
#include "Keyboard.h"
#include "Timer.h"
#include "Sound.h"
#include "Level.h"
#include "Mouse.h"
#include "IDSound.h"

/*******************************************
/**      Глобальные переменные	        /**/
//**************************************/**/
/**/				  	/**/
/**/extern	SOUND   Sound;	        /**/
/**/extern	SPRITE  Sprite;		/**/
/**/extern	SPRITE  LvSpr;		/**/
/**/extern	SPRITE  BigFont;        /**/
/**/extern	LEVEL	Level;	        /**/
/**/extern	SUPERMARIO  Supermario; /**/
/**/extern	MOUSE	Mouse;		/**/
/**/extern	SCREEN	scr;		/**/
/**/extern	LOG Log;		/**/
/**/				        /**/
/******************************************/

CString itoc(int);
extern CString _S;
#endif
