
## Сlass Diagram




  

  

	@startuml
	' Клас Monitor
	class Monitor {
	- const core::InstanceSpecifier &mSpecifier
	- std::function<void(InitMonitorReason)> mInitMonitor
	- bool mOffered
	- debouncing::Debouncer *mDebouncer
	- Event *mEvent
	~ Monitor(const core::InstanceSpecifier &, std::function<void(InitMonitorReason)>)
	~ Monitor(const core::InstanceSpecifier &, std::function<void(InitMonitorReason)>, CounterBased)
	~ Monitor(const core::InstanceSpecifier &, std::function<void(InitMonitorReason)>, TimeBased)
	+ void ReportMonitorAction(MonitorAction)
	+ void AttachEvent(Event *)
	+ core::Result<void> Offer()
	+ void StopOffer()
	~ void onEventStatusChanged(bool passed)
	}
	' Клас Event
	class Event {
	+ void SetFaultDetectionCounter(int8_t)
	+ void SetEventStatusBits(std::map<EventStatusBit, bool>)
	}
	' Класи Debouncer і його підкласи
	abstract class Debouncer {
	+ void ReportPassed()
	+ void ReportFailed()
	+ void Freeze()
	+ void Reset()
	}
	class CounterBasedDebouncer {
	- int mCounter
	+ CounterBasedDebouncer(std::function<void(bool)>)
	~ void ReportPassed()
	~ void ReportFailed()
	}
	class TimerBasedDebouncer {
	- std::chrono::milliseconds mDelay
	+ TimerBasedDebouncer(std::function<void(bool)>)
	~ void ReportPassed()
	~ void ReportFailed()
	}
	' Наслідування від Debouncer
	Debouncer <|-- CounterBasedDebouncer
	Debouncer <|-- TimerBasedDebouncer
	' Асоціації між класами
	Monitor "1" --> "1" Event
	Monitor "1" --> "1" Debouncer : mDebouncer
	@enduml


![](https://github.com/Nagorniii/photo/blob/main/2.png?raw=true)


-   **Клас** **Monitor**: Включає атрибути, методи та взаємозв'язки з іншими класами. Наприклад, **mSpecifier**, **mInitMonitor**, **mOffered**, **mDebouncer**, **mEvent** — атрибути, що визначають стан класу. Основні методи, такі як **ReportMonitorAction**, **AttachEvent**, **Offer**, **StopOffer**, описують функціональність цього класу.
-   **Клас** **Event**: Має методи для налаштування різних параметрів, таких як **SetFaultDetectionCounter** та **SetEventStatusBits**.
-   **Класи** **Debouncer** **та його підкласи**: **Debouncer** є абстрактним класом, з якого успадковують **CounterBasedDebouncer** та **TimerBasedDebouncer**. Вони мають основні методи для керування станами, такими як **ReportPassed**, **ReportFailed**, **Freeze**, та **Reset**.
-   **Наслідування**: Показує, що **CounterBasedDebouncer** та **TimerBasedDebouncer** успадковують від **Debouncer**.
-   **Асоціації**: Вказують, як класи взаємодіють один з одним. Наприклад, **Monitor** асоціюється з **Event** та **Debouncer**.
