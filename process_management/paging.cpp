#include "paging.h"
#include <string>

tab_str_ram paging::ram;
int paging::adrPag;
int paging::offset;

paging::paging()
{
	tab_str_ram::tab_str_ram();
}


paging::~paging()
{
}

void paging::writeM(int pid, int adr, char data)
{
	convAdr(adr);
	ram.writeM(pid, adrPag, offset, data);
}

char paging::readM(int pid, int adr)
{
	convAdr(adr);
	return ram.readM(pid, adrPag, offset);
}

void paging::clearM(int pid)
{
	ram.clearM(pid);
}

void paging::display()
{
	ram.display();
}

void paging::convAdr(int adrL)
{
	adrPag = adrL / 16;
	offset = adrL % 16;
}