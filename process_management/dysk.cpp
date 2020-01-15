#include "dysk.h"
#include "iostream"
#include "lock.h"

array<iWezel, 32> dysk::tablicaIwezlow;
array<char, 1024> dysk::tablicaDysk;
array<katalog, 1024> dysk::tablicaKatalogow;
array<wpis, 32> dysk::tablicaWpisow;
array<bool, 32> dysk::wektorBitowy;
short dysk::wielkoscBloku;
int dysk::wielkoscDysku;
short dysk::wolneBloki;
int dysk::ileFolderow;


dysk::dysk()
{
	wolneBloki = 32; //ustawianie wolnych blokow dyskowych na 32
	wielkoscBloku = 32; //ustawianie wielkosci bloku na 32
	wielkoscDysku = 1024; //ustawianie wilkosci dysku na 1024
	ileFolderow = 0; // na poczatku 0 folderow
	for (int i = 0; i<wektorBitowy.size(); i++){
		wektorBitowy[i] = '1'; //ustawianie wektora bitowego na 1 (1-puste, 0-zajete)
	}
	for (int i = 0; i<tablicaDysk.size(); i++){
		tablicaDysk[i] = '0'; // ustawianie pustego dysku - same '0'
	}
	katalog katalog("Dysk");
	tablicaKatalogow[ileFolderow] = katalog;
	ileFolderow++;//po zainicjalizowaniu folderow zwieksza ich ilosc

}

void dysk::utworzPlik(string nazwa, string rozszerzenie, string nazwaFolderu) //funkcja zajmuje jeden blok dyskowy i tworzy  iwezel i wpis katalogowy
{
	vector<short> pom = tablicaKatalogow[znajdzFolder(nazwaFolderu)].pobierzNumery();//wektor nr folderow z katalogu
	if (znajdzFolder(nazwaFolderu) == -1){
		cout << "Nie znaleziono folderu" << endl;
	}
	if (znajdzPlik(nazwa, rozszerzenie) == -1 && znajdzFolder(nazwaFolderu) != -1) {// jest folder nie ma pliku

		if (wolneBloki != 0){//jezeli wolne bloki
			Lock *l = new Lock();
			short iWezel = znajdzIwezel();//pomocnicze
			tablicaKatalogow[znajdzFolder(nazwaFolderu)].dodajNumerIwezela(iWezel);//dodanie nr iwezla do tablicy kat
			wektorBitowy[znajdzWolnyBlok()] = false; // zmiana wektora bitowego na zajety
			tablicaIwezlow[iWezel].ustawPierwszyBlok(znajdzWolnyBlok());//istawianie pierwszego bloku
			tablicaIwezlow[iWezel].ustawRozmiarPliku(0);//ustawianie rozmiru-na poczatku o
			tablicaWpisow[iWezel].ustawNazwe(nazwa);//ustawianie nazwy
			tablicaWpisow[iWezel].ustawNumerIwezla(iWezel);//ustawianie i-wezla
			tablicaWpisow[iWezel].ustawRozszrzenie(rozszerzenie); //ustawianie rozszerzenia 
			wolneBloki--;//mniejszanie ilosci wolnych blokow
		}
		else { 
			cout << "Brak miejsca" << endl;
		}
	}
}

