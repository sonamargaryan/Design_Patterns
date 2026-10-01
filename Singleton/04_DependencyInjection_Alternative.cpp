#include <iostream>

class Config {
public:
    int screenWidth = 1920;
    int screenHeight = 1080;
};

class PolygonRenderer {
private:
    Config& m_config;
public:
    PolygonRenderer(Config& config) : m_config(config) {} 
    
    void render() {
        std::cout << "Rendering polygon on screen: " 
                  << m_config.screenWidth << "x" << m_config.screenHeight << "\n";
    }
};

int main() {
    Config appConfig; 
    
    PolygonRenderer renderer(appConfig); 
    renderer.render();
    
    return 0;
}
