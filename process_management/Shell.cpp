#include "Shell.h"
#include "Colors.h"
#include "process_management.h"
#include <iomanip>
#include <sstream>
#include <iterator>

//paging m;
extern Process_Tree drzewko;


//KONWERSJA INPUT (STRING) NA VECTOR CMD
std::vector<std::string> Shell::make_cmd(std::string input)
{
	std::stringstream ss(input);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}

void Shell::print_help()
{
	// -h

	std::cout << "cmd -h	 - command help (wyswietlenie argumentow dla wybranej komendy)" << std::endl << std::endl;

	// PRACA KROKOWA

	std::cout << "ENTER	 - step work (praca krokowa)" << std::endl;

	// ZARZĄDZANIE PLIKAMI

	std::cout << "touch	 - create file (tworzenie pliku)" << std::endl; // ok [folder_name][file_name][s_folder_name]*
	//std::cout << "ul - unlink (usuwanie dowiazan)\n"; // ok [file_name][s_folder_name]*
	std::cout << "rm	 - remove file (usuwanie pliku)" << std::endl; // ok [folder_name][file_name][s_folder_name]*
	std::cout << "cat	 - open file (otwarcie pliku)" << std::endl; // ok [file_name][open_type][s_folder_name]*   open_type == (r | rw)
	//std::cout << "close - close file (zamkniecie otwartego pliku)\n"; // ok [file_name][s_folder_name]*															//Czy to ma sens?
	//std::cout << "tc - truncate (skracanie pilku)\n"; // ok [file_name][final_bytes_amount][s_folder_name]*
	//std::cout << "rds - read sequential (odczytywanie z pliku sekwencyjnie)\n"; // ok [file_name][bytes_amount][s_folder_name]*
	//std::cout << "rdi - read index (odczytywanie z pliku indeksowo)\n"; // ok [file_name][byte_number_in_file][bytes_amount][s_folder_name]*
	//std::cout << "wrts - write sequential (zapisywanie do pliku sekwencyjnie)\n"; // ok [folder_name][data][s_folder_name]*
	//std::cout << "wrti - write index (zapisywanie do pliku indeksowo)\n"; // ok [file_name][data][byte_number_in_file][s_folder_name]*
	//std::cout << "lsk - lseek (zmiana wskazania biezacej pozycji)\n\n"; // ok [file_name][move_by_amount_in_bytes][reference_point][s_folder_name]*

	// ZARZĄDZANIE KATALOGAMI

	std::cout << "ls	 - directory list (wyswietlenie zawartosci folderu)" << std::endl; // ok [folder_name]
	std::cout << "mkdir    - make directory (tworzenie katalogu)" << std::endl; // ok [folder_name][folder_to_create_name][sfolder_name]*
	std::cout << "rmdir	 - remove directory (usuwanie katalogu)" << std::endl; // ok [folder_name][sfolder_name]*
	std::cout << "cd	 - change directory (przejscie do folderu)" << std::endl << std::endl;
	//std::cout << "cdr - create directory registration (tworzenie wpisu katalogowego)\n"; // ok [folder_name][file_name][file_name][sfolder_name]*
	//std::cout << "ddr - delete directory registration (usuwanie wpisu katalogowego)\n"; // ok [file_name][sfolder_name]*
	//std::cout << "frn - file rename (przemianowanie pliku)\n"; // ok [file_name][new_file_name][sfolder_name]*
	//std::cout << "dc - directory content (tworzenie wykazu spisu zawartosci)\n"; // ok [folder_name][sfolder_name]*


	// DYSK OGOLNIE --- CZYJE?

	//std::cout << "sb - show block (wyswietlenie bloku dyskowego za pomoca symboli ASCII)\n"; // ok []
	//std::cout << "sbd - show block d (wyswietlenie bloku dyskowego za pomoca wartosci liczbowych)\n"; // ok []
	//std::cout << "sd - show disc (wyswietlenie zawartosci dysku za pomoca symboli ASCII)\n"; // ok []
	//std::cout << "sdd - show disc d (wyswietlenie zawartosci dysku za pomoca wartosci liczbowych)\n\n"; // ok []

	// PAMIEC RAM

	std::cout << "meminfo	 - memory info (wyswietlenie aktualnego stanu ramu)" << std::endl << std::endl; // ok []

	// PROCESY

	std::cout << "cp	 - create process (utworzenie procesu)" << std::endl; // [process_name][file_name]
	std::cout << "kill	 - kill process (zakonczenie procesu)" << std::endl; // [process_name]
	std::cout << "run	 - execute (wykonanie programu)" << std::endl; // ok [process_name][file_name]
	std::cout << "tree	 - display processes tree (wyswietlenie drzewa procesow)" << std::endl << std::endl; // ok []

	// HELP

	std::cout << "history	 - wyswietlenie historii wpisanych komend" << std::endl; // ok []
	std::cout << "help	 - wyswietlenie wszystkich komend" << std::endl; // ok []
	std::cout << "clear	 - wyczyszczenie okna konsoli" << std::endl;
	//std::cout << "logo (wyswietlenie logo systemu operacyjnego)\n"; // ok []
	//std::cout << "creators(wyswietlenie tworcow systemu)\n\n"; // ok []

	// EXIT

	std::cout << "exit	 - wyjscie z konsoli" << std::endl; // ok []

	// ERROR
}

