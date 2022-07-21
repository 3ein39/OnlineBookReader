#include<iostream>
using namespace std;

class Admin {
private:
    string name;
    string password;
    string email;
    string user_name;

public:
    // Default constructor with initializer list -- delegating constructor
    Admin() : Admin("", "", "", "") {}

    Admin(const string& name, const string& password, const string& email, const string& user_name) {
        this->name = name;
        this->password = password;
        this->email = email;
        this->user_name = user_name;
    }

    void setName(const string& name) {
        this->name = name;
    }
    void setPassword(const string& password) {
        this->password = password;
    }
    void setEmail(const string& email) {
        this->email = email;
    }
    void setUserName(const string& user_name) {
        this->user_name = user_name;
    }
    const string& getName() const {
        return name;
    }
    const string& getPassword() const {
        return password;
    }
    const string& getEmail() const {
        return email;
    }
    const string& getUserName() const {
        return user_name;
    }
};

int main() {

    return 0;
}