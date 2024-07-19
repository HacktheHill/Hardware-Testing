// INSPIRED FROM https://github.com/usefulsensors/person_sensor_arduino

// INCLUDES
#include <Wire.h>
#include "person_sensor.hpp"

// VARIABLES
// How long to wait between reading the sensor. The sensor can be read as
// frequently as you like, but the results only change at about 5FPS, so
// waiting for 200ms is reasonable.
const int32_t SAMPLE_DELAY_MS = 200;

// SETUP
void setup_person_sensor()
{
  // You need to make sure you call Wire.begin() in setup, or the I2C access
  // below will fail.
  // Connect to pins:
  //    -- PICO --
  //    SDA = Pin 6
  //    SCL = Pin 7
  //    -- NANO IOT --
  //    SDA = Pin A4
  //    SCL = Pin A5
  Wire.begin();
}

// TEST CODE
void test_person_sensor()
{
  person_sensor_results_t results = {};
  // Perform a read action on the I2C address of the sensor to get the
  // current face information detected.
  if (!person_sensor_read(&results)) {
    Serial.println("No person sensor results found on the i2c bus");
    delay(SAMPLE_DELAY_MS);
    return;
  }

  Serial.println("********");
  Serial.print(results.num_faces);
  Serial.println(" faces found");
  for (int i = 0; i < results.num_faces; ++i) {
    const person_sensor_face_t* face = &results.faces[i];
    Serial.print("Face #");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(face->box_confidence);
    Serial.print(" confidence, (");
    Serial.print(face->box_left);
    Serial.print(", ");
    Serial.print(face->box_top);
    Serial.print("), (");
    Serial.print(face->box_right);
    Serial.print(", ");
    Serial.print(face->box_bottom);
    Serial.print("), ");
    if (face->is_facing) {
      Serial.println("facing");
    } else {
      Serial.println("not facing");
    }
  }
}

// CALLBACK CODE
void callback_person_sensor(void (*callback_found)(person_sensor_results_t), void (*callback_not_found)() )
{
  person_sensor_results_t results = {};
  if (!person_sensor_read(&results) || results.num_faces <= 0) {
    callback_not_found();
    return;
  }

  callback_found(results);
}

void notfound()
{
  Serial.println("NOTHING FOUND");
}

void found(person_sensor_results_t results)
{
  Serial.print(results.num_faces);
  Serial.println(" faces found!");
}

// DRIVER CODE
void setup() {
  setup_person_sensor();
  Serial.begin(115200);
}

void loop() {
  callback_person_sensor(&found, &notfound);
  delay(SAMPLE_DELAY_MS);
}