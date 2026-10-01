#include <iostream>


class Bird {
public:
    virtual void eat() { std::cout << "Eating..." << std::endl; }
    virtual ~Bird() = default;
};

class FlyingBird : public Bird {
public:
    virtual void fly() = 0;
};

class Eagle : public FlyingBird {
public:
    void fly() override { std::cout << "Eagle is flying high!" << std::endl; }
};

class Penguin : public Bird {
public:
    void swim() { std::cout << "Penguin is swimming fast!" << std::endl; }
};

int main() {
    Eagle myEagle;
    myEagle.eat();
    myEagle.fly();

    Penguin myPenguin;
    myPenguin.eat();
    myPenguin.swim();
    // myPenguin.fly();
    
    return 0;
}
