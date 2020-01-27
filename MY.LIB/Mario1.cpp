//12:15 1500 тгд

//Mario1.cpp
////////////////////////////////////////////////////////
//						      //
// MARIO1.CPP содержит редко модифицируемые функции   //
//                                                    //1
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "total.h"

//double sign(double);

int random(int);

//================загрузка спрайтов==================
void SUPERMARIO::LoadSprites()
{
	int t,i;
	SPRITE::IMAGE im;

	BigFont.DeleteAllSprites();
	Sprite.DeleteAllSprites();
	LvSpr.DeleteAllSprites();

	//загружаем буквы
	{
		//загружаем буквы
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (i=0; i<28; i++)
		{
			im.ID=i;
			BigFont.Load("graph\\fontbig.dat", i*24*24L,im);
		}

		//изменяем случайно цвет букв
		for(i=0;i<28;i++)
		{
			int base=random(7)*16+144;
			//BigFont.ModifyColor(i,(rand() % 4)*16);
			SPRITE::IMAGE &im=BigFont.GetImage(i);

				for(int i=0; i<24; i++)
				for(int j=0; j<24; j++)
				{
					//if (im.Read(i,j)) im.Write(i,j,208+random(16));
					if (unsigned (im.Read(j,i))==159) im.Write(j,i, base
						+int(double(i)/26.0*15.0));
					if (unsigned (im.Read(j,i))==155) im.Write(j,i, base+4);
				}

		}
	}

	//загружаем тесты
	{
		im.ID=SPRITE_TEST;
		im.Attribute=0;
		Sprite.LoadSpriteform("graph\\test.sp0",im);
	}

	//загружаем цифры
	{
		im.Hei=8;
		im.Len=8;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=12,i=SPRITE_DIGITAL0; i<=SPRITE_DIGITAL9; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\font.dat", t*64L,im);
		}
	}


	//SPRITE_MUSHROOM_LIVE,		//гриб, дающий жизнь

	//загружаем гриб, дающий жизнь
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MUSHROOM_LIVE;
		Sprite.Load("graph\\sprite.dat", 5*24*24L,im);
	}

	//загружаем оружие стрелу
	{
		im.Hei=7;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_ARROW;
		Sprite.Load("graph\\levelbox.dat", (BRICK::ARROW-1)*24*24L,im);
	}

	//загружаем оружие ножик
	{
		im.Hei=12;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_DAGGER;
		Sprite.Load("graph\\levelbox.dat", (BRICK::DAGGER-1)*24*24L,im);
	}

	//загружаем сопли
	{
		im.Hei=14;
		im.Len=24;

		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_SALIVA1;
		Sprite.Load("graph\\sprite.dat", 75*24*24L,im);

		im.ID=SPRITE_SALIVA2;
		Sprite.Load("graph\\sprite.dat", 76*24*24L,im);
	}

	//загружаем рыбку
	{
		im.ID=SPRITE_FISH1;
		Sprite.LoadSpriteform("graph\\fish.sp0", im);
		im.ID=SPRITE_FISH2;
		Sprite.LoadSpriteform("graph\\fish.sp1", im);
	}


	//загружаем оружие топорик
	{
		im.Hei=20;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_AXE;
		Sprite.Load("graph\\levelbox.dat", (BRICK::AXE-1)*24*24L,im);
	}

	//загружаем улитку
	{
		im.ID=SPRITE_HELIX1;
		Sprite.LoadSpriteform("graph\\helix.sp0", im);
		im.ID=SPRITE_HELIX2;
		Sprite.LoadSpriteform("graph\\helix.sp1", im);

	}

	//загружаем акулу
	{
		im.ID=SPRITE_SHARK1;
		im.Attribute=SCREEN::FLIP_HORZ | SCREEN::TRANSP;
		Sprite.LoadSpriteform("graph\\shark.sp0", im);
		im.ID=SPRITE_SHARK2;
		Sprite.LoadSpriteform("graph\\shark.sp1", im);

	}


	//загружаем пузырики
	{
		im.ID=SPRITE_BUBBLE1;
		Sprite.LoadSpriteform("graph\\bubble.sp0", im);
		im.ID=SPRITE_BUBBLE2;
		Sprite.LoadSpriteform("graph\\bubble.sp1", im);
		im.ID=SPRITE_BUBBLE3;
		Sprite.LoadSpriteform("graph\\bubble.sp2", im);
		im.ID=SPRITE_BUBBLE4;
		Sprite.LoadSpriteform("graph\\bubble.sp3", im);
	}

	//загружаем космонавта
	{
		im.Hei=48;
		im.Len=48;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_COSMONAUT0;
	//	Sprite.Load("graph\\cosmonau.sp0", 0x16,im);
		Sprite.Load("graph\\explode.sp5", 0x16,im);

		im.ID=SPRITE_COSMONAUT1;
	//	Sprite.Load("graph\\cosmonau.sp1", 0x16,im);
		Sprite.Load("graph\\explode.sp6", 0x16,im);

		im.ID=SPRITE_COSMONAUT2;
	//	Sprite.Load("graph\\cosmonau.sp2", 0x16,im);
		Sprite.Load("graph\\explode.sp5", 0x16,im);

		im.ID=SPRITE_COSMONAUT3;
	//	Sprite.Load("graph\\cosmonau.sp3", 0x16,im);
		Sprite.Load("graph\\explode.sp6", 0x16,im);
	}


	//загружаем взрыв
	{
		im.Hei=40;
		im.Len=40;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_EXPLODESTART;
		Sprite.Load("graph\\explode.sp1", 0x16,im);

		im.ID++;
		Sprite.Load("graph\\explode.sp2", 0x16,im);

		im.ID++;
		Sprite.Load("graph\\explode.sp3", 0x16,im);

		im.ID++;
		Sprite.Load("graph\\explode.sp4", 0x16,im);
	}


	//загружаем желтого орла
	{
		im.Hei=48;
		im.Len=48;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_EAGLESTART;
		Sprite.Load("graph\\spr.dat", 20,im);
		im.ID=SPRITE_EAGLEEND;
		Sprite.Load("graph\\spr1.dat",20,im);
	}

	//загружаем голову
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_HEAD1;
		Sprite.LoadSpriteform("graph\\head.sp0", im);

		im.ID=SPRITE_HEAD2;
		Sprite.LoadSpriteform("graph\\head.sp1",im);

			im.ID=SPRITE_HEAD3;
		Sprite.LoadSpriteform("graph\\head.sp2",im);
	}

	//загружаем гриб, дающий увеличение
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MUSHROOM_BIG;
		Sprite.Load("graph\\sprite.dat", 50*24*24L,im);
	}

	//загружаем анимацию открывания двери
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=0,i=SPRITE_DOOROPEN; i<=SPRITE_DOORCLOSE; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24L*24,im);
		}
	}

	//загружаем, как осыпается кирпичик
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=68,i=SPRITE_TIDESTART; i<=SPRITE_TIDEEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24L*24,im);
		}
	}

	//загружаем, как разрушается стрела
	{
		im.Hei=12;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=72,i=SPRITE_ARROWDESTROYEDSTART; i<=SPRITE_ARROWDESTROYEDEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24L*24,im);
		}
	}


	//загружаем звезду
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_STAR;
		Sprite.Load("graph\\sprite.dat", 51*24*24L,im);
	}

	//загружаем цветок
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_FLOWER;
		Sprite.Load("graph\\sprite.dat", 52*24*24L,im);
	}

	//загружаем маленькую монетку
	{
		im.Hei=12;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_SMALLMONEY;
		Sprite.Load("graph\\sprite.dat", 34*24*24L,im);
	}

	//загружаем лифт
	{
		im.Hei=15;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_LIFT;
		Sprite.Load("graph\\sprite.dat", 47*24*24L,im);
	}

	//загружаем тележку
	{
		im.Hei=13;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=65,i=SPRITE_TROLLEYSTART; i<=SPRITE_TROLLEYEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем туземца
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=60,i=SPRITE_ABORIGINESTART; i<=SPRITE_ABORIGINEEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем чем стреляет Mario
	{
		im.Hei=12;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=41,i=SPRITE_FIRESTART; i<=SPRITE_FIREEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем летящего марио
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MARIOFLY;
		Sprite.Load("graph\\sprite.dat", 28*24*24L,im);
	}

	//загружаем мертвого марио
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MARIODEATH;
		Sprite.Load("graph\\sprite.dat", 13*24*24L,im);
	}

    //загружаем мостик
	{
		im.Hei=15;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_BRIDG;
		Sprite.Load("graph\\sprite.dat", 64*24*24L,im);
	}

	//загружаем мостик для воды
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_WATERBRIDG;
		Sprite.LoadSpriteform("graph\\wbridg.spr", im);
	}

	//загружаем птичку
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_BIRD1;
		Sprite.LoadSpriteform("graph\\bird.sp0", im);
		im.ID=SPRITE_BIRD2;
		Sprite.LoadSpriteform("graph\\bird.sp1", im);
	}

	//загружаем скелета
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_SKELETON;
		Sprite.LoadSpriteform("graph\\skeleton.sp0", im);
	}

	//загружаем марио
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=24,i=SPRITE_RICKSTART; i<=SPRITE_RICKEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем зубастый цветок
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=48,i=SPRITE_TOOTHFLOWERSTART; i<=SPRITE_TOOTHFLOWEREND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем ходящий грибок
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=20,i=SPRITE_MASHASTART; i<=SPRITE_MASHAEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем злобного ежика
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=111,i=SPRITE_HEDGEHOGSTART; i<=SPRITE_HEDGEHOGEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем СЖАТЫЙ ходящий грибок
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MASHASMALL;
		Sprite.Load("graph\\sprite.dat", 22*24*24L,im);
	}


	//загружаем ПАНЦИРЬ
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_TURTLEHOUSE;
		Sprite.Load("graph\\sprite.dat", 44*24*24L,im);
	}

	//загружаем ЧЕРЕПАХУ
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=45,i=SPRITE_TURTLESTART; i<=SPRITE_TURTLEEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем ДРАКОНА
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=36,i=SPRITE_LIZARDSTART; i<=SPRITE_LIZARDEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем летящего дракона
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_LIZARDFLY;
		Sprite.Load("graph\\sprite.dat", 35*24*24L,im);
	}

	//загружаем как монетка вращается
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=53,i=SPRITE_MONEYSTART; i<=SPRITE_MONEYEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}


	//загружаем свинью
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (t=16,i=SPRITE_PIGSTART; i<=SPRITE_PIGEND; i++, t++)
		{
			im.ID=i;
			Sprite.Load("graph\\sprite.dat", t*24*24L,im);
		}
	}

	//загружаем фон
	{
		im.Hei=24;
		im.Len=24;
	//	im.Attribute=SCREEN::TRANSP;
		im.Attribute=0;
		for (t=0,i=1; i<=NUMBER_LEVELBOX; i++, t++)
		{
			im.ID=i;
			LvSpr.Load("graph\\levelbox.dat", t*24*24L,im);
		}
	}

	//загружаем указатель в меню
	{
		im.Hei=8;
		im.Len=8;
		im.Attribute=SCREEN::TRANSP;
		im.ID=SPRITE_POINTER;
		Sprite.Load("graph\\font.dat", 3*8*8L,im);
	}

	//загружаем маленький кирпич
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SCREEN::TRANSP;
		im.ID=SPRITE_SMALLBRICK;
		Sprite.Load("graph\\sprite.dat", 31*24*24L,im);
	}


}


