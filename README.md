# ara-diag-monitor

A **diagnostic monitor** is a routine running inside an **AA** entity determining the proper functionality of a component.

In general **diagnostic monitors** are independent from the **DM**. Once the **ECU** is started and initialized they are permanently monitoring a part of the system and reporting the state to the **DM**. There are use cases, where it might not be required to continue to monitor the system part and the monitor could stop its task until a certain situation arises.

The *ara::diag::Monitor* interface is used by the **DM** to provide applications the ability to report monitor states to the **DM**.

