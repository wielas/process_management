#include "process_management.h"

int available_pid = 2;
vector<PCB*> PQ;
vector<PCB*> SPQ;
int depth = 0;

void PCB::print() {

	for (int i = 0; i < depth; i++)
	{
		std::cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	}
	std::cout << char(191) << " " << "PID: " << PID << std::endl;
	for (int i = 0; i < depth; i++)
	{
		std::cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	}
	std::cout << char(180) << " " << "Nazwa procesu: " << process_name << std::endl;
	for (int i = 0; i < depth; i++)
	{
		std::cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	}
	std::cout << char(180) << " " << "Priorytet: " << priority << std::endl;

	if (program_instructions.size())
	{
		for (int i = 0; i < depth; i++)
		{
			std::cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
		}
		std::cout << char(180) << " " << "Nazwa pliku: " << program_instructions << std::endl;
	}
	for (int i = 0; i < depth; i++)
	{
		std::cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	}
	std::cout << char(180) << " " << "Stan procesu: ";
	if (this->status == 0) cout << " UNDECLARED" << endl;
	if (this->status == 1) cout << " RUNNING" << endl;
	if (this->status == 2) cout << " SLEEPING" << endl;
	if (this->status == 3) cout << " ZOMBIE" << endl;
	if (this->status == 4) cout << " INIT" << endl;
	if (this->status == 5) cout << " READY" << endl;
	for (int i = 0; i < depth; i++)
	{
		std::cout << char(196) << char(196) << char(196) << char(196) << char(196) << char(196);
	}
	std::cout << char(217) << " " << "Liczba rozkazow: " << done_task_num << endl << endl;

	/*cout << "____________________" << endl;
	cout << "PID = " << this->PID << endl;
	cout << "Nazwa = " << this->process_name << endl;
	if (this->status == 0) cout << "Status = UNDECLARED" << endl;
	if (this->status == 1) cout << "Status = RUNNING" << endl;
	if (this->status == 2) cout << "Status = SLEEPING" << endl;
	if (this->status == 3) cout << "Status = ZOMBIE" << endl;
	if (this->status == 4) cout << "Status = INIT" << endl;
	if (this->status == 5) cout << "Status = READY" << endl;
	cout << "Priorytet = " << this->priority << endl;
	cout << "Nazwa pliku = " << this->program_instructions << endl;
	cout << "____________________" << endl;*/

}


bool Process_Tree::fork(PCB* proc, const string& name) {
	if (find_process(name))
	{
		cout << "Proces o danej nazwie juz istnieje" << endl;
		return false;
	}
	else {
		if (proc->PID == process.PID)
		{
			Process_Tree* new_proc = new Process_Tree();
			new_proc->daddy = proc;
			values_enter(new_proc->process, name);
			children.push_back(new_proc);
			cout << "proces z inita" << endl;
		}
		else {
			//szukanie procesu ktorego wskazalismy jako ojca wsrod potomkow procesu init
			for (Process_Tree* temp1 : children)
			{
				if (temp1->process.PID == proc->PID)
				{
					Process_Tree* new_proc = new Process_Tree();
					new_proc->daddy = proc;
					values_enter(new_proc->process, name);
					temp1->children.push_back(new_proc);
					break;
				}
				//szukanie procesu ktorego wskazalismy jako ojca wsrod dzieci potomkow procesu init
				else if (temp1->children.size() != 0)
				{
					for (Process_Tree* temp2 : temp1->children)
					{
						if (temp2->process.PID == proc->PID)
						{
							Process_Tree* new_proc = new Process_Tree();
							new_proc->daddy = proc;
							values_enter(new_proc->process, name);
							temp2->children.push_back(new_proc);
							break;
						}
					}
				}
			}
		}
		return true;
	}
}

bool Process_Tree::fork(PCB* proc, const string& name, const string& instructions) {
	if (find_process(name))
	{
		cout << "Proces o danej nazwie juz istnieje" << endl;
		return false;
	}
	else {
		if (proc->PID == process.PID)
		{
			Process_Tree* new_proc = new Process_Tree();
			new_proc->daddy = proc;
			values_enter(new_proc->process, name, instructions);
			children.push_back(new_proc);
			cout << "proces z inita" << endl;
		}
		else {
			//szukanie procesu ktorego wskazalismy jako ojca wsrod potomkow procesu init
			for (Process_Tree* temp1 : children)
			{
				if (temp1->process.PID == proc->PID)
				{
					Process_Tree* new_proc = new Process_Tree();
					new_proc->daddy = proc;
					values_enter(new_proc->process, name, instructions);
					temp1->children.push_back(new_proc);
					break;
				}
				//szukanie procesu ktorego wskazalismy jako ojca wsrod dzieci potomkow procesu init
				else if (temp1->children.size() != 0)
				{
					for (Process_Tree* temp2 : temp1->children)
					{
						if (temp2->process.PID == proc->PID)
						{
							Process_Tree* new_proc = new Process_Tree();
							new_proc->daddy = proc;
							values_enter(new_proc->process, name, instructions);
							temp2->children.push_back(new_proc);
							break;
						}
					}
				}
			}
		}
		return true;
	}
}

