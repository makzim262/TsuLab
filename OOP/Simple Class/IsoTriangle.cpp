#include <iostream>
#include <cmath>

#include "IsoTriangle.h"

// 1) конструктор
IsoTriangle::IsoTriangle(const float x, const float y, const float base, const float height) : 
    x_(x), y_(y), base_(base), height_(height) {}

// 2) ввод
void IsoTriangle::input() {
    std::cout << "Координаты точки А: ";
    std::cin >> x_ >> y_;
    std::cout << "Основание треугольника: ";
    std::cin >> base_;
    if (base_ <= 0) throw std::invalid_argument("Основание должно быть положительным");
    std::cout << "Высота треугольника: ";
    std::cin >> height_;
    if (height_ <= 0) throw std::invalid_argument("Высота должна быть положительной");
    std::cout << std::endl;
}
// 2) вывод
void IsoTriangle::output() const {
    std::cout << "Треугольник: A(" << x_ << ", " << y_ << ")" << "\n"
              << "Основание: " << base_ << "\n" << "Высота: " << height_ << "\n\n";
}

// 4) проверка, является ли треугольник равносторонним
bool IsoTriangle::isEquil() const {
    float side = sideLength();
    return (side == base_);
}

// 5) нахождение радиуса вписанной окружности
float IsoTriangle::inRadius() const {
    float S = base_ / 2 * height_;
    float p = (sideLength() * 2 + base_) / 2;
    return S/p;
}

// 6) нахождение центра вписанной окружности
std::pair<float, float> IsoTriangle::inCenter() const {
    float centerX = x_ + base_ / 2;
    float centerY = y_ - (height_ - inRadius());
    return {centerX, centerY};
}

// 7) нахождение большего угла
float IsoTriangle::largestAngle() const {
    float side = sideLength();
    float baseAngle = acos((2 * side * side - base_ * base_) / (2 * side* side));
    baseAngle = baseAngle * 180 / M_PI;
    float vertexAngle = 180 - 2 * baseAngle;
    return std::max(baseAngle, vertexAngle);
}

// 10) нахождение длины боковых сторон
float IsoTriangle::sideLength() const {
    return sqrt(pow(base_ / 2, 2) + height_ * height_);
}

// 11) нахождение высоты к боковой стороне
float IsoTriangle::altToSide() const {
    return (base_ * height_ / sideLength());
}

// 12) пересекает ли линия заданая общим уравнением треугольник
bool IsoTriangle::intersectLine(float a, float b, float c) const {
    float x1 = x_ + base_ / 2;
    float y1 = y_;

    float x2 = x_ + base_;
    float y2 = y_ - height_;

    float x3 = x_;
    float y3 = y_ - height_;

    float val1 = a*x1 + b*y1 + c;
    float val2 = a*x2 + b*y2 + c;
    float val3 = a*x3 + b*y3 + c;

    return (val1 * val2 <= 0 or val1 * val3 <= 0 or val2 * val3 <= 0);
}

// 8) оператор масштабирования
IsoTriangle IsoTriangle::operator*(float k) const {
    if (k <= 0) throw std::invalid_argument("Коэффициент масштабирования должен быть положительным");
    return IsoTriangle(x_, y_, base_ * k, height_ * k);
}

IsoTriangle& IsoTriangle::operator*=(float k){
    base_ *= k;
    height_ *= k;
    return *this;
}

// 9) проверка на подобие
bool IsoTriangle::operator==(const IsoTriangle& other) const {
    float ratio1 = base_ / height_;
    float ratio2 = other.base_ / other.height_;
    return !(ratio1-ratio2);
}   