#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <set>

using namespace std;

void dynamic_programming_knapsack(int W, vector<int> &weights, vector<int> &benefits);

int n,knapsack_capacity;

vector<string> string_split(string &str, char separator) {
    stringstream ss(str);
    string part;
    vector<string> parts;
    while (getline(ss, part, separator)) {
        parts.push_back(part);
    }
    return parts;
}

/*Using all subsets of items to fill the knapsack*/
void dynamic_programming_knapsack(int W, vector<int> &weights, vector<int> &benefits) {
	cout<<"0/1 Knapsack problem using Dynamic Programming :"<<endl;
	int n = weights.size();
	vector<vector<int>> B(n+1, vector<int> (W+1));
	vector<int> items_taken;

	for(int w = 0; w <= W; w++)
		B[0][w] = 0;
	for(int k = 1; k <= n; k++) {
		B[k][0] = 0;
		for(int w = 1; w <= W; w++) {
			if ((weights[k-1] <= w) && (B[k-1][w-weights[k-1]] + benefits[k-1] > B[k-1][w]) ){
				B[k][w] = B[k-1][w-weights[k-1]] + benefits[k-1];
			}
			else
				B[k][w] = B[k-1][w];
		}
	}

	int total_benefit = B[n][W];

	/*Getting the items put in knapsack.*/
	for(int i=n; i>0 && W>0; i--) {
		if(B[i][W]!=B[i-1][W]) {
			W-=weights[i-1];
			items_taken.push_back(i);
		}
	}

	int total_weight = 0;
	for(int i=0; i<items_taken.size(); i++) 
		total_weight += weights[items_taken[i]-1];

	cout<<"Total profit :"<<total_benefit<<endl;
	cout<<"Total weight :"<<total_weight<<endl;
	cout<<endl<<"Items selected :"<<endl;
	for(int i=0; i<items_taken.size(); i++) 
		cout<<"(item"<<items_taken[i]<<", "<<weights[items_taken[i]-1]<<", "<<benefits[items_taken[i]-1]<<")"<<endl;	
}

int main(int argc, char* argv[]) {
	n = knapsack_capacity = 0;
	ifstream file("knapsack.txt");
	vector<string> lines,weights_str,benefits_str;
	vector<int> weights,benefits;
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
		
	dynamic_programming_knapsack(knapsack_capacity, weights, benefits);
}