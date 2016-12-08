//
//  checker.h
//  Checkers2
//
//  Created by Marcus Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#ifndef checker_h
#define checker_h


#include "coordinate.h"
#include "piece.h"
#include "player.h"

class Checker : public Piece {
private:
    static Coordinate up_moves_array[2];
    static Coordinate down_moves_array[2];
    static Coordinate up_attacks_array[2];
    static Coordinate down_attacks_array[2];
    static int number_of_up_moves;
    static int number_of_down_moves;
    static int number_of_up_attacks;
    static int number_of_down_attacks;
    static int number_of_king_moves;
    static int number_of_king_attacks;


    static Coordinate king_moves_array[4];
    static Coordinate king_attacks_array[4];

    static char player1_king_symbol;
    static char player2_king_symbol;

    bool is_king;

public:
    Checker();
    virtual Coordinate *get_moves() override;
    virtual Coordinate *get_attacks() override;

    bool get_is_king();
    void set_is_king(bool);

    char get_player1_king_symbol();
    char get_player2_king_symbol();

    virtual char get_symbol(Coordinate *) override;

    void set_player1_king_symbol(char);
    void set_player2_king_symbol(char);

    virtual int get_number_of_moves() override;
    virtual int get_number_of_attacks() override;

};



#endif /* checker_h */