char SystemMessage2[256];

DWORD SoundDeCoding(CString command, CString check)
{

	CreateDirectory("sound",NULL);
	SetCurrentDirectory("sound");


	CFile fil;

	
	if (fil.Open(check, fil.modeRead))
	{
		fil.Close();
		SetCurrentDirectory("..");
		return 0;
	}

	char s[2048]="lame.exe";

	//ShowWindow
	STARTUPINFO si={0};
	si.cb=sizeof(si);
	//si.wShowWindow=;
	si.wShowWindow=SW_HIDE;
	si.dwFlags=STARTF_USESHOWWINDOW;
	
	si.dwXSize=100;
	si.dwYSize=100;
	//si.dwXCountChars=640;
	//si.dwYCountChars=480;
	
	PROCESS_INFORMATION pi={0};


	BOOL ok=CreateProcess(
		NULL,
		command.GetBuffer(0),//command.GetBuffer(0),
		//NULL,
		NULL, NULL,
		false, 0, NULL,
		NULL,&si,&pi);
	
	DWORD err=WaitForSingleObject(pi.hProcess, 256000);

	if (err==WAIT_ABANDONED)
	{
		strcat(SystemMessage2, "WAIT_ABANDONED");
	}
	else if (err==WAIT_OBJECT_0)
	{
		strcat(SystemMessage2, "WAIT_OBJECT_0");
	}
	else if (err==WAIT_TIMEOUT)
	{
		strcat(SystemMessage2, "WAIT_TIMEOUT");
	}
	else
	{
		char buf[64];
		itoa(err,buf,10);
		strcat(SystemMessage2, buf);
	}

	SetCurrentDirectory("..");


	return 1;
}



//************* загрузка звуков ******************
void SUPERMARIO::LoadSounds(void)
{

	scr.clear();

	Msg(" ЗАГРУЗКА, ПОЖАЛУЙСТА, ПОДОЖДИТЕ ... ",9);
	scr.update();

	CString lame1="lame.exe --decode zastavka.mp3 zastavka.wav";
	CString lame2="lame.exe --decode loop.mp3 loop.wav";
	CString lame3="lame.exe --decode loop_zachita.mp3 loop_zachita.wav";

	SoundDeCoding(lame1, "zastavka.wav");

	scr.clear();
	Msg(" ЗАГРУЗКА 1 ЗАВЕРШЕНА ", 9);
	scr.update();

	
	SoundDeCoding(lame2, "loop.wav");

	scr.clear();
	Msg(" ЗАГРУЗКА 2 ЗАВЕРШЕНА ", 9);
	scr.update();

	
	SoundDeCoding(lame3,"loop_zachita.wav");

	scr.clear();
	Msg(" ЗАГРУЗКА 3 ЗАВЕРШЕНА ", 9);
	scr.update();


	SOUND::MONOSTEREO ms=SOUND::MONOSTEREO::MONO;
	SOUND::BITCOUNT bc=SOUND::BITCOUNT::BIT8;
	int f=11025;
	int dataoffset=46; //смещение до данных от начала файла(пропуск заголовка WAV)
	Sound.load("sound\\pop.wav", f, ms, bc,		SND_POP, dataoffset);
	Sound.load("sound\\xplode2.wav", f, ms, bc,	SND_XPLODE, dataoffset);
	Sound.load("sound\\gem.wav", f, ms, bc,		SND_NEWLIVE, dataoffset);
	Sound.load("sound\\jl87.wav", f, ms, bc,	SND_LAUGHT, dataoffset);
	Sound.load("sound\\nlevel.wav", f, ms, bc,	SND_NEWLEVEL, dataoffset);
	Sound.load("sound\\explode.wav", f, ms, bc,	SND_EXPLODE, dataoffset);
	Sound.load("sound\\exorcism.wav", f, ms, bc,SND_EXORCISM, dataoffset);
	Sound.load("sound\\apple.wav", f, ms, bc,	SND_APPLE, dataoffset);
	Sound.load("sound\\bell1.wav", f, ms, bc,	SND_BELL, dataoffset);
	Sound.load("sound\\finger.wav", f, ms, bc,	SND_FINGER, dataoffset);
	Sound.load("sound\\health.wav", f, ms, bc,	SND_HEALTH, dataoffset);
	Sound.load("sound\\restart.wav", f, ms, bc,	SND_RESTART, dataoffset);
	Sound.load("sound\\menusel.wav", f, ms, bc,	SND_MENUSEL, dataoffset);
	Sound.load("sound\\fire.wav", f, ms, bc,	SND_FIRE, dataoffset);
	Sound.load("sound\\spring.wav", f, ms, bc,	SND_SPRING, dataoffset);
	Sound.load("sound\\pop.wav", f, ms, bc,		SND_POP1, dataoffset);
	Sound.load("sound\\gfx3.wav", f, ms, bc,	SND_GFX3, dataoffset);
	Sound.load("sound\\pigegrin.wav", f, ms, bc,SND_PIGEGRIN, dataoffset);

	Sound.load("sound\\zastavka.wav", 44100, 
		SOUND::MONOSTEREO::STEREO, SOUND::BITCOUNT::BIT16, SND_ZASTAVKA, dataoffset);
	
	Sound.load("sound\\loop.wav",44100, SOUND::MONOSTEREO::STEREO, 
		SOUND::BITCOUNT::BIT16,SND_GHOTIC, dataoffset);

	Sound.load("sound\\loop_zachita.wav",44100, SOUND::MONOSTEREO::MONO, 
		SOUND::BITCOUNT::BIT16,SND_GHOTIC_FAST, dataoffset);

}

