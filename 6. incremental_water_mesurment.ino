#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

AsyncWebServer server(80);

#define echoPin 4 // הפין אקו (Echo) של החיישן האולטרסוני
#define trigPin 5 //הפין טריג (trig) של החיישן האולטרסוני

float duration; // variable for the duration of sound wave travel
float mm; // variable for the distance measurement

float measurements[] = {};
float wholeseason;
float lastm;
int x;

const char* ssid = "home3";   // your network SSID (name)
const char* password = "10203040";   // your network password

WiFiClient client;

unsigned long myChannelNumber = 1635956;
const char * myWriteAPIKey = "XYKCRSX1PPT9JB0Y";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  WiFi.mode(WIFI_STA);
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP8266.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
}

void loop() {
  WiFi.begin(ssid, password);
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect");
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("\nConnected.");

    for (int count = 0; count < 10; count++) {
      digitalWrite(trigPin, LOW);
      delay(300);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      mm = (duration * 0.034 / 2) * 10; // Speed of sound wave divided by 2 (go and back)
      measurements[count] = mm;
    }
    float sendvalue = lowestnumber();  
   
    if (lastm < sendvalue) lastm = sendvalue;    
    
    float valueofdif = lastm - sendvalue;
    wholeseason = wholeseason + valueofdif;
    Serial.print("| המדידה הקודמת: "); Serial.print(lastm); Serial.print("| המדידה הנוכחית: "); Serial.print(sendvalue); Serial.print("ההפרש: "); Serial.println(valueofdif);
    x = ThingSpeak.writeField(myChannelNumber, 1, valueofdif, myWriteAPIKey);
    lastm = sendvalue;
    if (x == 200) {
      Serial.println("Channel update successful.");
      Serial.println("going to sleep!");
      delay(300000);
      Serial.println("woke up! lets go to measure rain!");
    }
   
  }
}
float calculatefrequent(float a[], int size) {
  int most = 0;     /*- כמות הפעמים שמופיע המספר שחוזר על עצמו הכי הרבה פעמים -*/
  float mostnum = 0;       /*- המספר שחוזר על עצמו הכי הרבה פעמים -*/
  float currentnum = 0;       /*- המספר שהפונקציה "חוקרת" כרגע  -*/
  for (int i = 0; i < size; i++) {     /*- עבור כל i  -*/
    currentnum = a[i];           /*- המספר שנחקר כרגע הוא הi במערך -*/
    int count = 0;                 /*- משתנה שסופר כמה פעמים הוא מופיע -*/
    for (int j = 0; j < size; j++) {      /*- עבור כל j -*/
      if ( a[i] != mostnum) {                  /*- אם אנו חוקרים מספר שונה מהגבוה ביותר -*/
        if (currentnum == a[j]) count += 1;            /*- אז אם המספר הנחקר שווה לזה שמופיע במערך במיקום j ספור +1 -*/
      }
    }
    if (count > most) {                     /*- אם המספר הנחקר מופיע יותר פעמים מקודמיו -*/
      most = count;                         /*- אז זו כמות הפעמים שהמספר החדש מופיע -*/
      mostnum = a[i];                      /*- וזה המספר החדש -*/
    }
  }
  //Serial.print("Most Frequent: ");            /*- אחרי שנעשה את זה עשר פעמים -*/
  //Serial.println(mostnum);  /*- המספר שמופיע הכי הרבה פעמים נמצא במשתנה הזה -*/
  return mostnum;
}

float lowestnumber() {
  float lowest = 0;
  float check = 0;
  for (int q = 0; q < 10; q++) {
    check = calculatefrequent(measurements, 10);
    if (lowest < check) lowest = check;
  }
  Serial.print("lowest: ");
  Serial.println(check);
  return check;
}
