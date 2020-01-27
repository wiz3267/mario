//12:15 1500 òãä

//Mario1.cpp
////////////////////////////////////////////////////////
//						      //
// MARIO1.CPP ñîäåðæèò ðåäêî ìîäèôèöèðóåìûå ôóíêöèè   //
//                                                    //1
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "total.h"

//double sign(double);

int random(int);

//================çàãðóçêà ñïðàéòîâ==================
void SUPERMARIO::LoadSprites()
{
	int t,i;
	SPRITE::IMAGE im;

	BigFont.DeleteAllSprites();
	Sprite.DeleteAllSprites();
	LvSpr.DeleteAllSprites();

	//çàãðóæàåì áóêâû
	{
		//çàãðóæàåì áóêâû
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		for (i=0; i<28; i++)
		{
			im.ID=i;
			BigFont.Load("graph\\fontbig.dat", i*24*24L,im);
		}

		//èçìåíÿåì ñëó÷àéíî öâåò áóêâ
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

	//çàãðóæàåì òåñòû
	{
		im.ID=SPRITE_TEST;
		im.Attribute=0;
		Sprite.LoadSpriteform("graph\\test.sp0",im);
	}

	//çàãðóæàåì öèôðû
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


	//SPRITE_MUSHROOM_LIVE,		//ãðèá, äàþùèé æèçíü

	//çàãðóæàåì ãðèá, äàþùèé æèçíü
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MUSHROOM_LIVE;
		Sprite.Load("graph\\sprite.dat", 5*24*24L,im);
	}

	//çàãðóæàåì îðóæèå ñòðåëó
	{
		im.Hei=7;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_ARROW;
		Sprite.Load("graph\\levelbox.dat", (BRICK::ARROW-1)*24*24L,im);
	}

	//çàãðóæàåì îðóæèå íîæèê
	{
		im.Hei=12;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_DAGGER;
		Sprite.Load("graph\\levelbox.dat", (BRICK::DAGGER-1)*24*24L,im);
	}

	//çàãðóæàåì ñîïëè
	{
		im.Hei=14;
		im.Len=24;

		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_SALIVA1;
		Sprite.Load("graph\\sprite.dat", 75*24*24L,im);

		im.ID=SPRITE_SALIVA2;
		Sprite.Load("graph\\sprite.dat", 76*24*24L,im);
	}

	//çàãðóæàåì ðûáêó
	{
		im.ID=SPRITE_FISH1;
		Sprite.LoadSpriteform("graph\\fish.sp0", im);
		im.ID=SPRITE_FISH2;
		Sprite.LoadSpriteform("graph\\fish.sp1", im);
	}


	//çàãðóæàåì îðóæèå òîïîðèê
	{
		im.Hei=20;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_AXE;
		Sprite.Load("graph\\levelbox.dat", (BRICK::AXE-1)*24*24L,im);
	}

	//çàãðóæàåì óëèòêó
	{
		im.ID=SPRITE_HELIX1;
		Sprite.LoadSpriteform("graph\\helix.sp0", im);
		im.ID=SPRITE_HELIX2;
		Sprite.LoadSpriteform("graph\\helix.sp1", im);

	}

	//çàãðóæàåì àêóëó
	{
		im.ID=SPRITE_SHARK1;
		im.Attribute=SCREEN::FLIP_HORZ | SCREEN::TRANSP;
		Sprite.LoadSpriteform("graph\\shark.sp0", im);
		im.ID=SPRITE_SHARK2;
		Sprite.LoadSpriteform("graph\\shark.sp1", im);

	}


	//çàãðóæàåì ïóçûðèêè
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

	//çàãðóæàåì êîñìîíàâòà
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


	//çàãðóæàåì âçðûâ
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


	//çàãðóæàåì æåëòîãî îðëà
	{
		im.Hei=48;
		im.Len=48;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_EAGLESTART;
		Sprite.Load("graph\\spr.dat", 20,im);
		im.ID=SPRITE_EAGLEEND;
		Sprite.Load("graph\\spr1.dat",20,im);
	}

	//çàãðóæàåì ãîëîâó
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_HEAD1;
		Sprite.LoadSpriteform("graph\\head.sp0", im);

		im.ID=SPRITE_HEAD2;
		Sprite.LoadSpriteform("graph\\head.sp1",im);

			im.ID=SPRITE_HEAD3;
		Sprite.LoadSpriteform("graph\\head.sp2",im);
	}

	//çàãðóæàåì ãðèá, äàþùèé óâåëè÷åíèå
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MUSHROOM_BIG;
		Sprite.Load("graph\\sprite.dat", 50*24*24L,im);
	}

	//çàãðóæàåì àíèìàöèþ îòêðûâàíèÿ äâåðè
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

	//çàãðóæàåì, êàê îñûïàåòñÿ êèðïè÷èê
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

	//çàãðóæàåì, êàê ðàçðóøàåòñÿ ñòðåëà
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


	//çàãðóæàåì çâåçäó
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_STAR;
		Sprite.Load("graph\\sprite.dat", 51*24*24L,im);
	}

	//çàãðóæàåì öâåòîê
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_FLOWER;
		Sprite.Load("graph\\sprite.dat", 52*24*24L,im);
	}

	//çàãðóæàåì ìàëåíüêóþ ìîíåòêó
	{
		im.Hei=12;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_SMALLMONEY;
		Sprite.Load("graph\\sprite.dat", 34*24*24L,im);
	}

	//çàãðóæàåì ëèôò
	{
		im.Hei=15;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_LIFT;
		Sprite.Load("graph\\sprite.dat", 47*24*24L,im);
	}

	//çàãðóæàåì òåëåæêó
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

	//çàãðóæàåì òóçåìöà
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

	//çàãðóæàåì ÷åì ñòðåëÿåò Mario
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

	//çàãðóæàåì ëåòÿùåãî ìàðèî
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MARIOFLY;
		Sprite.Load("graph\\sprite.dat", 28*24*24L,im);
	}

	//çàãðóæàåì ìåðòâîãî ìàðèî
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MARIODEATH;
		Sprite.Load("graph\\sprite.dat", 13*24*24L,im);
	}

    //çàãðóæàåì ìîñòèê
	{
		im.Hei=15;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_BRIDG;
		Sprite.Load("graph\\sprite.dat", 64*24*24L,im);
	}

	//çàãðóæàåì ìîñòèê äëÿ âîäû
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_WATERBRIDG;
		Sprite.LoadSpriteform("graph\\wbridg.spr", im);
	}

	//çàãðóæàåì ïòè÷êó
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_BIRD1;
		Sprite.LoadSpriteform("graph\\bird.sp0", im);
		im.ID=SPRITE_BIRD2;
		Sprite.LoadSpriteform("graph\\bird.sp1", im);
	}

	//çàãðóæàåì ñêåëåòà
	{
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_SKELETON;
		Sprite.LoadSpriteform("graph\\skeleton.sp0", im);
	}

	//çàãðóæàåì ìàðèî
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

	//çàãðóæàåì çóáàñòûé öâåòîê
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

	//çàãðóæàåì õîäÿùèé ãðèáîê
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

	//çàãðóæàåì çëîáíîãî åæèêà
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

	//çàãðóæàåì ÑÆÀÒÛÉ õîäÿùèé ãðèáîê
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_MASHASMALL;
		Sprite.Load("graph\\sprite.dat", 22*24*24L,im);
	}


	//çàãðóæàåì ÏÀÍÖÈÐÜ
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_TURTLEHOUSE;
		Sprite.Load("graph\\sprite.dat", 44*24*24L,im);
	}

	//çàãðóæàåì ×ÅÐÅÏÀÕÓ
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

	//çàãðóæàåì ÄÐÀÊÎÍÀ
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

	//çàãðóæàåì ëåòÿùåãî äðàêîíà
	{
		im.Hei=24;
		im.Len=24;
		im.Attribute=SPRITE::SPRITETRANSPARENT;
		im.ID=SPRITE_LIZARDFLY;
		Sprite.Load("graph\\sprite.dat", 35*24*24L,im);
	}

	//çàãðóæàåì êàê ìîíåòêà âðàùàåòñÿ
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


	//çàãðóæàåì ñâèíüþ
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

	//çàãðóæàåì ôîí
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

	//çàãðóæàåì óêàçàòåëü â ìåíþ
	{
		im.Hei=8;
		im.Len=8;
		im.Attribute=SCREEN::TRANSP;
		im.ID=SPRITE_POINTER;
		Sprite.Load("graph\\font.dat", 3*8*8L,im);
	}

	//çàãðóæàåì ìàëåíüêèé êèðïè÷
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



