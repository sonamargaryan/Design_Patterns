#include <iostream>
#include <vector>

class Shape {
public:
    virtual double calculateArea() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double calculateArea() const override { return width * height; }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double calculateArea() const override { return 3.14159 * radius * radius; }
};

class AreaCalculator {
public:
    double totalArea(const std::vector<Shape*>& shapes) {
        double sum = 0;
        for (const auto& shape : shapes) {
            sum += shape->calculateArea(); // Պոլիմորֆիզմ
        }
        return sum;
    }
};

int main() {
    Rectangle rect(5.0, 4.0);
    Circle circle(3.0);
    
    std::vector<Shape*> shapes = {&rect, &circle};
    AreaCalculator calc;
    
    std::cout << "Total Area: " << calc.totalArea(shapes) << std::endl;
    return 0;
}
