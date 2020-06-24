cmake_minimum_required(VERSION 3.16)

project(sir_simulation CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML COMPONENTS graphics window system REQUIRED)
find_package(ROOT COMPONENTS Hist MathCore Gui REQUIRED)

include(${ROOT_USE_FILE})
add_subdirectory(src)
add_subdirectory(tests)
