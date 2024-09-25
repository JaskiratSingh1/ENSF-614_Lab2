//
//  point.h
//  ExerciseB
//
//  Created by Jaskirat Singh on 9/24/24.
//

#ifndef point_h
#define point_h

class Point {
private:
    double xCoordinate;
    double yCoordinate;
    int id;
    static int count;
    static int id_counter;
public:
    Point(double xValue, double yValue);
    Point(const Point& rhs);
    Point& operator=(const Point& rhs);
    ~Point();
    
    void setx(double x_value);
    void sety(double y_value);

    double getx() const;
    double gety() const;
    int getID() const;

    void display() const;
    static int counter();
    
    double distance(const Point& other) const;
    static double distance(const Point& p1, const Point& p2);
};


#endif /* point_h */
