include_directories(${PROJECT_SOURCE_DIR}/include)
add_compile_options(-Wall -Wextra -fsanitize=address)
add_link_options(-fsanitize=address)

add_library(simulation simulation.cpp)

add_library(simple_infection simple_infection.cpp)

add_library(incubation_infection incubation_infection.cpp)

add_library(motion motion.cpp)

add_library(population population.cpp)

add_library(display display.cpp)

add_library(plot plot.cpp)
target_include_directories(plot PRIVATE ${ROOT_INCLUDE_DIR})

add_executable(SIR_simulation main.cpp)
set_target_properties(SIR_simulation PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
target_include_directories(SIR_simulation PRIVATE ${ROOT_INCLUDE_DIR})
target_link_libraries(SIR_simulation simulation motion incubation_infection simple_infection population display plot)
target_link_libraries(SIR_simulation sfml-graphics sfml-window sfml-system)
target_link_libraries(SIR_simulation ROOT::MathCore ROOT::Hist ROOT::Gui)