//=========== загрузка музыки ==============
void SUPERMARIO::LoadMusic()
{
	song[0]="music\\main.mid";
	song_start[0]=0;

	song[1]="music\\main.mid";
	song_start[1]=0;

	song[2]="music\\main.mid";
	song_start[2]=3000;

	song[3]="music\\main.mid";
	song_start[3]=2000;
}

void SUPERMARIO::BIGSTRING::Add(int Sprite,int n)
{
    SPRITE::IMAGE &im=spr->GetImage(Sprite);

	char *d=im.Datacolor;
	for (int i=0; i<im.Len*im.Hei; i++)
	{
		if (d[i]) d[i]+=n;
	}
}

void SUPERMARIO::BIGSTRING::Show(int x,int y)
{
	for(UINT i=0;i<strlen(a);i++)
	{
        if ( a[i]>='A' && a[i]<='Z' )	spr->Show(x,y,a[i]-'A');
        if ( a[i]=='?')					spr->Show(x,y,26);
        if ( a[i]=='!')					spr->Show(x,y,27);

        x+=24;
	}
}

//рисует строку состояния супер марио
void SUPERMARIO::DrawStateline()
{
    int n=0;

    //показываем число собранных карт
/*	{
    int dx=320-20*3-10, dy=5, len=20, hei=10;
    UINT t=0,c;

	for(UINT i=0; i<2; i++)
	for(UINT j=0; j<3; j++)
	{
            if (t < MapCounter ) c=15;
            else c=1;

            t++;

        scr.rectangle(dx+j*len, dy+i*hei,
            len, hei,c);
    }

    scr.putpixel(dx,dy,0);
    scr.putpixel(dx+len*3-1,dy,0);

    scr.putpixel(dx,dy+hei*2-1,0);
    scr.putpixel(dx+len*3-1,dy+hei*2-1,0);
	}
*/
	//Sprite.Show(95,12,SPRITE_SMALLMONEY);
	Sprite.Show(93,2, SPRITE_MARIOFLY, SCREEN::TRANSP);

	scr.color=16;
	scr.locateXY(15*8,(n+1)*8);
	scr << "x " << Lives;

	scr.color=15;
	scr.locateXY(15*8-1,(n+1)*8-1);
	scr << "x " << Lives;


	scr.color=16;
	scr.locateXY(1*4,4);
	scr<<"ОЧКИ";

	scr.color=15;
	scr.locateXY(1*4-1,4-1);
	scr<<"ОЧКИ";

	scr.color=16;
	scr.locateXY(1*4,4+10);
	scr.putNumb(Score,6);

	scr.color=15;
	scr.locateXY(1*4-1,4+10-1);
	scr.putNumb(Score,6);

    //показываем мощность стрел, кинжалов и топоров
    /*{
		scr.setcolor(14);
		Sprite.Show(160,0, SPRITE_ARROW);
		scr << cur(24,0) << ArrowPower;

		Sprite.Show(160,8, SPRITE_DAGGER);
		scr.locateXY(24*8, 10);
		scr<< DaggerPower;

		Sprite.Show(160,18, SPRITE_AXE);
		scr.locateXY(24*8, 21);
		scr << AxePower;
		scr.setcolor(15);
	}*/

    int k=SPRITE_ARROW;	//по умолчанию стрела
    switch (Arms)
    {
		case ARROW:
			k=SPRITE_ARROW;
			break;
		
		case DAGGER:
			k=SPRITE_DAGGER;
			break;
		
		case AXE:
			k=SPRITE_AXE;
			break;
		
		case SALIVA:
			k=SPRITE_SALIVA1;
			break;
    }
    Sprite.Show(210, 12, k);


    //scr << cur (23,n) << "WORLD" ;
	//scr << cur(24,n+1) << LevelNumber/4+1 << '-' << LevelNumber%4+1;


	scr.color=16;
    scr.locateXY(34*8,4);
	scr << "ВРЕМЯ";

	scr.color=15;
	scr.locateXY(34*8-1,4-1);
	scr << "ВРЕМЯ";

	scr.color=16;
	scr.locateXY(35*8,4+10);
	scr << Time;

	scr.color=15;
	scr.locateXY(35*8-1,4+10-1);
	scr << Time;
	
}

//создать очки
//score - число очков
//svisor - ссыка на супервизор объектов
// ob - сслыкна на обычный объект. здесь используются TimeLive, x,y - координаты
// первой цыфры. Все остальные параметры как обычно
//используем рекурсию
void SUPERMARIO::CreateScore(int score, ANIM & svisor, ANIM & ob)
{
        int t=score % 10;
	if (score>9) {
		CreateScore( score/10, svisor, ob);
		}
	ob.SpriteIndex=SPRITE_DIGITAL0+t;
	ob.AlwaysAnimate=TRUE;
		svisor+=ob;
	ob.x+=6;
}



//===================обновляем координаты у чужих==================
void SUPERMARIO::ALIEN::RenewXY()
{
	//обновляем координату X
	x+=Speedx;
	Speedx+=Acceleratx;
	RenewRect();

	//если чужой не загашен
	if (~Status & DEATH)
	{
		//если не удалось пройти через преграды
		if (!chk_all(*this,0) )
		{
			if (Speedx>0)
			{
				x-=int(x)%24;
			}
			else
			{
				x-=int(x)%24;
				x+=24;
			}
		}
	}


	RenewRect();

	//обновляем координату Y
	y+=Speedy;
	Speedy+=Acceleraty;
	RenewRect();

//	int collis;	//было ли столкновение с полом

	if (~Status & DEATH)
	{
		//если не удалось пройти через преграды
		if (!chk_all(*this,0) )
		{
			//летел вниз
			if (Speedy>0)
			{
				y-=int(y)%24;
			}
			else
			{
				y=y-int(y)%24+24;
			}
		}
	}

	RenewRect();

	//ANIM::RenewXY();

	//если чужой метртвый - ничего не делать
	if ( Status & DEATH ) return;



	//иначе чужой живой

	//************не даем чужим пройти через преграды********
		  if ( ! chk_left(*this,0) )	Speedx=fabs(Speedx);

		  if ( !chk_right(*this,0) )	Speedx=-fabs(Speedx);

		  ANIM ob;
		  ob=*this;
		  ob.x+=24*sign(Speedx);
		ob.RenewRect();


		//если под чужим ничего нет
		if ( chk_down(*this,0) )
		{
			//чужой падает
			Acceleraty=0.2;
		  }

	//если внизу впереди пусто на одну клетку
		if ( chk_down(ob,0) )
		{
		//если внизу пусто еще на несколько клеток
					 if ( scanlevel_down(ob, 0) )
		{
			//меняем направление по оси Ох на противоположное
			Speedx*=-1;
		}
		//иначе внизу на ближайшие несколько клеток что-то есть
		{
			//Acceleraty=0;
		 }


	}
	//иначе внизу даже на одну клетку что-то есть
	else
	{
			//y-=int(y)%24;
			Speedy=0;
			Acceleraty=0;
	}


}

