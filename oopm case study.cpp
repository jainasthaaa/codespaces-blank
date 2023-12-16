#include <iostream>
#include <vector>
#include <limits> // for numeric_limits
#include <algorithm>

class Employee {
public:
    Employee(int id, std::string name) : id(id), name(name) {}

    virtual void display() const {
        std::cout << "ID: " << id << ", Name: " << name;
    }

    int getId() const {
        return id;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

private:
    int id;
    std::string name;
};

class Manager : public Employee {
public:
    Manager(int id, std::string name, std::string department)
        : Employee(id, name), department(department) {}

    void display() const override {
        Employee::display();
        std::cout << ", Department: " << department;
    }

private:
    std::string department;
};

class Engineer : public Employee {
public:
    Engineer(int id, std::string name, std::string specialty)
        : Employee(id, name), specialty(specialty) {}

    void display() const override {
        Employee::display();
        std::cout << ", Specialty: " << specialty;
    }

private:
    std::string specialty;
};

class EmployeeDatabase {
public:
    // Insertion
    void addEmployee(Employee* emp) {
        employees.push_back(emp);
    }

    // Deletion
    void removeEmployee(int id) {
        auto it = std::remove_if(employees.begin(), employees.end(),
                                 [id](const Employee* emp) { return emp->getId() == id; });

        employees.erase(it, employees.end());
    }

    // Searching
    Employee* findEmployee(int id) const {
        auto it = std::find_if(employees.begin(), employees.end(),
                               [id](const Employee* emp) { return emp->getId() == id; });

        if (it != employees.end()) {
            return *it;
        } else {
            return nullptr; // Not found
        }
    }

    // Updation
    void updateEmployee(int id, const std::string& newName) {
        Employee* emp = findEmployee(id);

        if (emp != nullptr) {
            emp->setName(newName);
        } else {
            std::cout << "Employee with ID " << id << " not found." << std::endl;
        }
    }

    // Display all employees
    void displayAllEmployees() const {
        for (const auto& emp : employees) {
            emp->display();
            std::cout << std::endl;
        }
    }

private:
    std::vector<Employee*> employees;
};

int main() {
    EmployeeDatabase database;

    while (true) {
        std::cout << "\nMenu:\n"
                     "1. Add Employee\n"
                     "2. Display All Employees\n"
                     "3. Search Employee\n"
                     "4. Update Employee\n"
                     "5. Remove Employee\n"
                     "6. Exit\n"
                     "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter employee details:\n";
                int id;
                std::string name;
                std::cout << "ID: ";
                std::cin >> id;
                std::cout << "Name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                std::getline(std::cin, name);

                // Add employee based on type (Manager or Engineer)
                std::cout << "Enter employee type (1 for Manager, 2 for Engineer): ";
                int type;
                std::cin >> type;

                if (type == 1) {
                    std::string department;
                    std::cout << "Department: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                    std::getline(std::cin, department);

                    Manager* manager = new Manager(id, name, department);
                    database.addEmployee(manager);
                } else if (type == 2) {
                    std::string specialty;
                    std::cout << "Specialty: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                    std::getline(std::cin, specialty);

                    Engineer* engineer = new Engineer(id, name, specialty);
                    database.addEmployee(engineer);
                } else {
                    std::cout << "Invalid employee type.\n";
                }

                break;
            }
            case 2:
                std::cout << "All Employees:\n";
                database.displayAllEmployees();
                break;
            case 3: {
                std::cout << "Enter employee ID to search: ";
                int searchId;
                std::cin >> searchId;

                Employee* foundEmployee = database.findEmployee(searchId);

                if (foundEmployee != nullptr) {
                    std::cout << "Employee found: ";
                    foundEmployee->display();
                    std::cout << std::endl;
                } else {
                    std::cout << "Employee with ID " << searchId << " not found." << std::endl;
                }

                break;
            }
            case 4: {
                std::cout << "Enter employee ID to update: ";
                int updateId;
                std::cin >> updateId;

                std::string newName;
                std::cout << "Enter new name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
                std::getline(std::cin, newName);

                database.updateEmployee(updateId, newName);
                break;
            }
            case 5: {
                std::cout << "Enter employee ID to remove: ";
                int deleteId;
                std::cin >> deleteId;
                database.removeEmployee(deleteId);
                break;
            }
            case 6:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
