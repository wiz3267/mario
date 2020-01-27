//Sprite.cpp

#define FALSE 0
#define TRUE  1


#include "stdafx.h"

//*************************************************************
//********* SPRITE.CPP  функции-члены класса SPRITE ***********
//*************************************************************
#include <stdio.h>
#include <fstream.h>
#include <string.h>

#include "debug.h"
#include "sprite.h"
#include "screen.h"

//инициализируем статическую переменную
int SPRITE::CountObject=0;  //число созданных объектов

//создание спрайта
//Image - ссылка на структуру, описывающую спрайт
//ДЕЙСТВИЯ: выделяется память под массив точек и Image помещается в массив 
//увеличивается на 1 счетчик спрайтов
//ВОЗВРАТ: TRUE - спрайт создан успешно, FALSE - ошибка создания спрайта
int SPRITE::Create(IMAGE& Image)
{
	//проверяем, можно ли еще создать спрайт
	if ( Counter == SPRITES_MAX)
	{
		Fatal("SPRITE::Create - sprites too many");
		return FALSE;
	}

	//проверяем, уникален ли индекс
	if ( find(Image.ID) != -1 )
	{
		Fatal("SPRITE::Create - Index already exist");
		return FALSE;
	}

	//проверяем параметры структуры Image
	if (Image.Len > 320 || Image.Hei> 200)
	{
		Fatal("SPRITE::Create - sprite too big");
		return FALSE;
	}

	//попытка выделить память под спрайт
	Image.Datacolor = new char[Image.Len * Image.Hei];
	if ( !Image.Datacolor )
	{
		Fatal("SPRITE::Create - can't allocate memory");
		return FALSE;
	}

	//копируем струкутру Image в элемент Count массива структур Sprites
	int k=find_free();
	Sprites[k]=Image;
	Counter++;
	return TRUE;
}



//================== SPRITE-конструктор =====================
SPRITE::SPRITE(SCREEN far * screen, int SpMax)
{
	CountObject++;
	#if DEBUGMESSAGES
	Debug("Run SPRITE constructor");
	#endif

	//запоминаем адрес объект типа SCREEN
	scr = screen;

	//запоминаем максимальное количестов спрайтов допустимых для этого
	//объекта
	SPRITES_MAX=SpMax;

	Counter=0;  //пока число созданных спрайтов равно нулю

	//выделяем память под массив типа IMAGE
	Sprites=new IMAGE[SPRITES_MAX];

	//если не удалось выделить память
	if ( !Sprites)
	{
		CountObject--;
		Fatal("SPRITE::SPRITE - no RAM for IMAGE[]");
	}

	for(int i=0; i<SPRITES_MAX; i++)
	{
		Sprites[i].Datacolor=NULL;
		Sprites[i].ID=-1;
	}
}

// ПОМНИ! Деструктор может быть вызван без вызова конструктора !!!
// Строй деструктор, учитывая это
//деструктор
SPRITE::~SPRITE(void)
{
	//если программа завершилась аварийно - не был вызван конструктор
	if (CountObject!=0)
	{
		#if DEBUGMESSAGES
		Debug("Run SPRITE destructor");
		#endif


		//если выделена память под массив Sprites (имеющий тип IMAGE)
		if ( Sprites != NULL )
		{
			//удаляем память из под спрайтов
			for (int i=0; i<Counter; i++)
			{
			  if (Sprites[i].Datacolor) delete Sprites[i].Datacolor;
			  Sprites[i].Datacolor=NULL;
			}
			//удаляем массив структур типа IMAGE
			delete Sprites;
		}
		else
		{
			Debug(" '~SPRITE' - Sprite==NULL! ");
		}
	}

	else //ни одного объекта не было создано
	{
		Debug("SPRITE-destructor: objects not exist");
	}
}

//поиск номера элемента массива образов спрайта с идентификатором ID
//ВОЗВРАТ:
//-1 поиск не принес результатов, спрайта с таким ID не существует
//0...(SPRITES_MAX-1) номер элемента массива 
int SPRITE::find(int ID)
{
  for (int i=0; i<Counter; i++)
  {
    if ( Sprites[i].ID==ID)
    {
      return i;
    }
  }

  return -1;
}

//поиск номера элемента массива, где нет спрайта
//-1 нет
//0...(SPRITES_MAX-1) номер элемента массива
int SPRITE::find_free()
{
  for (int i=0; i<SPRITES_MAX; i++)
  {
    if (Sprites[i].Datacolor==0) return i;
  }

        Debug("SPRITE::find_free - no free sprites!");
  return -1;
}

