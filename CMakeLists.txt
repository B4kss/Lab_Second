cmake_minimum_required(VERSION 3.10)
project(Lab_Second)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------
# Используем MDd для совместимости с gtest
# ------------------------
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# ------------------------
# Основная программа
# ------------------------
add_executable(program
    main.cpp
    functions.cpp
)

# ------------------------
# GoogleTest
# ------------------------
add_subdirectory(googletest)

# ------------------------
# Тесты
# ------------------------
include_directories(${PROJECT_SOURCE_DIR})

add_executable(runTests
    tests/test_functions.cpp
    functions.cpp
)

target_link_libraries(runTests
    gtest
    gtest_main
)

enable_testing()
add_test(NAME MyTests COMMAND runTests)
