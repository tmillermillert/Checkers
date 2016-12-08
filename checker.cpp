//
//  checker.cpp
//  Checkers2
//
//  Created by Marcus Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#include <stdio.h>
#include "checker.h"

char Checker::player1_king_symbol = 'X';
char Checker::player2_king_symbol = 'O';

int Checker::number_of_up_moves = 2;
int Checker::number_of_down_moves = 2;
int Checker::number_of_up_attacks = 2;
int Checker::number_of_down_attacks = 2;
int Checker::number_of_king_moves = 4;
int Checker::number_of_king_attacks = 4;


Coordinate negative_one_one(-1, 1);
Coordinate one_one(1, 1);
Coordinate Checker::up_moves_array [2] = {negative_one_one, one_one};


Coordinate negative_one_negative_one(-1, -1);
Coordinate one_negative_one(1, -1);
Coordinate Checker::down_moves_array [2] = {negative_one_negative_one, one_negative_one};


Coordinate Checker::king_moves_array [4] = {negative_one_one, one_one,
    negative_one_negative_one, one_negative_one};


Coordinate negative_two_two(-2, 2);
Coordinate two_two(2, 2);
Coordinate Checker::up_attacks_array [2] = {negative_two_two, two_two};


Coordinate negative_two_negative_two(-2, -2);
Coordinate two_negative_two(2, -2);
Coordinate Checker::down_attacks_array [2] = {negative_two_negative_two, two_negative_two};

Coordinate Checker::king_attacks_array [4] = {negative_two_two, two_two,
    negative_two_negative_two, two_negative_two};

Checker::Checker() : Piece() {
    is_king = false;
}

Coordinate *Checker::get_moves() {
    Player *p_ptr = get_player_ptr();
    if (p_ptr) {
        int p_num = p_ptr->get_number();
        bool i_k = get_is_king();
        if (i_k == true) {
            return king_moves_array;
        } else if (p_num == 1) {
            return &up_moves_array[0];
        } else {
            return down_moves_array;
        }
    } else {
        return Coordinate::get_null_coordinate_ptr();
    }
}

Coordinate *Checker::get_attacks() {
    Player *p_ptr = get_player_ptr();
    if (p_ptr) {
        int p_num = p_ptr->get_number();
        bool i_k = get_is_king();
        if (i_k == true) {
            return king_attacks_array;
        } else if (p_num == 1) {
            return up_attacks_array;
        } else {
            return down_attacks_array;
        }
    } else {
        return Coordinate::get_null_coordinate_ptr();
    }
}

bool Checker::get_is_king() {
    return is_king;
}

char Checker::get_player1_king_symbol() {
    return player1_king_symbol;
}

char Checker::get_player2_king_symbol() {
    return player2_king_symbol;
}

char Checker::get_symbol(Coordinate *coordinate_ptr) {
    Player *p_ptr = get_player_ptr();
    if (p_ptr) {
        int p_num = p_ptr->get_number();
        bool i_k = get_is_king();
        if (p_ptr == Player::get_null_player_ptr()) {
            return Piece::get_empty_symbol(coordinate_ptr);
        } else if (i_k == true && p_num == 1) {
            return get_player1_king_symbol();
        } else if (i_k == true && p_num == 2) {
            return get_player2_king_symbol();
        } else if (p_num == 1) {
            return get_player1_symbol();
        } else {
            return get_player2_symbol();
        }
    } else {
        return '\0';
    }
}

void Checker::set_player1_king_symbol(char c) {
    player1_king_symbol = c;
}

void Checker::set_player2_king_symbol(char c) {
    player2_king_symbol = c;
}

int Checker::get_number_of_moves() {
    if (get_is_king()) {
        return number_of_king_moves;
    } else {
        return number_of_up_moves;
    }
}

int Checker::get_number_of_attacks() {
    if (get_is_king()) {
        return number_of_king_attacks;
    } else {
        return number_of_up_attacks;
    }
}

void Checker::set_is_king(bool i) {
    is_king = i;
}
