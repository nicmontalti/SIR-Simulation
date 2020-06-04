include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(simulation simulation.cpp)
target_compile_options(simulation PRIVATE -Wall -Wextra -fsanitize=address)

add_library(simple_infection simple_infection.cpp)
target_compile_options(simple_infection PRIVATE -Wall -Wextra -fsanitize=address)

add_library(incubation_infection incubation_infection.cpp)
target_compile_options(incubation_infection PRIVATE -Wall -Wextra -fsanitize=address)

add_library(motion motion.cpp)
target_compile_options(motion PRIVATE -Wall -Wextra -fsanitize=address)

add_library(SIR_population SIR_population.cpp)
target_compile_options(SIR_population PRIVATE -Wall -Wextra -fsanitize=address)

add_library(display display.cpp)
target_compile_options(display PRIVATE -Wall -Wextra -fsanitize=address)

add_library(simulation_plot simulation_plot.cpp)
target_include_directories(simulation_plot PRIVATE ${ROOT_INCLUDE_DIR})

add_executable(SIR_simulation main.cpp)
set_target_properties(SIR_simulation PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_include_directories(SIR_simulation PRIVATE ${ROOT_INCLUDE_DIR})
target_link_options(SIR_simulation PRIVATE -fsanitize=address)
target_link_libraries(SIR_simulation simulation motion simple_infection SIR_population display)
target_link_libraries(SIR_simulation sfml-graphics sfml-window sfml-system)
target_link_libraries(SIR_simulation ROOT::Core m dl ROOT::Hist ROOT::Gui)
