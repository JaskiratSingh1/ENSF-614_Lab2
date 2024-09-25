//
//  shape.h
//  ExerciseB
//
//  Created by Jaskirat Singh on 9/24/24.
//

#ifndef shape_h
#define shape_h

#include "point.h"

class Shape {
private:
    Point origin;
    char* shapeName;

public:
    Shape(double x, double y, const char* name);
    Shape(const Point& p, const char* name);
    Shape(const Shape& other);
    Shape& operator=(const Shape& other);
    virtual ~Shape();

    const Point& getOrigin() const;
    const char* getName() const;

    virtual void display() const;

    double distance(const Shape& other) const;
    static double distance(const Shape& s1, const Shape& s2);

    void move(double dx, double dy);
};

#endif /* shape_h */
