# ara-diag-monitor

A **diagnostic monitor** is a routine running inside an **AA** entity determining the proper functionality of a component.

In general **diagnostic monitors** are independent from the **DM**. Once the **ECU** is started and initialized they are permanently monitoring a part of the system and reporting the state to the **DM**. There are use cases, where it might not be required to continue to monitor the system part and the monitor could stop its task until a certain situation arises.

The *ara::diag::Monitor* interface is used by the **DM** to provide applications the ability to report monitor states to the **DM**.

# Monitor Project Tests

This project includes unit, mock, and integration tests for the `Monitor` class and its interactions with the `Event` class. Below are the descriptions of each test type and steps to set up and run the tests.

## Test Descriptions

### Unit Tests (monitor_unit_test.cpp)
Unit tests focus on testing individual functions or methods in isolation. They ensure that each function behaves as expected under various conditions. The unit tests for the `Monitor` class include:

### Mock Tests (monitor_mock_test.cpp)
Mock tests use Google Mock to simulate interactions with dependencies and verify the behavior of the `Monitor` class in isolation. The mock tests for the `Monitor` class include:

### Integration Tests (monitor_integration_test.cpp)
Integration tests verify the interactions between multiple components to ensure they work together correctly. The integration tests for the `Monitor` and `Event` classes include:

### Directly Using g++ (for simplicity)

1. **Compile and link the tests**:
    ```sh
    g++ -std=c++11 -I/path/to/gtest/include -I/path/to/gmock/include -L/path/to/gtest/lib -lgtest -lgtest_main -lgmock -lgmock_main tests/monitor_unit_test.cpp -o monitor_unit_test
    g++ -std=c++11 -I/path/to/gtest/include -I/path/to/gmock/include -L/path/to/gtest/lib -lgtest -lgtest_main -lgmock -lgmock_main tests/monitor_mock_test.cpp -o monitor_mock_test
    g++ -std=c++11 -I/path/to/gtest/include -I/path/to/gmock/include -L/path/to/gtest/lib -lgtest -lgtest_main -lgmock -lgmock_main tests/monitor_integration_test.cpp -o monitor_integration_test
    ```

2. **Run the tests**:
    ```sh
    ./monitor_unit_test
    ./monitor_mock_test
    ./monitor_integration_test
    ```