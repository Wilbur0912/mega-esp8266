# Instruction

We seperate three code, which is esp8266, mega2560 and data_collection repectively.

## mega2560 code

For mega2560, it can extract 9 pressure data from pressure sensor and send the data to esp8266 with Serial3. 
## esp8266

For esp8266, after receiving data from mega2560, it can send the data to backend

## data_collection
For data_collection, this code can extract pressure data with the speed of 115200, it is especially used for collection training data.