void Shell::print_history()
{
	for (const auto& i : cmd_history)
	{
		std::cout << "\n" << i;
	}
	std::cout << "\n";
}

void Shell::run_function(std::vector<std::string> cmd)
{
	// PRACA KROKOWA
	if (cmd.empty()) {
		//Execute(); - wykonanie kroku (Hubert?)
		return;
	}
	//ZARZADZANIE PLIKAMI
	//Tworzenie pliku
	else if (cmd[0] == "touch")
	{
		if (cmd.size() == 2) {
			if (cmd[1] == "-h") {
				std::cout << "\n" << cmd[0] << " " << "[nazwa_pliku]\n";
			}
			else
			{
				//Stworz plik - Koziołek
				std::cout << green << "[SHELL]" << white << " - Utworzono plik : " << cmd[1] << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//Usuwanie pliku
	else if(cmd[0] == "rm")
	{
		if (cmd.size() == 2) {
			if (cmd[1] == "-h") {
				std::cout << "\n" << cmd[0] << " " << "[nazwa_pliku]\n";
			}
			else if(/*Sprawdzenie czy taki plik istnieje*/ running)
			{
				//Usuń plik - Koziołek
				std::cout << green << "[SHELL]" << white << " - Usunieto plik : " << cmd[1] << std::endl;
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Podany plik nie istnieje!" << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//Otwarcie pliku
	else if(cmd[0] == "cat")
	{
		if(cmd.size() == 2)
		{
			if(cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[nazwa_pliku]\n";
			}
			else if(/*sprawdzenie czy taki plik istnieje*/ running)
			{
				//Otwórz plik - Koziołek
			}
			else
			{
				std::cout << red <<  "[SHELL]" << white << " - Podany plik nie istnieje!" << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//ZARZĄDZANIE KATALOGAMI
	//Listowanie katalogu
	else if(cmd[0] == "ls")
	{
		if (cmd.size() == 1)
		{
			//Listuj katalog
		}
		else if (cmd.size() == 2)
		{
			if(cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[]\n";
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//Stworz folder
	else if (cmd[0] == "mkdir")
	{
		if (cmd.size() == 2)
		{
			if (cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[nazwa_folderu]\n";
			}
			else if (/*sprawdzenie czy istnieje katalog o tej nazwie*/ running)
			{
				//Stwórz katalog - Koziołek
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Taki katalog juz istnieje!" << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//Usun folder
	else if (cmd[0] == "rmdir")
	{
	if (cmd.size() == 2)
	{
		if (cmd[1] == "-h")
		{
			std::cout << "\n" << cmd[0] << " " << "[nazwa_folderu]\n";
		}
		else if (/*sprawdzenie czy katalog istnieje*/ running)
		{
			//Usun katalog - Koziołek
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Podany katalog nie istnieje!" << std::endl;
		}
	}
	else
	{
		std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
		std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
	}
	}
	//Przejdz do folderu
	else if (cmd[0] == "cd")
	{
	if (cmd.size() == 2)
	{
		if (cmd[1] == "-h")
		{
			std::cout << "\n" << cmd[0] << " " << "[nazwa_folderu]\n";
		}
		else if (/*sprawdzenie czy katalog istnieje*/ running)
		{
			//Przejdz do katalogu - Koziołek
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Podany katalog nie istnieje!" << std::endl;
		}
	}
	else
	{
		std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
		std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
	}
	}
	//DYSK OGÓLNIE - CZYJE?
	//PAMIĘĆ RAM
	else if (cmd[0] == "meminfo")
	{
	if (cmd.size() == 1)
	{
		//Wyswietlanie pamieci - Mikołaj
	}
	else if (cmd.size() == 2)
	{
		if (cmd[1] == "-h")
		{
			std::cout << "\n" << cmd[0] << " " << "[]\n";
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	else
	{
		std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
		std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
	}
	}
	//PROCESY
	//Tworzenie procesu
	else if (cmd[0] == "cp")
	{
		if (cmd.size() == 2)
		{
			if (cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[nazwa_procesu]\n";
				std::cout << "\n" << cmd[0] << " " << "[nazwa_procesu][nazwa_pliku]\n";
				std::cout << "\n" << cmd[0] << " " << "[nazwa_procesu][nazwa_pliku][priorytet]\n";
			}
			else
			{
				drzewko.fork(&drzewko.process, cmd[1]);
				/*std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;*/
			}
		}
		else if (cmd.size() == 3)
		{
			if(/*sprawdzenie poprawnosci nazwy pliku i procesu*/ running)
			{
				drzewko.fork(&drzewko.process, cmd[1], cmd[2]);
			}
			else if(/*plik nie istnieje lub cos innego mu nie gra*/ running)
			{
				std::cout << red << "[SHELL]" << white << " - Plik jest niepoprawny!" << std::endl;
			}
			else if(/*proces juz istnieje*/ running)
			{
				std::cout << red << "[SHELL]" << white << " - Proces o tej nazwie juz istnieje!" << std::endl;
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}
		else if (cmd.size() == 4) 
		{
			if (/*sprawdzenie poprawnosci nazwy pliku i procesu*/ running)
			{
				drzewko.fork(&drzewko.process, cmd[1], cmd[2], stoi(cmd[3]));
			}
			else if (/*plik nie istnieje lub cos innego mu nie gra*/ running)
			{
				std::cout << red << "[SHELL]" << white << " - Plik jest niepoprawny!" << std::endl;
			}
			else if (/*proces juz istnieje*/ running)
			{
				std::cout << red << "[SHELL]" << white << " - Proces o tej nazwie juz istnieje!" << std::endl;
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}

		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//Zakonczenie procesu
	else if (cmd[0] == "kill")
	{
		if (cmd.size() == 2)
		{
			if (cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[nazwa_procesu]\n";
			}
			else if (/*sprawdzenie poprawnosci nazwy procesu i czy mozna zakonczyc*/ running)
			{
				drzewko.find_process(cmd[1])->set_state(ZOMBIE);
				//Usun proces
			}
			else if (/*nie mozna zakonczyc*/ running)
			{
				std::cout << red << "[SHELL]" << white << " - Nie mozna zakocznyc procesu!" << std::endl;
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	else if (cmd[0] == "run")
	{
		if (cmd.size() == 2)
		{
			if (cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[nazwa_procesu]\n";
			}
			else if (/*sprawdzenie poprawnosci nazwy procesu*/ running)
			{
				//Uruchom proces
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawa nazwa procesu!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;

			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//Drzewo procesow
	else if (cmd[0] == "tree")
		{
		if (cmd.size() == 1)
		{
			//Wyswietl drzewko procesow
			drzewko.print_tree();
		}
		else if (cmd.size() == 2)
		{
			if (cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[nazwa_procesu]\n";
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//HELP
	else if (cmd[0] == "help")
	{
		if (cmd.size() == 1)
		{
			print_help();
		}
		else if (cmd.size() == 2)
		{
			if (cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[]\n";
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}

	//HISTORY
	else if(cmd[0] == "history")
	{
		if(cmd.size() == 1)
		{
			print_history();
		}
		else if (cmd.size() == 2)
		{
			if(cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[]\n";
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}

	// EXIT
	else if (cmd[0] == "exit")
	{
		if (cmd.size() == 1)
		{
			running = false;
		}
		else if (cmd.size() == 2)
		{
			if (cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[]\n";
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	//Wyczyszczenie ekranu
	else if(cmd[0] == "clear")
	{
		if(cmd.size() == 1)
		{
			system("cls");
		}
		else if(cmd.size() == 2)
		{
			if(cmd[1] == "-h")
			{
				std::cout << "\n" << cmd[0] << " " << "[]\n";
			}
			else
			{
				std::cout << red << "[SHELL]" << white << " - Niepoprawny argument!" << std::endl;
				std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;

			}
		}
		else
		{
			std::cout << red << "[SHELL]" << white << " - Niepoprawna liczba argumentow!" << std::endl;
			std::cout << "          Wprowadz " << cmd[0] << " -h, aby uzyskac pomoc." << std::endl;
		}
	}
	else
	{
		std::cout << red << "[SHELL]" << white << " - Niepoprawna komedna, wprowadz help aby uzsykac pomoc." << std::endl;
	}
}

void Shell::run()
{
	while(running)
	{
		std::cout << "\nuser@os:";
		getline(std::cin, input);
		cmd = make_cmd(input);
		run_function(cmd);
		cmd_history.push_back(input);
	}
	std::cout << green << "Wylaczanie systemu..." << white;
	Sleep(1500);
}