SPRITE::IMAGE far & SPRITE::GetImage(int ID)
{
  int n=find(ID);
  if (n==-1)
  {
    Fatal("SPRITE::GetImage - Sprite not exist");
  }
  return Sprites[n];
}

// загрузить спрайт из файла
// fname - имя файла
// offset - смещение от начала файла
// Image - адрес структуры, описывающей спрайт
int SPRITE::Load(char far * fname, unsigned long offset, SPRITE::IMAGE Image)
{
  FILE * stream;

  //проверяем, можно ли еще загружать спрайт
  if ( Counter == SPRITES_MAX)
  {
    Fatal("SPRITE::Load - sprites too many");
    return FALSE;
  }

  //проверяем, уникален ли индекс
  if ( find(Image.ID) != -1 )
  {
      Debug("SPRITE::Load - Index already exist");
      return FALSE;
  }

  //проверяем параметры структуры Image
  if (Image.Len > 320 || Image.Hei> 200)
  {
    Fatal("SPRITE::Load - sprite too big");
    return FALSE;
  }

  //открываем файл
  stream = fopen( fname, "rb" );

  //если не смогли открыть файл
  if ( !stream)
  {
    Fatal("SPRITE::Load - can't open file");
    return FALSE;
  }

  //позиционируем указатель файла
  if ( fseek( stream, offset, SEEK_SET) )
  {
    Debug("SPRITE::Load - can't seek pointer");
    fclose(stream);
    return FALSE;
  }

  //попытка выделить память под спрайт
  Image.Datacolor = new char[Image.Len * Image.Hei];
  if ( !Image.Datacolor )
  {
    Fatal("SPRITE::Load - can't allocate memory");
    fclose(stream);
    return FALSE;
  }

  //читаем из файла
  fread(Image.Datacolor, Image.Len, Image.Hei, stream);

  //закрываем файл
  fclose(stream);

  //копируем струкутру Image в элемент Count массива структур Sprites
  Sprites[find_free()]=Image;
  Counter++;
  return TRUE;
}



//загрузка спрайта из файла моего формата (расширение *.SPR)
// fname - имя файла
// im - сюда запишется информация о файле
int SPRITE::LoadSpriteform(char * fname, SPRITE::IMAGE &im)
{
	ifstream ifl(fname, ios::binary);
	if (!ifl)
	{
	  Fatal("LoadSpriteForm - File not found");
	  return 0;
	}

	SPRITEINFO sf;
	FILEHEADER fh;

	//считываем заголовок
	ifl.read( (char*) &fh.Signature, 10 );
	ifl.read ((char*) &fh.Info,4);
	ifl.read ((char*) &fh.Sprite,4);
	ifl.read ((char*) &fh.FileSize,4);

	fh.Signature[9]=0;
	if ( strcmp(fh.Signature, "SPRITEFOR") )
	{
	  Fatal("LoadSpriteform - bad file format");
	  return 0;
	}

	//позиционируемся на информационную структуру
	ifl.seekg( fh.Info );

	//считываем описание спрайта
	ifl.read( (char*) &sf.Len, 2);
	ifl.read( (char*) &sf.Hei, 2);
	ifl.read( (char*) &sf.Attribute, 2);

	//позиционируемся на массив точек
	ifl.seekg( fh.Sprite);

	im.Len=sf.Len;
	im.Hei=sf.Hei;
	//im.Attribute=sf.Attribute;

	//если спрайт создался
	if (Create(im))
	{
	  //считываем сам спрайт
	  ifl.read(im.Datacolor, im.Len*im.Hei);
	}
	else
	{
	  Fatal("Can't create the Sprite");
	  return 0;
	}

	ifl.close();
	return 1;
}


//прибавляет к цвету каждой точки (кроме нуля) код n
void SPRITE::ModifyColor(int index, char n)
{
	IMAGE &im=GetImage(index);
	for(int i=0,t; i<im.Len; i++)
	for(int j=0; j<im.Hei; j++)
	{
		if (t=im.Read(i,j))
		{
			im.Write(i,j, t + n);
		}
	}
}

//================= Scroll - скроллинг спрайта с возвратом ============
//Index - номер спрайта
//V - на сколько точек сдвигать
//F - набор флагов ( SCROLL_UP, SCROLL_DOWN, SCROLL_LEFT, SCROLL_RIGHT )

