#include "process_management.h"
#include "procesor.h"
#include "Shell.h"

extern vector<PCB*> PQ;

Process_Tree drzewko;


int main() {

	
	drzewko.process = PCB(1);

	drzewko.fork(&drzewko.process, "flappy", "dumdum", 169);
	drzewko.fork(&drzewko.children[0]->process, "flappy_son", "dumdum", 101);
	drzewko.fork(&drzewko.process, "flappy_brother", "dumdum", 102);
	
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