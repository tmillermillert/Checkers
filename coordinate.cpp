//
//  coordinate.cpp
//  Checkers2
//
//  Created by Marcus Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#include <stdio.h>
#include "coordinate.h"

double Coordinate::NULL_VALUE = -100;
Coordinate Coordinate::null_coordinate(NULL_VALUE, NULL_VALUE);

// Default constructor

Coordinate::Coordinate(double x1, double y1) {
    x = x1;
    y = y1;
}

double Coordinate::get_x() {
    return x;
}

void Coordinate::set_x(double new_x) {
    x = new_x;
}

double Coordinate::get_y() {
    return y;
}

void Coordinate::set_y(double new_y) {
    y = new_y;
}

Coordinate Coordinate::add(Coordinate *another_coordinate) {
    Coordinate new_coordinate;
    double new_x = get_x() + another_coordinate->get_x();
    double new_y = get_y() + another_coordinate->get_y();
    new_coordinate.set_x(new_x);
    new_coordinate.set_y(new_y);
    return new_coordinate;
}

bool Coordinate::equal(Coordinate *another_coordinate) {
    if (get_x() == another_coordinate->get_x() &&
            get_y() == another_coordinate->get_y()) {
        return true;
    } else {
        return false;
    }
}

Coordinate *Coordinate::get_null_coordinate_ptr() {
    return &null_coordinate;
}
