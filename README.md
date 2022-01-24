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

# stage 6: full rainmeter
Libraries: 
https://github.com/me-no-dev/ESPAsyncTCP
https://github.com/me-no-dev/ESPAsyncWebServer
https://github.com/ayushsharma82/AsyncElegantOTA
