#include <iostream>
#include <string>
#include <stdexcept>

class DBConnectionBuilder;

class DBConnection {
    friend class DBConnectionBuilder; 

private:
    std::string host;
    int port;
    std::string user;
    std::string password;
    std::string dbName;
    bool useSSL;

    DBConnection() : port(3306), useSSL(false) {}

public:
    void printConnectionInfo() const {
        std::cout << "--- Database Connection ---\n";
        std::cout << "Host:       " << host << ":" << port << "\n";
        std::cout << "User:       " << user << "\n";
        std::cout << "Database:   " << dbName << "\n";
        std::cout << "SSL Secure: " << (useSSL ? "Yes" : "No") << "\n";
        std::cout << "--------------------------------\n";
    }
};

class DBConnectionBuilder {
private:
    DBConnection db; 

public:
    explicit DBConnectionBuilder(const std::string& host) {
        if (host.empty()) {
            throw std::invalid_argument("Error: Host is required and cannot be empty.:");
        }
        db.host = host;
    }

    DBConnectionBuilder& port(int port) {
        db.port = port;
        return *this;
    }

    DBConnectionBuilder& credentials(const std::string& user, const std::string& password) {
        db.user = user;
        db.password = password;
        return *this;
    }

    DBConnectionBuilder& database(const std::string& dbName) {
        db.dbName = dbName;
        return *this;
    }

    DBConnectionBuilder& enableSSL(bool useSSL = true) {
        db.useSSL = useSSL;
        return *this;
    }

    DBConnection build() const {
        if (db.user.empty() || db.password.empty()) {
            throw std::logic_error("Error: The database user password is required for a complete connection:");
        }
        if (db.port <= 0 || db.port > 65535) {
            throw std::out_of_range("Error: The port must be in the range of 1 to 65535:");
        }

        return db;
    }
};

int main() {
    try {

        const DBConnection db = DBConnectionBuilder("127.0.0.1")
                                    .port(5432)
                                    .credentials("admin", "secret123")
                                    .database("my_project_db")
                                    .enableSSL(true)
                                    .build(); 
        
        db.printConnectionInfo();

    } catch (const std::exception& e) {
        std::cerr << "Exception. " << e.what() << '\n';
    }

    return 0;
}
