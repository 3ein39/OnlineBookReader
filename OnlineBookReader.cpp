#include<iostream>
#include <map>
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
        setName(name);
        setPassword(password);
        setEmail(email);
        setUserName(user_name);
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

class AdminsManager {
private:
    map<string, Admin> username_adminObj_map;

public:
    // Default constructor creates admin for simplicity
    AdminsManager() {
        // we could have a separate file to read from and store data
        // but for simplicity we will use a single admin object
        // also it is not a good idea to store password in plain text
        // but anyway, the purpose of this project is to enhance designing skills
        string name = "Admin", password = "123", email = "admin@mail", user_name = "admin";
        Admin admin(name, password, email, user_name);
        username_adminObj_map[user_name] = admin;
    }

    const Admin& getAdmin(const string& user_name) {
        return username_adminObj_map.at(user_name);
    }

    bool isAdminExist(const string& user_name) {
        return username_adminObj_map.find(user_name) != username_adminObj_map.end();
    }
};

int main() {

    return 0;
}