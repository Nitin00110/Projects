#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class To_Do_List{
public:
	string Task;
	bool isDone;
	int priority;
	To_Do_List* next;
	To_Do_List* prev;
	To_Do_List(string task,int p){
		Task = task;
		priority = p;
		next = nullptr;
		prev = nullptr;
		isDone = false;
	}
};

class To_Do_Create{
	To_Do_List* head;
	To_Do_List* tail;
public:
	To_Do_Create(){
		head = nullptr;
		tail = nullptr;
	}
	void insert(string Task, int priority){
		To_Do_List* newNode = new To_Do_List(Task,priority);
		if(head == nullptr){
			head = newNode;
			tail = newNode;
		}
		else{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		cout << "Task Added" << endl;
	}
	void Deletion(int n){
		if(head == nullptr || n<1){
			cout << "inValid Position" << endl;
			return;
		}
		To_Do_List* toDelete = head;
		for(int i = 1;i<n && toDelete ;++i){
			toDelete = toDelete->next;
		}
		if(toDelete == nullptr){
				cout << "inValid Position" << endl;
				return;
			}
		if(toDelete->prev != nullptr){
			toDelete->prev->next = toDelete->next;
		}
		else{
			head = toDelete->next;
		}
		if(toDelete->next != nullptr){
			toDelete->next->prev = toDelete->prev;
		}
		else{
			tail = toDelete->prev;
		}
		delete(toDelete);
		cout << "Task is Deleted" << endl;
	}
	void Display(){
		if(head == nullptr){
			cout << "Add Tasks to Display" << endl;
			return;
		}
		sortByPriority();
		int pos = 1;
		To_Do_List* temp = head;
		while(temp){
			cout << pos << ". "<< temp->Task << " (Priority: " << temp->priority << ")";
			if(temp->isDone) cout<< "  [Done]";
			cout << endl;
			pos++;
			temp = temp->next;
		}

	}
	void markDone(int n){
		To_Do_List* temp = head;
		if(!temp) cout << "Add Task First to Mark Done" <<endl;
		for(int i = 1;i<n;++i){
			if(!temp){
				cout << "inValid Position" << endl;
				return;
			}
			temp = temp->next;
		}
		temp->isDone = true;
	}
	void savelife(){
		ofstream file("To-Do-List.txt");
		To_Do_List* temp = head;
		while(temp){
			file << temp->Task << "," << temp->priority << ","<< temp->isDone << endl;
			temp = temp->next;
		}
		file.close();
		cout << "Task Saved in file.\n";
	}
	void loadfile(){
		ifstream file("To-Do-List.txt");
		if(!file) return;
		string line;
		while(getline(file,line)){
			string task;
			int isDone,Priority;
			size_t pos1 = line.find(",");
			size_t pos2 = line.rfind(",");
			task = line.substr(0,pos1);
			isDone = stoi(line.substr(pos1+1,pos2-pos1-1));
			Priority = stoi(line.substr(pos2+1));
			insert(task,Priority);
			if(tail) tail->isDone = isDone;
		}
		file.close();
	}
	void sortByPriority() {
		if (!head || !head->next) return;

		bool swapped;
		do {
			swapped = false;
			To_Do_List* curr = head;
			while (curr && curr->next) {
				if (curr->priority < curr->next->priority) {
					swap(curr->Task, curr->next->Task);
					swap(curr->priority, curr->next->priority);
					swap(curr->isDone, curr->next->isDone);
					swapped = true;
				}
				curr = curr->next;
			}
		} while (swapped);
	}

};

int main(){
	To_Do_Create todo;
	int choice = 0;
	
	todo.loadfile();
	while(true){
		cout << "\n////// To-Do-List \\\\\\" << endl;
		cout << "Press 1 for Insert a Task" << endl;
		cout << "Press 2 for Deletion of Task" << endl;
		cout << "Press 3 to Display all Tasks + Their Status" << endl;
		cout << "Press 4 to Mark Done a Certain Task" << endl;
		cout << "Press 5 to Close To-Do-List" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore();

		if(choice == 1){
			string Task;
			int priority;
			cout << "What is Your Task You Need to Complete" << endl;
			getline(cin, Task);
			cout << "Enter Priority(0-5)" << endl;
			cin >> priority;
			todo.insert(Task,priority);
		}
		else if(choice == 2){
			int id;
			cout << "Enter Task Number You Want to Delete" << endl;
			cin >> id;
			cin.ignore();
			todo.Deletion(id);
		}
		else if(choice == 3){
			cout << "Your Tasks --->" << endl;
			todo.Display();
		}
		else if(choice == 4){
			int id;
			cout << "Which Task You Completed?" << endl;
			cin >> id;
			cin.ignore();
			todo.markDone(id);
			cout << "Congrats! On Completing Your Task No." << id << endl; 
		}
		else if(choice == 5){
			todo.savelife();
			cout << "Exited" << endl;
			break;
		}
		else{
			cout << "Invalid Input. Try Again" << endl;
			cin.clear(); 
			cin.ignore(10000, '\n'); 
		}
	}
	return 0;
}
