//Debug.h

#ifndef __DEBUG_H
#define __DEBUG_H

//*********************************************************
//**** ��������� ������� ��� DEBUG.CPP ********************
//*********************************************************

//������ ����������� ���������
void Debug(char far *);

#define MSG_UPDATE 1
#define MSG_NOUPDATE 0

//������ ���������
void Msg(char far *,int=12,int flag=MSG_UPDATE);

//������ ��������� �� ������ � ���������� ������ ��������� ===
void Fatal(char far * str);

#endif