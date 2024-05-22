
## Сomponent Diagram




    @startuml
    componentDiagram
    ' Компоненти
    component "Моніторинг" as Monitoring
	component "Діагностика" as Diagnostics
	component "Дебаунсинг" as Debouncing
	component "Системні Компоненти" as SystemComponents
	component "Події" as Events
	component "Зовнішня Система" as ExternalSystem

	' Зв'язки між компонентами
	Monitoring --> Debouncing : Використовує
	Monitoring --> Events : Прикріплює
	Monitoring --> Diagnostics : Взаємодіє
	Debouncing --> SystemComponents : Залежить
	Diagnostics --> SystemComponents : Залежить
	Diagnostics --> ExternalSystem : Обмін даними

	' Інтерфейси
	interface "Діагностичний Інтерфейс" as DiagnosticInterface
	interface "Системний Інтерфейс" as SystemInterface

	' Взаємодія з інтерфейсами
	Monitoring -up- DiagnosticInterface : Використовує
	SystemComponents -down- SystemInterface : Взаємодіє
	@enduml


![](https://raw.githubusercontent.com/Nagorniii/photo/1d8daf51804e9880ec21f2ed930fde3c7e098dfe/1.png)
