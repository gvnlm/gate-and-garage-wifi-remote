#include "Arduino_LED_Matrix.h"
#include "animations.h"
#include "WiFiS3.h"
#include "secrets.h"
#include <Servo.h>

ArduinoLEDMatrix led_matrix{};
constexpr uint32_t CLEAR[] = {0, 0, 0}; // Empty frame to clear the LED matrix

constexpr char WIFI_NAME[]{SECRET_WIFI_NAME};
constexpr char WIFI_PW[]{SECRET_WIFI_PW};
constexpr int PORT{80};
WiFiServer server(PORT);

Servo servo{};
constexpr pin_size_t SIGNAL_PIN{12};
constexpr int REST_ANGLE{83};
constexpr int GATE_ANGLE{REST_ANGLE + 35}; // Angle needed to press gate remote
constexpr int GARAGE_ANGLE{REST_ANGLE - 49}; // Angle needed to press garage remote
constexpr int PRESS_DURATION{200};

void setup() {
  Serial.begin(9600);
  led_matrix.begin();

  servo.attach(SIGNAL_PIN);
  servo.write(REST_ANGLE);

  startServer();
}

void loop() {
  WiFiClient client{server.available()};

  if (client) {
    Serial.println("Client connected");
    Serial.println();
    
    // Play request animation once
    led_matrix.loadSequence(requestAnimation);
    led_matrix.play(false);

    String request{""};

    while (client.connected()) {
      if (client.available()) {
        request += static_cast<char>(client.read());
      }

      // If reached end of request header
      if (request.endsWith("\r\n\r\n")) {
        Serial.print(request);

        // Respond to request
        client.println("HTTP/1.0 204 No Content");
        client.println();

        break;
      }
    }

    if (request.startsWith("GET /gate ")) {
      press(GATE_ANGLE);
    }

    if (request.startsWith("GET /garage ")) {
      press(GARAGE_ANGLE);
    }

    client.stop();

    Serial.println("Client disconnected");
    Serial.println();

    // Allow time for request animation to complete before clearing LED matrix
    delay(500);
    led_matrix.loadFrame(CLEAR);
  }
}

void startServer() {
  // Loop WiFi animation
  led_matrix.loadSequence(wifiAnimation);
  led_matrix.play(true);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("ERROR: No WiFi module found");
    while (true)
      ;
  }

  int status{WL_IDLE_STATUS};

  while (status != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(WIFI_NAME);
    Serial.println("...");
    Serial.println();

    status = WiFi.begin(WIFI_NAME, WIFI_PW);
    delay(10000);

    if (status != WL_CONNECTED) {
      Serial.print("Failed to connect to ");
      Serial.println(WIFI_NAME);
      Serial.println();
    }
  }

  Serial.print("Successfully connected to ");
  Serial.println(WIFI_NAME);
  Serial.println();

  server.begin();

  Serial.print("Server running at http://");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Play tick animation once
  led_matrix.loadSequence(tickAnimation);
  led_matrix.play(false);
  delay(1500);

  // Stop WiFi animation loop
  led_matrix.loadFrame(CLEAR);
}

void press(int angle) {
  servo.write(angle);
  delay(PRESS_DURATION);
  servo.write(REST_ANGLE);
}
