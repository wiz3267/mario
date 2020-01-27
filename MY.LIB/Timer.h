//Timer.h
#ifndef __TIMER_H
#define __TIMER_H

//******************************************************************
//******* TIMER.H ������������ ���� ��� ������ � �������� **********
//******************************************************************

class TIMER
{
public:
	static int CountObjects;	//����� ��������� �������� ���� TIMER
	volatile unsigned long TotalCounter;	//������� ����� ���������� � ������ ������������� �������

//******************** ������-����� ***************
public:
	volatile int Counter;		//������� ����� ����������
	int Freq;		//������� �������,����
	static const double MIN_FREQ;	//����������� �������
	static const double MAX_FREQ;	//������������ �������


//********************** �������-����� **************************
public:
//	int  GetCounter();		//��������� �������� ��������
	unsigned long GetTotalCounter() { return TotalCounter; };
	void Restart(double Freq);	//������� ������� � ����� ��������
//	void SetCounter(int count);	//��������� �������� ��������
	TIMER(double freq=MIN_FREQ);	//�������������� ������ ���������� 0x08
	~TIMER(void);			//��������������� �������
};

extern TIMER Timer;

#endif