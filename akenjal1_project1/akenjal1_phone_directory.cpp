#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

struct person {
	string first_name;
	string last_name;
	string phone_number;
};

vector<person> persons;

void create(string filename){
	ifstream file(filename);
	string line;
	while (getline(file,line)) {
		stringstream ss(line);
		struct person temp;
		string fname,lname,phone;
		ss>>fname>>lname>>phone;
		temp.first_name = fname;
		temp.last_name = lname;
		temp.phone_number = phone;

		persons.push_back(temp);

	}
}

void display() {
	cout<<endl;
	for(int i = 0; i<persons.size(); i++){
		cout<<persons[i].first_name <<" "<<persons[i].last_name <<" "<<persons[i].phone_number <<endl;
	}
}

int searchfordelete(string name){
	int low, mid, high;
	low = 0;
	high = persons.size()-1;
	mid = (low+high)/2;

	while(low<=high) {
		if((persons[mid].first_name+" "+persons[mid].last_name) < (name+",")){
			low = mid + 1;
		}
		else if(!(persons[mid].first_name+" "+persons[mid].last_name).compare(name+",")){
			return mid;
		}
		else{
			high = mid - 1;
		}
		mid = (low+high)/2;
	}
	if(low>high){
		return -1;
	}
}

void delete1(string name) {
	int index = searchfordelete(name);
	if(index == -1) {
		cout<<endl;
		cout<<"Name not found"<<endl;
	}
	else
	{
		persons.erase(persons.begin()+index);
		display();
	}
}

int partition(vector<person>& v,int p,int r){
	int random = rand() % (r - p)+p;
	swap(v[r],v[random]);

	int i = p-1, j;
	for(j = p; j<r; j++){
		if((v[j].first_name.compare(v[r].first_name) < 0)){
			i++;
			swap(v[i],v[j]);
		}
		else if((v[j].first_name.compare(v[r].first_name) == 0) && (v[j].last_name.compare(v[r].last_name) < 0)){
			i++;
			swap(v[i],v[j]);
		}
		else if((v[j].first_name.compare(v[r].first_name) == 0) && (v[j].last_name.compare(v[r].last_name) == 0) && (v[j].phone_number.compare(v[r].phone_number) < 0)){
			i++;
			swap(v[i],v[j]);
		}
	}
	i++;
	swap(v[i],v[r]);
	return i;
}

void rand_quick_sort(vector<person>& v, int p, int r){
	if(p < r) {
		int	q = partition(v, p, r);
		rand_quick_sort(v, p, q-1);
		rand_quick_sort(v, q+1, r);
	}
}

void sort_contact(){
	rand_quick_sort(persons, 0, persons.size()-1);
}

void insert(string name, string phone_number) {
	struct person temp;
	stringstream ss(name);
	string fname,lname;
	ss>>fname>>lname;
	temp.first_name = fname;
	temp.last_name = lname;
	temp.phone_number = phone_number;
	persons.push_back(temp);
}

void search(string name) {
	int low, mid, high;
	low = 0;
	high = persons.size()-1;
	mid = (low+high)/2;

	while(low<=high) {
		if((persons[mid].first_name+" "+persons[mid].last_name) < (name+",")){
			low = mid + 1;
		}
		else if(!(persons[mid].first_name+" "+persons[mid].last_name).compare(name+",")){
			cout<<endl;
			cout<<persons[mid].first_name <<" "<<persons[mid].last_name <<" "<<persons[mid].phone_number <<endl;
			return;
		}
		else{
			high = mid - 1;
		}
		mid = (low+high)/2;
	}
	if(low>high){
		cout<<endl;
		cout<<"Name not found"<<endl;
	}
}

int main(int argc, char* argv[]) {
	if(argc!= 2){
		cout<<"\nPlease enter the arguments correctly. Example: \n./akenjal1_phone_directory.out test_input.txt"<<endl;
		return 0;
	}
	create(argv[1]);
	int choice;
	string fname,lname,phone;
	do{
		cout<<"\n1) sort_contact"<<endl;
		cout<<"2) search"<<endl;
		cout<<"3) delete"<<endl;
		cout<<"4) insert"<<endl;
		cout<<"Enter the Choice"<<endl;
		cin>>choice;
		switch(choice){
			case 1:
				sort_contact();
				display();
				break;
			case 2:
				cout<<"\nEnter the Name->";
				cin>>fname;
				cin>>lname;
				search(fname+" "+lname);
				break;
			case 3:
				cout<<"\nEnter the Name->";
				cin>>fname;
				cin>>lname;
				delete1(fname+" "+lname);
				break;
			case 4:
				cout<<"\nEnter the Name->";
				cin>>fname;
				cin>>lname;
				cin>>phone;
				insert(fname+" "+lname, phone);
				sort_contact();
				display();
				break;
			default:
				cout<<"Enter valid choice.";
				break;
		}
	}while(choice);
	return 0;
}
