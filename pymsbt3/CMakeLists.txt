cmake_minimum_required(VERSION 3.10)
project(pymsbt3 VERSION 0.1.0)

set (PYBIND11_PYTHON_VERSION 3.7)

add_subdirectory(./src/include/pybind11)
pybind11_add_module(${PROJECT_NAME} ./src/wrapper.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PYBIND11_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC msbt)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
