cmake_minimum_required(VERSION 3.5)

project(chattiprojekti VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED)

# Rename the target to chattiprojekti
add_executable(chattiprojekti mainwindow.cpp chatserver.cpp)

# Other configurations and dependencies
# ...

# Link against the required Qt libraries
target_link_libraries(chattiprojekti PRIVATE
    Qt6::Widgets
    Qt6::Network
)

set_target_properties(chattiprojekti PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS chattiprojekti
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
