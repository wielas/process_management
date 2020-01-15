#pragma once
#include <iostream>
using namespace std;

class iWezel
{
public:
	iWezel();
	static void wypiszIwezel();

#pragma region operacje na zmmiennych prywatnych
	static void czysc(); // Zwalnianie struktury

	static void ustawRozmiarPliku(short rozmiar);
	static int pobierzRozmiarPliku();

	static void ustawPierwszyBlok(short blok);
	static short pobierzPierwszyBlok();

	static void ustawDrugiBlok(short blok);
	static short pobierzDrugiBlok();

	static void ustawIndeksowyBlok(short blok);
	static short pobierzIndeksowyBlok();
#pragma endregion operacje na zmmiennych prywatnych

private:
	static int rozmiarPliku;
	static short pierwszyBlok;
	static short drugiBlok;
	static short indeksowyBlok;
};