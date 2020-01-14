#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum State{ UNDECLARED, RUNNING, SLEEPING, ZOMBIE, INIT, READY };

class PCB {
public:
	int PID;
	string process_name;
	string program_instructions;
	State status;
	int priority; // <100, 139>
	int task_num;
	int done_task_num;
	float q;
	
	PCB() { 
		this->PID = 0;
		this->status = UNDECLARED;
		this->task_num = 0;
		this->done_task_num = 0;
	}

	PCB(int a) {
		this->PID = a;
		this->program_instructions = "";
		this->priority = 100;
		this->process_name = "INIT";
		this->status = INIT;
		this->task_num = 0;
		this->done_task_num = 0;
	}
	PCB(int priority, int PID, State state, int task_num, int done_task_num, float q)
			{
				this->priority = priority;
				this->PID = PID;
				this->status = state;
				this->task_num = task_num;
				this->done_task_num = done_task_num;
				this->q = q;
			}
	
	void print();
	void set_state(State stat);

	void set_priority(int prioritet)
	{
		priority = prioritet;
	}

	void set_PID(int pid)
	{
		PID = pid;
	}


	void set_task_num(int tsk_n)
	{
		task_num = tsk_n;
	}

	void set_done_task_num(int d_tsk_n)
	{
		done_task_num = d_tsk_n;
	}

	void set_q(float p)
	{
		q = p;
	}
};

class Process_Tree {
public:
	PCB process;
	PCB* daddy;
	vector<Process_Tree*> children;

	bool fork(PCB* proc, const string& name);
	bool fork(PCB* proc, const string& name, const string& instructions);
	bool fork(PCB* proc, const string& name, const string& instructions, const int &priorytet);

	void values_enter(PCB& proc, const string& process_name);
	void values_enter(PCB& proc, const string& process_name, const string& instructions);
	void values_enter(PCB& proc, const string& process_name, const string& instructions, const int &priorytet);


	PCB* find_process(const int& PID);
	PCB* find_process(const string& name);

	void print_tree();
};

//stworzyæ proces o podanym id operuj¹cy na podanym pliku