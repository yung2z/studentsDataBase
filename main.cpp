#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "gtest/gtest.h"
#include <sstream>

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
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    if (database.empty()){
        std::cout << "База данных пуста\n";
        return;
    }
    std::cout << "Список студентов:\n";
    for (size_t i = 0; i < database.size(); i++) {
        const Student& student = database[i];
        std::cout << i + 1 << ". Имя: " << student.name << "\n";
        std::cout << "   Возраст: " << student.age << "\n";
        std::cout << "   Специальность: " << student.major << "\n";
        std::cout << "   Средний балл: " << student.gpa << "\n\n";
    }
}

// Функция для удаления студента из базы данных
void removeStudent(std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста. Нечего удалять.\n";
        return;
    }

    displayStudents(database);
    
    int index;
    std::cout << "Введите номер студента для удаления (1-" << database.size() << "): ";
    std::cin >> index;
    
    if (std::cin.fail() || index < 1 || index > static_cast<int>(database.size())) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Неверный номер студента.\n";
        return;
    }
    
    std::string nameToRemove = database[index - 1].name;
    database.erase(database.begin() + index - 1);
    std::cout << "Студент " << nameToRemove << " удален из базы данных.\n";
}

// Функция для удаления студента по имени (для тестов)
bool removeStudentByName(std::vector<Student>& database, const std::string& name) {
    auto it = std::remove_if(database.begin(), database.end(),
        [&name](const Student& student) {
            return student.name == name;
        });
    
    if (it != database.end()) {
        database.erase(it, database.end());
        return true;
    }
    return false;
}

// Тесты
TEST(StudentFunctionsTest, RemoveStudentByName) {
    std::vector<Student> database = {
        {"Sasha", 21, "Math", 5.0},
        {"Andrew", 20, "Math", 4.2},
        {"Nikita", 22, "Math", 3.8}
    };
    
    bool result = removeStudentByName(database, "Andrew");
    EXPECT_TRUE(result);
    EXPECT_EQ(database.size(), 2);
    EXPECT_EQ(database[0].name, "Sasha");
    EXPECT_EQ(database[1].name, "Nikita");
}

TEST(StudentFunctionsTest, RemoveStudentByName_NotFound) {
    std::vector<Student> database = {
        {"Sasha", 21, "Math", 5.0},
        {"Andrew", 20, "Math", 4.2}
    };
    
    bool result = removeStudentByName(database, "Ivan");
    EXPECT_FALSE(result);
    EXPECT_EQ(database.size(), 2);
}

TEST(StudentFunctionsTest, RemoveStudentByName_EmptyDatabase) {
    std::vector<Student> database;
    
    bool result = removeStudentByName(database, "Sasha");
    EXPECT_FALSE(result);
    EXPECT_TRUE(database.empty());
}

TEST(StudentFunctionsTest, RemoveStudentByName_MultipleSameNames) {
    std::vector<Student> database = {
        {"Sasha", 21, "Math", 5.0},
        {"Sasha", 20, "Physics", 4.5},
        {"Andrew", 22, "Math", 4.2}
    };
    
    bool result = removeStudentByName(database, "Sasha");
    EXPECT_TRUE(result);
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Andrew");
}

TEST(StudentFunctionsTest, RemoveStudentByName_CaseSensitive) {
    std::vector<Student> database = {
        {"sasha", 21, "Math", 5.0},
        {"Sasha", 20, "Physics", 4.5}
    };
    
    bool result = removeStudentByName(database, "Sasha");
    EXPECT_TRUE(result);
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "sasha");
}

void view() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Удалить студента\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                removeStudent(database);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
        }
    } while (choice != 0);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        view();
        return 0;
    }
}
