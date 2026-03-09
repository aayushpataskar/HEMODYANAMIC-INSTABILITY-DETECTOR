# Hemodynamic Instability Index (HII)

The Hemoguard system computes a composite instability score using a weighted combination of physiological features.

## Feature Weights

| Feature | Weight |
|-------|------|
| Pulse Transit Time (PTT) | 0.30 |
| Heart Rate Variability (HRV) | 0.20 |
| PPG Amplitude | 0.20 |
| Bioimpedance Change (ΔZ) | 0.15 |
| Temperature Gradient (ΔT) | 0.10 |
| Heart Rate (HR) | 0.05 |

Sum of weights = 1.0

---

## HII Formula

HII = Σ wi · Fi

Where:

Fi = normalized physiological feature  
wi = corresponding feature weight

Expanded form:

HII =
0.30 * PTT +
0.20 * HRV +
0.20 * PPG_amp +
0.15 * ΔZ +
0.10 * ΔT +
0.05 * HR

---

## Risk Classification

| HII Range | Status |
|-----------|--------|
| < 0.35 | Stable |
| 0.35 – 0.65 | Early Instability |
| > 0.65 | High Risk |