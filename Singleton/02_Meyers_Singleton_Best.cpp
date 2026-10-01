#include <iostream>
#include <string>

class Singleton {
private:
    std::string data;

    Singleton() {
        std::cout << "Singleton object created in memory:\n";
        std::cout << "Enter initial value for Singleton (no spaces): ";
        std::cin >> data; 
    }

    ~Singleton() {
        std::cout << "Singleton object destroyed:\n";
    }

public:
 
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& getInstance() {
        static Singleton instance; 
        return instance;
    }

    void setData(const std::string& newData) {
        data = newData;
    }

    std::string getData() const {
        return data;
    }
};

int main() {
    std::cout << "---start---\n\n";

    Singleton& instance1 = Singleton::getInstance();
    std::cout << "1st instance type: " << instance1.getData() << "\n\n";
    std::cout << "-> changing type of instance1 to 'new updated value'\n";
    instance1.setData("new updated value");
    Singleton& instance2 = Singleton::getInstance();
    std::cout << "Instance 2 type: " << instance2.getData() << "\n\n";
    if (&instance1 == &instance2) {
        std::cout << "prove that Instance 1 and Instance 2 is the same (" << &instance1 << ")\n";
    }

    std::cout << "\n--- finish ---\n";
    return 0;
}