void SUPERMARIO::MARIO::RenewXY()
{
	Supermario.MarioRenewXY(*this);
}

//========= 'RenewXY()' - обновление координат у марио ============2
void SUPERMARIO::MarioRenewXY(MARIO &rk)
{
	//если марио мертвый, надо просто обновлять
	// координаты без всяких проверок
	if (rk.Status & MARIO_DEATH)
	{
		rk.PERSON::RenewXY();
		rk.RenewRect();
		return;
	}

	//марио должен шевелить ногами в соотвествии со скоростью
	//если не под водой
	if (~LevelStatus & LEVEL_UNDERWATER)
	{
		rk.FrameSpeed=fabs(rk.Speedx)/6.0;
	}
	//иначе под водой
	else
	{
		//шевелит ногами медленно
		rk.FrameSpeed=fabs(rk.Speedx)/10.0;
	}

	//перемещаем Mario на новое место по оси Ox
	rk.x+=rk.Speedx;

	//если марио прилеплен надо сместить его относительно
	//лифта
	if (rk.Status & MARIO_CLAMMY)
	{
		rk.ClammyX+=rk.Speedx;
	}

	//обновляем его местоположение
	rk.RenewRect();

	//если после перемещения по оси Ox Mario оказался
	//в кирпичах
	if ( ! chk_all(rk,0) )
	{
		//Debug("Can't move on Ox");

		//возвращаем его на место по оси oX
		rk.x-=rk.Speedx;
		//ClammyX-=Speedx*SPEED_UNIT;

		//обнуляем скорость
		rk.Speedx=0;

		//обнуляем ускорение
		rk.Acceleratx=0;

		// ВАЖНО ! Обновляем его местоположение
		rk.RenewRect();
	}
	//иначе после перемещения по оси Ox Mario свободен
	else
	{
		//увеличиваем скорость Marioа по оси Ox
		rk.Speedx+=rk.Acceleratx;

		//если идет и (не летит или под водой)
		if (rk.Speedx && (!rk.Speedy || LevelStatus & LEVEL_UNDERWATER))
		{
			//пусть шевелит ногами
			rk.RenewFrame();
		}
	}

	//перемещаем Mario на новое место по оси Oy
	rk.y+=rk.Speedy;
	rk.RenewRect();

	//если перемещение по оси oY оказалось невозможным
	//из-за кирпичией
	if ( ! chk_all(rk,0) )
	{
		//Debug("Can't move on Oy");
		//rk.y-=rk.Speedy;

		//если Mario летел вниз
		if (rk.Speedy>0)
		{
			//возвращаем его на место по оси oy
			rk.y-=int(rk.y)%24;
			//обнуляем скорость
			rk.Speedy=0;
			//обнуляем ускорение
			rk.Acceleraty=0;
		}
		//Mario летел вверх
		else
		{
			Sound.play(SND_POP1);
			//очень точно центруем Mario
			rk.y=rk.y-int(rk.y)%24+24;

			//обнуляем все
			//(а то будет дрожать)
			rk.Speedy=0;
			rk.Acceleraty=0;
		}
	}
	//иначе ничего не мешает падать...
	else
	{
		//увеличиваем скорость Marioа по оси Oy
		rk.Speedy+=rk.Acceleraty;
	}

	//обновляем структуру Rect
	rk.RenewRect();

	//если под Mario находится пустота и не падает
	if ( chk_down(rk,0) && !rk.Acceleraty )
	{
		//велим марио падать
		//?????
		if (LevelStatus & LEVEL_UNDERWATER)
			rk.Acceleraty=0.09;
		else 
			rk.Acceleraty=0.2;
	}

	//rk.Acceleraty=0.2;
	//и напоследок
	//если марио летит и не под водой
	if (rk.Speedy && ~LevelStatus & LEVEL_UNDERWATER)
	{
		   if (~rk.Status & MARIO_BIG)
			rk.SpriteIndex=SPRITE_MARIOFLY;
		else
			rk.SpriteIndex=SPRITE_LIZARDFLY;
	}
	else
	{
		rk.SpriteIndex=int(rk.FrameCurrent);
	}

	//если падает слишком быстро, ограничиваем скорость
	//если под водой
	if ( LevelStatus & LEVEL_UNDERWATER)
	{
		if (rk.Speedy>3) rk.Speedy=3;
		//если на воздухе
		else
		if (rk.Speedy>7) rk.Speedy=7;
	}

	//если под водой, не даем подняться выше воды
	if (LevelStatus & LEVEL_UNDERWATER)
	{
		if (rk.y<0) rk.y=0;
	}


	//************************************************
	//************** собираем разные призы************
	//************************************************
	{

		#define N 8
		ANIM rk2=rk;
		int x=rk2.Rect.Left+10;
		int y=rk2.Rect.Top+10;
		rk2.Rect.Left+=N;
		rk2.Rect.Right-=N;
		rk2.Rect.Top+=N;
		rk2.Rect.Bottom-=N;
		#undef N

		//собрали монетку
		if( (Level.ReadXY(x,y)  & LEVEL::MASK) == BRICK::MONEY
		 && !(Level.ReadXY(x,y) & LEVEL::ALIEN)
		)
		{
			Level.WriteXY(x,y,0);

			MoneyCounter++;
			//за 100 монеток даем жизнь
			if (MoneyCounter>=100)
			{
				MoneyCounter=0;
				Lives++;
				Sound.play(SND_NEWLIVE, SOUND::NOSTOP);
			}
			else    Sound.play(SND_APPLE);

			//очки забавно подпрыгивают
			ANIM ob;
			int x=rk2.Rect.Left,y=rk2.Rect.Top;
			ob.x=x-x%24;
			ob.y=y-y%24;
			ob.Speedx=rk.Speedx/2;
			ob.Speedy=-4;
			ob.Acceleraty=0.2;
			//ob.TimeLive=24;
			CreateScore(200, SCORES, ob);
			Score+=200;
		}

		//собрали кристалл
		if( chk_all_transp(rk2,BRICK::CRYSTAL) )
		{
			Level.WriteXY(rk2.Rect.Left,rk2.Rect.Top,0);

			MoneyCounter++;
			//за 7-ой кристал даем жизнь
			if (MoneyCounter>=7)
			{
				MoneyCounter=0;
				Lives++;
				Sound.play(SND_NEWLIVE, SOUND::NOSTOP);
			}
			else Sound.play(SND_APPLE);

		}

		//19 may 2008 собрали зелье
		if( chk_all_transp(rk2,111) )
		{
			Level.WriteXY(rk2.Rect.Left,rk2.Rect.Top,0);
			
			rk.Status|=MARIO_WIZ;
			Sound.play(SND_EXORCISM);
		}


		//собрали карту
		if( (Level.ReadXY(int(rk2.x+12),int(rk2.y+12)) & LEVEL::MASK) == BRICK::MAP )
		{
			MapCounter++;

			//собрали всю карту
			if (MapCounter >= 6)
			{
				OldArms=Arms;	//сохраняем старое оружие
				Arms=SALIVA;
				ArmsPower=SalivaPower;
			}

			Level.WriteXY(int(rk2.x+12),int(rk2.y+12),0);

			Sound.play(SND_RESTART, SOUND::NOSTOP);

			int r=63,g=63,b=63;
			scr.SetColorRegister(0,r,g,b);
			scr.pause(4);

			r=0,g=0,b=0;
			scr.SetColorRegister(0,r,g,b);

		}

		 //собираем оружие, если оружие не сопли
		 if (Arms != SALIVA)
		 {
			//собрали стрелу
			if( chk_all_transp(rk2,BRICK::ARROW) )
			{
				if ( Arms == ARROW)
				{
					ArrowPower+=1;
					ArmsPower=ArrowPower;
				}

				Level.WriteXY(rk2.Rect.Left,rk2.Rect.Top,0);
				Arms=ARROW;

				Sound.play(SND_APPLE);
			}

			//собрали ножик
			if( chk_all_transp(rk2,BRICK::DAGGER) )
			{
				if (Arms == DAGGER)
				{
					DaggerPower+=2;
					ArmsPower=DaggerPower;
				}


				Level.WriteXY(rk2.Rect.Left,rk2.Rect.Top,0);
				Arms=DAGGER;

				Sound.play(SND_APPLE);
			}

			//собрали топорик
			if( chk_all_transp(rk2,BRICK::AXE) )
			{
				if (Arms == AXE)
				{
					AxePower+=3;
					ArmsPower=AxePower;
				}

				Level.WriteXY(rk2.Rect.Left,rk2.Rect.Top,0);
				Arms=AXE;

				Sound.play(SND_APPLE);
			}
		 }
	}

	//******************************************
	//   проверяем, упал ли марио в пропасть
	//******************************************
	if (rk.y>Level.MaxY+200+24)
	{
		Sound.play(SND_EXORCISM);
		//делаем рика загашенным
		rk.Status|=MARIO_DEATH;
	}


//******************************************
//   МАРИО выбивает знаки вопроса и кирпичи
//******************************************
{
	int x,y;
	x=rk.Rect.Left+12;
	y=int(rk.y-1);

	//int k=get_up(rc);
	int k=ReadXY(x,y) & LEVEL::MASK;     //код кирпича без атрибутов
	int k_nomask=Level.ReadXY(x,y);	//код с уровня с атрибутами

	//если сверху кирпич и марио летит вверх
	if ( k!=-1 && rk.Speedy<=0.5)
	{
		ANIM br;

		//вычисляем координаты кирпича
		x-=int(x)%24;
		y-=int(y)%24;

		br.x=x;
		br.y=y;
		br.SpriteIndex=BRICK::ANSWER;
		br.TimeLive=24;
		br.Acceleraty=0.3;
		br.Speedy=-3;
		br.Hot.Set(0,0,23,23);

		switch(k_nomask)
		{
			//невидимая звезда
			case ALIEN::MUSHROOMLIVE |LEVEL::ALIEN | LEVEL::logTRANSP:
			{
				br.SpriteIndex=BRICK::ANSWER;

				Level.WriteXY(x,y,BRICK::ANSWER);
				rk.Speedy=0;
                rk.Acceleraty=0;
				rk.x+=3;


				ANIM gr;
				gr.x=br.x;
				gr.y=br.y-10;
				gr.SpriteIndex=SPRITE_STAR;
				gr.Acceleraty=0.2;
				gr.Speedy=-4;
				gr.Speedx=+1.5;
				gr.Hot.Set(0,0,22,23);

				gr.TimeLive=10;

				Prize+=gr;
				break;
			}

			//гриб, дающий жизнь
			/*case BRICK::MUSHROOMLIVE | LEVEL::ALIEN | LEVEL::logTRANSP:
			{
				Level.WriteXY(x,y,0);

				ANIM gr;
				gr.x=br.x;
				gr.y=br.y-20;
				gr.Acceleraty=0.2;
				gr.Speedx=1.0;
				gr.Speedy=-3;
				gr.Hot.Set(5,5,16,23);
				gr.SpriteIndex=SPRITE_MUSHROOM_LIVE;
				gr.TimeLive=30;

				Prize+=gr;

				br.SpriteIndex=BRICK::ANSWER;
				break;

			} */

		}

		switch(k)
		{

			//разбиваем кирпичи
			case BRICK::BREAK:
			{

				//чтобы не пролетал вверх
				rk.Speedy=0.01;

				//если марио маленький кирпич
				//только подпрыгивает
				if (~rk.Status & MARIO_BIG)
				{
					br.SpriteIndex=BRICK::BREAK;
					Answer+=br;
					Level.WriteXY(x,y,0);
					rk.Speedy=0.01;
					Sound.play(SND_FINGER);

				}
				//иначе кирпич разлетается
				else
				{

					//увеличиваем число очков
					Supermario.Score+=50;

					Level.WriteXY(x,y,0);

					PERSON ob;
					ob.Hot.Set(0,0,24,14);

					ob.x=br.x;
					ob.y=br.y;
					ob.SpriteIndex=SPRITE_SMALLBRICK;
					ob.TimeLive=0;
					ob.Acceleraty=0.3;
					#define sx 2
					#define sx2 2.5
					#define sy -4
					#define sy2 -2

					if (Brick.Counter>16)
					{
						Brick.Del(&Brick[0]);
						Brick.Del(&Brick[0]);
						Brick.Del(&Brick[0]);
						Brick.Del(&Brick[0]);
					}

					ob.Speedx=sx;
					ob.Speedy=sy;
					ob.Movement=PERSON::RIGHT;
					Brick+=ob;

					ob.Speedx=-sx;
					ob.Speedy=sy;
					ob.Movement=PERSON::LEFT;
					Brick+=ob;

					ob.Speedx=-sx2;
					ob.Speedy=sy2;
					ob.Movement=PERSON::FLIP_VERT | PERSON::LEFT;
					Brick+=ob;

					ob.Speedx=sx2;
					ob.Speedy=sy2;
					ob.Movement=PERSON::FLIP_VERT | PERSON::RIGHT;
					Brick+=ob;

					Sound.play(SND_EXPLODE);
				}

				break;
			}


			//пустой знак вопроса
			case BRICK::ANSWER:
			{
				br.SpriteIndex=BRICK::ANSWER;
				break;
			}
			
			//выбили звезда
			case BRICK::BRICKSTAR:
			{
				br.SpriteIndex=BRICK::BRICKSTAR;

				ANIM gr;
				gr.x=br.x;
				gr.y=br.y-10;
				gr.SpriteIndex=SPRITE_STAR;
				gr.Acceleraty=0.2;
				gr.Speedy=-3;
				
				int k=1;
				if (rand()%10>5) k=-1;
				
				gr.Speedx=-1.5*k;
				gr.Hot.Set(0,0,22,23);

				gr.TimeLive=10;
				Prize+=gr;

				break;
			}

			//грибок
			case BRICK::ANSWERMUSHROOM:
			{
				ANIM gr;
				gr.x=br.x;
                gr.y=br.y-20;
				if (~rk.Status & MARIO_BIG)
                {
					gr.SpriteIndex=SPRITE_MUSHROOM_BIG;
                }
                else
				{
					gr.SpriteIndex=SPRITE_FLOWER;
                }
				gr.Acceleraty=0.2;
				gr.Speedx=1.0;
                gr.Speedy=-3;
                gr.Hot.Set(5,5,16,23);
                gr.TimeLive=30;
                Prize+=gr;

				br.SpriteIndex=k;
				break;
			}

			//кирпичик, где много монеток
			case BRICK::MANYMONEY:
            {
				br.SpriteIndex=BRICK::MANYMONEY;
				break;
			}
		}


		/*switch(k_nomask)
        {
			case BRICK::MUSHROOMLIVE | LEVEL::ALIEN | LEVEL::logTRANSP:
            {
				Answer+=br;
				Level.WriteXY(x,y,0);
        	    rk.Speedy=0.01;
				Sound.play(SND_FINGER);
				break;
			}
			
		}*/

		switch(k)
		{
			//кирпичики подлетают
			case BRICK::BRICKSTAR:
			//case BRICK::BREAK:
			case BRICK::ANSWER:
			case BRICK::ANSWERMUSHROOM:
			case BRICK::MANYMONEY:
			case ALIEN::MUSHROOMLIVE:
			{
				Answer+=br;
				Level.WriteXY(x,y,0);
				rk.Speedy=0.01;
				Sound.play(SND_FINGER);
				break;
             }
		}

        switch(k)
        {
			case BRICK::MANYMONEY:
			case BRICK::ANSWER:
			{
				//запускаем монетку
				br.y-=20;
				br.Speedx=0;
				br.Speedy=-3.0;
				br.Acceleraty=0;
				br.FrameFirst=SPRITE_MONEYSTART;
				br.FrameLast=SPRITE_MONEYEND;
				br.FrameSpeed=0.9;
				br.TimeLive=40;
				br.Acceleraty=0.15;
				Money+=br;
				Supermario.MoneyCounter++;
                Sound.play(SND_GFX3);
			}
		}
	}
}


//***************************************************
//   ???mario гасит чужих или чужие гасят mario???
//***************************************************

//проверка столкновения марио с линией огня
for(int j=0;j<FireLine.Counter; j++)
{
ANIM &fr=FireLine[j];
//если огонь загасил марио
//????????????
if (~rk.Status & MARIO_PROTECTED && CheckUnionRects(fr.Rect,rk.Rect) != FALSE)
{
                                                //гасим марио
	rk.Speedx=0;
	rk.Speedy=-5;
	rk.Acceleratx=0;
	rk.Acceleraty=0.2;
	rk.FrameSpeed=0;
	rk.Status|=MARIO_DEATH;
	Sound.play(SND_LAUGHT);
}
}

//проверка чужих
for(j=0;j<Alien.Counter;j++)
{
PERSON &al=(PERSON&) Alien[j];
//если живой чужой столкунлся с марио
if (!al.Status && CheckUnionRects(al.Rect,rk.Rect) != FALSE)
{
	//если чужой упал на марио сверху
	if ( rk.y-al.y>=0)
	{
		//если марио защищенный
		if (rk.Status & MARIO_PROTECTED)
		{
			//он загасил чудовище
			Sound.play(SND_POP1);

			//гасим чудовище
			al.Status=ALIEN::DEATH;
			al.TimeLive=250;
			al.Speedx=rk.Speedx;
			al.Acceleraty=0.2;
			al.Speedy=-4;
			al.FrameSpeed=0;
			al.Movement |= PERSON::FLIP_VERT;
			//всегда анимировать
			al.AlwaysAnimate=TRUE;
		}

		//иначе марио не защищенный
		//если не дракон(он не гасит марио)
		else if (al.FrameFirst != SPRITE_LIZARDSTART)
		{
			//гасим марио
			rk.Speedx=0;
			rk.Speedy=-5;
			rk.Acceleratx=0;
			rk.Acceleraty=0.2;
			rk.FrameSpeed=0;
			rk.Status|=MARIO_DEATH;
			Sound.play(SND_POP1);
			//Sound.play(SND_LAUGHT);
			//выдерживаем паузу
			//scr.pause(DEATHPAUSE);
		}
		break;
	}

	//иначе наоборот - марио загасил чужого
	else
	{
		switch(al.FrameFirst)
		{
			case SPRITE_MASHASTART:
			case SPRITE_TURTLESTART:
			case SPRITE_PIGSTART:
			//case SPRITE_LIZARDSTART:

			//создаем очки
			ANIM ob;
			ob.x=al.x;
			ob.y=al.y;
			ob.Speedy=-0.7;
			ob.TimeLive=30;
			CreateScore(100,SCORES,ob);
			Supermario.Score+=100;
		}


		rk.Speedy=-2.5;

		//останавливаем и гасим чужого
		switch(al.FrameFirst)
		{
			case SPRITE_MASHASTART:
			case SPRITE_TURTLESTART:
			//свиньи и лизарды гасятся только оружием
			//case SPRITE_LIZARDSTART:
			//case SPRITE_PIGSTART:

			Sound.play(SND_POP1);

			al.Status=ALIEN::DEATH;
			al.TimeLive=20;
			al.Speedx=0;
			al.Speedy=0;
			al.Acceleraty=0;
			al.Acceleratx=0;
			al.FrameSpeed=0;
		}

		switch (al.FrameFirst)
		{

			//если марио напрыгнул на свинку
			case SPRITE_PIGSTART:
			{
				//о-очень высоко подпрыгивает
				rk.Speedy=-9;
				break;
			}
			//если марио напрыгнул на дракона
			case SPRITE_LIZARDSTART:
			{
				//о-очень высоко подпрыгивает
				rk.Speedx=4+0.1*random(50);
				if (random(2)) rk.Speedx*=-1;
				break;
			}

			//если марио напрыгнул на гриб
			case SPRITE_MASHASTART:
				al.SpriteIndex=SPRITE_MASHASMALL;
				break;

			//если марио напрыгнул на черепеаху
			case SPRITE_TURTLESTART:
				al.SpriteIndex=SPRITE_TURTLEHOUSE;
				al.FrameFirst=SPRITE_TURTLEHOUSE;
                al.FrameLast=SPRITE_TURTLEHOUSE;
                al.FrameCurrent=SPRITE_TURTLEHOUSE;
                al.TimeLive=0;
                al.Status=0;
                break;
		
			//если марио напрыгнул на панцирь
			case SPRITE_TURTLEHOUSE:
				//звучит звук
				Sound.play(SND_POP);

				//время жизни панциря увеличивается
				al.TimeLive+=500;
				al.Status=0;

				//если панцирь стоит
				if (al.Speedx==0)
					//запускаем его
					al.Speedx=4*sign(rk.Speedx+0.01);
				//иначе панцирь двигается
				else
					//останавливаем его
					al.Speedx=0;
		}

	}
}
}

}