//************* çàãðóçêà çâóêîâ ******************
void SUPERMARIO::LoadSounds(void)
{

	scr.clear();

	Msg(" ÇÀÃÐÓÇÊÀ, ÏÎÆÀËÓÉÑÒÀ, ÏÎÄÎÆÄÈÒÅ ... ",9);
	scr.update();

	CString lame1="lame.exe --decode zastavka.mp3 zastavka.wav";
	CString lame2="lame.exe --decode loop.mp3 loop.wav";
	CString lame3="lame.exe --decode loop_zachita.mp3 loop_zachita.wav";

	SoundDeCoding(lame1, "zastavka.wav");

	scr.clear();
	Msg(" ÇÀÃÐÓÇÊÀ 1 ÇÀÂÅÐØÅÍÀ ", 9);
	scr.update();

	
	SoundDeCoding(lame2, "loop.wav");

	scr.clear();
	Msg(" ÇÀÃÐÓÇÊÀ 2 ÇÀÂÅÐØÅÍÀ ", 9);
	scr.update();

	
	SoundDeCoding(lame3,"loop_zachita.wav");

	scr.clear();
	Msg(" ÇÀÃÐÓÇÊÀ 3 ÇÀÂÅÐØÅÍÀ ", 9);
	scr.update();


	SOUND::MONOSTEREO ms=SOUND::MONOSTEREO::MONO;
	SOUND::BITCOUNT bc=SOUND::BITCOUNT::BIT8;
	int f=11025;
	int dataoffset=46; //ñìåùåíèå äî äàííûõ îò íà÷àëà ôàéëà(ïðîïóñê çàãîëîâêà WAV)
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

	/*zx3267 comment for fast loading
	Sound.load("sound\\zastavka.wav", 44100, 
		SOUND::MONOSTEREO::STEREO, SOUND::BITCOUNT::BIT16, SND_ZASTAVKA, dataoffset);
	
	Sound.load("sound\\loop.wav",44100, SOUND::MONOSTEREO::STEREO, 
		SOUND::BITCOUNT::BIT16,SND_GHOTIC, dataoffset);

	Sound.load("sound\\loop_zachita.wav",44100, SOUND::MONOSTEREO::MONO, 
		SOUND::BITCOUNT::BIT16,SND_GHOTIC_FAST, dataoffset);
	*/

}

//=========== çàãðóçêà ìóçûêè ==============
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

