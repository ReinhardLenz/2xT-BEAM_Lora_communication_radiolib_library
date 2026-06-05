#include <Arduino.h>
#include <RadioLib.h>
#include <SPI.h>
#include <TinyGPS++.h>

// --------------------
// ⚠️ Adjust these pins!
// --------------------
static const int LORA_NSS  = 18;   // CS
static const int LORA_DIO1 = 33;   // DIO1 (IRQ)
static const int LORA_RST  = 23;   // RESET
static const int LORA_BUSY = 32;   // BUSY

// SPI pins (ESP32 default VSPI is usually SCK=18, MISO=19, MOSI=23, but boards vary)
// If your board uses different SPI pins, you can set them with SPI.begin(SCK, MISO, MOSI, NSS).
// For many T-Beam boards, default SPI pins work if wired accordingly.

SX1262 radio = SX1262(
    new Module(
        LORA_NSS,
        LORA_DIO1,
        LORA_RST,
        LORA_BUSY
    )
);

static const float LORA_FREQ = 868.0;   // change to 915.0 if needed


void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("SX126x Sender starting...");
  SPI.begin(5, 19, 27, 18);
  // If needed, explicitly init SPI pins here:
  // SPI.begin(SCK, MISO, MOSI, LORA_NSS);

  int state = radio.begin(LORA_FREQ);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("radio.begin() failed, code = ");
    Serial.println(state);
    while (true) { delay(1000); }
  }

  // Optional: set LoRa parameters (must match receiver)
  // radio.setSpreadingFactor(7);
  // radio.setBandwidth(125.0);
  // radio.setCodingRate(5);
  // radio.setOutputPower(14); // dBm (check your module/regional limits)

  Serial.println("✅ Radio init OK");
}

void loop() {
  const char* msg = "hello";

  Serial.print("Sending: ");
  Serial.println(msg);

  int state = radio.transmit(msg);

  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("✅ TX success");
  } else {
    Serial.print("❌ TX failed, code = ");
    Serial.println(state);
  }

  delay(2000);
}