# Smart Vehicle Proximity Alert System

This is a research paper on the design and evaluation of a Smart Vehicle Alert and Monitoring System (SVAMS). The system is an Internet of Things (IoT) architecture for real-time proximity intelligence in vehicles.

## Abstract

SVAMS uses ESP32-C3 and Arduino Nano 33 IoT microcontrollers. The system uses ultrasonic sensors for proximity detection, MQTT for data transfer, and OLED displays for immediate alerts. It also pushes data to a cloud backend for logging and analysis. The system is a modular IoT architecture with embedded edge computing and low-latency wireless communication. Controlled tests showed sub-100 ms alert latency and reliable object detection between 5-100 cm. This framework can be used for vehicle-to-driver and vehicle-to-cloud safety applications.

## I. Introduction

Due to increased urban vehicle density, there is a need for responsive, accurate, and cost-efficient embedded safety technologies. While high-end cars have advanced driver-assistance systems (ADAS), these are often too expensive for most low-cost and legacy vehicles. The SVAMS project, built on open-source hardware and software, addresses this gap. It uses an Arduino Nano 33 IoT and an ESP32-C3 with HC-SR04 ultrasonic sensors to monitor distances to obstacles. Proximity data is sent over an MQTT broker, processed by the ESP32, and displayed on an OLED module. All events are logged to a cloud backend via HTTP or MQTT integration with InfluxDB for long-term analysis.

## II. Use Case and Motivation

Urban driving conditions and the lack of sensors in older vehicles increase the risk of low-speed collisions. A 2023 report found that about 37% of non-fatal urban collisions happen at speeds below $30~km/hr. The adoption of ADAS is concentrated in the Global North, and aftermarket solutions are often isolated and not extensible. SVAMS fills this gap by using a ground-up IoT architecture with open-source components. The system is suitable for municipal fleets, ride-share vehicles, and last-mile delivery vans.

## III. System Architecture

SVAMS is a modular system with two microcontrollers: an Arduino Nano 33 IoT sensor node and an ESP32-C3 processing node. They communicate asynchronously via the MQTT protocol. The sensor node publishes proximity data, which the processing node subscribes to. The processing node then renders the information on an OLED screen and sends it to an InfluxDB instance for logging. The architecture is resilient, as local sensing and display continue even if the cloud disconnects.

### A. Sensing Node Design
The Arduino Nano 33 IoT senses distance using an HC-SR04 ultrasonic sensor. The distance is calculated from the time-of-flight of sound pulses. The filtered distance is sent as a JSON object over MQTT at a 1 Hz interval.

### B. Processing Node
The ESP32-C3 subscribes to the MQTT topic, parses the JSON message, and displays the raw distance value on an SSD1306 OLED display. It also logs data to an InfluxDB Cloud instance using Influx Line Protocol (ILP) and HTTPS authentication.

### C. MQTT Protocol
The system uses the lightweight MQTT protocol for message exchange. The broker used is Mosquitto, and the topic is `02a9c4da-80b8-4571-bb96-24ca990ac744/vehicle/proximity. The end-to-end latency was measured at 50-70 ms.

## IV. Component Integration & Software Stack

The hardware stack is minimal and efficient. The Arduino Nano 33 IoT interfaces with the HC-SR04 sensor, while the ESP32-C3 connects to the SSD1306 OLED display via I²C. A custom library was implemented for flicker-free OLED text updates. Both microcontrollers use the Arduino IDE and non-blocking firmware architectures.

## V. Results and Evaluation

The system was evaluated for latency, display responsiveness, message continuity, and fault recovery. The OLED display provided immediate feedback, showing "DANGER" for objects within 15 cm and "SAFE" beyond 20 cm. All MQTT messages were logged to InfluxDB with zero loss, and the cloud dashboard accurately reflected physical distance changes. The hardware was thermally stable and performed well under continuous load without exhausting heap space.

## VI. Conclusion

SVAMS is a low-cost, modular, and real-time embedded safety system for vehicles. The dual-microcontroller architecture provides modularity and resilience. The system demonstrated an average response time of under 70 milliseconds, meeting real-time application criteria. It serves as a reference model for future academic study or deployment in contexts like autonomous parking systems.

## VII. Future Work

Future work includes adding a threshold-based classifier and multimodal alerts. Other planned enhancements are:
* **BLE and V2X Communication**: Broadcasting alerts to smartphones or wearable devices using Bluetooth Low Energy (BLE).
* **Geolocation and Spatiotemporal Logging**: Incorporating a GPS module to geo-tag data and identify high-risk zones.
* **Multi-Sensor and Multi-Vehicle Scalability**: Expanding the system to monitor multiple vehicle zones concurrently.
* **LIDAR and Infrared Sensor Fusion**: Integrating these sensors for better accuracy in non-ideal conditions.
* **Edge AI for Behaviour Recognition**: Using machine learning models to provide predictive alerts.
* **OTA Updates and Config Portals**: Simplifying maintenance with over-the-air firmware updates and field configuration.
