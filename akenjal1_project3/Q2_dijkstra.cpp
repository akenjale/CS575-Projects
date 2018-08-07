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

typedef vector<vector<int>> matrix_2d;

int find_min_distance(vector<int> &dist_arr, vector<int> &visited);
void display(vector<int> &arr);
bool vertex_visited(vector<int> &visit, matrix_2d &D, int m, int i);
bool edge_exists(vector<int> &d_arr, int m);
bool weight_comparison(vector<int> &d_arr, matrix_2d &D, int m, int i);

int n,infinite = 99999999;

vector<string> string_split(string &str, char separator) {
    stringstream ss(str);
    string part;
    vector<string> parts;
    while (getline(ss, part, separator))
        parts.push_back(part);   
    return parts;
}

/*Finding shortest path to all nodes*/
void find_shortest_path (matrix_2d &D, int source_vertex) {
	vector<int> distance_arr(n,infinite), visited(n,0);
	distance_arr[source_vertex] = 0;

	for(int i =0; i<n-1; i++) {
		int min = find_min_distance(distance_arr,visited);
		visited[min] = 1;

		for(int i=0; i<n; i++) {
			bool visited_v = vertex_visited(visited, D, min, i);
			bool edge = edge_exists(distance_arr, min);
			bool less_than = weight_comparison(distance_arr, D, min, i);
			if(visited_v && edge && less_than)
				distance_arr[i] = distance_arr[min] + D[min][i];
		}
	}

	display(distance_arr);
}

/*Checking whether a node is previously visited.*/
bool vertex_visited(vector<int> &visit, matrix_2d &D, int m, int i) {
	return ((visit[i]==0) && D[m][i]);
}

/*Check if edge exists*/
bool edge_exists(vector<int> &d_arr, int m) {
	return d_arr[m] != infinite;
}

/*Check if wheight is less than the pervious weight.*/
bool weight_comparison(vector<int> &d_arr, matrix_2d &D, int m, int i) {
	return d_arr[m]+D[m][i] < d_arr[i];
}

/*Finding minimum distance between source and a node*/
int find_min_distance(vector<int> &dist_arr, vector<int> &visited) {
	int d = infinite, min_dist;
	for(int i = 0; i < n; i++) {
		if(visited[i] == 0 && dist_arr[i]<=d) {
			d = dist_arr[i];
			min_dist = i;
		}
	}
	return min_dist;	
}

void display(vector<int> &arr) {
	cout<<"Source\t\tDistance"<<endl;
	cout<<"============================"<<endl;
	for (int i = 0; i <arr.size() ; ++i)
	{
		cout<<i<<"\t\t"<<arr[i]<<endl;
	}
}

int main(int argc, char* argv[]) {
	ifstream file("matrix_input.txt");
	vector<string> lines, elements;
	string line;
	
	while(getline(file,line)) {
		vector<string> parts= string_split(line, ',');
		n = parts.size();
		for(int i =0; i < n; i++)
			elements.push_back(parts[i]);		
	}

	matrix_2d D(n, vector<int> (n,0));
	int k = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(stoi(elements[k]) == -99) {
				D[i][j] = infinite;
				k++;
			}
			else {
				D[i][j] = stoi(elements[k]);
				k++;	
			}
		}
	}

	find_shortest_path(D, 0);
}