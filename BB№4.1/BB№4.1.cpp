#include <iostream>
#include <cmath>

using namespace std;

class Trik {

	struct Point {
		double x, y, z;
	};

	Point A, B, C;

	double dist(Point& p1, Point& p2) {
		return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
	}

public:

	Trik() : A{ 0,0,0 }, B{ 0,1,0 }, C{ 1,0,1 } {}
	Trik(Point a, Point b, Point c) : A(a), B(b), C(c) {}
	~Trik() {
		cout << "Деструктор визван";
	}

	void set() {
		cout << "Введіть координати вершини A (x, y, z): ";
		cin >> A.x >> A.y >> A.z;
		cout << "Введіть координати вершини B (x, y, z): ";
		cin >> B.x >> B.y >> B.z;
		cout << "Введіть координати вершини C (x, y, z): ";
		cin >> C.x >> C.y >> C.z;
	}
	void show() {
		cout << "Вершини трикутника:\n";
		cout << "A(" << A.x << ", " << A.y << ", " << A.z << ")" << endl;
		cout << "B(" << B.x << ", " << B.y << ", " << B.z << ")" << endl;
		cout << "C(" << C.x << ", " << C.y << ", " << C.z << ")" << endl;
	}


	double P()  {
		return dist(A, B) + dist(A, C) + dist(C, B);
	}
	double S()  {
		double s = P() / 2;
		double AB, AC, CB;
		AB = dist(A, B);
		AC = dist(A, C);
		CB = dist(C, B);
		return sqrt(s * (s - AB) * (s - AB) * (s - CB));
	}


	Trik operator+(Trik& other) {
		double kra = sqrt((this->S() + other.S()) / this->S());
		Point newB = { A.x + (B.x - A.x) * kra, A.y + (B.y - A.y) * kra, A.z + (B.z - A.z) * kra };
		Point newC = { A.x + (C.x - A.x) * kra, A.y + (C.y - A.y) * kra, A.z + (C.z - A.z) * kra };
		return Trik(A, newB, newC);
	}
	Trik operator-(Trik& other) {
		double kra = sqrt(abs(this->S() - other.S()) / this->S());
		Point newA = { C.x, C.y, C.z };
		Point newB = { C.x + (A.x - C.x) * kra, C.y + (A.y - C.y) * kra, C.z + (A.z - C.z) * kra };
		Point newC = { C.x + (B.x - C.x) * kra, C.y + (B.y - C.y) * kra, C.z + (B.z - C.z) * kra };
		return Trik(newA, newB, newC);
	}
	Trik& operator++() {
		A.x += 1; B.x += 1; C.x += 1;
		return *this;
	}
	Trik operator++(int) {
		Trik temp = *this;
		A.y += 1; B.y += 1; C.y += 1;
		return temp;
	}
	Trik& operator--() {
		A.x -= 1; B.x -= 1; C.x -= 1;
		return *this;
	}
	Trik operator--(int) {
		Trik temp = *this;
		A.y -= 1; B.y -= 1; C.y -= 1;
		return temp;
	}
	bool operator==(Trik& other) {
		double AB1 = dist(A, B), BC1 = dist(B, C), CA1 = dist(C, A);
		double AB2 = dist(other.A, other.B), BC2 = dist(other.B, other.C), CA2 = dist(other.C, other.A);
		return (AB1 == AB2 && BC1 == BC2 && CA1 == CA2);
	}

};



int main()
{
	setlocale(LC_ALL, "ukr");

	Trik trik1;
	Trik trik2;

	trik1.set();
	trik2.set();

	cout << "ТРикутник 1: " << endl;
	trik1.show();
	cout << "Трикутник 2: " << endl;
	trik2.show();
	cout << "Периметр першого трикутника: " << trik1.P() << " та площа " << trik1.S() << endl;
	cout << "Периметр другого трикутника: " << trik2.P() << " та площа " << trik2.S() << endl;

	Trik trik3 = trik1 + trik2;
	cout << "Додавання" << endl; trik3.show();
	Trik trik4 = trik1 - trik2;
	cout << "Віднімання" << endl; trik4.show();

	++trik1;
	cout << "Префіксне додавання: " << endl;
	trik1.show();
	trik1++;
	cout << "Постфіксне додавання: " << endl;
	trik1.show();

	--trik2;
	cout << "Префіксне віднімання: " << endl;
	trik2.show();
	trik2--;
	cout << "Постфіксне віднімання: " << endl;
	trik2.show();

	if (trik1 == trik2) {
		cout << "Трикутники рівні" << endl;
	}
	else {
		cout << "Трикутники не рівні" << endl;
	}

}

