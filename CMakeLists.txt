cmake_minimum_required(VERSION 3.16.3)

project(App)

SET(wxWidgets_ROOT_DIR mnt/c/wxWidgets-3.1.5)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)

include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} appli.cpp)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

