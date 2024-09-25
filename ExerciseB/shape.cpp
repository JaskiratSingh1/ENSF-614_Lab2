//
//  shape.cpp
//  ExerciseB
//
//  Created by Jaskirat Singh on 9/24/24.
//

#include <iostream>
#include <cstring>
#include "shape.h"

using namespace std;

Shape::Shape(double x, double y, const char* name) : origin(x, y) {
    shapeName = new char[strlen(name) + 1];
    strcpy(shapeName, name);
}

Shape::Shape(const Point& p, const char* name) : origin(p) {
    shapeName = new char[strlen(name) + 1];
    strcpy(shapeName, name);
}

Shape::Shape(const Shape& other) : origin(other.origin) {
    shapeName = new char[strlen(other.shapeName) + 1];
    strcpy(shapeName, other.shapeName);
}

Shape& Shape::operator=(const Shape& other) {
    if(this != &other) {
        delete[] shapeName;
        shapeName = new char[strlen(other.shapeName) + 1];
        strcpy(shapeName, other.shapeName);
        origin = other.origin;
    }
    return *this;
}

Shape::~Shape() {
    delete[] shapeName;
}

const Point& Shape::getOrigin() const {
    return origin;
}

const char* Shape::getName() const {
    return shapeName;
}

void Shape::display() const {
    cout << "Shape Name: " << shapeName << endl;
    cout << "X Coordinate: " << origin.getX() << endl;
    cout << "Y Coordinate: " << origin.getY() << endl;
}

double Shape::distance(const Shape& other) const {
    return origin.distance(other.origin);
}

double Shape::distance(const Shape& s1, const Shape& s2) {
    return Point::distance(s1.origin, s2.origin);
}

void Shape::move(double dx, double dy) {
    origin.setX(origin.getX() + dx);
    origin.setY(origin.getY() + dy);
}
