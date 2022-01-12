# ESP-IDF I2C Scanner

## Overview
Use this program to check if your I2C device is still alive.

## How to use this project
Run command below in your terminal.  
```bash
git clone https://github.com/OckertM/ESP-IDF-I2C-Scanner.git
```

### Hardware Required
1 x ESP32  
1 x I2C sensor/device  
2 x 4K7 resistors

Connect one 4K7 resistor between GPIO 21 (SDA) and 3.3V.  
Connect the other 4K7 resistor between GPIO 22 (SCL) and 3.3V.

**Note:** You are most likely going to need pullup resistors even if the internal pullups are enabled!

#### Pin Assignment:
GPIO 21 SDA  
GPIO 22 SCL  

### Build and Flash
Enter `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output
```bash
I (172347) i2c scanner: Found device at address 0x48
I (172347) i2c scanner: Found 1 device
```

## Troubleshooting
When in doubt, **check your GPIO!**
