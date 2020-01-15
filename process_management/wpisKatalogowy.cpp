#include "wpisKatalogowy.h"
#include <iostream>

string wpis::nazwa;
string wpis::rozszerzenie;
short wpis::numerIwezela;

wpis::wpis()
{
	nazwa.empty();
	rozszerzenie.empty();
	numerIwezela = -1;
}

wpis::wpis(string nazwa, string rozszerzenie, short numer)
{
	nazwa = nazwa;
	rozszerzenie = rozszerzenie;
	numerIwezela = numer;
}

void wpis::czysc()
{
	nazwa.empty();
	rozszerzenie.empty();
	numerIwezela = -1;
}

void wpis::wypisz()
{
	cout << " - nazwa pliku: " << nazwa << endl;
	cout << " - rozszerzenie pliku: " << rozszerzenie << endl;
	cout << " - iwezel pliku: " << numerIwezela << "\n";

}

void wpis::ustawNazwe(string nazwa)
{
	nazwa = nazwa;
}

string wpis::pobierzNazwe()
{
	return nazwa;
}

void wpis::ustawRozszrzenie(string rozszerzenie)
{
	rozszerzenie = rozszerzenie;
}

string wpis::pobierzRozszerzenie()
{
	return rozszerzenie;
}

void wpis::ustawNumerIwezla(short numer)
{
	numerIwezela = numer;
}

short wpis::pobierzNumer()
{
	return numerIwezela;
}