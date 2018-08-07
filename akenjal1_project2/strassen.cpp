#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
using namespace std;
typedef vector<vector<float>> matrix_2d;

/* Function to generate random number */
float randomNumberGenerator(float x, float y){
	return round ((((float)rand() / (float)RAND_MAX) * (y-x) - y)*100) / 100.0;
}

/* Function to print the matrix */
void printMatrix(matrix_2d &matrix) {
	int n = matrix.size();
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout<<setw(6)<<setprecision(2)<<fixed<<matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	return;
}

/* Function for matrix addition and subtraction */
matrix_2d matrixAdditionSubtraction(matrix_2d &matrix1, matrix_2d &matrix2, int operation) {
	int n = matrix1.size();
	matrix_2d result(n, vector<float> (n, 0.0));
	if(operation) { 
		for(int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				result[i][j] = matrix1[i][j] + matrix2[i][j];
			}
		}
	}
	else { 
		for(int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				result[i][j] = matrix1[i][j] - matrix2[i][j];
			}
		}
	}
	return result;
}

/* Function to split matrix into split matrix into sub-matrices */
matrix_2d splitMatrix(matrix_2d &matrix1, matrix_2d &matrix2, int n_from, int n_to) {
	int n = matrix1.size();
	for(int i = 0, x = n_from ; i < n ; i++, x++) {
		for (int j = 0, y = n_to; j < n; j++, y++) {
			matrix1[i][j] = matrix2[x][y];
		}
	}
	return matrix1;
}

/* Recursive function for strassens multiplication */
matrix_2d recursiveStrassensMultiplication(int n, matrix_2d &matrix1, matrix_2d &matrix2) {
	
	matrix_2d strassensMResult(n, vector<float> (n, 0.0));

	if (n == 1) {// base case
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					strassensMResult[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
	}
	else { // recursive case
		int new_n = n/2;

		matrix_2d matrix1_11(new_n, vector<float> (new_n, 0.0)), matrix1_12(new_n, vector<float> (new_n, 0.0)), 
				matrix1_21(new_n, vector<float> (new_n, 0.0)), matrix1_22(new_n, vector<float> (new_n, 0.0)), 
				matrix2_11(new_n, vector<float> (new_n, 0.0)), matrix2_12(new_n, vector<float> (new_n, 0.0)), 
				matrix2_21(new_n, vector<float> (new_n, 0.0)), matrix2_22(new_n, vector<float> (new_n, 0.0));

		//splitting the matrix m1 into sub-matrices matrix1_11, matrix1_12, matrix1_21, matrix1_22
		matrix1_11 = splitMatrix(matrix1_11, matrix1, 0, 0);
		matrix1_12 = splitMatrix(matrix1_12, matrix1, 0, new_n);	
		matrix1_21 = splitMatrix(matrix1_21, matrix1, new_n, 0);	
		matrix1_22 = splitMatrix(matrix1_22, matrix1, new_n, new_n);

		//splitting the matrix m2 into sub-matrices matrix2_11, matrix2_12, matrix2_21, matrix2_22
		matrix2_11 = splitMatrix(matrix2_11, matrix2, 0, 0);
		matrix2_12 = splitMatrix(matrix2_12, matrix2, 0, new_n);	
		matrix2_21 = splitMatrix(matrix2_21, matrix2, new_n, 0);	
		matrix2_22 = splitMatrix(matrix2_22, matrix2, new_n, new_n);


		matrix_2d m1(new_n, vector<float> (new_n, 0.0)), m2(new_n, vector<float> (new_n, 0.0)), 
				m3(new_n, vector<float> (new_n, 0.0)), m4(new_n, vector<float> (new_n, 0.0)), 
				m5(new_n, vector<float> (new_n, 0.0)), m6(new_n, vector<float> (new_n, 0.0)), 
				m7(new_n, vector<float> (new_n, 0.0)), temp1(new_n, vector<float> (new_n, 0.0)), 
				temp2(new_n, vector<float> (new_n, 0.0));
		
		// calculating m1-m7
		temp1 = matrixAdditionSubtraction(matrix1_11, matrix1_22, 1);
		temp2 = matrixAdditionSubtraction(matrix2_11, matrix2_22, 1);
		m1 = recursiveStrassensMultiplication(new_n, temp1, temp2);

		temp1 = matrixAdditionSubtraction(matrix1_21, matrix1_22, 1);
		m2 = recursiveStrassensMultiplication(new_n, temp1, matrix2_11);

		temp1 = matrixAdditionSubtraction(matrix2_12, matrix2_22, 0);
		m3 = recursiveStrassensMultiplication(new_n, matrix1_11, temp1);

		temp1 = matrixAdditionSubtraction(matrix2_21, matrix2_11, 0);
		m4 = recursiveStrassensMultiplication(new_n, matrix1_22, temp1);

		temp1 = matrixAdditionSubtraction(matrix1_11, matrix1_12, 1);
		m5 = recursiveStrassensMultiplication(new_n, temp1, matrix2_22);

		temp1 = matrixAdditionSubtraction(matrix1_21, matrix1_11, 0);
		temp2 = matrixAdditionSubtraction(matrix2_11, matrix2_12, 1);
		m6 = recursiveStrassensMultiplication(new_n, temp1, temp2);

		temp1 = matrixAdditionSubtraction(matrix1_12, matrix1_22, 0);
		temp2 = matrixAdditionSubtraction(matrix2_21, matrix2_22, 1);
		m7 = recursiveStrassensMultiplication(new_n, temp1, temp2);

		//calculating strassensMResult11 by m1+m4-m5+m7
		temp1 = matrixAdditionSubtraction(m1, m4, 1);
		temp2 = matrixAdditionSubtraction(temp1, m5, 0);
		temp2 = matrixAdditionSubtraction(temp2, m7, 1);
		for(int i = 0; i < new_n; i++) {
			for (int j = 0; j < new_n; j++) {
				strassensMResult[i][j] = temp2[i][j];	
			}
		}

		//calculating submatrix strassensMResult12 by m3+m5
		temp1 = matrixAdditionSubtraction(m3, m5, 1);
		for(int i = 0; i < new_n; i++) {
			for (int j = 0; j < new_n; j++) {
				strassensMResult[i][j+new_n] = temp1[i][j];	
			}
		}

		//calculating submatrix strassensMResult21 by m2+m4
		temp1 = matrixAdditionSubtraction(m2, m4, 1);
		for(int i = 0; i < new_n; i++) {
			for (int j = 0; j < new_n; j++) {
				strassensMResult[i+new_n][j] = temp1[i][j];	
			}
		}

		//calculating submatrix strassensMResult22 by m1+m3+m2+m6
		temp1 = matrixAdditionSubtraction(m1, m3, 1);
		temp2 = matrixAdditionSubtraction(temp1, m2, 0);
		temp2 = matrixAdditionSubtraction(temp2, m6, 1);
		for(int i = 0; i < new_n; i++) {
			for (int j = 0; j < new_n; j++) {
				strassensMResult[i+new_n][j+new_n] = temp2[i][j];	
			}
		}
	}
	return strassensMResult;
}

/* Wrapper function for strassens multiplication */
void strassensMultiplication(matrix_2d &matrix1, matrix_2d &matrix2) {
	int n = matrix1.size(), new_n;

	if(n & (n-1)) //check if n is a power of 2
		//getting next highest power of 2
		new_n = pow(2, int(ceil(log2(n-1)+1)));//this takes care of the case when n is not = 2^k where k is a positive integer and makes the matrics of 2^k (example when n=3, new_n will be 4 and 8 when n=5)
	else
		new_n = n;

	matrix_2d strassensMResult(new_n, vector<float> (new_n, 0.0)), finalStrassensMResult(n, vector<float> (n, 0.0)), 
			new_matrix1(new_n, vector<float> (new_n, 0.0)), new_matrix2(new_n, vector<float> (new_n, 0.0));


	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			new_matrix1[i][j] = matrix1[i][j];
			new_matrix2[i][j] = matrix2[i][j];
		}
	}

	strassensMResult = recursiveStrassensMultiplication(new_n, new_matrix1, new_matrix2);

	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			finalStrassensMResult[i][j] = strassensMResult[i][j];
		}
	}	
	cout<<"Strassens Multiplication Output:"<<endl;
	printMatrix(finalStrassensMResult);
	return;
}

