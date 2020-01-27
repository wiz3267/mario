//Sound.cpp

#include "stdafx.h"
#include <mmsystem.h>
#include <dsound.h>
#include "IdSound.h"

//*******************************************************************
//***************** �������-����� ������ 'SOUND' ********************
//*******************************************************************
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug.h"
#include "sound.h"
#include "total.h"

extern SOUND Sound;
extern LOG Log;

HWND hMainWnd = NULL;
LPDIRECTSOUND pDS = NULL;
LPDIRECTSOUNDBUFFER pDSBuffer = NULL;
int DIRECTSOUND_BUFFERSIZE=15000;

CString itoc(int M)
{
	CString k;
	k.Format("%i",M);
	return k;
}

int SOUND::CountObject=0;


//CALLBACK_FUNCTION

void CALLBACK waveOutProc(
  HWAVEOUT hwo,      
  UINT uMsg,         
  DWORD dwInstance,  
  DWORD dwParam1,    
  DWORD dwParam2     
)
{
	//Sound.Log.Write("CALLBACK waveOutProc!");
	if (uMsg==WOM_DONE)
	{
		WAVEHDR * hdr=(WAVEHDR*)dwParam1; // (DWORD) lpwvhdr 
		delete hdr->lpData;
		delete hdr;
		//Sound.Log.Write("CALLBACK delete lpData and hdr");
	}
}


//�������� ��������� ���������� ������
SOUND::SNDERROR SOUND::opendevice(int freq, SOUND::MONOSTEREO ms, SOUND::BITCOUNT bc)
{
	WAVEFORMATEX pwf;

	pwf.wFormatTag=WAVE_FORMAT_PCM;
	if (ms==MONOSTEREO::MONO) pwf.nChannels=1;
	else if (ms==MONOSTEREO::STEREO) pwf.nChannels=2;

	pwf.nSamplesPerSec=freq;
	pwf.nAvgBytesPerSec=pwf.nSamplesPerSec;
	
	if (ms==MONOSTEREO::STEREO) pwf.nBlockAlign=2;
	else if (ms==MONOSTEREO::MONO) pwf.nBlockAlign=1;

	if (bc==BIT16) pwf.nBlockAlign*=2;

	if (bc==BITCOUNT::BIT16) pwf.wBitsPerSample=16;
	else if (bc==BITCOUNT::BIT8) pwf.wBitsPerSample=8;

	if (waveOutOpen(&waveOut, WAVE_MAPPER, &pwf, DWORD(waveOutProc),0,
		CALLBACK_FUNCTION))
	{
		Log.Write("Open sound device FAILED!");
		waveOut=NULL;
		return ERR_COMMON;
	}
	Log.Write("open sound device ok");
	return SUCCESS;
}
	
SOUND::SNDERROR SOUND::closedevice()//�������� ��������� ����������
{
	int errClose=waveOutClose(waveOut);
	if (errClose==0) 
	{
		Log.Write("close waveout device ok");
		return SUCCESS;
	}
	else 
	{
		Log.Write("close waveout device failed!");
		return ERR_COMMON;
	}
}


//�����������
SOUND::SOUND(void)
{
	Log.Create("sound.log");
	const int SAMPLE_RATE=44100;

	opendevice(SAMPLE_RATE, MONOSTEREO::STEREO, BITCOUNT::BIT16);	

	sound_enable=true;

	CountObject++;
}

//��������� ����
SOUND::SNDERROR SOUND::sndplay(SNDSTRUCT far & ss)
{
	//���� �������� ���������� �� �������
	if (waveOut==NULL) return ERR_WAVEDEVICENOTOPEN;

	if (!sound_enable) return SUCCESS;

	//������������� ����
	stop();

	//��������� ������
	closedevice();

	//��������� ������ � ������ �������� �������������, ������ �������, ������������
	opendevice(ss.frequency,STEREO,BIT16);

	Log.Write(_S+ss.fname+" ("+itoc(ss.idsound)+")");

	//��������� ���� ��������� ������ ����
	WAVEHDR *hdr=new WAVEHDR;
	if (!hdr) return ERR_OUTOFMEMORY;
	ZeroMemory(hdr,sizeof(WAVEHDR));
	hdr->dwBufferLength=ss.soundlen;
	hdr->lpData=new char[ss.soundlen];
	hdr->dwFlags=WHDR_BEGINLOOP | WHDR_ENDLOOP;
	hdr->dwLoops=-1;

	if (hdr->lpData == NULL) 
	{
		delete hdr;

		return ERR_OUTOFMEMORY;
	}

	memcpy(hdr->lpData,ss.sounddata,ss.soundlen);
	
	int errOutPrepareHeader=waveOutPrepareHeader(waveOut,hdr,sizeof(WAVEHDR));
	int errOutWrite=waveOutWrite(waveOut,hdr,sizeof(WAVEHDR));

	if (errOutPrepareHeader==0 && errOutWrite==0)
	{
		//Log.Write("send data to wav device ok");
	}
	else
	{
		Log.Write("waveOutPrepareHeader="+itoc(errOutPrepareHeader));
		Log.Write("waveOutWrite="+itoc(errOutWrite));
	}
	return SUCCESS;
}

