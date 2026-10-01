#include <iostream>

class IPrinter {
public:
    virtual void printDocument() = 0;
    virtual ~IPrinter() = default;
};

class IScanner {
public:
    virtual void scanDocument() = 0;
    virtual ~IScanner() = default;
};

class SimplePrinter : public IPrinter {
public:
    void printDocument() override {
        std::cout << "Simple Printer: Printing document..." << std::endl;
    }
};

class MultiFunctionMachine : public IPrinter, public IScanner {
public:
    void printDocument() override {
        std::cout << "MFP: Printing fast and in color..." << std::endl;
    }
    void scanDocument() override {
        std::cout << "MFP: Scanning document to PDF..." << std::endl;
    }
};

int main() {
    SimplePrinter simple;
    simple.printDocument();
    
    MultiFunctionMachine mfp;
    mfp.printDocument();
    mfp.scanDocument();
    
    return 0;
}
