#include <iostream>
#include <string> 
#include <vector>
using namespace std;

class Board {
	string cells = "         ";
	void playCell(string turn, int place);
	vector<string> rows ();
public:
	string display ();
	void Xturn();
	void Yturn();

	int gameOver();
};


string Board::display(){
	char ch1 = cells[0];
	char ch2 = cells[1];
	string str = string()+cells[0]+"|"+cells[1]+"|"+ cells[2] + "\n" + cells[3]+"|" + cells[4] +"|"+ cells[5] + "\n" + cells[6]+"|" + cells[7]+"|" + cells[8] + "\n";
	return str;
}
void Board::playCell(string turn, int place){
	if (place == 0){
		cells = string() + turn + cells.substr(1,8);
	} else if (place == 8){
		cells = string() + cells.substr(0,8) + turn;
	} else {
		cells = string() + cells.substr(0,place) + turn + cells.substr(place+1,9-place);
	}
}
void Board::Xturn(){
	cout << "It is X's turn please enter your cell \n";
	cout << "Enter the row number (1-3) followed by the column number (1-3)\n";
	cout << "For example 1 2 would be the middle of the top row\n";
	int row, col;
	cin >> row >> col;
	int place = (row-1)*3+col-1;
	if (row>3||col>3||row<1||col<1){
		cout << "please eneter a valid row and column\n";
		Xturn();
	} else if (cells[place] == 32){
		playCell("X", (row-1)*3+col-1);
	} else {
		cout << "please enter an empty cell\n";
		Xturn();
	}
}
void Board::Yturn(){
	cout << "It is Y's turn please enter your cell \n";
	cout << "Enter the row number (1-3) followed by the column number (1-3)\n";
	cout << "For example 1 2 would be the middle of the top row\n";
	int row, col;
	cin >> row >> col;
	int place = (row-1)*3+col-1;
	if (row>3||col>3||row<1||col<1){
		cout << "please eneter a valid row and column\n";
		Yturn();
	} else if (cells[place] == 32){
		playCell("Y", (row-1)*3+col-1);
	} else {
		cout << "please enter an empty cell\n";
		Yturn();
	}
}
int Board::gameOver(){
	int empty = 0;
	for (int i = 0; i < 9; i ++){
		if (cells[i] == 32){
			empty++;
		}
	} if (empty == 0){
		return 3;
	}
	vector<string> row = rows();
	for (auto & element : row) {
		if (element.compare("XXX") == 0){
			return 1;
		} else if (element.compare("OOO") == 0){
			return 2;
		}
	}
	return 0;
}
vector<string> Board::rows(){
	vector<string> rows;
	rows.push_back(string()+cells[0]+ cells[1]+ cells[2]);
	rows.push_back(string()+cells[3]+ cells[4]+ cells[5]);
	rows.push_back(string()+cells[6]+ cells[7]+ cells[8]);
	rows.push_back(string()+cells[0]+ cells[3]+ cells[6]);
	rows.push_back(string()+cells[1]+ cells[4]+ cells[7]);
	rows.push_back(string()+cells[2]+ cells[5]+ cells[8]);
	rows.push_back(string()+cells[0]+ cells[4]+ cells[8]);
	rows.push_back(string()+cells[2]+ cells[4]+ cells[6]);
	return rows;
}

int main () {
	Board board;
	cout << board.display()<< "\n";
	while (board.gameOver() == 0 ){
		board.Xturn();
		cout << board.display();
		if (board.gameOver() ==0) {
			board.Yturn();
			cout << board.display();
		}

	}
	if (board.gameOver() == 1){
		cout << "\n" << "X wins";
	} else if (board.gameOver() == 2){
		cout << "\n" << "Y wins";
	} else if (board.gameOver() == 3){
		cout << "\n" << "Its a tie";
	}

	// vector<string> rows = board.rows();
	// for (auto & element : rows) {
 //    	cout << element<< "\n";
	// }
	return 0;
}


