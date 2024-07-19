// INSPIRED BY https://github.com/ElectronicCats/mpu6050

// INCLUDES
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// VARIABLES FOR RAW INPUT
MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
#define OUTPUT_READABLE_ACCELGYRO // uncomment for human-readable content
//#define OUTPUT_BINARY_ACCELGYRO // uncomment for 16bit binary, as-fast-as-possible but illegible content

// DEBUG
bool blinkState = false;

// SETUP CODE
bool setup_mpu6050()
{
  // Connect to pins:
  //    -- PICO --
  //    SDA = Pin 6
  //    SCL = Pin 7
  //    -- NANO IOT --
  //    SDA = Pin A4
  //    SCL = Pin A5
  if (I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE)
        Wire.begin();
  
  // Initialize Device
  accelgyro.initialize();
  return accelgyro.testConnection();
}

// TEST CODE
void test_mpu6050()
{
  // gets data
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // display data
  #ifdef OUTPUT_READABLE_ACCELGYRO
      Serial.print("a/g:\t");
      Serial.print(ax); Serial.print("\t");
      Serial.print(ay); Serial.print("\t");
      Serial.print(az); Serial.print("\t");
      Serial.print(gx); Serial.print("\t");
      Serial.print(gy); Serial.print("\t");
      Serial.println(gz);
  #endif

  #ifdef OUTPUT_BINARY_ACCELGYRO
      Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
      Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
      Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
      Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
      Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
      Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
  #endif

  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_BUILTIN, blinkState);
}

// DRIVER CODE
void setup() {
  Serial.begin(115200);
  bool result = setup_mpu6050();
  if (!result) Serial.println("MPU NOT INITIALIZED!");
}

void loop() {
  test_mpu6050();
  delay(100);
}