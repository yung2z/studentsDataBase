#include <iostream>
#include <vector>
#include <string>
#include <limits>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных. Всего студентов: " << database.size() << "\n";
}

// Заглушка для удаления студента из базы данных (реализация будет добавлена позже)
void deleteStudent(std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста. Нечего удалять.\n";
        return;
    }

    size_t index;
    while (true) {
        std::cout << "Введите индекс студента для удаления (0-" << (database.size() - 1) << "): ";
        if (!(std::cin >> index)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Пожалуйста, введите число.\n";
            continue;
        }
        if (index >= database.size()) {
            std::cout << "Неверный индекс. Допустимый диапазон: 0-" << (database.size() - 1) << "\n";
            continue;
        }
        break;
    }

    database.erase(database.begin() + static_cast<long long>(index));
    std::cout << "Студент удалён. Осталось студентов: " << database.size() << "\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов (" << database.size() << "):\n";
    for (size_t i = 0; i < database.size(); ++i) {
        const Student& student = database[i];
        std::cout << "#" << i << "\n";
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
    if (database.empty()) {
        std::cout << "(пусто)\n";
    }
}

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
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                deleteStudent(database);
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
