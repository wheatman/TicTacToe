#include <iostream>
#include <string> 
#include <vector>
using namespace std;

class Board {
	string cells = "         ";
	int firstTurn=1;
	vector<string> rows ();
public:
	void playCell(string turn, int place);
	string display ();
	void Xturn();
	void Oturn();
	void CompTurn();
	int oneTurnAway(string letter);
	int gameOver();
};


string Board::display(){
	return string()+cells[0]+"|"+cells[1]+"|"+ cells[2] + "\n" + cells[3]+"|" + cells[4] +"|"+ cells[5] + "\n" + cells[6]+"|" + cells[7]+"|" + cells[8] + "\n";
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
void Board::Oturn(){
	cout << "It is O's turn please enter your cell \n";
	cout << "Enter the row number (1-3) followed by the column number (1-3)\n";
	cout << "For example 1 2 would be the middle of the top row\n";
	int row, col;
	cin >> row >> col;
	int place = (row-1)*3+col-1;
	if (row>3||col>3||row<1||col<1){
		cout << "please eneter a valid row and column\n";
		Oturn();
	} else if (cells[place] == 32){
		playCell("O", (row-1)*3+col-1);
	} else {
		cout << "please enter an empty cell\n";
		Oturn();
	}
}
void Board::CompTurn(){
	if (firstTurn==1){
		firstTurn = 0;
		if (cells[4] ==32){
			playCell("O", 4);
		} else {
			playCell("O", 0);
		}
	} else {
		int placeO = oneTurnAway("O");
		int placeX = oneTurnAway("X");
		// first priority win
		if ( placeO >=0){
			playCell("O", placeO);
		} // second priority don't lose
		else if (placeX >= 0){
			playCell("O", placeX);
		} // third priority go in the center
		else if (cells[4]==32){
			playCell("O", 4);
		} else {
			for (int i = 0; i < 4; i ++){
				if (cells[2*i+1] == 32){
					playCell("O", 2*i+1);
					break;
				}
			}
		}
	}
	
}
// return cell to go in if one turn away, return -1 else
int Board::oneTurnAway(string letter){
	vector<string> row = rows();
	int count = 0;
	int rowNumber = 0;
	for (auto & element : row) {
		count = 0;
		for (int i = 0; i < 3; i ++){
			if (element[i] == letter[0]){
				count++;
			} else if (element[i] != 32){
				break;
			}
		}
		if (count == 2){
			for (int i = 0; i < 3; i ++){
				if (element[i] == 32){
					if (rowNumber<3){
						return rowNumber*3+i;
					} else if (rowNumber<6){
						return rowNumber-3+3*i;
					} else if (rowNumber == 6){
						return (i+1)*(i+1)-1;
					} else if (rowNumber = 7){
						return (i+1)*2;
					}
					return 1;
				}
			}
			
		}
		rowNumber++;
	}
	return -1;


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
	string again = "y";
	while(again.compare("y")==0){
		Board board;
		cout << board.display()<< "\n";
		// board.playCell("X", 2);
		// cout << board.display()<< "\n";
		// board.playCell("X", 4);
		// cout << board.display()<< "\n";
		// board.oneTurnAway("X");
		// cout << board.display()<< "\n";

		while (board.gameOver() == 0 ){
			board.Xturn();
			cout << board.display()<< "\n";
			if (board.gameOver() ==0) {
				board.CompTurn();
				cout << board.display()<<"\n";
			}

		}
		if (board.gameOver() == 1){
			cout << "\n" << "You win\n";
		} else if (board.gameOver() == 2){
			cout << "\n" << "You lose\n";
		} else if (board.gameOver() == 3){
			cout << "\n" << "Its a tie\n";
		}
		cout << "would you like to play again? (y/n) \n";
		cin >> again;
	}

	return 0;
}


