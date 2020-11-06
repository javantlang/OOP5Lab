#include <iostream>

using namespace std;

class Color
{
    string color;
public:
    Color()
    {
        this->color = "black";
    }
    Color(string color)
    {
        this->color = color;
    }
    Color(Color& col)
    {
        this->color = col.color;
    }
};

class Shape
{
protected:
    int x;
    int y;
    Shape()
    {
        this->x = 0;
        this->y = 0;
    }
    Shape(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Shape(Shape& p)
    {
        x = p.x;
        y = p.y;
    }

public:
    virtual string classname()
    {
        return "Shape";
    }
    virtual bool isA(string name)
    {
        return (name == "Shape");
    }

    virtual void getCoord()
    {
        cout << classname() << "(" << x << ", " << y << ")\n";
    }

    //НЕ переопределяемый
    void Move(int dx, int dy)
    {
        cout << classname() << "isMoving" << "\n";
        x += dx;
        y += dy;
    }

    //----------------------------------------------

    /*НЕ переопределяемы метод,
    * вызывает не виртуальный метод oneStep,
    * который переопределён у класса-потомка
    */
    void MakesomeSteps(int amount)
    {
        while (amount)
        {
            oneStep();
            --amount;
        }
    }

    //Переопределяемый метод
    void oneStep()
    {
        cout << "Steps from Shape\n";
        ++x;
        ++y;
    }

    //----------------------------------------------

    /*НЕ переопределяемы метод,
    * вызывает виртуальный метод Round,
    * который переопределён у класса-потомка
    */
    void RoundsomeTime(int amount)
    {
        while (amount)
        {
            Round();
            --amount;
        }
    }

    virtual void Round()
    {
        cout << "Shape is round~\n";
    }

    //----------------------------------------------

    //Переопределяемый метод
    void Draw()
    {
        cout << "Draw Shape\n";
    }

    virtual  ~Shape()
    {
        cout << "~Shape()\n";
        x = 0;
        y = 0;
    }
};

class Circle : public Shape
{
protected:
    int r;
public:
    Circle() : Shape()
    {
        r = 0;
        cout << "Circle()";
    }
    Circle(int x, int y, int r) : Shape(x, y)
    {
        this->r = r;
        cout << "Circle(" << x << ", " << y << ", " << r << ")\n";
    }
    Circle(Circle& c)
    {
        this->x = c.x;
        this->y = c.y;
        this->r = c.r;
    }

    virtual string classname()
    {
        return "Circle";
    }
    virtual bool isA(string name)
    {
        return (name == "Circle" || Shape::isA(name));
    }

    void Draw()
    {
        cout << "Draw Circle\n";
    }

    void oneStep()
    {
        cout << "Steps from Circle\n";
        x += r;
        y += r;
    }

    virtual void Round()
    {
        cout << classname() << " is round~\n";
    }

    void Roll()
    {
        cout << classname() << " is rolling\n";
    }

    virtual ~Circle()
    {
        cout << "~Circle()\n";
        x = 0;
        y = 0;
        r = 0;
    }
};

class FillCircle : public Circle
{
    Color* color;
public:
    FillCircle() : Circle()
    {
        this->color = new Color();
        cout << "FillCircle()";
    }
    FillCircle(int x, int y, int r, string color) : Circle(x, y, r)
    {
        this->color = new Color(color);
        cout << "FillCircle(" << x << ", " << y << ", " << r << ")\n";
    }
    FillCircle(FillCircle& c)
    {
        this->x = c.x;
        this->y = c.y;
        this->r = c.r;
        this->color = new Color(*c.color);
    }

    virtual string classname()
    {
        return "FillCircle";
    }
    virtual bool isA(string name)
    {
        return (name == "FillCircle" || Circle::isA(name));
    }

    void Draw()
    {
        cout << "Draw FillCircle\n";
    }

    virtual ~FillCircle()
    {
        cout << "~FillCircle()\n";
        x = 0;
        y = 0;
        r = 0;
    }
};

class Rectangle : public Shape
{
protected:
    int width;
    int height;
public:
    Rectangle() : Shape()
    {
        width = 0;
        height = 0;
        cout << "Rectangle()";
    }
    Rectangle(int x, int y, int width, int height) : Shape(x, y)
    {
        this->width = width;
        this->height = height;
        cout << "Rectangle(" << x << ", " << y << ", " << width << ", " << height << ")\n";
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
        return "Rectangle";
    }
    virtual bool isA(string name)
    {
        return (name == "Rectangle" || Shape::isA(name));
    }

    void Draw()
    {
        cout << "Draw Rectangle\n";
    }

    void oneStep()
    {
        cout << "Steps from Rectanlge\n";
        x += width;
        y += height;
    }

    virtual void Round()
    {
        cout << "Rectangle is round~\n";
    }

    void Prick()
    {
        cout << "Rectangle is pricking\n";
    }

    virtual ~Rectangle()
    {
        cout << "~Rectangle()\n";
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
};
