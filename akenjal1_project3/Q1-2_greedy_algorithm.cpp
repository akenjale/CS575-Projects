#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

int n,knapsack_capacity;

struct item {
	int item_no;
	int weight;
	int benefit;
	int density;
};

typedef vector<item> item_vector;

void greedy1(item_vector &items);
void greedy2(item_vector &items);
void greedy3(item_vector &items);
void greedy4(item_vector &items);

/*Overriding the boolean operator to sort the struct vector of items accoring to different fields.*/
struct max_benefit
{
    bool operator()( const item &item1, const item &item2) const {
        return item1.benefit > item2.benefit;
    }
};

struct min_weight
{
    bool operator()( const item &item1, const item &item2) const {
        return item1.weight < item2.weight;
    }
};

struct max_weight
{
    bool operator()( const item &item1, const item &item2) const {
        return item1.weight > item2.weight;
    }
};

struct max_density
{
    bool operator()( const item &item1, const item &item2) const {
        return item1.density > item2.density;
    }
};

vector<string> string_split(string &str, char separator) {
    stringstream ss(str);
    string part;
    vector<string> parts;
    while (getline(ss, part, separator)) {
        parts.push_back(part);
    }
    return parts;
}

/*Filling the knapsack with different items untill full.*/
item_vector fill_knapsack(item_vector &items) {
	int current_weight = 0;
	item_vector knapsack;
	for(int i = 0; i < items.size(); i++) {
		if(current_weight+items[i].weight <= knapsack_capacity) {
			current_weight += items[i].weight;
			knapsack.push_back(items[i]);
		}
	}
	return knapsack;
}

/*Printing the total weight, profit and items in knapsack.*/
void print_knapsack(item_vector &knapsack) {
	int total_ben, total_weight;
	total_ben=total_weight = 0;
	for(int i = 0; i < knapsack.size(); i++) {
		total_ben += knapsack[i].benefit;
		total_weight += knapsack[i].weight;
	}
	cout<<"Total profit :"<<total_ben<<endl;
	cout<<"Total weight :"<<total_weight<<endl<<endl;
	cout<<"Items selected :"<<endl;
	for(int i = 0; i < knapsack.size(); i++)
		cout<<"(item"<<knapsack[i].item_no<<", "<<knapsack[i].weight<<", "<<knapsack[i].benefit<<")"<<endl;
	cout<<endl<<"====================================="<<endl;
}

void greedy1(item_vector &items) {
	cout<<endl<<"0/1 Knapsack Problem - Greedy 1: Maximum benefit first :"<<endl;
	sort(items.begin(), items.end(), max_benefit());
	//print_items(items);
	item_vector knapsack = fill_knapsack(items);
	print_knapsack(knapsack);
}

void greedy2(item_vector &items) {
	cout<<endl<<"0/1 Knapsack Problem - Greedy 2: Minimum weight first :"<<endl;
	sort(items.begin(), items.end(), min_weight());
	item_vector knapsack = fill_knapsack(items);
	print_knapsack(knapsack);
}

void greedy3(item_vector &items) {
	cout<<endl<<"0/1 Knapsack Problem - Greedy 3: Maximum weight first :"<<endl;
	sort(items.begin(), items.end(), max_weight());
	item_vector knapsack = fill_knapsack(items);
	print_knapsack(knapsack);
}

void greedy4(item_vector &items) {
	cout<<endl<<"0/1 Knapsack Problem - Greedy 4: Maximum benefit per unit :"<<endl;
	sort(items.begin(), items.end(), max_density());
	item_vector knapsack = fill_knapsack(items);
	print_knapsack(knapsack);
}

int main(int argc, char* argv[]) {
	n = knapsack_capacity = 0;
	ifstream file("knapsack.txt");
	vector<string> lines,weights,benefits;
	string line;
	while(getline(file,line))
		lines.push_back(line);

	n = stoi(lines[0]);
	weights = string_split(lines[1],',');
	benefits = string_split(lines[2],',');
	knapsack_capacity = stoi(lines[3]);
	
	item_vector items;
	items.reserve(n);

	for(int i=0; i<n; i++) {
		struct item temp;
		temp.item_no = i+1;
		temp.weight = stoi(weights[i]);
		temp.benefit = stoi(benefits[i]);
		temp.density = temp.benefit/temp.weight;
		items.push_back(temp);
	}

	greedy1(items);
	greedy2(items);
	greedy3(items);
	greedy4(items);
}