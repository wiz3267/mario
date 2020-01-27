//Level.cpp

#include "stdafx.h"
#include "total.h"

#include <fstream.h>

#include "SpriteEditor.h"

static int LevelModify=0;

//преобразует число num в строку символов,
//num - число
//width - ширина преобразования
//dest - адрес строки, куда будет происходить вывод
void LEVEL::ConvertNumber(int num, char width, char * dest)
{
	if (width>10 || width<1) Debug("ConvertNumber - width incorrect");
	dest[0]=9;
	char * str = new char[width];
	for (int i=0; i<width; i++)
	{
		str[i]=num % 10;
		num/=10;
	}
	int k;
	for (i=width-1,k=0; k<width; k++,i--)
	{
		dest[k]=str[i]+'0';
	}
	delete str;
}

static	int 
		x=0,y=0,		//координаты показа уровня
		CurrentSprite=6,//номер текущего спрайта
		xcur=0,ycur=0,	//координаты синего курсора
		LOOP=TRUE;		//если LOOP=FALSE, то выход из редактора

//редактор уровня LevelNumber
int LEVEL::Editor(int LevelNumber)
{

	int bkcolor=scr.bkcolor;
	int textcolor=scr.color;

	LOOP=TRUE;

	int ShowMap=1;		//показывать карту

	int *SaveBlock=0;	//хранит блок, запомненный <CTRL>+<INS>
	unsigned int BlockLen, BlockHei;

	
	x=this->x;
	y=this->y;

	Load(LevelNumber);

	//создаем мышь
	//MOUSE Mouse(&scr);

	//стартуем тимер
	//Timer.Restart(19);

	//цикл Редактора уровней
	while (LOOP)
	{
		//рисуем фон
		scr.rectangle(0,0,320,200,BackgroundColor);


		//рисуем уровень
		this->x=x;
		this->y=y;
		Show(x,y, SHOW_DEBUG | SHOW_BACKGROUND | SHOW_FOREGROUND);

		//рисуем полоски
		{
			int a;
			if (x/24 % 2 ) a=24;
			else a=0;
			for(int x=a; x<320; x+=48)
			{
				scr.linedown(x,0,200, 15);
			}

			for(int y=0; y<200; y+=24)
			{
				scr.lineright(0,y,320, 7);
			}
		}

		//устанавливаем цвет текста и фона
		{
			scr.setcolor(15);
			scr.setbkcolor(16);
		}

		//рисуем синий курсор
		//if (Timer.GetTotalCounter()%40>1)
        {
			scr.rectangle(xcur*BoxLen+3, ycur*BoxHei+3,
						BoxLen-6, BoxHei-6, 9);
        }

		//выводим текущий спрайт
		{
			scr.setbkcolor(16);
			scr.rectangle(320-BoxLen-4-1,200-BoxLen-4-1,BoxLen+4,BoxLen+4,0);
			if (CurrentSprite)
			{
				spr->Show(320-BoxLen-2-1,200-BoxLen-2-1, CurrentSprite);
			}
		}

		//показываем самую важную информацию
		{
            //выводим номер текущего спрайта
			scr << cur(34,24) << CurrentSprite;
			//показываем локальные координаты
			scr << cur(0,24) << "CUR " << xcur << ':' << ycur;
			//показываем координаты окна
			scr << cur(9,24)<< "WIN "<< x/BoxLen << ':' << y/BoxHei;
			//показываем абсолютные координаты
			scr << cur(19,24)<< "GLOBAL  "<< (x/BoxLen + xcur) << ':' << (y/BoxHei+ycur);

			//показываем номер уровня
   	        scr << cur(0,23) << "LEVEL " << LevelNumber;
			//выводим размеры уровня
   	        scr << cur(9,23) << Len << 'x' << Hei;

			//показываем место старта mario
            scr.locateXY(MarioX-x,MarioY-y);
            scr<<"Mario";

			//показываем время
			scr << cur(17,23) << "TIME=" << Time;

            if (BackgroundColor & FLAG_UNDERWATER)
			scr << cur(26,23) << "ПОДВОДОЙ";
		}


		//рисуем карту уровня (уровень в уменьшенном масштабе)
        if (ShowMap & 1)
        {
            for(int y=0;y<Hei; y++)
			for(int x=0; x<Len; x++)
            {
                int a=Read(x,y);
				if (a) a=8+a%8;
                    
                scr.putpixel(x,y,a);

				if (!a && x<this->x/24+13 && x>=this->x/24
                && y>=this->y/24 && y<this->y/24+8)
				{
					scr.putpixel(x,y,15);
				}
            }
       }

         // *** ОБРАБАТЫВАЕМ НАЖАТИЯ КЛАВИШ *****

		//включаем выключаем карту
		if ( Keyb[KEY_TAB] )
		{
			//осуществляем повтор
			Keyb.Set(KEY_TAB,0);

			ShowMap++;
		}

		//движение окна с клавиатуры
		if ( Keyb[KEY_RIGHTCTRL] || Keyb[KEY_LEFTCTRL] )
		{
			if ( Keyb[KEY_LEFT]  && x>=BoxLen) x-=BoxLen;
			if ( Keyb[KEY_RIGHT] && x<BoxLen*Len-320) x+=BoxLen;
			if ( Keyb[KEY_UP]    && y>=BoxHei) y-=BoxHei;
			if ( Keyb[KEY_DOWN]  && y<BoxHei*Hei-200)  y+=BoxHei;
		}


		//движение окна с помощью мыши
		/*{
			if (Mouse.x>318 && x<BoxLen*Len-320)
				x+=BoxLen;
			if (Mouse.x<3 && x>BoxLen)
				x-=BoxLen;
			if (Mouse.y>198 && y<BoxHei*Hei-200)
				y+=BoxHei;
			if (Mouse.y<3 && y>BoxHei)
				y-=BoxHei;
		}*/


		//run Sprite Editor from Level Editor
		if (Keyb[KEY_S] && Keyb[KEY_E])
		{
			SPRITEEDITOR SprEditor;
			SprEditor.Editor(spr,CurrentSprite);
			Supermario.LoadSprites();	
		}

		//вывод таблицы спрайтов (S - SELECT)
		if (Keyb[KEY_S])
		{
			int current=CurrentSprite;

			int timecounter=0;
			while(1)
			{
				scr.clear();

				int nspr=1;

				if (Keyb[KEY_ENTER]) break;

				if (current>13*6) nspr=13*4;

				for(int ys=0;ys<10;ys++)
				{
					for(int xs=0;xs<13;xs++)
					{
						if (spr->find(nspr))
						spr->Show(xs*24,ys*24, nspr);
						if (current==nspr)
						{
							//на спрайте рисуем белый квадрат
							if ((timecounter%10) <5)
							{
								scr.rectangle(xs*24,ys*24,24,24, 15);							
								scr.locateXY(xs*24, ys*24);
								scr<<nspr;
							}
						}

						nspr++;
						if (nspr==112) break;
					}
					if (nspr==112) break;
				}
				scr.update();
				scr.pause(10);

				timecounter++;
				if (Keyb[KEY_DOWN])
				{
					current+=13;
					if (spr->find(current)==-1) current-=13;
					else timecounter=0;
				}
				if (Keyb[KEY_UP])
				{
					current-=13;
					if (spr->find(current)==-1) current+=13;
					else timecounter=0;
				}
				if (Keyb[KEY_LEFT] && current>0) current--,timecounter=0;
				if (Keyb[KEY_RIGHT] && current<112) current++,timecounter=0;
				if (Keyb[KEY_ENTER]) {CurrentSprite=current;break;}
			}	

			Keyb.clear();
		}

		

		//управление курсором
		if ( ! Keyb[KEY_RIGHTCTRL] && ! Keyb[KEY_LEFTCTRL] )
		{
 		    #define PS 4
			if ( Keyb[KEY_LEFT] && xcur>=1 ) { xcur--;scr.pause(PS); }
			if ( Keyb[KEY_RIGHT] && xcur<320/BoxLen-1 ) { xcur++;scr.pause(PS); }
			if ( Keyb[KEY_UP] && ycur>=1 ) { ycur--;scr.pause(PS); }
			if ( Keyb[KEY_DOWN] && ycur<200/BoxHei-1 ) { ycur++;scr.pause(PS); }
		}

                //медленное перемещение
        if ( Keyb[KEY_LEFTSHIFT] )
		{
			Keyb^KEY_UP;
			Keyb^KEY_DOWN;
			Keyb^KEY_LEFT;
			Keyb^KEY_RIGHT;
		}


		if (Keyb[KEY_F1] && Keyb[KEY_RIGHTCTRL])
		{
			char help[]=
			"{0,0, ALWAYS}, 0\n"
			"{0,17, CHGLEVEL}, 1\n"
			"{0,5, ALWAYS}, 2\n"
			"{0,15, ALWAYS}, 3\n"
			"{0,3, ALWAYS}, 4\n"
			"{0,2, ALLMAP}, 5\n"
			"{0,16, ALWAYS}, 6\n"
			"{0,6, ALWAYS}, 7\n"
			"{10,15,CHGLEVEL}, 8\n"
			"{10,15,BOSSLIVE | CHGLEVEL}, 9\n"
			"{1,17, BOSSDEATH | CHGLEVEL} 10\n";

			scr.clear();
			scr<<cur(0,0);
			scr.color=4;
			scr<<"Таблица перемещний\n";
			scr.color=7;
			scr<<help;
			scr.update();
			Keyb.ReadScan();
		}

		if (Keyb[KEY_F1] && Keyb[KEY_LEFTCTRL])
		{
			char help1[]=
			"20 свинья\n21 динозаврик\n22 ходячий грибок\n"
			"23 черепашка\n24 зубастый цветок\n"
			"25 крутящаяся огненная линия\n"
			"26 ежик\n27 туземец\n29 мостик влево-вправо\n"
			"30 лифт\n"
			"31 мостик вверх-вниз (много )\n"
			"32 мостик вверх-вниз (немного )\n"
			"33 орел влево - вправо\n"
			"34 водяной мостик вправо-влево на 6\n"
			"35 водяной мостик влево-вправо на 6\n"
			"36 мостик вверх-вниз (на 4 с паузой)\n"
			"37 мостик (движение сложное)\n"
			"38 мостик (движение сложное)\n"
			"39 мостик (движение сложное)\n"
			"40 первая голова\n41 космонавт\n"
			"42 мостик на 2 уровне( начало )\n";
			char help2[]=
			"43 мостик вниз-вверх на 9\n"
			"44 мостик вниз-вверх на 5 с паузой\n"
			"45 мостик вверх-вниз на 4 c паузой\n"
			"46 мостик вверх-вниз на 2 с паузой\n"
			"47 мостик вниз-вверх на 6 с паузой\n"
			"48 водный мостик влево-вправо на 16\n"
			"49 скелет, просто за него дают очки\n"
			"50 скелет открывает дверь\n"
			"51 птичка\n52 рыбка\n53 улитка\n"
			"54 акула (босс)\n"
			"55 следующий уровень(автомат)\n"
			"56 невидимая жизнь\n";

			scr.clear();
			scr<<cur(0,0);
			scr.color=4;
			scr<<"Коды чужих\n";
			scr.color=15;
			scr<<help1;
			scr.update();
			Keyb.ReadScan();
			scr.clear();
			scr<<cur(0,0);
			scr.color=4;
			scr<<"Коды чужих\n";
			scr.color=15;

			scr<<help2;
			scr.update();
			Keyb.ReadScan();
		}

		// <F1> - помощь
		if ( Keyb[KEY_F1] )
		{
			char help[]=
			"<F1>, <LEFTCTRL+F1> ПОМОЩЬ\n"
			"<F2> сохранить уровень\n"
			"<F3> загрузить уровень\n"
			"<TAB> показать/скрыть карту\n"
			"<CTRL>+<N> новый уровень\n"
			"<CTRL>+<T> установить время игры\n"
			"<CTRL>+<B> цвет заднего фона\n"
			"<CTRL>+<L> загрузить уровень N\n"
			"<CTRL>+<M> таблица перемещений\n"
			"<B> атрибут (фон)\n"
			"<F> атрибут (на передний план)\n"
			"<C> атрибут (обрушающийся под марио)\n"
			"<D> атрибут (разрущающийся оружием)\n"
			"<A> атрибут (чужой)\n"
			"<T> атрибут (фон просвечивает)\n"
            "<U> подводный уровень (марио плавает)\n"
			"<PAGE UP> следующий уровень\n"
			"<PAGE DOWN> предыдущий уровень\n"
			"<+><1> <-><2> выбор кирпичиков\n"
			"<ENTER> получить код кирпичка\n"
			"<SPACE> рисовать\n"
			"<M> позиция Mario\n"
			"<CTRL>+<INS> копировать\n"
			"<SHIFT>+<INS> вставить\n"
			"<DELETE> удалить \n";

			scr.clear();
			scr<<cur(0,0);
			scr<<help;
			scr.update();
			Keyb.ReadScan();

			char help2[]=
			"<SHIFT> удерживайте чтобы перемещаться\nмедленно\n"
			"<E>+<S> редактор спрайтов(Sprite Editor)\n"
			"<S> выбор спрайта (Select)\n"
			;
			
			scr.clear();
			scr<<cur(0,0);
			scr<<help2;
			scr.update();
			Keyb.ReadScan();
			
		}

		// <LEFTCTRL> + <INSERT> запомнить блок кирпича
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_INSERT])
		{
			scr.bkcolor=9;
			Msg(" Ширина =     ",9);
			BlockLen=scr.InputNumber(3);
			Msg(" Высота =     ",9);
			BlockHei=scr.InputNumber(3);

			if ( !(BlockLen*BlockHei) || (long(BlockLen)*BlockHei)>10*1024*1024)
			{
				Debug(" Блок слишком велик! ");
			}
			else
			{
				//если блок уже есть, удалем его
				if ( SaveBlock ) delete SaveBlock;

				//выделяем память под блок
				if( !(SaveBlock = new int[BlockLen*BlockHei]) )
				{
					Debug(" Нехватает памяти ");
				}
				//иначе копируем блок с экрана в память
				else
				{
					for(unsigned y=0; y<BlockHei; y++)
					for(unsigned x=0; x<BlockLen; x++)
					SaveBlock[y*BlockLen+x]=
					Read(this->x/24+xcur+x,this->y/24+ycur+y);
				}
			}
		}

		//вставка блока
        if ( Keyb[KEY_LEFTSHIFT] && Keyb[KEY_INSERT])
        {
            //если блок ранее был выделен
            if ( SaveBlock )
            {
                for(UINT y=0; y<BlockHei; y++)
				for(UINT x=0; x<BlockLen; x++)
				{
					Write(this->x/24+xcur+x,this->y/24+ycur+y,
					SaveBlock[y*BlockLen+x]);
				}

			}
        }

		// <ENTER> узнать код кирпича
		if ( Keyb[KEY_ENTER] )
		{
			CurrentSprite=Read(x/BoxLen+xcur,y/BoxHei+ycur) & MASK;
		}

		// <SPACE> рисуем
		if ( Keyb[KEY_SPACE] )
		{
			//пишем в массив
			Write(x/BoxLen+xcur,  y/BoxHei+ycur, CurrentSprite);
		}

		// <B> (Background) установить признак фона для кирпича
		if ( Keyb[KEY_B] && !Keyb[KEY_LEFTCTRL] )
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=BACKGROUND;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_B;
		}

		// <D> (Destroyed) установить признак разрушаемости кирпичика
		if ( Keyb[KEY_D])
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=DESTROYED;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_D;
		}

		// <C> (Collapse) установить признак обрушаемости
		// кирпичика под ногами
		if ( Keyb[KEY_C])
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=COLLAPSE;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_C;
		}


		// <T> (Transparant) установить наличия прозрачных пикселей в кирпиче
		if ( Keyb[KEY_T] && !Keyb[KEY_LEFTCTRL])
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=TRANSPARENTPIXELS;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_T;
		}


		// <F> (Foreground) установить признак 'кирпич перед спрайтом'
		if ( Keyb[KEY_F] )
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=FOREGROUND;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_F;
		}

		// <M> (Mario) установить место старта игры
		if ( Keyb[KEY_M] )
		{
			MarioX=x+xcur*24;
			MarioY=y+ycur*24;
		}

		// <A> (Alien) установить признак чужого
		if ( Keyb[KEY_A] )
		{
			int m=ReadXY(x+xcur*24, y+ycur*24);
			m^=ALIEN;
			WriteXY(x+xcur*24,y+ycur*24,m);
			Keyb^KEY_A;
		}

		// <DELETE> стираем элемент
		if ( Keyb[KEY_DELETE] )
		{
			//пишем в массив
			Write(x/BoxLen+xcur, y/BoxLen+ycur,0);
		}

		// <U> - Underwater - подводный уровень
		if (Keyb[KEY_U])
		{
			BackgroundColor^=FLAG_UNDERWATER;
			Keyb^KEY_U;
		}

		// рисуем мышью
		/*if ( Mouse.Buttons & MOUSE::BUTTON_LEFT)
		{
			//если надо позиционировать окно с помощью мыши
			if (ShowMap & 1 && Mouse.x<Len && Mouse.y<Hei)
			{
				if (Mouse.x>Len-12) Mouse.x=Len-12;
				if (Mouse.y>Hei-7) Mouse.y=Hei-7;
				x=Mouse.x*24;
				y=Mouse.y*24;
			}
			else
			{
				Write(x/BoxLen+Mouse.x/BoxLen, y/BoxHei+Mouse.y/BoxHei, CurrentSprite);
			}
		}*/

		//стираем с помощью мыши
		if ( Mouse.Buttons & MOUSE::BUTTON_RIGHT)
		{
			Write(x/BoxLen+Mouse.x/BoxLen, y/BoxHei+Mouse.y/BoxHei, 0);
		}
		

		// <F3> загрузка уровня
		if ( Keyb[KEY_F3] )
		{
			Msg(" Перезагрузить уровень ? (Y,N) ", 9);
			if (Keyb.ReadScan() == KEY_Y)
			{

				Load(LevelNumber);
				x=this->x;
				y=this->y;
			}
			else
			{
				Msg("      УРОВЕНЬ НЕ ЗАГРУЖЕН !       ");
				Keyb.ReadScan();
			}

		}

		// <F2> запись уровня
		if ( Keyb[KEY_F2] )
		{
			Msg(" Сохранить уровень ?! (Y,N)",2);
			if (Keyb.ReadScan() == KEY_Y)
			{
				Msg(" ИЗМЕНЕНИЯ ЗАПИСАНЫ В ФАЙЛ ",9);
				Save(LevelNumber);
				Keyb.ReadScan();
//				Debug("OK");
			}
			else
			{
				Msg(" ВНИМАНИЕ, УРОВЕНЬ НЕ СОХРАНЕН! ",10);
				Keyb.ReadScan();
//				Debug("OK");

			}
		}

		//<PAGE UP> смена уровня
		if ( Keyb[KEY_PAGEUP] && LevelNumber<50)
		{
			if (LevelModify) {Msg(" Уровень изменен! "); Keyb.ReadScan();}
			else
			{

					LevelNumber++;
					Load(LevelNumber);
					x=this->x;
					y=this->y;
			}

			scr.pause(15);
		}

		//<CTRL>+<L> загрузить уровень (номер вводится с клавиатуры)
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_L] )
		{
			scr.bkcolor=9;
			Msg(" Загрузить уровень =      ",9);
			LevelNumber=WORD(scr.InputNumber(4));
			Load(LevelNumber);
		}

		//<CTRL>+<T> установить время
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_T] )
		{
			scr.bkcolor=9;
			Msg(" Time =      ",9);
			Time=WORD(scr.InputNumber(4));
			LevelModify=1;
		}

		//<ALT>+<B> установить цвет заднего плана
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_B] )
		{
			int t=0;
			scr.bkcolor=2;
			do
			{
				Msg(" BACKGROUNDCOLOR =     ",2);
				t=scr.InputNumber(3);
			}	while (t>255);
			BackgroundColor=t;
			LevelModify=1;
		}

		//<PAGE DOWN> смена уровня
		if ( Keyb[KEY_PAGEDOWN] && LevelNumber>0 )
		{
			if (LevelModify) {Msg(" Уровень изменен! "); Keyb.ReadScan();}
			else
			{

					LevelNumber--;
						Load(LevelNumber);
					x=this->x;
					y=this->y;
			}

			scr.pause(15);
		}

		// <+><1> выбор спрайта
		if ( Keyb[KEY_PADADD] || Keyb[KEY_1] )//&& CurrentSprite<SUPERMARIO::NUMBER_LEVELBOX)
		{	
			//scr.pause(30);
			CurrentSprite++;
			if (spr->find(CurrentSprite) == -1)
			{
				CurrentSprite--;
			}
			Keyb^KEY_PADADD;
			Keyb^KEY_1;


		}

		// <-><2> выбор спрайта
		if ( (Keyb[KEY_PADSUB] || Keyb[KEY_2]) && CurrentSprite>1)
		{
			//scr.pause(30);
			CurrentSprite--;
			if (spr->find(CurrentSprite) == -1)
			{
				CurrentSprite++;
			}
			Keyb^KEY_PADSUB;
			Keyb^KEY_2;

		}

		// <ESC> выход из редактора
		if ( Keyb[KEY_ESC] )
		{
			//если уровень был изменен
			if (LevelModify)
			{
				Msg(" ВНИМАНИЕ! ФАЙЛ НЕ СОХРАНЕН !");
				scr.clear();
				Keyb.ReadScan();
			}
			else
			{
				scr.clear(0);
				LOOP=FALSE;
			}
		}

		// <ALT>+<N> создание нового уровня
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_N] )
		{
  			scr.bkcolor=9;
			Msg(" Ширина =     ",9);
			int len=scr.InputNumber(3);
			Msg(" Высота =     ",9);
			int hei=scr.InputNumber(3);

			New(len,hei);
			x=this->x;
			y=this->y;
		}

		//показываем таблицу перемещений
		if ( Keyb[KEY_LEFTCTRL] && Keyb[KEY_M])
		{
			scr.clear();

			scr.setcolor(12);

			scr.center(0,"ТАБЛИЦА ПЕРЕМЕЩЕНИЙ");

			scr.setcolor(13);
			scr<<cur(0,1)<<"КОД";
			scr<<cur(6,1)<<"КУДА";
			scr.setcolor(15);
			for(int i=0; i<SUPERMARIO::SHUFFLE_COUNT; i++)
			{
				SUPERMARIO::SHUFFLE &shuffle=Supermario.Shuffle[i];
				scr<<cur(0,i+2)<<i;
				scr<<cur(3,i+2)<<"-> "<<shuffle.BoxCode<<" ";

				//ALWAYS	=	0x00,	//перемещаться можно всегда
				//ALLMAP	=	0x01,	//перемещаться можно только если собрана вся карта	
				//BOSSLIVE	=	0x02,	//перемещаться можно если жив босс(голова)
				//BOSSDEATH	=	0x04,	//перемещаться можно если босс мертвый
				//CHGLEVEL	=	0x08	//идет смена файла
				int Status=shuffle.Status;

				if (Status & shuffle.ALLMAP)	scr<<"ВСЯКАРТА ";
				if (Status & shuffle.BOSSLIVE)	scr<<"БОСЖИВ ";
				if (Status & shuffle.BOSSDEATH) scr<<"БОСМЕРТВ ";
				if (Status & shuffle.CHGLEVEL) 
				{
					scr<<"НАУРОВЕНЬ["<<Supermario.Shuffle[i].LevelNumber<<"]";
				}
				if (Status & shuffle.NEXTLEVEL) 
				{
					scr<<"СЛЕДУРОВЕНЬ";
				}

			}

			scr.update();
			Keyb.ReadScan();
		}

		//рисуем курсор мыши
		//Mouse.Draw();

		scr.locateXY(Mouse.x,Mouse.y);
		scr.putpixel();

		//синхронизация по таймеру
		while (Timer.Counter<1);
		Timer.Counter=0;

		//обновление экрана
		scr.update();
		
		Sleep(1);
	}

	//удаляем блок
	if (SaveBlock) delete SaveBlock;

	scr.bkcolor=bkcolor;
	scr.color=textcolor;

	return LevelNumber;
}

