#pragma once
#include <string>
#include <array>
class tab_str_ram											//---wywolywanie wszystkiego za pomoca klasy paging---//
{
	static std::tuple<int, int, int>pageAr[32];					//tablica stron (pozycja: 0 - identyfikator strony, 1 - identyfikator ramki, 2 - identyfikator procesu (jesl 0 ramka wolna))
	static int rNr;
	static std::array<char,512> ramAr;								//pamiec podzialona na 32 ramki o rozmiarze 16 znakow
	static void removeP(int nr);
public:
	tab_str_ram();
	~tab_str_ram();
	static char readM(int pid, int adrP, int offset);				//odczyt z pamieci
	static void writeM(int pid, int adrP, int offset, char data);	//zapis do pamieci
	static void clearM(int pid);									//usuwanie z pamieci danych dla danego procesu
	static void display();											//wyswietlanie obrazu pamieci
	static bool checkPageArR(int pid, int adrP);					//kontrola tablicy stron dla odczytu
	static bool checkPageArW(int pid, int adrP);					//kontrola tablicy stron dla zapisy
	static int findAdr(int adrP, int off);							//funkcja do odnajdywania komorki o danym adresie
	static int findMem();											//funkcja do odnajdywania wolnych ramek
};