% if lib=="ethernet":
#include <SPI.h>
#include <Ethernet.h>
#include "plotly_streaming_ethernet.h"
% elif lib=="wifi":
#include <WiFi.h>
#include "plotly_streaming_wifi.h"
% elif lib=="cc3000":
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <plotly_streaming_cc3000.h>

#define WLAN_SSID       "StationC"
#define WLAN_PASS       "stationcgaspe"
#define WLAN_SECURITY   WLAN_SEC_WPA2
% elif lib=="gsm":
#include <GSM.h>
#include "plotly_streaming_gsm.h"
% endif


// arguments: username, api key, streaming token, filename
// e.g. plotly graph("my_username", "abcdefghij", "ABCDEFGHIJ", "My plotly filename"); 
// Sign up to plotly here: https://plot.ly
// View your API key and streamtokens here: https://plot.ly/settings
char *tokens[] = {"8xdfnkq1nb","xtndiqvpol"};
plotly graph("streaming-demos", "3yyglqsi85", tokens, "filename");


% if lib=="wifi":
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char ssid[] = "wifi_network_name"; //  your network SSID (name) 
char pass[] = "wifi_password"; // // your network password

void wifi_connect(){
    // attempt to connect using WPA2 encryption:
    Serial.println("... Attempting to connect to WPA network...");
    status = WiFi.begin(ssid, pass);
    // if you're not connected, stop here:
    if ( status != WL_CONNECTED) { 
      Serial.println("... Couldn't get a WiFi connection, trying again");
      wifi_connect();
    } 
    // if you are connected, print out info about the connection:
    else {
      Serial.println("... Connected to network");
    }
}
% elif lib=="ethernet":
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte my_ip[] = { 199, 168, 222, 18 }; // google will tell you: "public ip address"

void startEthernet(){
    Serial.println("... Initializing ethernet");
    if(Ethernet.begin(mac) == 0){
        Serial.println("... Failed to configure Ethernet using DHCP");
        // no point in carrying on, so do nothing forevermore:
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, my_ip);
    }
    Serial.println("... Done initializing ethernet");
    delay(1000);
}

% elif lib=="cc3000":
void wifi_connect(){
  /* Initialise the module */
  Serial.println(F("\n... Initializing..."));
  if (!graph.cc3000.begin())
  {
    Serial.println(F("... Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  // Optional SSID scan
  // listSSIDResults();
  
  if (!graph.cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("... Connected!"));
  
  /* Wait for DHCP to complete */
  Serial.println(F("... Request DHCP"));
  while (!graph.cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }
}

% elif lib=="gsm":
void gsm_connect(){
  // ...
}
% endif

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  % if lib=="wifi":
  wifi_connect();
  % elif lib=="ethernet":
  startEthernet();
  % elif lib=="cc3000":
  wifi_connect();
  %elif lib=="gsm":
  gsm_connect();
  % endif


  graph.begin();

  unsigned long x = millis();
  int y = analogRead(A0);
  graph.plot(x, y, tokens[0]);
  graph.plot(x, y+5, tokens[1]);

}

void loop() {}
