#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// Тестируемые функции работают через переданные потоки ввода/вывода
void addStudent(std::vector<Student>& database, std::istream& in, std::ostream& out);
void deleteStudent(std::vector<Student>& database, std::istream& in, std::ostream& out);
void displayStudents(const std::vector<Student>& database, std::ostream& out);


