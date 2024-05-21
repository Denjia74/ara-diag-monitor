---

# Software Design Document

### Title: ara-diag-monitor
### Author: Dovzhenko Denys
### Version: 0.1

---

## Introduction

### Purpose
У цьому документі надається детальний опис `ara-diag-monitor`, програми діагностичного моніторингу в рамках адаптивного додатку AUTOSAR (АА). Діагностичний монітор відповідає за визначення функціональності різних компонентів системи та звітування про неї менеджеру діагностики (DM). 

### References {#refs}
- AUTOSAR Adaptive Platform Release R23-11
- AUTOSAR_AP_SWS_Diagnostics
- ISO 26262: Functional Safety for Road Vehicles

## Terminology {#term}

### Definitions

| Term                     | Definition                                                          |
|--------------------------|---------------------------------------------------------------------|
| Diagnostic Monitor (DM)  | Підпрограма, яка перевіряє працездатність компонентів системи.      |
| ECU                      | Electronic Control Unit, основна частина автомобільної електроніки. |
| ara::diag::Monitor       | Інтерфейс для звітування про стан моніторів до DM.                  |
| Debouncer                | Механізм фільтрації хибних змін у стані контрольованої події        |

### Abbreviations

| Abbreviation | Description                                      |
|--------------|--------------------------------------------------|
| DM           | Diagnostic Monitor                               |
| ECU          | Electronic Control Unit                          |
| AA           | Adaptive Application                             |
| AUTOSAR      | Automotive Open System Architecture              |

## System Overview {#so}

### Features
- Постійний моніторинг компонентів системи.
- Звітування про стан компонентів до ДМ.
- Налаштовування процедури моніторингу відповідно до системних вимог.

### System Components
- **Diagnostic Monitor Module**: Реалізує процедури моніторингу.
- **Diagnostic Manager (DM)**: Отримує та оброблює результати з Diagnostic Monitor.
- **System Components**: Різні частини ECU, що контролюються (наприклад, датчики, виконавчі механізми).

### Communication between Subsystems
- Монітор діагностики використовує інтерфейс `ara::diag::Monitor` для передачі станів до DM.
- DM агрегує ці стани і виконує необхідні діагностичні дії або звіти.

### System Characteristics
- **Надійність**: Забезпечує безперервний і точний моніторинг компонентів.
- **Масштабованість**: Дозволяє налаштування моніторингу додаткових компонентів за потреби.
- **Продуктивність**: Мінімальний вплив на продуктивність ECU при забезпеченні своєчасних оновлень.

### Input/Output
- **Input**: Сигнали та стани від різних компонентів системи.
- **Output**: Звіти про стан діагностики надсилаються до DM.

### Software Performance {#perf}

#### Stand Description
Програмне забезпечення працює на адаптивній платформі AUTOSAR, яка забезпечує необхідне середовище виконання та сервіси.

#### Metrics

| Type                 | Value                                           |
|----------------------|-------------------------------------------------|
| Monitoring Frequency | 10 Hz                                           |
| Latency              | < 1 ms for state reporting                      |
| Resource Utilization | CPU: < 5%, Memory: < 1 MB                       |

#### Charts

### Graphical User Interface

## Sequence Diagrams {#seq}

## Data Structures {#dd}

### Enums

#### InitMonitorReason
```cpp
enum class InitMonitorReason : uint32_t {
    kClear = 0x00,     ///< Event was cleared
    kRestart = 0x01,   ///< Operation cycle of the event was restarted
    kReenabled = 0x02, ///< Enable conditions (if set) are fulfilled
    kDisabled = 0x03   ///< Enable conditions (if set) are no longer fulfilled
};
```
- **Description**: Причини для повторної ініціалізації Monitor.

