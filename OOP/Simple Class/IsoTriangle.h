#pragma once

class IsoTriangle {

private:

    float x_ = 0.0;
    float y_ = 0.0;
    float base_ = 1.0;
    float height_ = 1.0;

public:

    IsoTriangle() = default;
    IsoTriangle(const float x, const float y, const float base, const float height);

    void input();
    void output() const;

    float getX() const {return x_;}
    float getY() const {return y_;}
    float getBase() const {return base_;}
    float getHeight() const {return height_;}

    void setX(float x) {x_ = x;}
    void setY(float y) {y_ = y;}
    void setBase(float base) {
        if (base >0) base_ = base;
        else throw std::invalid_argument("Основание должно быть положительным");
    }
    void setHeight(float height) {
        if (height > 0) height_ = height;
        else throw std::invalid_argument("Высота должна быть положительной");
    }

    bool isEquil() const;
    float inRadius() const;
    std::pair<float, float> inCenter() const;
    float largestAngle() const;
    float sideLength() const;

    IsoTriangle operator*(float k) const;
    IsoTriangle& operator*=(float k);
};