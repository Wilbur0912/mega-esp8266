# Instruction

We seperate three code, which is esp8266, mega2560 and data_collection repectively.

## mega2560 code

For mega2560, it can extract 9 pressure data from pressure sensor and send the data to esp8266 with Serial3. When upload this code to the board, we have to switch the DIP to 1234 ON
## esp8266 code

For esp8266, after receiving data from mega2560, it can send the data to backend. When upload this code to the board, we have to switch the DIP to 567 ON

## So after upload all code, what's next?
In order to make it run, we have to switch the DIP to 1256 ON. For 1 and 2, they specially make esp8266 and mega2560 work together. For 5 and 6, they are specially make computer connect to esp8266 to see the serial print in esp8266. As we mention, this setting we cannot directly see the the message that printed out from mega2560, since the setting doesn't make computer connect directly to mega2560.

## switches of mega2560 R3 WIFI
![image](https://github.com/Wilbur0912/sitting_posture_detection_mega-esp8266/assets/89004015/e8334234-fe2e-4d13-8307-f3202f5106d4)


## data_collection
For data_collection, this code can extract pressure data with the speed of 115200, it is especially used for collection training data.