//=============стартуем игру==============
SUPERMARIO::SUPERMARIO()
{
	ChangeEffect=false;
	GAMEEXIT=FALSE;
}

//проверяет, что находится над объектом(прямоугольником)
//what задает номер кирпича для проверки
//mask задает те атрибуты, которые необходимо обнулить при проверке
//ВНИМАНИЕ: по умолчанию зануляются все аттрибуты
//Возврат: TRUE - если над объектом находится только этот кирпич
//FALSE - если над объектом есть другие кирпичики
int SUPERMARIO::chk_up(MOVEOBJ & ob, int what, int mask)
{
	int x=ob.Rect.Left;
	int y=ob.Rect.Top-1;
	int x1=ob.Rect.Right;

	if(
		(ReadXY(x,y) & mask) == what &&
		(ReadXY(x1,y) & mask) == what
	  )
        {
		return 1;
        }
		else
        {
		return 0;
        }
}

int SUPERMARIO::chk_left(MOVEOBJ & ob, int what, int w)
{
	int x=ob.Rect.Left;
	int y=ob.Rect.Top;
	int y1=ob.Rect.Bottom;

	if (ReadXY(x-w,y) == what &&
		ReadXY(x-w,y1) == what)
		return 1;

	return 0;
}

int SUPERMARIO::chk_right(MOVEOBJ & ob, int what,int w)
{
	int y=ob.Rect.Top;
	int x1=ob.Rect.Right;
	int y1=ob.Rect.Bottom;

	if (ReadXY(x1+w,y) == what && ReadXY(x1+w,y1) == what)
		return 1;

	return 0;
}