/*
DWORD WINAPI PlaySoundThread(LPVOID param)
{
	sndPlaySound((char*)param,SND_ASYNC);
	return 0;
}*/

//============= 'play' - ��������� ���� �� ID =============
SOUND::SNDERROR SOUND::play(int id,int flag)
{
    //���� ������� ���� ������������� � ������ "�� �������������"
    //� ������ ������������� ������ ���� - ���������� ������������
	//if (sounds[current].flag == NOSTOP && soundStatus()==YESPLAYING) return;
	//���� ����

	if (!sound_enable) return SUCCESS;
	//return SUCCESS;

	switch (id)
	{
		case SND_GHOTIC_FAST:
		case SND_ZASTAVKA:
		case SND_GHOTIC:
		{
			flag=255;
			//return SUCCESS;
		}
	
	}

	for(int n=0; n<count;n++)
	{
		if (sounds[n].idsound==id) break;
	}

	if (n==count) 
	{
		Log.Write("play: id=="+ itoc(id)+" ERR_SOUNDNOTFOUND");\
		return ERR_SOUNDNOTFOUND;
	}

	//Log.Write(_S+CString("Play: n= ") + n + " (" +itoc(sounds[n].idsound)+")");

	//sounds[n].flag=flag;
	current=id;
	if (flag==255) sndplay(sounds[n]);
	else
	{
		Log.Write(_S+sounds[n].fname+" ("+itoc(sounds[n].idsound)+")");
		//	if (pDSBuffer) pDSBuffer->Release();
		if (PrepareBuffers(n))
		{

			PlaySoundBuffer();
		}
	}

	return SUCCESS;
}

//============= 'stop' - ���������� ������� ���� =========
SOUND::SNDERROR SOUND::stop(void)
{
	int err=waveOutReset(waveOut);
	if (err==0) 
	{
		Log.Write("sound stop ok");
		return SNDERROR::SUCCESS;
	}
	else 
	{
		Log.Write("sound stop failed!");
		return SNDERROR::ERR_COMMON;
	}
}

//��������� ���� � ������ 
//���������� ����� ����������� ������
//SOUND::SNDERROR SOUND::load(char * fname,int freq, int idsound)

SOUND::SNDERROR SOUND::load(char* fname,  int freq, 
		SOUND::MONOSTEREO ms, SOUND::BITCOUNT bc, int ids, int dataoffset)
{
	if (count>=COUNTMAX) return ERR_SOUNDSTOMANY;

	SNDSTRUCT &snd=sounds[count];
	snd.fname=fname;
	snd.frequency=freq;
	snd.idsound=ids;

	Log.Write(_S+"load "+fname);

	CFile file;
	if (file.Open((char*)fname, file.modeRead))
	{
		int size=file.GetLength();
		file.Seek(dataoffset,CFile::begin);
		snd.soundlen=size-dataoffset;
		snd.sounddata=new BYTE[snd.soundlen];
		if (snd.sounddata != NULL)
		{
			file.Read(snd.sounddata,snd.soundlen);
			Log.Write("file.Read ok");
			count++;

			return SUCCESS;
		}
		else
		{
			Log.Write(_S+"out of memory"+fname);
			file.Close();
			return ERR_OUTOFMEMORY;
		}
		file.Close();
	}
	else
	{
		Log.Write("error: ERR_FILENOTFOUND");
		return ERR_FILENOTFOUND;
	}
	
}

//=============== 'unload' - ��������� ���� n �� ������ =============
void SOUND::unload(int n)
{
	if (n<0 || n>count-1 || count==0)
	{
		Fatal ("SOUND::unload - cannot unload not exist a sound!");
		return;
	}
	
	if (sounds[n].sounddata)
	{
			Log.Write("SOUND::unload("+itoc(n)+")");
			delete sounds[n].sounddata;
			sounds[n].sounddata=NULL;
	}
	
}

