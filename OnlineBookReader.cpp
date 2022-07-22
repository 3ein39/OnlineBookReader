#include<iostream>
#include <map>
#include <vector>
using namespace std;

class User {
private:
    string name;
    string password;
    string email;
    string userName;
public:
    // Default constructors
    User() {}

    User(const string& name, const string& password, const string& email, const string& userName) {
        setName(name);
        setPassword(password);
        setEmail(email);
        setUserName(userName);
    }
    void printInfo() {
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "user_name: " << getUserName() << endl;
    }
    // setter and getters
    void setName(const string& name) {
        this->name = name;
    }
    const string& getName() const {
        return name;
    }
    void setPassword(const string& password) {
        this->password = password;
    }
    const string& getPassword() const {
        return password;
    }
    void setEmail(const string& email) {
        this->email = email;
    }
    const string& getEmail() const {
        return email;
    }
    void setUserName(const string& userName) {
        this->userName = userName;
    }
    const string& getUserName() const {
        return userName;
    }
};


class Book {
private:
    int isbn{};
    string title;
    string author;
    int nPages{};
    vector<string> content;

    public:
    // Default constructors
    Book() : isbn(0),nPages(0) {}

    Book(const int isbn,const string& title,const string& author,const int nPages) {
        setIsbn(isbn), setTitle(title), setAuthor(author), setnPages(nPages);
    }
    // setters and getters
    void setIsbn(const int isbn) {
        this->isbn = isbn;
    }
    const int& getIsbn() const {
        return isbn;
    }
    void setTitle(const string& title) {
        this->title = title;
    }
    const string& getTitle() const {
        return title;
    }
    void setAuthor(const string& author) {
        this->author = author;
    }
    const string& getAuthor() const {
        return author;
    }
    void setnPages(const int nPages) {
        this->nPages = nPages;
    }
    const int& getnPages() const {
        return nPages;
    }
    void setContent(vector<string>& content) {
        this->content = content;
    }
    const vector<string>& getContent() {
        return content;
    }
    // returning content of specific page
    const string& getContentByPage(const int page) {
        return content[page];
    }

};

class BooksManager {
private:
    vector<Book> books;
    map<string, int> sessions; // title to last page map
public:
    // Default constructors with fake database
    BooksManager() {
        vector<string> v(5);
        v[0] = "Chapter 1";
        v[1] = "Chapter 2";
        v[2] = "Chapter 3";
        v[3] = "Chapter 4";
        v[4] = "Chapter 5";
        Book a;
        a.setTitle("The Lord of the Rings");
        a.setAuthor("J.R.R. Tolkien");
        a.setnPages(5);
        a.setIsbn(34524);
        a.setContent(v);
        books.push_back(a);
        Book b;
        b.setTitle("The Hobbit");
        b.setAuthor("J.R.R. Tolkien");
        b.setnPages(5);
        b.setIsbn(34525);
        b.setContent(v);
        books.push_back(b);
    }
    // setters and getters
    const vector<Book>& getBooks() const {
        return books;
    }
    // add book to the vector
    void addBook() {
        cout << "Enter the ISBN: ";
        int isbn;
        cin >> isbn;
        cout << "Enter the title: ";
        string title;
        cin >> title;
        cout << "Enter the author: ";
        string author;
        cin >> author;
        cout << "Enter the number of pages: ";
        int nPages;
        cin >> nPages;
        vector<string> v(nPages);
        for (int i = 0; i < nPages; ++i) {
            cout << "Enter the content of chapter " << i + 1 << ": ";
            string content;
            cin >> content;
            v[i] = content;
        }
        Book a;
        a.setTitle(title);
        a.setAuthor(author);
        a.setnPages(nPages);
        a.setIsbn(isbn);
        a.setContent(v);
        books.push_back(a);
    }