int SUPERMARIO::chk_down(MOVEOBJ & ob, int what)
{
	int x=ob.Rect.Left;
	int x1=ob.Rect.Right;
	int y1=ob.Rect.Bottom;

	if (ReadXY(x,y1+1) == what && ReadXY(x1,y1+1) == what)
		return 1;

	return 0;
}


//проверяет, чтобы горячий прямоугольник спрайта находился в
//кирпичах what с атрибутами
//возвращает 1,если это так, или 0, если не так
int SUPERMARIO::chk_all(MOVEOBJ & ob, int what)
{
	int x=ob.Rect.Left;
	int y=ob.Rect.Top;
	int x1=ob.Rect.Right;
	int y1=ob.Rect.Bottom;

	if
	(
		ReadXY(x,y) == what &&
		ReadXY(x,y1) == what &&
		ReadXY(x1,y) == what &&
		ReadXY(x1,y1) == what
	)
		return 1;

	return 0;
}

//проверяет, находится ли спрайт в пустоте или в фоне
//возврат 0 - если в пустоте
// != 0 - если в чем-то
int SUPERMARIO::chk(MOVEOBJ & ob)
{
	int x=ob.Rect.Left;
	int y=ob.Rect.Top;
	int x1=ob.Rect.Right;
	int y1=ob.Rect.Bottom;
	int m=Level.ReadXY(x,y);
	if (! (m & LEVEL::logTRANSP) ) return m;
	m=Level.ReadXY(x1,y1);
	if (! (m & LEVEL::logTRANSP) ) return m;
	m=Level.ReadXY(x,y1);
	if (! (m & LEVEL::logTRANSP) ) return m;
	m=Level.ReadXY(x1,y);
	if (! (m & LEVEL::logTRANSP) ) return m;
	return 0;
}


