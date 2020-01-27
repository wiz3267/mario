//Timer.h
#ifndef __TIMER_H
#define __TIMER_H

//******************************************************************
//******* TIMER.H заголовочный файл для работы с таймером **********
//******************************************************************

class TIMER
{
public:
	static int CountObjects;	//число созданных объектов типа TIMER
	volatile unsigned long TotalCounter;	//счетчик числа прерывания с начала инициализации таймера

//******************** ДАННЫЕ-ЧЛЕНЫ ***************
public:
	volatile int Counter;		//счетчик числа прерываний
	int Freq;		//частота таймера,Герц
	static const double MIN_FREQ;	//минимальная частота
	static const double MAX_FREQ;	//максимальная частота


//********************** ФУНКЦИИ-ЧЛЕНЫ **************************
public:
//	int  GetCounter();		//получение значения счетчика
	unsigned long GetTotalCounter() { return TotalCounter; };
	void Restart(double Freq);	//рестарт таймера с новой частотой
//	void SetCounter(int count);	//установка значения счетчика
	TIMER(double freq=MIN_FREQ);	//инициализирует вектор прерывания 0x08
	~TIMER(void);			//восстанавливает частоту
};

extern TIMER Timer;

#endif