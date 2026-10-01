#include <iostream>

class BadSingleton {
private:
    static BadSingleton* s_instance;
    BadSingleton() { std::cout << "Bad Singleton Created (Memory Leak!)\n"; }

public:
    BadSingleton(const BadSingleton&) = delete;
    BadSingleton& operator=(const BadSingleton&) = delete;

    static BadSingleton* getInstance() {
        if (s_instance == nullptr) {
            s_instance = new BadSingleton(); // new կա, delete չկա
        }
        return s_instance;
    }
};

BadSingleton* BadSingleton::s_instance = nullptr;

int main() {
    BadSingleton* instance = BadSingleton::getInstance();
    return 0;
}
