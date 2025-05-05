#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT11.h>

DHT11 dht11(18);

const char* wifiname = "IoT"; //your WiFi name
const char* password = "IoT@1234"; //Your WiFi password

// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update"; //https://api.thingspeak.com/update

// write API Key provided by thingspeak
String apiKey = "OEAIEWIFRQ7RFP6V";//your write API key

void setup() {

  Serial.begin(115200);
  WiFi.begin(wifiname, password);

  Serial.println("Connecting");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      delay(1000); // wait for 10 seconds

      int temperature = 0;
      int humidity = 0;
      int result = dht11.readTemperatureHumidity(temperature, humidity);

      if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
        delay(2000);
      } else {
          // Print error message based on the error code.
          Serial.println(DHT11::getErrorString(result));
      }

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Data to send with HTTP POST
      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(temperature);          

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      http.end();

    }

    else {
      Serial.println("WiFi Disconnected");
    }
}
