#include <iostream>
#include <string>


    std::string name;
    std::string email;
public:
    User(const std::string& n, const std::string& e) : name(n), email(e) {}
    
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
};


class UserRepository {
public:
    void saveToDatabase(const User& user) {
        
        std::cout << "Saving user " << user.getName() << " to the database..." << std::endl;
    }
};

int main() {
    User user1("Aram", "aram@example.com");
    UserRepository dbRepo;
    
    dbRepo.saveToDatabase(user1);
    return 0;
}
