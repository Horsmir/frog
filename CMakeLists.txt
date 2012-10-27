project(frog)
cmake_minimum_required(VERSION 2.6)

if (NOT CMAKE_BUILD_TYPE)
    set ( CMAKE_BUILD_TYPE Release )
endif (NOT CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE MATCHES [Dd]ebug)
    message(STATUS "Debug build")
    add_definitions(-DDEBUG)
else()
    message(STATUS "non-debug build")
    add_definitions(-DNDEBUG)
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

if (NOT CMAKE_INSTALL_PREFIX)
	set(CMAKE_INSTALL_PREFIX /usr)
endif(NOT CMAKE_INSTALL_PREFIX)
message(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")

set(MAJOR_VERSION 0)
set(MINOR_VERSION 2)
set(PATCH_VERSION 2)
set(FROG_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
add_definitions(-DFROG_VERSION=\"${FROG_VERSION}\")
message(STATUS "")
message(STATUS "Frog version: ${FROG_VERSION}")
message(STATUS "")

find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

configure_file (
  "${PROJECT_SOURCE_DIR}/frogconfigure.h.in"
  "${PROJECT_BINARY_DIR}/frogconfigure.h"
  )
configure_file (
  "${PROJECT_SOURCE_DIR}/README.in"
  "${PROJECT_SOURCE_DIR}/README"
  )
  
set(frog_SRCS gamemanager.cpp cardgraphicsscene.cpp pilepack.cpp pilefault.cpp pilebase.cpp pilereserve.cpp pile.cpp cardsvgitem.cpp frog.cpp main.cpp)
set(helpbrowser_SRCS help_browser/helpbrowser.cpp)
set(frog_UIS mainwindow.ui help_browser/helpform.ui)
set(frog_QRCS frog.qrc)

qt4_automoc(${frog_SRCS} ${helpbrowser_SRCS})
QT4_WRAP_UI(UI_HEADERS ${frog_UIS})
QT4_ADD_RESOURCES(QRC_SOURCES ${frog_QRCS})

add_executable(frog ${frog_SRCS} ${helpbrowser_SRCS} ${UI_HEADERS} ${QRC_SOURCES})
target_link_libraries(frog ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTSVG_LIBRARY})

install(TARGETS frog RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES frog.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES icons/frog.svg DESTINATION ${CMAKE_INSTALL_PREFIX}/share/pixmaps)
install(DIRECTORY doc/ DESTINATION ${CMAKE_INSTALL_PREFIX}/share/doc/frog)
install(DIRECTORY images DESTINATION ${CMAKE_INSTALL_PREFIX}/share/frog)

########## Add make dist target ################
set(CPACK_PACKAGE_VERSION "${FROG_VERSION}")
set(CPACK_SOURCE_GENERATOR "TBZ2")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "frog-${FROG_VERSION}")
set(CPACK_IGNORE_FILES "/CVS/;/\\\\.git\;/\\\\.svn/;\\\\.swp$;\\\\.#;/#;\\\\.tar.gz$;/CMakeFiles/;CMakeCache.txt;build/;dist/;exp/;.*~")
set(CPACK_SOURCE_IGNORE_FILES ${CPACK_IGNORE_FILES})
include(CPack)
# simulate autotools' "make dist"
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
