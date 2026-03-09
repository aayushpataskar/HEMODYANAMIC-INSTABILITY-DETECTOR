#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ECG_PIN 34
#define ONE_WIRE_BUS 4

MAX30105 particleSensor;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);

float chestTemp = 0;
float fingerTemp = 0;

long lastBeat = 0;
float heartRate = 0;
float HRV = 0;

unsigned long ecgPeakTime = 0;
unsigned long ppgPeakTime = 0;

float PTT = 0;
float perfusionIndex = 0;

float impedanceChange = 0; // placeholder until AD5933 added

float HII = 0;

void setup()
{
  Serial.begin(115200);

  Wire.begin();

  if (!particleSensor.begin(Wire))
  {
    Serial.println("MAX30102 not found");
    while (1);
  }

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeIR(0x0A);

  tempSensors.begin();

  pinMode(ECG_PIN, INPUT);
}

void loop()
{

  /* ---------------- ECG SIGNAL ---------------- */

  int ecgSignal = analogRead(ECG_PIN);

  static int ecgThreshold = 2000;

  if(ecgSignal > ecgThreshold)
  {
      ecgPeakTime = millis();
  }

  /* ---------------- PPG SIGNAL ---------------- */

  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue))
  {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    heartRate = 60.0 / (delta / 1000.0);

    ppgPeakTime = millis();

    PTT = (ppgPeakTime - ecgPeakTime);
  }

  /* ---------------- TEMPERATURE ---------------- */

  tempSensors.requestTemperatures();

  chestTemp = tempSensors.getTempCByIndex(0);
  fingerTemp = tempSensors.getTempCByIndex(1);

  float tempGradient = chestTemp - fingerTemp;

  /* ---------------- PERFUSION INDEX ---------------- */

  perfusionIndex = particleSensor.getIR();

  /* ---------------- HRV ESTIMATION ---------------- */

  static float prevHR = 0;
  HRV = abs(heartRate - prevHR);
  prevHR = heartRate;

  /* ---------------- HII CALCULATION ---------------- */

  float w1 = 0.30;
  float w2 = 0.20;
  float w3 = 0.20;
  float w4 = 0.15;
  float w5 = 0.15;

  HII =
      w1 * (PTT / 200.0) +
      w2 * (HRV / 10.0) +
      w3 * (perfusionIndex / 10000.0) +
      w4 * (impedanceChange) +
      w5 * (tempGradient);

  /* ---------------- RISK CLASSIFICATION ---------------- */

  String status;

  if (HII < 0.3)
    status = "Stable";
  else if (HII < 0.6)
    status = "Early Instability";
  else
    status = "High Risk";

  /* ---------------- OUTPUT ---------------- */

  Serial.println("----- Hemoguard Data -----");

  Serial.print("HR: ");
  Serial.println(heartRate);

  Serial.print("HRV: ");
  Serial.println(HRV);

  Serial.print("PTT: ");
  Serial.println(PTT);

  Serial.print("Perfusion: ");
  Serial.println(perfusionIndex);

  Serial.print("Temp Gradient: ");
  Serial.println(tempGradient);

  Serial.print("HII: ");
  Serial.println(HII);

  Serial.print("Status: ");
  Serial.println(status);

  Serial.println("---------------------------");

  delay(200);
}