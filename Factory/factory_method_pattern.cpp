#include <iostream>
#include <memory>
#include <string>

class ITransport {
public:
    virtual ~ITransport() = default;
    virtual void deliver() const = 0;
};

class Truck : public ITransport {
public:
    void deliver() const override {
        std::cout << "[Freight] The product is shipped overland in boxes:\n";
    }
};

class Ship : public ITransport {
public:
    void deliver() const override {
        std::cout << "[Shipping] The product is shipped by sea in a container\n";
    }
};

class Logistics {
public:
    virtual ~Logistics() = default;

    virtual std::unique_ptr<ITransport> createTransport() const = 0;

    void planDelivery() const {
        std::cout << "Logistics: We are planning the delivery...\n";
        
        std::unique_ptr<ITransport> transport = createTransport();
        
        transport->deliver();
    }
};

class RoadLogistics : public Logistics {
public:
    std::unique_ptr<ITransport> createTransport() const override {
        return std::make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics {
public:
    std::unique_ptr<ITransport> createTransport() const override {
        return std::make_unique<Ship>();
    }
};

void clientCode(const Logistics& logisticsFactory) {
    logisticsFactory.planDelivery();
}

int main() {
    std::cout << "--- Launch of land logistics ---\n";
    RoadLogistics roadLogistics;
    clientCode(roadLogistics);

    std::cout << "\n--- Launch of maritime logistics ---\n";
    SeaLogistics seaLogistics;
    clientCode(seaLogistics);

    return 0;
}
