//
//  computer_player.h
//  Checkers2
//
//  Created by Darlene Miller on 10/18/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#ifndef computer_player_h
#define computer_player_h

#include "player.h"

class Computer_player : public Player {
public:
    virtual int get_move(Square square_array[][8], Coordinate start_moves[], Coordinate start_jumps[], int num_start_moves, int num_start_jumps) override;
    Computer_player(int i);
};


#endif /* computer_player_h */
