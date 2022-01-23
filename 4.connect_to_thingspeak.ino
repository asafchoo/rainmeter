#include <ESP8266WiFi.h>
#include "ThingSpeak.h" 

WiFiServer server(80);

#define echoPin 4 // הפין אקו (Echo) של החיישן האולטרסוני
#define trigPin 5 //הפין טריג (trig) של החיישן האולטרסוני

float duration; // variable for the duration of sound wave travel
float mm; // variable for the distance measurement

float measurements[] = {};
float measurements2p[] = {};

const char* ssid = "Heman";   // your network SSID (name) 
const char* password = "chechoo1";   // your network password

WiFiClient client;

unsigned long myChannelNumber = 1635956;
const char * myWriteAPIKey = "XYKCRSX1PPT9JB0Y";

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
    Serial.println(" "); 
    WiFi.begin(ssid, password);
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){  
      delay(1000);     
      Serial.print("."); 
    } 
    Serial.println(" "); 
    Serial.println("\nConnected.");
    
  for (int cnt = 0; cnt <10; cnt++) {
    for (int count = 0; count < 10; count++) {
      digitalWrite(trigPin, LOW);
      delay(50);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
  
      mm = (duration * 0.034 / 2) * 10; // Speed of sound wave divided by 2 (go and back)
      measurements[count] = mm;
    }
    measurements2p[cnt] = calculatefrequent(measurements,10);
  }
  float sendvalue = calculatefrequent(measurements2p,10);
  Serial.print("very very Most Frequent: ");  
  Serial.println(sendvalue);
  delay(1000);

  int x = ThingSpeak.writeField(myChannelNumber, 1, sendvalue, myWriteAPIKey);

  if(x == 200){
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}  
}

float calculatefrequent(float a[], int size) {
  int most = 0;     /*- כמות הפעמים שמופיע המספר שחוזר על עצמו הכי הרבה פעמים -*/
  float mostnum = 0;       /*- המספר שחוזר על עצמו הכי הרבה פעמים -*/
  float currentnum = 0;       /*- המספר שהפונקציה "חוקרת" כרגע  -*/ 
  for (int i=0; i <size; i++) {        /*- עבור כל i  -*/
      currentnum=a[i];             /*- המספר שנחקר כרגע הוא הi במערך -*/
      int count = 0;                 /*- משתנה שסופר כמה פעמים הוא מופיע -*/
      for (int j=0;j <size; j++) {          /*- עבור כל j -*/
        if ( a[i] != mostnum) {                  /*- אם אנו חוקרים מספר שונה מהגבוה ביותר -*/
          if (currentnum == a[j]) count += 1;            /*- אז אם המספר הנחקר שווה לזה שמופיע במערך במיקום j ספור +1 -*/     
        }
      }
      if (count > most) {                     /*- אם המספר הנחקר מופיע יותר פעמים מקודמיו -*/
        most = count;                         /*- אז זו כמות הפעמים שהמספר החדש מופיע -*/
        mostnum = a[i];                      /*- וזה המספר החדש -*/
      }
  }
  return mostnum;
}
