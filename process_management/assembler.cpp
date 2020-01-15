#include "assembler.hpp"
#include "process_management.h"
#include "paging.h"

PCB *currPCB;
vector<string> executed_order;
extern Process_Tree drzewko;


regex for_value("[\\d]+");
regex for_address("[\\[]([0-9]+|[A-D]+)[\\]]");
regex for_register("[ABCD]");
regex for_state("[.][a-z]");

map<string, int> arg_amount = {
	{"PN", 2}, //przeniesienie
	{"DD", 2}, //dodawanie
	{"OD", 2}, //odejmowanie
	{"MN", 2}, //mnożenie
	{"IK", 1}, //inkrementacja
	{"DK", 1}, //dekrementacja

	{"JR", 3}, //==
	{"JN", 3}, //!=
	{"JW", 3}, //>
	{"JM", 3}, //<
	{"SK", 1}, //skok bezwarunkowy
	{"ZT", 0}, //zatrzymaj proces

	{"OT", 3}, //otwarcie pliku
	{"ZP", 4}, //zapis do pliku
	{"OP", 3}, //odczyt z pliku
	{"ZM", 1}, //zamknięcie pliku

	{"TP", 2}, //tworzy proces
	{"UP", 1}, //usuwa proces
	{"WD", 3}, //wysyła dane do procesu
	{"PD", 2}  //odbiera dane z procesu
};

int logical_address(string argument) {

	string number;
	string registers[4] = { "A", "B", "C", "D" };
	for (int i = 1; i < argument.length() - 1; i++)
		number.push_back(argument[i]);

	for (auto reg : registers)
		if (reg == number) {
			return read_register(reg);
		}

	return stoi(number);
}

//1-dodawanie
//2-odejmowanie
//3-mnożenie

void math_operation(int operation) {
	int l1, l2;

	if (regex_match(executed_order[2], for_address)) {
		l1 = paging::readM(currPCB->PID, logical_address(executed_order[2]));
	}
	else if (regex_match(executed_order[2], for_value))
		l1 = stoi(executed_order[2]);

	else if (regex_match(executed_order[2], for_register))
		l1 = read_register(executed_order[2]);

	if (regex_match(executed_order[1], for_address)) {
		l2 = paging::readM(currPCB->PID, logical_address(executed_order[1]));

		switch (operation) {
		case 1:
			paging::writeM(currPCB->PID, logical_address(executed_order[1]), l2 + l1);
			break;
		case 2:
			paging::writeM(currPCB->PID, logical_address(executed_order[1]), l2 - l1);
			break;
		case 3:
			paging::writeM(currPCB->PID, logical_address(executed_order[1]), l2 * l1);
			break;
		}
	}
	else if (regex_match(executed_order[1], for_register)) {
		l2 = read_register(executed_order[1]);
		switch (operation) {
		case 1:
			save_to_register(executed_order[1], l2+l1);
			break;
		case 2:
			save_to_register(executed_order[1], l2-l1);
			break;
		case 3:
			save_to_register(executed_order[1], l2*l1);
			break;
		}
	}
}

//1 - Inkrementacja
//2 - Dekrementacja

void inc_dec(int operation) {
	if (regex_match(executed_order[1], for_address)) {
		int log_addr = logical_address(executed_order[1]);
		int to_save = paging::readM(currPCB->PID, log_addr);
		if (operation == 1) {
			paging::writeM(currPCB->PID, log_addr, to_save+1);
		}
		else if (operation == 2) {
			paging::writeM(currPCB->PID, log_addr, to_save-1);
		}
	}
	else if (regex_match(executed_order[1], for_register)) {
		int to_save = read_register(executed_order[1]);

			 if (operation == 1) save_to_register(executed_order[1], to_save+1);
		else if (operation == 2) save_to_register(executed_order[1], to_save-1);
	}
}

//1 - równe
//2 - nierówne
//3 - większe
//4 - mniejsze

void conditional_jumps(int operation) {
	int l1, l2, l3 = logical_address(executed_order[3]);
	
	if (regex_match(executed_order[1], for_address)) {
		l1 = paging::readM(currPCB->PID, logical_address(executed_order[1]));
	}
	else if (regex_match(executed_order[1], for_value))
		l1 = stoi(executed_order[1]);

	else if (regex_match(executed_order[1], for_register))
		l1 = read_register(executed_order[1]);

	
	if (regex_match(executed_order[2], for_address)) {
		l2 = paging::readM(currPCB->PID, logical_address(executed_order[2]));
	}
	else if (regex_match(executed_order[2], for_value))
		l2 = stoi(executed_order[2]);

	else if (regex_match(executed_order[2], for_register))
		l2 = read_register(executed_order[2]);
	
	switch (operation) {
	case 1:
		if (l1 == l2) currPCB->done_task_num = l3;
		break;
	case 2:
		if (l1 != l2) currPCB->done_task_num = l3;
		break;
	case 3:
		if (l1 > l2) currPCB->done_task_num = l3;
		break;
	case 4:
		if (l1 < l2) currPCB->done_task_num = l3;
		break;
	}
}

