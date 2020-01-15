#pragma once
#include <string>
#include <vector>
#include <array>
#include <iostream>
using namespace std;


class katalog
{
public:
	katalog();
	katalog(string nazwa);
	katalog(string nazwa, short wskaznikNaOjca);
	static void wypiszKatalog();
	static void ustawNazwe(string nazwa);
	static string pobierzNazwe();
	static void dodajNumerIwezela(short numer); // Dodaje przekazany numer iWezela do kolekcji numeryIwezlow
	static void usunNumerIwezla(short numer); // Usuwa przekazany numer z kolejcji numeryIwezlow
	static vector<short> pobierzNumery(); // Zwraca kolekcje numeryIwezlow
	static void ustawOjca(short ojciec);
	static short pobierzOjca();
	static void ustawSyna(short syn);
	static array<short, 32> pobierzSynow(); // Zwraca kolekcj� podfolder�w
	static void usunSyna(short syn);
	static short ilePodfolderow();
	static void ustawPodfoldery(int i);
private:
	static string nazwa;
	static vector<short> numeryIwezlow; // vektor przechowujacy numery i-wezlow w katalogu
	static short wskaznikNaOjca;
	static array<short, 32> wskaznikNaPodfolder; // folder moze miec podfoldery
	static short podfoldery;
};