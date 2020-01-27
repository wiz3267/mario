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
	//���������� �� ���� ������� �����������
	for(int j=0; j<SHUFFLE_COUNT; j++)
	{
		int y=int(rk.y);
		y=rk.Rect.Top;

		//���������� ���������� �����������
		int cx=rk.Rect.Left/24, cy=y/24;
		int t=Level.ReadXY(rk.Rect.Left,y);
		//���� ��� ������ ���� �� �����������
		if ( t == (j | LEVEL::ALIEN| LEVEL::logTRANSP) )
		{
			//��������, ����� �� �������������
			// 		����
			// ����� ��� ����� ��� �����������
			// � ����� ���� ������ 6
			if (
			(Shuffle[j].Status & SHUFFLE::ALLMAP && MapCounter < 6)
							||
			//	���
			// ������������� ����� ������ ���� ���� ���,
			// � ���� �����
			(Shuffle[j].Status & SHUFFLE::BOSSLIVE && !BossLive)
							||
			//	���
			// ������������� ����� ������ ���� ���� �����,
			// � ���� ��� ���
			//   ����� ����������� ����������
			(Shuffle[j].Status & SHUFFLE::BOSSDEATH && BossLive)
			)
			{
				//���� ��� ������� ��������� ����������� � ����� ��� �� �������
				if ((Shuffle[j].Status & SHUFFLE::ALLMAP &&MapCounter < 6))
				{
					MOVETXT tx;
					//tx.Message="ELEMENTAL   REQUIRED";
					tx.Message="��������� �����";
					tx.Color=15;
					tx.x=(320-strlen(tx.Message)*8)/2;
					tx.y=50;
					tx.Speedy=0.1;
					tx.TimeLive=260;
					Movetxt.DelAll();
					Movetxt+=tx;
				}


				//���� ��������� ��� ������� �������� �����
				//� ��� ��� ���
				if ((Shuffle[j].Status & SHUFFLE::BOSSDEATH &&BossLive))
				{
					MOVETXT tx;
					//tx.Message="NO ENTRY HERE";
					tx.Message="����� ��� �����. ������ ������� �����";
					tx.Color=15;
					tx.x=(320-strlen(tx.Message)*8)/2;
					tx.y=50;
					tx.TimeLive=60;
					Movetxt.DelAll();
					Movetxt+=tx;
				}
			}

			//����� ����� �������������
			else
			{

				//******* 06 feb 2008 08:57 ************
				//���� ����������� �� ���������	 �������
				//if (LevelNumber != Shuffle[j].LevelNumber)
				if (Shuffle[j].Status & SHUFFLE::CHGLEVEL)
				{
					GameMode |= GAMEMODE_LOADLEVEL;
					GameMode |= GAMEMODE_RESTARTLEVEL;
					LevelNumber++;
					ColorEffect();
					break;
				}


				//���� ����������� �� ������ ����
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
				//���� �����, �� ������� ���� �������
				for(y1=0; y1<Level.MaxY+224; y1+=24)
				for(x1=0; x1<Level.MaxX+320; x1+=24)
				{
					int a=Level.ReadXY(x1,y1);
					if (a == (Shuffle[j].BoxCode | LEVEL::ALIEN | LEVEL::logTRANSP))
					{
						//���� ����� �����
						if ( a==t &&  (x1/24 != cx) && (y1/24 !=cy) )
						{
							//����� �� ������������ ������/
							//&&  (x1/24 != cx) && (y1/24 !=cy) )
							goto abcdef;
						}
						else if (a!=t) goto abcdef;
					}
				}
				//����� �� �����
				//fatal("       CANT TRANSFROM     ");
				{
					MOVETXT tx;
					//tx.Message="NO ENTRY HERE";
					tx.Message="������ �������������";
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

				//�������� ������
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
	
