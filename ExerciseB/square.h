//
//  square.h
//  ExerciseB
//
//  Created by Jaskirat Singh on 9/24/24.
//

#ifndef square_h
#define square_h

class Square : public Shape {
private:
    double side_a;

public:
    Square(double x, double y, double side, const char* name);
    virtual ~Square();

    double area() const;
    double perimeter() const;

    double getSideA() const;
    void setSideA(double side);

    virtual void display() const;
};


#endif /* square_h */
