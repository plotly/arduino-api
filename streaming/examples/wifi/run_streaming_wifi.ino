#include <WiFi.h>
#include "plotly_streaming_wifi.h"


// arguments: username, api key, streaming token, filename
// e.g. plotly graph("my_username", "abcdefghij", "ABCDEFGHIJ", "My plotly filename"); 
// Sign up to plotly here: https://plot.ly
// View your API key and streamtokens here: https://plot.ly/settings
char *tokens[] = {"8xdfnkq1nb","xtndiqvpol"};
plotly graph("streaming-demos", "3yyglqsi85", tokens, "filename");


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

void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  wifi_connect();


  graph.begin();

  unsigned long x = millis();
  int y = analogRead(A0);
  graph.plot(x, y, tokens[0]);
  graph.plot(x, y+5, tokens[1]);

}

void loop() {}
