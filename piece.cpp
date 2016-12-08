//
//  piece.cpp
//  Checkers2
//
//  Created by Darlene Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#include <stdio.h>
#include "piece.h"

char Piece::player1_symbol = 'x';
char Piece::player2_symbol = 'o';
char Piece::empty_symbol = ' ';
char Piece::even_empty_symbol = ' ';
Piece Piece::NULL_PIECE;
Coordinate Piece::moves[0];
Coordinate Piece::attacks[0];
int Piece::number_of_moves = 0;
int Piece::number_of_attacks = 0;

Piece* Piece::get_null_piece_ptr() {
    return &Piece::NULL_PIECE;
}

Player *Piece::get_player_ptr() {
    return player_ptr;
}

void Piece::set_player_ptr(Player *p) {
    player_ptr = p;
}

char Piece::get_player1_symbol() {
    return player1_symbol;
}

void set_player1_symbol(char c) {
    Piece::player1_symbol = c;
}

char Piece::get_player2_symbol() {
    return player2_symbol;
}

void Piece::set_player2_symbol(char c) {
    Piece::player2_symbol = c;
}

char Piece::get_empty_symbol(Coordinate* coordinate_ptr) {
    int x = coordinate_ptr->get_x();
    int y = coordinate_ptr->get_y();
    if ((x + y) % 2 == 0) {
        return get_even_empty_symbol();

    } else {
        return empty_symbol;
    }
}

// Default constructor

Piece::Piece() {
    player_ptr = Player::get_null_player_ptr();
}

char Piece::get_symbol(Coordinate * coordinate_ptr) {
    Player *p_ptr = get_player_ptr();
    if (p_ptr == Player::get_null_player_ptr()) {
        return get_empty_symbol(coordinate_ptr);
    } else if (p_ptr->get_number() == 1) {
        return get_player1_symbol();
    } else {
        return get_player2_symbol();
    }
}

Coordinate *Piece::get_moves() {
    return moves;
}

Coordinate *Piece::get_attacks() {
    return attacks;
}

int Piece::get_number_of_moves() {
    return number_of_moves;
}

int Piece::get_number_of_attacks() {
    return number_of_attacks;
}

void Piece::set_even_empty_symbol(char c) {
    even_empty_symbol = c;
}

char Piece::get_even_empty_symbol() {
    return even_empty_symbol;
}
