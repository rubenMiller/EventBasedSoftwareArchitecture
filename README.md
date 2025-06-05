# EventBasedSoftwareArchitecture

Repository for the class Software Architecture.

## Structure

The structure of the repository:

```bash
.
├── examples
│   ├── local-minimal-example
│   └── mqtt-minimal-example
├── project
│   ├── arduino
│   └── server
├── README.md
└── requirements.txt
```

The main logic is contaied in the 'project' folder, sorted by files for the server and for the arduino. In 'examples' minmal examples are contained, which where used for testing.


```bash
project
├── arduino
│   ├── examples
│   │   ├── arduino_main.ino
│   │   ├── set-motor.ino
│   │   ├── status.ino
│   │   └── ultrasonic_sensor
│   └── main
│       ├── main.ino
│       ├── StatusPublisher.cpp
│       ├── StatusPublisher.h
│       ├── StepMotor.cpp
│       ├── StepMotor.h
│       ├── UltrasonicSensor.cpp
│       └── UltrasonicSensor.h
└── server
    ├── mosquitto.conf
    └── start_mosquitto_server.sh
```

In the project folder, most files are for the arduino, because most of the logic is executed on there. The 'main' folder contains the production logic and the 'examples' only contains files that where used while developing. In the 'server' folder, only a copy of the used config is stored and the bash file to start the server. The config file needs to be saved at
```bash
/etc/mosquitto/conf.d/default.conf
```