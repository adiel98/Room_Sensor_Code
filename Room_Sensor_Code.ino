 /////////////////
 // MODIFY HERE //
/////////////////

// Add your PushingBox Scenario DeviceID here:
  char devid[] = "vDCE014E8A2BFBE2";
  
  //////////////
 //   End    //
//////////////

char serverName[] = "api.pushingbox.com";
boolean DEBUG = true;
#include <Bridge.h>
#include <HttpClient.h>

 /* PIR sensor tester
 */
 
 
 //
 int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
 
/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
 const int ledPin = 13;                // choose the pin for the LED
 const int inputPin = 2;               // choose the input pin (for PIR sensor)
   int pirState = LOW;
  int val = 0;// we start, assuming no motion detected
//  

// variable for reading the pin status


#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
 
void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);
  while (!Serial); // wait for a serial connection
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("Temperature");

    delay(1000);
}
 

void loop() {

  //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C"); 
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
 
 delay(1000);       

  // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    

    delay(100);
  // Initialize the client library
  HttpClient client;

  //Setup sensorValue to read a value from Analog Port A0
  int sensorValue = analogRead(A0);
  
  //Testing value - when sensor is not connected - comment out when sketch is shown to be working - and take value from A0 instead
  //sensorValue=1500;
  lcd.print(temperatureF);

  // Make a HTTP request:  
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=&TimeStamp=&TempC="+temperatureF; //?IDtag=$IDtag$&TimeStamp=$TimeStamp$&TempC=$TempC$
  client.get (APIRequest);
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();

  }
   Serial.flush();
  String UploadMessage;
  Serial.print("\n Uploaded Room Data: ");
  Serial.print(sensorValue);
  delay(5000);


  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Room in Use!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Room Vacant");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}





