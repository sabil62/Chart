
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

#define FIREBASE_HOST "flutter-56d87.firebaseio.com" //--> URL address of your Firebase Realtime Database.
#define FIREBASE_AUTH "tlQLCDrPdBfxaTfYIAA3O45nnzG7xEPm5gj1N1UO" //--> Your firebase database secret code.
#define WIFI_SSID "Space" // Change the name of your WIFI
#define WIFI_PASSWORD "111122220" // Change the password of your WIFI
//Successfully integtated two ultrasonic sensors

String id = "KLL";


//greeen wire  light D6
//yellow D7 
//final top stack ultrasonic sensor
//v++ external grnd external + common
#define echoPin D7 //top USS
#define trigPin D6 //

#define echoPin_bottom D5 //side USS
#define trigPin_bottom D4 //

//Defination for DHT sensors
#include "DHT.h"        
#define DHTTYPE DHT11 
#define dht_dpin D3
#define sensor_pin A0 

#include <Servo.h> 
int servoPin = D2; 
Servo Servo1; 

DHT dht(dht_dpin, DHTTYPE); 


// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

long duration_bottom; // variable for the duration of sound wave travel
int distance_bottom; // variable for the distance measurement


String binStatDB = "BinStats";
    String binId = "binId";
    String binLevel = "binLevel";
    String binStatus = "binStatus";
    String humid = "humidity";
    String moistureAnalogValue = "moistureAnalogValue";
    String moistureStatus = "moistureStatus";
    String temperature = "temperature";
    String timeStamp = "timeStamp";
    String user_ID = "userId";

String Bins = "Bins";
    String createdDate = "createdDate";
    String locate = "location";
    String userId = "userId";

String Faqs = "Faqs";
    String answer = "answer";
    String createdAt = "createdAt";
    String question = "question";
    String updatedAt = "updatedAt";

String Rewards = "Rewards";
    String created_Reward_Date = "createdDate";
    String description = "description";
    String rewardPoint = "rewardPoint";
    String title = "title";
    String user_Reward_Id = "userId";

String Users = "Users";
    String created_Date = "createdDate";
    String firstName = "firstName";
    String lastName = "lastName";
    String updatedDate = "updatedDate";
String TD = "Time";
String HD = "Humidity";


//String DBaddH = DBnm + "/" + TD + "/" + HD; //--> Creating a Database path
//Firebase.pushString(DBaddH,strHum); //--> 


void setup() {

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.pushString("ID",id);

  //
  Servo1.attach(servoPin);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  pinMode(trigPin_bottom, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin_bottom, INPUT); // Sets the echoPin as an INPUT

  dht.begin();
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  push_id();
  push_timeStamp();
  push_userId();

  //Bins data_firebase
  push_createdDate();
  push_location();
  push_Bins_userId();

 //Bins faq
  push_ans();
  push_createdAt();
  push_question();
  push_updatedAt();

//Bins Users
push_User_createdDate();
push_firstName();
push_lastName();
push_UpdatedDate();

//Bin Rewards

//push_Reward_create(); remainning to add on
//push_Reward_desc(); remaininig to add from logic
push_Reward_title();
push_Reward_id();
push_Reward_create();



}


     

      
void loop() {
  
  top_US();
  bottom_US();
  tempSensor();
  moisture();
  

}

void top_US(){


  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance in CM: ");
  Serial.print(distance);
  if(distance<=5){
    //AlmostFull
    // String binPercentage = String(80);
      String binLevelpush =  binStatDB + "/" + binLevel; //--> Creating a Database path
      Firebase.pushString(binLevelpush,String(80));
      
    }
   else if((distance >= 5)&&(distance <= 14)){
  
      String binLevelpush =  binStatDB + "/" + binLevel; //--> Creating a Database path
      Firebase.pushString(binLevelpush,String(50));
    }
   else{
      String binLevelpush =  binStatDB + "/" + binLevel; //--> Creating a Database path
      Firebase.pushString(binLevelpush,String(10));
     // Firebase.child("some").setString("test baby");
    }
   
//  Serial.println("\n");
  
  }