//====================== конструктор ==================
//Sprite - адрес объекта супервизора спрайтов, используемых
//для рисования

LEVEL::LEVEL(int len, int hei,SPRITE *spr1)
{
		SIGNATURE=0xF0E0D0C0L;
        sizeofLevel=sizeof(*this);

	//запоминаем адреc объекта-экрана
	spr=spr1;

	//длина уровня
	Len=len;
	Hei=hei;

	//размеры одной коробочки(по умолчанию)
	BoxLen=24;
	BoxHei=24;

	//поскольку New удаляет то, что было по адресу Data
	Data=NULL;
	New(len,hei);
}
//=========================== деструктор ============================
LEVEL::~LEVEL()
{
	//удаляем уровень
	delete [] Data;
	Data=NULL;
}



//создаем новый уровень
void LEVEL::New(int len,int hei)
{
	delete Data;	//удаляем прежний уровень

	Data=new WORD[len*hei];	//выделяем память под новый уровень
	if (!Data)
	{
		Fatal("LEVEL::New Can't allocate memory!");
		len=1;
		hei=1;
	}

	x=0;
	y=0;
	Len=len;
	Hei=hei;
	MaxX=(Len-14)*24+(24-8);
	MaxY=(Hei-9)*24+(24-8);

	//очистка уровня
	for (int i=0; i<len*hei; i++)
		Data[i]=0;

}

