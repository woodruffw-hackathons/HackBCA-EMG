HackBCA - EMG
=============

## What is it?
A collection of programs (written in Arduino Wiring and Processing) used to interface with the Olimex EMG/EKG shield.

The actual data writer (WriteSensorData.ino) is based upon the example code provided by Olimex.

The three Processing programs (GraphSensorData.pde, PlaySensorData.pde, and MuscleGame.pde) take that data (obtained from a serial terminal) and output it to the user in various ways.

PlaySensorData.pde depends upon Processing's Minim library for audio output.

## License
All code is licensed under the MIT License.