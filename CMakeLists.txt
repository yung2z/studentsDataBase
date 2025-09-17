cmake_minimum_required(VERSION 3.16)
project(studentsDataBase CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека с логикой
add_library(studentslib
    students.cpp
)
target_include_directories(studentslib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Приложение
add_executable(studentsDb
    main.cpp
)
target_link_libraries(studentsDb PRIVATE studentslib)

# Тесты с GoogleTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Для MSVC, чтобы не смешивать рантаймы (безопасно и на Linux)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(tests
    tests.cpp
)
target_link_libraries(tests PRIVATE studentslib GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)


