#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
//tx:9,rx:10

//DIP WHOLE SENSOR IN WATER
int pin1=8;

int humid1=700;
int humid2=400;
int ms=0;

void setup() {
  // put your setup code here, to run once:
   mySerial.begin(9600);   // Setting the baud rate of GSM Module 
  Serial.begin(9600);
pinMode(pin1,OUTPUT);
digitalWrite(pin1,HIGH);


  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:

  int value1=analogRead(A1);
Serial.println(value1);

String str="";
str=readsms_master();
/*
if(str.length()==2){
  digitalWrite(pin1,LOW);
ms=0;
SendMessage(value1,ms);
delay(30000);
}

if(str.length()==3){
  digitalWrite(pin1,LOW);
ms=0;
SendMessage(value1,ms);
delay(30000);
}*/

if(value1>700 && value1<400){
  //do nothing
  }
  
else{

if(value1>700 ||(value1<400&& str.length()==2))//motor onn
{Serial.println("hi");
digitalWrite(pin1,LOW);
ms=0;
SendMessage(value1,ms);
  //      deletemsg();

delay(10000);
  //  deletemsg();

}

if(value1<400 || (value1>700&&str.length()==3))//motor off
{
  
  digitalWrite(pin1,HIGH);
  ms=1;
  SendMessage(value1,ms);
  //  deletemsg();
  

  delay(10000);
     // deletemsg();

}


}


}

void SendMessage(int val,int motor_status)
{
  String msg="";
  if(motor_status==0)
    msg="ON";
    else
    msg="OFF";
    
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919910077157\"\r"); // Replace x with mobile number
  delay(1000);
  
  if(val>700){
  mySerial.println("moisture level:"+(String)val+"(LOW),"+"motor is "+msg+", send ON/OFF to toggle motor");// The SMS text you want to send
   
  }

 if(val<400){
  mySerial.println("moisture level:"+(String)val+"(HIGH),"+"motor is "+msg+", send ON/OFF to toggle motor");// The SMS text you want to send
   
  }
  
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);

}

String readsms_master()
{
  int done=0;
  String higher_value="";
  String lower_value="";
   int flag=1;
  mySerial.println("AT+CMGF=1\r\n"); // AT Command to receive a live SMS
    Serial.write(mySerial.read());
    int x=0;
    while(!mySerial.find("OK"))
    {
      if(x>15)
      {
        return;
      }
      x++;
    }
    mySerial.flush();
    x=0;
  mySerial.println("AT+CPMS=\"SM\"\r\n");
    Serial.write(mySerial.read());
    while(!mySerial.find("CPMS"))
    {
      if(x>10)
      {
        return;
      }
      x++;
    }
   // Serial.print("second achived");
    mySerial.flush();
  mySerial.println("AT+CMGL=\"ALL\"\r\n");
char cString[14];
//master_no.toCharArray(cString, master_no.length() + 1);
Serial.write(mySerial.read());
 String k=mySerial.readString();
 Serial.println(k);
 Serial.println(k.length());
     mySerial.flush();

   deletemsg();
  if(k.length()==118||k.length()==116||k.length()==102)
  return "on";
  if(k.length()==119||k.length()==117||k.length()==103)
  return "off";

  return "";
     
}

void deletemsg(){

int x=0;
    mySerial.flush();

     mySerial.println("AT+CMGD=1,4\r\n");
  Serial.write(mySerial.read());
    while(!mySerial.find("OK"))
    {
      if(x>10)
      {
        return;
      }
      x++;
    }}

