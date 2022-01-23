# Rainmeter
ESP8266 rainmeter

# Project purpose
measuring rain volume in container with US sensor and store data in firebase.

# stage 1: usensor check
file: test-usonic-sensor.ino

# stage 2: filer results by 10
file: usensor-filer-by-10.ino

# stage 3: filer results by 100
file: usensor-filer-by-100.ino

# stage 4: connecting to thingspeak

# stage 5: sleep 2 min interval

*remember:* needs to connect rst pin to D0 for the sleep to work, and disconnect rst pin for upload new code!
