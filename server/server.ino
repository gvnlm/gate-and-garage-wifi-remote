#include "WiFiS3.h"
#include "secrets.h"

constexpr char WIFI_NAME[]{SECRET_WIFI_NAME};
constexpr char WIFI_PW[]{SECRET_WIFI_PW};

constexpr int SERVER_PORT{80};
WiFiServer server(SERVER_PORT);

void setup() {
  Serial.begin(9600);

  startServer();
}

void loop() {}

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