/* Function for standard matrix multiplication */
void standardMultiplication(matrix_2d &matrix1, matrix_2d &matrix2) {
	int n = matrix1.size();
	matrix_2d standardMResult(n, vector<float> (n, 0.0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				standardMResult[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	cout<<endl<<"Standard Multiplication Output:"<<endl;
	printMatrix(standardMResult);
	return;
}

int main(int argc, char* argv[]) {
	int n;
	if(argc!= 2){
		cout<<"\nPlease enter the arguments correctly. Example: \n./strassen.out <value_of_n>"<<endl;
		return 0;
	}
	else {
		istringstream input(argv[1]);
		if(!(input >> n && input.eof())){
			cout<<"\nPlease enter the argument for n correctly. Enter an integer."<<endl;
			return 0;	
		}
		else{
			n = atoi(argv[1]);
			if(n<=0){
				cout<<"\nPlease enter the argument for n correctly. Enter a positive integer."<<endl;
				return 0;
			}
		}
	}

	matrix_2d matrix1(n, vector<float> (n, 0.0)), matrix2(n, vector<float> (n, 0.0)), 
			strassenMResult(n, vector<float> (n, 0.0));

	for(int i = 0; i < matrix1.size(); i++) {
		for (int j = 0; j < matrix1[i].size(); j++) {
			matrix1[i][j] = randomNumberGenerator(-5.0,5.0);
		}
	}

	for(int i = 0; i < matrix2.size(); i++) {
		for (int j = 0; j < matrix2[i].size(); j++) {
			matrix2[i][j] = randomNumberGenerator(-5.0,5.0);
		}
	}

	cout<<"\nMatrix A:"<<endl;
	printMatrix(matrix1);
	cout<<endl<<"Matrix B:"<<endl;
	printMatrix(matrix2);
	cout<<endl<<endl;;
	strassensMultiplication(matrix1, matrix2);
	standardMultiplication(matrix1, matrix2);
	cout<<endl<<endl;

	return 0;
}