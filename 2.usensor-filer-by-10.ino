#define echoPin 4 // הפין אקו (Echo) של החיישן האולטרסוני
#define trigPin 5 //הפין טריג (trig) של החיישן האולטרסוני

float duration; // variable for the duration of sound wave travel
float mm; // variable for the distance measurement

float measurements[] = {};

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void loop() {
  for (int count = 0; count < 10; count++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

    mm = (duration * 0.034 / 2) * 10; // Speed of sound wave divided by 2 (go and back)
    measurements[count] = mm;
  }

  calculatefrequent(measurements,10);

}

float calculatefrequent(float a[], int size) {
  int most = 0;     /*- כמות הפעמים שמופיע המספר שחוזר על עצמו הכי הרבה פעמים -*/
  float mostnum = 0;       /*- המספר שחוזר על עצמו הכי הרבה פעמים -*/
  float currentnum = 0;       /*- המספר שהפונקציה "חוקרת" כרגע  -*/ 
  for (int i=0; i <size; i++) {        /*- עבור כל i  -*/
      delay(200);             
      currentnum=a[i];             /*- המספר שנחקר כרגע הוא הi במערך -*/
      int count = 0;                 /*- משתנה שסופר כמה פעמים הוא מופיע -*/
      for (int j=0;j <size; j++) {          /*- עבור כל j -*/
        if ( a[i] != mostnum) {                  /*- אם אנו חוקרים מספר שונה מהגבוה ביותר -*/
          if (currentnum == a[j]) count += 1;            /*- אז אם המספר הנחקר שווה לזה שמופיע במערך במיקום j ספור +1 -*/
          delay(200);         
          Serial.print("for ");               
          Serial.print(a[i]);          
          Serial.print(" :");
          Serial.println(count);
        }
      }
      if (count > most) {                     /*- אם המספר הנחקר מופיע יותר פעמים מקודמיו -*/
        most = count;                         /*- אז זו כמות הפעמים שהמספר החדש מופיע -*/
        mostnum = a[i];                      /*- וזה המספר החדש -*/
        Serial.print("most: ");
        Serial.println(most);
        Serial.print("mostnum: ");
        Serial.println(mostnum);
      }
  }
  delay(2000);
  Serial.print("Most Frequent: ");            /*- אחרי שנעשה את זה עשר פעמים -*/
  Serial.println(mostnum);  /*- המספר שמופיע הכי הרבה פעמים נמצא במשתנה הזה -*/
  return mostnum;
}
