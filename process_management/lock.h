//
// Created by Celestyna on 09.01.2020.
//
#pragma once
#include <queue>
#include <vector>
#include "process_management.h" // z tego pliku (od Krzysia) klasa Lock i jej funkcje beda pobierać klase PCB

class Lock
{
public:

    bool is_lock_open; // informacja czy zamek jest zamkniety czy otwarty | 0 - zamkniety, 1 - otwarty
    PCB* who_closed_lock; // Zmienna mowiaca ktory proces zamknal zamek, PCB - identyfikator procesu
    std::vector<PCB*> processes_queue; //kolejka przechowująca oczekujace procesy



    Lock(); // konstruktor domyślny klasy Lock

    bool get_is_open();

    PCB* get_who_closed_lock(); //funkcja pobiera informacje o tym kto zamknal zamek - przydatne przy wybudzaniu, gdyz tylko ten proces ktory zamek zamknal moze go otworzyc

    int get_processes_queue_size(); //pobiera rozmiar kolejki - jesli wiekszy od 0 to zamek jest ciagle zamkniety tylko zmienia "proces-klucznika", a jezeli rowny 0, to otwiera zamek

    void set_is_lock_open(bool b); //ustawia stan zamka

    void set_who_closed_lock(PCB* process); //ustawia kto zamknal zamek - to bardzo wazne zeby wiedziec ktory proces ostatnio był procesem-klucznikiem

    bool add_to_processes_queue(PCB *process); // dodaj proces do kolejki (ten co chce zamknac i nie moze (bo ktos inny zamyka), czyli oczekuje)

    PCB* remove_from_processes_queue(); //usuwa z kolejki pierwszy proces ktory czekal na przydział do danych wspoldzielonych - ten proces ropoczyna operacje zamykania zamka

};


void lock_lock(Lock *lock, PCB *process); // zamykanie zamka

void unlock_lock(Lock *lock, PCB *process); //otwieranie zamka

void unlock(Lock *lock, PCB *process);
