project(superstring)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall)

find_package(OpenMP)
add_definitions(${OpenMP_CXX_FLAGS})

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)


set(SOURCES
  src/instance.cpp
  src/random.cpp 
  src/individual.cpp
  src/composition.cpp
  src/ox.cpp
  src/ux.cpp
  src/pmx.cpp
  src/mutation.cpp
  src/population.cpp
  src/algorithm_state.cpp
  src/termination.cpp
  src/solver.cpp
  src/adaptation.cpp
  src/stat_utils.cpp
  src/parent_selector.cpp
  src/crossover.cpp
  src/replacement.cpp
  src/immigration.cpp
)


set(TESTS
  test/random.cpp
  test/individual.cpp
  test/ux.cpp
  test/ox.cpp
  test/pmx.cpp
  test/parent_selector.cpp
  test/composition.cpp
  test/population.cpp
  test/adaptation.cpp
  test/best_of_replacement.cpp
  test/crossover.cpp
  test/replacement.cpp
)


add_library(superstringlib ${SOURCES})
target_link_libraries(superstringlib gomp)

add_executable(ut ${TESTS})
target_link_libraries(ut superstringlib ${GTEST_BOTH_LIBRARIES})

#add_custom_target(
#  copy_benchmarks ALL
#  COMMAND cp  ${CMAKE_CURRENT_SOURCE_DIR}/../benchmark/* ${CMAKE_CURRENT_BINARY_DIR}/)