#include "WiFiS3.h"
#include "secrets.h"

constexpr char WIFI_NAME[]{SECRET_WIFI_NAME};
constexpr char WIFI_PW[]{SECRET_WIFI_PW};

constexpr int SERVER_PORT{80};
WiFiServer server(SERVER_PORT);

constexpr pin_size_t GATE_PIN{3};
constexpr pin_size_t GARAGE_PIN{8};
constexpr int ON_TIME{500}; // Duration gate/garage remote is on when activated

void setup() {
  Serial.begin(9600);

  pinMode(GATE_PIN, OUTPUT);
  pinMode(GARAGE_PIN, OUTPUT);

  startServer();
}

void loop() {
  WiFiClient client{server.available()};

  if (client) {
    Serial.println("Client connected");
    Serial.println();

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
      powerOnThenOff(GATE_PIN, ON_TIME);
    }

    if (request.startsWith("GET /garage ")) {
      powerOnThenOff(GARAGE_PIN, ON_TIME);
    }

    client.stop();

    Serial.println("Client disconnected");
    Serial.println();
  }
}

void startServer() {
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
}

void powerOnThenOff(pin_size_t pin, int onTime) {
  digitalWrite(pin, HIGH);
  delay(onTime);
  digitalWrite(pin, LOW);
}
