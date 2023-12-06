cmake_minimum_required(VERSION 3.15)
project(brasilapi-cc VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Drogon REQUIRED)
message(STATUS "Drogon include directories: ${DROGON_INCLUDE_DIRS}")

# Define source files
file(GLOB_RECURSE PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

# Adicionando a biblioteca brasilapi
add_library(brasilapi ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_include_directories(brasilapi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(brasilapi PUBLIC Drogon::Drogon)

# Adicionando executável
add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE brasilapi)

# Test
set(TEST_SOURCES
    src/Tests/Services/BanksTest.cc
    src/Tests/main-test.cc 
)
add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)  
target_link_libraries(tests PRIVATE brasilapi GTest::GTest GTest::Main)


# Instalação e exportação
install(TARGETS brasilapi
    EXPORT BrasilAPITargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY src/Client/
    DESTINATION include/BrasilAPI
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT BrasilAPITargets
    FILE BrasilAPITargets.cmake
    DESTINATION lib/cmake/BrasilAPI
)