//========== 'Save' - сохранение уровня ===================
int LEVEL::Save(int LevelNumber)
{
	MaxX=(Len-14)*24+(24-8);
	MaxY=(Hei-9)*24+(24-8);

	//открытие файла
	//char * name="levels\\level???.dat";
	char name[]="levels\\level???.dat";
	ConvertNumber(LevelNumber, 3, name+12);
	

	ofstream ofl(name, ios::binary);

	if ( !ofl ) {
		Debug("LEVEL::SAVE - can't create file");
		return 0;
	}
	//пишем в файл
	//пишем сам объект

	ofl.write((char*)&SIGNATURE,4);
	ofl.write((char*)&sizeofLevel,2);
	ofl.write((char*)&spr,4);
	ofl.write((char*)&x,2);
	ofl.write((char*)&y,2);
	ofl.write((char*)&MaxX,2);
	ofl.write((char*)&MaxY,2);
	ofl.write((char*)&Len,2);
	ofl.write((char*)&Hei,2);
	ofl.write((char*)&BoxLen,2);
	ofl.write((char*)&BoxHei,2);
	ofl.write((char*)Data,4);
	ofl.write((char*)&MarioX,2);
	ofl.write((char*)&MarioY,2);
	ofl.write((char*)&BackgroundColor,2);
	ofl.write((char*)&Time,2);

	
	ofl.write( (char*)Data, Len*Hei*2);

	ofl.close();
	LevelModify=0;
	return 1;
}

