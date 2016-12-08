//
//  piece.h
//  Checkers2
//
//  Created by Marcus Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#ifndef piece_h
#define piece_h

#include "coordinate.h"
#include "player.h"

#include <string>

class Piece {
private:
    Player *player_ptr;
    static Piece NULL_PIECE;
    static Coordinate moves[0];
    static Coordinate attacks[0];
    static int number_of_moves;
    static int number_of_attacks;
    static char even_empty_symbol;
public:
    static char player1_symbol;
    static char player2_symbol;
    static char empty_symbol;
    virtual char get_empty_symbol(Coordinate *);
    void set_even_empty_symbol(char);
    char get_even_empty_symbol();
    Piece(); // Default constructor

    Player *get_player_ptr();
    void set_player_ptr(Player *);

    virtual char get_player1_symbol();
    void static set_player1_symbol(char);

    virtual char get_player2_symbol();
    void static set_player2_symbol(char);
    static Piece* get_null_piece_ptr();

    virtual char get_symbol(Coordinate *);
    virtual Coordinate *get_moves();
    virtual Coordinate *get_attacks();

    virtual int get_number_of_moves();
    virtual int get_number_of_attacks();

};


#endif /* piece_h */