#define BOX_LADDER 10

int SUPERMARIO::chk2(MOVEOBJ &ob)
{
	return chk(ob);
}


//возвращает 0, если читается 0 или прозрачный
//иначе возвращается код кирпича без атрибутов
int SUPERMARIO::ReadXY(int x,int y)
{
	int k=Level.ReadXY(x,y);
	if ( k & LEVEL::logTRANSP )	return 0;
	return k & LEVEL::MASK;
}

//возвращается код кирпича без атрибутов
int SUPERMARIO::ReadXY1(int x,int y)
{	int k=Level.ReadXY(x,y);
	return k & LEVEL::MASK;
}


//проверяет, находится ли спрайт в пустоте
int SUPERMARIO::chk_all_transp(MOVEOBJ & ob, int what)
{
	int x=ob.Rect.Left;
	int y=ob.Rect.Top;
	int x1=ob.Rect.Right;
	int y1=ob.Rect.Bottom;

	if (ReadXY1(x,y) == what &&
		ReadXY1(x,y1) == what &&
			ReadXY1(x1,y) == what &&
				ReadXY1(x1,y1) == what )
		return 1;

	return 0;
}



//Возвращает -1 если вверху разные кирпичи
// Иначе код этих кирпичей
int SUPERMARIO::get_up(MOVEOBJ & ob)
{
	int x=ob.Rect.Left;
	int y=ob.Rect.Top;
	int x1=ob.Rect.Right;

	if (ReadXY(x,y-1) == ReadXY(x1,y-1) )
		return ReadXY(x,y-1);

	return -1;

}


//==================== проигрывание мелодии =========================
void SUPERMARIO::PlayMusic(int n)
{
/*	CurrentMusic=n;

	char ret[256];
	char buf[2048]="open ";

	strcat(buf,song[n]);
	strcat(buf, " alias snd");

//	mciSendString("stop snd", ret,sizeof(ret),NULL);
	mciSendString("close snd", ret,sizeof(ret),NULL);
    //играем мелодию
	mciSendString(buf, ret,sizeof(ret),NULL);
	mciSendString("set snd time format milliseconds",ret,sizeof(ret),NULL);
	wsprintf(buf,"seek snd to %i",song_start[n]);
	mciSendString(buf, ret,sizeof(ret),NULL);
	mciSendString("play snd", ret,sizeof(ret),NULL);

//	WinExec("\"C:\\Program Files\\Winamp\\Winamp.exe\" \"music\\raiders.mid\"",SW_HIDE);
//	WinExec(buf,SW_HIDE);
// 	WinExec(buf, SW_HIDE);
*/	
}


//========объекты  Rick ловять призы Prize=============
void SUPERMARIO::prPrizeCatch(ANIM &Rick, ANIM &Prize)
{
//******************************************************
//   призы не проходят сквозь стенки и марио ловит призы
//******************************************************
for(int j=0;j<Rick.Counter;j++)
for(int i=0; i<Prize.Counter;i++)
{
ANIM & al=Prize[i];
ANIM & rk=Rick[j];

//если поймали какой-то приз
if (CheckUnionRects(al.Rect,rk.Rect))
{
	Sound.play(SND_HEALTH, SOUND::NOSTOP);
	int scor;

	switch(al.SpriteIndex)
	{
		//поймали гриб, дающий жизнь
		case SPRITE_MUSHROOM_LIVE:
		{
			//увеличиваем число жизней
			Lives++;
			scor=1000;
			Sound.play(SND_RESTART);
			break;
		}

		//поймали звезду
		case SPRITE_STAR:
		{
			rk.Status|=MARIO_PROTECTED;
			ProtectedCounter+=1500*10;
			scor=2000;
			//PlayMusic(PROTECTED_MUSIC);
			Sound.play(SND_GHOTIC_FAST);
			break;
		}

		//поймали обычный гриб, дающий превращение в дракона (Лизард)
		case SPRITE_MUSHROOM_BIG:
		{
			scor=1000;
			rk.Status|=MARIO_BIG;
			rk.FrameFirst=SPRITE_LIZARDSTART;
			rk.FrameLast=SPRITE_LIZARDEND;
			rk.FrameCurrent=SPRITE_LIZARDSTART;
			rk.RenewFrame();
			break;
		}

		//поймали цветок
		//баг/фича - если цветок берет
		//не динозаврик - он тоже может стрелят
		case SPRITE_FLOWER:
		{
			scor=1500;
			rk.Status|=MARIO_CANFIRE;
			rk.FrameFirst=SPRITE_LIZARDSTART;
			rk.FrameLast=SPRITE_LIZARDEND;
			rk.FrameCurrent=SPRITE_LIZARDSTART;
			rk.RenewFrame();
		}
	}

	//создаем очки
	{
		ANIM ob;
		ob.x=al.x;
		ob.y=al.y+12;
		ob.Speedy=-0.7;
		ob.TimeLive=40;
		CreateScore(scor,SCORES,ob);
		Score+=scor;
	}

	//удаляем приз
	{
		Prize.Del(&al);
		i--;
	}

	//продолжаем цикл
	continue;
}//if (CheckUnionRects(al.Rect,rk.Rect))

		//даем возможность призу подняться без препятсвий
		if (al.TimeLive>3) continue;
		al.TimeLive=0;

		//если внизу пустота
		if (chk_down(al,0))
		{
			al.Acceleraty=0.2;
		}
		//иначе внизу земля
		else
		//если падает вниз
		if (al.Speedy>0)
		{
			al.y=int(al.y)/24*24;
			al.Acceleraty=0;

			//смотря какой приз
			//он будет отталкиваться
			//от земли по разному
			switch(al.SpriteIndex)
			{
				//звезда мощно
				case SPRITE_STAR:
				al.Speedy=-0.8*abs(al.Speedy);
				break;

				//гриб слабо
				case SPRITE_MUSHROOM_BIG:
				al.Speedy=-0.4*abs(al.Speedy);
				break;
				
				default:
				al.Speedy=-0.4*abs(al.Speedy);
				break;
				
			}
			//слишком низко не должен прыгать
			if (al.Speedy>-0.5) al.Speedy=0;
		}

		ANIM al2=al;
		al2.Rect.Bottom-=4;
		if (!chk_left(al2,0)) al.Speedx=abs(al.Speedx);
		if (!chk_right(al2,0)) al.Speedx=-abs(al.Speedx);
}
}

