//Sprite.cpp

#define FALSE 0
#define TRUE  1


#include "stdafx.h"

//*************************************************************
//********* SPRITE.CPP  �������-����� ������ SPRITE ***********
//*************************************************************
#include <stdio.h>
#include <fstream.h>
#include <string.h>

#include "debug.h"
#include "sprite.h"
#include "screen.h"

//�������������� ����������� ����������
int SPRITE::CountObject=0;  //����� ��������� ��������

//�������� �������
//Image - ������ �� ���������, ����������� ������
//��������: ���������� ������ ��� ������ ����� � Image ���������� � ������ 
//������������� �� 1 ������� ��������
//�������: TRUE - ������ ������ �������, FALSE - ������ �������� �������
int SPRITE::Create(IMAGE& Image)
{
	//���������, ����� �� ��� ������� ������
	if ( Counter == SPRITES_MAX)
	{
		Fatal("SPRITE::Create - sprites too many");
		return FALSE;
	}

	//���������, �������� �� ������
	if ( find(Image.ID) != -1 )
	{
		Fatal("SPRITE::Create - Index already exist");
		return FALSE;
	}

	//��������� ��������� ��������� Image
	if (Image.Len > 320 || Image.Hei> 200)
	{
		Fatal("SPRITE::Create - sprite too big");
		return FALSE;
	}

	//������� �������� ������ ��� ������
	Image.Datacolor = new char[Image.Len * Image.Hei];
	if ( !Image.Datacolor )
	{
		Fatal("SPRITE::Create - can't allocate memory");
		return FALSE;
	}

	//�������� ��������� Image � ������� Count ������� �������� Sprites
	int k=find_free();
	Sprites[k]=Image;
	Counter++;
	return TRUE;
}



