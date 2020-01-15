#include "tab_str_ram.h"
#include <iostream>

std::tuple<int, int, int>tab_str_ram::pageAr[32];
int tab_str_ram::rNr;
std::array<char, 512> tab_str_ram::ramAr;

tab_str_ram::tab_str_ram()
{
	for (int i = 0; i < 32; i++)
		pageAr[i] = std::make_tuple(-1, i, 0);
	for (int i = 0; i < 512; i++) {
		ramAr[i] = NULL;
	}
}

tab_str_ram::~tab_str_ram()
{
}

void tab_str_ram::removeP(int nr)
{
	for (int i = 0; i < 16; i++) {
		ramAr[(nr * 16) + i] = NULL;
	}
}


void tab_str_ram::writeM(int pid, int adrP, int offset, char data)
{
	if (checkPageArW(pid, adrP) == true) {

		if (offset == 0) {
			if (findMem() >= 0) {
				std::make_tuple(adrP, findMem(), pid);
			}
			else {
				std::string x = "brak wolnej pamieci";
				throw x;
			}
		}
		int x = findAdr(adrP, offset);
		ramAr[x] = data;
	}
	else if (findMem() >= 0) {

		pageAr[findMem()] = std::make_tuple(adrP, findMem(), pid);
		int x = findAdr(adrP, offset);
		ramAr[x] = data;
	}
	else {
		std::string x = "brak wolnej pamieci";
		throw x;
	}
}

char tab_str_ram::readM(int pid, int adrP, int offset)
{
	char val;
	if (checkPageArR(pid, adrP) == true) {
		val = ramAr[findAdr(adrP, offset)];
	}
	else {
		std::string x = "brak dostepu do pamieci";
		throw x;
	}
	return val;
}

void tab_str_ram::clearM(int pid)
{
	for (int i = 0; i < 32; i++)
		if (pid == std::get<2>(pageAr[i])) {
			pageAr[i] = std::make_tuple(-1, i, 0);
			removeP(i);
		}
}

void tab_str_ram::display()
{
	for (int i = 0; i < 32; i++) {
		if (i < 10)
			std::cout << "[" << i << "]  " << "|" << ramAr[i * 16] << "|" << ramAr[i * 16 + 1] << "|" << ramAr[i * 16 + 2] << "|" << ramAr[i * 16 + 3] << "|" << ramAr[i * 16 + 4]
			<< "|" << ramAr[i * 16 + 5] << "|" << ramAr[i * 16 + 6] << "|" << ramAr[i * 16 + 7] << "|" << ramAr[i * 16 + 8] << "|" << ramAr[i * 16 + 9] << "|" << ramAr[i * 16 + 10]
			<< "|" << ramAr[i * 16 + 11] << "|" << ramAr[i * 16 + 12] << "|" << ramAr[i * 16 + 13] << "|" << ramAr[i * 16 + 14] << "|" << ramAr[i * 16 + 15] << "|" << std::endl;
		else
		{
			std::cout << "[" << i << "] " << "|" << ramAr[i * 16] << "|" << ramAr[i * 16 + 1] << "|" << ramAr[i * 16 + 2] << "|" << ramAr[i * 16 + 3] << "|" << ramAr[i * 16 + 4]
				<< "|" << ramAr[i * 16 + 5] << "|" << ramAr[i * 16 + 6] << "|" << ramAr[i * 16 + 7] << "|" << ramAr[i * 16 + 8] << "|" << ramAr[i * 16 + 9] << "|"
				<< ramAr[i * 16 + 10] << "|" << ramAr[i * 16 + 11] << "|" << ramAr[i * 16 + 12] << "|" << ramAr[i * 16 + 13] << "|" << ramAr[i * 16 + 14] << "|"
				<< ramAr[i * 16 + 15] << "|" << std::endl;
		}
	}
	for (int i = 0; i < 32; i++) {
		if (std::get<0>(pageAr[i]) < 10) {
			std::cout << "| " << std::get<0>(pageAr[i]);
		}
		else {
			std::cout << "|" << std::get<0>(pageAr[i]);
		}
		if (std::get<1>(pageAr[i]) < 10)
		{
			std::cout << "| " << std::get<1>(pageAr[i]);
		}
		else
		{
			std::cout << "|" << std::get<1>(pageAr[i]);
		}
		if (std::get<2>(pageAr[i]) < 10)
		{
			std::cout << "| " << std::get<2>(pageAr[i]) << "|" << std::endl;
		}
		else {
			std::cout << "|" << std::get<2>(pageAr[i]) << "|" << std::endl;
		}
	}
}

bool tab_str_ram::checkPageArR(int pid, int adrP)
{
	for (int i = 0; i < 32; i++) {
		if ((std::get<0>(pageAr[i]) == adrP) 
			and (std::get<2>(pageAr[i]) == pid)) return true;
	}
	return false;
}

bool tab_str_ram::checkPageArW(int pid, int adrP)
{
	for (int i = 0; i < 32; i++) {
		if (((std::get<0>(pageAr[i]) == adrP) and (std::get<2>(pageAr[i]) == pid))) {
			return true;
		}
	}
	return false;
}


int tab_str_ram::findAdr(int adrP, int off)
{
	int rNr;
	for (int i = 0; i < 32; i++) {
		if ((std::get<0>(pageAr[i]) == adrP))
			rNr = std::get<1>(pageAr[i]);
	}
	return (rNr * 16) + off;
}

int tab_str_ram::findMem()
{
	for (int i = 0; i < 32; i++) {
		if (std::get<2>(pageAr[i]) == 0) return i;
	}
	return -1;
}