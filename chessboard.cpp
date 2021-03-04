#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int top_border[8] = {1, 2, 3, 4, 5, 6, 7, 8};	

string board[8][8] = {
			{"r", "k", "b", "K", "Q", "b", "k", "r"},
			{"p", "p", "p", "p", "p", "p", "p", "p"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"p", "p", "p", "p", "p", "p", "p", "p"},
			{"r","k","b", "Q", "K", "b", "k", "r"}
	 		};

string original[8][8] = {
			{"r", "k", "b", "K", "Q", "b", "k", "r"},
			{"p", "p", "p", "p", "p", "p", "p", "p"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"*", "*", "*", "*", "*", "*", "*", "*"},
			{"p", "p", "p", "p", "p", "p", "p", "p"},
			{"r","k","b", "Q", "K", "b", "k", "r"}
	 		};

void print_chess_board() {
	cout<<"  ";
	for (int k = 0; k < 8; k++) {
		cout <<top_border[k]<<" ";
	}
	cout <<"\n";
	for (int i = 0; i < 8; i++) {
		cout <<i+1<<" ";
		for (int j = 0; j < 8; j++) {
			cout<<board[i][j]<<" ";
		}
		cout <<"\n";
	}
}

void print_original() {
	cout<<"  ";
	for (int k = 0; k < 8; k++) {
		cout <<top_border[k]<<" ";
	}
	cout <<"\n";
	for (int i = 0; i < 8; i++) {
		cout <<i+1<<" ";
		for (int j = 0; j < 8; j++) {
			cout<<original[i][j]<<" ";
		}
		cout <<"\n";
	}
}

void print_help() {
	system("cls");
	cout<<"		Help Menu:"<<endl;
	cout<<" / - for meta commands"<<endl;
	cout<<" . - for game commands"<<endl;
	cout<<" "<<endl;
	cout<<"		Meta commands:"<<endl;
	cout<<  " reset - reset game board"<<endl;
	cout<<	" invert - change terminal color to w/b"<<endl;
	cout<<	" revert - change terminal color to b/w"<<endl;
	cout<<	" exit"<<endl;
	cout<<	"	Game commands:"<<endl;
	cout<<	" basic format:"<<endl;
	cout<<	" {chess piece} {color} {original column} {original row} {new column} {new row}"<<endl;
	cout<<" "<<endl;
	print_chess_board();
}

void print_prompt() {
	cout <<"Command>> ";
}

vector<int>history;

#define COMMAND_SUCCESS 1
#define COMMAND_UNKNOWN 0

int meta_input(string input) {
	if (input == "exit") {
		system("cls");
		exit(0);
	}
	else if (input == "reset") {
		system("cls");
		print_original();
		return COMMAND_SUCCESS;
	}
	else if (input == "invert") {
		system("color f0");
		return COMMAND_SUCCESS;
	}
	else if (input == "revert") {
		system("color 0f");
		return COMMAND_SUCCESS;
	}
	else if (input == "help") {
		print_help();
		return COMMAND_SUCCESS;
	}
	else {
		return COMMAND_UNKNOWN;
	}
}

#define WRONG_SIDE 3

int check_side(string color, int side) {
	if (side == 0) {
		return COMMAND_SUCCESS;
	}
	else {
		if (color == "w" && (side % 2 == 0) || color == "b" && (side % 2 != 0)) {
			return WRONG_SIDE; 
		}
		return COMMAND_SUCCESS;
	}
}

void wrong_side(string character) {
	cout<<"Error. That is not your "<<character<<endl;
}


void not_selected(string character) {
	cout <<"Error. "<<character<<" not selected"<<endl;
}

void replace(int origin_c, int origin_r, int new_c, int new_r, char character) {
	board[new_c - 1][new_r - 1] = character;
	board[origin_c - 1][origin_r - 1] = '*';	
	system("cls");
	print_chess_board();
}

string pawn = "pawn"; // 1
string rook = "rook"; // 2
string knight = "knight"; // 3
string bishop = "bishop"; // 4
string queen = "Queen"; // 5
string king = "King"; // 6

void queen_move(string move, string color, int origin_c, int origin_r, int new_c, int new_r, int side) {
	if (abs(origin_c-new_c)==4 && abs(origin_r-new_r)!=2 || abs(origin_c-new_c)==2 && abs(origin_r-new_r) != 4) {
		cout <<"Error. Knights cant move that way."<<endl;
	}
	else if (board[origin_c - 1][origin_r - 1] != "Q") {
		not_selected(queen);
		side--;
	}
	else {
		switch(check_side(color, side)) {
			case (WRONG_SIDE):
				wrong_side(queen);
				break;
			case (COMMAND_SUCCESS):
				char character = 'Q';
				replace(origin_c, origin_r, new_c, new_r, character);
				break;
		}
	}
}


