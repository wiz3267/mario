//Mario2.cpp
////////////////////////////////////////////////////////
// MARIO2.CPP содержит функции класса SUPERMARIO      //
////////////////////////////////////////////////////////

#include "stdafx.h"
#include "total.h"

int random(int);

//проверяет чтобы внизу до конца уровня будет код n
//возвращает 1, если это так
//возвращает 0, если встетился другой код
int SUPERMARIO::scanlevel_down(MOVEOBJ &ob, int n, int deltax)
{
	//сканирование до конца уровня
	//for(int y=ob.y+24; y<=Level.MaxY+200-24; y+=24)
	for(int y=int(ob.y+24); y<=int(ob.y+24+24*2); y+=24)
	{
		if (Level.ReadXY(int(ob.x+deltax),y) != n) return 0;
	}

	return 1;
}

//проверяет все ли марио загасились
//возврат 1 - все
//        0 - пока не все
int SUPERMARIO::AllMarioDeath(ANIM&ob)
{
	for(int i=0;i<ob.Counter;i++)
        {
		if (~ob[i].Status & SUPERMARIO::MARIO_DEATH || ob[i].y<Level.MaxY+200+24*40)
                {
                	return 0;
                }
        }

	return 1;
}


void SUPERMARIO::prBuildGamePicture()
{
	//определяем единицу скорости
	{
		//MOVEOBJ::SPEED_UNIT=70.0/Timer.Freq;
		//UNIT=MOVEOBJ::SPEED_UNIT;
	}

	//моргаем цветом 255
	{
			//char r=random(64),g=random(63),b=random(64);
			//scr.SetColorRegister(255,r,g,b);
	}


	//рисуем задний фон
	if (!Level.BackgroundColor)
	{
			scr.clear();
	}
    else
    {
        int n=2;
        double start;
		double k=0;

		//if (Rick[0].Status & MARIO_PROTECTED)
		//start=Level.y/70.0+Timer2/10.0-2;
		//else
		start=Level.y/70.0-2;
	
		for(int i=0; i<=200-n; i+=n)
		{
			scr.rectangle(0,i,320,n,
				int(144+16*((Level.BackgroundColor % 7) -1)+8+7*sin( start+k)) );
				k+=0.05;
		}
	}

//	LvSpr.Scroll(56, SPRITE::SCROLL_UP); //26 jan 2008 1:34 спрайт воды

	//высчитываем, когда Mario показывать в середине
	//а когда смещать
	int x1,y1;
	for(int i=0;i<Rick.Counter;i++)
	{
		if (~Rick[i].Status & MARIO_DEATH)
		{
			break;
		}
	}


	double TX=160-12;
	double TY=24;

	int LevelMinX=0;	//!!!!!!временно!!!!!!!

    //если загасили все Mario - показываем последнее изображение
    if (i==Rick.Counter) 
	{
		x1=Level.x;
        y1=Level.y;
	}
    //иначе показываем картинку относительно марио
    else
    {
			if (Rick[i].x<TX+LevelMinX)
				x1=LevelMinX;
			else
				x1=int(Rick[i].x-TX);

			if (Rick[i].y<TY)
				y1=0;
			else
				y1=int(Rick[i].y-TY);

			if (Rick[i].x-TX>Level.MaxX)
				x1=Level.MaxX;

			if (Rick[i].y-TY>Level.MaxY)
				y1=Level.MaxY;
	}
		//рисуем определенный уровень
    {
		Level.x=x1;
		Level.y=y1;
		//рисуем те кубики уровня которые должны быть
		//на заднем плане
		Level.Show(x1,y1, Level.SHOW_BACKGROUND);
	}

	//устанавливаем координаты окна
	//чтобы чужие показывались корректно
    {
		MOVEOBJ::WindowX=Level.x;
		MOVEOBJ::WindowY=Level.y;
    }

	SCORES.Animate();		//показываем как летят очки
	Skeleton.Animate();		//показываем скелетов
	Prize.Animate();		//показываем призы
	Alien.Animate();		//показываем чужих
	Bullet.Animate();		//показываем пули
	Brick.Animate();		//показываем движ. кирпичи
	Money.Animate();		//показываем вращ. монетки
	Answer.Animate();		//показываем знаки вопроса
	Lift.ShowAll();         //показываем лифты
	Toothflower.Animate();	//показываем зубастые цветки
	Door.Animate();			//показываем двери
	FireLine.Animate();		//показываем огоньки
	CleverAlien.Animate();	//показываем умных чужих
	Boss.Animate();			//показываем босса

	//идея! Ввести общую функию Add(MOVEOBJ*ob, SizeOf);

	if (HeadSaliva.Counter)
	{
	
		HeadSaliva.Animate();		//показываем слюни
	}

	Cleverobj.ShowAll();		//показываем клевые(умные) объекты

	//уменьшаем счетик защиты
    if (ProtectedCounter) ProtectedCounter--;

	//показываем Mario
	for (i=0; i<Rick.Counter; i++)
	{
		PERSON&rk=(PERSON&) Rick[i];

        //если марио ушел за левую границу экрана
        if (rk.x<LevelMinX)
		{
			rk.x=LevelMinX;
			rk.Speedx=0;	//чтобы не прилеплялся
			rk.Acceleratx=0;//к границе экрана
		}

		//если марио ушел за правую границу уровня
		if (rk.x>Level.MaxX+320-24)
		{
			rk.x=Level.MaxX+320-24;

			rk.Speedx=0;	//чтобы не прилеплялся
			rk.Acceleratx=0;//к границе экрана
		}


		//если марио загашен
		//if (rk.Status & MARIO_DEATH) continue;


		//если марио не защищенный
        if ( ~rk.Status & MARIO_PROTECTED )
        {
			rk.Show();
		}


		//если защищенный показываем мерцающим
		if( ProtectedCounter % 4 > 2)
		{
			rk.Show();
		}

        //если число игроков > 1 показываем номер игрока
        if (Rick.Counter>1)
        {
			int m=0;
            if (rk.Movement == PERSON::LEFT) m=20;
            Sprite.Show(int(rk.x-rk.WindowX-4+m),int(rk.y-rk.WindowY-3), SPRITE_DIGITAL0+i+1);
        }

	}

	//!!!!!! ВРЕМЕННО !!!!!!!!!
    if (Keyb[KEY_1])
	{
		//рисуем статус
		for(i=0; i<Rick.Counter; i++)
		{
			int a=Rick[i].Status;
			{
				scr<<cur(0,5+i)<<"MARIO "<<i+1<<" is ";
				if (a & MARIO_CLAMMY) scr<<"CLAMMY ";
				if (a & MARIO_BIG) scr<<"BIG ";
				if (a & MARIO_DEATH) scr<<"DEATH ";
				if (a & MARIO_CANFIRE) scr<<"CANFIRE ";
				if (a & MARIO_PROTECTED) scr<<"PROTECTED ";
				scr<<'!';
			 }
		}
		//scr.color=15;
		//scr<<cur(0,4)<<"FPS="<<fps;

    }

    //показываем дверь,которая должна быть перед марио
    {
		Door1.Animate();
	}

	Timer1+=1;

    if (Different.Counter)
		Different.Animate();		//показываем разные объекты

	//(показываем те кубики, что на переднем плане)
	Level.Show(x1,y1,Level.SHOW_FOREGROUND);	

     //рисуем полосу статуса
    DrawStateline();

	//если время кончается
	if (Time<30 && Time&1)
	{
		BIGSTRING Faster(&BigFont,"FASTER !");
        Faster.Show(64,88);
	}

	//если время закончилось
	if (!Time)
	{
		 //выводим надпись
		BIGSTRING TimeUp(&BigFont, "TIME UP");
		TimeUp.Show(76, 88);
		scr.update();
	}

	//если переход уровня, не обновлять экран
	if ( ! (GameMode & GAMEMODE_RESTARTLEVEL) )
	{
		//Update();
	}


    //если кончилось время
    if (!Time)
    {

        for(int i=0; i<Rick.Counter;i++)
		{
            ANIM&rk=Rick[i];
			if (rk.Status & MARIO_DEATH) continue;

            //гасим марио
            rk.Speedx=0;
      		rk.Speedy=-5;
	        rk.Acceleratx=0;
        	rk.Acceleraty=0.2;
	        rk.FrameSpeed=0;
        	rk.Status|=MARIO_DEATH;

            //если был липучий - теперь нет
			rk.Status&=~MARIO_CLAMMY;
			Sound.play(SND_LAUGHT);
	        //выдерживаем паузу
			//scr.pause(DEATHPAUSE);
		}
    }
		

    //уменьшаем время
	if ( Timer2--%20 == 0)
	{
		if (Time) Time-=1;
	}

	//рисуем знак вопроса
	if (ShowExit)
	{
		//string s(&BigFont, "EXIT ?");
		//s.Show(100);
		scr.center(100, "Выйти в главное меню ?");
	}

	//показываем сообщения
	//if ( !random(4) ) 
	Movetxt.Animate();

}

