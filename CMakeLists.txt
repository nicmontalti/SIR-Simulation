cmake_minimum_required(VERSION 3.17.1)

project(sir_simulation CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(run_infection_tests simple_infection.cpp infection.test.cpp SIR_population.cpp run_tests.cpp)
add_test(NAME infection_tests COMMAND run_infection_tests)
 
add_executable(run_motion_tests motion.cpp motion.test.cpp SIR_population.cpp)
target_compile_options(run_motion_tests PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(run_motion_tests PRIVATE -fsanitize=address)
target_link_libraries(run_motion_tests sfml-graphics sfml-window sfml-system)

add_executable(run_simulation_tests simulation.cpp simulation.test.cpp simple_infection.cpp motion.cpp SIR_population.cpp run_tests.cpp)
add_test(NAME simulation_tests COMMAND run_simulation_tests)

add_executable(sir_simulation simulation.cpp simple_infection.cpp motion.cpp SIR_population.cpp main.cpp)
target_compile_options(sir_simulation PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(sir_simulation PRIVATE -fsanitize=address)
target_link_libraries(sir_simulation sfml-graphics sfml-window sfml-system)

add_executable(run_display_tests simulation.cpp simple_infection.cpp motion.cpp SIR_population.cpp display.cpp display.test.cpp)
target_compile_options(run_display_tests PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(run_display_tests PRIVATE -fsanitize=address)
target_link_libraries(run_display_tests sfml-graphics sfml-window sfml-system)

add_executable(run_incubation_infection_tests simulation.cpp incubation_infection.cpp motion.cpp SIR_population.cpp display.cpp incubation_infection.test.cpp)
target_compile_options(run_incubation_infection_tests PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(run_incubation_infection_tests PRIVATE -fsanitize=address)
target_link_libraries(run_incubation_infection_tests sfml-graphics sfml-window sfml-system)