void execution() {
	string o = executed_order[0];
	if (o == "PN") {
		int to_save;

		if (regex_match(executed_order[2], for_address)) {
			to_save = paging::readM(currPCB->PID, logical_address(executed_order[2]));
		}
		else if (regex_match(executed_order[2], for_value)) {
			to_save = stoi(executed_order[2]);
		}

		else if (regex_match(executed_order[2], for_register)) {
			to_save = read_register(executed_order[2]);
		}

		if (regex_match(executed_order[1], for_address)) {
			paging::writeM(currPCB->PID, logical_address(executed_order[1]), to_save);
		}
		else if (regex_match(executed_order[1], for_register)) {
			save_to_register(executed_order[1], to_save);
		}
	}
	else if (o == "DD")	math_operation(1);
	else if (o == "OD") math_operation(2);
	else if (o == "MN") math_operation(3);
	else if (o == "IK") inc_dec(1);
	else if (o == "DK") inc_dec(2);
	else if (o == "JR") conditional_jumps(1);
	else if (o == "JN") conditional_jumps(2);
	else if (o == "JW") conditional_jumps(3);
	else if (o == "JM") conditional_jumps(4);
	else if (o == "SK") {
		currPCB->done_task_num = logical_address(executed_order[1]);
	}
	else if (o == "ZT") {
		currPCB->set_state(ZOMBIE);
	}
	else if (o == "OT") {
		//int id_pliku = open_file(executed_order[1], executed_order[3]);
		//write_memory(currPCB, logical_address(executed_order[2]), id_pliku);
	}
	else if (o == "ZP") {
		//int id_pliku = read_memory(currPCB, logical_address(executed_order[1]));
		//pętla idąca przez pamięć, pobierająca do tablicy to, co ma zostać zapisane
		//write_file(id_pliku, , executed_order[3]);
	}
	else if (o == "OP") {
		//int id_pliku = read_memory(currPCB, logical_address(executed_order[1]));
		//pętla odczytująca znak po znaku z pliku i zapisująca dane w RAMie
		//read_file(id_pliku, );
	}
	else if (o == "ZM") {
		//int id_pliku = read_memory(currPCB, logical_address(executed_order[1]));
		//close_file(id_pliku);
	}
	else if (o == "TP") {
		drzewko.fork(currPCB, executed_order[1], executed_order[2], stoi(executed_order[3]))
	}
	else if (o == "UP") {
		drzewko.kill(stoi(executed_order[1]));
	}
	else {
		//Wyrzucić brak komendy
	}
}

void save_to_register(string regTo, int value) {
		 if (regTo == "A") currPCB->A = value;
	else if (regTo == "B") currPCB->B = value;
	else if (regTo == "C") currPCB->C = value;
	else if (regTo == "D") currPCB->D = value;
	else {
		throw "NOREGISTER";
	}
}

int read_register(string reg) {
		 if (reg == "A") return currPCB->A;
	else if (reg == "B") return currPCB->B;
	else if (reg == "C") return currPCB->C;
	else if (reg == "D") return currPCB->D; 
	
	throw "NOREGISTER";
}

vector<string> read_bytes(int amount) {
	vector<string> dane;
	for (int i = 0; i < amount; i++) {
		string dana;

		for (;;) {
			char byte;
			//adres logiczny jest w: currPCB->done_task_num
			byte = paging::readM(currPCB->PID, currPCB->done_task_num);
			currPCB->done_task_num++;
			if (byte == ' ' || (byte == ';')) break;
			dana.push_back(byte);
		}
		dane.push_back(dana);
	}
	
	return dane;
}

void interpret(PCB *pcb) {
	currPCB = pcb;

	vector<string> rozkaz {"NULL"};
	
	//Pobieramy nazwę instrukcji
	rozkaz[0] = read_bytes(1)[0];

	//Dowiadujemy się z mapy ile argumentów ma dana instrukcja bytes_amount
	int bytes_amount = arg_amount[rozkaz[0]];

	//Pobieramy argumenty z pamięci
	for (auto argument : read_bytes(bytes_amount))
		rozkaz.push_back(argument);
	executed_order = rozkaz;

	//Wykonujemy fukcję przypisaną do danego rozkazu
	execution();

	//oddajemy kontrolę po wykonaniu rozkazu
}