# SIT_CSC2003_ES_AY2022

Embedded Systems and Sensor Programming. Based on a specific microcontroller and a set of real-world applications and examples, students will learn the functionality of microcontrollers and their integration within an embedded system.

## Project

### msp432

The current files can enable uart connection to m5stickc plus. Only the `ground`, `G32`, and `G33` pins are required to connect to `ground`, `P3.2`, and `P3.3` respectively. `TimerA` is created to send data to m5stickc plus at ~1s interval.

### m5stickc plus

`uart.m5f` can be loaded and viewed on https://flow.m5stack.com/. It create MQTT client that publish `msp432` topic to a local MQTT broker and a uart connection to read data from msp432.
