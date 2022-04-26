 #include <DHT.h>
int dpin=8;
DHT dht(dpin,DHT11);
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include<Wire.h>
#include "WiFiEsp.h" 
#include <SoftwareSerial.h> 
#define rxPin 3 
#define txPin 2 

SoftwareSerial esp01(txPin, rxPin); // SoftwareSerial NAME(TX, RX); 

const char ssid[] = "iptime"; // your network SSID (name) 

const char pass[] = ""; // your network password 

int status = WL_IDLE_STATUS; // the Wifi radio's status 


WiFiEspServer server(80); 


void setup() {
  mlx.begin();
  Serial.begin(9600);
  esp01.begin(9600);
  WiFi.init(&esp01); 
  while ( status != WL_CONNECTED) { 
  Serial.print(F("Attempting to connect to WPA SSID: ")); 
  Serial.println(ssid); 
  status = WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network 
  IPAddress ip = WiFi.localIP(); 
  Serial.print("IP Address: "); 
  Serial.println(ip); } 
  server.begin(); 
  dht.begin();

  } 

  void loop() { 
    float temp =mlx.readObjectTempC();
    Serial.println(temp);

  float hum=dht.readHumidity();
  float siltemp=dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("real temp: ");
  Serial.println(siltemp);

   delay(5000);

    WiFiEspClient client = server.available(); 


  if (client) { 
    while (client.connected()) {
      if (client.available()) { 
        String income_AP = client.readStringUntil('\n'); 
        client.flush(); 
         client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n" 
            "Refresh: 10\r\n"       
            "\r\n"        
            );
        client.println(); 
        String page; 
        client.print(page); 
        client.println();                    
        client.print("curling iron: ");
        client.println(temp);
        client.print("         ");     
         client.print("temperature: ");
        client.println(siltemp);
        client.print("         ");  
         client.print("hum: ");
        client.println(hum);
        delay(1); 
        break; } } 
        client.stop(); 
        Serial.println(F("Client disconnected"));
        } }