//======== 'Load' - загрузка уровня =================
int LEVEL::Load(int LevelNumber)
{
	char name[]="levels\\level???.dat";
	ConvertNumber(LevelNumber, 3, name+12);

	//char * name="levels\\level000.dat";


	//открытие файла
	CFile ifl;
	
	
	//если не смогли открыть файл - создаем пустой уровень
	if ( !ifl.Open(name,ifl.modeRead) )
	{
                Debug("LEVEL::LOAD file not exist");
       			New(14,10);
				return 1;
	}



	//удаляем данные старого уровня
	delete Data;
	Data=NULL;

	//читаем из файла:

        //запоминаем то, что не может быть считано правильно
	SPRITE *spr1=spr;


	//читаем сигнатуру
	ifl.Read( &SIGNATURE, sizeof(SIGNATURE) );

        //анализируем сигнатуру:
	//если она не равна f0e0d0c0
        if (SIGNATURE != 0xF0E0D0C0L)
        {
                Debug("LEVEL::Load - bad file format");
				return 0;
        }
        else
        {
        	//считываем размер объекта
                ifl.Read( &sizeofLevel, sizeof(sizeofLevel) );

                /*if (sizeofLevel> sizeof(*this) )
                {
                        Debug("LEVEL::Load - sizeofLevel too big !)");
						return 0;
				}

                if ( sizeofLevel<sizeof(*this) )
                {
                        Debug("LEVEL::Load - sizeofLevel too small !)");
                        return 0;
                }*/

                //считываем объект
                //ifl.seekg(0);
                //ifl.read( (char*)this, sizeofLevel);

                //if (sizeofLevel<sizeof(*this))
	              // 	sizeofLevel=sizeof(*this);
				ifl.Read((char*)&spr, 4);
				ifl.Read((char*)&x, 2);
				ifl.Read((char*)&y, 2);

				ifl.Read((char*)&MaxX, 2);
				ifl.Read((char*)&MaxY, 2);

				ifl.Read((char*)&Len, 2);
				ifl.Read((char*)&Hei, 2);
				ifl.Read((char*)&BoxLen, 2);
				ifl.Read((char*)&BoxHei, 2);
				ifl.Read((char*)&Data, 4);

				ifl.Read((char*)&MarioX, 2);
				ifl.Read((char*)&MarioY, 2);
				ifl.Read((char*)&BackgroundColor, 2);
				ifl.Read((char*)&Time, 2);
        }

	//восстанавливаем адрес объекта-экрана
	spr=spr1;

	//выделяем память под данные
	Data=new WORD[Len*Hei];

	if (!Data)	//если не смогли выделить память под данные
	{
		Fatal("LEVEL::Load() - can't allocate memory!");
		return 0;
	}

	//читаем данные
	ifl.Read( (char*)Data, Hei*Len*2 );
/*	if (siz != Hei*Len)
	{
		fatal("LEVEL::Load - loading too smal!");
  }*/
	//закрываем файл
	ifl.Close();

	//устанавливаем признак того, что уровень не изменен
	LevelModify=0;

	return 1;
}

