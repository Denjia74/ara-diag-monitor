cmake_minimum_required(VERSION "3.15")
project(ara-diag-monitor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Source files
set(SOURCE_FILES
    src/monitor.cpp
)

set(TEST_FILES
    tests/monitor_unit_test.cpp
    tests/monitor_mock_test.cpp
    tests/monitor_integration_test.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(ara_diag_monitor STATIC ${SOURCE_FILES})

add_executable(runTests ${TEST_FILES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ara_diag_monitor)

enable_testing()
add_test(NAME runTests COMMAND runTests)
