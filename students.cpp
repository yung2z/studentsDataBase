#include "students.h"

void addStudent(std::vector<Student>& database, std::istream& in, std::ostream& out) {
    Student student;
    out << "Введите имя студента: ";
    in >> student.name;
    out << "Введите возраст студента: ";
    in >> student.age;
    out << "Введите специальность студента: ";
    in >> student.major;
    out << "Введите средний балл студента: ";
    in >> student.gpa;

    database.push_back(student);
    out << "Студент добавлен в базу данных. Всего студентов: " << database.size() << "\n";
}

void deleteStudent(std::vector<Student>& database, std::istream& in, std::ostream& out) {
    if (database.empty()) {
        out << "База данных пуста. Нечего удалять.\n";
        return;
    }

    size_t index;
    while (true) {
        out << "Введите индекс студента для удаления (0-" << (database.size() - 1) << "): ";
        if (!(in >> index)) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            out << "Пожалуйста, введите число.\n";
            continue;
        }
        if (index >= database.size()) {
            out << "Неверный индекс. Допустимый диапазон: 0-" << (database.size() - 1) << "\n";
            continue;
        }
        break;
    }

    database.erase(database.begin() + static_cast<long long>(index));
    out << "Студент удалён. Осталось студентов: " << database.size() << "\n";
}

void displayStudents(const std::vector<Student>& database, std::ostream& out) {
    out << "Список студентов (" << database.size() << "):\n";
    for (size_t i = 0; i < database.size(); ++i) {
        const Student& student = database[i];
        out << "#" << i << "\n";
        out << "Имя: " << student.name << "\n";
        out << "Возраст: " << student.age << "\n";
        out << "Специальность: " << student.major << "\n";
        out << "Средний балл: " << student.gpa << "\n\n";
    }
    if (database.empty()) {
        out << "(пусто)\n";
    }
}


