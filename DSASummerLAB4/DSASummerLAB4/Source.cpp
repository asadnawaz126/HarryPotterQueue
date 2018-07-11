#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string getString(char x);
class Student {
public:
	Student * next;
	int school;
	int rollNumber;
	Student* prev;

	Student(int school, int rolnmb) {
		this->school = school;
		this->rollNumber = rolnmb;
		next = NULL;
		prev = NULL;
	}

};
class Queue {
	int size = 0;

	Student* head;
	Student* tail;
public:
	void enqueue(int school, int rolnmb);
	void dequeue(ofstream &file);
	void displayQueue();
};

int main() {

	ofstream newFile;
	newFile.open("output.txt");

	Queue queue;

	string fileName = "input3.txt";

	ifstream inFile;


	inFile.open(fileName);
	int numberOfqueries;

	string queryString;

	vector<char> dequeueList;

	getline(inFile, queryString);

	numberOfqueries = stoi(queryString);
	//cout << queries << endl;

	while (!inFile.eof()) {
		vector<string>studentData;
		string data;
		getline(inFile, data);


		int spacePosition = 0; //position of whitespace

		int index = 0; //bunny data index

		for (int i = 0; i < data.length(); i++) {


			if (data[i] == ' ') {

				studentData.push_back(data.substr(spacePosition, i - spacePosition));

				spacePosition = i + 1;

			}

			else if (i == data.length() - 1) {

				studentData.push_back(getString(data[i]));

			}


		}

		if (studentData[0] == "E") {
			queue.enqueue(stoi(studentData[1]), stoi(studentData[2]));
		}

		else if (studentData[0] == "D")
			queue.dequeue(newFile);
	}
	cout << endl;
	queue.displayQueue();

	getchar();
	return 0;

}


void Queue::enqueue(int school, int rolnmb) {

	Student* temp = new Student(school, rolnmb);


	//I have 1 Node that is both head and tail with the next and prev of this Node both pointing to NULL
	if (head == NULL) {
		head = temp;			//head now points to temp
		tail = temp;			//tail now points to temp
		temp->prev = NULL;
		temp->next = NULL;
	}


	else {
		Student* curr = NULL;
		Student* previous = tail;

		int flag = 0;
		while (previous != NULL) {
			curr = previous;
			previous = previous->prev;
			if (temp->school == curr->school) {
				//this if condition is to cater for the final student school being equal to the new student school
				if (curr == tail) {
					curr->next = temp;
					temp->prev = curr;
					curr = temp;
					break;
				}

				//this block caters to the new student school being equal to the last student's school in the queue who is not the last student
				else {
					Student* temp2 = curr->next;
					curr->next = temp;
					temp->prev = curr;
					temp->next = temp2;
					temp2->prev = temp;
					flag++;
					break;
				}

			}
		}
		//if no same school student is found, add new student to end of list
		if (flag == 0) {

			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}
}

void Queue::dequeue(ofstream &file) {
	Student* temp;
	temp = head;
	if (head == NULL) {
		cout << "Error: Queue is Empty!" << endl;
		return;
	}

	else {
		cout << head->school << " " << head->rollNumber << endl;
		file << head->school << " " << head->rollNumber << endl;
		head = head->next;
		head->prev = NULL;
		delete temp;
	}

}

void Queue::displayQueue() {

	Student* temp = head;

	if (head == NULL) {
		cout << "Error: Queue is Empty!" << endl;
		return;
	}

	else {
		while (temp != NULL) {
			cout << temp->school << " " << temp->rollNumber << endl;
			temp = temp->next;
		}
	}
}

string getString(char x)
{
	string s(1, x);

	return s;
}