bool Process_Tree::fork(PCB* proc, const string& name, const string& instructions, const int& priorytet) {
	if (find_process(name))
	{
		cout << "Proces o danej nazwie juz istnieje" << endl;
		return false;
	}
	else {
		if (proc->PID == process.PID)
		{
			Process_Tree* new_proc = new Process_Tree();
			new_proc->daddy = proc;
			values_enter(new_proc->process, name, instructions, priorytet);
			children.push_back(new_proc);
			cout << "proces z inita" << endl;
		}
		else {
			//szukanie procesu ktorego wskazalismy jako ojca wsrod potomkow procesu init
			for (Process_Tree* temp1 : children)
			{
				if (temp1->process.PID == proc->PID)
				{
					Process_Tree* new_proc = new Process_Tree();
					new_proc->daddy = proc;
					values_enter(new_proc->process, name, instructions, priorytet);
					temp1->children.push_back(new_proc);
					break;
				}
				//szukanie procesu ktorego wskazalismy jako ojca wsrod dzieci potomkow procesu init
				else if (temp1->children.size() != 0)
				{
					for (Process_Tree* temp2 : temp1->children)
					{
						if (temp2->process.PID == proc->PID)
						{
							Process_Tree* new_proc = new Process_Tree();
							new_proc->daddy = proc;
							values_enter(new_proc->process, name, instructions, priorytet);
							temp2->children.push_back(new_proc);
							break;
						}
					}
				}
			}
		}
		return true;
	}
}


void Process_Tree::values_enter(PCB & proc, const string & process_name) {
	proc.PID = available_pid;
	available_pid++;
	proc.process_name = process_name;
	proc.program_instructions = "";
	proc.priority = 120;
	proc.status = UNDECLARED;
	proc.task_num = 0;
}

void Process_Tree::values_enter(PCB& proc, const string& process_name, const string& instructions) {
	proc.PID = available_pid;
	available_pid++;
	proc.process_name = process_name;
	proc.program_instructions = instructions;
	proc.priority = 120;
	proc.status = SLEEPING;
	SPQ.push_back(&proc);
	proc.task_num = 0;
}

void Process_Tree::values_enter(PCB& proc, const string& process_name, const string& instructions, const int& priorytet) {
	proc.PID = available_pid;
	available_pid++;
	proc.process_name = process_name;
	proc.program_instructions = instructions;
	proc.priority = priorytet;
	proc.status = SLEEPING;
	SPQ.push_back(&proc);
	proc.task_num = 0;
}


PCB* Process_Tree::find_process(const int& PID){
	if (process.PID == PID)
	{
		return &process;
	}
	else
	{
		for (Process_Tree* i : children)
		{
			if (i->process.PID == PID)
			{
				return &i->process;
			}
		}
		for (Process_Tree* i : children)
		{
			PCB* foundPCB = i->find_process(PID);
			if (foundPCB != nullptr)return foundPCB;
		}
		return nullptr;
	}
}

PCB* Process_Tree::find_process(const string& name) {
	if (process.process_name == name)
	{
		return &process;
	}
	else
	{
		for (Process_Tree* i : children)
		{
			if (i->process.process_name == name)

				return &i->process;
			;
		}
		for (Process_Tree* i : children)
		{
			PCB* foundPCB = i->find_process(name);
			if (foundPCB != nullptr)return foundPCB;
		}
		return nullptr;
	}
}


void PCB::set_state(State stat) {
	switch (stat) {
	case UNDECLARED:
	{
		this->status = stat;
		break;
	}
	case RUNNING:
	{
		if (this->status == SLEEPING || this->status == RUNNING) break;
		else
		{
			this->status = READY;
			PQ.push_back(this);
			break;
		}
	}
	case READY: 
	{
		if (this->status == SLEEPING || this->status == RUNNING) break;
		else
		{
			this->status = READY;
			PQ.push_back(this);
			break;
		}
	}
	case SLEEPING:
	{
		if (this->status == SLEEPING || this->status == RUNNING) break;
		else
		{
			this->status = SLEEPING;
			SPQ.push_back(this);
			break;
		}
	}
	case ZOMBIE:
	{
		auto it = find(PQ.begin(), PQ.end(), this);
		auto its = find(SPQ.begin(), SPQ.end(), this);

		if (it != PQ.end()) {
			PQ.erase(it);
			this->status = ZOMBIE;
		}
		if (its != SPQ.end()) {
			SPQ.erase(it);
			this->status = ZOMBIE;
		}
		else {

			this->status = ZOMBIE;
		}
	}
	}
}

void Process_Tree::print_tree() {
	process.print();
	if (children.size() > 0)
		for (Process_Tree* i : children)
		{
			depth++;
			i->print_tree();
			depth--;
		}
}

void Process_Tree::toInit(Process_Tree* tree)
{
	int howmanykids1 = tree->children.size();

	for (int j = 0; j < howmanykids1; j++)
	{
		children.push_back(tree->children[0]);
		tree->children.erase(tree->children.begin());
	}
}

void Process_Tree::kill(const int& pid)
{
	if (pid != 1)
	{
		int howmanykids = children.size();
		for (int i = 0; i < howmanykids; i++)
		{
			//usuwanie jesli proces nie ma potomkow
			if (children[i]->process.PID == pid && children[i]->children.size() == 0)
			{
				children.erase(children.begin() + i);
				break;
			}
			else if (children[i]->process.PID == pid && children[i]->children.size() != 0)
			{
				toInit(children[i]);
				children.erase(children.begin() + i);
				break;
			}
			//usuwanie potomka dziecka inita
			else if (children[i]->children.size() != 0)
			{
				children[i]->kill(pid);
			}
		}
	}
	else
	{
		std::cout <<  "Nie mozna usunac procesu Init" << std::endl;
	}
}