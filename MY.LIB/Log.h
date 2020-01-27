//Log.h
#ifndef __LOG__H
#define __LOG__H

#include "screen.h"

class LOG
{
	CStdioFile file;
	CString filename;
	CString lastlog[25];	//последние строчки лог файла
	int		current;		//текущая строка в lastlog
	bool openok;
public:
	SCREEN screen;
	LOG();
	bool Create(char * fname=NULL);
	void Write(const CString &message);
	void Show();	//показать лог на экране
	~LOG();
};

#endif