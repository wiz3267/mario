//Timer.cpp

#include "stdafx.h"

#include "timer.h"
#include "sprite.h"
#include "screen.h"
#include "debug.h"

//создаем предопределенный объект
TIMER Timer;

//************************************************************
//'timer.cpp' функции-члены класса TIMER для работы с таймером
//************************************************************

#define TIMER_INT	0x1c

unsigned long	int08h_old;

//инициализируем статические переменные
	int	TIMER::CountObjects=0;
        const double TIMER::MAX_FREQ=48000u;
        const double TIMER::MIN_FREQ=18.20648;


// КОНСТРУКТОР таймера
// int freq - частота таймера (MIN_FREQ - MAX_FREQ)
TIMER::TIMER(double freq)
{
}

//перезапускаем таймер с новой частотой
//минимальная частота должна быть 1193180/65536=18.20648 герц
//максимальная частота может быть 1193180/1=1193180 герц
void TIMER::Restart(double freq)
{
}
//=====================деструктор=====================
TIMER::~TIMER()
{
}
