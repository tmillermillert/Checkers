//
//  coordinate.h
//  Checkers2
//
//  Created by Darlene Miller on 10/13/16.
//  Copyright © 2016 Marcus Tanner Miller. All rights reserved.
//

#ifndef coordinate_h
#define coordinate_h

class Coordinate {
private:
    static double NULL_VALUE;
    double x;
    double y;
    static Coordinate null_coordinate;
public:
    Coordinate(double x1 = NULL_VALUE, double y1 = NULL_VALUE); // Default constructor

    double get_x();
    void set_x(double);

    double get_y();
    void set_y(double);

    Coordinate add(Coordinate *);
    bool equal(Coordinate *);

    static Coordinate *get_null_coordinate_ptr();
};
#endif /* coordinate_h */
