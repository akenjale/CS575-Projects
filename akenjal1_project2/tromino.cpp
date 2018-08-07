#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
using namespace std;
typedef vector<vector<int>> board_2d;

int number = 1, k, arg_n, hole_row, hole_column;
board_2d board;

/* Function to print the board */
void printBoard(board_2d &board) {
	int n = board.size();
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(i == hole_row  && j == hole_column)
				cout<<setw(3)<<"X"<<" ";
			else
				cout<<setw(3)<<board[i][j]<<" ";
		}
		cout<<endl;
	}
	return;
}

/* Function to fill a tile with a number */
void fillTile(int row, int column, int number) {
	board[row][column] = number;
	return;
}

/* Recursive function for tiling */
void trominoTile(int n, int hole_row, int hole_column) {

	if(n==2){ //base case
		//fill the tromino tile. The hole will be the non-zero block.
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(board[hole_row+i][hole_column+j] == 0){
					board[hole_row+i][hole_column+j] = number;					
				}
			}
		}
		number++;
	}
	else { //recursive case
		int new_row = hole_row, new_column = hole_column;

		//copying the row and column value of the hole in the variables new_row and new_column
		for(int i = hole_row; i < hole_row+n; i++) {
			for(int j = hole_column; j < hole_column+n; j++) {
				if(board[i][j]!=0){
					new_row = i;
					new_column = j;					
				}
			}
		}

		//hole is in the top left sub-board  
		if(new_row < hole_row + n/2 && new_column < hole_column + n/2) {
			//recursively fill the top left sub-board 
			trominoTile(n/2, hole_row, hole_column);
			fillTile(hole_row + n/2, hole_column + n/2 - 1, number);
			fillTile(hole_row + n/2, hole_column + n/2, number);
			fillTile(hole_row + n/2 - 1, hole_column + n/2, number);
			number++;
			trominoTile(n/2, hole_row, hole_column + n/2);
			trominoTile(n/2, hole_row + n/2, hole_column);
			trominoTile(n/2, hole_row + n/2, hole_column + n/2);
		}
		//hole is in the top right sub-board 
		else if(new_row < hole_row + n/2 && new_column >= hole_column + n/2) {
			//recursively fill the top right sub-board
			trominoTile(n/2, hole_row, hole_column + n/2);

			fillTile(hole_row + n/2, hole_column + n/2 - 1, number);
			fillTile(hole_row + n/2, hole_column + n/2, number);
			fillTile(hole_row + n/2 - 1, hole_column + n/2 - 1, number);
			number++;
			trominoTile(n/2, hole_row, hole_column);
			trominoTile(n/2, hole_row + n/2, hole_column);
			trominoTile(n/2, hole_row + n/2, hole_column + n/2);
		}
		//hole is in the bottom left sub-board
		else if(new_row >= hole_row + n/2 && new_column < hole_column + n/2) {
			//recursively fill the bottom left sub-board
			trominoTile(n/2, hole_row + n/2, hole_column);

			fillTile(hole_row + n/2 - 1, hole_column + n/2 - 1, number);
			fillTile(hole_row + n/2, hole_column + n/2, number);
			fillTile(hole_row + n/2 - 1, hole_column + n/2 - 1, number);
			number++;
			trominoTile(n/2, hole_row, hole_column);
			trominoTile(n/2, hole_row, hole_column + n/2);
			trominoTile(n/2, hole_row + n/2, hole_column + n/2);
		}
		//hole is in the bottom right sub-board
		else {
			trominoTile(n/2, hole_row + n/2, hole_column + n/2);
			//recursively fill the right sub-board
			fillTile(hole_row + n/2 - 1, hole_column + n/2, number);
			fillTile(hole_row + n/2, hole_column + n/2 - 1, number);
			fillTile(hole_row + n/2 - 1, hole_column + n/2 - 1, number);
			number++;
			trominoTile(n/2, hole_row + n/2, hole_column);
			trominoTile(n/2, hole_row, hole_column + n/2);
			trominoTile(n/2, hole_row, hole_column);
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	//validating the arguments
	if(argc!= 4){
		cout<<"\nPlease enter the arguments correctly. Example: \n./tromino.out <value_of_k> <hole_position_row_number> <hole_position_column_number>"<<endl;
		return 0;
	}
	else {
		for (int i = 1; i<4; i++) {
			istringstream input(argv[i]);
			if(!(input >> arg_n && input.eof())){
				if(i==1){
					cout<<"\nPlease enter the argument for <value_of_k> correctly. Enter integer."<<endl;
					return 0;					
				}
				if(i==2) {
					cout<<"\nPlease enter the argument for <hole_position_row_number> correctly. Enter integer."<<endl;
					return 0;					
				}
				if(i==3) {
					cout<<"\nPlease enter the argument for <hole_position_column_number> correctly. Enter integer."<<endl;
					return 0;
				}
			}
			else{
				k = atoi(argv[1]);
				hole_row = atoi(argv[2]);
				hole_column = atoi(argv[3]);
				int size = pow(2,k);
				if(hole_row > size-1 || hole_column > size-1 || hole_row < 0 || hole_column < 0){
					cout<<"\nPlease enter the arguments for <hole_position_row_number> and <hole_position_column_number> correctly. Enter a value between 0 and 2^k-1."<<endl;
					return 0;
				}
			}
		}
	}

	int n = pow(2,k);
	//creating the 2^k x 2^k board and initializing all values to 0 and hole at position specified in input
	board = board_2d(n, vector<int> (n,0));
	board[hole_row][hole_column] = 88;

	trominoTile(n, 0, 0);
	printBoard(board);
	return 0;
}	