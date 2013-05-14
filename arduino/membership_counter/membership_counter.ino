/*
London Hackspace Membership Counter
 
 LED Segment shifting, displaydata, etc are from Matt Little (info@re-innovation.co.uk / www.re-innovation.co.uk)
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

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

unsigned int localPort = 8888;

EthernetUDP UDP;

void setup()
{

  pinMode(sLatch, OUTPUT);
  pinMode(sClk, OUTPUT);
  pinMode(sData, OUTPUT);

  Serial.begin(9600);
  Serial.println("Membership counter starting up.");

  Serial.print("Attempting to get IP via DHCP...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("failed.");
    Serial.println("Unable to configure Ethernet using DHCP, halting.");
    for(;;)
      ;
  } 
  else {
    Serial.println("done.");
    Serial.print("IP address: ");
    for (byte thisByte = 0; thisByte < 4; thisByte++) {
      Serial.print(Ethernet.localIP()[thisByte], DEC);
      Serial.print("."); 
    }
  }

  Serial.println();

  Serial.print("Starting listener on port ");
  Serial.print(localPort);
  Serial.print("...");
  Serial.println();

  UDP.begin(localPort);
}

void loop()
{

  long int iNumber1 = random(0,9);
  long int iNumber2 = random(0,9);
  long int iNumber3 = random(0,9);
  long int iNumber4 = random(0,9);

  String sPre = "Currently London Hackspace has ";
  String sPost = " members.";
  String sNumber1 = String(iNumber1);
  String sNumber2 = String(iNumber2);
  String sNumber3 = String(iNumber3);
  String sNumber4 = String(iNumber4);
  String sDisplay =  String(sPre + sNumber1 + sNumber2 + sNumber3 + sNumber4 + sPost);
  Serial.println(sDisplay);

  digitalWrite(sLatch, LOW);

  shiftOut(sData, sClk, MSBFIRST, iNumber4);
  shiftOut(sData, sClk, MSBFIRST, iNumber3);
  shiftOut(sData, sClk, MSBFIRST, iNumber2);   
  shiftOut(sData, sClk, MSBFIRST, iNumber1); 

  digitalWrite(sLatch, HIGH);

  delay(1000);
}

int int7segment (int segmentData)
{
  int displayData = B11111100;


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