void dysk::zapiszDoPliku(string nazwa, string rozszerzenie, string dane, string nazwaFolderu)
{
	short pozycjaPliku = znajdzPlik(nazwa, rozszerzenie);
	short pozycjaFolderu = znajdzFolder(nazwaFolderu);
	if (znajdzPlik(nazwa, rozszerzenie) == -1){//jesli nei znaleziono pliku
		cout << "Nie znaleziono pliku o podanej nazwie" << endl;
	}
	if (znajdzFolder(nazwaFolderu) == -1){//jesli nie znaleziono folderu
		cout << "Nie znaleziono folderu o podnaej nazwie" << endl;
	}
	if (znajdzPlik(nazwa, rozszerzenie) != -1 && znajdzFolder(nazwaFolderu) != -1){//jesli znaleziono plik i folder
		for (int i = 0; i<dane.length(); i++){//rob tak dlugo jak dlugie sa dane
			if (tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() < 32){ //pierwszy przypadek jesli dane maja miec 32 bity, jeden bezposredni wskaznik na blok dyskowy
				tablicaDysk[tablicaIwezlow[pozycjaPliku].pobierzPierwszyBlok()*wielkoscBloku + tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku()] = dane[i]; //wypelnianie dysku znak pozaku
				tablicaIwezlow[pozycjaPliku].ustawRozmiarPliku(tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() + 1); //powiekszanie rozmairu pliku o jeden
			}
			if (tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() >= 32 && tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() < 64){// II przypadek , 2 bepodrenie bloki
				if (tablicaIwezlow[pozycjaPliku].pobierzDrugiBlok() == -1) { // rezerwacja II bloku -> jak nie jest zarezerwowany
					short blok = znajdzWolnyBlok();//szukanie wolnego bloku
					wektorBitowy[blok] = false; // zmiana wektora bitowego na danym polu na zajety czyli 0
					tablicaIwezlow[pozycjaPliku].ustawDrugiBlok(blok);//zmienianie tablicy iwezlow, ustawianie 2 bloku
					i++;
					wolneBloki--;//zmniejszanie liczby wolnych blokow
				}
				tablicaDysk[tablicaIwezlow[pozycjaPliku].pobierzDrugiBlok()*wielkoscBloku + tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() % wielkoscBloku] = dane[i]; //to samo co w pierszym
				tablicaIwezlow[pozycjaPliku].ustawRozmiarPliku(tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() + 1);//to samo co w pierwszym
			}
			if (tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() >= 64){ //ostatni przypadek, 2 bezporedenie wskazniki a reszta na blok indeksowy
				int pomocniczaPozycjaDoZapisu = 0;
				if (tablicaIwezlow[pozycjaPliku].pobierzIndeksowyBlok() == -1){ // zarezerwowanie bloku indeksowego --> najblizszy jaki jest
					wolneBloki--;//zmniejszanie liczby wolnych blokow
					short wolnyBlok = znajdzWolnyBlok();
					wektorBitowy[wolnyBlok] = false; // zmiana wektora bitowego na danym polu na zajety czyli 0
					tablicaIwezlow[pozycjaPliku].ustawIndeksowyBlok(wolnyBlok);
					for (int j = wolnyBlok * wielkoscBloku; j<  wolnyBlok*wielkoscBloku + 32; j++){
						tablicaDysk[j] = -1;//reszta dysku w bloku indeksowym wypelnione -1
					}
					i++;
				}
				if (tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() % 32 == 0){ // nalezy poszukac nastepny blok na dane
					//szuka bloku zacyna od poczatku nowego bloku a konczy na koncu bloku bo jest podzielny przez 32
					for (int j = tablicaIwezlow[pozycjaPliku].pobierzIndeksowyBlok()*wielkoscBloku; j<tablicaIwezlow[pozycjaPliku].pobierzIndeksowyBlok()*wielkoscBloku + 32; j++){
						if (tablicaDysk[j] == -1){// jesli napotka -1 to nzak ze to jest tablica indeksowa
							short blok = znajdzWolnyBlok();
							wektorBitowy[blok] = false; // zmiana wektora bitowego na danym polu na zajety czyli 0
							tablicaDysk[j] = blok;
							wolneBloki--;//zmniejszanie liczby wolnych blokow
							break;
						}
					}
				}
				for (int k = tablicaIwezlow[pozycjaPliku].pobierzIndeksowyBlok()*wielkoscBloku; k<tablicaIwezlow[pozycjaPliku].pobierzIndeksowyBlok()*wielkoscBloku + 31; k++){
					if (tablicaDysk[k] != -1 && tablicaDysk[k + 1] == -1){
						pomocniczaPozycjaDoZapisu = tablicaDysk[k];
					}
				}
				tablicaDysk[pomocniczaPozycjaDoZapisu*wielkoscBloku + tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku() % wielkoscBloku] = dane[i];//wypelnia dysk
				tablicaIwezlow[pozycjaPliku].ustawRozmiarPliku(tablicaIwezlow[pozycjaPliku].pobierzRozmiarPliku()+1);//powiekszenie rozmiaru pliku o jeden
			}
		}
	}
}

