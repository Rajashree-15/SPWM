# 3-Phase Sinusoidal PWM — ATmega328P (Bare-Metal)

Implemented a 3-phase Sinusoidal Pulse Width Modulation (SPWM) algorithm on the ATmega328P using direct register-level bit manipulation, with no HAL or abstraction layers.

## Why SPWM in Power Converters

In power converters, switches (MOSFETs, IGBTs) need to be controlled precisely to synthesize an AC output from a DC bus. SPWM is the standard technique because it minimizes harmonic distortion in the output voltage, producing a waveform that closely approximates a pure sine wave. This directly reduces stress on motors and loads, improves efficiency, and meets EMI standards. Compared to square-wave switching, SPWM produces significantly lower Total Harmonic Distortion (THD), making it essential for motor drives, inverters, and UPS systems.

## Dead Time — Why It Matters

In a 3-phase inverter, each phase leg has two switches (high-side and low-side) that must never conduct simultaneously — this would cause a shoot-through fault, creating a direct short across the DC bus and destroying the switches. Since real switches do not turn off instantaneously, a dead time interval must be inserted between turning off one switch and turning on the complementary switch. This small blanking period prevents overlap and protects the hardware. In this implementation, dead time was managed through direct manipulation of the ATmega328P's 16-bit timer registers, ensuring deterministic and hardware-accurate timing without relying on software delays.

## Implementation Details

- **Platform:** ATmega328P
- **Method:** Bare-metal, direct register bit manipulation
- **Modulation:** 3-phase SPWM
- **Dead Time:** Hardware-level, via 16-bit timer register control
- **No HAL / No abstraction layers**
