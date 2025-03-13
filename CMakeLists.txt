cmake_minimum_required(VERSION 3.14)

project(netcam LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Git integration
find_package(Git REQUIRED)

# Ensure Git commands are executed before configure_file
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE GIT_BRANCH_RESULT
)

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE GIT_COMMIT_HASH_RESULT
)

execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=short
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_DATE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE GIT_COMMIT_DATE_RESULT
)

# Check if Git commands succeeded
if(NOT GIT_BRANCH_RESULT EQUAL 0)
    set(GIT_BRANCH "unknown")
endif()

if(NOT GIT_COMMIT_HASH_RESULT EQUAL 0)
    set(GIT_COMMIT_HASH "unknown")
endif()

if(NOT GIT_COMMIT_DATE_RESULT EQUAL 0)
    set(GIT_COMMIT_DATE "unknown")
endif()

# Generate git_version.h
configure_file(
    ${CMAKE_SOURCE_DIR}/includes/git_version.h.in
    ${CMAKE_BINARY_DIR}/git_version.h
    @ONLY
)

# Include the generated directory
include_directories(${CMAKE_BINARY_DIR})

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)
find_package(OpenCV REQUIRED)

# Add source files
set(
    SOURCES
    main.cpp
)
include_directories(${PROJECT_SOURCE_DIR}/includes)
# Add executable
add_executable(netcam ${SOURCES})

# Link libraries
target_link_libraries(netcam
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    ${OpenCV_LIBS}
)

include(GNUInstallDirs)
install(TARGETS netcam
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)