//================== SPRITE-����������� =====================
SPRITE::SPRITE(SCREEN far * screen, int SpMax)
{
	CountObject++;
	#if DEBUGMESSAGES
	Debug("Run SPRITE constructor");
	#endif

	//���������� ����� ������ ���� SCREEN
	scr = screen;

	//���������� ������������ ���������� �������� ���������� ��� �����
	//�������
	SPRITES_MAX=SpMax;

	Counter=0;  //���� ����� ��������� �������� ����� ����

	//�������� ������ ��� ������ ���� IMAGE
	Sprites=new IMAGE[SPRITES_MAX];

	//���� �� ������� �������� ������
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

// �����! ���������� ����� ���� ������ ��� ������ ������������ !!!
// ����� ����������, �������� ���
//����������
SPRITE::~SPRITE(void)
{
	//���� ��������� ����������� �������� - �� ��� ������ �����������
	if (CountObject!=0)
	{
		#if DEBUGMESSAGES
		Debug("Run SPRITE destructor");
		#endif


		//���� �������� ������ ��� ������ Sprites (������� ��� IMAGE)
		if ( Sprites != NULL )
		{
			//������� ������ �� ��� ��������
			for (int i=0; i<Counter; i++)
			{
			  if (Sprites[i].Datacolor) delete Sprites[i].Datacolor;
			  Sprites[i].Datacolor=NULL;
			}
			//������� ������ �������� ���� IMAGE
			delete Sprites;
		}
		else
		{
			Debug(" '~SPRITE' - Sprite==NULL! ");
		}
	}

	else //�� ������ ������� �� ���� �������
	{
		Debug("SPRITE-destructor: objects not exist");
	}
}

//����� ������ �������� ������� ������� ������� � ��������������� ID
//�������:
//-1 ����� �� ������ �����������, ������� � ����� ID �� ����������
//0...(SPRITES_MAX-1) ����� �������� ������� 
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

//����� ������ �������� �������, ��� ��� �������
//-1 ���
//0...(SPRITES_MAX-1) ����� �������� �������
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

// ��������� ������ �� �����
// fname - ��� �����
// offset - �������� �� ������ �����
// Image - ����� ���������, ����������� ������
int SPRITE::Load(char far * fname, unsigned long offset, SPRITE::IMAGE Image)
{
  FILE * stream;

  //���������, ����� �� ��� ��������� ������
  if ( Counter == SPRITES_MAX)
  {
    Fatal("SPRITE::Load - sprites too many");
    return FALSE;
  }

  //���������, �������� �� ������
  if ( find(Image.ID) != -1 )
  {
      Debug("SPRITE::Load - Index already exist");
      return FALSE;
  }

  //��������� ��������� ��������� Image
  if (Image.Len > 320 || Image.Hei> 200)
  {
    Fatal("SPRITE::Load - sprite too big");
    return FALSE;
  }

  //��������� ����
  stream = fopen( fname, "rb" );

  //���� �� ������ ������� ����
  if ( !stream)
  {
    Fatal("SPRITE::Load - can't open file");
    return FALSE;
  }

  //������������� ��������� �����
  if ( fseek( stream, offset, SEEK_SET) )
  {
    Debug("SPRITE::Load - can't seek pointer");
    fclose(stream);
    return FALSE;
  }

  //������� �������� ������ ��� ������
  Image.Datacolor = new char[Image.Len * Image.Hei];
  if ( !Image.Datacolor )
  {
    Fatal("SPRITE::Load - can't allocate memory");
    fclose(stream);
    return FALSE;
  }

  //������ �� �����
  fread(Image.Datacolor, Image.Len, Image.Hei, stream);

  //��������� ����
  fclose(stream);

  //�������� ��������� Image � ������� Count ������� �������� Sprites
  Sprites[find_free()]=Image;
  Counter++;
  return TRUE;
}



//�������� ������� �� ����� ����� ������� (���������� *.SPR)
// fname - ��� �����
// im - ���� ��������� ���������� � �����
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

	//��������� ���������
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

	//��������������� �� �������������� ���������
	ifl.seekg( fh.Info );

	//��������� �������� �������
	ifl.read( (char*) &sf.Len, 2);
	ifl.read( (char*) &sf.Hei, 2);
	ifl.read( (char*) &sf.Attribute, 2);

	//��������������� �� ������ �����
	ifl.seekg( fh.Sprite);

	im.Len=sf.Len;
	im.Hei=sf.Hei;
	//im.Attribute=sf.Attribute;

	//���� ������ ��������
	if (Create(im))
	{
	  //��������� ��� ������
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


//���������� � ����� ������ ����� (����� ����) ��� n
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

//================= Scroll - ��������� ������� � ��������� ============
//Index - ����� �������
//V - �� ������� ����� ��������
//F - ����� ������ ( SCROLL_UP, SCROLL_DOWN, SCROLL_LEFT, SCROLL_RIGHT )

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

	//��������� �����
	for(int i=0; i<count; i++)
	{
		if (F & SCROLL_UP) 
		{
			//��������� ������ ������ �������
			memcpy( save, Im.Datacolor, Im.Len );
			//�������� ������ �����
			memcpy( Im.Datacolor, Im.Datacolor+Im.Len,
			  (Im.Hei-1)*Im.Len );
			//��������������� ������ ������
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

/*	//��������� ������
	if (F & SCROLL_RIGHT) {
	  //������� ��� ��������� �� ����������
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

  //������� ��������� �����
  delete save;

  return 0;


}

//============ 'ShowDirect' ���������� ������ �� ������� (0,1,2...) ===========
// x,y - ���������� ������ �������
// Index - ������ �������
// Def - �������� ��� ������� bitblt
// �������: TRUE - ������ ���������, FALSE - ���������� ������ �� �������
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

//================= 'Show' ���������� ������ � �������� Index =============
// x,y - ���������� ������ �������
// ID - unicum ID �������
// Def - �������� ��� ������� bitblt, ������� ���������� � ���������� �������
// �������: TRUE - ������ ����������� �������, FALSE - ���������� ����������
// ����
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

//������� ������ � ��������������� ID
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