//реализация функции умных объектов для объектов Rick
void SUPERMARIO::MindobjFunctions(PERSON &Rick, MINDOBJ &Cleverobj)
{
for(int i=0; i<Rick.Counter; i++)
{
	PERSON &rk=Rick[i];

	if (rk.Status & MARIO_DEATH) continue;
	for(int j=0; j<Cleverobj.Counter; j++)
	{
		MINDOBJ &cl=Cleverobj[j];
		//если марио столкнулся с клевым объектом
		if(CheckUnionRects(rk.Rect, cl.Rect))
		{
			//пытаемся прилепиться
			double a=rk.y+rk.Hot.Bottom,
			b=cl.y+cl.Hot.Top;
			if
			(
				cl.State & MINDOBJ::LIFT	&&
				!(rk.Status & MARIO_CLAMMY)	&&
				rk.Speedy>=0				&&
				(a-b)>0						&&
				(a-b)<10
			)
			{
				rk.Speedy=0;
				rk.Acceleraty=0;
				rk.y=cl.y-24+cl.Hot.Top+1;
				//говорим марио, что он на клевом объекте
				rk.Status |=MARIO_CLAMMY;
				rk.Link=j;
				rk.ClammyX=rk.x-cl.x;
				//rk.ClammyX=cl.x-rk.x;
			}
			//иначе если не прилеплен
			else if (!(rk.Status & MARIO_CLAMMY))
			{
				//если клевый объект опасный
				//и марио не защищенный
				if(cl.State & MINDOBJ::DANGER &&
				~rk.Status & MARIO_PROTECTED)
				{
					rk.Status |= MARIO_DEATH;
					rk.Speedx=0;
					rk.Acceleratx=0;
					rk.Speedy=-4;
					rk.Acceleraty=0.2;
					rk.Movement=rk.FLIP_VERT;
			
					Sound.play(SND_PIGEGRIN, SOUND::NOSTOP);
				}
			}

		}
	}
}
}

