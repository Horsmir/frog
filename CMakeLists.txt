project(frog)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(frog_SRCS frog.cpp main.cpp)
qt4_automoc(${frog_SRCS})
add_executable(frog ${frog_SRCS})
target_link_libraries(frog ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS frog RUNTIME DESTINATION bin)
