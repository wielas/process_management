#pragma once
#include <array>
#include "iwezel.h"
#include "katalog.h"
#include "wpisKatalogowy.h"
class dysk
{
public:
	dysk();
	//aby wpisac dane na dysk nalezy najpierw wywolac funkcje 'utworzPlik' (tworzy pusty), a nastepnie 'zapiszDoPliku', aby zapisal dane
	static void utworzPlik(string nazwa, string rozszerzenie, string nazwaFolderu ); //funkcja zajmuje jeden blok dyskowy i tworzy  iwezel i wpis katalogowy
																			  //na poczatu za nazwe folderu nalezy podac "Dysk"
	static void zapiszDoPliku(string nazwa, string rozszerzenie, string dane, string nazwaFolderu ); //funkcja wpisuje odpowiedniu dane na bloki dyskowe
	static void usunPlik(string nazwa, string rozszerzenie, string nazwaFolderu); // funkcja zwalnia bloki, czy�ci wpis na dysku
	static void utworzFolder(string nazwa, string nazwaNadrzednego); // funkcja tworzy folder podrz�dny w danym folderze 
	static void dodajPlikDoKatalogu(string nazwaDolcelowego, string nazwaPliku, string rozszerzenie, string nazwaFolderuZPlikiem ); //dodawanie pliku do katalogu
	static void usunFolder(int pozycja);// funkcja usuwajaca katalog o danej pozycji wywolywanie razem z 'znajdzFolder',np: dysk.usunFolder(dysk.znajdzFolder("nowyFolder"));
	static short znajdzFolder(string nazwa); //funckja zwraca miejsce w tablicy folderow/klatalogow
	static void wypiszDrzewo(); // funkcja wypisuje wszytkie informacje i plikach i katalogach
	static void wypiszDysk(); // funkcja wypisuje na konsole wypelniony dysk
	static void wypiszWektorBitowy(); //funkcja wypisuje na  konsole wektor bitowy
	static void wypiszTabliceIwezelow(); //funkcja wypisuje na konsole tablice i-ewzlow
	static void wypiszTabliceWpisow();// funkcja wypisuje na konsole tablice aktualnych wpoisow
private:
	static array<iWezel, 32> tablicaIwezlow; // tablica przechowujaca i-wezly
	static array<char, 1024> tablicaDysk; // rzeczywisty 'dyk'
	static array<katalog, 1024> tablicaKatalogow; //tablica przechowujaca katalogi/foldery
	static array<wpis, 32> tablicaWpisow; // tablica przechowujaca wpisy
	static array<bool, 32> wektorBitowy; // tablica mowiaza to dostepomnosci miejsca na bloku dyskowym ->1 Blok wolny, 0 Blok zaj�ty
	static short wielkoscBloku; //deklaracja wielkosci bloku
	static int wielkoscDysku; //deklaracja wielkosci dysku
	static short wolneBloki;  //itp
	static int ileFolderow;
	static void ileWolnych();//funkcja mowiaca o ilosci wolnych blokow indeksowych
	static short znajdzPlik(string nazwa, string rozszerzenie); // funkcja zwraca numer i-wez�a w kt�rym znajduje si� plik, je�li plik nie istenieje -1
	static short znajdzWolnyBlok(); // funkcja zwracajca numer pierwszego wolnego bloku na dysku, je�li brak zwraca -1
	static short znajdzIwezel(); // funkcja zwracajaca numer pierwszego wolnego i-w�z�a, je�li brak zwraca -1
	static string pobierzNazweFolder(short pom); //funjca zwracajca nazwe folderu, kiedy za argument podajmy pozycje w tablicy katalogow
};