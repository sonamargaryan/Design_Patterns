#include <iostream>
#include <string>
#include <memory>

class IPrototype {
public:
    virtual ~IPrototype() = default;
    virtual std::unique_ptr<IPrototype> clone() const = 0;
};


class Enemy : public IPrototype {
private:
    std::string name;
    int health;
    int* weaponDamage;

public:
    Enemy(std::string n, int h, int dmg) : name(n), health(h) {
        weaponDamage = new int(dmg);
        std::cout << "[Init] The original object was created from scratch: " << name << "\n";
    }

    Enemy(const Enemy& other) {
        this->name = other.name;
        this->health = other.health;
        
        this->weaponDamage = new int(*(other.weaponDamage));
        std::cout << "[Copy] A deep copy was performed (using the copy constructor): " << name << "\n";
    }

    ~Enemy() {
        delete weaponDamage;
    }

    std::unique_ptr<IPrototype> clone() const override {
        return std::make_unique<Enemy>(*this);
    }

    std::unique_ptr<Enemy> cloneViaSerialization() const {
        std::cout << "[Serialization] Copying via serialization\n";
        std::cout << "  -> step 1: The object is converted into JSON/XML text (Costly!)\n";
        std::cout << "  -> step 2: It is converted from text into a new object (Deserialization)\n";
        
        
        return std::make_unique<Enemy>(*this);
    }

    
    void adjustHealth(int newHealth) {
        health = newHealth;
    }

    void print() const {
        std::cout << "  Monster: " << name << " |life: " << health 
                  << " | Weapon's destination: " << weaponDamage 
                  << " (Damage: " << *weaponDamage << ")\n";
    }
};


int main() {
    std::cout << "--- 1. PREMADE OBJECT ---\n";
    Enemy prototypeOrc("Orc Warrior", 100, 25);
    prototypeOrc.print();

    std::cout << "\n--- 2. COPY + ADJUSTMENT ---\n";
    auto clonedOrc1 = prototypeOrc.clone();
    
    Enemy* adjustedOrc = dynamic_cast<Enemy*>(clonedOrc1.get());
    if (adjustedOrc) {
        adjustedOrc->adjustHealth(80); 
        adjustedOrc->print();
    }

    std::cout << "\n--- 3. SERIALIZATION APPROACH (Ձեր նշած այլընտրանքը) ---\n";
    auto clonedOrc2 = prototypeOrc.cloneViaSerialization();
    clonedOrc2->print();

    std::cout << "\nNote that the weapon pointers are different; in other words, it is a deep copy!\n";

    return 0;
}