//================ ���������� ============================
SOUND::~SOUND(void)
{
	Log.Write("SOUND::~SOUND start");
    if ( CountObject != 0 )
    {
		#if DEBUGMESSAGES
		Debug("Run SOUND destructor");
		#endif

		//�������� ������
		for (int i=0; i<count; i++) unload(i);

		CountObject--;

		if (waveOut)
		{
			stop();
			closedevice();
		}
    }

    else	//�� ������ ������� �� ���� �������
    {
		#if DEBUGMESSAGES
		Log.Write("SOUND::~SOUND: CountObject == 0!");
		#endif
    }

}

void MidiStop()
{
}

BOOL CreateBuffers()
{
	HRESULT hRet;
	DSBUFFERDESC dsbd={0};
	dsbd.dwSize		=	sizeof(dsbd);
	dsbd.dwFlags	=	DSBCAPS_STATIC | DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = DIRECTSOUND_BUFFERSIZE;
	WAVEFORMATEX wf={0};
	wf.cbSize=sizeof(wf);
	wf.nSamplesPerSec=11025;
	wf.wBitsPerSample=8;
	wf.nChannels=1;
	wf.wFormatTag=WAVE_FORMAT_PCM;
	wf.nBlockAlign=1;
	wf.nAvgBytesPerSec=11025;

	dsbd.lpwfxFormat	= &wf;
	hRet = pDS->CreateSoundBuffer(&dsbd, &pDSBuffer, NULL);
	if (hRet != DS_OK)
	{
		Log.Write("CreateSoundBuffer fail");
		return (FALSE);
	}

	Log.Write("CreateSoundBuffer ok");

	return TRUE;
}

BOOL SOUND::PrepareBuffers(int n)
{
try 
{
	if (pDSBuffer==NULL) return FALSE;

	HRESULT hRet;
/////////////////////////////////////////////////////////
	void * pPtr1 = NULL;
	void * pPtr2 = NULL;
	DWORD dwSize1=0;
	DWORD dwSize2=0;

	//���������� ������ �������� ������
	DWORD dwWaveSize = Sound.sounds[n].soundlen;

	//�������� ������������� �������� �����
	int size=DIRECTSOUND_BUFFERSIZE;
	if (sounds[n].soundlen< size) size=sounds[n].soundlen;

	hRet = pDSBuffer->Lock(0, size, &pPtr1, &dwSize1, &pPtr2, &dwSize2, 0L);
	if (hRet != DS_OK)
	{
		Log.Write(_S+"Lock sound buffer fail (err="+itoc(hRet)+")");
		return (FALSE);
	}

	Log.Write("Lock sound buffer ok");

	//���� ����������, ��������� � ����� �������� ������
	//��������� � pPtr1, dwWaveSize
	BYTE *addr=(BYTE*)pPtr1;
	
	
	FillMemory(addr, DIRECTSOUND_BUFFERSIZE,128);
	for(DWORD i=0; i<dwSize1; i++)
	{
		addr[i]=Sound.sounds[n].sounddata[i];
	}

	//�� �������� �������������� �����
	pDSBuffer->Unlock( pPtr1, dwWaveSize, NULL, 0);
}
catch(...)
{
	Log.Write("SOUND::PrepareBuffers Exception!");
	return FALSE;
}
	return (TRUE);

}

//����������� �������� �����
void SOUND::PlaySoundBuffer()
{
try 
{
	pDSBuffer->SetCurrentPosition(0);

	pDSBuffer->Play(0,0,0);
}
catch(...)
{
	Log.Write("SOUND::PlaySoundBuffer() - Exception");
}
}

BOOL SOUND::InitDirectSound()
{
	HWND hWnd;

	hWnd=AfxGetApp()->m_pMainWnd->m_hWnd;

	HRESULT hRet;
	hMainWnd=hWnd;

	//������� ������ DirectSound
	hRet=DirectSoundCreate(NULL, &pDS, NULL);

	if (hRet != DS_OK)
	{
		return (FALSE);
	}

	Log.Write("DirectSoundCreate ok");

	//������������� ����� ����������� �������
	hRet = pDS ->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if (hRet != DS_OK)
	{
		Log.Write("SetCooperativeLevel fail");
		return (FALSE);
	}

	Log.Write("SetCooperativeLevel ok");

	//������� �������� ������
	if (!CreateBuffers())
	{
		return (FALSE);
	}

	//��������� ����� �����������
	/*if (!PrepareBuffers())
	{
		return (FALSE);
	}*/

	//PlaySoundBuffer();

	return TRUE;
}

void SOUND::testdirectsound()
{
	InitDirectSound();
}