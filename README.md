# Hemoguard

**Hemoguard** is a multimodal biomedical monitoring system designed to detect early signs of internal bleeding and hemodynamic instability in post-operative patients.

The system integrates multiple physiological signals including ECG, PPG, thoracic bioimpedance, and temperature to compute a **Hemodynamic Instability Index (HII)** that provides early warnings of potential hemorrhage.

---

## Problem Statement

Internal bleeding after surgery often develops gradually and may not immediately cause visible changes in traditional vital signs such as heart rate or blood pressure.  
Current monitoring methods may fail to detect early physiological changes, delaying intervention and increasing risk to the patient.

Hemoguard addresses this problem by continuously monitoring subtle physiological indicators that appear **before major vital sign collapse**.

---

## System Overview

The Hemoguard system consists of two wearable sensing units:

### Chest Unit
- ECG electrodes for cardiac electrical activity
- Thoracic bioimpedance electrodes for blood volume changes
- Temperature sensor for core body temperature

### Finger Unit
- PPG sensor for peripheral blood flow
- Temperature sensor for peripheral temperature

These signals are processed by an **ESP32 microcontroller**, which extracts physiological features and computes the Hemodynamic Instability Index.

---

## Sensor Architecture

| Sensor | Purpose |
|------|------|
| ECG (AD620 instrumentation amplifier) | Heart electrical activity |
| MAX30102 | PPG waveform and pulse detection |
| AD5933 | Thoracic bioimpedance measurement |
| DS18B20 | Core and peripheral temperature monitoring |
| ESP32 | Signal processing and feature extraction |

---

## Signal Processing Pipeline

Sensors → Signal Conditioning → Feature Extraction → Multimodal Fusion → HII Calculation → Risk Detection

Extracted features include:

- Heart Rate (HR)
- Heart Rate Variability (HRV)
- Pulse Transit Time (PTT)
- PPG Pulse Amplitude
- Thoracic Impedance Change
- Temperature Gradient

---

## Hemodynamic Instability Index (HII)

The system computes a composite instability score using weighted physiological features.
