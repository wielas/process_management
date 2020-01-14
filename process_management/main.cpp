#include "process_management.h"
#include "procesor.h"
#include "Shell.h"
extern vector<PCB*> PQ;

Process_Tree drzewko;


int main() {

	
	drzewko.process = PCB(1);

	Shell s;
	s.run();


	


	for (int i = 0; i < PQ.size(); i++) {
		PQ[i]->print();
	}



	SetRunning();
	SetRunning();
	SetRunning();
	SetRunning();


	cout << endl << endl << endl << endl << endl;
	PQ.clear();
	SetRunning();
	SetRunning();


	return 0;
}