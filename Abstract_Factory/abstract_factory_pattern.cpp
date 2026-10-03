#include <iostream>
#include <memory>
#include <string>

class IButton {
public:
    virtual ~IButton() = default;
    virtual void render() const = 0;
};

class ICheckbox {
public:
    virtual ~ICheckbox() = default;
    virtual void render() const = 0;
};

class WinButton : public IButton {
public:
    void render() const override { std::cout << "[Windows] A Windows-style button is being drawn (Button)\n"; }
};

class WinCheckbox : public ICheckbox {
public:
    void render() const override { std::cout << "[Windows] A Windows-style button is being drawn (Checkbox)\n"; }
};

class MacButton : public IButton {
public:
    void render() const override { std::cout << "[MacOS] A MAC-style button is being drawn (Button)\n"; }
};

class MacCheckbox : public ICheckbox {
public:
    void render() const override { std::cout << "[MacOS] A MAC-style button is being drawn (Checkbox)\n"; }
};

class IGUIFactory {
public:
    virtual ~IGUIFactory() = default;
    virtual std::unique_ptr<IButton> createButton() const = 0;
    virtual std::unique_ptr<ICheckbox> createCheckbox() const = 0;
};

class WinFactory : public IGUIFactory {
public:
    std::unique_ptr<IButton> createButton() const override {
        return std::make_unique<WinButton>();
    }
    std::unique_ptr<ICheckbox> createCheckbox() const override {
        return std::make_unique<WinCheckbox>();
    }
};

class MacFactory : public IGUIFactory {
public:
    std::unique_ptr<IButton> createButton() const override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<ICheckbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

void renderApplicationUI(const IGUIFactory& factory) {
    std::cout << "We are starting the construction of the interface...\n";
    auto button = factory.createButton();
    auto checkbox = factory.createCheckbox();

    button->render();
    checkbox->render();
    std::cout << "The interface was successfully built!\n\n";
}

int main() {
    std::cout << "--- We are launching the program in the Windows environment ---\n";
    WinFactory winFactory;
    renderApplicationUI(winFactory);

    std::cout << "--- We are launching the program in the MAC environment. ---\n";
    MacFactory macFactory;
    renderApplicationUI(macFactory);

    return 0;
}
