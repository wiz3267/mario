//Sound.h
#ifndef __SOUND__H
#define __SOUND__H

#include <mmsystem.h>
#include "Log.h"

//**************************************************************
//** �������� ������ 'SOUND' - ������������ � ��������� ����� **
//**************************************************************

void MidiStop();


struct SNDSTRUCT
{
	char * fname;
	BYTE * sounddata;	//��������� �� �������� ������
	int soundlen;			//����� �������� ������������������
	int far * IsPlaying;	//����� ����� ���������
	int frequency;			//������� ���������������
	int flag;				//��� ��������� ������
	int idsound;			//������������� �����

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
		COUNTMAX=100,	//��� ����� ����� ������: ������������ ����� ������
		NOSTOP=1,		//���� �� ������ ����������� ��������� ������
		YESSTOP=0,		//���� ����� ���������� ��������� ������
		YESPLAYING=1,
		NOPLAYING=0
	};

	enum SNDERROR
	{
		SUCCESS,
		ERR_COMMON,	//����� ������
		ERR_WAVEDEVICENOTOPEN,
		ERR_OUTOFMEMORY,
		ERR_SOUNDSTOMANY,
		ERR_SOUNDNOTFOUND,
		ERR_FILENOTFOUND
	};

private:


static int CountObject;	//����� �������� ������ SOUND

	int current;			//ID �������������� � ������ ������ �����
	int count;				//����� ������
	//int load_status;		//������ ��������
	unsigned int isplay;	//���� ���������

	HWAVEOUT waveOut;		//���������� ������ �����
	BOOL PrepareBuffers(int i);
	void PlaySoundBuffer();
	
public:
	bool sound_enable;		//��������� ����
	BOOL InitDirectSound();		//������������� ������ ������
	//��������� ID �������������� �����
	int GetCurrent() {return current;}

	//�������� ��������� ���������� ������
	SNDERROR opendevice(int freq, MONOSTEREO, BITCOUNT);	
	
	SNDERROR closedevice();//�������� ��������� ����������

	SNDSTRUCT sounds[COUNTMAX]; //������ ����������,�� ���������� � ������
	SOUND(void);				//�����������
	~SOUND(void);				//����������
	SNDERROR load(char* fname,int freq, MONOSTEREO, BITCOUNT,int idsound, int fileoffset=0);	
	SNDERROR play(int ID,int flag=0);	//��������� ���� �� ID � ������
	SNDERROR sndplay(SNDSTRUCT far & sndplay);	//��������� ����
	SNDERROR stop();		//���������� ������������
	void testdirectsound();
	void unload(int n);		//������� �������� ���� � ������� n
};

#endif