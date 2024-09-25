//
//  square.cpp
//  ExerciseB
//
//  Created by Jaskirat Singh on 9/24/24.
//

#include <iostream>
#include "square.h"

using namespace std;

Square::Square(double x, double y, double side, const char* name)
    : Shape(x, y, name), side_a(side) {}

Square::~Square() {}

double Square::area() const {
    return side_a * side_a;
}

double Square::perimeter() const {
    return 4 * side_a;
}

double Square::get_side_a() const {
    return side_a;
}

void Square::set_side_a(double side) {
    side_a = side;
}

void Square::display() const {
    cout << "Square Name: " << getName() << endl;
    cout << "X-coordinate: " << getOrigin().getx() << endl;
    cout << "Y-coordinate: " << getOrigin().gety() << endl;
    cout << "Side a: " << side_a << endl;
    cout << "Area: " << area() << endl;
    cout << "Perimeter: " << perimeter() << endl;
}