int SPRITE::Scroll(int Index, int F, int count)
{
//	return 0;

	int n=find(Index);
	if (n==-1) {
	Debug("SPRITE::Scroll - sprite not exist");
	return FALSE;
	}

	IMAGE & Im = GetImage(Index);

//	Msg("Sprite::Scroll", 15);

	char *Datacolor=Im.Datacolor;
	int Len=Im.Len;
	int Hei=Im.Hei;

	char *save = new char[Im.Len];

	if (save==NULL) return 0;

	//скроллинг вверх
	for(int i=0; i<count; i++)
	{
		if (F & SCROLL_UP) 
		{
			//сохраняем первую строку спрайта
			memcpy( save, Im.Datacolor, Im.Len );
			//сдвигаем спрайт вверх
			memcpy( Im.Datacolor, Im.Datacolor+Im.Len,
			  (Im.Hei-1)*Im.Len );
			//восстанавливаем первую строку
			memcpy( Im.Datacolor+(Im.Hei-1)*(Im.Len), save, Im.Len );
		}

		if (F & SCROLL_RIGHT)
		{
			for(int y=0; y<Im.Hei; y++)
			{
				int len=Im.Len;
				char * current=Im.Datacolor+y*len;
				BYTE a=current[len-1];
				memcpy(save, current, len);
				memcpy(current+1, save, len-1);
				current[0]=a;
			}
		}
	}

/*	//скроллинг вправо
	if (F & SCROLL_RIGHT) {
	  //напишем эту процедуру на ассемблере
	  _asm {
				pusha
                mov esi,Datacolor
				mov edi,Datacolor

                mov edx,Hei
                mov ecx,Len                
Scroll_Loop_0:
				dec ecx
                add edi,ecx
                mov al,[edi]
                mov esi,edi
                dec esi

				std
                rep movsb

                mov [edi],al

                mov ecx,Len
                add edi,ecx

                dec edx
                jnz Scroll_Loop_0

				popa
        }
  }
  */

  //удаляем временный буфер
  delete save;

  return 0;


}

//============ 'ShowDirect' нарисовать спрайт по индексу (0,1,2...) ===========
// x,y - координаты вывода спрайта
// Index - индекс спрайта
// Def - атрибуты для функции bitblt
// Возврат: TRUE - спрайт отображен, FALSE - отобразить спрайт не удалось
int SPRITE::ShowDirect(int x,int y,int Index,int Def)
{
	if (Index>=Counter || Index<0)
	{
		Debug("SPRITE::ShowDirect: Index out of range");
		return FALSE;
	}

	scr ->  bitblt(x,y,
	  Sprites[Index].Len, Sprites[Index].Hei,
	  Sprites[Index].Datacolor, Sprites[Index].Attribute | Def);
	return TRUE;
}

//================= 'Show' показывает спрайт с индексом Index =============
// x,y - координаты вывода спрайта
// ID - unicum ID спрайта
// Def - атрибуты для функции bitblt, которые соединятся с атрибутами спрайта
// Возврат: TRUE - спрайт отобразился успешно, FALSE - невозможно отобразить
// файл
int SPRITE::Show(int x,int y,int ID,int Def)
{
	//Msg("Sprite::Show", 3);
	int n=find(ID);
	if (n==-1)
	{
		Fatal("SPRITE::Show - sprite not exist");
		return FALSE;
	}

	scr ->  bitblt(x,y,
	  Sprites[n].Len, Sprites[n].Hei,
	  Sprites[n].Datacolor, Sprites[n].Attribute | Def);
	
	return TRUE;
}

//удалить спрайт с идентификатором ID
int SPRITE::Delete(int ID)
{
	int n=find(ID);
	if (n==-1)
	{
		Debug("SPRITE::Delete - sprite not exist");
		return FALSE;
	}

	if (Sprites[n].Datacolor == 0)
	{
	  Debug("SPRITE::Delete - you want delete space!");
			return FALSE;
	}

	delete Sprites[n].Datacolor;
	Sprites[n].Datacolor=NULL;
	Sprites[n].ID=-1;
	Counter--;

	return TRUE;
}

void SPRITE::DeleteAllSprites()
{
	for(int i=0; i<Counter; i++)
	{
		Sprites[i].ID=-1;
		if (Sprites[i].Datacolor) 
		{
			delete Sprites[i].Datacolor;
			Sprites[i].Datacolor=NULL;
		}
	}
	Counter=0;
}

void SPRITE::IMAGE::Write(int x,int y,unsigned char color)
{
	if (x<0 || x>=Len || y<0 || y>=Hei)
	{
		Debug("IMAGE::Write - bad coordinate");
		return;
	}
	else
	{
		Datacolor[y*Len+x]=color;
	}
}

unsigned char SPRITE::IMAGE::Read(int x,int y)
{
	if (x<0 || x>=Len || y<0 || y>=Hei)
	{
		Debug("IMAGE::Read - bad coordinate");
		return 0;
	}
	else
    {
		return char(Datacolor[y*Len+x]);
	}
}