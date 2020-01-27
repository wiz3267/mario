//Level.h
#ifndef __WIZLEVEL_H
#define __WIZLEVEL_H

#include "sprite.h"
#include "rects.h"

//класс LEVEL предназначен для описания уровня
class LEVEL
{
// !!! ВНИМАНИЕ !!! При добавлении новых данных их можно дописывать
// ТОЛЬКО в конец текущего описания. В противном случае
// чтение прежних файлов level???.dat станет невозможным
// не меняйте порядок следования и тип данных, если хотите читать старые файлы уровней
//************************ ЗАГОЛОВОК ФАЙЛА УРОВНЯ *********************
private:
	unsigned long SIGNATURE;//сигнатура структуры
	WORD sizeofLevel;	//размер структуры в байтах
	SPRITE *spr;		//указатель на используемый класс спрайтов
public:
	WORD x,y;			//координаты окна показа уровня
	WORD MaxX,MaxY;		//максимальные координаты показа уровня
	WORD Len;			//ширина уровня в кубиках
	WORD Hei;			//высота уровня в кубиках
	WORD BoxLen;		//ширина кубика в пикселях
	WORD BoxHei;		//высота кубика в пикселях
private:
	WORD *Data;			//указатель на данные
public:
	WORD MarioX,MarioY;	//координаты марио
	WORD BackgroundColor;//цвет заднего плана в данном уровне и флаги
	WORD Time;			 //время, за которое надо пройти этот уровень
//************************ КОНЕЦ ЗАГОЛОВКА ФАЙЛА УРОВНЯ ***************

//************************** МЕТОДЫ ****************************
public:
	void ConvertNumber(int num, char width, char far * dest);
	int	 Editor(int n);			//редактор уровня n
	LEVEL(int len, int hei,SPRITE *spr); //конструктор создание уровня
	~LEVEL();					//деструктор
	int  Load(int n);			//загрузка уровня n
	void New(int len,int hei);	//создание нового уровня
	int  Read(int x,int y);		//считать один кубик из уровня
	int  ReadXY(int x,int y)	//считать из уровня кубик (точность до пикселя)
	{
		return Read(x/BoxLen,y/BoxHei);
	}
	int  Save(int n);			//запись уровня  n
	void Show();				//нарисовать уровень
	void Show(int x,int y,char=SHOW_BACKGROUND|SHOW_FOREGROUND);	//нарисовать уровень с заданной позиции
	void Write(int x,int y,int what);//записать в уровень
	
	//записать в уровень кубик
	//x,y - пиксельные координаты
	//what - код кубика вместе с атрибутами
	void WriteXY(int x,int y,int what)
	{
		Write(x/BoxLen, y/BoxHei,what);
	};

public:
	enum {
		MASK=0x1ff
	};

	//свойства кубика
	enum box_logic{
		BACKGROUND  =0x8000,	//кирпич есть задний  фон(для всех объектов
							//он равнозначен пустоте)
		ALIEN		=0x4000,//это не кубик, а код кубика задает номер чужого
		FOREGROUND	=0x2000,//этот кирпич будет поверх всех объектов
		logTRANSP	=BACKGROUND,	//"логически прозрачный"
		TRANSPARENTPIXELS=0x1000,	//кирпич имеет прозрачные пикселы(иначе неимет)
		DESTROYED	=0x0800,	//кирпичик может разрушаться
		COLLAPSE	=0x0400,	//кирпичик обваливается под ногами
		PULL=DESTROYED | FOREGROUND, //кирпичик, когда разрушается, тащит все за собой
		//действительно только для чужих
		//AGAIN=FOREGROUND	//чужой должен появиться снова, если его загасят
	};

	//как показывать уровень
	enum {
		SHOW_DEBUG		=0x01,	//показывать отладку
		SHOW_BACKGROUND	=0x02,	//показать задний план
		SHOW_FOREGROUND	=0x04	//показать передний план
	};

	enum {
		FLAG_UNDERWATER=0x8000	 //этот уровень - подводный
	};
}; //class LEVEL

#endif