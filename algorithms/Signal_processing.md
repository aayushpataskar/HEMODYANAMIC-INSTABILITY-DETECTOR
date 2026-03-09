# Signal Processing Pipeline

Raw physiological signals are filtered and processed before feature extraction.

## ECG Processing

Band-pass filtering between 0.5 Hz and 40 Hz is applied to remove baseline drift and high-frequency noise.

R-peaks are detected using amplitude thresholding.

---

## PPG Processing

PPG signals are filtered using a low-pass filter to remove motion artifacts.

Pulse peaks are detected using derivative-based peak detection.

---

## Bioimpedance Processing

Thoracic impedance is measured using AC current injection and voltage sensing.

Impedance trends are used to estimate blood volume changes.

---

## Temperature Processing

Temperature readings are averaged over multiple samples to reduce noise.