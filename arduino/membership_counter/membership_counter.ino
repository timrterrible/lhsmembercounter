/*
London Hackspace Membership Counter
 
 Large parts of this code are from Matt Little (info@re-innovation.co.uk / www.re-innovation.co.uk)
 */

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

const int sLatch = A3;
const int sData = A4;
const int sClk =  A5;

long int number1 = 0;
long int number2 = 0;
long int number3 = 0;
long int number4 = 0;  


void setup()
{
  Serial.begin(9600);

  pinMode(sLatch, OUTPUT);
  pinMode(sClk, OUTPUT);
  pinMode(sData, OUTPUT);  
}

void loop()
{
  digitalWrite(sLatch, LOW);

  shiftOut(sData, sClk, MSBFIRST, number4);
  shiftOut(sData, sClk, MSBFIRST, number3);
  shiftOut(sData, sClk, MSBFIRST, number2); 
  shiftOut(sData, sClk, MSBFIRST, number1); 

  digitalWrite(sLatch, HIGH);

  Serial.println(i);
  Serial.println(number1);
  Serial.println(number2);
  Serial.println(number3);
  Serial.println(number4);

  delay(100);   
}

int int7segment (int segmentData)
{
  int displayData;

  switch (segmentData)
  {
  case 0:
    displayData = B11111100;  // The number 0 in binary   
    break;
  case 1:
    displayData = B01100000;  // The number 1 in binary   
    break;
  case 2:
    displayData = B11011010;  // The number 2 in binary   
    break;
  case 3:
    displayData = B11110010;  // The number 3 in binary   
    break;
  case 4:
    displayData = B01100110;  // The number 4 in binary   
    break;
  case 5:
    displayData = B10110110;  // The number 5 in binary   
    break;
  case 6:
    displayData = B10111110;  // The number 6 in binary   
    break;
  case 7:
    displayData = B11100000;  // The number 7 in binary   
    break;
  case 8:
    displayData = B11111110;  // The number 8 in binary   
    break;
  case 9:
    displayData = B11110110;  // The number 9 in binary
    break; 
  case 10:
    displayData = B00000001;  // Decimal point ON  
    break;

  }
  return displayData;
}

