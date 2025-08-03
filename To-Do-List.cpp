#include<iostream>
#include<string>
#include<fstream>
#include<unordered_map>
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
class Trie{
	public:
	unordered_map<char,Trie*> children;
	bool isEndofWord;

	Trie(){
		isEndofWord = false;
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
    head = mergeSort(head);

    To_Do_List* temp = head;
    while (temp->next)
        temp = temp->next;
    tail = temp;

    cout << "Tasks sorted by priority using Merge Sort (O(n log n))" << endl;
	}

	void Edit(int n) {
		To_Do_List* temp = head;
		if (!temp || n < 1) {
			cout << "Invalid position" << endl;
			return;
		}

		for (int i = 1; i < n && temp; ++i) {
			temp = temp->next;
		}
		if (!temp) {
			cout << "Invalid position" << endl;
			return;
		}

		cout << "Current Task: " << temp->Task << endl;
		cout << "Enter new task name (or press Enter to cancel): ";
		string newTask;
		cin.ignore();
		getline(cin, newTask);

		if (newTask.empty()) {
			cout << "Edit cancelled." << endl;
			return;
		}

		temp->Task = newTask;
		cout << "Task updated!" << endl;
	}
	To_Do_List* split(To_Do_List* head) {
		To_Do_List* fast = head;
		To_Do_List* slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		To_Do_List* temp = slow->next;
		slow->next = nullptr;
		if(temp) temp->prev = nullptr;
		return temp;
	}

	To_Do_List* mergeSorted(To_Do_List* first, To_Do_List* second) {
		if (!first) return second;
		if (!second) return first;

		if (first->priority < second->priority) {
			first->next = mergeSorted(first->next, second);
			if(first->next) first->next->prev = first;
			first->prev = nullptr;
			return first;
		} else {
			second->next = mergeSorted(first, second->next);
			if(second->next) second->next->prev = second;
			second->prev = nullptr;
			return second;
		}
	}

	To_Do_List* mergeSort(To_Do_List* node) {
		if (!node || !node->next)
			return node;

		To_Do_List* second = split(node);

		node = mergeSort(node);
		second = mergeSort(second);

		return mergeSorted(node, second);
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
		cout << "Press 6 to Edit a Task" << endl;
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
		else if (choice == 6) {
			int id;
			cout << "Which Task Number Do You Want to Edit?" << endl;
			cin >> id;
			todo.Edit(id);
		}
		else{
			cout << "Invalid Input. Try Again" << endl;
			cin.clear(); 
			cin.ignore(10000, '\n'); 
		}
	}
	return 0;
}
