# QuadCopter Flight Controller, Arduino-based

This repository contains an Arduino-based flight controller project for a quadcopter using an MPU6050 IMU for yaw, pitch and roll measurements and a barometer for height measurements.
The project is currently under development and the quadcopter flies, although not yet reliably.

## Project overview

The quadcopter receives sensor data from an MPU6050 IMU, which is a 6-axis gyroscope + accelerometer.
It receives altitude data from a barometer.
It computes control outputs from yaw, pitch, roll and altitude acceleration commands using PID controllers.

## Current status

* MPU6050 data can be read and used.
* Motors can be controlled.
* Serial communication for bluetooth module for remote commands.
* PID controller structure is implemented.

### Next
* PID controllers require tuning.
* Barometer needs implementation.
* Quadcopter should be able to hang still in the air.

## Contributions
Some libraries have been developed.
Each library contains examples that can be used for testing the library.
The examples can be imported in the Arduino IDE.
Examples are located in the `libraries/<library_name>/examples/` directory.

### Developed libraries
* Geometry: helper functions for geometry
* IMPU: reading and processing the MPU6050 IMU sensor
* IMotor: motor control
* IQuadController: main flight controller of the quadcopter
* IRemoteController: remote control abstraction. Currently contains serial implementation for bluetooth module
* PID: pid controller implementation

### Imported third-party libraries
* I2Cdev
* MPU6050

## Using the project
Feel free to use the code distributed for your own project.
