cmake_minimum_required(VERSION 3.15)
project(ara-diag-monitor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Source files
set(SOURCE_FILES
    include/debouncer.cpp
    include/counter_based_debouncer.cpp
    include/diag_error_domain.cpp
    include/error_code.cpp
    include/event.cpp
    include/instance_specifier.cpp
    include/timer_based_debouncer.cpp
    src/monitor.cpp
)

set(HEADER_FILES
    include/counter_based_debouncer.h
    include/debouncer.h
    include/diag_error_domain.h
    include/error_code.h
    include/error_domain.h
    include/event.h
    include/instance_specifier.h
    include/optional.h
    include/result.h
    include/timer_based_debouncer.h
    src/monitor.h
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
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(ara_diag_monitor STATIC ${HEADER_FILES} ${SOURCE_FILES})

add_executable(runTests ${TEST_FILES})
# Link directly to gtest and gtest_main targets provided by FetchContent
target_link_libraries(runTests GTest::gtest GTest::gtest_main pthread ara_diag_monitor)

enable_testing()
add_test(NAME runTests COMMAND runTests)

