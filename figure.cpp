#include "figure.h"
#include <iostream>
#include<string>
#include <cmath>

using namespace std;

double Sides(Point A, Point B) { //Сторони
	double s = hypot((B.x - A.x), (B.y - A.y));
	return s;
}

Figure::Figure(Point A, Point B, Point C) {
    this->name = "Triange";
    perimetr = Sides(A, B) + Sides(B, C) + Sides(C, A);
    int poly = perimetr / 2;
    square = sqrt(poly * (poly - Sides(A, B)) * (poly - Sides(B, C)) * (poly - Sides(C, A)));
}

Figure::Figure(Point A, Point B, Point C, Point D) {
    this->name = "Rectangle";
    perimetr = Sides(A, B) + Sides(B, C) + Sides(C, D) + Sides(D, A);
    int poly = perimetr / 2;
    square = sqrt((poly - Sides(A, B)) * (poly - Sides(B, C)) * (poly - Sides(C, D)) * (poly - Sides(D, A)))
}

Figure::Figure(Point A, Point B, Point C, Point D, Point F) {
    this->name = "5-Tangel";
    perimetr = Sides(A, B) + Sides(B, C) + Sides(C, D) + Sides(D, F) + Sides(F, A);
    square = 5/4 * Sides(A, B) * ctg(pi/5);

}

template <typename ... Args> int ArgsCount(Args ... args) {
    return sizeof...(args);
}

template <typename  ...Point> Figure::Figure(Point... points) {
    int num = ArgsCount(Point... points);
    this->name = num + "-" + "Tangel";

}

Figure::~Figure()
{

}

double Figure::get_perimetr() 
{
    cout << perimetr << endl;
}

double Figure::get_square() 
{
    cout << square << endl;
}

string Figure::get_name() {
    cout << name << endl;
}