#pragma once
#include <string>
#include <vector>
#include <iostream>


class Shell
{
private:
	bool running = true;									//warunek dzia³ania programu
	std::string input;										//wejœcie u¿ytkownika
	std::vector<std::string> cmd;							//wektor polecenia i jego argumentów
	std::vector<std::string> cmd_history;					//wektor historii poleceñ

	std::vector<std::string> make_cmd(std::string input);	//przekszta³ca input na wektor
	void run_function(std::vector<std::string> cmd);		//uruchamia funkcje z innych modu³ów
	void print_history();									//wyswietla historie polecen
	void print_help();										//wyœwietla pomoc

public:
	void run();												//odpowiada za dzia³anie sytemu
};