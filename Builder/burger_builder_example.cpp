#include <iostream>
#include <string>
#include <vector>

class Burger {
private:
    std::string bun;
    std::string patty;
    std::string cheese;
    std::string sauce;
    std::vector<std::string> veggies;

public:
    void setBun(const std::string& b) { bun = b; }
    void setPatty(const std::string& p) { patty = p; }
    void setCheese(const std::string& c) { cheese = c; }
    void setSauce(const std::string& s) { sauce = s; }
    void addVeggie(const std::string& v) { veggies.push_back(v); }

    void showBurger() const {
        std::cout << "--- Your Burger is ready ---\n";
        std::cout << "Bun: " << bun << "\n";
        std::cout << "Patty: " << patty << "\n";
        if (!cheese.empty()) std::cout << "Cheese: " << cheese << "\n";
        if (!sauce.empty()) std::cout << "Sauce: " << sauce << "\n";
        
        std::cout << "Veggies: ";
        if (veggies.empty()) {
            std::cout << "None\n";
        } else {
            for (const auto& v : veggies) {
                std::cout << v << " ";
            }
            std::cout << "\n";
        }
        std::cout << "------------------------------\n\n";
    }
};

class BurgerBuilder {
public:
    virtual ~BurgerBuilder() = default;
    virtual void buildBun() = 0;
    virtual void buildPatty() = 0;
    virtual void buildCheese() = 0;
    virtual void buildVeggies() = 0;
    virtual void buildSauce() = 0;
    virtual Burger* getBurger() = 0;
};

class CheeseBurgerBuilder : public BurgerBuilder {
private:
    Burger* burger;
public:
    CheeseBurgerBuilder() { burger = new Burger(); }
    ~CheeseBurgerBuilder() { delete burger; }

    void buildBun() override { burger->setBun("Classic Sesame Bun"); }
    void buildPatty() override { burger->setPatty("Beef Patty"); }
    void buildCheese() override { burger->setCheese("Cheddar Cheese"); }
    void buildVeggies() override { 
        burger->addVeggie("Pickles"); 
        burger->addVeggie("Onion"); 
    }
    void buildSauce() override { burger->setSauce("Ketchup and Mustard"); }
    
    Burger* getBurger() override { return burger; }
};

class VeganBurgerBuilder : public BurgerBuilder {
private:
    Burger* burger;
public:
    VeganBurgerBuilder() { burger = new Burger(); }
    ~VeganBurgerBuilder() { delete burger; }

    void buildBun() override { burger->setBun("Whole Wheat Gluten-Free Bun"); }
    void buildPatty() override { burger->setPatty("Soy (Tofu) Patty"); }
    void buildCheese() override { burger->setCheese(""); } // Vegans don't eat cheese
    void buildVeggies() override { 
        burger->addVeggie("Lettuce"); 
        burger->addVeggie("Tomato"); 
        burger->addVeggie("Avocado"); 
    }
    void buildSauce() override { burger->setSauce("Vegan Mayonnaise"); }
    
    Burger* getBurger() override { return burger; }
};

class Chef {
private:
    BurgerBuilder* builder;
public:
    void setBuilder(BurgerBuilder* b) {
        builder = b;
    }
    void makeBurger() {
        builder->buildBun();
        builder->buildPatty();
        builder->buildCheese();
        builder->buildVeggies();
        builder->buildSauce();
    }
};

int main() {
    Chef chef; // Our chef
    
    std::cout << "Order 1: Creating a Cheeseburger...\n";
    CheeseBurgerBuilder cheeseBuilder;
    chef.setBuilder(&cheeseBuilder);
    chef.makeBurger(); // Chef assembles it
    
    Burger* cheeseBurger = cheeseBuilder.getBurger();
    cheeseBurger->showBurger();

    std::cout << "Order 2: Creating a Vegan Burger...\n";
    VeganBurgerBuilder veganBuilder;
    chef.setBuilder(&veganBuilder);
    chef.makeBurger(); // Chef assembles it
    
    Burger* veganBurger = veganBuilder.getBurger();
    veganBurger->showBurger();

    return 0;
}
