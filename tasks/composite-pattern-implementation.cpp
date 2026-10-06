#include <iostream>
#include <vector>
#include <algorithm>
class Product{
public:
    virtual double get_price() const = 0;
    
};

class Pen: public Product{
    private:
    double price;
    std::string name;
   public:
   Pen(std::string n, double p) : name(n), price(p) {}
   double get_price() const override {
       return price;
   }
   
    
};
class Box : public Product{
    private:
    std::vector<Product*> products;
    public:
    void addProduct(Product* product) {
        if (product == this) {
            std::cerr << "Cannot add a box to itself." << std::endl;
            return;
        }
        products.push_back(product);
    }
    double get_price() const override {
        int n=0;
        double total = 0;
        for (const auto& product : products) {
            std::cout << n++ << std::endl;
            total += product->get_price();
        }
        return total;
    }
    void removeProduct(Product* product) {
        products.erase(std::remove(products.begin(), products.end(), product), products.end());
    }
};

int main(){
    Pen pen("sev", 150);
    Box root;
    root.addProduct(&pen);
    Box subbox;
    Pen red_pen("red", 200);
    subbox.addProduct(&red_pen);
    subbox.addProduct(&pen);
    root.addProduct(&subbox);
    subbox.removeProduct(&red_pen);
    root.addProduct(&root);
    int total_price = root.get_price();
    std::cout << "Total price: " << total_price << std::endl;

}
