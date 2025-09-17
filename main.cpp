#include <iostream>
#include <vector>
#include "students.h"

int main() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Удалить студента\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие (0-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database, std::cin, std::cout);
                break;
            case 2:
                displayStudents(database, std::cout);
                break;
            case 3:
                deleteStudent(database, std::cin, std::cout);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