void knight_move(string move, string color, int origin_c, int origin_r, int new_c, int new_r, int side) {
	if (abs(origin_c-new_c)==4 && abs(origin_r-new_r)!=2 || abs(origin_c-new_c)==2 && abs(origin_r-new_r) != 4) {
		cout <<"Error. Knights cant move that way."<<endl;
	}
	else if (board[origin_c - 1][origin_r - 1] != "K") {
		not_selected(knight);
		side--;
	}
	else {
		switch(check_side(color, side)) {
			case (WRONG_SIDE):
				wrong_side(knight);
				break;
			case (COMMAND_SUCCESS):
				char character = 'k';
				replace(origin_c, origin_r, new_c, new_r, character);
				break;
		}
	}
}


void king_move(string move, string color, int origin_c, int origin_r, int new_c, int new_r, int side) {
	if ( abs(origin_c - new_c) > 1 || abs(origin_r - new_r) > 1 ) {
		cout <<"Error. Kings can only move 1 block at a time."<<endl;
	}
	else if (board[origin_c - 1][origin_r - 1] != "K") {
		not_selected(king);
		side--;
	}
	else {
		switch(check_side(color, side)) {
			case (WRONG_SIDE):
				wrong_side(king);
				break;
			case (COMMAND_SUCCESS):
				char character = 'K';
				replace(origin_c, origin_r, new_c, new_r, character);
				break;
		}
	}
}

void bishop_move(string move, string color, int origin_c, int origin_r, int new_c, int new_r, int side) {
	if (abs(origin_c-new_c) == 0 && abs(origin_r-new_r) > 0||abs(origin_c-new_c) > 0 && abs(origin_r-new_r) == 0) {
		cout <<"Error. Bishops can only move diagonally."<<endl;
	}
	else if (board[origin_c - 1][origin_r - 1] != "b") {
		not_selected(bishop);
		side--;
	}
	else {
		switch(check_side(color, side)) {
			case (WRONG_SIDE):
				wrong_side(bishop);
				break;
			case (COMMAND_SUCCESS):
				char character = 'b';
				replace(origin_c, origin_r, new_c, new_r, character);
				break;
		}
	}
}

void rook_move(string move, string color, int origin_c, int origin_r, int new_c, int new_r, int side) {
	if (abs(origin_c - new_c) > 0 && abs(origin_r - new_r) > 0 ) {
		cout <<"Error. Rooks cant move diagonally."<<endl;
		side--;
	}
	else if (board[origin_c - 1][origin_r - 1] != "r") {
		not_selected(rook);
		side--;
	}
	else {
		switch(check_side(color, side)) {
			case (WRONG_SIDE):
				wrong_side(rook);
				break;
			case (COMMAND_SUCCESS):
				char character = 'r';
				replace(origin_c, origin_r, new_c, new_r, character);
				break;
		}
	}
}

void pawn_move(string move, string color, int origin_c, int origin_r, int new_c, int new_r, int side) {
	if ( abs(origin_c - new_c) > 2 || abs(origin_r - new_r) > 1) {
		cout <<"Error. Pawn cant move that many blocks."<<endl;
		side--;
	}
	else if (board[origin_c - 1][origin_r - 1] != "p") {
		not_selected(pawn);
		side--;
	}
	else {
		switch(check_side(color, side)) {
			case (WRONG_SIDE):
				wrong_side(pawn);
				break;
			case (COMMAND_SUCCESS):
				char character = 'p';
				replace(origin_c, origin_r, new_c, new_r, character);
				break;
		}
	}
}

void game_input(string name, string color, int origin_c, int origin_r, int new_c, int new_r, int side) {
	if (name == "pawn") {
		pawn_move(name, color, origin_c, origin_r, new_c, new_r, side);
	}
	else if (name == "rook") {
		rook_move(name, color, origin_c, origin_r, new_c, new_r, side);
	}
	else if (name == "bishop") {
		bishop_move(name, color, origin_c, origin_r, new_c, new_r, side);
	}
	else if (name == "king") {
		king_move(name, color, origin_c, origin_r, new_c, new_r, side);
	}
	else if (name == "queen") {
		queen_move(name, color, origin_c, origin_r, new_c, new_r, side);
	}
	else if (name == "knight") {
		knight_move(name, color, origin_c, origin_r, new_c, new_r, side);
	}
	else {
		cout <<"Error. Missing or unknown variable."<<endl;
	}
}
//This works. But it has to be in the format: .pawn w 1 1 to 1 2
//To do: create a error function to catch bugs.  
int main() {
	print_help();
	int side = 0;
	while(true) {
		print_prompt();
		string name, color, symbol;
		int origin_c, origin_r, new_c, new_r;
		string init;
		cin >> init; 
		if (init == "/") {
			print_prompt();
			cin >> name;
			switch(meta_input(name)) {
				case (COMMAND_SUCCESS):
					cout <<"--executed--\n";
					continue;
				case (COMMAND_UNKNOWN):
					cout <<"Error: Unknown command.\n";
					continue;
			}	
		}
		else if (init == ".") {
			print_prompt();
			cin >> name >> color>> origin_c>> origin_r>>symbol>> new_c>>new_r;
			side += 1;
			game_input(name,color, origin_c,origin_r,new_c,new_r,side);
		}
		else {
			cout <<"Error: Unknown command. \n";
		}
	}
}



