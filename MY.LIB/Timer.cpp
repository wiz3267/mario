//Timer.cpp

#include "stdafx.h"

#include "timer.h"
#include "sprite.h"
#include "screen.h"
#include "debug.h"

//������� ���������������� ������
TIMER Timer;

//************************************************************
//'timer.cpp' �������-����� ������ TIMER ��� ������ � ��������
//************************************************************

#define TIMER_INT	0x1c

unsigned long	int08h_old;

//�������������� ����������� ����������
	int	TIMER::CountObjects=0;
        const double TIMER::MAX_FREQ=48000u;
        const double TIMER::MIN_FREQ=18.20648;


// ����������� �������
// int freq - ������� ������� (MIN_FREQ - MAX_FREQ)
TIMER::TIMER(double freq)
{
}

//������������� ������ � ����� ��������
//����������� ������� ������ ���� 1193180/65536=18.20648 ����
//������������ ������� ����� ���� 1193180/1=1193180 ����
void TIMER::Restart(double freq)
{
}
//=====================����������=====================
TIMER::~TIMER()
{
}
