# avr-microwave-software
In this project, I created the core software logic for a microwave oven. It runs on ATmega328P using bare-metal C, hardware timers, and interrupts instead of standard Arduino libraries.

You can test the FSM logic and interact with the circuit directly in your browser:
[**Run in Wokwi Simulator**](https://wokwi.com/projects/new/arduino-uno)
This project is optimized for simulation. If you plan to flash this code onto a physical ATmega328P, please note:
* **Hardware Debouncing is Required:** The Wokwi circuit uses ideal buttons with bouncing disabled. Real physical buttons produce mechanical noise (contact bounce) when pressed. Since this code relies on ultra-fast hardware interrupts (INT0, INT1), you must add physical RC-filters (a resistor and capacitor) to the button pins to prevent multiple rapid triggers.
* **Current Limiting:** Ensure you use a 220Ω - 330Ω resistor in series with the LED on PD4 to avoid burning out the microcontroller pin.
