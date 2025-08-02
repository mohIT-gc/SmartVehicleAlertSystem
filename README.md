# Smart Vehicle Proximity Alert System

[cite_start]This is a research paper on the design and evaluation of a Smart Vehicle Alert and Monitoring System (SVAMS)[cite: 6, 16]. [cite_start]The system is an Internet of Things (IoT) architecture for real-time proximity intelligence in vehicles[cite: 1, 9].

## Abstract

[cite_start]SVAMS uses ESP32-C3 and Arduino Nano 33 IoT microcontrollers[cite: 6]. [cite_start]The system uses ultrasonic sensors for proximity detection, MQTT for data transfer, and OLED displays for immediate alerts[cite: 7]. [cite_start]It also pushes data to a cloud backend for logging and analysis[cite: 8]. [cite_start]The system is a modular IoT architecture with embedded edge computing and low-latency wireless communication[cite: 9]. [cite_start]Controlled tests showed sub-100 ms alert latency and reliable object detection between 5-100 cm[cite: 10]. [cite_start]This framework can be used for vehicle-to-driver and vehicle-to-cloud safety applications[cite: 11].

## I. Introduction

[cite_start]Due to increased urban vehicle density, there is a need for responsive, accurate, and cost-efficient embedded safety technologies[cite: 13]. [cite_start]While high-end cars have advanced driver-assistance systems (ADAS), these are often too expensive for most low-cost and legacy vehicles[cite: 14]. [cite_start]The SVAMS project, built on open-source hardware and software, addresses this gap[cite: 17]. [cite_start]It uses an Arduino Nano 33 IoT and an ESP32-C3 with HC-SR04 ultrasonic sensors to monitor distances to obstacles[cite: 18, 19]. [cite_start]Proximity data is sent over an MQTT broker, processed by the ESP32, and displayed on an OLED module[cite: 20]. [cite_start]All events are logged to a cloud backend via HTTP or MQTT integration with InfluxDB for long-term analysis[cite: 21].

## II. Use Case and Motivation

[cite_start]Urban driving conditions and the lack of sensors in older vehicles increase the risk of low-speed collisions[cite: 32, 36]. [cite_start]A 2023 report found that about 37% of non-fatal urban collisions happen at speeds below $30~km/h$[cite: 33, 35]. [cite_start]The adoption of ADAS is concentrated in the Global North, and aftermarket solutions are often isolated and not extensible[cite: 41, 46]. [cite_start]SVAMS fills this gap by using a ground-up IoT architecture with open-source components[cite: 52, 53]. [cite_start]The system is suitable for municipal fleets, ride-share vehicles, and last-mile delivery vans[cite: 57, 58, 59].

## III. System Architecture

[cite_start]SVAMS is a modular system with two microcontrollers: an Arduino Nano 33 IoT sensor node and an ESP32-C3 processing node[cite: 66, 67]. [cite_start]They communicate asynchronously via the MQTT protocol[cite: 68]. [cite_start]The sensor node publishes proximity data, which the processing node subscribes to[cite: 69, 70]. [cite_start]The processing node then renders the information on an OLED screen and sends it to an InfluxDB instance for logging[cite: 70]. [cite_start]The architecture is resilient, as local sensing and display continue even if the cloud disconnects[cite: 72, 73].

### A. Sensing Node Design
[cite_start]The Arduino Nano 33 IoT senses distance using an HC-SR04 ultrasonic sensor[cite: 76, 77]. [cite_start]The distance is calculated from the time-of-flight of sound pulses[cite: 77, 78, 80, 81]. [cite_start]The filtered distance is sent as a JSON object over MQTT at a 1 Hz interval[cite: 82, 83, 93].

### B. Processing Node
[cite_start]The ESP32-C3 subscribes to the MQTT topic, parses the JSON message, and displays the raw distance value on an SSD1306 OLED display[cite: 96, 98, 99, 103]. [cite_start]It also logs data to an InfluxDB Cloud instance using Influx Line Protocol (ILP) and HTTPS authentication[cite: 104, 105, 108].

### C. MQTT Protocol
[cite_start]The system uses the lightweight MQTT protocol for message exchange[cite: 111, 112]. [cite_start]The broker used is Mosquitto, and the topic is `02a9c4da-80b8-4571-bb96-24ca990ac744/vehicle/proximity`[cite: 114, 115]. [cite_start]The end-to-end latency was measured at 50-70 ms[cite: 120].

## IV. Component Integration & Software Stack

[cite_start]The hardware stack is minimal and efficient[cite: 130]. [cite_start]The Arduino Nano 33 IoT interfaces with the HC-SR04 sensor, while the ESP32-C3 connects to the SSD1306 OLED display via I²C[cite: 131, 135]. [cite_start]A custom library was implemented for flicker-free OLED text updates[cite: 140]. [cite_start]Both microcontrollers use the Arduino IDE and non-blocking firmware architectures[cite: 151, 165].

## V. Results and Evaluation

[cite_start]The system was evaluated for latency, display responsiveness, message continuity, and fault recovery[cite: 199, 200, 203, 204]. [cite_start]The OLED display provided immediate feedback, showing "DANGER" for objects within 15 cm and "SAFE" beyond 20 cm[cite: 209, 219]. [cite_start]All MQTT messages were logged to InfluxDB with zero loss, and the cloud dashboard accurately reflected physical distance changes[cite: 223, 227]. [cite_start]The hardware was thermally stable and performed well under continuous load without exhausting heap space[cite: 312, 314].

## VI. Conclusion

[cite_start]SVAMS is a low-cost, modular, and real-time embedded safety system for vehicles[cite: 316]. [cite_start]The dual-microcontroller architecture provides modularity and resilience[cite: 318]. [cite_start]The system demonstrated an average response time of under 70 milliseconds, meeting real-time application criteria[cite: 326]. [cite_start]It serves as a reference model for future academic study or deployment in contexts like autonomous parking systems[cite: 330].

## VII. Future Work

[cite_start]Future work includes adding a threshold-based classifier and multimodal alerts[cite: 335]. Other planned enhancements are:
* [cite_start]**BLE and V2X Communication**: Broadcasting alerts to smartphones or wearable devices using Bluetooth Low Energy (BLE)[cite: 339].
* [cite_start]**Geolocation and Spatiotemporal Logging**: Incorporating a GPS module to geo-tag data and identify high-risk zones[cite: 343, 344].
* [cite_start]**Multi-Sensor and Multi-Vehicle Scalability**: Expanding the system to monitor multiple vehicle zones concurrently[cite: 347].
* [cite_start]**LIDAR and Infrared Sensor Fusion**: Integrating these sensors for better accuracy in non-ideal conditions[cite: 351].
* [cite_start]**Edge AI for Behaviour Recognition**: Using machine learning models to provide predictive alerts[cite: 354, 355].
* [cite_start]**OTA Updates and Config Portals**: Simplifying maintenance with over-the-air firmware updates and field configuration[cite: 357].
