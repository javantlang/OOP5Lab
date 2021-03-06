﻿#include <iostream>
#include <time.h>
#include "Shapes.h"
#include "BaseandDesc.h"

using namespace std;

const int N = 10;

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

    /*Вызов не виртуального, но переопределённого метода
    * oneStep() в базовом методе MakesomeSteps()
    */
    circleObj->MakesomeSteps(5);
    rectObj->MakesomeSteps(3);
    circleObj->getCoord();
    rectObj->getCoord();

    /*Вызов виртуального oneStep() 
    * в базовом методе MakesomeSteps()
    */
    circleObj->RoundsomeTime(1);
    rectObj->RoundsomeTime(1);

    delete circleObj;
    delete rectObj;
}

void TestWithStore()
{
    cout << "ТЕСТ С ОБЪЕКТАМИ В ХРАНИЛИЩЕ\n";
    Shape* shapeObj[N];

    for (int i = 0; i < N; ++i)
    {
        if (rand() % 3 == 0)
            shapeObj[i] = new Circle(rand() % 10, rand() % 10, rand() % 10);
        else if (rand() % 3 == 1)
            shapeObj[i] = new FillCircle(rand() % 10, rand() % 10, rand() % 10, "Blue");
        else
            shapeObj[i] = new Rectangle(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    }

    cout << "-----------------------------------\n";

    //Безопасное приведение типов вручную
    cout << "БЕЗОПАСНОЕ ПРИВЕДЕНИЕ ТИПОВ ВРУЧНУЮ\n";
    for (int i = 0; i < N; ++i)
    {
        if (shapeObj[i]->isA("Circle"))
            ((Circle*)shapeObj[i])->Roll();
        if (shapeObj[i]->isA("Rectangle"))
            ((Rectangle*)shapeObj[i])->Prick();
    }

    cout << "-----------------------------------\n";

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

void DinamicCastFunc()
{
    cout << "ПРИВЕДЕНИЕ ТИПОВ С ПОМОЩЬЮ ДИНАМИК КАСТ\n";
    Shape* shapeObj[N];

    for (int i = 0; i < N; ++i)
    {
        if (rand() % 2 == 0)
            shapeObj[i] = new Circle(rand() % 10, rand() % 10, rand() % 10);
        else
            shapeObj[i] = new Rectangle(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    }

    cout << "-----------------------------------\n";

    //Безопасное приведение типов через dinamic_cast
    cout << "БЕЗОПАСНОЕ ПРИВЕДЕНИЕ ТИПОВ\n";
    for (int i = 0; i < N / 2; ++i)
    {
        Circle* cir = dynamic_cast<Circle*>(shapeObj[i]);
        if (cir != NULL)
        {
            cout << "Преобразование в круг успешно завершено\n";
            cir->Roll();
        }
        else
            cout << "Манёвр с кругом не удался\n";
    }

    cout << "-----------------------------------\n";

    for (int i = N / 2; i < N; ++i)
    {
        Rectangle* cir = dynamic_cast<Rectangle*>(shapeObj[i]);
        if (cir != NULL)
        {
            cout << "Преобразование в прямоугольник успешно завершено\n";
            cir->Prick();
        }
        else
            cout << "Манёвр с прямоугольником не удался\n";
    }
}

void ChkWithname()
{
    cout << "ПРИВЕДЕНИЕ ТИПОВ С CLASSNAME()\n";

    Shape* shapeObj[N];

    for (int i = 0; i < N; ++i)
    {
        if (rand() % 3 == 0)
            shapeObj[i] = new Circle(rand() % 10, rand() % 10, rand() % 10);
        else if (rand() % 3 == 1)
            shapeObj[i] = new FillCircle(rand() % 10, rand() % 10, rand() % 10, "Blue");
        else
            shapeObj[i] = new Rectangle(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    }

    cout << "-----------------------------------\n";

    for (int i = 0; i < N; ++i)
    {
        if (shapeObj[i]->classname() == "Circle")
            ((Circle*)shapeObj[i])->Roll();
        else if (shapeObj[i]->classname() == "Rectangle")
            ((Rectangle*)shapeObj[i])->Prick();
        else
            cout << "FillCircle не зашёл и не покрутился\n";
    }
}

void BaseTest()
{
    Base defBase1;
    Base defBase2("One");
    Base defBase3(defBase2);

    func1(defBase1);
    func1(defBase2);
    func1(defBase3);

    func2(&defBase1);
    func2(&defBase2);
    func2(&defBase3);

    func3(defBase1);
    func3(defBase2);
    func3(defBase3);

    Base defDesc1;
    Base defDesc2("One");
    Base defDesc3(defDesc2);

    func1(defDesc1);
    func1(defDesc2);
    func1(defDesc3);

    func2(&defDesc1);
    func2(&defDesc2);
    func2(&defDesc3);

    func3(defDesc1);
    func3(defDesc2);
    func3(defDesc3);
}

int main()
{
    srand(time(0));

    setlocale(0, "");

    TestWithDef();

    TestWithStore();

    DinamicCastFunc();

    ChkWithname();

    BaseTest();

    return 0;
}
