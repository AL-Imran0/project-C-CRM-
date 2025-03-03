#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct Customer {
    int id;
    string name, email, phone, address, notes;
};

vector<Customer> customers;
int customerID = 1;
const string filename = "customers.txt";

void loadCustomers() {
    ifstream file(filename);
    if (!file) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Customer c;
        ss >> c.id >> ws;
        getline(ss, c.name, ',');
        getline(ss, c.email, ',');
        getline(ss, c.phone, ',');
        getline(ss, c.address, ',');
        getline(ss, c.notes);
        customers.push_back(c);
        if (c.id >= customerID) customerID = c.id + 1;
    }
    file.close();
}

void saveCustomers() {
    ofstream file(filename);
    for (auto &c : customers) {
        file << c.id << " " << c.name << "," << c.email << "," << c.phone << "," << c.address << "," << c.notes << endl;
    }
    file.close();
}

void addCustomer() {
    Customer c;
    c.id = customerID++;
    cout << "Enter Name: "; getline(cin, c.name);
    cout << "Enter Email: "; getline(cin, c.email);
    cout << "Enter Phone: "; getline(cin, c.phone);
    cout << "Enter Address: "; getline(cin, c.address);
    cout << "Enter Notes: "; getline(cin, c.notes);
    customers.push_back(c);
    saveCustomers();
    cout << "Customer added successfully!\n";
}

void viewCustomers() {
    cout << "\nCustomer List:\n";
    for (auto &c : customers) {
        cout << "ID: " << c.id << " | Name: " << c.name << " | Email: " << c.email 
             << " | Phone: " << c.phone << " | Address: " << c.address 
             << " | Notes: " << c.notes << endl;
    }
}

void updateCustomer() {
    int id;
    cout << "Enter Customer ID to Update: "; cin >> id; cin.ignore();
    for (auto &c : customers) {
        if (c.id == id) {
            cout << "Enter New Name: "; getline(cin, c.name);
            cout << "Enter New Email: "; getline(cin, c.email);
            cout << "Enter New Phone: "; getline(cin, c.phone);
            cout << "Enter New Address: "; getline(cin, c.address);
            cout << "Enter New Notes: "; getline(cin, c.notes);
            saveCustomers();
            cout << "Customer updated!\n";
            return;
        }
    }
    cout << "Customer not found!\n";
}

void deleteCustomer() {
    int id;
    cout << "Enter Customer ID to Delete: "; cin >> id;
    customers.erase(remove_if(customers.begin(), customers.end(), [id](Customer &c) {
        return c.id == id;
    }), customers.end());
    saveCustomers();
    cout << "Customer deleted!\n";
}

void searchCustomer() {
    string keyword;
    cout << "Enter Name or Email to Search: "; getline(cin, keyword);
    cout << "\nSearch Results:\n";
    for (auto &c : customers) {
        if (c.name.find(keyword) != string::npos || c.email.find(keyword) != string::npos) {
            cout << "ID: " << c.id << " | Name: " << c.name << " | Email: " << c.email 
                 << " | Phone: " << c.phone << " | Address: " << c.address 
                 << " | Notes: " << c.notes << endl;
        }
    }
}

int main() {
    loadCustomers();
    int choice;
    do {
        cout << "\nCRM System\n";
        cout << "1. Add Customer\n2. View Customers\n3. Update Customer\n4. Delete Customer\n5. Search Customer\n6. Exit\nChoose an option: ";
        cin >> choice; cin.ignore();
        switch (choice) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: updateCustomer(); break;
            case 4: deleteCustomer(); break;
            case 5: searchCustomer(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (choice != 6);
    return 0;
}
