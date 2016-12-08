//
//  square.cpp
//  Checkers2
//
//  Created by Marcus Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#include <stdio.h>
#include "square.h"

using namespace std;

Square Square::NULL_SQUARE;

Square::Square(Coordinate* c, Piece* p, Square *u, Square *d, Square *r, Square *l,
        Square *ul, Square *ur, Square *dl, Square *dr) // Default constructor
{
    coordinate_ptr = c;
    piece_ptr = p;
    up_ptr = u;
    down_ptr = d;
    right_ptr = r;
    left_ptr = l;
    up_left_ptr = ul;
    up_right_ptr = ur;
    down_left_ptr = dl;
    down_right_ptr = dr;
}

Square *Square::get_null_square_ptr() {
    return &NULL_SQUARE;
}

Coordinate *Square::get_coordinate_ptr() {
    return coordinate_ptr;
}

void Square::set_coordinate_ptr(Coordinate *c) {
    coordinate_ptr = c;
}

Piece *Square::get_piece_ptr() {
    return piece_ptr;
}

void Square::set_piece_ptr(Piece *p) {
    piece_ptr = p;
}

Square *Square::get_up_ptr() {
    return up_ptr;
}

void Square::set_up_ptr(Square *u) {
    up_ptr = u;
}

Square *Square::get_down_ptr() {
    return down_ptr;
}

void Square::set_down_ptr(Square *d) {
    down_ptr = d;
}

Square *Square::get_right_ptr() {
    return right_ptr;
}

void Square::set_right_ptr(Square *r) {
    right_ptr = r;
}

Square *Square::get_left_ptr() {
    return left_ptr;
}

void Square::set_left_ptr(Square *l) {
    left_ptr = l;
}

Square *Square::get_up_left_ptr() {
    return up_left_ptr;
}

void Square::set_up_left_ptr(Square * ul) {
    up_left_ptr = ul;
}

Square *Square::get_up_right_ptr() {
    return up_right_ptr;
}

void Square::set_up_right_ptr(Square * ur) {
    up_right_ptr = ur;
}

Square *Square::get_down_left_ptr() {
    return down_left_ptr;
}

void Square::set_down_left_ptr(Square * dl) {
    down_left_ptr = dl;
}

Square *Square::get_down_right_ptr() {
    return down_right_ptr;
}

void Square::set_down_right_ptr(Square *dr) {
    down_right_ptr = dr;
}

// see if piece has that move

bool Square::piece_has_move(Coordinate* current) {
    Coordinate* this_coordinate_ptr = this->get_coordinate_ptr();
    if (this_coordinate_ptr == Coordinate::get_null_coordinate_ptr())
        return Square::get_null_square_ptr();

    Piece *p = get_piece_ptr();
    Coordinate *moves_ptr = p->get_moves();

    int number_of_moves = p->get_number_of_moves();
    for (int i = 0; i < number_of_moves; i++) {
        if (this_coordinate_ptr->add(&moves_ptr[i]).equal(current)) {
            return true;
        }
    }
    return false;

}


//see if square exist

