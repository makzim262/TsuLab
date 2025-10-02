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
    std::cout << "Высота треугольника: ";
    std::cin >> height_;
    std::cout << std::endl;

    if (base_ <= 0 || height_ <=0) {
        throw std::invalid_argument("Основание и высота треугольника должны быть положительными");
    }
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



// проверка методов
int main() {

    IsoTriangle a;
    a.input();
    a.output();

    std::cout << "sideLength: "<< a.sideLength() << "\n";
    std::cout << "inRadius: " << a.inRadius() << "\n";
    std::cout << "inCenter: (" << a.inCenter().first << ", " << a.inCenter().second << ")" << "\n";
    std::cout << "largestAngle: " << a.largestAngle() << "\n\n";

    a *= 3;
    a.setX(10);
    a.setY(10);

    std::cout << "x: " << a.getX() << ", y: " << a.getY() << "\n";
    std::cout << "base: " << a.getBase() << "\n";
    std::cout << "height: " << a.getHeight() << "\n";

    return 0;
}
