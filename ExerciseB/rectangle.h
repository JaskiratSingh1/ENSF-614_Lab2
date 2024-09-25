//
//  rectangle.h
//  ExerciseB
//
//  Created by Jaskirat Singh on 9/24/24.
//

#ifndef rectangle_h
#define rectangle_h

#include "square.h"

class Rectangle : public Square {
private:
    double side_b;

public:
    Rectangle(double x, double y, double side_a, double side_b, const char* name);
    Rectangle(const Rectangle& other);
    Rectangle& operator=(const Rectangle& other);
    virtual ~Rectangle();

    double area() const;
    double perimeter() const;

    double get_side_b() const;
    void set_side_b(double side);

    virtual void display() const;
};

#endif /* rectangle_h */