//=========== 'Read' - считать один символ ===========
//x,y - символьные координаты
int LEVEL::Read(int xc,int yc)
{
	if (xc<0 || xc>=Len || yc<0 || yc>=Hei)
	{
//		Debug("LEVEL::Read - X or(and) Y is bad");
		return 0;
	}
	return Data[yc*Len+xc];
}

void LEVEL::Show()
{
	Show(x,y);
}

//===================== 'Show' - показать уровень ================
//x,y - ПИКСЕЛЬНЫЕ координаты
void LEVEL::Show(int x,int y,char how)
{
/*
	if (x>MaxX)
	{
		Debug("LEVEL::Show - X is too big");
                return;
	}
	if (x<0)
	{
		Debug("LEVEL::Show - X too small");
                return;
	}
	if (y<0)
	{
		Debug("LEVEL::Show - Y too small");
				return;
	}

	if ( y>MaxY)
	{
		Debug("LEVEL::Show - Y too big");
        	return;
	}
*/

	int xoff=-x%BoxLen;
	int yoff=-y%BoxHei;

	for (int j=0; j<=200+BoxHei; j+=BoxHei)
	{
		for(int i=0; i<320+BoxLen; i+=BoxLen)
		{
            unsigned t=ReadXY(x+i,y+j);

            int msk;
			if (t& TRANSPARENTPIXELS) msk=SPRITE::SPRITETRANSPARENT;
			else		    msk=0;

			if ( (t & MASK) && (~t & ALIEN)
							&& 
				( (t&FOREGROUND && how&SHOW_FOREGROUND) 
				|| (~t&FOREGROUND && how&SHOW_BACKGROUND))
				)
				spr->ShowDirect(xoff+i, yoff+j, (t & MASK) -1, msk);

		
			//если показать отладку
			if (how & SHOW_DEBUG)
			{
			if ( t & TRANSPARENTPIXELS)
			{
				scr.locateXY(xoff+i+7+7, yoff+j);
				scr << setcolor(14) <<'T';
			}

			if ( t & DESTROYED)
			{
				scr.locateXY(xoff+i, yoff+j+8);
				scr << setcolor(15) <<'D';
			}

			if ( t & COLLAPSE)
			{
				scr.locateXY(xoff+i+8, yoff+j+8);
				scr << setcolor(11) <<'C';
			}


			if ( t & BACKGROUND)
			{
				scr.locateXY(xoff+i, yoff+j);
				scr<< setcolor(9) <<'B';
			}

			if ( t & FOREGROUND)
			{
				scr.locateXY(xoff+i+7, yoff+j);
				scr << setcolor(12) <<'F';
			}
			
			if (t & ALIEN)
			{
			scr.locateXY(xoff+i,
			yoff+j+8);
			scr << setcolor(15);

			int a=-1;

			switch ( t & MASK)
			{
			case SUPERMARIO::ALIEN::NEXTLEVEL:	//переместиться на след. уровень
			{
				scr<<"NEXTLEVEL";
				break;
			}

			case SUPERMARIO::ALIEN::PIG:         //свинья
			{
				a=SPRITE_PIGSTART;
				break;
			}

			case SUPERMARIO::ALIEN::LIZARD:     //динозаврик
			a=		SPRITE_LIZARDSTART;			//ДРАКОН
			break;

			case  SUPERMARIO::ALIEN::MASHA:		//ходячий грибок
			a=        SPRITE_MASHASTART;		//ходячий гриб
			break;

	        case  SUPERMARIO::ALIEN::TURTLE:	//черепашка
            a=        SPRITE_TURTLESTART;		
            break;

			case  SUPERMARIO::ALIEN::TOOTHFLOWER:	//зубастый цветок
			a=        SPRITE_TOOTHFLOWERSTART;	//зубастый цветок
            break;

			case  SUPERMARIO::ALIEN::FIRELINE:    //крутящаяся огненная линия
			scr<<"FIRELINE";
			break;

			case  SUPERMARIO::ALIEN::HEDGEHOG:	//ежик
            scr<<"HEDGEHOG";
            break;

			case  SUPERMARIO::ALIEN::ABORIGINE:	//туземец
			a=SPRITE_ABORIGINESTART;			//туземец
            break;

	        case  SUPERMARIO::ALIEN::LIFT:	//лифт
            scr<<"LIFT";
            break;

            default:
			scr.locateXY(xoff+i,
			yoff+j+8+8);
			scr << int(t & MASK);

			}
			if (a!=-1)
			{
                Sprite.Show(xoff+i,yoff+j, a, 0);//SCREEN::FLIP_HORZ);
            }
			} //if (t & ALIEN)
			} //if (how & DEBUG)
		} //for(i
	}//for(j
}


//пишем в уровень
void LEVEL::Write(int xc,int yc,int what)
{
	if (xc<0 || xc>=Len || yc<0 || yc>=Hei)
	{
		//Debug("LEVEL::Write X or(and) Y is bad");
		return;
	}

    if (Data[yc*Len+xc] != what)
    {
		Data[yc*Len+xc]=what;
		//устанавливаем признак изменения уровня
		LevelModify=1;
    }

}