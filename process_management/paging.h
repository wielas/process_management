#pragma once
#include <string>
#include <bitset>
#include "tab_str_ram.h"
class paging
{
	static tab_str_ram ram;
	static int adrPag, offset;
	static void convAdr(int adrL);									//zamiana adresu logicznego na fizyczny( zwraca adresz fizyczny, numer stronicy i offset)
public:
	paging();
	~paging();
	static void writeM(int pid, int adr, char data);				//zapis
	static char readM(int pid, int adr);							//odczyt
	static void clearM(int pid);									//wywolanie przy usuwaniu procesu (czyszczenie pamieci z wszelkich danych procesu)
	static void display();
};