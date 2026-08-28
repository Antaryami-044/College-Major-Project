# 🫀 IoT Wearable Health Monitor & Emergency Response System

> A low-cost, real-time cardiac monitoring device designed to prevent heart failure fatalities through continuous health tracking and automatic emergency alerts.

---

## 📸 Project Demonstration

Abstract
> <img width="350" align="center" height="500" alt="Abstract" src="https://github.com/user-attachments/assets/be73beeb-19dc-4999-9bec-a21bafe103ce" />


<div align="center">

<!-- OPTION 1: Place a GIF or Video Link here -->
### 🎥 System Demo & Real-Time Waveform Simulation

https://github.com/user-attachments/assets/8f825155-b244-40a9-90b8-6922a021e1ad



<br/>

<!-- OPTION 2: Arduino Uno R4 details Photo -->
<img src="https://github.com/Antaryami-044/College-Major-Project/blob/main/images/uno%20r4.jpg" alt="Hardware Setup" width="75%" />
<p><i>Figure 1: Arduino Uno R4 WiFi Pin Diagram </i></p>

</div>

---

## 📌 Overview

Heart disease accounts for a significant portion of sudden health emergencies, particularly where medical access is delayed. This project introduces a low-cost, continuous cardiac tracking solution engineered to detect early signs of heart failure and cardiovascular anomalies. Built for high-risk patients, the elderly, and rural healthcare environments, the device monitors vital signs and instantly notifies caregivers during critical medical events.

### Key Features
* **Continuous Vital Tracking:** Captures real-time Heart Rate (BPM), Oxygen Saturation ($\text{SpO}_2$), and Body Temperature.
* **Onboard Edge Computing:** Filters analog sensor noise directly on the microcontroller for fast, accurate anomaly detection.
* **Instant Emergency Dispatch:** Automatically sends SMS, email, and live GPS location alerts with a **1.4-second response latency**.
* **Live Cloud Dashboard:** Streams real-time health telemetry to ThingSpeak for remote physician monitoring and analytics.

---

## ⚙️ Architecture & Tech Stack

<div align="center">

<img src="https://github.com/Antaryami-044/College-Major-Project/blob/main/images/CKT%20Diagram.jpg" alt="Circuit Diagram" width="80%" />
<p><i>Figure 2: System Circuit Diagram & Pin Interconnections</i></p>

</div>

### Component Breakdown
* **Microcontroller:** Arduino Uno R4 WiFi (Embedded C++ Firmware)
* **Biometric Sensors:**
  * **AD8232:** Single-Lead Heart Rate Monitor (ECG signal extraction)
  * **MAX30100:** Pulse Oximeter & Heart Rate Sensor ($\text{SpO}_2$)
  * **LM35:** Analog Precision Temperature Sensor
* **Cloud & Communication:** ThingSpeak IoT Platform, REST/MQTT APIs, Wi-Fi, GSM/GPS module

---

## 📊 Live Telemetry & Cloud Dashboard

<div align="center">

<img src="https://github.com/Antaryami-044/College-Major-Project/blob/main/images/Full%20img%20of%20ThingSpeak.jpeg" alt="ThingSpeak Dashboard" width="85%" />
<p><i>Figure 3: ThingSpeak Live Cloud Dashboard showing BPM Graphs and GPS Location Mapping</i></p>


<img src="https://github.com/Antaryami-044/College-Major-Project/blob/main/images/graph%20of%20hearbeat.jpeg" alt="ThingSpeak Dashboard" width="85%" />
<p><i>Figure 4: HeartBeat Graph with (Signal, Thersold and BPM)</i></p>

</div>

The platform continuously uploads vital parameters to the cloud, giving doctors and caregivers an intuitive graphical dashboard to inspect live ECG signals, historical trends, and emergency location coordinates.

---

## 🚀 Use Cases

### 1. High-Risk Home Patient Monitoring
* **Scenario:** An elderly patient wears the device at home.
* **Operation:** If cardiac parameters breach safe thresholds, onboard edge-computing logic flags an anomaly and instantly sends an automated SMS/email with real-time GPS coordinates to emergency contacts.

### 2. Remote Clinical Telehealth
* **Scenario:** A doctor needs to evaluate a patient residing in a remote or rural area.
* **Operation:** The clinician logs into the secure ThingSpeak web console to review real-time heart rate trends, signal stability, and location metrics without requiring the patient to travel.

---