void dysk::usunPlik(string nazwa, string rozszerzenie, string nazwaFolderu)
{
	if (znajdzPlik(nazwa, rozszerzenie) == -1){//sprawdzanie czy isteniejeplik/katalog o danej nazwie
		cout << "Nie znaleziono pliku o podanej nazwie" << endl;
	}
	if (znajdzFolder(nazwaFolderu) == -1){
		cout << "Nie znaleziono folderu o podanej nazwie" << endl;
	}
	if (znajdzPlik(nazwa, rozszerzenie) != -1 && znajdzFolder(nazwaFolderu) != -1){ //jezli isteje plik/katalog o danej nazwie
		//lock_lock()
		tablicaDysk[tablicaIwezlow[znajdzPlik(nazwa, rozszerzenie)].pobierzPierwszyBlok() * 32] = '0';//ustawianie danego miejsca w tablicy dyskowej na 0
		wektorBitowy[tablicaIwezlow[znajdzPlik(nazwa, rozszerzenie)].pobierzPierwszyBlok()] = true;// uzupenienie wektora bitowego w odpowiendim miejcu na wolny czyli true czyli 1
		tablicaIwezlow[znajdzPlik(nazwa, rozszerzenie)].czysc();//czysczenie odpowiedniego miejsca w tablicy iwezlow
		tablicaWpisow[znajdzPlik(nazwa, rozszerzenie)].czysc();//czysczenie odpowiedniego miejsca w tablicy wpisow
		tablicaKatalogow[znajdzFolder(nazwaFolderu)].usunNumerIwezla(znajdzPlik(nazwa, rozszerzenie)); //usuwanie nr iwezla w tablicy katalogow
		wolneBloki++; //po usunieciu zwiekszam liczbe wolnych blokow
	}
}

void dysk::utworzFolder(string nazwa, string nazwaNadrzednego)
{

	if (znajdzFolder(nazwaNadrzednego) != -1 && znajdzFolder(nazwa) == -1){
		if (tablicaKatalogow[znajdzFolder(nazwaNadrzednego)].ilePodfolderow() == 31){ //sprawdzanie czy jest miejsce na foldery podrzedne
			cout << "Brak miejsca na zrobienie folderow podrzednych"<<endl;
		}
		katalog katalog(nazwa, znajdzFolder(nazwaNadrzednego));
		tablicaKatalogow[ileFolderow] = katalog;
		++ileFolderow; //zwiekszanie liczby folderow po utworzeniu
	}
	else {
		cout << "Niepoprawna nazwa foleru" << endl;
	}
	tablicaKatalogow[znajdzFolder(nazwa)].ustawOjca(znajdzFolder(nazwaNadrzednego)); //ustawianie folderu nadrzednego  dla folderu
	tablicaKatalogow[znajdzFolder(nazwaNadrzednego)].ustawSyna(znajdzFolder(nazwa)); //ustawianie syna dla folderu nadrzednego
	tablicaKatalogow[znajdzFolder(nazwaNadrzednego)].ustawPodfoldery(tablicaKatalogow[znajdzFolder(nazwaNadrzednego)].ilePodfolderow()+1);//tworzy sie folder podrzedny dla jakiegos folderu

}

void dysk::dodajPlikDoKatalogu(string nazwaDolcelowego, string nazwaPliku, string rozszerzenie, string nazwaFolderuZPlikiem)
{
	int pozycjaKataloguZPlikiem = znajdzFolder(nazwaFolderuZPlikiem);
	int pozycjaKataloguDocelowego = znajdzFolder(nazwaDolcelowego);
	int pozycjaPliku = znajdzPlik(nazwaPliku, rozszerzenie);
	if (pozycjaKataloguZPlikiem == -1 || pozycjaKataloguDocelowego == -1){//wyjatki
		cout << "Niepoprawna nazwa katalogu" << endl;
	}
	if (pozycjaPliku == -1){
		cout << "Nie znaleziono danego pliku"<<endl;
	}
	if (pozycjaKataloguZPlikiem != -1 && pozycjaPliku != -1){//jesli plik istenije
		tablicaKatalogow[pozycjaKataloguDocelowego].dodajNumerIwezela(znajdzPlik(nazwaPliku, rozszerzenie));//dodawanie nr iwezla danego pliku do odpowiednigo miejsca w tablicy katalogow na miejscu docelowym
		tablicaKatalogow[pozycjaKataloguZPlikiem].usunNumerIwezla(znajdzPlik(nazwaPliku, rozszerzenie)); //usuniecie nr iwezla danego pliku z odpowiedniego miejsca w tablicy katalogow z mijeca na kotrym byl wczesniej
	}
}

