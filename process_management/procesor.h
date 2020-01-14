#pragma once

#include "process_management.h"
#include <math.h>

extern vector<PCB*> PQ;


//class PCB
//{
//public:
//	int priority;
//	int PID;
//	State status;
//	int task_num;
//	int done_task_num;
//	float q;
//
//	PCB(int priority, int PID, State state, int task_num, int done_task_num, float q)
//	{
//		this->priority = priority;
//		this->PID = PID;
//		this->status = state;
//		this->task_num = task_num;
//		this->done_task_num = done_task_num;
//		this->q = q;
//	}
//
//	void set_priority(int prioritet)
//	{
//		priority = prioritet;
//	}
//
//	void set_PID(int pid)
//	{
//		PID = pid;
//	}
//
//	void set_state(State s)
//	{
//		status = s;
//	}
//
//	void set_task_num(int tsk_n)
//	{
//		task_num = tsk_n;
//	}
//
//	void set_done_task_num(int d_tsk_n)
//	{
//		done_task_num = d_tsk_n;
//	}
//
//	void set_q(float p)
//	{
//		q = p;
//	}
//};

PCB* running = NULL;//process obecnie running//prosic o deklaracje w konstruktorze jako null
bool czy_istnieje_running;//czy istnieje running jakikolwiek
int all_processes;//suma wszystkich procesow w kolejce
int all_priorities;//suma wszystkich priorytetow
int q_sum;//zmienna potrzebna do obliczen
int iteration;//zawiera iinformacje w ktorym miejscu kolejki jestesmy
int sumka;//zmienna ktora pomaga w przydziale procesora
PCB p(0, 0, INIT, 0, 0, 0); //wskaznik do obiektu pcb klasy procesu 
PCB* p1 = &p;
//std::vector<PCB*> PQ;//wektor procesow gotowych



