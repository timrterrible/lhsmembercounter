/*
London Hackspace Membership Counter
 
 Large parts of this code are from Matt Little (info@re-innovation.co.uk / www.re-innovation.co.uk)
 Remainder butched by T Reynolds ( tim@christwithfries.net / www.appliedpraxis.com )
 
 */

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>
#include <SPI.h>

const int sLatch = A3;
const int sData = A4;
const int sClk =  A5;


void setup()
{
  Serial.begin(9600);

  pinMode(sLatch, OUTPUT);
  pinMode(sClk, OUTPUT);
  pinMode(sData, OUTPUT);  
}

void loop()
{
  //Hardcoded count to display TODO: Clever ethernet stuff.
  long int iNumber1 = 0;
  long int iNumber2 = 6;
  long int iNumber3 = 6;
  long int iNumber4 = 0;

  //Take latch low
  digitalWrite(sLatch, LOW);

  //Update display
  shiftOut(sData, sClk, MSBFIRST, iNumber4);
  shiftOut(sData, sClk, MSBFIRST, iNumber3);
  shiftOut(sData, sClk, MSBFIRST, iNumber2); 
  shiftOut(sData, sClk, MSBFIRST, iNumber1); 

  //Take latch high
  digitalWrite(sLatch, HIGH);

  //Echo to serial
  String sNumber1 = String(iNumber1);
  String sNumber2 = String(iNumber2);
  String sNumber3 = String(iNumber3);
  String sNumber4 = String(iNumber4);
  String sDisplay =  String(sNumber1 + sNumber2 + sNumber3 + sNumber4);
  Serial.println(sDisplay);

  //Wait 1 sec
  delay(1000);
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
