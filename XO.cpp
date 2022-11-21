#include "XO.hpp"

XO::XO() {//The method is a default consturctor




}

XO::XO(const int8_t* play, const uint8_t* pos, const uint8_t& n) {//The method is a copy constructor, which can copy the board 
	for (int i = 0; i < n; i++) {//Use for loop to copy all the variable in the board
		b.state[pos[i]] = play[i];
		b.moves[i] = pos[i];
		b.turn[i] = play[i];
	}
	b.numMoves = n;

}


void XO::show() {//This method help us to console out the board
	std::cout << b<<std::endl;
}


bool XO::makeMove(const int8_t& play, const uint8_t& pos) {//This method is a command which can place the player marker in the board
	if (pos > 8) {//check whether oversize
		return false;
	}
	if (gameOver()) {
		return false;
	}
	for (int i = 0; i < b.numMoves; i++) {//check whether the position have been occupied
		if (b.moves[i] == pos) {
			return false;
		}
	}
	int8_t a = 1;
	if (b.numMoves > 0) {//check whether the order is corret;
		a = b.numMoves - 1;
		if (b.turn[a] == play) {
			return false;
		}
	}
	if (play != 1 ) {//check whether the input of player is correct
		if (play != -1) {
			return false;
		}
	}
	//put the value into the board
	b.state[pos] = play;
	b.moves[b.numMoves] = pos;
	b.turn[b.numMoves] = play;
	b.numMoves++;
	//for (int i = 0; i < b.numMoves; i++) {
	//	std::cout << b.turn[i];
	//}
	//for (int i = 0; i < b.numMoves; i++) {
	//	std::cout << b.moves[i];
	//}
	return true;
}