void SetRunning()
{

	if (PQ.size() == 0)//jezeli nie ma zadnego procesu w kolejce uruchom INIT
	{

		PQ.push_back(p1);
		std::cout << "[CFS] " << "RUNNING = INIT" << std::endl; //opis co sie wykonuje 
		std::cout << "-------------------------------------------------------" << std::endl;

	}
	else
	{
		if (PQ[0]->status == INIT)//gdy istnieje juz INIT i jest to jedyny proces
		{

			if (PQ.size() == 1)//gdy init to jedyny proces w kolejce
			{
				std::cout << "[CFS] " << "STILL RUNNING INIT" << std::endl; //opis co sie wykonuje 
				std::cout << "-------------------------------------------------------" << std::endl;

			}
			if (PQ.size() != 1)//gdy init nie jest jedynym procesem w kolejce -> usun init
			{
				PQ.erase(PQ.begin());
			}
		}//TU MA W OGOLE NIE CHODZIC ;P
		else if (PQ[0]->status != INIT) //gdy nie ma init w QRP[0]
		{

			if (czy_istnieje_running == 1)//jezeli istnieje jakis running to:
			{
				q_sum = 0;
				all_priorities = 0;
				sumka = 0;//wyzerowanie sumki
				all_processes = PQ.size();
				for (int i = 0; i < all_processes; i++)
				{
					all_priorities = all_priorities + PQ[i]->priority;

				}
				std::cout << "All priorities=" << all_priorities << std::endl;
				for (int i = 0; i < all_processes; i++)
				{
					float s = (20 * (all_priorities / PQ[i]->priority));
					s = ((floor(s * 100)) / 100);
					PQ[i]->set_q(s);
					q_sum = q_sum + PQ[i]->q;
				}
				for (int i = 0; i < all_processes; i++)
				{
					int r = (((PQ[i]->q * 100) / q_sum) * 0.2);//moga wyskakiwac bledy z uwagi na floor
					r = r - PQ[i]->done_task_num;//ODEJMUJE DONE TASK NUM OD NOWEGO TASK NUM
					if (r <= 0) sumka++;//jezeli tasknum-donetasknum<=0 to sumka ++
					//mozliwe ze potrzebne rzutowanie na koniec do float
					PQ[i]->set_task_num(r);//na ile rozkazow proces dostal procesor -> NADPISUJE TASK NUM
					std::cout << "proces o pid:" << PQ[i]->PID << " dostal task num=" << PQ[i]->task_num << std::endl;
				}
				if (sumka != PQ.size())// jakis jest do wykonania
				{
					int min;
					//wybrac proces o najmniejszym priorytecie i task_num-done_task_num>0
					for (int i = 0; i < all_processes; i++)
					{
						if (PQ[i]->task_num > 0)
							min = PQ[i]->priority;//narazie jako minimum priorytet jakiejs iteracji ktora ma cos do wykonania
						std::cout << "proces o pid:" << PQ[i]->PID << " ma done task num=" << PQ[i]->done_task_num << std::endl;
					}
					for (int i = 0; i < all_processes; i++)
					{
						if ((PQ[i]->priority <= min) && (PQ[i]->task_num > 0))//jezeli jakas iteracja ma mniejszy priorytet, ustaw nowe minimum. 
						//a zmienna iteration na odpowiadajaca mu iteracje z tabeli qrp
						{
							min = PQ[i]->priority;
							iteration = i;//moze byc tak, albo ilosc wykonanych rozkazow tez jako pole w kklasie pcb
						}
					}

					//zobaczyc czy pcb runnning to null czy moze to ten sam czy inny
					//ubezpieczyc  sie na to ze ten proces juz jest running?
					if ((running == NULL) || (running != PQ[iteration]))//jezeli to pierwsze wywolanie lub inny proces niz wczesniej
					{
						std::cout << "[CFS] " << "RUNNING PROCESS WITH PID: " << PQ[iteration]->PID << std::endl; //opis co sie wykonuje
					}
					else if (running == PQ[iteration])
					{
						std::cout << "[CFS] " << "RUNNING STILL THE SAME PROCESS, WITH PID: " << PQ[iteration]->PID << std::endl; //opis co sie wykonuje
					}
					running = PQ[iteration];//zapisanie obiektu ktoremu zostal przydzielony procesor w zmiennej wskaznikowej 
					PQ[iteration]->set_state(RUNNING);//ustawic stan jako running
					int w = 0;
					w = PQ[iteration]->done_task_num;
					PQ[iteration]->set_done_task_num(w + 1);
					std::cout << "-------------------------------------------------------" << std::endl;
				}
			}
		}
		if (((PQ[0]->status != INIT)) && ((czy_istnieje_running == 0) || (sumka == PQ.size())))//jesli nie istnieje zaden running to rozpocznij. licznik bedzie sie plusowal
		{
			q_sum = 0;
			all_priorities = 0;
			all_processes = PQ.size();//ile procesow jest do podzialu procesora 
			for (int i = 0; i < all_processes; i++)
			{
				all_priorities = all_priorities + PQ[i]->priority;//jaka jest suma wszystkich priorytetow
			}
			for (int i = 0; i < all_processes; i++)
			{
				float s = (20 * (all_priorities / PQ[i]->priority));//obliczanie q dla obiektu
				s = ((floor(s * 100)) / 100);
				PQ[i]->set_q(s);//pole q musi byc polem klasy pcb
				q_sum = q_sum + PQ[i]->q;//pole q sum zaincluowane na gorze tego pliku
			}
			for (int i = 0; i < all_processes; i++)//obliczyc liczbe rozkazow przydzialu rocesora 
			{
				int r = floor((PQ[i]->q * 100) / q_sum);//moga wyskakiwac bledy z uwagi na floor
				//mozliwe ze potrzebne rzutowanie na koniec do float
				PQ[i]->set_task_num(r);//na ile rozkazow proces dostal procesor
				PQ[i]->set_done_task_num(0);//zaden rozkaz sie jeszcze nie wykonal w zadnej iteracji
			}
			int min;
			//wybrac proces o najmniejszym priorytecie
			for (int i = 0; i < all_processes; i++)
			{
				min = PQ[0]->priority;//narazie jako minimum priorytet 1 iteracji
				if (PQ[i]->priority < min)//jezeli jakas iteracja ma mniejszy priorytet, ustaw nowe minimum. 
					//a zmienna iteration na odpowiadajaca mu iteracje z tabeli qrp
				{
					min = PQ[i]->priority;
					iteration = i;//moze byc tak, albo ilosc wykonanych rozkazow tez jako pole w klasie pcb
				}
			}
			//zobaczyc czy pcb runnning to null czy moze to ten sam czy inny
			czy_istnieje_running = 1;//teraz juz istnieje running
			if ((running == NULL) || (running != PQ[iteration]))//jezeli to pierwsze wywolanie lub inny proces niz wczesniej
			{
				std::cout << "[CFS] " << "RUNNING PROCESS WITH PID: " << PQ[iteration]->PID << std::endl; //opis co sie wykonuje
			}
			else if (running == PQ[iteration])
			{
				std::cout << "[CFS] " << "RUNNING STILL THE SAME PROCESS, WITH PID: " << PQ[iteration]->PID << std::endl; //opis co sie wykonuje
			}
			running = PQ[iteration];//zapisanie obiektu ktoremu zostal przydzielony procesor w zmiennej wskaznikowej 
			PQ[iteration]->set_state(RUNNING);//ustawic stan jako running
			PQ[iteration]->set_done_task_num(1);
			std::cout << "-------------------------------------------------------" << std::endl;
		}
	}
}
