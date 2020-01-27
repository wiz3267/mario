//Debug.h

#ifndef __DEBUG_H
#define __DEBUG_H

//*********************************************************
//**** Прототипы функции для DEBUG.CPP ********************
//*********************************************************

//выдача отладочного сообщения
void Debug(char far *);

#define MSG_UPDATE 1
#define MSG_NOUPDATE 0

//выдача сообщения
void Msg(char far *,int=12,int flag=MSG_UPDATE);

//выдача сообщения об ошибке и завершение работы программы ===
void Fatal(char far * str);

#endif