#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct UserData {
    string name;
    string vehicleNumber;
    string vehicleType;
};

void saveData(const vector<UserData>& users, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Name,Vehicle Number,Vehicle Type\n";
        for (const auto& user : users) {
            file << user.name << "," << user.vehicleNumber << "," << user.vehicleType << "\n";
        }
        file.close();
        cout << "Data saved successfully to " << filename << endl;
    } else {
        cerr << "Unable to open file for writing" << endl;
    }
}

void loadData(vector<UserData>& users, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line, name, vehicleNumber, vehicleType;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            name = line.substr(0, pos1);
            vehicleNumber = line.substr(pos1 + 1, pos2 - pos1 - 1);
            vehicleType = line.substr(pos2 + 1);
            users.push_back({name, vehicleNumber, vehicleType});
        }
        file.close();
    } else {
        cerr << "Unable to open file for reading" << endl;
    }
}

void addUser(vector<UserData>& users) {
    UserData newUser;
    cout << "Enter name: ";
    cin >> newUser.name;
    cout << "Enter vehicle number: ";
    cin >> newUser.vehicleNumber;
    cout << "Enter vehicle type: ";
    cin >> newUser.vehicleType;
    users.push_back(newUser);
}

void searchByVehicleNumber(const vector<UserData>& users, const string& vehicleNumber) {
    for (const auto& user : users) {
        if (user.vehicleNumber == vehicleNumber) {
            cout << "Owner: " << user.name << "\nVehicle Type: " << user.vehicleType << endl;
            return;
        }
    }
    cout << "Vehicle not found" << endl;
}

int main() {
    vector<UserData> users;
    string filename = "userData.csv";
    
    // Load existing data
    loadData(users, filename);

    int choice;
    while (true) {
        cout << "1. Add User\n2. Search by Vehicle Number\n3. Save Data\n4. Exit\nEnter your choice: ";
        cin >> choice;
        if (choice == 1) {
            addUser(users);
        } else if (choice == 2) {
            string vehicleNumber;
            cout << "Enter vehicle number: ";
            cin >> vehicleNumber;
            searchByVehicleNumber(users, vehicleNumber);
        } else if (choice == 3) {
            saveData(users, filename);
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}

