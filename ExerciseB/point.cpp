//
//  point.cpp
//  ExerciseB
//
//  Created by Jaskirat Singh on 9/24/24.
//

#include <iostream>
#include <cmath>
#include "point.h"

using namespace std;

int Point::count = 0;
int Point::id_counter = 1001;

Point::Point(double xValue, double yValue) : xCoordinate(xValue), yCoordinate(yValue), id(id_counter++) {
    count++;
}

Point::Point(const Point& rhs) : xCoordinate(rhs.xCoordinate), yCoordinate(rhs.yCoordinate), id(id_counter++) {
    count++;
}

Point& Point::operator=(const Point& rhs) {
    if (this != &rhs) {
        xCoordinate = rhs.xCoordinate;
        yCoordinate = rhs.yCoordinate;
        // id remains unique per object
    }
    return *this;
}

Point::~Point() {
    count--;
}

void Point::setX(double x_value) {
    xCoordinate = x_value;
}

void Point::setY(double y_value) {
    yCoordinate = y_value;
}

double Point::getX() const {
    return xCoordinate;
}

double Point::getY() const {
    return yCoordinate;
}

int Point::getID() const {
    return id;
}

void Point::display() const {
    cout << "X-coordinate: " << xCoordinate << endl;
    cout << "Y-coordinate: " << yCoordinate << endl;
}

int Point::counter() {
    return count;
}

double Point::distance(const Point& other) const {
    double dx = xCoordinate - other.xCoordinate;
    double dy = yCoordinate - other.yCoordinate;
    return sqrt(dx * dx + dy * dy);
}

double Point::distance(const Point& p1, const Point& p2) {
    double dx = p1.xCoordinate - p2.xCoordinate;
    double dy = p1.yCoordinate - p2.yCoordinate;
    return sqrt(dx * dx + dy * dy);
}