// эффект посинения экрана
void SUPERMARIO::ColorEffect()
{
	//эффект - черные точки растворяют изображение
	for(int j=0; j<1400; j++)
	{
		//scr.pause(1);
		for(int i=0; i<256; i++)
		{
			scr.putpixel(rand()%320, rand()%240, 0);
		}

		scr.update();
	}
			

}

int  SUPERMARIO::MenuConfiguration(void)
{
	Keyb.clear();
	scr.clear();
	scr.update();

	Timer.Restart(60);

	int y=8;
	double t=0;

	
	int N=4;	//число элементов меню
	char far * txt[]=
	{
		 "1. ОТКЛЮЧЕНИЕ ЗВУКА ",
		 "2. ОТКЛЮЧЕНИЕ МУЗЫКИ ",
		 "3. ПЕРЕНАЗНАЧЕНИЕ КЛАВИШ",
		 "4. ВЫХОД В ГЛАВНОЕ МЕНЮ"
	 };

	int TitleNew=-1;	//т.к. перед использованием TitleNew увеличивается
	int nm=0;
	int py=y;
	double levelx=0,speed_levelx=2.5;

   while ( !Keyb[KEY_ENTER] )
   {
	SCREEN &Screen=scr;

	//**** построение изображения *****
	Screen.setcolor(15);
	Screen.setbkcolor(0);
	Screen.rectangle(0,0,320,200,0);

	//вывод строк меню на экран
	for (int k=0; k<N; k++)
	{
		double	
				x1=(320-8*strlen(txt[k]))/2,
				y1=k*26+y*4;

		if (k == nm)
		{
	        scr.rectangle(int(x1),int(y1),8*strlen(txt[k]),24,3);
		}

		//string str(&BigFont,txt[k]);
		//str.Show(x1,y1);
		scr.locateXY(int(x1),int(y1));  
		scr.putText(txt[k]);

		//вывод указателя
		int px=20;
		Sprite.Show(int(x1-20),int(y1)-1,SPRITE_POINTER);

	}

	//если нажали клавишу ВВЕРХ
	if ( Keyb[KEY_UP] && py>y )
	{
		Keyb.Set(KEY_UP,0);

		py-=2;
		nm--;
		t=0;
	}

	//если нажали клавишу ВНИЗ
	if ( Keyb[KEY_DOWN] && py<y+(N-1)*2 )
	{
		Keyb.Set(KEY_DOWN,0);
		py+=2;
		nm++;
		t=0;
	}

	while (Timer.Counter <2);
	Timer.Counter=0;

	scr.color=15;//rand()%256;
	scr.center(15, "Солдат Марио");
	
	static t=0;
	scr.color=15;//t;
	scr.center(200-15, "(c) 1997-2011 Wiz");
	t++;

	scr.update();

	}

   Keyb.clear();

   if (nm==0)
   {
	   Sound.sound_enable=false;
	   Sound.stop();
   }
   return nm;
}


int  SUPERMARIO::MenuMain(void)
{
	scr.clear();
	scr.update();

	SPRITE zast(&scr,2);
	SPRITE::IMAGE im;
	int SPRITE_ZAST0=256;

	im.ID=SPRITE_ZAST0;
	im.Attribute=0;
	zast.LoadSpriteform("graph\\zast.sp0",im);

	//перенастраиваем счетчик случайных чисел
	//random();

	for(UINT i=0; i<GetTickCount()%100; i++) rand();

	Level.Load(rand()%10);
	
	Timer.Restart(60);

	#define GAMENAME "SUPER JACKS"

	BIGSTRING s1(&BigFont,GAMENAME);

	ANIM Title(&BigFont);
	PERSON Mario(&Sprite);

	//определяем границы перемещения
	{
		MOVEOBJ::Lim.Left=-24;
		MOVEOBJ::Lim.Right=324;
		MOVEOBJ::Lim.Bottom=224;
		MOVEOBJ::Lim.Top=-24;
		MOVEOBJ::WindowX=0;
		MOVEOBJ::WindowY=0;
	}

	int N=7;	//число элементов меню
	char far * txt[]=
	{
		 "1. ОДИН ИГРОК",
		 "2. ДВА ИГРОКА",
		 "3. ТРИ ИГРОКА",
		 "4. КОНФИГУРАЦИЯ",
		 "5. РЕДАКТОР УРОВНЕЙ",
		 "6. РЕДАКТОР СПРАЙТОВ",
		 "7. ВЫХОД"
		 
	 };

	int TitleNew=-1;	//т.к. перед использованием TitleNew увеличивается
	int nm=0;
	double levelx=0,speed_levelx=2.5;

	while ( !Keyb[KEY_ENTER] )
	{
	SCREEN &Screen=scr;

	//**** построение изображения *****
	Screen.setcolor(15);
	Screen.setbkcolor(0);
	Screen.rectangle(0,0,320,200,0);

	if (levelx>0)
	{
		double levely=Level.MaxY-30+30*sin(levelx/90);
		Level.Show(int(levelx),int(levely));
	}
	
	levelx+=speed_levelx;
	
	if (levelx>320*4) 
	{
		speed_levelx*=-1;
		Level.Load(rand()%10);
	}
	
	if (levelx<0) 
	{
		speed_levelx*=-1;
		Level.Load(rand()%10);
	}

	//вывод заставки
	//zast.Show(90+rand()%3,0,SPRITE_ZAST0);

	//вывод строк меню на экран
	for (int k=0; k<N; k++)
	{
		const int HEI_STRING=20;
		double x1,y1;
		//x1=(320-8*strlen(txt[k]))/2;
		x1=90;
		y1=k*HEI_STRING+40; //у координаты вывода меню

		if (k == nm)
		{
			scr.rectangle(int(x1),int(y1),8*strlen(txt[k]),HEI_STRING-5,3);
		}

		//STRING str(&BigFont,txt[k]);
		//str.Show(x1,y1);
		scr.locateXY(int(x1),int(y1));  
		scr.putText(txt[k]);

		//вывод указателя
		int px=20;
		Sprite.Show(int(x1-20),int(y1)-1,SPRITE_POINTER);

	}

	//нажали вверх
	if ( Keyb[KEY_UP])
	{
		nm--;
		if (nm==-1) 
		{
			nm=N-1;
		}
		Keyb.Set(KEY_UP,0);
	}

	//если нажали клавишу ВНИЗ
	if ( Keyb[KEY_DOWN])
	{
		nm++;
		if (nm==N)
		{
			nm=0;
		}
		Keyb.Set(KEY_DOWN,0);
	}

	Title.Animate();
	Mario.Animate();

    //если все надписи прошли, показывать надпись 'SUPER MARIO'
	if (TitleNew == 4) s1.Show(20,35);

	while (Timer.Counter <2);
	Timer.Counter=0;

	scr.color=15;
	scr.center(15, "Солдат Марио");
	
	scr.color=15;
	scr.center(200-15, "(c) 1997-2011 Wiz");

	scr.update();

	if (Keyb[KEY_1]) return 1;
	if (Keyb[KEY_2]) return 2;
	if (Keyb[KEY_3]) return 3;
	if (Keyb[KEY_4]) return 4;
	if (Keyb[KEY_5]) return 5;
	if (Keyb[KEY_6]) return 6;
	if (Keyb[KEY_7]) return 7;
	if (Keyb[KEY_8]) return 8;
	if (Keyb[KEY_9]) return 9;
	if (Keyb[KEY_0]) return 0;

	}

   return nm+1;
}
