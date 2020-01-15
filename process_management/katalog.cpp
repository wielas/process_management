#include "katalog.h"
#include <iostream>

string katalog::nazwa;
vector<short> katalog::numeryIwezlow;
short katalog::wskaznikNaOjca;
array<short, 32> katalog::wskaznikNaPodfolder;
short katalog::podfoldery;

katalog::katalog()
{
	nazwa.empty();
	podfoldery = 0; // podczas tworzenia brak podfolderow
	wskaznikNaOjca = -1; // brak ojca
	for (short wskaznik_na_syna : wskaznikNaPodfolder)
	{
		wskaznik_na_syna = -1; // brak synow czyli podfolderow
	}
}

katalog::katalog(string nazwa)
{
	nazwa = nazwa;
	wskaznikNaOjca = -1; //brak ojca
	for (int i = 0; i<wskaznikNaPodfolder.size(); i++)
	{
		wskaznikNaPodfolder[i] = -1; // brak synow czyli podfolderow
	}
}

katalog::katalog(string nazwa, short wskaznikNaOjca)
{
	nazwa = nazwa;
	wskaznikNaOjca = wskaznikNaOjca;
	for (int i = 0; i<wskaznikNaPodfolder.size(); i++)
	{
		wskaznikNaPodfolder[i] = -1;
	}
}

void katalog::wypiszKatalog()
{
	cout << " - nazwa: " << nazwa << endl;
	cout << " - i-wezyly w katalogu: " << endl;
	for (short element : numeryIwezlow)
	{
		cout << element << " ";//wyspisuje wszytskie iwezly zawarte w danym katalogu
	}
	cout << endl;;
}

void katalog::ustawNazwe(string nazwa)
{
	nazwa = nazwa;
}

string katalog::pobierzNazwe()
{
	return nazwa;
}

void katalog::dodajNumerIwezela(short numer)
{
	numeryIwezlow.push_back(numer);
}

void katalog::usunNumerIwezla(short numer)
{
	numeryIwezlow.erase(find(numeryIwezlow.begin(), numeryIwezlow.end(), numer) + 0);
}

vector<short> katalog::pobierzNumery()
{
	return numeryIwezlow;
}

void katalog::ustawOjca(short ojciec)
{
	wskaznikNaOjca = ojciec;
}

short katalog::pobierzOjca()
{
	return wskaznikNaOjca;
}

void katalog::ustawSyna(short syn)
{
	for (int i = 0; i<wskaznikNaPodfolder.size(); i++){
		if (wskaznikNaPodfolder[i] == -1){
			wskaznikNaPodfolder[i] = syn;
			break;
		}
	}
}

array<short, 32> katalog::pobierzSynow()
{
	return wskaznikNaPodfolder;
}

void katalog::usunSyna(short syn)
{
	for (int i = 0; i<wskaznikNaPodfolder.size(); i++){
		if (wskaznikNaPodfolder[i] == syn){
			wskaznikNaPodfolder[i] = -1;
		}
	}
}

short katalog::ilePodfolderow()
{
	return podfoldery;
}

void katalog::ustawPodfoldery(int i)
{
	podfoldery = i;
}