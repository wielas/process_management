#pragma once
#include <string>
#include <vector>
#include <iostream>


class Shell
{
private:
	bool running = true;									//warunek dzia�ania programu
	std::string input;										//wej�cie u�ytkownika
	std::vector<std::string> cmd;							//wektor polecenia i jego argument�w
	std::vector<std::string> cmd_history;					//wektor historii polece�

	std::vector<std::string> make_cmd(std::string input);	//przekszta�ca input na wektor
	void run_function(std::vector<std::string> cmd);		//uruchamia funkcje z innych modu��w
	void print_history();									//wyswietla historie polecen
	void print_help();										//wy�wietla pomoc

public:
	void run();												//odpowiada za dzia�anie sytemu
};