Square *Square::get_square(Coordinate* current, Coordinate* previous, Coordinate* previous_previous) {
    Coordinate* this_coordinate_ptr = this->get_coordinate_ptr();
    if (this_coordinate_ptr == Coordinate::get_null_coordinate_ptr())
        return Square::get_null_square_ptr();
    if (this_coordinate_ptr == previous_previous)
        return Square::get_null_square_ptr();

    int tx = this_coordinate_ptr->get_x();
    int ty = this_coordinate_ptr->get_y();
    int cx = current->get_x();
    int cy = current->get_y();

    if (tx == cx && ty == cy) {
        return this;
    } else if (tx < cx && ty < cy) {
        return get_up_right_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else if (tx > cx && ty > cy) {
        return get_down_left_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else if (tx > cx && ty < cy) {
        return get_up_left_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else if (tx < cx && ty > cy) {
        return get_down_right_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else if (tx < cx) {
        return get_right_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else if (ty < cy) {
        return get_up_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else if (tx > cx) {
        return get_left_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else if (ty > cy) {
        return get_down_ptr()->get_square(current, this_coordinate_ptr, previous);
    } else {
        return Square::get_null_square_ptr(); //error
    }

}

// see if the player has a piece a square

bool Square::has_piece(Coordinate *coordinate_ptr, Player *player_ptr) {
    Square *square_ptr;
    square_ptr = get_square(coordinate_ptr);
    if (square_ptr == Square::get_null_square_ptr()) {
        return false;
    } else {
        Piece * piece_ptr = square_ptr->get_piece_ptr();
        if (piece_ptr == Piece::get_null_piece_ptr()) {
            return false;
        } else if (piece_ptr->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    }
}

// see if square exist
// see if player has piece there
// see if see if piece has that move
// see if there are any pieces in between

//see if square exist

bool Square::piece_inbetween(Coordinate* current) {
    Coordinate* this_coordinate_ptr = this->get_coordinate_ptr();

    int tx = this_coordinate_ptr->get_x();
    int ty = this_coordinate_ptr->get_y();
    int cx = current->get_x();
    int cy = current->get_y();

    if (tx == cx && ty == cy) {
        return false;
    } else if (tx < cx && ty < cy) {
        if (get_up_right_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_up_right_ptr()->piece_inbetween(current);
    } else if (tx > cx && ty > cy) {
        if (get_down_left_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_down_left_ptr()->piece_inbetween(current);
    } else if (tx > cx && ty < cy) {
        if (get_up_left_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_up_left_ptr()->piece_inbetween(current);
    } else if (tx < cx && ty > cy) {
        if (get_down_right_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_down_right_ptr()->piece_inbetween(current);
    } else if (tx < cx) {
        if (get_right_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_right_ptr()->piece_inbetween(current);
    } else if (ty < cy) {
        if (get_up_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_up_ptr()->piece_inbetween(current);
    } else if (tx > cx) {
        if (get_left_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_left_ptr()->piece_inbetween(current);
    } else if (ty > cy) {
        if (get_down_ptr()->get_piece_ptr() != Piece::get_null_piece_ptr()) {
            return true;
        }
        return get_down_ptr()->piece_inbetween(current);
    } else {
        return true;
    }

}

Square *Square::move_piece(Coordinate *coordinate_ptr, Player* player_ptr) {
    Square* square_ptr;
    bool is_piece;
    square_ptr = get_square(coordinate_ptr);
    if (square_ptr == Square::get_null_square_ptr()) {
        return Square::get_null_square_ptr();
    }
    is_piece = has_piece(get_coordinate_ptr(), player_ptr);
    if (is_piece == false) {
        return Square::get_null_square_ptr();
    }
    bool is_move;
    is_move = piece_has_move(coordinate_ptr);
    if (is_move == false) {
        return Square::get_null_square_ptr();
    }
    bool is_inbetween;
    is_inbetween = piece_inbetween(coordinate_ptr);
    if (is_inbetween) {
        return Square::get_null_square_ptr();
    }
    Piece *moving_piece = get_piece_ptr();
    set_piece_ptr(Piece::get_null_piece_ptr());
    square_ptr->set_piece_ptr(moving_piece);
    if (coordinate_ptr->get_y() == 7 || coordinate_ptr->get_y() == 0) {
        Checker * c_ptr = static_cast<Checker *> (square_ptr->get_piece_ptr());
        c_ptr->set_is_king(true);
    }
    return square_ptr;
}

bool Square::piece_has_jump(Coordinate* current) {
    Coordinate* this_coordinate_ptr = this->get_coordinate_ptr();
    if (this_coordinate_ptr == Coordinate::get_null_coordinate_ptr())
        return Square::get_null_square_ptr();

    Piece *p = get_piece_ptr();
    Coordinate *jumps_ptr = p->get_attacks();

    int number_of_attacks = p->get_number_of_attacks();
    for (int i = 0; i < number_of_attacks; i++) {
        if (this_coordinate_ptr->add(&jumps_ptr[i]).equal(current)) {
            return true;
        }
    }
    return false;

}

// see if square exist
// see if player has piece there
// see if the piece has that move
// see if there is a checker in-between
//

Square *Square::jump_piece(Coordinate *coordinate_ptr, Player* player_ptr) {
    Square* square_ptr;
    bool is_piece;
    square_ptr = get_square(coordinate_ptr);
    if (square_ptr == Square::get_null_square_ptr()) {
        return Square::get_null_square_ptr();
    }
    is_piece = has_piece(get_coordinate_ptr(), player_ptr);
    if (is_piece == false) {
        return Square::get_null_square_ptr();
    }
    bool is_move;
    is_move = piece_has_jump(coordinate_ptr);
    if (is_move == false) {
        return Square::get_null_square_ptr();
    }
    bool is_inbetween;
    is_inbetween = opponent_piece_inbetween(coordinate_ptr, player_ptr);
    if (is_inbetween == false) {
        return Square::get_null_square_ptr();
    }
    Square *square_inbetween_piece_ptr;
    square_inbetween_piece_ptr = get_piece_in_direction(coordinate_ptr);
    square_inbetween_piece_ptr->set_piece_ptr(Piece::get_null_piece_ptr());
    Piece *moving_piece = get_piece_ptr();
    set_piece_ptr(Piece::get_null_piece_ptr());
    square_ptr->set_piece_ptr(moving_piece);
    if (coordinate_ptr->get_y() == 7 || coordinate_ptr->get_y() == 0) {
        Checker * c_ptr = static_cast<Checker *> (square_ptr->get_piece_ptr());
        c_ptr->set_is_king(true);
    }
    return square_ptr;
}

bool Square::opponent_piece_inbetween(Coordinate* current, Player *player_ptr) {
    Coordinate* this_coordinate_ptr = this->get_coordinate_ptr();

    int tx = this_coordinate_ptr->get_x();
    int ty = this_coordinate_ptr->get_y();
    int cx = current->get_x();
    int cy = current->get_y();

    if (tx < cx && ty < cy) {
        if (get_up_right_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_up_right_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else if (tx > cx && ty > cy) {
        if (get_down_left_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_down_left_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else if (tx > cx && ty < cy) {
        if (get_up_left_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_up_left_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else if (tx < cx && ty > cy) {
        if (get_down_right_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_down_right_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else if (tx < cx) {
        if (get_right_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_right_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else if (ty < cy) {
        if (get_up_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_up_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else if (tx > cx) {
        if (get_left_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_left_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else if (ty > cy) {
        if (get_down_ptr()->get_piece_ptr() == Piece::get_null_piece_ptr()
                || get_down_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return false;
        } else {
            return true;
        }
    } else {
        cout << "Error\n\n\n";
        return true;
    }

}

bool Square::my_piece_inbetween(Coordinate* current, Player *player_ptr) {
    Coordinate* this_coordinate_ptr = this->get_coordinate_ptr();

    int tx = this_coordinate_ptr->get_x();
    int ty = this_coordinate_ptr->get_y();
    int cx = current->get_x();
    int cy = current->get_y();

    if (tx < cx && ty < cy) {
        if (get_up_right_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else if (tx > cx && ty > cy) {
        if (get_down_left_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else if (tx > cx && ty < cy) {
        if (get_up_left_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else if (tx < cx && ty > cy) {
        if (get_down_right_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else if (tx < cx) {
        if (get_right_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else if (ty < cy) {
        if (get_up_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else if (tx > cx) {
        if (get_left_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else if (ty > cy) {
        if (get_down_ptr()->get_piece_ptr()->get_player_ptr() == player_ptr) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }

}

Square *Square::get_piece_in_direction(Coordinate* current) {
    Coordinate* this_coordinate_ptr = this->get_coordinate_ptr();

    int tx = this_coordinate_ptr->get_x();
    int ty = this_coordinate_ptr->get_y();
    int cx = current->get_x();
    int cy = current->get_y();

    if (tx < cx && ty < cy) // move up and to the right
    {
        return get_up_right_ptr();
    } else if (tx > cx && ty > cy) // move down and to the left
    {
        return get_down_left_ptr();
    } else if (tx > cx && ty < cy) // move up and to the left
    {
        return get_up_left_ptr();
    } else if (tx < cx && ty > cy) // move down and to the right
    {
        return get_down_right_ptr();
    } else if (tx < cx) // move to the right
    {
        return get_right_ptr();
    } else if (ty < cy) // move up
    {
        return get_up_ptr();
    } else if (tx > cx) // move left
    {
        return get_left_ptr();
    } else if (ty > cy) // move down
    {
        return get_down_ptr();
    } else {
        cout << "Error\n\n\n";
        return Square::get_null_square_ptr();
    }
}