void bottom_US(){

   // Clears the trigPin condition
  digitalWrite(trigPin_bottom, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_bottom, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_bottom, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_bottom = pulseIn(echoPin_bottom, HIGH);
  // Calculating the distance
  distance_bottom = duration_bottom * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance_bottom: ");
  Serial.print(distance_bottom);
  Serial.println(" cm");

  String OOO = "OPEN";
  String CCC = "CLOSED";
  if( distance_bottom <= 30){
      Servo1.write(180); 
     
    String binStatuspush =  binStatDB + "/" + binStatus; //--> Creating a Database path
    Firebase.pushString(binStatuspush,OOO);
      delay(3000);
  
  }
     else{
    //  Serial.println('ninteyfive');
    Servo1.write(00);
 
    String binStatuspush =  binStatDB + "/" + binStatus; //--> Creating a Database path
    Firebase.pushString(binStatuspush,CCC);
       delay(300);
     } 
  }



void tempSensor(){

float h = dht.readHumidity();
float t = dht.readTemperature();         
Serial.print("Current humidity = ");
Serial.print(h);
Serial.print("%  ");
Serial.print("temperature = ");
Serial.print(t); 
Serial.println("C  ");

String humide = String(h);
String binHumiditypush =  binStatDB + "/" + humid; //--> Creating a Database path
Firebase.pushString(binHumiditypush,humide);
delay(200);

String temp = String(t);
String binTemperaturepush =  binStatDB + "/" + temperature; //--> Creating a Database path
Firebase.pushString(binTemperaturepush,temp);
}

void moisture(){
int moisture_percentage;
   moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );
 
    Serial.print("Soil Moisture(in Percentage) = ");
    Serial.print(moisture_percentage);
    Serial.println("%");
int analog = (analogRead(A0));

String seven = "MOIST";
String one = "DRY";

if(analog>= 700){
    String binMoisturepush =  binStatDB + "/" + moistureStatus; //--> Creating a Database path
    Firebase.pushString(binMoisturepush, one);
} 
else{
String binMoisturepush =  binStatDB + "/" + moistureStatus; //--> Creating a Database path
Firebase.pushString(binMoisturepush, seven);
}

String moist = String(moisture_percentage);
String binMoisturepush =  binStatDB + "/" + moistureAnalogValue; //--> Creating a Database path
Firebase.pushString(binMoisturepush, moist);
delay(100);


    delay(1000);
  }


void push_id(){

String id = "-MLu9WUL3KYn6gq6S-dr";
String binIdpush =  binStatDB + "/" + binId; //--> Creating a Database path
Firebase.pushString(binIdpush,id);

}

void push_timeStamp(){
String timeSt = "17:30:22";
String bintimeStamppush =  binStatDB + "/" + timeStamp; //--> Creating a Database path
Firebase.pushString(bintimeStamppush,timeSt);
 
 }

void push_userId(){
String id = "-MLmQOBuBvlYCJOLg5sc";
String binUserIdpush =  binStatDB + "/" + userId; //--> Creating a Database path
Firebase.pushString(binUserIdpush,id);
 }

///push bins functions

void push_createdDate(){
String bins = "Bins";
String DateCt = "11/26/2020";
String binsDatepush =  bins + "/" + createdDate; //--> Creating a Database path
Firebase.pushString(binsDatepush,DateCt);
}

void push_location(){
String bins = "Bins";
String gps = "27.717844,85.3248188";
String binLocationpush = bins + "/" + locate; //--> Creating a Database path
Firebase.pushString(binLocationpush,gps);
}


void push_Bins_userId(){
String bins = "Bins";
String id = "-MLmQOBuBvlYCJOLg5sc";
String binUserIdpush =  bins + "/" + userId; //--> Creating a Database path
Firebase.pushString(binUserIdpush,id);
}


void push_ans(){
  String ans = "We will reply you very soon";
  String question = " How can you boost up composting?";
  String Faqpush = Faqs + "/" + answer; //--> Creating a Database path
  Firebase.pushString(Faqpush,ans);
}

void push_question(){
  String qe = "question";
  String question = " How can you boost up composting?";
  String Faqpush = Faqs + "/" + qe; //--> Creating a Database path
  Firebase.pushString(Faqpush,question);
}
void push_createdAt(){

//String Faqs = "Faqs";
String DateCt = "11/26/2020";
String FaqDatepush =  Faqs + "/" + createdAt; //--> Creating a Database path
Firebase.pushString(FaqDatepush,DateCt);
  
}
void push_updatedAt(){
 String DateCt = "11/27/2020";
String FaqDatepush =  Faqs + "/" + updatedAt; //--> Creating a Database path
Firebase.pushString(FaqDatepush,DateCt);
  
}


///Firebase Users

void push_User_createdDate(){
      String DateCt = "11/26/2020";
      String FaqDatepush =  Users + "/" + createdDate; //--> Creating a Database path
      Firebase.pushString(FaqDatepush,DateCt);
}
  
void push_firstName(){
      String fN = "Hari";
      String FaqDatepush =  Users + "/" + firstName; //--> Creating a Database path
      Firebase.pushString(FaqDatepush,fN);
  
}
void push_lastName(){
      String lN = "lastName";
      String FaqDatepush =  Users + "/" + lN; //--> Creating a Database path
      Firebase.pushString(FaqDatepush,lN);
 }
 
void push_UpdatedDate(){
  String DateCt = "11/26/2020";
      String FaqDatepush =  Users + "/" + updatedDate; //--> Creating a Database path
      Firebase.pushString(FaqDatepush,DateCt);
  }

//Firebae Rewards.

void push_Reward_create(){
    String DateCt = "11/26/2020";
      String FaqDatepush =  Rewards + "/" + created_Reward_Date; //--> Creating a Database path
      Firebase.pushString(FaqDatepush,DateCt);
  
}

  
void push_Reward_title(){
   String lN = "Rewards";
      String FaqDatepush =  Rewards + "/" + title; //--> Creating a Database path
      Firebase.pushString(FaqDatepush,lN);
  }

  
void push_Reward_id(){

String rewardId = "-MLmQOBuBvlYCJOLg5sc";
String binLocationpush = Rewards + "/" + user_Reward_Id; //--> Creating a Database path
Firebase.pushString(binLocationpush,rewardId);
  
}
