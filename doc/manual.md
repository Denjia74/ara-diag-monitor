## User Manual

### Overview
Цей посібник містить покрокові інструкції з розгортання та тестування програми `ara-diag-monitor`. Проєкт включає в себе діагностичний моніторинг та тести для перевірки функціональності. Репозиторій коду містить наступне:

- Вихідний код
- Unit тести та інтеграційні тести за класами

### Prerequisites

- **Operating System**: Linux-based OS distribution.
- **Git**: Для встановлення та клонування репозиторію.
- **C++ Compiler**: Компілятор, що підтримує C++14 або пізнішу версію.
- **GoogleTest**: Тестовий фреймворк C++ від Google.
- **GoogleMock**: Тестовий фреймворк моків (mock) C++ від Google.
- **CMake** 

### Cloning the Repository

1. Відкрити термінал
2. Клонувати репозиторій за допомогою наступної команди:
   ```bash
   git clone https://github.com/Denjia74/ara-diag-monitor.git
   ```

### Building the Project

1. **Create a Build Directory**:
   ```bash
   mkdir build
   cd build
   ```

2. **Run CMake to Generate Build Files**:
   ```bash
   cmake ..
   ```

3. **Build the Project**:
   ```bash
   make
   ```
### Building and Running the Tests

#### Using `g++` (for simplicity)

1. **Compile and link the tests**:
    ```bash
    g++ -std=c++14 -I/path/to/gtest/include -I/path/to/gmock/include -L/path/to/gtest/lib -lgtest -lgtest_main -lgmock -lgmock_main tests/monitor_unit_test.cpp -o monitor_unit_test
    g++ -std=c++14 -I/path/to/gtest/include -I/path/to/gmock/include -L/path/to/gtest/lib -lgtest -lgtest_main -lgmock -lgmock_main tests/monitor_mock_test.cpp -o monitor_mock_test
    g++ -std=c++14 -I/path/to/gtest/include -I/path/to/gmock/include -L/path/to/gtest/lib -lgtest -lgtest_main -lgmock -lgmock_main tests/monitor_integration_test.cpp -o monitor_integration_test
    ```

2. **Run the tests**:
    ```bash
    ./monitor_unit_test
    ./monitor_mock_test
    ./monitor_integration_test
    ```

### Understanding the Tests

#### Integration Tests
- **File**: `monitor_integration_test.cpp`
- **Purpose**: Перевіряє взаємодію між класами `Monitor` та `Event`.
- **Example**:
  ```cpp
  // Test that verifies Monitor reports a 'kPassed' action and checks Event's fault detection counter
  TEST_F(MonitorEventIntegrationTest, MonitorEventInteractionTest) {
      monitor.ReportMonitorAction(MonitorAction::kPassed);
      EXPECT_EQ(1, event.GetFaultDetectionCounter());
  }
  ```

#### Mock Tests
- **File**: `monitor_mock_test.cpp`
- **Purpose**: Використовує GoogleMock для перевірки взаємодії з класом `Event`.
- **Example**:
  ```cpp
  // Test that verifies the AttachEvent function in Monitor class
  TEST_F(MonitorTest, AttachEventTest) {
      Monitor monitor;
      monitor.AttachEvent(mockEvent.get());
      EXPECT_EQ(mockEvent.get(), monitor.GetEvent());
  }
  ```

#### Unit Tests
- **File**: `monitor_unit_test.cpp`
- **Purpose**: Перевіряє окремі функціональні можливості класу `Monitor`.
- **Example**:
  ```cpp
  // Unit test for Monitor class with CounterBased debouncer, testing the Offer and StopOffer methods
  TEST(MonitorTest, CounterBasedOfferScenario) {
      core::InstanceSpecifier _specifier("Instance0");
      InitMonitorReason _currentReason{InitMonitorReason::kClear};
      auto _initMonitor = [&](InitMonitorReason newReason) {
          _currentReason = newReason;
      };
      CounterBased _defaultValues;

      Monitor _monitor(_specifier, _initMonitor, _defaultValues);

      core::Result<void> _result{_monitor.Offer()};
      EXPECT_TRUE(_result.HasValue());
      EXPECT_EQ(InitMonitorReason::kReenabled, _currentReason);

      core::Result<void> _newResult{_monitor.Offer()};
      EXPECT_FALSE(_newResult.HasValue());

      _monitor.StopOffer();
      EXPECT_EQ(InitMonitorReason::kDisabled, _currentReason);
  }
  ```
### Clean Up

Видалити зкомпільовані файли назовсім:
```bash
rm -rf build
```

#### Using `CMake` (for more complex projects)

1. **Створення папки build**:
   ```bash
   mkdir build
   cd build
   ```

2. **Запуск CMake для генерації build файлів**:
   ```bash
   cmake ..
   ```

3. **Компіляція проєкту**:
   ```bash
   cmake --build .
   ```

4. **Запуск тестів**:
   ```bash
   ctest
   ```

### Conclusion

Виконання цих кроків дозволить розгорнути і протестувати застосунок `ara-diag-monitor`. Переконайтеся, що всі залежності встановлено правильно і проєкт зібрано без помилок. Запуск тестів допоможе перевірити цілісність і функціональність компонентів програми.