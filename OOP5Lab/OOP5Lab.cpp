﻿#include <iostream>

using namespace std;

class Point
{
protected:
    int x;
    int y;
    Point()
    {
        x = 0;
        y = 0;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Point(Point& p)
    {
        x = p.x;
        y = p.y;
    }

public:
    virtual string classname()
    {
        return "Point\n";
    }
    virtual bool isA(string name)
    {
        return (name == classname());
    }

    virtual  ~Point()
    {
        x = 0;
        y = 0;
    }
};

class Circle : Point
{
    int r;
public:
    Circle() : Point()
    {
        r = 0;
    }
    Circle(int x, int y, int r) : Point(x, y)
    {
        this->r = r;
    }
    Circle(Circle& c)
    {
        this->x = c.x;
        this->y = c.y;
        this->r = c.r;
    }

    virtual string classname()
    {
        return "Circle\n";
    }
    virtual bool isA(string name)
    {
        return (name == classname() || Point::isA(name));
    }

    ~Circle()
    {
        x = 0;
        y = 0;
        r = 0;
    }
};

class Rectangle : Point
{
    int width;
    int height;
public:
    Rectangle() : Point()
    {
        width = 0;
        height = 0;
    }
    Rectangle(int x, int y, int width, int height) : Point(x, y)
    {
        this->width = width;
        this->height = height;
    }
    Rectangle(Rectangle& r)
    {
        this->x = r.x;
        this->y = r.y;
        this->width = r.width;
        this->height = r.height;
    }

    virtual string classname()
    {
        return "Rectangle\n";
    }
    virtual bool isA(string name)
    {
        return (name == classname() || Point::isA(name));
    }

    ~Rectangle()
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
