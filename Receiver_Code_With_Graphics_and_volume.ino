#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const float tankHeight = 15.0; // Tank height in cm
const float maxFillHeight = 15.0; // Maximum fill height in cm
const float tankRadius = 5.0; // Tank radius in cm

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // 0x3C is the I2C address of the OLED display
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void drawTank(float percentage, float volume) {
  display.clearDisplay();
  
  // Calculate water height based on percentage
  float waterHeight = map(percentage, 0, 100, 0, 50);

  // Draw the tank outline on the right side
  int tankX = SCREEN_WIDTH - 30;
  int tankY = 10;
  int tankWidthPixels = 30;
  int tankHeightPixels = 50;
  display.drawRect(tankX, tankY, tankWidthPixels, tankHeightPixels, SSD1306_WHITE);

  // Draw the water level inside the tank
  display.fillRect(tankX, tankY + (tankHeightPixels - waterHeight), tankWidthPixels, waterHeight, SSD1306_WHITE);

  // Draw the water percentage on the left side
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Water Level:");
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.print(percentage);
  display.print(" %");

  // Draw the volume below the water level percentage
  display.setCursor(0, 35);
  display.setTextSize(1);
  display.print("Volume:");
  display.setCursor(0, 45);
  display.setTextSize(2);
  display.print(volume);
  display.print(" L");

  display.display();
}

void loop() {
  if (radio.available()) {
    long distance;
    radio.read(&distance, sizeof(distance));

    float percentage = (maxFillHeight - distance) / maxFillHeight * 100.0;

    // Cap the percentage at 100% if it's above the maxFillHeight
    if (percentage > 100) {
      percentage = 100;
    }

    // Calculate the volume of water
    float waterHeightCm = percentage / 100.0 * maxFillHeight; // Height of water in cm
    float volume = 3.14159 * tankRadius * tankRadius * waterHeightCm / 1000.0; // Volume in liters

    drawTank(percentage, volume);

    Serial.print("Water Level: ");
    Serial.print(percentage);
    Serial.print(" %, Volume: ");
    Serial.print(volume);
    Serial.println(" L");
  }
  delay(1000);
}
