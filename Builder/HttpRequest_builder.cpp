#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

struct HttpRequest {
    std::string url;
    std::string method = "GET";
    std::map<std::string, std::string> headers;
    std::string body;
    int timeoutMs = 3000;
};

class HttpRequestBuilder {
private:
    HttpRequest request; 

public:
   
    explicit HttpRequestBuilder(const std::string& url) {
        if (url.empty()) {
            throw std::invalid_argument("URL can't empty:");
        }
        request.url = url;
    }

    HttpRequestBuilder& method(const std::string& method) {
        request.method = method;
        return *this;
    }

    HttpRequestBuilder& header(const std::string& key, const std::string& value) {
        request.headers[key] = value;
        return *this;
    }

    HttpRequestBuilder& body(const std::string& body) {
        request.body = body;
        return *this;
    }

    HttpRequestBuilder& timeoutMs(int timeoutMs) {
        request.timeoutMs = timeoutMs;
        return *this;
    }

    HttpRequest build() const {
        if (request.method == "GET" && !request.body.empty()) {
            throw std::logic_error("false. GET requests must not have a body.:");
        }
        if (request.timeoutMs <= 0) {
            throw std::logic_error("Error: Timeout must be greater than zero:");
        }

        return request; 
    }
};

int main() {
    try {
    
        const HttpRequest req = HttpRequestBuilder("https://api.example.com/data")
                                    .method("POST")
                                    .header("Content-Type", "application/json")
                                    .header("Authorization", "Bearer token123")
                                    .body(R"({"name": "Sona"})")
                                    .timeoutMs(5000)
                                    .build();
        
        std::cout << "success\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
