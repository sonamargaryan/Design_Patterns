#include <iostream>
#include <memory>

class IEngine {
public:
    virtual void start() = 0;
    virtual ~IEngine() = default;
};

class V8Engine : public IEngine {
public:
    void start() override {
        std::cout << "V8 Engine is roaring: Vroom Vroom!" << std::endl;
    }
};

class ElectricEngine : public IEngine {
public:
    void start() override {
        std::cout << "Electric Engine started: Silent hum..." << std::endl;
    }
};

class Car {
private:
    std::shared_ptr<IEngine> engine; 
public:
    Car(std::shared_ptr<IEngine> eng) : engine(eng) {}
    
    void drive() {
        std::cout << "Car is turning the key..." << std::endl;
        engine->start();
    }
};

int main() {
    std::shared_ptr<IEngine> gasEngine = std::make_shared<V8Engine>();
    Car mustang(gasEngine);
    mustang.drive();

    std::cout << "------------------" << std::endl;

    std::shared_ptr<IEngine> evEngine = std::make_shared<ElectricEngine>();
    Car tesla(evEngine);
    tesla.drive();

    return 0;
}