//ðèñóåò ñòðîêó ñîñòîÿíèÿ ñóïåð ìàðèî
void SUPERMARIO::DrawStateline()
{
    int n=0;

    //ïîêàçûâàåì ÷èñëî ñîáðàííûõ êàðò
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
	scr<<"Î×ÊÈ";

	scr.color=15;
	scr.locateXY(1*4-1,4-1);
	scr<<"Î×ÊÈ";

	scr.color=16;
	scr.locateXY(1*4,4+10);
	scr.putNumb(Score,6);

	scr.color=15;
	scr.locateXY(1*4-1,4+10-1);
	scr.putNumb(Score,6);

    //ïîêàçûâàåì ìîùíîñòü ñòðåë, êèíæàëîâ è òîïîðîâ
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

    int k=SPRITE_ARROW;	//ïî óìîë÷àíèþ ñòðåëà
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
	scr << "ÂÐÅÌß";

	scr.color=15;
	scr.locateXY(34*8-1,4-1);
	scr << "ÂÐÅÌß";

	scr.color=16;
	scr.locateXY(35*8,4+10);
	scr << Time;

	scr.color=15;
	scr.locateXY(35*8-1,4+10-1);
	scr << Time;
	
}

//ñîçäàòü î÷êè
//score - ÷èñëî î÷êîâ
//svisor - ññûêà íà ñóïåðâèçîð îáúåêòîâ
// ob - ññëûêíà íà îáû÷íûé îáúåêò. çäåñü èñïîëüçóþòñÿ TimeLive, x,y - êîîðäèíàòû
// ïåðâîé öûôðû. Âñå îñòàëüíûå ïàðàìåòðû êàê îáû÷íî
//èñïîëüçóåì ðåêóðñèþ
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



