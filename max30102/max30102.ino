/// INCLUDES
#include <MAX3010x.h>
/// VARIABLES
MAX30105 sensor;
/// SETUP
bool setup_max30102()
{
  return sensor.begin();
}

/// TEST CODE
void test_max30102()
{
  auto sample = sensor.readSample(1000);
  Serial.print("IR: ");
  Serial.print(sample.ir);
  Serial.print(" | RED: ");
  Serial.println(sample.red);
}

/// DRIVER CODE
void setup() {
  Serial.begin(115200);
  bool result = setup_max30102();
  if (!result) Serial.println("DID NOT INITIATE MAX30102");
}

void loop() {
  // put your main code here, to run repeatedly:
  test_max30102();
  delay(10);
}
