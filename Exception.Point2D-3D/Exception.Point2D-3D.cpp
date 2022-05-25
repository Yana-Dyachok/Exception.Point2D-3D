/*На базі класу Точка на площині створіть клас Точка3Д(точка в просторі).Реалізуйте методи введення, виведення.Реалізуйте методи за допомогою  даних класів клас Відрізок,
що дозволяє працювати з точками розмірностей 2 та 3  введення та виведення, визначення довжини відрізка. Вказівка: визначіть додатковий  член "розмірність" в класах Точка,Точка3Д
Додаткова задача - визначення чи перетинаються два відрізки.Реалізуйте всі можливі винятки.*/
#include <iostream>
#include <cmath>
using namespace std;
class Point {
protected:
	double x, y;//координати точок 2D
	double dimension;//розмірність
public:
	Point() {
		x = 0; y = 0;  dimension = 0;
	}


    void Input() {//метод введення
		cout << "Enter coordinates x,  y:" << endl;
		cin >> x>> y;
	}


	void Output() {//метод виведення
		cout << "In Point2D x= " << x <<'\t' << " y= " << y << endl;
	}


	~Point() {}
};


class Point3D : public Point {
protected:
	double X,Y,Z;//координати точок 3D
public:
	Point3D() {
		X= 0; Y = 0; Z = 0;
	}


	void Input3D()  {//метод введення
		cout << "Enter coordinates x,  y, z:" << endl;
		cin >> X >> Y>>Z;
	}


	void Output3D()  {//метод виведення
		cout << "In Point3D x= " << X << '\t' << " y= " << Y << '\t' << " z= " << Z << endl;
	}

	~Point3D() {}
};


class Segment :  public Point3D {
protected:
	double  x1, y1;//координати точки перетину двох відрізків
public:
	Segment() {
		x1 = 0; y1 = 0;
	}


	double getDimension() {//знаходимо довжину відрізка
		dimension = sqrt(pow((X - x), 2) + pow((Y-y), 2)+ pow((Z - 0), 2));//оскільки точка в Point знаходиться в 2D, то координата z=0
		return dimension;
	}


	void findPoint(Segment &A, Segment &B) {//формула знаходження точки перетину відрізків (?)
		x1 = -((A.x * B.y - B.x * A.y) * (A.X - B.X) - (A.X * B.Y - B.X * A.Y) * (B.x - A.x)) / ((A.y - B.y) * (B.X - A.X) - (A.Y - B.y) * (B.x - A.x));
		y1= ((A.Y- B.Y) * (-x1) - (A.X * B.Y - B.X * A.Y)) / (B.X- A.X);
		int i=0;
		if(((B.X - A.X)==0) or (((A.y - B.y) * (B.X - A.X) - (A.Y - B.y) * (B.x - A.x)==0))){throw i;}
	}
	double cos1(Segment& A, Segment& B) {//кут між векторами 
		int i = 0;
		if (((sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2))) * (sqrt(pow((x1 - A.x), 2) + pow((y1 - A.y), 2))))==0) { throw i; }
		return ((B.x-A.x) * (x1-A.x) + (B.y-A.y) * (y1 - A.y)) / ((sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2))) * (sqrt(pow((x1 - A.x), 2) + pow((y1 - A.y), 2))));
	}


	double cos2(Segment& A, Segment& B) {//кут між векторами 
		int i = 0;
		if (((sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2))) * (sqrt(pow((A.X - A.x), 2) + pow((A.Y - A.y), 2))))==0) { throw i; }
		return ((B.x - A.x) * (A.X - A.x) + (B.y - A.y) * (A.Y - A.y)) / ((sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2))) * (sqrt(pow((A.X - A.x), 2) + pow((A.Y - A.y), 2))));
	}


	double cos3(Segment& A, Segment& B) {//кут між векторами 
		int i = 0;
		if ((sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2))) * (sqrt(pow((A.X - A.x), 2) + pow((A.Y - A.y), 2)))==0) { throw i; }
		return ((B.x - A.x) * (A.X - A.x) + (B.y - A.y) * (A.Y - A.y)) / ((sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2))) * (sqrt(pow((A.X - A.x), 2) + pow((A.Y - A.y), 2))));
	}
	//оскільки відрізки знаходяться в різних площинах, то пересіктись вони зможуть якщо точка перетину  A(X,Y,Z) або B(X,Y,Z) з площини 3D буде лежати на відрізку в Point2D, 
	//а це можливо якщо координати Z будуть рівними 0, тобто точки з площини 3D будуть в площині 2D, якщо z не дорівнює 0, то пересіктись можуть в точні перетину, яку знайшли в findPoint()
	bool cheakPoint(Segment& A, Segment& B) {
		try//якщо буде ділення на 0- знаходимо помилку
		{
			cos1(A, B);
			cos2(A, B);
			cos3(A, B);
		}
		catch (int i) {
			cout << "Don't divide by zero  " << i << endl; 
		}
		if (cos1(A, B) == 1) return true;//якщо кути між відповідними векторів дорівнюють 0, то точка перетину чи початкова чи остання точка з 3D лежить на відрізку з 2D
		else if (Z == 0) {
			if ((A.x == A.X and A.y ==A.Y)or (B.x == B.X and B.y == B.Y))return true;//умова за якої одна початкова чи остання точка з 3D лежить  на початковій чи останній точці з 2D 
			if ( cos2(A, B) == 1 or cos3(A, B) == 1)return true;
		}
		else return false;
	}


	~Segment() {}
};

int main(){

	Segment A, B;
	A.Input();
	A.Input3D();
	A.Output();
	A.Output3D();
	cout << "Dimension of two points is: " << A.getDimension() << endl;
	B.Input();//для виконання додаткового завдання потрібно використати ще один об'єкт щоб сформувались відрізки
	B.Input3D();
	try//якщо буде ділення на 0- знаходимо помилку
	{
		A.findPoint(A, B);
	}
	catch (int i) {
		cout << "Don't divide by zero  " << i << endl;
	}
	cout << "Segment in 3D cross with segment 2D- (true=1, false=0) is = " << A.cheakPoint(A, B) << endl;//перевіряємо чи пересікаються відрізки
}