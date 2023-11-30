cmake_minimum_required(VERSION 3.15)
project(brasilapi-cc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_executable(test_brasilapi_client src/Examples/mainExample.cc)
target_include_directories(test_brasilapi_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(test_brasilapi_client PRIVATE brasilapi)

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
