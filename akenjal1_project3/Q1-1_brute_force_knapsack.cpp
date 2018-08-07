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

void brute_force_knapsack(vector<int> &item_set, vector<int> &weights, vector<int> &benefits, int W);

int n,knapsack_capacity;

vector<string> string_split(string &str, char separator) {
    stringstream ss(str);
    string part;
    vector<string> parts;
    while (getline(ss, part, separator))
        parts.push_back(part);   
    return parts;
}

/*Function to compute knapsack using all possible subsets of given items.*/
void brute_force_knapsack(vector<int> &item_set, vector<int> &weights, vector<int> &benefits, int W){
	int n = item_set.size();
	vector<int> max_subset;
	int current_max, knapsack_weight;
	current_max = knapsack_weight = 0;

	/*Creating all possible subsets and checking with previous max.*/
	for(int i = 0; i < pow(2,n); i++) {
		vector<int> subset;
		for(int j = 0; j < n; j++) {
			if(i & (1<<j))
				subset.push_back(j+1);
		}
		
		int current_weight, current_benefit;
		current_weight = current_benefit = 0;

		for(int i = 0; i < subset.size(); i++) {
			if(current_weight + weights[subset[i]-1] <= W) {
				current_weight += weights[subset[i]-1];
				current_benefit += benefits[subset[i]-1];
			}
		}

		if(current_benefit > current_max){
			current_max = current_benefit;
			knapsack_weight = current_weight;
			max_subset = subset;
		}
	}
	cout<<"0/1 Knapsack problem using Brute Force :"<<endl;
	cout<<"Total benefit :"<<current_max<<endl;
	cout<<"Total weight :"<<knapsack_weight<<endl;
	cout<<endl<<"Items selected :"<<endl;
	for(int i=0; i < max_subset.size(); i++)
		cout<<"(item"<<max_subset[i]<<", "<<weights[max_subset[i]-1]<<", "<<benefits[max_subset[i]-1]<<")"<<endl;
}

int main(int argc, char* argv[]) {
	n = knapsack_capacity = 0;
	ifstream file("knapsack.txt");
	vector<string> lines, weights_str, benefits_str;
	vector<int> weights, benefits, item_set;

	string line;
	
	while(getline(file,line))
		lines.push_back(line);

	n = stoi(lines[0]);
	weights_str = string_split(lines[1],',');
	benefits_str = string_split(lines[2],',');
	weights.reserve(n);
	benefits.reserve(n);
	transform(weights_str.begin(), weights_str.end(), back_inserter(weights), [](const string &s) { return stoi(s); });
	transform(benefits_str.begin(), benefits_str.end(), back_inserter(benefits), [](const string &s) { return stoi(s); });
	knapsack_capacity = stoi(lines[3]);

	for(int i = 1; i <= n; i++)
		item_set.push_back(i);

	brute_force_knapsack(item_set, weights, benefits, knapsack_capacity);
}