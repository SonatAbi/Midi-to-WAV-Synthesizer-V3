cmake_minimum_required(VERSION 3.5)
project(M2 CXX)

# prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()
  
# require a C++11 compiler and use it for all targets
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# configure Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Widgets Test REQUIRED)

set(SOURCE
  event.hpp event.cpp
  track.hpp track.cpp
  midi.hpp midi.cpp
  signal.hpp signal.cpp
  wav.hpp wav.cpp
  interactive_instrument.hpp interactive_instrument.cpp
  qinstrument.hpp qinstrument.cpp)


add_executable(qinstrument main.cpp ${SOURCE})
target_link_libraries(qinstrument Qt5::Widgets)

add_executable(test_qinstrument test_qinstrument.cpp ${SOURCE})
target_link_libraries(test_qinstrument Qt5::Widgets Qt5::Test)

# setup testing
set(TEST_FILE_DIR "${CMAKE_SOURCE_DIR}/tests")

configure_file(${CMAKE_SOURCE_DIR}/test_config.hpp.in 
  ${CMAKE_BINARY_DIR}/test_config.hpp)

include_directories(${CMAKE_BINARY_DIR})

enable_testing()

add_test(00_Install ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install)
add_test(test_qinstrument test_qinstrument)

add_subdirectory(tests)