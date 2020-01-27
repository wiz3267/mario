//Mario4.cpp
#include "stdafx.h"
#include "total.h"

void SUPERMARIO::FunctionSpeed()
{
	ANIM ob;
	/*ob.Speedx=4.3;
	ob.Acceleratx=0.1;
	ob.Speedy=2.3;
	ob.Acceleraty=0.0001;*/


	Level.Load(0);

	while (1)
	{

	scr.clear();
	Msg(" SPEED CALCULATING ... ",9);
	Timer.Restart(100);
	unsigned long ComputerSpeed=0;
	int i=0;
	do
	{
		ComputerSpeed++;
		Level.Show(i,i);
		i++;
	} while (Timer.Counter<100);

	scr<<cur(0,0)<<ComputerSpeed;
	Msg("     Press any key     ");

	scr.update();

	if (Keyb.ReadScan() == KEY_ESC) break;
	}

	return;

}


void SUPERMARIO::Teleport(int i,PERSON &rk)
{
	//проходимся по всей таблице перемещений
	for(int j=0; j<SHUFFLE_COUNT; j++)
	{
		int y=int(rk.y);
		y=rk.Rect.Top;

		//запоминаем координаты перемещения
		int cx=rk.Rect.Left/24, cy=y/24;
		int t=Level.ReadXY(rk.Rect.Left,y);
		//если под ногами одно из перемещений
		if ( t == (j | LEVEL::ALIEN| LEVEL::logTRANSP) )
		{
			//проверка, можно ли переместиться
			// 		ЕСЛИ
			// нужна вся карта для перемещения
			// и число карт меньше 6
			if (
			(Shuffle[j].Status & SHUFFLE::ALLMAP && MapCounter < 6)
							||
			//	или
			// переместиться можно только если босс жив,
			// а босс погиб
			(Shuffle[j].Status & SHUFFLE::BOSSLIVE && !BossLive)
							||
			//	или
			// переместиться можно только если босс погиб,
			// а босс еще жив
			//   тогда перемещение НЕВОЗМОЖНО
			(Shuffle[j].Status & SHUFFLE::BOSSDEATH && BossLive)
			)
			{
				//ЕСЛИ ДЛЯ ПРОХОДА ТРЕБУЕТСЯ ПЕРЕМЕЩЕНИЕ А КАРТА ЕЩЕ НЕ СОБРАНА
				if ((Shuffle[j].Status & SHUFFLE::ALLMAP &&MapCounter < 6))
				{
					MOVETXT tx;
					//tx.Message="ELEMENTAL   REQUIRED";
					tx.Message="ТРЕБУЕТСЯ КАРТА";
					tx.Color=15;
					tx.x=(320-strlen(tx.Message)*8)/2;
					tx.y=50;
					tx.Speedy=0.1;
					tx.TimeLive=260;
					Movetxt.DelAll();
					Movetxt+=tx;
				}


				//ЕСЛИ ТРЕБУЕТСЯ ДЛЯ ПРОХОДА ЗАГАСИТЬ БОССА
				//А БОС ЕЩЕ ЖИВ
				if ((Shuffle[j].Status & SHUFFLE::BOSSDEATH &&BossLive))
				{
					MOVETXT tx;
					//tx.Message="NO ENTRY HERE";
					tx.Message="ЗДЕСЬ НЕТ ВХОДА. УБЕЙТЕ ВНАЧАЛЕ БОССА";
					tx.Color=15;
					tx.x=(320-strlen(tx.Message)*8)/2;
					tx.y=50;
					tx.TimeLive=60;
					Movetxt.DelAll();
					Movetxt+=tx;
				}
			}

			//иначе можно переместиться
			else
			{

				//******* 06 feb 2008 08:57 ************
				//если перемещение на следующий	 уровень
				//if (LevelNumber != Shuffle[j].LevelNumber)
				if (Shuffle[j].Status & SHUFFLE::CHGLEVEL)
				{
					GameMode |= GAMEMODE_LOADLEVEL;
					GameMode |= GAMEMODE_RESTARTLEVEL;
					LevelNumber++;
					ColorEffect();
					break;
				}


				//если перемещение на другой файл
				//if (LevelNumber != Shuffle[j].LevelNumber)
				if (Shuffle[j].Status & SHUFFLE::CHGLEVEL)
				{
					GameMode |= GAMEMODE_LOADLEVEL;
					GameMode |= GAMEMODE_RESTARTLEVEL;
					LevelNumber=Shuffle[j].LevelNumber;
					//MidiStop();
					ColorEffect();
					//Level.Load(LevelNumber);
					break;
				}

				int x1,y1;
				//ищем кубик, на который надо перейти
				for(y1=0; y1<Level.MaxY+224; y1+=24)
				for(x1=0; x1<Level.MaxX+320; x1+=24)
				{
					int a=Level.ReadXY(x1,y1);
					if (a == (Shuffle[j].BoxCode | LEVEL::ALIEN | LEVEL::logTRANSP))
					{
						//если тотже кубик
						if ( a==t &&  (x1/24 != cx) && (y1/24 !=cy) )
						{
							//чтобы не перемещались тудаже/
							//&&  (x1/24 != cx) && (y1/24 !=cy) )
							goto abcdef;
						}
						else if (a!=t) goto abcdef;
					}
				}
				//иначе не нашли
				//fatal("       CANT TRANSFROM     ");
				{
					MOVETXT tx;
					//tx.Message="NO ENTRY HERE";
					tx.Message="НЕКУДА ПЕРЕМЕСТИТЬСЯ";
					tx.Color=15;
					tx.x=(320-strlen(tx.Message)*8)/2;
					tx.y=50;
					tx.TimeLive=120;
					Movetxt.DelAll();
					Movetxt+=tx;
					break;
				}

		abcdef:

				OldMarioX=x1+12;
				OldMarioY=y1;
				GameMode |= GAMEMODE_RESTARTLEVEL;
				Keyb.clear();

				//включаем защиту
				rk.Status |= MARIO_PROTECTED;
				ProtectedCounter=50;
				Sound.play(SND_HEALTH);

				scr.SaveScreen();
				ChangeEffect=1;
				//ColorEffect();
				break;
			} //end else
		}  //endif
	} //end for
}
	
