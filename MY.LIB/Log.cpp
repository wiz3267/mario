//Log.cpp
#include "stdafx.h"

#include "Log.h"
#include "Screen.h"

LOG Log;

LOG::LOG()
{
	current=0;
}

LOG::~LOG()
{
	if (openok) file.Close();
}

CString itoc(int);

void LOG::Write(const CString &message)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString tm;
	tm.Format("%02i:%02i:%02i ",st.wHour,st.wMinute, st.wSecond);

	lastlog[current]=tm+message;
	
	current++;
	if (current==25) current=0;

	if (!openok) return;

	CString t;

	t.Format("%02i:%02i:%02i:%03i ",st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	

	t+=message;
	file.WriteString(t);
	file.WriteString("\n");

	static F=0;

}

bool LOG::Create(char *fname)
{
	DeleteFile(fname);
	filename=file;
	if (file.Open(fname, file.modeWrite|file.modeCreate))
	{
		openok=true;
	}
	else
	{
		openok=false;
	}

	return openok;
}


extern SCREEN scr;
//показать последние строчки лога на экране
void LOG::Show()
{
	int z=current;

	for(int i=24; i>=13; i--)
	{
		scr.locate(0,i);

		z--;
		if (z==-1) z=24;

		scr<<lastlog[z].GetBuffer(0);
	}

}

// DirectSoundCreate