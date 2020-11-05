#include <iostream>
#include <time.h>

using namespace std;

const int N = 10;

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
        cout << classname() <<"(" << x << ", " << y << ")\n";
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
        cout << '\n';
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
        return (name == classname() || Shape::isA(name));
    }

    void Draw()
    {
        cout << "Draw Circle\n";
    }

    void oneStep()
    {
        x += r;
        y += r;
    }

    virtual void Round()
    {
        cout << "Circle is round~\n";
    }

    void Roll()
    {
        cout << "Circle is rolling\n";
    }

    virtual ~Circle()
    {
        cout << "~Circle()\n";
        x = 0;
        y = 0;
        r = 0;
    }
};

class Rectangle : public Shape
{
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
        return (name == classname() || Shape::isA(name));
    }

    void Draw()
    {
        cout << "Draw Rectangle\n";
    }

    void oneStep()
    {
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

void TestWithDef()
{
    cout << "ТЕСТ С ОБЪЕКТАМИ\n";
    Circle* circleObj = new Circle(5, 5, 5);
    Rectangle* rectObj = new Rectangle(3, 3, 3, 3);

    //Вызов переопределяемых методов
    circleObj->Draw();
    rectObj->Draw();
    //Вызов не переопределяемых методов
    circleObj->Move(2, 2);
    rectObj->Move(1, 1);
    //Вызов виртуального метода в классах-потомках
    circleObj->Round();
    rectObj->Round();
    //Вызов виртуального метода в базовом классе
    circleObj->getCoord();
    rectObj->getCoord();
    delete circleObj;
    delete rectObj;
}

void TestWithStore()
{
    cout << "ТЕСТ С ОБЪЕКТАМИ В ХРАНИЛИЩЕ\n";
    Shape* shapeObj[N];

    for (int i = 0; i < N; ++i)
    {
        if (rand() % 2 == 0)
            shapeObj[i] = new Circle(rand() % 10, rand() % 10, rand() % 10);
        else
            shapeObj[i] = new Rectangle(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    }

    //Безопасное приведение типов вручную
    cout << "БЕЗОПАСНОЕ ПРИВЕДЕНИЕ ТИПОВ\n";
    for (int i = 0; i < N; ++i)
    {
        if (shapeObj[i]->isA("Circle"))
            ((Circle*)shapeObj[i])->Roll();
        if (shapeObj[i]->isA("Rectangle"))
            ((Rectangle*)shapeObj[i])->Prick();
    }

    //ВЫЗОВ РАЗЛИЧНЫХ МЕТОДОВ У SHAPE
    cout << "ВЫЗОВ РАЗЛИЧНЫХ МЕТОДОВ У SHAPE\n";
    //Вызов переопределяемых методов
	shapeObj[0]->Draw();
    //Вызов не переопределяемых методов
	shapeObj[0]->Move(2, 2);
    //Вызов виртуального метода в классах-потомках
	shapeObj[0]->Round();
    //Вызов виртуального метода в базовом классе
	shapeObj[0]->getCoord();
    for (int i = 0; i < N; ++i)
    {
        delete shapeObj[i];
    }
}

int main()
{
    srand(time(0));
    setlocale(0, "");

    TestWithDef();

    TestWithStore();

    return 0;
}