void dysk::usunFolder(int jaki)  // funkcja usuwajaca katalog o danej pozycji 
//wywolywanie razem z 'znajdzFolder',np: dysk.usunFolder(dysk.znajdzFolder("nowyFolder"));
{
	if (znajdzFolder(pobierzNazweFolder(jaki)) != -1) { //jesli folder istenije
		tablicaKatalogow[tablicaKatalogow[jaki].pobierzOjca()].usunSyna(jaki);//usuwam foldery podrzedne
		array<short, 32> folderyPodrzedne = tablicaKatalogow[jaki].pobierzSynow(); //podfoldery wkladam do pomocnieczej tablicy folderyPodrzedne
		vector<short> iWezly = tablicaKatalogow[jaki].pobierzNumery(); //vektor z numerami i-wezlow
		int gdzieOjciec = tablicaKatalogow[jaki].pobierzOjca();
		for (int i = 0; i < iWezly.size(); i++){
			usunPlik(tablicaWpisow[iWezly[i]].pobierzNazwe(), tablicaWpisow[iWezly[i]].pobierzRozszerzenie(), pobierzNazweFolder(jaki));//usunPlik(nazwa,rozserzenie,nazwa folderu nadrzednego)
			//pobiera nazwe z tab wpisw, pobiera rozszerzenie z tab wpisow oraz nazwe folderu
		}
		katalog katalog = tablicaKatalogow[jaki];
		for (int i = 0; i < folderyPodrzedne.size(); i++){
			if (folderyPodrzedne[i] != -1) {
				usunFolder(folderyPodrzedne[i]);//usuwanie folderu podrzednego jesli istenieje
			}
		}
		ileFolderow--; // zmiejszam ilosc isteniejacych folderow
		tablicaKatalogow[gdzieOjciec].ustawPodfoldery(tablicaKatalogow[gdzieOjciec].ilePodfolderow() - 1);//zmiejszanie ilosci podolerow u ojca
	}
	else { 
		cout << "Brak Katalogu o podanje nazwie" << endl; 
	}
}

void dysk::wypiszDrzewo()
{
	cout << "WSZYTKIE FOLDERY I PLIKI W NICH ZAWARTE: " << endl;
	for (int i = 0; i<ileFolderow; i++){ //pentle powtarza tyle razy ile folderow
		cout << " - nazwa folderu: " << tablicaKatalogow[i].pobierzNazwe() << "\n";//wypisanie nazwy folderu

		cout << " - pliki zawarte w folderze: ";
		vector<short> tabpom = tablicaKatalogow[i].pobierzNumery(); //pobieranie nr plikow z tablicy katolagow i przypisywanie ich do vektora pomocniczego tabpom
		if (tabpom.size() == 0){ //jesli vektor pomocniczy pusty = brak plikow
			cout << "brak plikow";
		}
		for (int i = 0; i<tabpom.size(); i++){//jesli nie pusty sprawdzamy kazda pozycje
			cout << tablicaWpisow[tabpom[i]].pobierzNazwe() << "." << tablicaWpisow[tabpom[i]].pobierzRozszerzenie() << ", ";//wypisywanie nazw plikow wraz z rozszerzeniami (pobiera z tablicy wpisow)
		}cout << endl;
		int k = tablicaKatalogow[i].pobierzOjca();//sprawdzanie folderow nadrzednych
		cout << " - folder nadrzedny: "; 
		if (tablicaKatalogow[i].pobierzOjca() == -1) { cout << "brak folderu narzednego"<<endl; } //sprawdzanie czy folder posiada folder nadrzedny ---> tu co jak nie 
		else { 
			cout << tablicaKatalogow[tablicaKatalogow[i].pobierzOjca()].pobierzNazwe() << endl; //pobieramy nazwe folderu narzednego 
		}
		cout << " - foldery podrzedne: ";
		bool podfoldery = true;
		array<short, 32> tabpom2 = tablicaKatalogow[i].pobierzSynow(); // pobieramy foldery podrzedne z tablicy katalogow i umeiszczamy je w pomocniczej tablicy
		for (int i = 0; i<tabpom2.size(); i++){
			if (tabpom2[i] != -1) { // jesli istnieje cos w tablicy tabpom2
				cout << tablicaKatalogow[tabpom2[i]].pobierzNazwe() << ", "; //wypisywanie nazw folderow podrzednych
				podfoldery = false;
			}
		}
		if (podfoldery){
			cout << "brak folderow podrzednych";
		}
		cout << endl<<endl;
	}
}

