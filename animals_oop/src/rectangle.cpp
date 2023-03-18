#include "rectangle.h"

#include <iostream>

Rectangle::Rectangle(double width, double height)
    : _width{width}, _height{height} {}

Rectangle::~Rectangle() { std::cout << "Rectangle destructor" << std::endl;}

void Rectangle::area() const { std::cout << "area: " << _width * _height << std::endl;}
