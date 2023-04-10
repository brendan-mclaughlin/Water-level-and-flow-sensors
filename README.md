# Water-level-and-flow-sensors
ECE484 Chip Interface Repository
compile_script.py -> Run this to compile all lib and main files. Can also be used to flash the 328 with latest software
flowAndLevel.c -> File that demonstrates using all of hardware. LCD screen will print off current water flow rate(L/Hr) and the water level percentage of sensor. File has no control over water pump since I needed supply it with more than 5V to sufficiently move a measurable amount of water
lib/HD44780_Settings.h -> File used to set LCD Pins
lib/HD44780.c -> File used to change display of LCD.
