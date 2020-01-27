//Sound.h
#ifndef __SOUND__H
#define __SOUND__H

#include <mmsystem.h>
#include "Log.h"

//**************************************************************
//** описание класса 'SOUND' - проигрывание и обработка звука **
//**************************************************************

void MidiStop();


struct SNDSTRUCT
{
	char * fname;
	BYTE * sounddata;	//указатель на звуковые данные
	int soundlen;			//длина звуковой последовательности
	int far * IsPlaying;	//адрес флага состояния
	int frequency;			//частота воспроизведения
	int flag;				//как проиграть музыку
	int idsound;			//идентификатор звука

	SNDSTRUCT()
	{
		fname=NULL;
		sounddata=NULL;
		soundlen=NULL;
		frequency=NULL;

	}
	~SNDSTRUCT()
	{
		if (sounddata) delete sounddata;
	}
};

class SOUND
{
public:

	enum MONOSTEREO
	{
		MONO,
		STEREO
	};

	enum BITCOUNT
	{
		BIT8,
		BIT16
	};

	enum {
		COUNTMAX=100,	//это число можно менять: максимальное число звуков
		NOSTOP=1,		//звук не должен прерываться следующим звуком
		YESSTOP=0,		//звук может прерваться следующим звуком
		YESPLAYING=1,
		NOPLAYING=0
	};

	enum SNDERROR
	{
		SUCCESS,
		ERR_COMMON,	//общая ошибка
		ERR_WAVEDEVICENOTOPEN,
		ERR_OUTOFMEMORY,
		ERR_SOUNDSTOMANY,
		ERR_SOUNDNOTFOUND,
		ERR_FILENOTFOUND
	};

private:


static int CountObject;	//число объектов класса SOUND

	int current;			//ID проигрываемого в данным момент звука
	int count;				//число звуков
	//int load_status;		//статус загрузки
	unsigned int isplay;	//флаг состояния

	HWAVEOUT waveOut;		//дескриптор вывода звука
	BOOL PrepareBuffers(int i);
	void PlaySoundBuffer();
	
public:
	bool sound_enable;		//разрешить звук
	BOOL InitDirectSound();		//инициализация директ саунда
	//получение ID проигрываемого звука
	int GetCurrent() {return current;}

	//открытие звукового устройства вывода
	SNDERROR opendevice(int freq, MONOSTEREO, BITCOUNT);	
	
	SNDERROR closedevice();//закрытие звукового устройства

	SNDSTRUCT sounds[COUNTMAX]; //массив указателей,на информацию о звуках
	SOUND(void);				//конструктор
	~SOUND(void);				//деструктор
	SNDERROR load(char* fname,int freq, MONOSTEREO, BITCOUNT,int idsound, int fileoffset=0);	
	SNDERROR play(int ID,int flag=0);	//проиграть звук по ID с флагом
	SNDERROR sndplay(SNDSTRUCT far & sndplay);	//проиграть звук
	SNDERROR stop();		//остановить проигрывание
	void testdirectsound();
	void unload(int n);		//удалить заданный звук с номером n
};

#endif