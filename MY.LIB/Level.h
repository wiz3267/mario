//Level.h
#ifndef __WIZLEVEL_H
#define __WIZLEVEL_H

#include "sprite.h"
#include "rects.h"

//����� LEVEL ������������ ��� �������� ������
class LEVEL
{
// !!! �������� !!! ��� ���������� ����� ������ �� ����� ����������
// ������ � ����� �������� ��������. � ��������� ������
// ������ ������� ������ level???.dat ������ �����������
// �� ������� ������� ���������� � ��� ������, ���� ������ ������ ������ ����� �������
//************************ ��������� ����� ������ *********************
private:
	unsigned long SIGNATURE;//��������� ���������
	WORD sizeofLevel;	//������ ��������� � ������
	SPRITE *spr;		//��������� �� ������������ ����� ��������
public:
	WORD x,y;			//���������� ���� ������ ������
	WORD MaxX,MaxY;		//������������ ���������� ������ ������
	WORD Len;			//������ ������ � �������
	WORD Hei;			//������ ������ � �������
	WORD BoxLen;		//������ ������ � ��������
	WORD BoxHei;		//������ ������ � ��������
private:
	WORD *Data;			//��������� �� ������
public:
	WORD MarioX,MarioY;	//���������� �����
	WORD BackgroundColor;//���� ������� ����� � ������ ������ � �����
	WORD Time;			 //�����, �� ������� ���� ������ ���� �������
//************************ ����� ��������� ����� ������ ***************

//************************** ������ ****************************
public:
	void ConvertNumber(int num, char width, char far * dest);
	int	 Editor(int n);			//�������� ������ n
	LEVEL(int len, int hei,SPRITE *spr); //����������� �������� ������
	~LEVEL();					//����������
	int  Load(int n);			//�������� ������ n
	void New(int len,int hei);	//�������� ������ ������
	int  Read(int x,int y);		//������� ���� ����� �� ������
	int  ReadXY(int x,int y)	//������� �� ������ ����� (�������� �� �������)
	{
		return Read(x/BoxLen,y/BoxHei);
	}
	int  Save(int n);			//������ ������  n
	void Show();				//���������� �������
	void Show(int x,int y,char=SHOW_BACKGROUND|SHOW_FOREGROUND);	//���������� ������� � �������� �������
	void Write(int x,int y,int what);//�������� � �������
	
	//�������� � ������� �����
	//x,y - ���������� ����������
	//what - ��� ������ ������ � ����������
	void WriteXY(int x,int y,int what)
	{
		Write(x/BoxLen, y/BoxHei,what);
	};

public:
	enum {
		MASK=0x1ff
	};

	//�������� ������
	enum box_logic{
		BACKGROUND  =0x8000,	//������ ���� ������  ���(��� ���� ��������
							//�� ����������� �������)
		ALIEN		=0x4000,//��� �� �����, � ��� ������ ������ ����� ������
		FOREGROUND	=0x2000,//���� ������ ����� ������ ���� ��������
		logTRANSP	=BACKGROUND,	//"��������� ����������"
		TRANSPARENTPIXELS=0x1000,	//������ ����� ���������� �������(����� ������)
		DESTROYED	=0x0800,	//�������� ����� �����������
		COLLAPSE	=0x0400,	//�������� ������������ ��� ������
		PULL=DESTROYED | FOREGROUND, //��������, ����� �����������, ����� ��� �� �����
		//������������� ������ ��� �����
		//AGAIN=FOREGROUND	//����� ������ ��������� �����, ���� ��� �������
	};

	//��� ���������� �������
	enum {
		SHOW_DEBUG		=0x01,	//���������� �������
		SHOW_BACKGROUND	=0x02,	//�������� ������ ����
		SHOW_FOREGROUND	=0x04	//�������� �������� ����
	};

	enum {
		FLAG_UNDERWATER=0x8000	 //���� ������� - ���������
	};
}; //class LEVEL

#endif