//
// Created by Celestyna on 09.01.2020.
//

#include <iostream>
#include "lock.h"
#include "process_management.h"
;
Lock::Lock()
{
    this->is_lock_open = true;
    this->who_closed_lock;
    this->processes_queue;
}

// informacja o stanie zamka //true - otwarty //false - zamkniety
bool Lock::get_is_open()
{
    return is_lock_open;
}

// informacja kto zajmuje zamek (czyli kto zamek zamknal - ten musi go otworzyc)
PCB* Lock::get_who_closed_lock()
{
    return who_closed_lock;
}

// informacja o rozmiarze kolejki
int Lock::get_processes_queue_size()
{
    return this->processes_queue.size();
}

// ustawianie stanu zamka // 1 lub 0 - true or false
void Lock::set_is_lock_open(bool state)
{
    this->is_lock_open = state;
}

// ustawianie pid (process identyficator) procesu zajmujacego zamek
void Lock::set_who_closed_lock(PCB* process)
{
    if (!this->is_lock_open) // jesli zamek jest zamkniety (is_open = false) oznacza to, ze jakis proces go zamknal - tutaj ustalamy ktory proces zamyka zamek
    {
        this->who_closed_lock = process;
        std::cout << "Proces o PID " << process->PID << " zamknal zamek.\n"; //praca krokowa - komunikat, ktory proces zamknal zamek
    }
    else std::cout << "Zamek otwarty"; //jesli zamek otwarty zatem is_open = true;
}

// dodawanie procesu na koniec kolejki
bool Lock::add_to_processes_queue(PCB *process)
{
    if (!this->is_lock_open)
    {
        this->processes_queue.push_back(process);
        return 1; //proces sie dodal do kolejki
    }
    else return 0; //funkcja zwraca czy proces dodal sie do kolejki, wiec jesli zamek byl otwarty to preces nie dodal sie do kolejki bo nie musial na nic czekac tylko mogl se dzialac
}

// usuwanie pid procesu z poczatku kolejki
PCB* Lock::remove_from_processes_queue()
{
    PCB* process = this->processes_queue.front();
    this->processes_queue.erase(processes_queue.begin());
    return process; // w tej f. nastepuje usuniecie procesu z kolejki (ktory czekal na swoja kolej by moc pracowac na danych wspoldzielonych - zostaje on wywolywany przez
    //poprzedzajacy go proces, ktory wlasnie otweozryl zamek) return jest po to zeby procesor wiedzial ktory proces zostal wybudzony czyli przeszedl to stanu gotowosci
}

// zamykanie zamka
void lock_lock(Lock *lock, PCB *process) //zamek zawsze jest wskaznikiem, proces tez (poniewaz zawsze musimy działac dynamicznie na danych)
{
    if (lock->get_is_open()) //jezeli zamek otwarty
    {
        lock->set_is_lock_open(false); //ustawia stan na false - zamknyka zamek
        lock->set_who_closed_lock(process);  //ustawia jaki proces go zamknal
        // proces wykonuje dzialania w sekcji krytycznej
    }

    else // jak zamek jest zamkniety
    {
        if (lock->get_who_closed_lock() != process) // jezeli jest zamkniety przez inny proces, niz ten ktory chce zaczac dzialac na wpoldzielonych danych
        {
            if (lock->add_to_processes_queue(process)) //jesli proces sie dodal do kolejki to
            {
                process->set_state(State::SLEEPING); //ustala stan procesu na oczekujacy (SLEEPING - stan procesu zdeklarowany w klasie PCB u Krzysia)
            }
            std::cout << "Zamek jest juz zamkniety. Proces o PID " << process->PID << " laduje w kolejce.\n";
        }
            // proces zmienia stan na waiting.
        else // moze sie zdarzyc, kiedy proces ktory zamknal zamek chce go znowusz zamknac
        {
			process->set_state(State::ZOMBIE); //proces przechodzi do stanu zatrzymania
			lock->set_is_lock_open(true);
			//unlock_lock(lock, &process); //123
            std::cout << "Blad systemu - Zamek jest juz zamkniety przez ten proces.\n";
        }
    }
}

// otwieranie zamka
void unlock_lock(Lock* lock, PCB* process)
{
    if (lock->get_is_open()) {
        std::cout << "Zamek jest juz otwarty.\n";
    } else {
        if (lock->get_processes_queue_size() > 0) //jezeli kolejka jest wieksza od 0 to
        {
            process = lock->remove_from_processes_queue(); // usuwa pierwszy proces z kolejki i zwraca ktory usunal
            process->set_state(State::READY); //ustala stan tego procesu na gotowosc READY (RUNNABLE - stan gotowosci)
            lock->set_who_closed_lock(process);
            std::cout << "Proces o PID " << process->PID << " ponownie zamknal zamek\n";
            if (lock->get_processes_queue_size() == 1)
                std::cout << "W kolejce oczekuje jeszcze 1 proces.\n";
            else
                std::cout << "W kolejce oczekuje jeszcze " << lock->get_processes_queue_size() << " procesow.\n";
        } else // jezeli kolejka jest rowna 0
        {
            if (lock->get_who_closed_lock() == process) {
                lock->set_is_lock_open(true); //otwieram zamek
                std::cout << "Brak procesow w kolejce. Otwieranie zamka.\n";
			}
			else
			{
				process->set_state(State::ZOMBIE);
				std::cout << "Blad Systemu - Proces o PID " << process->PID << " nie moze otworzyc zamka, poniewaz inny proces go zamknal!\n";
			}
        }

    }
}



