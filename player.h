//
//  player.h
//  Checkers2
//
//  Created by Darlene Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#ifndef player_h
#define player_h

class Square;
#include "coordinate.h"
#include <iostream>
#include <stdio.h>

class Player {
private:
    int number;
    static Player NULL_PLAYER;
    static int NULL_NUMBER;
public:
    Player(); // Default constructor
    Player(int);
    virtual int get_move(Square square_array[][8], Coordinate start_moves[], Coordinate start_jumps[], int num_start_moves, int num_start_jumps);
    static Player *get_null_player_ptr();
    static int *get_null_number_ptr();

    int get_number();
    void set_number(int);

};

#endif /* player_h */
