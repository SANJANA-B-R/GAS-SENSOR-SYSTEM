#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(3, OUTPUT);
  pinMode(5, INPUT);
  pinMode(7, OUTPUT);
  lcd.init(); 
}

void loop()
{
 int a=0;
 a=digitalRead(5);
   if(a==0) 
    {   
      lcd.backlight();
      lcd.setCursor(1,0);
      lcd.print(" GAS LEAKAGE!");
      lcd.setCursor(0,1);
      lcd.print("   EMERGENCY!  ");

      digitalWrite(7,HIGH);
      digitalWrite(3,HIGH);
      delay(500);
      digitalWrite(3,LOW);
      delay(200);
      digitalWrite(3,HIGH);
      delay(500);
      digitalWrite(3,LOW);
      delay(200);
      
      SendMessage();
     }
   if(a==1)
   {
     lcd.backlight();
     lcd.setCursor(1,0);
     lcd.print("    NORMAL     ");
     lcd.setCursor(0,1);
     lcd.print("    WORKING!     "); 
     digitalWrite(7,LOW);
     digitalWrite(3,LOW);
   }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}

 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918304856647\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("GAS Leakage!!! EMERGENCY.");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(10000);
 }
