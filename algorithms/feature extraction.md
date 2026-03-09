# Feature Extraction

The Hemoguard system extracts multiple physiological indicators from raw sensor signals.

## Heart Rate (HR)

Heart rate is derived from the ECG signal by detecting R-peaks in the QRS complex.

HR = 60 / RR_interval

Where RR_interval is the time between two consecutive R-peaks.

---

## Heart Rate Variability (HRV)

HRV is estimated using beat-to-beat variations:

HRV = |HR_current - HR_previous|

---

## Pulse Transit Time (PTT)

PTT measures the time delay between electrical and mechanical heart activity.

PTT = t(PPG_peak) - t(ECG_R_peak)

---

## PPG Pulse Amplitude

The amplitude of the PPG waveform represents peripheral perfusion.

PPG_amp = max(PPG_signal) - min(PPG_signal)

---

## Temperature Gradient

Temperature gradient indicates peripheral vasoconstriction.

ΔT = Chest_Temp - Finger_Temp

---

## Bioimpedance Change

Thoracic impedance variations indicate blood volume changes.

ΔZ = Z_current - Z_baseline