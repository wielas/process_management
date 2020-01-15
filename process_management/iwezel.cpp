#include "iwezel.h"
#include <cstdio>

int iWezel::rozmiarPliku;
short iWezel::pierwszyBlok;
short iWezel::drugiBlok;
short iWezel::indeksowyBlok;

iWezel::iWezel()
{
	indeksowyBlok = -1;
	rozmiarPliku = 0;
	pierwszyBlok = -1;
	drugiBlok = -1;
	
}

void iWezel::wypiszIwezel()
{
	cout << " - blok indeksowy: " << indeksowyBlok << endl;
	cout << " - pierwszy bezposredni blok: " << pierwszyBlok << endl;
	cout << " - drugi bezposredni blok: " << drugiBlok << endl;
	cout << " - rozmiar pliku: " << rozmiarPliku << endl;
	
}

void iWezel::czysc()
{
	rozmiarPliku = 0;
	pierwszyBlok = -1;
	drugiBlok = -1;
	indeksowyBlok = -1;
}

void iWezel::ustawRozmiarPliku(short rozmiar)
{
	rozmiarPliku = rozmiar;
}

int iWezel::pobierzRozmiarPliku()
{
	return rozmiarPliku;
}

void iWezel::ustawPierwszyBlok(short blok)
{
	pierwszyBlok = blok;
}

short iWezel::pobierzPierwszyBlok()
{
	return pierwszyBlok;
}

void iWezel::ustawDrugiBlok(short blok)
{
	drugiBlok = blok;
}

short iWezel::pobierzDrugiBlok()
{
	return drugiBlok;
}

void iWezel::ustawIndeksowyBlok(short blok)
{
	indeksowyBlok = blok;
}

short iWezel::pobierzIndeksowyBlok()
{
	return indeksowyBlok;
}