void dysk::wypiszDysk()
{
	vector<int> blokiIndeksowe; //pomocnicza tablica blokow indeksowych

	for (int i = 0; i<tablicaIwezlow.size(); i++){
		if (tablicaIwezlow[i].pobierzIndeksowyBlok() != -1){ // blok indeksowy tab iwezlow nie jest pusty
			blokiIndeksowe.push_back(tablicaIwezlow[i].pobierzIndeksowyBlok()); //do pomocniczej tablicy blokow indeksowych wkladam nr bloku indeksowego 
		}
	}

	for (int i = 0; i<32; i++){
		cout << i << " "; //wypisanie numeru bloku dyskowego
		for (int k = 0; k<32; k++){
			if (find(blokiIndeksowe.begin(), blokiIndeksowe.end(), i) != blokiIndeksowe.end()){
				cout << static_cast<short>(tablicaDysk[(i*wielkoscBloku) + k]) << " "; //wypisywanie dysku
			}
			else {
				cout << tablicaDysk[(i*wielkoscBloku) + k];//wypisanie dysku
			}
		}
		cout << endl;//przechodzenie do nowej linii w bloku dyskowym tak aby podzielil sie na 32 bloki poo 32 bity
	}
	cout << endl;
}

void dysk::wypiszWektorBitowy()
{
	cout << "WEKTOR BITOWY ('0' oznacza zjety blok, '1' oznacza blok wolny): "<<endl;
	for (int i = 0; i<wektorBitowy.size(); i++){
		cout << wektorBitowy[i];//wypisywanie wektora bitowego
	}
	cout << endl << endl;
}

void dysk::wypiszTabliceIwezelow()
{
	cout << "TABLICA I-WEZLOW:"<<endl;
	for (iWezel tablicaIwezlow : tablicaIwezlow){
		tablicaIwezlow.wypiszIwezel(); //wypisywanie wszystkich elementow tablicy iwezlow
		cout << endl;
	}
}

void dysk::ileWolnych() //ilosc wolnych blokow dyskowych
{
	cout << endl << "Wolnych blokow dyskowych jest: " << wolneBloki << endl;
}

void dysk::wypiszTabliceWpisow()
{
	cout << "TABLICA WPISOW: " << endl;
	for (int i = 0; i<tablicaWpisow.size(); i++){
		tablicaWpisow[i].wypisz(); //wypisywanie tablicy wpisow
		cout << endl;
	}
}

short dysk::znajdzPlik(string nazwa, string rozszerzenie) //szukanie pliku po nazwi w tablicy w pisow
{
	int pom = -1;
	for (int i = 0; i< tablicaWpisow.size(); i++){
		if (tablicaWpisow[i].pobierzNazwe() == nazwa && tablicaWpisow[i].pobierzRozszerzenie() == rozszerzenie){
			pom = tablicaWpisow[i].pobierzNumer(); //pobiera nr z tab wpisow i przypisuje do zmiennej pomocniczej
			break;
		}
	}
	return pom;
}

short dysk::znajdzWolnyBlok()
{
	short pom = -1;
	for (int i = 0; i< wektorBitowy.size(); i++){
		if (wektorBitowy[i] == true){ //'1' - wolne miejsce , '0'-zajete miejsce
			pom = i;
			break;
		}
	}if (pom == -1){
		cout << "Brak wolnych blokow na dyskow" << endl;
	}
	return pom;
}

short dysk::znajdzIwezel()
{
	short pom = -1;
	for (int i = 0; i < tablicaIwezlow.size(); i++){
		if (tablicaIwezlow[i].pobierzPierwszyBlok() == -1){
			pom = i;//zwraca pierwszy wolny i-wezel
			break;
		}
	}
	return pom;
}

string dysk::pobierzNazweFolder(short pom)
{
	return tablicaKatalogow[pom].pobierzNazwe();//funjca zwracajca nazwe folderu, kiedy za argument podajmy pozycje w tablicy katalogow
}

short dysk::znajdzFolder(string nazwa)
{
	short pom = -1;
	for (int i = 0; i<tablicaKatalogow.size(); i++){
		if (tablicaKatalogow[i].pobierzNazwe() == nazwa){
			pom = i;// zrwaca znaleziony folder jak nie to -1
			break;
		}
	}
	return pom;
}