#pragma once
#include <iostream>
#include<string>

using namespace std;

class Point {
public:
	int x, y;
	Point() {
		x = 0; y = 0;
	}
	Point(int xx, int yy) {
		x = xx; y = yy;
	}
	void PrintP() {
		cout << "(" << x << ";" << y << ")" << endl;
	}
};


class Figure
{
	double perimetr;
	double square;
	string name;
public:
	virtual double get_perimetr();
	virtual double get_square();
	virtual string get_name();
	Figure(Point A, Point B, Point C);
    Figure(Point A, Point B, Point C, Point D);
    Figure(Point A, Point B, Point C, Point D, Point F);
    template <typename  ...Point>Figure(Point... points);
	~Figure();
};

