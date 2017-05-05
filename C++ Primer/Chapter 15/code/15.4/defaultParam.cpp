#include <iostream>

class Shape {
   public:
    enum ShapeColor { Red, Green, Blue };
    virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle : public Shape {
   public:
    void draw(ShapeColor color = Green) const override {
        if (color == Red) std::cout << "Red" << std::endl;
        if (color == Green) std::cout << "Green" << std::endl;
        if (color == Blue) std::cout << "Blue" << std::endl;
    }
};

class Circle : public Shape {
   public:
    void draw(ShapeColor color) const override {
        if (color == Red) std::cout << "Red" << std::endl;
        if (color == Green) std::cout << "Green" << std::endl;
        if (color == Blue) std::cout << "Blue" << std::endl;
    }
};

int main() {
    Shape* ps;
    Rectangle* pr = new Rectangle();
    Circle* pc = new Circle();
    pr->draw();
    pc->draw(Shape::Blue);
    ps = pr;
    ps->draw();
    ps = pc;
    ps->draw();
    return 0;
}
