#include <FS.h> // Используем библиотеку FS
#include <SPIFFS.h> // Для совместимости со старыми версиями

void setup() {
  Serial0.begin(115200);
  
  // Инициализация файловой системы
  if (!SPIFFS.begin(true)) {
    Serial0.println("An error occurred while mounting SPIFFS");
    return;
  }

  // Запись строки в файл
  writeStringToFile("/example.txt", "Hello world");

  // Чтение строки из файла
  String readString = readStringFromFile("/example.txt");
  Serial0.println("Read from file: " + readString);
}

void loop() {
  // Ваш основной код здесь
}

void writeStringToFile(const char* path, const char* message) {
  File file = SPIFFS.open(path, "w");
  if (!file) {
    Serial0.println("Failed to open file for writing");
    return;
  }

  if (file.print(message)) {
    Serial0.println("File was written");
  } else {
    Serial0.println("Write failed");
  }

  file.close();
}

String readStringFromFile(const char* path) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial0.println("Failed to open file for reading");
    return "";
  }

  String content = file.readString();
  file.close();
  return content;
}