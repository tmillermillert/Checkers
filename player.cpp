//
//  player.cpp
//  Checkers2
//
//  Created by Marcus Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//


#include "player.h"
#include "square.h"
using namespace std;

int Player::NULL_NUMBER = -100;

int *Player::get_null_number_ptr() {
    return &NULL_NUMBER;
}

Player::Player() // Default constructor
{
    number = *get_null_number_ptr();
}

Player::Player(int n) {
    number = n;
}

int Player::get_move(Square square_array[][8], Coordinate start_moves[], Coordinate start_jumps[], int num_start_moves, int num_start_jumps) {
    char tmp = ' ';
    bool is_in = false;
    int selection = 0;
    while (is_in == false) {
        cin.ignore(INT_MAX, '\n');
        cout << "Enter number: ";
        cin >> tmp;
        if (tmp == 'q') {
            return -1;
        } else if (tmp == 's') {
            return -2;
        } else if (tmp == 'm') {
            return -3;
        }
        if (isdigit(tmp) == false) {
            selection = -1;
        } else {
            selection = tmp - 48;
        }
        if (num_start_jumps > 0) {
            if (selection >= 0 && selection < num_start_jumps) {
                return selection;
            }
        } else {
            if (selection >= 0 && selection < num_start_moves) {
                return selection;
            }
        }
        cout << "Invalid choice!\n";
    }
    return selection;

}

int Player::get_number() {
    return number;
}

void Player::set_number(int i) {
    number = i;
}

Player Player::NULL_PLAYER;

Player *Player::get_null_player_ptr() {
    return &NULL_PLAYER;
}