//******************************************************
//***************** собираем скелетов ******************
//******************************************************
void SUPERMARIO::SkeletonCollect()
{
	for(int j=0; j<Rick.Counter; j++)
	for(int i=0; i<Skeleton.Counter; i++)
	{
		ANIM &rk=Rick[j];
		ANIM &sk=Skeleton[i];
		if (CheckUnionRects(rk.Rect,sk.Rect))
		{
			switch (sk.Status)
			{
				//если берем скелета, за которого дают очки
				case SKELET_SCORE:
				{
					Skeleton.Del(i);
					i--;

					Score+=130;

					MOVETXT tx;
					tx.Message="THANKYOU   ADVENTURER";
					tx.Color=14;
					tx.x=(320-strlen(tx.Message)*8)/2;
					tx.y=50;
					tx.TimeLive=100;
					Movetxt.DelAll();
					Movetxt+=tx;

					Sound.play(SND_EXORCISM, SOUND::NOSTOP);
					break;
				}

				//если это скелет, открывающий дверь
				case SKELET_DOOR:
				{
					//если вся карта собрана
					if (MapCounter==6)
					{
						//открываем стену
						for(int x=0; x<=Level.MaxX+320; x+=24)
						for(int y=0; y<=Level.MaxY+200; y+=24)
						if (Level.ReadXY(x,y)==BRICK::DOOR)
						Level.WriteXY(x,y,0);

						//удаляем скелета
						Skeleton.Del(i);
						i--;

						//звук взрыв
						Sound.play(SND_XPLODE);
					}
					//выдаем сообщение
					else
					{
						MOVETXT tx;
						tx.Message="ELEMENTAL   REQUIRED";
						tx.Color=13;
						tx.x=(320-strlen(tx.Message)*8)/2;
						tx.y=50;
						tx.TimeLive=20;
						Movetxt.DelAll();
						Movetxt+=tx;
					}
					break;
				}
			} //switch (sk.Status)
		} //if (CheckUnionRects(rk.Rect,sk.Rect))
	} //for(int i=0; i<Skeleton.Counter; i++)
}

