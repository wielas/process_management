#pragma once
#include <string>
#include <iostream>
using namespace std;

class wpis
{
public:
	wpis();
	wpis(string nazwa, string rozszerzenie, short numer);
	static void czysc();
	static void wypisz();
	static void ustawNazwe(string nazwa);
	static string pobierzNazwe();
	static void ustawRozszrzenie(string rozszerzenie);
	static string pobierzRozszerzenie();
	static void ustawNumerIwezla(short numer);
	static short pobierzNumer();
private:
	static string nazwa;
	static string rozszerzenie;
	static short numerIwezela;
};