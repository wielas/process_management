#include "process_management.h"
#include "procesor.h"
#include "Shell.h"
extern vector<PCB*> PQ;

Process_Tree drzewko;


int main() {

	//kiskes.process.PID = 1;
	//kiskes.process.process_name = "INIT";
	//kiskes.process.status = INIT;

	//kiskes.process.print();

	//kiskes.fork(&kiskes.process, "hellokitty");
	//kiskes.children[0]->process.print();
	//kiskes.fork(&kiskes.children[0]->process, "kitty_kid", "program1");
	//kiskes.children[0]->children[0]->process.print();
	//kiskes.fork(&kiskes.children[0]->children[0]->process, "kids_kid", "program sranie");
	//kiskes.children[0]->children[0]->children[0]->process.print();
	//
	////findpcb test
	//cout << kiskes.find_process(2)->process_name << endl;
	//cout << kiskes.find_process("hellokitty")->PID << endl;

	//kiskes.children[0]->process.set_state(RUNNING);
	//cout << "showtime: " << PQ[0]->process_name << endl;
	//kiskes.children[0]->process.print();

	Process_Tree kiskes;
	kiskes.process = PCB(1);
	drzewko.process = PCB(1);
	Shell s;
	s.run();

	//Process_Tree kiskes;
	//kiskes.process = PCB(1);
	cout << kiskes.process.process_name << endl;
	kiskes.fork(&kiskes.process, "hellokitty1", "file1.txt", 100);
	kiskes.fork(&kiskes.process, "hellokitty2", "file2.txt", 100);
	kiskes.fork(&kiskes.process, "hellokitty3", "file3.txt");
	kiskes.fork(&kiskes.process, "hellokitty4");

	


	for (int i = 0; i < PQ.size(); i++) {
		PQ[i]->print();
	}


	cout << endl << endl << endl;

	kiskes.find_process("hellokitty1")->set_state(ZOMBIE);

	for (int i = 0; i < PQ.size(); i++) {
		PQ[i]->print();
	}


	SetRunning();
	SetRunning();
	SetRunning();
	SetRunning();
	SetRunning();
	SetRunning();
	SetRunning();
	SetRunning();

	SetRunning();
	SetRunning();

	cout << endl << endl << endl << endl << endl;
	PQ.clear();
	SetRunning();
	SetRunning();
	SetRunning();
	SetRunning();

	return 0;
}