# AVR LED Brightness Control Project
This repository contains an AVR-based project to control LED brightness using a button. The code is structured and compiled using a custom Makefile.

## Code Description
The main functionality is to adjust the PWM duty cycle and consequently the brightness of an LED connected to an ATmega328p microcontroller based on button presses.

* On each button press, the brightness of the LED increases.
* Once it reaches the maximum brightness, a subsequent press resets it to a dimmer state.

## Makefile Overview
The **'Makefile'** provided is for building and uploading the AVR project to the ATmega328p microcontroller. Let's break down the key parts:

### Variables:
* Toolchain binaries: The tools required to compile, link, and upload the project.
- `CC`: AVR GCC Compiler.
- `LD`: AVR Linker.
- `OBJCOPY`: Converts ELF format to different formats like HEX.
- `OBJDUMP`: Dumps information from object files.
- `AVRSIZE`: Provides size of the generated binary.
- `OBJISP`: AVRDUDE tool to upload firmware.

* MCU Specifications:
- `MCU`: Specifies the microcontroller being used (`atmega328p` in this case).
- `CFLAGS`: Compiler flags. Includes optimizations, MCU type, frequency, and standard C version.

* Serial Port:
- `PORT`: Specifies the serial port for uploading firmware.
  
* Binary and Output:
- `BIN`: Name of the output binary.
- `OUT`: Name of the HEX file generated.
- `SOURCES`: Source files for the project.
  
*Build Directories:
- `DEBUG`: Determines if the build is a debug build (`1` for debug).
- `OUTPUTDIR`: Directory for the build output, either `bin/debug` or `bin/release`.

## Targets:
* `all`: Default target that builds the project and outputs the hex file.

- `isp`: Uploads the generated HEX file to the MCU using AVRDUDE.

* `clean`: Removes generated files.

# Using the Makefile:
* Compile the Project:
```bash
make
```
* Upload to MCU:
```bash
make isp
```

* Clean the Project:
``` bash
make clean
```

## Hardware Setup and Connections

### Components Needed:
- ATmega328p microcontroller board (e.g., Arduino Uno)
- LED
- Push-button
- 10kΩ resistor (for button pull-up, if the internal pull-up is not used)
- Breadboard and jumper wires

### Connections:

#### 1. **LED:**
Connect the anode (longer leg) of the LED to pin `D6` of the ATmega328p (or the respective Arduino board pin). Connect the cathode (shorter leg) to the ground (GND) of the board, preferably through a current-limiting resistor (e.g., 220Ω).

#### 2. **Push-button:**
The button is used to adjust the brightness of the LED.
- One end of the push-button goes to pin `D2` of the ATmega328p.
- The other end connects to the ground (GND).

If you're not using the internal pull-up of the microcontroller:
- Connect a 10kΩ resistor from the `D2` side of the button (where you connected it to the microcontroller) to VCC (usually 5V or 3.3V depending on the board). This resistor acts as a pull-up.