    // show all available books and pick one to read
    // store the last page of the book in the map
    void pickBook() {
        cout << "\nOur current book collection: " << endl;
        for (int i = 0; i < books.size(); ++i) {
            cout << "\t" << i + 1 << ": " << books[i].getTitle() << endl;
        }
        int choice;
        cout << "\nEnter the number of the book you want to read: ";
        cin >> choice;
        if (choice > 0 && choice <= books.size()) {
            beginSession(books[choice - 1]);
        }
        else {
            cout << "Invalid choice. Try again\n";
        }
    }

    // begin a session of reading a book
    void beginSession(Book& book) {
        string title = book.getTitle();
        sessions[title] = 1;

        int choice;
        while (true) {
            getPage(book, sessions[title]);
            cout << "\nMenu: " << endl;
            cout << '\t' <<"1: View Next Page\n";
            cout << '\t' <<"2: View Previous Page\n";
            cout << '\t' <<"3: Stop Reading\n";
            cout << "Enter number in range 1 - 3: ";
            cin >> choice;
            if (!(1 <= choice && choice <= 3)) {
                cout << "Invalid choice. Try again\n";
                continue;
            }
            if (choice == 1) {
                getPage(book, ++sessions[title]);
            }
            else if (choice == 2) {
                getPage(book, --sessions[title]);
            }
            else if (choice == 3) {
             // after breaking .. the last session will be stored in the sessions map
             break;
            }
        }
    }
    void getPage(Book& book,int pagen) {
        string title = book.getTitle();
        cout << "You are now reading " << title << endl;

        cout << "Current page: " << sessions[title] << "/" << book.getnPages() << endl;
        cout << book.getContentByPage(sessions[title] - 1) << endl;
    }


    /*
     * Searching and removing functions will be in use
     * ... but in the next version :)
     */

    // remove book from the vector
    void removeBook(const int isbn) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                books.erase(books.begin() + i);
            }
        }
    }
    // search book by isbn
    const Book& searchBookByIsbn(const int isbn) const {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                return books[i];
            }
        }
    }
    // search book by title
    const Book& searchBookByTitle(const string& title) const {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getTitle() == title) {
                return books[i];
            }
        }
    }
    // search book by author
    const Book& searchBookByAuthor(const string& author) const {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getAuthor() == author) {
                return books[i];
            }
        }
    }
};

class UsersManager {
private:
    map<string, User> userName_userObj_map;
    User current_user;
    BooksManager booksManager;

public:
    // Default constructors with fake users for testing
    UsersManager() {
        userName_userObj_map["hany"] = User("Hany", "123", "test@mail", "hany");
    }
    // setter and getters
    void setCurrentUser(const string& userName) {
        current_user = userName_userObj_map[userName];
    }
    const User& getCurrentUser() const {
        return current_user;
    }
    // return user by userName
    const User& getUser(const string& userName) const {
        return userName_userObj_map.at(userName);
    }
    // add user to the map
    void addUser(const User& user) {
        userName_userObj_map[user.getUserName()] = user;
    }
    // check if the user name is already exist in the map
    bool isUserNameExist(const string& userName) {
        return userName_userObj_map.find(userName) != userName_userObj_map.end();
    }
    // check if the user name and password are correct
    bool isUserNameAndPasswordCorrect(const string& userName, const string& password) {
        if (isUserNameExist(userName)) {
            return userName_userObj_map[userName].getPassword() == password;
        }
        return false;
    }
    void accessSystem() {
        while (true) {
            int choice = userMenu();
            if (choice == 1)
                current_user.printInfo();
            else if (choice == 3)
                booksManager.pickBook();
            else if (choice == 4)
                break;
        }
    }