//обработка различных режимов игры
void SUPERMARIO::GameModesTreat()
{
	//загрузка уровня
	if (GameMode & GAMEMODE_LOADLEVEL )
	{
		//07 feb 2008 10:27
		ShowLevelNumberTimeCounter=0;
		//GameMode_LoadLevelSituation();

		//удаляем
		Alien.DelAll();   	//всех чужих
		Prize.DelAll();		//всех призы
		SCORES.DelAll();	//очки
		Bullet.DelAll();	//стрельбу
		Brick.DelAll();		//кирпичи
		Money.DelAll();		//деньги
		Answer.DelAll();
		Toothflower.DelAll();	//цветки
		FireLine.DelAll();	//огни
		Lift.DelAll();		//лифты
		Cleverobj.DelAll();	//клевые объекты
		CleverAlien.DelAll();	//умных чужих
		HeadSaliva.DelAll();	//слюни башки
		Boss.DelAll();		//удаляем боссов
		Skeleton.DelAll();	//удаляем скелетов

		//обнуляем этот режим игры
		GameMode^=GAMEMODE_LOADLEVEL;

		MapCounter=0;	//обнуляем число собранных карт;

		//загружаем уровень
		{
			Level.Load(LevelNumber);

			//проверяем, это подводный уровень ?
			if (Level.BackgroundColor & LEVEL::FLAG_UNDERWATER)
			{
				LevelStatus=LEVEL_UNDERWATER;
			}
			else
			{
				LevelStatus=0;
			}

			//определяем пределы передвижения для этого уровня
			MOVEOBJ::Lim.Top=-200;
			MOVEOBJ::Lim.Left=-200;
			MOVEOBJ::Lim.Right=Level.MaxX+320;
			MOVEOBJ::Lim.Bottom=Level.MaxY+200;
		}

		{
			//устанавливаем марио
			for(int i=0; i<Rick.Counter; i++)
			{
				Rick[i].x=Level.MarioX;
				Rick[i].y=Level.MarioY;

				// делаем марио человечком
				Rick[i].Status=0;

				//закоментировано - чтобы сила и вид оружия не обнулялись
				//при переходе на другой уровень
				//Arms=ARROW;
				//ArmsPower=ArrowPower;

				OldMarioX=Level.MarioX;
				OldMarioY=Level.MarioY;
			}
		}

		//устанавливаем минимальную границу
		{
			//LevelMinX=0;
		}

		//настравиваем время
		{
			Time=Level.Time;
		}

		//отображаем состояние игры
		{

        	MidiStop();

			scr.rectangle(0,0,320,200,0);
			
			DrawStateline();

			scr << cur(17,8) << "МИР ";
			scr.putNumb(LevelNumber/4+1,1);
			scr<< '-';
			scr.putNumb(LevelNumber%4+1,1);
			Sprite.Show(130,93,SPRITE_RICKSTART);
			scr << cur(20,13) << "x ";
			scr.putNumb(Lives);
			scr.update();

			
			//scr.pause(100);
	
			NORMAL_MUSIC=LevelNumber%2;

			if (LevelStatus&LEVEL_UNDERWATER) NORMAL_MUSIC=3;

			PlayMusic(NORMAL_MUSIC);

			Sound.play(SND_GHOTIC);

		}


	//******************************************
	//   сканируем поле в поисках чужих
	//******************************************
	{
		//обнуляем этот режим игры
		GameMode^= GAMEMODE_ALIEN_SCAN;

		for(int y=0; y<Level.MaxY+200; y+=24)
		for(int x=0; x<Level.MaxX+320; x+=24)
		{
			int m=Level.ReadXY(x,y);
			int t=m&LEVEL::MASK;
			if (m & LEVEL::ALIEN)
			{
				//записать после себя нуль
				switch(t)
				{
					case ALIEN::TOOTHFLOWER:
					case ALIEN::LIFT:
					case ALIEN::TURTLE:
					case ALIEN::MASHA:
					case ALIEN::LIZARD:
					case ALIEN::PIG:
					case ALIEN::HEDGEHOG:
					case ALIEN::FIRELINE:
					case ALIEN::ABORIGINE:
					case ALIEN::BRIDG_LR1:
					case ALIEN::BRIDG_UD1:
					case ALIEN::BRIDG_UD2:
					case ALIEN::EAGLE_LR1:
					case ALIEN::BRIDG_RL2:
					case ALIEN::BRIDG_LR2:
					case ALIEN::BRIDG_UD3:
					case ALIEN::BRIDG_LR_DIAG1:
					case ALIEN::BRIDG_UR_LU1:
					case ALIEN::BRIDG_UL_RU1:
					case ALIEN::HEAD1:
					case ALIEN::BRIDG_R16_D3_R16:
					case ALIEN::BRIDG_P_DN9:
					case ALIEN::BRIDG_UD_4P:
					case ALIEN::BRIDG_DU_5P:
					case ALIEN::BRIDG_UD_2P:
					case ALIEN::BRIDG_DU_6P:
					case ALIEN::WBRIDG_LR_16:	//водный мостик влево-вправо на 16
					case ALIEN::SKELETON1:
					case ALIEN::SKELETON2:
					case ALIEN::BIRD:
					case ALIEN::COSMONAUT:
					case ALIEN::FISH:
					case ALIEN::HELIX:
					case ALIEN::SHARK:
					//удаляем
					Level.WriteXY(x,y,0);
				} //switch (t)

				//создаем чужого
				ALIEN ob;
				ob.x=int(x/24)*24;
				ob.y=int(y/24)*24;
				ob.Speedx=-0.9;
				ob.Hot.Set(5,0,18,23);

				//переключатель для различных чужих
				switch(t)
				{

				//элемент "перемещение на уровень N"
				case ALIEN::CHANGELEVEL:
				{
					//всего в таблице SHUFFLE_COUNT элементов
					Shuffle[19].BoxCode=19;
					Shuffle[19].LevelNumber=Level.ReadXY(x+24,y);
					Shuffle[19].Status=SHUFFLE::CHGLEVEL;
					Level.WriteXY(x+24,y,0);

					break;
				}

				//акула (ихтиозавр)
				case ALIEN::SHARK:
				{
					MINDOBJ cl;
					cl.x=ob.x;
					cl.y=ob.y;
					cl.State=cl.PERSON | cl.DANGER
					;

					cl.Hot.Set(10,10,80,30);
					cl.ShootCounter=10;

					//создаем разброс в движении
					int K=random(24*6);
					//разброс в скорости
					double t=0.1*random(40);

					MINDOBJ::GOING go1[]=
					{
					  {-1-t,0, 24*8+K},
					  {1+t,0, 24*8+K},
					};


					MINDOBJ::GOING go2[]=
					{
					  {-1-t,0.5, 24*8+K},
					  {1+t,-0.5, 24*8+K},
					};


					MINDOBJ::FRAMING fr[]=
					{ {SPRITE_SHARK1, 6},
					  {SPRITE_SHARK2, 6}
					};

					CleverAlien.Add(cl,2,go1,2,fr);
					break;
				}


				//улитка
				case ALIEN::HELIX:
				{
					MINDOBJ cl;
					cl.x=ob.x+8;
					cl.y=ob.y+8;

					cl.State=cl.PERSON | cl.DANGER;
					cl.SpriteIndex=SPRITE_FISH1;
					cl.Hot.Set(8,0,24,13);


					int K=4*24+random(2*24);

					MINDOBJ::GOING go[]=
					{
					  {0.5,0, K},
					  {-0.5,0, K},
					};

					MINDOBJ::FRAMING fr[]=
					{ {SPRITE_HELIX1, 6},
					  {SPRITE_HELIX2, 6}
					};

					CleverAlien.Add(cl,2,go,2,fr);
					break;
				}

					//рыбка
				case ALIEN::FISH:
				{
					MINDOBJ cl;
					cl.x=ob.x;
					cl.y=ob.y;
					cl.State=cl.PERSON | cl.DANGER
					;

					cl.Hot.Set(10,10,26,16);

					//создаем разброс в движении
					int K=random(24*6);
					//разброс в скорости
					double t=0.1*random(10);

					MINDOBJ::GOING go1[]=
					{
					  {-1-t,0, 24*8+K},
					  {1+t,0, 24*8+K},
					};


					MINDOBJ::GOING go2[]=
					{
					  {-1-t,0.5, 24*8+K},
					  {1+t,-0.5, 24*8+K},
					};


					MINDOBJ::FRAMING fr[]=
					{ {SPRITE_FISH1, 6},
					  {SPRITE_FISH2, 6}
					};

					CleverAlien.Add(cl,2,go1,2,fr);

					break;


				}

				//птичка
				case ALIEN::BIRD:
				{
					MINDOBJ cl;
					cl.x=ob.x;
					cl.y=ob.y;
					cl.FrameSpeed=0.5;
					cl.State=cl.PERSON | cl.DANGER;
					cl.SpriteIndex=SPRITE_BIRD1;
					cl.Hot.Set(6,6,15,9);
					cl.Speedx=1.5;
					cl.Speedy=0.7;
					MINDOBJ::GOING go[]=
					{
					  {0,0, 24},
					};

                    MINDOBJ::FRAMING fr[]=
                    { {SPRITE_BIRD1, 6},
					  {SPRITE_BIRD2, 6}
					};
					CleverAlien.Add(cl,1,go,2,fr);
					break;

				}

				//скелет, за него дают очки
                case ALIEN::SKELETON2:
                {
					ANIM cl;
                    cl.x=ob.x;
                    cl.y=ob.y;
                    cl.SpriteIndex=SPRITE_SKELETON;
                    cl.Status=SKELET_DOOR;
                    cl.Hot.Set(9,15,44,22);
                    Skeleton+=cl;
                    break;
                }

				//скелет, который можно собирать
				case ALIEN::SKELETON1:
				{
					ANIM cl;
					cl.x=ob.x;
                    cl.y=ob.y;
                    cl.SpriteIndex=SPRITE_SKELETON;
					cl.Hot.Set(9,15,44,22);
                    cl.Status=SKELET_SCORE;
                    Skeleton+=cl;
                    break;
                }


				case ALIEN::WBRIDG_LR_16:	//водный мостик влево-вправо на 16
				{
					MINDOBJ cl;
					cl.x=ob.x-4;
					cl.y=ob.y+2;
					MINDOBJ::FRAMING fr[]={ {
					SPRITE_WATERBRIDG, 1} };

					MINDOBJ::GOING go[]=
					{
						{-1,0,24*16},
						{1,0,24*16}
					};
					
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,2,go,1,fr);
					break;
				}
										//мостки вниз-вверх на 6 с паузой
				case ALIEN::BRIDG_DU_6P:
				{
					MINDOBJ cl;
					cl.x=ob.x-4;
					cl.y=ob.y;
                    MINDOBJ::FRAMING fr[]={ {
                    SPRITE_BRIDG, 1} };

                    MINDOBJ::GOING go[]=
					{
						{0,0,24*3},
						{0,1,24*6},
						{0,0,24*3},
						{0,-1,24*6}
					};
					
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,4,go,1,fr);
					break;
				}

				//мостик вверх-вниз на 2 c паузой
				case ALIEN::BRIDG_UD_2P:
				{
					MINDOBJ cl;
					cl.x=ob.x;
					cl.y=ob.y;
					
					MINDOBJ::FRAMING fr[]=
					{ 
						{SPRITE_BRIDG, 1}
					};

					MINDOBJ::GOING go[]=
					{
						{0,0,24*4},
						{0,-1,24*2},
						{0,0,24*4},
						{0,1,24*2}
					};
					
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,4,go,1,fr);
					break;
				}


				//мостик вверх-вниз на 4 c паузой
				case ALIEN::BRIDG_UD_4P:
				{
					MINDOBJ cl;
					cl.x=ob.x;
					cl.y=ob.y;
					
					MINDOBJ::FRAMING fr[]=
					{ 
						{SPRITE_BRIDG, 1}
					};

					MINDOBJ::GOING go[]=
					{
						{0,0,24*2},
						{0,-1,24*4},
						{0,0,24*4},
						{0,1,24*4}
					};
					
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,4,go,1,fr);
					break;
				}

				//мостик вниз-вверх на 5 с паузой
				case ALIEN::BRIDG_DU_5P:
				{
					MINDOBJ cl;
					cl.x=ob.x+12;
					cl.y=ob.y+6;
					MINDOBJ::FRAMING fr[]={ {SPRITE_BRIDG, 1} };

					MINDOBJ::GOING go[]=
					{
						{0,0,24*2},
						{0,1,24*5+6},
						{0,0,24*4},
						{0,-1,24*5+6}
					};
					
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,4,go,1,fr);
					break;
				}

				//лифтик движение вниз-вверх на 9
				//с паузой
				case ALIEN::BRIDG_P_DN9:
				{
					MINDOBJ cl;
					cl.x=ob.x+5;
					cl.y=ob.y;
					MINDOBJ::FRAMING fr[]={ {SPRITE_BRIDG, 1} };

					MINDOBJ::GOING go[]=
					{
						{0,0,24*2},
						{0,1,24*9},
						{0,0,24*4},
						{0,-1,24*9}
					};
					
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,4,go,1,fr);
					break;
				}



				//лифтик движение сложное
				case ALIEN::BRIDG_R16_D3_R16:
				{
					MINDOBJ cl;
					cl.x=ob.x;
					cl.y=ob.y-1;
					MINDOBJ::FRAMING fr[]={ {SPRITE_BRIDG, 1} };

					double s=5.5;
					MINDOBJ::GOING go[]=
					{
						{1,0,int(24*1)},
						{2,0,int(24*2/2)},
						{3,0,int(24*1/3)},
						{s,0,int(24*8/s)},
						{s,-1,int(24*4/s)},
						{s, 0, int(24*6/s)},
						{s, -1, int(24*5/s)},
						{s, 0, int(24*3/s)},
						{3, 0, int(24*2/3)},
						{2, 0, int(24*2/2)},
						{1, 0, int(24*1)},
						//назад
						{-1,0, int(24*1)},
						{-2, 0, int(24*2/2)},
						{-3, 0, int(24*2/3)},
						{-s, 0, int(24*3/s)},
						{-s, 1, int(24*5/s)},
						{-s, 0, int(24*6/s)},
						{-s,1,int(24*4/s)},
						{-s,0,int(24*8/s)},
						{-3,0,int(24*1/3)},
						{-2,0,int(24*2/2)},
						{-1,0,int(24*1)},
					};
					
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,22,go,1,fr);
					break;
				}


				//башка //???????????
				case ALIEN::HEAD1:
				{
					double k=2.8,m=2.8;
					double r=7.5;
					
					MINDOBJ::GOING go[]=
					{
						{k,0,int(r) },
						{k,-m,int(r) },
						{0,-m,int(r) },
						{ -k, -m, int(r)},
						{ -k,0,int(r)},
						{ -k, m,int(r)},
						{  0, m, int(r)},
						{  k, m, int(r) },
						{ 0, 0, MINDOBJ::SET_INDEX},
						{ 4, -7, 2},
						{ -4, 7, 2},
						{ -4, -7, 2},
						{ 4, 7, 2},
						{ -6, -7, 2},
						{ 6, 7, 2},
						{ 8, -7, 2},
						{ -8, 7, 2},
						{ 0, 0, MINDOBJ::SET_INDEX},
					};
					
					MINDOBJ::FRAMING fr[]=
					{
						{SPRITE_HEAD1, 30},
						{SPRITE_HEAD2, 90},
						{SPRITE_HEAD1, 20},
						{SPRITE_HEAD2, 160},
						{SPRITE_HEAD1, 30},
						{SPRITE_HEAD2, 120},
						{0, MINDOBJ::SET_INDEX},
						{SPRITE_HEAD3, 20},
					};

					MINDOBJ cl;

					cl.State = //cl.PERSON
					cl.DANGER;
					cl.Hot.Set(0,1,24,15);
					cl.y=ob.y+5;
					cl.x=ob.x+12;

					cl.TimeLive=0;
					cl.Hot.Set(5,5,30,40);
					cl.ShootCounter=6;
					Boss.Add(cl, 18, go, 8, fr, 0,1);
					break;
				}


				//лифтик движение сложное
				//диагонально вверх(4) влево(2)
				//затем диагонально вверх(4) вправо(2)
				//затем вниз
				case ALIEN::BRIDG_UL_RU1:
				{
                    MINDOBJ cl;
                    cl.x=ob.x;
                    cl.y=ob.y;
                    MINDOBJ::FRAMING fr[]={ {
                    SPRITE_BRIDG, 1} };
                    MINDOBJ::GOING go[]=
					{
						{-1, -2, 24*4/2},
						{1, -2, 24*4/2},
						{-1, 2, 24*4/2},
						{1, 2, 24*4/2}
                    };
                    cl.State = MINDOBJ::LIFT;
                    cl.Hot.Set(0,0,23,12);
                    Cleverobj.Add(cl,4,go,1,fr);
                    break;
                }

                //лифтик движение сложное
                //диагонально вверх(4) вправо(2)
                //затем диагонально вверх(4) влево(2)
                case ALIEN::BRIDG_UR_LU1:
                {
                    MINDOBJ cl;
                    cl.x=ob.x;
                    cl.y=ob.y;
                    MINDOBJ::FRAMING fr[]={ {
                    SPRITE_BRIDG, 1} };
                    double sp=2.7;
                    MINDOBJ::GOING go[]=
					{
						{1, sp, 24*4/2},
						{-1, sp, 24*4/2},
						{1, -sp, 24*4/2},
						{-1, -sp, 24*4/2}
                    };
                    cl.State = MINDOBJ::LIFT;
                    cl.Hot.Set(0,0,23,12);
                    Cleverobj.Add(cl,4,go,1,fr);
                    break;
                }


                //лифтик движение сложное
                // вправо-диагональ-вправо-влево-
                // диагональ-влево
                case ALIEN::BRIDG_LR_DIAG1:
                {
                    MINDOBJ cl;
                    cl.x=ob.x;
                    cl.y=ob.y;
                    MINDOBJ::FRAMING fr[]={ {
                    SPRITE_BRIDG, 1} };
                    MINDOBJ::GOING go[]={
	                {0,0,5},
	                {1,0,8},
					{ 2,0,12},
                    { 3,-3, 24*2/3 },
					{ 4,-4, 24*3/4},
					{ 3,-3, 24*2/3},
                    {2,0,12},
                    {1,0,24},

                    {0,0,5},

                    {-1,0,24},
                    {-2,0,12},
					{ -3,3, 24*2/3},
                    { -4, 4, 24*3/4},
					{ -3,3, 24*2/3},
					{-2,0,12},
					{-1,0,8}
                    };
                    cl.State = MINDOBJ::LIFT;
                    cl.Hot.Set(0,0,23,12);
                    Cleverobj.Add(cl,16,go,1,fr);
                    break;
                }


                //лифтик вверх-вниз на 4 с задержкой
                case ALIEN::BRIDG_UD3:
                {
                    MINDOBJ cl;
                    cl.x=ob.x-6;
                    cl.y=ob.y;
                    MINDOBJ::FRAMING fr[]={ {
                    SPRITE_BRIDG, 1} };
                    MINDOBJ::GOING go[]={ {0,-1,24*4}, {0,0,24*2},
                    {0,1, 24*4 }, {0,0,24*2} };
                    cl.State = MINDOBJ::LIFT;
                    cl.Hot.Set(0,0,23,12);
                    Cleverobj.Add(cl,4,go,1,fr);
                    break;
                }

				//водяной мостик влево-вправо на 6 клеток
				case ALIEN::BRIDG_LR2:
                {
					MINDOBJ::FRAMING fr[]=
					{
						{SPRITE_WATERBRIDG, 1} 
					};
					MINDOBJ::GOING go[]=
					{ 
						{-1,0,24*6},
						{1,0, 24*6 } 
					};

					MINDOBJ cl;
					cl.x=ob.x-12;
					cl.y=ob.y+15;
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(8,0,24,12);

					Cleverobj.Add(cl,2,go,1,fr);
					break;
                }

                //мостик вправо-влево на 6 клеток
                case ALIEN::BRIDG_RL2:
                {
					MINDOBJ::FRAMING fr[]=
					{
						{SPRITE_WATERBRIDG, 1}
					};
					
					MINDOBJ::GOING go[]=
					{
						{1,0,24*6},
						{-1,0, 24*6 }
					};

					MINDOBJ cl;
					cl.x=ob.x;
					cl.y=ob.y+15;
					cl.State = MINDOBJ::LIFT;
					cl.Hot.Set(8,0,24,12);

					Cleverobj.Add(cl,2,go,1,fr);
					break;
                }

                //летающий влево-вправо орел
                case ALIEN::EAGLE_LR1:
                {
                    MINDOBJ cl;
                    cl.x=ob.x;
                    cl.y=ob.y;
                    MINDOBJ::FRAMING fr[]=
					{
						{SPRITE_EAGLESTART, 1}
					};


                    MINDOBJ::GOING go[]={ {-3,0,24*12/2},
                    {3,0, 24*12/2 } };

                    cl.State = MINDOBJ::PERSON
						| MINDOBJ::LIFT | MINDOBJ::DANGER;

                    cl.Hot.Set(8,0,32,48);
					CleverAlien.Add(cl,2,go,1,fr);
                    break;
                }

                //космонавт
				case ALIEN::COSMONAUT:
                {
					MINDOBJ cl;
                    cl.x=ob.x;
                    cl.y=ob.y;
                    /*MINDOBJ::FRAMING fr[]=
					{
					{SPRITE_EAGLE, 1} };*/
                    MINDOBJ::FRAMING fr[]=
                    {
                     {SPRITE_COSMONAUT0, 6},
					 {SPRITE_COSMONAUT1, 6},
                     {SPRITE_COSMONAUT2, 6},
                     {SPRITE_COSMONAUT3, 6},
                    };

                    MINDOBJ::GOING go[]=
					{
						{-1,0,24*7/2},
						{0,0,1},
						{1,0, 24*7/2 }
					};

					/*MINDOBJ::GOING go[]=
		            {
                        {0, -5, cl.SET_SPEED},
                        {0, 0.2, cl.SET_ACCELERAT},
						{0,0,50}
			        };*/
	                cl.State = MINDOBJ::PERSON| MINDOBJ::LIFT;
					cl.Hot.Set(0,0,32,64);
					CleverAlien.Add(cl,3,go,4,fr);
                    break;
				}


                //лифтик вверх-вниз на 8
                case ALIEN::BRIDG_UD2:
                {
					MINDOBJ cl;
                    cl.x=ob.x-12;
                    cl.y=ob.y+5;
                    MINDOBJ::FRAMING fr[]={ {
                    SPRITE_BRIDG, 1} };
                    MINDOBJ::GOING go[]={ {0,-1,24*8+10}, {0,0,1},
                    {0,1, 24*8+10 } };
                    cl.State = MINDOBJ::LIFT;
                    cl.Hot.Set(0,0,23,12);
					Cleverobj.Add(cl,3,go,1,fr);
					break;
                }

				//лифтик вверх-вниз на 18
                case ALIEN::BRIDG_UD1:
                {
                        MINDOBJ cl;
                        cl.x=ob.x-12;
                        cl.y=ob.y+5;
                        MINDOBJ::FRAMING fr[]={ {
                        SPRITE_BRIDG, 1} };
                        MINDOBJ::GOING go[]={ {0,-1,24*18}, {0,0,1},
                        {0,1, 24*18 } };
                        cl.State = MINDOBJ::LIFT;
                        cl.Hot.Set(0,0,23,12);
                        Cleverobj.Add(cl,3,go,1,fr);
						break;
                }

                //лифтик
                case ALIEN::BRIDG_LR1:
                {
                        MINDOBJ cl;
                        cl.x=ob.x;
                        cl.y=ob.y+4;
                        MINDOBJ::FRAMING fr[]={ {
                        SPRITE_BRIDG, 1} };
						MINDOBJ::GOING go[]={ {1,0,24*13},
                        {0,0,24*3},
                        {-1,0, 24*13 },
						{0,0,24*3} };
                        cl.State = MINDOBJ::LIFT;
                        cl.Hot.Set(0,0,23,12);
                        Cleverobj.Add(cl,4,go,1,fr);
                    break;
                }

                //крутящаяся линия
                case ALIEN::FIRELINE:
                {
					FIRELINE fr;
					Level.WriteXY(x,y,BRICK::BREAK);
					fr.xc=int(ob.x+10);
					fr.yc=int(ob.y+10);
					fr.Hot.Set(5,5,6,6);
					fr.FrameFirst=SPRITE_FIRESTART;
					fr.FrameLast=SPRITE_FIREEND;
					fr.FrameSpeed=0.2;
					fr.Speed=0.05;
					//огненную линию надо всегда анимировать
					fr.AlwaysAnimate=TRUE;

					//доверимся случаю
					double step=0.1*((y/24)%5);

					for (fr.Radius=0; fr.Radius<80; fr.Radius+=15)
					{
						FireLine+=fr;
						fr.Angle+=step;

					}
					break;
				}

                //туземец
                case ALIEN::ABORIGINE:
				{
					ob.FrameFirst=SPRITE_ABORIGINESTART;
					ob.FrameLast=SPRITE_ABORIGINEEND;
					ob.FrameSpeed=0.3;
                    ob.Hot.Set(2,0,23,23);
					Alien+=ob;
					break;
				}

                //ежик
                case ALIEN::HEDGEHOG:
                {
					ob.FrameFirst=SPRITE_HEDGEHOGSTART;
					ob.FrameLast=SPRITE_HEDGEHOGEND;
					ob.FrameSpeed=0.1;
					Alien+=ob;
					break;
                }

                //свинья
                case ALIEN::PIG:
					ob.FrameFirst=SPRITE_PIGSTART;
					ob.FrameLast=SPRITE_PIGEND;
					ob.FrameSpeed=0.4;
					ob.ShootCounter=2;
					Alien+=ob;
					break;
				
				//дракон
				case ALIEN::LIZARD:
					ob.FrameFirst=SPRITE_LIZARDSTART;
					ob.FrameLast=SPRITE_LIZARDEND;
					ob.FrameSpeed=0.3;
					ob.ShootCounter=3;
					Alien+=ob;
					break;

				//ходячий грибок
				case ALIEN::MASHA:
				{
					ob.FrameFirst=SPRITE_MASHASTART;
					ob.FrameLast=SPRITE_MASHAEND;
					int k=rand()%2 ? -1: 1;
					int speed=1+rand()%3;
					ob.FrameSpeed=0.1*speed;

					Alien+=ob;
					break;
				}

				//черепаха
				case ALIEN::TURTLE:
					ob.FrameFirst=SPRITE_TURTLESTART;
					ob.FrameLast=SPRITE_TURTLEEND;
					ob.Movement=PERSON::UNUSED;
					ob.ShootCounter=5;
					ob.Speedx=-0.9-0.1*random(20);
					ob.FrameSpeed=abs(ob.Speedx)/10.0;
					Alien+=ob;
					break;

				//зубастый цветок
				case ALIEN::TOOTHFLOWER:
				{
					ANIM ob1;

					ob1.y=ob.y;
					ob1.x=ob.x;

					ob1.x-=12;

					ob1.Speedy=-4;
					ob1.Speedx=0;

					ob1.FrameFirst=SPRITE_TOOTHFLOWERSTART;
					ob1.FrameLast=SPRITE_TOOTHFLOWEREND;
					ob1.FrameSpeed=0.1;
					ob1.SpriteIndex=SPRITE_TOOTHFLOWERSTART;

					ob1.TimeLive=0;
					ob1.Acceleraty=0.2;

					ob1.Hot.Set(8,6,23,23);

					Toothflower+=ob1;

					break;

				}

				//мостик, двигающися по окружности
				case ALIEN::CIRCLEBRIGDE:
				{
					FIRELINE fr;
					Level.WriteXY(x,y,BRICK::BREAK);
					fr.xc=int(ob.x+10);
					fr.yc=int(ob.y+10);
					fr.Hot.Set(5,5,6,6);
					fr.FrameFirst=SPRITE_BRIDG;
					fr.FrameLast=SPRITE_BRIDG;
					fr.FrameSpeed=1;
					fr.Speed=0.01;
					//огненную линию надо всегда анимировать
					fr.AlwaysAnimate=TRUE;

					fr.Radius=100;
					//доверимся случаю
					double step=0.1*((y/24)%5);

						FireLine+=fr;
						fr.Angle+=step;

					break;
				}

				//лифт
				case ALIEN::LIFT:
				{
					ANIM ob1;
					ob1.Hot.Set(0,0,24,10);
					ob1.TimeLive=3;

					ob1.x=ob.x;
					ob1.y=ob.y;
					ob1.Speedy=1.5;
					ob1.Speedx=0;
					ob1.SpriteIndex=SPRITE_LIFT;
					Lift+=ob1;

					ob1.x+=24;
					Lift+=ob1;

					ob1.x+=24;
					Lift+=ob1;

					ob1.x+=24;
					Lift+=ob1;

					ob1.x+=24;
					Lift+=ob1;
					break;
				}
				} // switch (t)
			}//if (m & LEVEL::ALIEN)
		} //for for
	} //конец сканирования
	} //конец обработки загрузки уровня if (GameMode & GAMEMODE_LOADLEVEL )


	//******************************************
	//   обрабатываем ситуацию рестарта уровня
	//******************************************
	
	if (GameMode & GAMEMODE_RESTARTLEVEL )
	{
		//07 feb 2008 09:56

        //обнуляем этот режим игры
        GameMode^=GAMEMODE_RESTARTLEVEL;

        //время идет снова
        Time=Level.Time;

        //настраиваем координаты марио
        for(int i=0;i<Rick.Counter;i++)
		{
			PERSON &rk=(PERSON&)Rick[i];

			rk.Status&=~MARIO_DEATH;
			rk.Status|=MARIO_PROTECTED;
			rk.Status|=MARIO_CANFIRE;
			ProtectedCounter=40;

			//rk.Set(Level.MarioX, Level.MarioY,
			//0,0, 0,0);
			if (!OldMarioX && !OldMarioY)
			{
				OldMarioX=Level.MarioX;
				OldMarioY=Level.MarioY;
			}

			rk.Set(OldMarioX, OldMarioY,
				0,0, 0,0);

			if (rk.Status & MARIO_BIG)
			{
				rk.FrameFirst=SPRITE_LIZARDSTART;
				rk.FrameLast=SPRITE_LIZARDEND;
				rk.SpriteIndex=SPRITE_LIZARDSTART;
			}
			else
			{
				rk.FrameFirst=SPRITE_RICKSTART;
				rk.FrameLast=SPRITE_RICKEND;
				rk.SpriteIndex=SPRITE_RICKSTART;
			}

			rk.Movement=rk.RIGHT;

			int k=4;
			rk.Hot.Set(k,3,23-k,23);

			rk.RenewRect();
			rk.RenewFrame();

		}
	}
	
}