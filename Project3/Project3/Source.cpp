#include<stdlib.h> //for using srand
#include<iostream>
#include<string>
#include<thread> //for using thread
#include<vector>
#include<fstream>

using namespace std;


//============================Data and functions===============================
const int N = 9;

vector<int> check;  //vector for check list
vector<int> copier; //empty vector to copy rows/columns to

int puzzle_rand[9][9];   //array for random puzzle
int puzzle_corr[9][9];   //array for correct puzzle
int puzzle_manu[9][9];   //array for manual puzzle

int resultValidationR[1] = { 0 }; //row result validator - could be an array with a value of either 0 or 1 
int resultValidationB[9] = { 0,0,0,0,0,0,0,0,0 }; //box result validator - could be an array with a value of either 0 or 1


void validateRow(int array[N][N]);
void validateBox(int p, int i, int j, int array[N][N]);
int contains(int key, vector<int> v);
//============================================================================


int main()
{

	fstream pfile;
	pfile.open("p.txt");


	//fill check list vector
	for (int i = 1; i <= 9; i++) {
		check.push_back(i);
	}
	//prints check list vector
	cout << "This is the check vector: ";

	for (int i = 0; i < check.size(); i++)
		cout << check[i] << " ";
	cout << endl;
	cout << endl;

	//===========================puzzle section==============================
	//creates 9x9 puzzle with random numbers
	cout << "The following is a randomly generated puzzle: " << endl;
	srand(time(NULL));
	for (int i = 0; i < 9; i++) { //row
		for (int j = 0; j < 9; j++) { //column
			puzzle_rand[i][j] = (rand() % 9) + 1;
			cout << puzzle_rand[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "The following is a correct puzzle read from a text file: " << endl;
	//takes values from p.txt (correct puzzle) and displays them
	int p[9][9];
	for (int i = 0; i < 9; i++) { //row
		for (int j = 0; j < 9; j++) { //column
			pfile >> puzzle_corr[i][j];
			cout << puzzle_corr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;



	int response; //response for entering own puzzle
	int a; //puzzle value used to manually fill the puzzle
	cout << "Would you like to test the random puzzle (enter 1), correct puzzle (enter 2), or test your own (enter 3)? ";
	cin >> response;
	switch (response)
	{
	case 1:
	{
		//============================Validation Threads================================//
		//thread 1 is for rows 1 to 9
		//thread 2 was to validate columns (unnecessary & unused)
		//threads 3 to 11 are for the 9 boxes

		//=====================Random Puzzle Validation=======================//
		thread t1(validateRow, puzzle_rand);
		t1.join();
		//space for unused t2
		thread t3(validateBox, 1, 0, 0, puzzle_rand);
		thread t4(validateBox, 2, 0, 3, puzzle_rand);
		t3.join();
		t4.join();
		thread t5(validateBox, 3, 0, 6, puzzle_rand);
		thread t6(validateBox, 4, 3, 0, puzzle_rand);
		t5.join();
		t6.join();
		thread t7(validateBox, 5, 3, 3, puzzle_rand);
		thread t8(validateBox, 6, 3, 6, puzzle_rand);
		t7.join();
		t8.join();
		thread t9(validateBox, 7, 6, 0, puzzle_rand);
		thread t10(validateBox, 8, 6, 3, puzzle_rand);
		t9.join();
		t10.join();
		thread t11(validateBox, 9, 6, 6, puzzle_rand);
		t11.join();

		//=====================Random Puzzle Validation Result====================//
		int index = 0;
		while (index < 9) {
		if (resultValidationB[index] == 1)
			index++;    //keep checking the array as long as it is filled with 1s
		else
			break;  //stop as soon as array contains one 0
		}

		if ((index == 9) && resultValidationR[0] == 1)   //resultValidation contains only 1s
			cout << "The puzzle is correct." << endl;
		else
			cout << "The puzzle is incorrect" << endl;

		break;
	}

	case 2:
	{

		//=====================Correct Puzzle Validation=======================//
		thread t1(validateRow, puzzle_corr);
		t1.join();
		//space for unused t13
		thread t3(validateBox, 1, 0, 0, puzzle_corr);
		thread t4(validateBox, 2, 0, 3, puzzle_corr);
		t3.join();
		t4.join();
		thread t5(validateBox, 3, 0, 6, puzzle_corr);
		thread t6(validateBox, 4, 3, 0, puzzle_corr);
		t5.join();
		t6.join();
		thread t7(validateBox, 5, 3, 3, puzzle_corr);
		thread t8(validateBox, 6, 3, 6, puzzle_corr);
		t7.join();
		t8.join();
		thread t9(validateBox, 7, 6, 0, puzzle_corr);
		thread t10(validateBox, 8, 6, 3, puzzle_corr);
		t9.join();
		t10.join();
		thread t11(validateBox, 9, 6, 6, puzzle_corr);
		t11.join();

		//=======================Correct Puzzle validation Result=================//
		int index = 0;
		while (index < 9) {
		if (resultValidationB[index] == 1)
			index++;    //keep checking the array as long as it is filled with 1s
		else
			break;  //stop as soon as array contains one 0
		}

		if ((index == 9) && resultValidationR[0] == 1)   //resultValidation contains only 1s
			cout << "The puzzle is correct." << endl;
		else
			cout << "The puzzle is incorrect" << endl;

		break;

	}

	case 3:
	{
		
		int a; //puzzle value used to manually fill the puzzle
		
		for (int i = 0; i < 9; i++) {
			cout << "Enter nine numbers between 1 and 9 for row " << i + 1 << ": ";
			for (int j = 0; j < 9; j++) {
				cin >> a;
				puzzle_manu[i][j] = a;
			}
		}

		cout << endl;
		
		cout << "This is your puzzle: " << endl;
		for (int i = 0; i < 9; i++) { //row
			for (int j = 0; j < 9; j++) { //column
				cout << puzzle_manu[i][j] << " ";
			}
			cout << endl;
		}


		//=====================Manual Puzzle Validation=======================
		thread t1(validateRow, puzzle_manu);
		t1.join();
		//space for unused t2
		thread t3(validateBox, 1, 0, 0, puzzle_manu);
		thread t4(validateBox, 2, 0, 3, puzzle_manu);
		t3.join();
		t4.join();
		thread t5(validateBox, 3, 0, 6, puzzle_manu);
		thread t6(validateBox, 4, 3, 0, puzzle_manu);
		t5.join();
		t6.join();
		thread t7(validateBox, 5, 3, 3, puzzle_manu);
		thread t8(validateBox, 6, 3, 6, puzzle_manu);
		t7.join();
		t8.join();
		thread t9(validateBox, 7, 6, 0, puzzle_manu);
		thread t10(validateBox, 8, 6, 3, puzzle_manu);
		t9.join();
		t10.join();
		thread t11(validateBox, 9, 6, 6, puzzle_manu);
		t11.join();
		//=======================Manual Puzzle validation Result=================
		int index = 0;
		while (index < 9) {
			if (resultValidationB[index] == 1)
				index++;    //keep checking the array as long as it is filled with 1s
			else
				break;  //stop as soon as array contains one 0
		}

		if ((index == 9) && resultValidationR[0] == 1)   //resultValidation contains only 1s
			cout << "The puzzle is correct." << endl;
		else
			cout << "The puzzle is incorrect" << endl;

		break;

	}


	default:
		break;
	}
	
	system("pause");
	return 0;
}


//============================Functions definitions==============================

void validateRow(int array[N][N]) {
	int i = 0;
	while (i < 9) { /*copy row into vector copier*/
		for (int j = 0; j < 9; j++)
			copier.push_back(array[i][j]);

		/*compare vectors copier and check*/
		if (copier.size() != 9) /*empty slot(s) in the row*/
			break;
		else {
			for (int k = 0; k < 9; k++) {
				if (contains(check[k], copier) != -1) { /*vector copier contains check[k]*/
					int position = contains(check[k], copier); /*index of number to be removed*/
					copier.erase(copier.begin() + position); /*remove number from vector copier*/
				}
				else
					break;
			}
		}

		i++; /*at this point, vector copier is empty. Get ready for validation of next row*/
	}

	if (copier.empty()) /*all rows have passed validation*/
		resultValidationR[0] = 1;
	else
		resultValidationR[0] = 0;
}




void validateBox(int p, int i, int j, int array[N][N]) {
	/*p is position of box
	p=1: i=0, j=0    p=2: i=0, j=3    p=3: i=0, j=6
	p=4: i=3, j=0    p=5: i=3, j=3    p=6: i=3, j=6
	p=7: i=6, j=0    p=8: i=6, j=3    p=9: i=6, j=6
	*/
	/*i starting row, j starting column of the box*/

	/*copy box into vector copier*/
	int x = i;
	int y = j;
	while (x <= i + 2) {
		if (y == j + 3) {   /*column outside of the box*/
			x++;    /*go to next row*/
			y = j; /*and start again from 1st column of the box*/
			copier.push_back(array[x][y]);
			y++;    /*go to next column*/
		}
		else {
			copier.push_back(array[x][y]);
			y++;    /*go to next column*/
		}
		if ((x == i + 2) && (y == j + 3)) /*stop the copy after the last item of the box has been copied*/
			break;
	}

	/*compare vectors copier and check*/
	if (copier.size() != 9) /*empty slot(s) in the box*/
		resultValidationB[p - 1] = 0;
	else {
		for (int k = 0; k < 9; k++) {
			if (contains(check[k], copier) != -1) { /*vector copier contains check[k]*/
				int position = contains(check[k], copier); /*index of number to be removed*/
				copier.erase(copier.begin() + position); /*remove number from vector copier*/
			}
			else
				break;
		}
	}

	if (copier.empty())
		resultValidationB[p - 1] = 1;
	else
		resultValidationB[p - 1] = 0;
}

int contains(int key, vector<int> v) {  /*find an integer in the vector and return its index*/
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == key)
			return i;
	}
	return -1;
}