bool XO::makeMoves(const int8_t* play, const uint8_t* pos, const uint8_t& n) {//This method could help us to mark the players quickly and easy in the board, since it could plug multiply rounds in the board
	if (gameOver()) {
		return false;
	}
	if (n + b.numMoves > 9) {//check whether oversize
		return false;
	}
	for (int i = 0; i < n; i++) {//check whether the input position oversize
		if (pos[i] > 8) {
			return false;
		}

	}
	for (int j = 0; j < n; j++) {//check whether each position have been occupied
		for (int i = 0; i < b.numMoves; i++) {
			if (b.moves[i] == pos[i]) {
				return false;
			}
		}
	}
	for (int i = 0; i < n; i++) {//Check whether the input players are valid
		if (play[i] != 1) {
			if (play[i] != -1) {
				return false;
			}
		}
	}

	for (int i = 0; i < n - 1; i++) {//Check whether the order has been in order
		if (play[i] == play[i + 1]) {
			return false;
		}
	}
	if (b.numMoves > 0) {
		if (play[0] == b.turn[b.numMoves - 1]) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {//Put the value into the board
		b.state[pos[i]] = play[i];
		b.moves[b.numMoves] = pos[i];
		b.turn[b.numMoves] = play[i];
		b.numMoves++;
//		makeMove(play[i], pos[i]);
	}

	return true;

}

int8_t XO::winner(const BoardXO& brd) {//This method help us to know who is the winner or tie
	for (int i = 0; i < 3; i++) {//row win
		if (brd.state[i * 3 + 0] != 0) {
			if (brd.state[i * 3 + 0] == brd.state[i * 3 + 1] && brd.state[i * 3 + 0] == brd.state[i * 3 + 2]) {
				return brd.state[i * 3 + 0];
			}
		}
	}
	for (int i = 0; i < 3; i++) {//vertical win
		if (brd.state[0 * 3 + i] != 0) {
			if (brd.state[0 * 3 + i] == brd.state[1 * 3 + i] && brd.state[0 * 3 + i] == brd.state[2 * 3 + i]) {
				return brd.state[0 * 3 + i];
			}
		}
	}
	if (brd.state[0] != 0) {//check right incline
		if (brd.state[0] == brd.state[4] && brd.state[0] == brd.state[8]) {
			return brd.state[0];
		}
	}
	if (brd.state[2] != 0) {//check left incline
		if (brd.state[2] == brd.state[4] && brd.state[2] == brd.state[6]) {
			return brd.state[2];
		}
	}
	if (brd.numMoves == 9) {//check whether draw
		return 0;
	}
}



bool XO::makeOptimalMove() {//This method use AI to find the bestway to move
	int bestmove;
	int bestscore;
	int score;
	int player;
	//find the current player
	if (b.turn[b.numMoves - 1] == -1) {
		player = 1;
	}
	else {
		player = -1;
	}
	if (player == -1) {//if player is X
		bestscore = 1000;
		for (int i = 0; i < 3; i++) {//check all position in the board
			for (int j = 0; j < 3; j++) {
				if (b.state[i * 3 + j] == 0) {
					b.state[i * 3 + j] = player;//occupied the board to test
					b.numMoves++;
					score = minimax(b, player);
					b.state[i * 3 + j] = 0;//unoccupied 
					b.numMoves--;
					if (bestscore == 1000) {//At the first time, give the bestscore corret value
						bestscore = score;
						bestmove = i * 3 + j;
					}
					if (score > bestscore) {//Check whether there is a better way that could make x win.
						bestscore = score;
						bestmove = i * 3 + j;
					}
					if (score == bestscore) {//right tree pinciple
						bestscore = score;
						bestmove = i * 3 + j;
					}
				}
			}
		}
	}
	else if (player == 1) {//if player is O
		bestscore = 1000;
		for (int i = 0; i < 3; i++) {//check all position in the board
			for (int j = 0; j < 3; j++) {
				if (b.state[i * 3 + j] == 0) {
					b.state[i * 3 + j] = player;//occupied the board to test
					b.numMoves++;
					score = minimax(b, player);
					b.state[i * 3 + j] = 0;//unoccupied 
					b.numMoves--;
					if (bestscore == 1000) {//At the first time, give the bestscore corret value
						bestscore = score;
						bestmove = i * 3 + j;
					}
					if (score < bestscore) {//Check whether there is a better way that could make x win.
						bestscore = score;
						bestmove = i * 3 + j;
					}
					if (score == bestscore) {//right tree pinciple
						bestscore = score;
						bestmove = i * 3 + j;
					}
				}
			}
		}

	}
	//b.state[bestmove] = player;
	//b.turn[b.numMoves] = player;
	//b.moves[b.numMoves] = bestmove;
	//b.numMoves++;
	makeMove(player, bestmove);
	return true;
}


int8_t XO::minimax(const BoardXO& brd, const int8_t& play) {

	int bestscore;
	int score;
	int player = play;
	//check whether there is the winner, if yes return the correct value
	if (winner(b) == 1) {
		return b.numMoves - 10;
	}
	else if (winner(b) == -1) {
		return 10 - b.numMoves;
	}
	else if (winner(b) == 0) {
		return 0;
	}
	if (play == 1) {
		player = -1;
	}
	else {
		player = 1;
	}

	if (player == -1) {//if player is X
		bestscore = 1000;
		for (int i = 0; i < 3; i++) {//check all position in the board
			for (int j = 0; j < 3; j++) {
				if (b.state[i * 3 + j] == 0) {//occupied the board to test
					b.state[i * 3 + j] = player;
					b.numMoves++;
					score = minimax(b, player);
					b.state[i * 3 + j] = 0;//unoccupied 
					b.numMoves--;
					if (bestscore == 1000) {//At the first time, give the bestscore corret value
						bestscore = score;
					}
					if (score > bestscore) {//Check whether there is a better way that could make x win.
						bestscore = score;
					}
				}
			}
		}
		return bestscore;
	}
	else if (player == 1) {//if player is O
		bestscore = 1000;
		for (int i = 0; i < 3; i++) {//check all position in the board
			for (int j = 0; j < 3; j++) {
				if (b.state[i * 3 + j] == 0) {//occupied the board to test
					b.state[i * 3 + j] = player;
					b.numMoves++;
					score = minimax(b, player);
					b.state[i * 3 + j] = 0;//unoccupied 
					b.numMoves--;
					if (bestscore == 1000) {//At the first time, give the bestscore corret value
						bestscore = score;
					}
					if (score < bestscore) {//Check whether there is a better way that could make x win.
						bestscore = score;
					}
				}
			}
		}
		return bestscore;
	}
}

BoardXO XO::getBoard() {//This method help to debug and shows the board
	return b;
}

bool XO::gameOver() {//This method helpus to check whether the game is over
	for (int i = 0; i < 3; i++) {//row win
		if (b.state[i * 3 + 0] != 0) {
			if (b.state[i * 3 + 0] == b.state[i * 3 + 1] && b.state[i * 3 + 0] == b.state[i * 3 + 2]) {
				return true;
			}
		}
	}
	for (int i = 0; i < 3; i++) {//vertical win
		if (b.state[0 * 3 + i] != 0) {
			if (b.state[0 * 3 + i] == b.state[1 * 3 + i] && b.state[0 * 3 + i] == b.state[2 * 3 + i]) {
				return true;
			}
		}
	}
	if (b.state[0] != 0) {//check right incline
		if (b.state[0] == b.state[4] && b.state[0] == b.state[8]) {
			return true;
		}
	}
	if (b.state[2] != 0) {//check left incline
		if (b.state[2] == b.state[4] && b.state[2] == b.state[6]) {
			return true;
		}
	}
	if (b.numMoves == 9) {//check whether draw
		return true;
	}
	return false;
}

int8_t XO::winner() {//This method help us to find who is the winenr
	for (int i = 0; i < 3; i++) {//row win
		if (b.state[i * 3 + 0] != 0) {
			if (b.state[i * 3 + 0] == b.state[i * 3 + 1] && b.state[i * 3 + 0] == b.state[i * 3 + 2]) {
				return b.state[i * 3 + 0];
			}
		}
	}
	for (int i = 0; i < 3; i++) {//vertical win
		if (b.state[0 * 3 + i] != 0) {
			if (b.state[0 * 3 + i] == b.state[1 * 3 + i] && b.state[0 * 3 + i] == b.state[2 * 3 + i]) {
				return b.state[0 * 3 + i];
			}
		}
	}
	if (b.state[0] != 0) {//check right incline
		if (b.state[0] == b.state[4] && b.state[0] == b.state[8]) {
			return b.state[0];
		}
	}
	if (b.state[2] != 0) {//check left incline
		if (b.state[2] == b.state[4] && b.state[2] == b.state[6]) {
			return b.state[2];
		}
	}
	return 0;
}