#### MonitorAction
```cpp
enum class MonitorAction : uint32_t {
    kPassed = 0x00,              ///< Monitoring passed
    kFailed = 0x01,              ///< Monitoring failed
    kPrepassed = 0x02,           ///< Monitoring pre-passed
    kPrefailed = 0x03,           ///< Monitoring pre-failed
    kFdcThresholdReached = 0x04, ///< Fault Detection Counter (FDC) threshold has been reached
    kResetTestFailed = 0x05,     ///< Reset TestFailed bit in UDS DTC status
    kFreezeDebouncing = 0x06,    ///< Freeze the internal debouncing
    kResetDebouncing = 0x07      ///< Reset the internal debouncing
};
```
- **Description**: Дії, що можуть бути сповіщені DM-ом.

### ara::diag::Monitor Class

#### Private Members
- `const core::InstanceSpecifier &mSpecifier`: Вказує екземпляр, якому належить монітор.
- `const std::function<void(InitMonitorReason)> mInitMonitor`: Зворотний виклик для переініціалізації монітора.
- `bool mOffered`: Показує, чи пропонується монітор на даний момент для нових запитів.
- `debouncing::Debouncer *mDebouncer`: Вказівник на Debouncer, що використовується монітором.
- `Event *mEvent`: Вказівник на подію, пов'язану з монітором.

#### Constructors

- **Monitor**
    ```cpp
    Monitor(
        const core::InstanceSpecifier &specifier,
        std::function<void(InitMonitorReason)> initMonitor);
    ```
    - **Description**: Створює об'єкт Monitor без Debouncer-а.

- **Monitor with Counter-Based Debouncing**
    ```cpp
    Monitor(
        const core::InstanceSpecifier &specifier,
        std::function<void(InitMonitorReason)> initMonitor,
        CounterBased defaultValues);
    ```
    - **Description**: Створює об'єкт Monitor зі CounterBasedDebouncer.
    - **Behavior**: Ініціалізує `CounterBasedDebouncer` з наданими значеннями зворотного виклику та значеннями за замовчуванням.

- **Monitor with Time-Based Debouncing**
    ```cpp
    Monitor(
        const core::InstanceSpecifier &specifier,
        std::function<void(InitMonitorReason)> initMonitor,
        TimeBased defaultValues);
    ```
    - **Description**: Створює об'єкт Monitor на основі TimerBasedDebouncer.
    - **Behavior**: Ініціалізує `TimerBasedDebouncer` з наданими значеннями зворотного виклику та значеннями за замовчуванням.

#### Destructor
```cpp
~Monitor() noexcept;
```
- **Description**: Деструктор для класу Monitor.
- **Behavior**: Вивільняє використані ресурси.

#### Public Methods

- **ReportMonitorAction**
    ```cpp
    void ReportMonitorAction(MonitorAction action);
    ```
    - **Description**: Повідомляє про дію монітора.
    - **Parameters**: `action` - остання дія DM-а.
    - **Behavior**: Залежно від дії, взаємодіє з Debouncer або Event. Викликає `std::invalid_argument`, якщо дія не підтримується.

- **AttachEvent**
    ```cpp
    void AttachEvent(Event *event);
    ```
    - **Description**: Приєднує подію до об'єкта Monitor.
    - **Parameters**: `event` - вказівник на подію, яку потрібно приєднати.
    - **Behavior**: Призначає подію на монітор для оновлення статусу.

- **Offer**
    ```cpp
    core::Result<void> Offer();
    ```
    - **Description**: Починає пропонувати обробку запитів на моніторинг.
    - **Returns**: Результат помилки, якщо обробник вже було запропоновано.
    - **Behavior**: Встановлює `mOffered` у true та викликає `mInitMonitor` з `InitMonitorReason::kReenabled`.

- **StopOffer**
    ```cpp
    void StopOffer();
    ```
    - **Description**: Зупиняє пропонувати обробку запитів на моніторинг.
    - **Behavior**: Встановлює `mOffered` у false та викликає `mInitMonitor` з `InitMonitorReason::kDisabled`.

#### Private Methods

- **onEventStatusChanged**
    ```cpp
    void onEventStatusChanged(bool passed);
    ```
    - **Description**: Обробляє зміну статусу події.
    - **Parameters**: `passed` - boolean, який вказує, чи відбулася подія, чи ні.
    - **Behavior**: Оновлює біти `FaultDetectionCounter` та біти стану події на основі параметра `passed`.

---

