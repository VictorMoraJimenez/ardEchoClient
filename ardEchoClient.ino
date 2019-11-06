/*

 This example connects to an WPA2 WiFi network.
 Then it prints the  MAC address of the WiFi shield,
 the IP address obtained, and other network details.

 */
#include <SPI.h>
#include <WiFi101.h>

#include "arduino_secrets.h" 

// Initialize the client library
WiFiClient client;
const char *msg_send = "Hello echo world!!!";
char *msg_receive = "";
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status
IPAddress server(192,168,10,1); //IP ECHO server

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    printWifiStatus(WiFi.status());
    // don't continue:
    while (true);
  }
}

void loop() {
  // check the network connection once every 10 seconds:
  wifiMaintainConnection();

  if (client.connect(server, 10000)) {
    Serial.println("TCP connected");
    // Write message to server:
    Serial.println("Send message");
    client.write(msg_send);
    
    delay(500);
    // Look for the response
    int i = client.available();
    Serial.print("Received: ");
    //Serial.println(client.available());
    while (client.available()){
        char c = client.read();
        Serial.print(c);
    }

    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();

    }

  }
  //printWifiStatus(WiFi.status());
  delay(10000);
}

void wifiMaintainConnection(){
 // attempt to connect to WiFi network if it's not connected:

  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    WiFi.begin(ssid, pass);

    while (WiFi.status() == WL_IDLE_STATUS){      
      // wait 1 seconds for connection:
      delay(1000);     
    }
  }
  printWifiStatus(WiFi.status());
}

void printWifiIP() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void printCurrentNet() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.println(rssi);

}

void printWifiStatus(int status) {
  // print WiFi status:
  switch (status) {
  case WL_CONNECTED:
    Serial.println("Connected to a WiFi network");
    printCurrentNet();
    break;
  case WL_NO_SHIELD:
    Serial.println("No wifi shield present");
    break;  
  case WL_IDLE_STATUS:
    Serial.println("Connecting to a WiFi network");
    break;
  case WL_NO_SSID_AVAIL:
    Serial.println("No SSID are avaible");
    break; 
  case WL_SCAN_COMPLETED:
    Serial.println("Scan completed");
    break;
  case WL_CONNECT_FAILED:
    Serial.println("Connection failed");
    break;         
  case WL_CONNECTION_LOST:
    Serial.println("Connection lost");
    break;
  case WL_DISCONNECTED:
    Serial.println("Disconnected network");
    break;
  default:
    break;
  }
}