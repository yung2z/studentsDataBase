#include <gtest/gtest.h>
#include <sstream>
#include "students.h"

// 1) Юнит: добавление одного студента
TEST(StudentsDbTests, AddSingleStudent) {
    std::vector<Student> db;
    std::istringstream in("Ivan\n20\nCS\n4.5\n");
    std::ostringstream out;
    addStudent(db, in, out);
    ASSERT_EQ(db.size(), 1u);
    EXPECT_EQ(db[0].name, "Ivan");
    EXPECT_EQ(db[0].age, 20);
    EXPECT_EQ(db[0].major, "CS");
    EXPECT_DOUBLE_EQ(db[0].gpa, 4.5);
}

// 2) Юнит: вывод пустой базы
TEST(StudentsDbTests, DisplayEmpty) {
    std::vector<Student> db;
    std::ostringstream out;
    displayStudents(db, out);
    auto s = out.str();
    EXPECT_NE(s.find("(пусто)"), std::string::npos);
}

// 3) Интеграция: добавление двух студентов и вывод
TEST(StudentsDbTests, AddTwoAndDisplay) {
    std::vector<Student> db;
    std::istringstream in("Ann\n19\nMath\n4.1\nBob\n21\nPhysics\n3.7\n");
    std::ostringstream out;
    addStudent(db, in, out);
    addStudent(db, in, out);
    out.str(""); out.clear();
    displayStudents(db, out);
    std::string s = out.str();
    EXPECT_NE(s.find("Ann"), std::string::npos);
    EXPECT_NE(s.find("Bob"), std::string::npos);
    ASSERT_EQ(db.size(), 2u);
}

// 4) Удаление с неверным индексом, потом с верным
TEST(StudentsDbTests, DeleteWithRetryOnInvalidIndex) {
    std::vector<Student> db = {
        {"A", 18, "X", 3.1},
        {"B", 19, "Y", 3.2},
        {"C", 20, "Z", 3.3}
    };
    // сначала некорректный индекс 10, затем корректный 1
    std::istringstream in("10\n1\n");
    std::ostringstream out;
    deleteStudent(db, in, out);
    ASSERT_EQ(db.size(), 2u);
    EXPECT_EQ(db[0].name, "A");
    EXPECT_EQ(db[1].name, "C");
}

// 5) Удаление из пустой базы
TEST(StudentsDbTests, DeleteFromEmpty) {
    std::vector<Student> db;
    std::istringstream in("");
    std::ostringstream out;
    deleteStudent(db, in, out);
    // Размер не меняется, вывелось сообщение
    ASSERT_TRUE(db.empty());
    EXPECT_NE(out.str().find("пусто"), std::string::npos);
}

// 6) Юнит: проверка форматирования вывода одного студента
TEST(StudentsDbTests, DisplayOneStudentFormat) {
    std::vector<Student> db = {{"Kate", 22, "IT", 4.9}};
    std::ostringstream out;
    displayStudents(db, out);
    std::string s = out.str();
    EXPECT_NE(s.find("#0"), std::string::npos);
    EXPECT_NE(s.find("Имя: Kate"), std::string::npos);
    EXPECT_NE(s.find("Возраст: 22"), std::string::npos);
    EXPECT_NE(s.find("Специальность: IT"), std::string::npos);
    EXPECT_NE(s.find("Средний балл: 4.9"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


