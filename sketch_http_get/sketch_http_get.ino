#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = ""; // Логин сети
const char *password = ""; // Пароль сети
const char *url = ""; // Нужный URL

void setup() {
  Serial0.begin(115200);

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial0.println("Connecting to WiFi...");
  }
  Serial0.println("Connected to WiFi");

  // Отправка HTTP GET запроса
  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();

  if (httpCode > 0) {
    // Получение данных
    String payload = http.getString();
    Serial0.println(payload);
  } else {
    Serial0.printf("HTTP request failed with error code: %d\n", httpCode);
  }

  http.end(); // Завершение сеанса HTTP

  // Пауза перед перезапуском
  delay(5000);
  ESP.restart();
}

void loop() {
}