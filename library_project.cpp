
#include<algorithm>
#include <iostream>
using namespace std;
int c_book = 0;
int c_users = 0;
struct book {
    int id = -1;
    string name = "";
    int q = -1;
    int borrowed = -1;
    void read_book() {
        cout << "Enter book Name,ID,Quantity: ";
        cin >> name >> id >> q;
        borrowed = 0;
    }
    bool prefix(string pre) {
        if (pre.size() > name.size())return false;
        for (int i = 0; i < pre.size(); i++) {
            if (pre[i] != name[i])return false;
        }
        return true;

    }
    void print() {
        cout << " ID " << id << " Name " << name << " Quantity " << q << " total_borrowed_book " << borrowed << "\n";
    }
    bool borrowed_book(int user_id) {
        if (q - borrowed == 0)return false;
        else {
            borrowed++;
            return true;
        }
    }
    void return_copy() {
        if (borrowed > 0) {
            borrowed--;
        }
    }
};
book books[300];
struct user {
    int id = -1;
    string name = "";
    int borrowed_book[300];
    int len = -1;
    void read_user() {
        cout << "Enter user Name,ID ";
        cin >> name >> id;
        len = 0;
    }
    void borrow(int book_id) {
        borrowed_book[len++] = book_id;
    }
    void return_copy(int book_id) {
        bool found = false;
        for (int i = 0; i < len; i++) {
            if (book_id == borrowed_book[i]) {
                found = true;
                for (int j = i + 1; j < len; j++) {
                    borrowed_book[j - 1] = borrowed_book[j];
                }
                len--;
                break;
            }
        }
        if (!found) {
            cout << "user:" << name << " didnot borrow this book befor "<<book_id;
        }

    }
    void print() {
        sort(borrowed_book, borrowed_book + len);//sort user's borrowed books
        cout << "User " << name << " ID " << id << " borrowed_books: ";
        for (int i = 0; i < len; i++) {
            cout << borrowed_book[i] << " ";
        }
        cout << "\n";

    }
    bool isborrowed(int book_id) {
        for (int i = 0; i < len; i++) {
            if (borrowed_book[i] == book_id) {
                return true;
            }
        }
        return false;
    }
};
user users[300];
void add_book() {
    books[c_book++].read_book();
}
void search() {
    cout << "Enter book name prefix: ";
    string pre;
    cin >> pre;
    bool found = false;
    for (int i = 0; i < c_book; i++) {
        if (books[i].prefix(pre)) {
            cout << books[i].name << " ";
            found = true;
        }
    }
    if (!found) {
        cout << "NO books with such prefix\n";
    }
}

int find_book_index_by_name(string book_name) {
    for (int i = 0; i < c_book; i++) {
        if (books[i].name == book_name)return i;
    }
    return -1;
}
void print_who_borrowd_book_by_name() {
    cout << "Enter book Name: ";
    string name;
    cin >> name;
    int book_indx = find_book_index_by_name(name);
    if (book_indx == -1) {
        cout << "invalid book name\n";
        return;
    }
    if (books[book_indx].borrowed == 0) {
        cout << "Noone borrowed this book before\n";
        return;
    }
    int book_id = books[book_indx].id;

    for (int i = 0; i < c_users; i++) {
        if (users[i].isborrowed(book_id)) {
            cout << users[i].name << " ";
        }
    }
    cout << "\n";
}
bool comp_by_id(book &b1, book &b2) {
    return b1.id < b2.id;
  }
void print_by_id() {
    sort(books, books + c_book, comp_by_id);
    for (int i = 0; i < c_book; i++) {
        books[i].print();
    }
}
bool comp_by_name(book&b1, book&b2) {
    return b1.name < b2.name;
}
void print_by_name() {
    sort(books, books + c_book, comp_by_name);
    for (int i = 0; i < c_book; i++) {
        books[i].print();
    }
}
void add_user() {
    users[c_users++].read_user();
}
int find_user_index_by_name(string user_name) {
    for (int i = 0; i < c_users; i++) {
        if (users[i].name == user_name) {
            return i;
        }
    }
    return -1;
}
void user_borrow_book() {
    cout << "Enter user Name and book Name: ";
    string book_name;
    string user_name;
    cin >> user_name >> book_name;
    int book_idx = find_book_index_by_name(book_name);
    int user_idx = find_user_index_by_name(user_name);
    users[user_idx].borrow(books[book_idx].id);
    books[book_idx].borrowed_book(users[user_idx].id);
}
void return_copy() {
    cout << "Enter user Name and book Name:";
    string user_name;
    string book_name;
    cin >> user_name >> book_name;
    int book_idx = find_book_index_by_name(book_name);
    int user_idx = find_user_index_by_name(user_name);
    users[user_idx].return_copy(books[book_idx].id);
    books[book_idx].return_copy();
}
void print_users() {
    for (int i = 0; i < c_users; i++) {
        users[i].print();
    }
}
int main()
{
    int choice = -1;
    while (true) {
      
        cout << "1) add_book\n";
        cout << "2) search_books_by_prefix\n";
        cout << "3) print_who_borrowed_book_by_name\n";
        cout << "4) print_library_by_id\n";
        cout << "5) print_library_by_name\n";
        cout << "6) add_user\n";
        cout << "7) user_borrow_book\n";
        cout << "8) user_return_book\n";
        cout << "9) print_users\n";
        cout << "10) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) {
            add_book();
        }
        else if (choice == 2) {
            search();
        }
        else if (choice == 3) {
            print_who_borrowd_book_by_name();
        }
        else if (choice == 4) {
            print_by_id();
        }
        else if (choice == 5) {
            print_by_name();
        }
        else if (choice == 6) {
            add_user();
        }
        else if (choice == 7) {
            user_borrow_book();
        }
        else if (choice == 8) {
            return_copy();
        }
        else if (choice == 9) {
            print_users();
        }
        else if (choice == 10)return 1;
        else cout << "Invalid choice ,Try again";
    }
    
}

