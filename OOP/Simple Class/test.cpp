#include <iostream>

#include "IsoTriangle.h"

int main() {

    IsoTriangle t1;
    t1.input();
    t1.output();

    std::cout << "sideLength: "<< t1.sideLength() << "\n";
    std::cout << "inRadius: " << t1.inRadius() << "\n";
    std::cout << "inCenter: (" << t1.inCenter().first << ", " << t1.inCenter().second << ")" << "\n";
    std::cout << "largestAngle: " << t1.largestAngle() << "\n";
    std::cout << "altToSide: " << t1.altToSide() << "\n\n";

    t1 *= 3;
    t1.setX(10);
    t1.setY(10);

    std::cout << "x: " << t1.getX() << ", y: " << t1.getY() << "\n";
    std::cout << "base: " << t1.getBase() << "\n";
    std::cout << "height: " << t1.getHeight() << "\n";

    IsoTriangle t2;
    t2.input();

    if (t1 == t2) std::cout << "true\n";

    float a, b, c;
    std::cout << "a, b, c прямой в общем виде: ";
    std::cin >> a >> b >> c;

    if (t1.intersectLine(a, b, c)) std::cout << "прямая пересекает треугольник";
    else std::cout << "прямая не пересекает треугольник";

    return 0;
}