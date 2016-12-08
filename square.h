//
//  square.h
//  Checkers2
//
//  Created by Marcus Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#ifndef square_h
#define square_h

#include "coordinate.h"
#include "player.h"
#include "piece.h"
#include "checker.h"

class Square {
private:
    Coordinate *coordinate_ptr;
    Piece *piece_ptr;
    Square *up_ptr;
    Square *down_ptr;
    Square *right_ptr;
    Square *left_ptr;
    Square *up_left_ptr;
    Square *up_right_ptr;
    Square *down_left_ptr;
    Square *down_right_ptr;
    static Square NULL_SQUARE;
public:
    Square(Coordinate* c = Coordinate::get_null_coordinate_ptr(), Piece* p = Piece::get_null_piece_ptr(), Square *u = Square::get_null_square_ptr(), Square *d =
            Square::get_null_square_ptr(), Square *r = Square::get_null_square_ptr(), Square *l = Square::get_null_square_ptr(),
            Square *ul = Square::get_null_square_ptr(), Square *ur = Square::get_null_square_ptr(), Square *dl = Square::get_null_square_ptr(), Square *dr = Square::get_null_square_ptr()); // Default constructor

    Coordinate *get_coordinate_ptr();
    void set_coordinate_ptr(Coordinate *);

    virtual Piece *get_piece_ptr();
    virtual void set_piece_ptr(Piece *);

    Square *get_up_ptr();
    void set_up_ptr(Square *);

    Square *get_down_ptr();
    void set_down_ptr(Square *);

    Square *get_right_ptr();
    void set_right_ptr(Square *);

    Square *get_left_ptr();
    void set_left_ptr(Square *);

    Square *get_up_left_ptr();
    void set_up_left_ptr(Square *);

    Square *get_up_right_ptr();
    void set_up_right_ptr(Square *);

    Square *get_down_left_ptr();
    void set_down_left_ptr(Square *);

    Square *get_down_right_ptr();
    void set_down_right_ptr(Square *);

    static Square *get_null_square_ptr();

    Square *get_square(Coordinate*,
            Coordinate* previous = Coordinate::get_null_coordinate_ptr(),
            Coordinate* previous_previous = Coordinate::get_null_coordinate_ptr());

    bool has_piece(Coordinate *, Player*);
    bool piece_has_move(Coordinate*);
    bool piece_inbetween(Coordinate*);
    Square *move_piece(Coordinate *, Player*);
    bool piece_has_jump(Coordinate* current);
    Square *jump_piece(Coordinate *coordinate_ptr, Player* player_ptr);
    bool opponent_piece_inbetween(Coordinate* current, Player *player_ptr);
    bool my_piece_inbetween(Coordinate* current, Player *player_ptr);
    Square *get_piece_in_direction(Coordinate* current);
};
#endif /* square_h */