//===================îáíîâëÿåì êîîðäèíàòû ó ÷óæèõ==================
void SUPERMARIO::ALIEN::RenewXY()
{
	//îáíîâëÿåì êîîðäèíàòó X
	x+=Speedx;
	Speedx+=Acceleratx;
	RenewRect();

	//åñëè ÷óæîé íå çàãàøåí
	if (~Status & DEATH)
	{
		//åñëè íå óäàëîñü ïðîéòè ÷åðåç ïðåãðàäû
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

	//îáíîâëÿåì êîîðäèíàòó Y
	y+=Speedy;
	Speedy+=Acceleraty;
	RenewRect();

//	int collis;	//áûëî ëè ñòîëêíîâåíèå ñ ïîëîì

	if (~Status & DEATH)
	{
		//åñëè íå óäàëîñü ïðîéòè ÷åðåç ïðåãðàäû
		if (!chk_all(*this,0) )
		{
			//ëåòåë âíèç
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

	//åñëè ÷óæîé ìåòðòâûé - íè÷åãî íå äåëàòü
	if ( Status & DEATH ) return;



	//èíà÷å ÷óæîé æèâîé

	//************íå äàåì ÷óæèì ïðîéòè ÷åðåç ïðåãðàäû********
		  if ( ! chk_left(*this,0) )	Speedx=fabs(Speedx);

		  if ( !chk_right(*this,0) )	Speedx=-fabs(Speedx);

		  ANIM ob;
		  ob=*this;
		  ob.x+=24*sign(Speedx);
		ob.RenewRect();


		//åñëè ïîä ÷óæèì íè÷åãî íåò
		if ( chk_down(*this,0) )
		{
			//÷óæîé ïàäàåò
			Acceleraty=0.2;
		  }

	//åñëè âíèçó âïåðåäè ïóñòî íà îäíó êëåòêó
		if ( chk_down(ob,0) )
		{
		//åñëè âíèçó ïóñòî åùå íà íåñêîëüêî êëåòîê
					 if ( scanlevel_down(ob, 0) )
		{
			//ìåíÿåì íàïðàâëåíèå ïî îñè Îõ íà ïðîòèâîïîëîæíîå
			Speedx*=-1;
		}
		//èíà÷å âíèçó íà áëèæàéøèå íåñêîëüêî êëåòîê ÷òî-òî åñòü
		{
			//Acceleraty=0;
		 }


	}
	//èíà÷å âíèçó äàæå íà îäíó êëåòêó ÷òî-òî åñòü
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

//========= 'RenewXY()' - îáíîâëåíèå êîîðäèíàò ó ìàðèî ============2
void SUPERMARIO::MarioRenewXY(MARIO &rk)
{
	//åñëè ìàðèî ìåðòâûé, íàäî ïðîñòî îáíîâëÿòü
	// êîîðäèíàòû áåç âñÿêèõ ïðîâåðîê
	if (rk.Status & MARIO_DEATH)
	{
		rk.PERSON::RenewXY();
		rk.RenewRect();
		return;
	}

	//ìàðèî äîëæåí øåâåëèòü íîãàìè â ñîîòâåñòâèè ñî ñêîðîñòüþ
	//åñëè íå ïîä âîäîé
	if (~LevelStatus & LEVEL_UNDERWATER)
	{
		rk.FrameSpeed=fabs(rk.Speedx)/6.0;
	}
	//èíà÷å ïîä âîäîé
	else
	{
		//øåâåëèò íîãàìè ìåäëåííî
		rk.FrameSpeed=fabs(rk.Speedx)/10.0;
	}

	//ïåðåìåùàåì Mario íà íîâîå ìåñòî ïî îñè Ox
	rk.x+=rk.Speedx;

	//åñëè ìàðèî ïðèëåïëåí íàäî ñìåñòèòü åãî îòíîñèòåëüíî
	//ëèôòà
	if (rk.Status & MARIO_CLAMMY)
	{
		rk.ClammyX+=rk.Speedx;
	}

	//îáíîâëÿåì åãî ìåñòîïîëîæåíèå
	rk.RenewRect();

	//åñëè ïîñëå ïåðåìåùåíèÿ ïî îñè Ox Mario îêàçàëñÿ
	//â êèðïè÷àõ
	if ( ! chk_all(rk,0) )
	{
		//Debug("Can't move on Ox");

		//âîçâðàùàåì åãî íà ìåñòî ïî îñè oX
		rk.x-=rk.Speedx;
		//ClammyX-=Speedx*SPEED_UNIT;

		//îáíóëÿåì ñêîðîñòü
		rk.Speedx=0;

		//îáíóëÿåì óñêîðåíèå
		rk.Acceleratx=0;

		// ÂÀÆÍÎ ! Îáíîâëÿåì åãî ìåñòîïîëîæåíèå
		rk.RenewRect();
	}
	//èíà÷å ïîñëå ïåðåìåùåíèÿ ïî îñè Ox Mario ñâîáîäåí
	else
	{
		//óâåëè÷èâàåì ñêîðîñòü Marioà ïî îñè Ox
		rk.Speedx+=rk.Acceleratx;

		//åñëè èäåò è (íå ëåòèò èëè ïîä âîäîé)
		if (rk.Speedx && (!rk.Speedy || LevelStatus & LEVEL_UNDERWATER))
		{
			//ïóñòü øåâåëèò íîãàìè
			rk.RenewFrame();
		}
	}

	//ïåðåìåùàåì Mario íà íîâîå ìåñòî ïî îñè Oy
	rk.y+=rk.Speedy;
	rk.RenewRect();

	//åñëè ïåðåìåùåíèå ïî îñè oY îêàçàëîñü íåâîçìîæíûì
	//èç-çà êèðïè÷èåé
	if ( ! chk_all(rk,0) )
	{
		//Debug("Can't move on Oy");
		//rk.y-=rk.Speedy;

		//åñëè Mario ëåòåë âíèç
		if (rk.Speedy>0)
		{
			//âîçâðàùàåì åãî íà ìåñòî ïî îñè oy
			rk.y-=int(rk.y)%24;
			//îáíóëÿåì ñêîðîñòü
			rk.Speedy=0;
			//îáíóëÿåì óñêîðåíèå
			rk.Acceleraty=0;
		}
		//Mario ëåòåë ââåðõ
		else
		{
			Sound.play(SND_POP1);
			//î÷åíü òî÷íî öåíòðóåì Mario
			rk.y=rk.y-int(rk.y)%24+24;

			//îáíóëÿåì âñå
			//(à òî áóäåò äðîæàòü)
			rk.Speedy=0;
			rk.Acceleraty=0;
		}
	}
	//èíà÷å íè÷åãî íå ìåøàåò ïàäàòü...
	else
	{
		//óâåëè÷èâàåì ñêîðîñòü Marioà ïî îñè Oy
		rk.Speedy+=rk.Acceleraty;
	}

	//îáíîâëÿåì ñòðóêòóðó Rect
	rk.RenewRect();

	//åñëè ïîä Mario íàõîäèòñÿ ïóñòîòà è íå ïàäàåò
	if ( chk_down(rk,0) && !rk.Acceleraty )
	{
		//âåëèì ìàðèî ïàäàòü
		//?????
		if (LevelStatus & LEVEL_UNDERWATER)
			rk.Acceleraty=0.09;
		else 
			rk.Acceleraty=0.2;
	}

	//rk.Acceleraty=0.2;
	//è íàïîñëåäîê
	//åñëè ìàðèî ëåòèò è íå ïîä âîäîé
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

	//åñëè ïàäàåò ñëèøêîì áûñòðî, îãðàíè÷èâàåì ñêîðîñòü
	//åñëè ïîä âîäîé
	if ( LevelStatus & LEVEL_UNDERWATER)
	{
		if (rk.Speedy>3) rk.Speedy=3;
		//åñëè íà âîçäóõå
		else
		if (rk.Speedy>7) rk.Speedy=7;
	}

	//åñëè ïîä âîäîé, íå äàåì ïîäíÿòüñÿ âûøå âîäû
	if (LevelStatus & LEVEL_UNDERWATER)
	{
		if (rk.y<0) rk.y=0;
	}


	//************************************************
	//************** ñîáèðàåì ðàçíûå ïðèçû************
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

		//ñîáðàëè ìîíåòêó
		if( (Level.ReadXY(x,y)  & LEVEL::MASK) == BRICK::MONEY
		 && !(Level.ReadXY(x,y) & LEVEL::ALIEN)
		)
		{
			Level.WriteXY(x,y,0);

			MoneyCounter++;
			//çà 100 ìîíåòîê äàåì æèçíü
			if (MoneyCounter>=100)
			{
				MoneyCounter=0;
				Lives++;
				Sound.play(SND_NEWLIVE, SOUND::NOSTOP);
			}
			else    Sound.play(SND_APPLE);

			//î÷êè çàáàâíî ïîäïðûãèâàþò
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

		//ñîáðàëè êðèñòàëë
		if( chk_all_transp(rk2,BRICK::CRYSTAL) )
		{
			Level.WriteXY(rk2.Rect.Left,rk2.Rect.Top,0);

			MoneyCounter++;
			//çà 7-îé êðèñòàë äàåì æèçíü
			if (MoneyCounter>=7)
			{
				MoneyCounter=0;
				Lives++;
				Sound.play(SND_NEWLIVE, SOUND::NOSTOP);
			}
			else Sound.play(SND_APPLE);

		}

		//19 may 2008 ñîáðàëè çåëüå
		if( chk_all_transp(rk2,111) )
		{
			Level.WriteXY(rk2.Rect.Left,rk2.Rect.Top,0);
			
			rk.Status|=MARIO_WIZ;
			Sound.play(SND_EXORCISM);
		}


		//ñîáðàëè êàðòó
		if( (Level.ReadXY(int(rk2.x+12),int(rk2.y+12)) & LEVEL::MASK) == BRICK::MAP )
		{
			MapCounter++;

			//ñîáðàëè âñþ êàðòó
			if (MapCounter >= 6)
			{
				OldArms=Arms;	//ñîõðàíÿåì ñòàðîå îðóæèå
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

		 //ñîáèðàåì îðóæèå, åñëè îðóæèå íå ñîïëè
		 if (Arms != SALIVA)
		 {
			//ñîáðàëè ñòðåëó
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

			//ñîáðàëè íîæèê
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

			//ñîáðàëè òîïîðèê
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
	//   ïðîâåðÿåì, óïàë ëè ìàðèî â ïðîïàñòü
	//******************************************
	if (rk.y>Level.MaxY+200+24)
	{
		Sound.play(SND_EXORCISM);
		//äåëàåì ðèêà çàãàøåííûì
		rk.Status|=MARIO_DEATH;
	}


//******************************************
//   ÌÀÐÈÎ âûáèâàåò çíàêè âîïðîñà è êèðïè÷è
//******************************************
{
	int x,y;
	x=rk.Rect.Left+12;
	y=int(rk.y-1);

	//int k=get_up(rc);
	int k=ReadXY(x,y) & LEVEL::MASK;     //êîä êèðïè÷à áåç àòðèáóòîâ
	int k_nomask=Level.ReadXY(x,y);	//êîä ñ óðîâíÿ ñ àòðèáóòàìè

	//åñëè ñâåðõó êèðïè÷ è ìàðèî ëåòèò ââåðõ
	if ( k!=-1 && rk.Speedy<=0.5)
	{
		ANIM br;

		//âû÷èñëÿåì êîîðäèíàòû êèðïè÷à
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
			//íåâèäèìàÿ çâåçäà
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

			//ãðèá, äàþùèé æèçíü
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

			//ðàçáèâàåì êèðïè÷è
			case BRICK::BREAK:
			{

				//÷òîáû íå ïðîëåòàë ââåðõ
				rk.Speedy=0.01;

				//åñëè ìàðèî ìàëåíüêèé êèðïè÷
				//òîëüêî ïîäïðûãèâàåò
				if (~rk.Status & MARIO_BIG)
				{
					br.SpriteIndex=BRICK::BREAK;
					Answer+=br;
					Level.WriteXY(x,y,0);
					rk.Speedy=0.01;
					Sound.play(SND_FINGER);

				}
				//èíà÷å êèðïè÷ ðàçëåòàåòñÿ
				else
				{

					//óâåëè÷èâàåì ÷èñëî î÷êîâ
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


			//ïóñòîé çíàê âîïðîñà
			case BRICK::ANSWER:
			{
				br.SpriteIndex=BRICK::ANSWER;
				break;
			}
			
			//âûáèëè çâåçäà
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

			//ãðèáîê
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

			//êèðïè÷èê, ãäå ìíîãî ìîíåòîê
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
			//êèðïè÷èêè ïîäëåòàþò
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
				//çàïóñêàåì ìîíåòêó
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
//   ???mario ãàñèò ÷óæèõ èëè ÷óæèå ãàñÿò mario???
//***************************************************

//ïðîâåðêà ñòîëêíîâåíèÿ ìàðèî ñ ëèíèåé îãíÿ
for(int j=0;j<FireLine.Counter; j++)
{
ANIM &fr=FireLine[j];
//åñëè îãîíü çàãàñèë ìàðèî
//????????????
if (~rk.Status & MARIO_PROTECTED && CheckUnionRects(fr.Rect,rk.Rect) != FALSE)
{
                                                //ãàñèì ìàðèî
	rk.Speedx=0;
	rk.Speedy=-5;
	rk.Acceleratx=0;
	rk.Acceleraty=0.2;
	rk.FrameSpeed=0;
	rk.Status|=MARIO_DEATH;
	Sound.play(SND_LAUGHT);
}
}

//ïðîâåðêà ÷óæèõ
for(j=0;j<Alien.Counter;j++)
{
PERSON &al=(PERSON&) Alien[j];
//åñëè æèâîé ÷óæîé ñòîëêóíëñÿ ñ ìàðèî
if (!al.Status && CheckUnionRects(al.Rect,rk.Rect) != FALSE)
{
	//åñëè ÷óæîé óïàë íà ìàðèî ñâåðõó
	if ( rk.y-al.y>=0)
	{
		//åñëè ìàðèî çàùèùåííûé
		if (rk.Status & MARIO_PROTECTED)
		{
			//îí çàãàñèë ÷óäîâèùå
			Sound.play(SND_POP1);

			//ãàñèì ÷óäîâèùå
			al.Status=ALIEN::DEATH;
			al.TimeLive=250;
			al.Speedx=rk.Speedx;
			al.Acceleraty=0.2;
			al.Speedy=-4;
			al.FrameSpeed=0;
			al.Movement |= PERSON::FLIP_VERT;
			//âñåãäà àíèìèðîâàòü
			al.AlwaysAnimate=TRUE;
		}

		//èíà÷å ìàðèî íå çàùèùåííûé
		//åñëè íå äðàêîí(îí íå ãàñèò ìàðèî)
		else if (al.FrameFirst != SPRITE_LIZARDSTART)
		{
			//ãàñèì ìàðèî
			rk.Speedx=0;
			rk.Speedy=-5;
			rk.Acceleratx=0;
			rk.Acceleraty=0.2;
			rk.FrameSpeed=0;
			rk.Status|=MARIO_DEATH;
			Sound.play(SND_POP1);
			//Sound.play(SND_LAUGHT);
			//âûäåðæèâàåì ïàóçó
			//scr.pause(DEATHPAUSE);
		}
		break;
	}

	//èíà÷å íàîáîðîò - ìàðèî çàãàñèë ÷óæîãî
	else
	{
		switch(al.FrameFirst)
		{
			case SPRITE_MASHASTART:
			case SPRITE_TURTLESTART:
			case SPRITE_PIGSTART:
			//case SPRITE_LIZARDSTART:

			//ñîçäàåì î÷êè
			ANIM ob;
			ob.x=al.x;
			ob.y=al.y;
			ob.Speedy=-0.7;
			ob.TimeLive=30;
			CreateScore(100,SCORES,ob);
			Supermario.Score+=100;
		}


		rk.Speedy=-2.5;

		//îñòàíàâëèâàåì è ãàñèì ÷óæîãî
		switch(al.FrameFirst)
		{
			case SPRITE_MASHASTART:
			case SPRITE_TURTLESTART:
			//ñâèíüè è ëèçàðäû ãàñÿòñÿ òîëüêî îðóæèåì
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

			//åñëè ìàðèî íàïðûãíóë íà ñâèíêó
			case SPRITE_PIGSTART:
			{
				//î-î÷åíü âûñîêî ïîäïðûãèâàåò
				rk.Speedy=-9;
				break;
			}
			//åñëè ìàðèî íàïðûãíóë íà äðàêîíà
			case SPRITE_LIZARDSTART:
			{
				//î-î÷åíü âûñîêî ïîäïðûãèâàåò
				rk.Speedx=4+0.1*random(50);
				if (random(2)) rk.Speedx*=-1;
				break;
			}

			//åñëè ìàðèî íàïðûãíóë íà ãðèá
			case SPRITE_MASHASTART:
				al.SpriteIndex=SPRITE_MASHASMALL;
				break;

			//åñëè ìàðèî íàïðûãíóë íà ÷åðåïåàõó
			case SPRITE_TURTLESTART:
				al.SpriteIndex=SPRITE_TURTLEHOUSE;
				al.FrameFirst=SPRITE_TURTLEHOUSE;
                al.FrameLast=SPRITE_TURTLEHOUSE;
                al.FrameCurrent=SPRITE_TURTLEHOUSE;
                al.TimeLive=0;
                al.Status=0;
                break;
		
			//åñëè ìàðèî íàïðûãíóë íà ïàíöèðü
			case SPRITE_TURTLEHOUSE:
				//çâó÷èò çâóê
				Sound.play(SND_POP);

				//âðåìÿ æèçíè ïàíöèðÿ óâåëè÷èâàåòñÿ
				al.TimeLive+=500;
				al.Status=0;

				//åñëè ïàíöèðü ñòîèò
				if (al.Speedx==0)
					//çàïóñêàåì åãî
					al.Speedx=4*sign(rk.Speedx+0.01);
				//èíà÷å ïàíöèðü äâèãàåòñÿ
				else
					//îñòàíàâëèâàåì åãî
					al.Speedx=0;
		}

	}
}
}

}

//=============ñòàðòóåì èãðó==============
SUPERMARIO::SUPERMARIO()
{
	ChangeEffect=false;
	GAMEEXIT=FALSE;
}

//ïðîâåðÿåò, ÷òî íàõîäèòñÿ íàä îáúåêòîì(ïðÿìîóãîëüíèêîì)
//what çàäàåò íîìåð êèðïè÷à äëÿ ïðîâåðêè
//mask çàäàåò òå àòðèáóòû, êîòîðûå íåîáõîäèìî îáíóëèòü ïðè ïðîâåðêå
//ÂÍÈÌÀÍÈÅ: ïî óìîë÷àíèþ çàíóëÿþòñÿ âñå àòòðèáóòû
//Âîçâðàò: TRUE - åñëè íàä îáúåêòîì íàõîäèòñÿ òîëüêî ýòîò êèðïè÷
//FALSE - åñëè íàä îáúåêòîì åñòü äðóãèå êèðïè÷èêè
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


//ïðîâåðÿåò, ÷òîáû ãîðÿ÷èé ïðÿìîóãîëüíèê ñïðàéòà íàõîäèëñÿ â
//êèðïè÷àõ what ñ àòðèáóòàìè
//âîçâðàùàåò 1,åñëè ýòî òàê, èëè 0, åñëè íå òàê
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

//ïðîâåðÿåò, íàõîäèòñÿ ëè ñïðàéò â ïóñòîòå èëè â ôîíå
//âîçâðàò 0 - åñëè â ïóñòîòå
// != 0 - åñëè â ÷åì-òî
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


//âîçâðàùàåò 0, åñëè ÷èòàåòñÿ 0 èëè ïðîçðà÷íûé
//èíà÷å âîçâðàùàåòñÿ êîä êèðïè÷à áåç àòðèáóòîâ
int SUPERMARIO::ReadXY(int x,int y)
{
	int k=Level.ReadXY(x,y);
	if ( k & LEVEL::logTRANSP )	return 0;
	return k & LEVEL::MASK;
}

//âîçâðàùàåòñÿ êîä êèðïè÷à áåç àòðèáóòîâ
int SUPERMARIO::ReadXY1(int x,int y)
{	int k=Level.ReadXY(x,y);
	return k & LEVEL::MASK;
}


//ïðîâåðÿåò, íàõîäèòñÿ ëè ñïðàéò â ïóñòîòå
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



//Âîçâðàùàåò -1 åñëè ââåðõó ðàçíûå êèðïè÷è
// Èíà÷å êîä ýòèõ êèðïè÷åé
int SUPERMARIO::get_up(MOVEOBJ & ob)
{
	int x=ob.Rect.Left;
	int y=ob.Rect.Top;
	int x1=ob.Rect.Right;

	if (ReadXY(x,y-1) == ReadXY(x1,y-1) )
		return ReadXY(x,y-1);

	return -1;

}


//==================== ïðîèãðûâàíèå ìåëîäèè =========================
void SUPERMARIO::PlayMusic(int n)
{
/*	CurrentMusic=n;

	char ret[256];
	char buf[2048]="open ";

	strcat(buf,song[n]);
	strcat(buf, " alias snd");

//	mciSendString("stop snd", ret,sizeof(ret),NULL);
	mciSendString("close snd", ret,sizeof(ret),NULL);
    //èãðàåì ìåëîäèþ
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


//========îáúåêòû  Rick ëîâÿòü ïðèçû Prize=============
void SUPERMARIO::prPrizeCatch(ANIM &Rick, ANIM &Prize)
{
//******************************************************
//   ïðèçû íå ïðîõîäÿò ñêâîçü ñòåíêè è ìàðèî ëîâèò ïðèçû
//******************************************************
for(int j=0;j<Rick.Counter;j++)
for(int i=0; i<Prize.Counter;i++)
{
ANIM & al=Prize[i];
ANIM & rk=Rick[j];

//åñëè ïîéìàëè êàêîé-òî ïðèç
if (CheckUnionRects(al.Rect,rk.Rect))
{
	Sound.play(SND_HEALTH, SOUND::NOSTOP);
	int scor;

	switch(al.SpriteIndex)
	{
		//ïîéìàëè ãðèá, äàþùèé æèçíü
		case SPRITE_MUSHROOM_LIVE:
		{
			//óâåëè÷èâàåì ÷èñëî æèçíåé
			Lives++;
			scor=1000;
			Sound.play(SND_RESTART);
			break;
		}

		//ïîéìàëè çâåçäó
		case SPRITE_STAR:
		{
			rk.Status|=MARIO_PROTECTED;
			ProtectedCounter+=1500*10;
			scor=2000;
			//PlayMusic(PROTECTED_MUSIC);
			Sound.play(SND_GHOTIC_FAST);
			break;
		}

		//ïîéìàëè îáû÷íûé ãðèá, äàþùèé ïðåâðàùåíèå â äðàêîíà (Ëèçàðä)
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

		//ïîéìàëè öâåòîê
		//áàã/ôè÷à - åñëè öâåòîê áåðåò
		//íå äèíîçàâðèê - îí òîæå ìîæåò ñòðåëÿò
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

	//ñîçäàåì î÷êè
	{
		ANIM ob;
		ob.x=al.x;
		ob.y=al.y+12;
		ob.Speedy=-0.7;
		ob.TimeLive=40;
		CreateScore(scor,SCORES,ob);
		Score+=scor;
	}

	//óäàëÿåì ïðèç
	{
		Prize.Del(&al);
		i--;
	}

	//ïðîäîëæàåì öèêë
	continue;
}//if (CheckUnionRects(al.Rect,rk.Rect))

		//äàåì âîçìîæíîñòü ïðèçó ïîäíÿòüñÿ áåç ïðåïÿòñâèé
		if (al.TimeLive>3) continue;
		al.TimeLive=0;

		//åñëè âíèçó ïóñòîòà
		if (chk_down(al,0))
		{
			al.Acceleraty=0.2;
		}
		//èíà÷å âíèçó çåìëÿ
		else
		//åñëè ïàäàåò âíèç
		if (al.Speedy>0)
		{
			al.y=int(al.y)/24*24;
			al.Acceleraty=0;

			//ñìîòðÿ êàêîé ïðèç
			//îí áóäåò îòòàëêèâàòüñÿ
			//îò çåìëè ïî ðàçíîìó
			switch(al.SpriteIndex)
			{
				//çâåçäà ìîùíî
				case SPRITE_STAR:
				al.Speedy=-0.8*abs(al.Speedy);
				break;

				//ãðèá ñëàáî
				case SPRITE_MUSHROOM_BIG:
				al.Speedy=-0.4*abs(al.Speedy);
				break;
				
				default:
				al.Speedy=-0.4*abs(al.Speedy);
				break;
				
			}
			//ñëèøêîì íèçêî íå äîëæåí ïðûãàòü
			if (al.Speedy>-0.5) al.Speedy=0;
		}

		ANIM al2=al;
		al2.Rect.Bottom-=4;
		if (!chk_left(al2,0)) al.Speedx=abs(al.Speedx);
		if (!chk_right(al2,0)) al.Speedx=-abs(al.Speedx);
}
}

// ýôôåêò ïîñèíåíèÿ ýêðàíà
void SUPERMARIO::ColorEffect()
{
	//ýôôåêò - ÷åðíûå òî÷êè ðàñòâîðÿþò èçîáðàæåíèå
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

	
	int N=4;	//÷èñëî ýëåìåíòîâ ìåíþ
	char far * txt[]=
	{
		 "1. ÎÒÊËÞ×ÅÍÈÅ ÇÂÓÊÀ ",
		 "2. ÎÒÊËÞ×ÅÍÈÅ ÌÓÇÛÊÈ ",
		 "3. ÏÅÐÅÍÀÇÍÀ×ÅÍÈÅ ÊËÀÂÈØ",
		 "4. ÂÛÕÎÄ Â ÃËÀÂÍÎÅ ÌÅÍÞ"
	 };

	int TitleNew=-1;	//ò.ê. ïåðåä èñïîëüçîâàíèåì TitleNew óâåëè÷èâàåòñÿ
	int nm=0;
	int py=y;
	double levelx=0,speed_levelx=2.5;

   while ( !Keyb[KEY_ENTER] )
   {
	SCREEN &Screen=scr;

	//**** ïîñòðîåíèå èçîáðàæåíèÿ *****
	Screen.setcolor(15);
	Screen.setbkcolor(0);
	Screen.rectangle(0,0,320,200,0);

	//âûâîä ñòðîê ìåíþ íà ýêðàí
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

		//âûâîä óêàçàòåëÿ
		int px=20;
		Sprite.Show(int(x1-20),int(y1)-1,SPRITE_POINTER);

	}

	//åñëè íàæàëè êëàâèøó ÂÂÅÐÕ
	if ( Keyb[KEY_UP] && py>y )
	{
		Keyb.Set(KEY_UP,0);

		py-=2;
		nm--;
		t=0;
	}

	//åñëè íàæàëè êëàâèøó ÂÍÈÇ
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
	scr.center(15, "Ñîëäàò Ìàðèî");
	
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

	//ïåðåíàñòðàèâàåì ñ÷åò÷èê ñëó÷àéíûõ ÷èñåë
	//random();

	for(UINT i=0; i<GetTickCount()%100; i++) rand();

	Level.Load(rand()%10);
	
	Timer.Restart(60);

	#define GAMENAME "SUPER JACKS"

	BIGSTRING s1(&BigFont,GAMENAME);

	ANIM Title(&BigFont);
	PERSON Mario(&Sprite);

	//îïðåäåëÿåì ãðàíèöû ïåðåìåùåíèÿ
	{
		MOVEOBJ::Lim.Left=-24;
		MOVEOBJ::Lim.Right=324;
		MOVEOBJ::Lim.Bottom=224;
		MOVEOBJ::Lim.Top=-24;
		MOVEOBJ::WindowX=0;
		MOVEOBJ::WindowY=0;
	}

	int N=7;	//÷èñëî ýëåìåíòîâ ìåíþ
	char far * txt[]=
	{
		 "1. ÎÄÈÍ ÈÃÐÎÊ",
		 "2. ÄÂÀ ÈÃÐÎÊÀ",
		 "3. ÒÐÈ ÈÃÐÎÊÀ",
		 "4. ÊÎÍÔÈÃÓÐÀÖÈß",
		 "5. ÐÅÄÀÊÒÎÐ ÓÐÎÂÍÅÉ",
		 "6. ÐÅÄÀÊÒÎÐ ÑÏÐÀÉÒÎÂ",
		 "7. ÂÛÕÎÄ"
		 
	 };

	int TitleNew=-1;	//ò.ê. ïåðåä èñïîëüçîâàíèåì TitleNew óâåëè÷èâàåòñÿ
	int nm=0;
	double levelx=0,speed_levelx=2.5;

	while ( !Keyb[KEY_ENTER] )
	{
	SCREEN &Screen=scr;

	//**** ïîñòðîåíèå èçîáðàæåíèÿ *****
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

	//âûâîä çàñòàâêè
	//zast.Show(90+rand()%3,0,SPRITE_ZAST0);

	//âûâîä ñòðîê ìåíþ íà ýêðàí
	for (int k=0; k<N; k++)
	{
		const int HEI_STRING=20;
		double x1,y1;
		//x1=(320-8*strlen(txt[k]))/2;
		x1=90;
		y1=k*HEI_STRING+40; //ó êîîðäèíàòû âûâîäà ìåíþ

		if (k == nm)
		{
			scr.rectangle(int(x1),int(y1),8*strlen(txt[k]),HEI_STRING-5,3);
		}

		//STRING str(&BigFont,txt[k]);
		//str.Show(x1,y1);
		scr.locateXY(int(x1),int(y1));  
		scr.putText(txt[k]);

		//âûâîä óêàçàòåëÿ
		int px=20;
		Sprite.Show(int(x1-20),int(y1)-1,SPRITE_POINTER);

	}

	//íàæàëè ââåðõ
	if ( Keyb[KEY_UP])
	{
		nm--;
		if (nm==-1) 
		{
			nm=N-1;
		}
		Keyb.Set(KEY_UP,0);
	}

	//åñëè íàæàëè êëàâèøó ÂÍÈÇ
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

    //åñëè âñå íàäïèñè ïðîøëè, ïîêàçûâàòü íàäïèñü 'SUPER MARIO'
	if (TitleNew == 4) s1.Show(20,35);

	while (Timer.Counter <2);
	Timer.Counter=0;

	scr.color=15;
	scr.center(15, "Ñîëäàò Ìàðèî");
	
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
