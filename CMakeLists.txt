cmake_minimum_required(VERSION 3.15)
project(brasil-api)

find_package(Drogon REQUIRED)

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} Drogon::Drogon)