    int userMenu() {
        int choice = -1;
        while (choice == -1) {
            cout << "\nHello " << current_user.getName() << " | User View" << endl;
            cout << "\nMenu: " << endl;
            cout << '\t' <<"1: View Profile\n";
            cout << '\t' <<"2: List & Select from My Reading History\n";
            cout << '\t' <<"3: List & Select from Available Books\n";
            cout << '\t' <<"4: Logout\n";

            cout << "Enter number in range 1 - 4: ";
            cin >> choice;

            if (!(1 <= choice && choice <= 4)) {
                cout << "Invalid choice. Try again\n";
                choice = -1;	// loop keep working
            }
        }
        return choice;
    }

};


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

    void printInfo() {
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "user_name: " << getUserName() << endl;
    }

    // Setters & Getters
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
    Admin current_admin;
    BooksManager booksManager;
public:
    // Default constructor creates admin for simplicity
    AdminsManager() {
        // we could have a separate file to read from and store data
        // but for simplicity we will use a single admin object
        // also it is not a good idea to store password in plain text
        // but anyway, the purpose of this project is to enhance designing skills
        string name = "Hussein Hany", password = "123", email = "admin@mail", user_name = "3ein39";
        Admin admin(name, password, email, user_name);
        username_adminObj_map[user_name] = admin;
    }

    const Admin& getAdmin(const string& user_name) {
        return username_adminObj_map.at(user_name);
    }
    void setCurrentAdmin(const string& user_name) {
        current_admin = username_adminObj_map.at(user_name);
    }

    bool isAdminExist(const string& user_name) {
        return username_adminObj_map.find(user_name) != username_adminObj_map.end();
    }

    void accessSystem() {
        while (true) {
            int choice = adminMenu();
            if (choice == 1)
                current_admin.printInfo();
            else if (choice == 2)
                booksManager.addBook();
            else if (choice == 3)
                break;
        }
    }

    int adminMenu() {
        int choice = -1;
        while (choice == -1) {
            cout << "\nHello " << current_admin.getName() << " | Admin View" << endl;
            cout << "\nMenu: " << endl;
            cout << '\t' <<"1: View Profile\n";
            cout << '\t' <<"2: Add Book\n";
            cout << '\t' <<"3: Logout\n";

            cout << "Enter number in range 1 - 3: ";
            cin >> choice;

            if (!(1 <= choice && choice <= 3)) {
                cout << "Invalid choice. Try again\n";
                choice = -1;	// loop keep working
            }
        }
        return choice;
    }
};

class readerSystem {
private:
    UsersManager usersManager;
    AdminsManager adminsManager;

    void doLogin() {
        string user_name, password;
        cout << "Enter user name: ";
        cin >> user_name;
        cout << "Enter password: ";
        cin >> password;
        if (adminsManager.isAdminExist(user_name) && adminsManager.getAdmin(user_name).getPassword() == password) {
            cout << "Admin Login successful\n" << endl;
            adminsManager.setCurrentAdmin(user_name);
            adminsManager.accessSystem();
        } else if (usersManager.isUserNameExist(user_name) && usersManager.getUser(user_name).getPassword() == password) {
            cout << "User Login successful\n" << endl;
            usersManager.setCurrentUser(user_name);
            usersManager.accessSystem();
        } else {
            cout << "Login failed" << endl;
            doLogin();
        }
    }
    int menu() {
        int choice = -1;
        while (choice == -1) {
            cout << "\nWelcome to Online Book Reader" << endl;
            cout << "\nMenu: " << endl;
            cout << '\t' <<"1: Login\n";
            cout << '\t' <<"2: Signup\n";

            cout << "Enter number in range 1 - 2: ";
            cin >> choice;

            if (!(1 <= choice && choice <= 2)) {
                cout << "Invalid choice. Try again\n";
                choice = -1;	// loop keep working
            }
        }
        return choice;
    }
public:
    void Run() {
        accessSystem();
    }

    void accessSystem() {
        while (true) {
            int choice = menu();
            if (choice == 1)
                doLogin();
        }
    }

};

int main() {

    readerSystem readerSystem;
    readerSystem.Run();
    return 0;
}
/*
 * Admin : 3ein39 123
 * User: hany 123
 */