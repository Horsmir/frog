project(frog)
cmake_minimum_required(VERSION 2.6)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 1)
set(FROG_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
add_definitions(-DFROG_VERSION=\"${FROG_VERSION}\")
message(STATUS "")
message(STATUS "Frog version: ${FROG_VERSION}")
message(STATUS "")

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(frog_SRCS gamemanager.cpp cardgraphicsscene.cpp pilepack.cpp pilefault.cpp pilebase.cpp pilereserve.cpp pile.cpp cardsvgitem.cpp frog.cpp main.cpp)
set(frog_UIS mainwindow.ui)
qt4_automoc(${frog_SRCS})
QT4_WRAP_UI(UI_HEADERS ${frog_UIS})

add_executable(frog ${frog_SRCS} ${UI_HEADERS})
target_link_libraries(frog ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY})
install(TARGETS frog RUNTIME DESTINATION bin)
