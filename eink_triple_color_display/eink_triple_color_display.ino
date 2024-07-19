/// DOC
/// https://wiki.seeedstudio.com/Grove-Triple_Color_E-Ink_Display_2_13/

/// INCLUDES
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <Wire.h>

/// VARIABLES
#define RECV_ERROR       -1
#define CONTINUE_TRANS    0
#define RECV_DONE         1
#define SERIAL Serial1

const unsigned char IMAGE_BLACK[] PROGMEM;
const unsigned char IMAGE_RED[] PROGMEM;

/// SETUP
bool setup_eink_triple_color_display()
{
  SERIAL.begin(230400);
  return SERIAL;
}

/// TEST CODE
void serial_send_data(const uint8_t* data, uint32_t data_len) {
    for (int i = 0; i < data_len; i++) {
        SERIAL.write(pgm_read_byte(&data[i]));
    }
}

//Send image array
void write_image_picture(void) {
    for (int i = 0; i < 13; i++) {
        serial_send_data(&IMAGE_BLACK[0 + i * 212], 212);
        delay(80);
    }
    delay(90);
    for (int i = 0; i < 13; i++) {
        serial_send_data(&IMAGE_RED[0 + i * 212], 212);
        delay(80);
    }
}

//Send the start transfer command
void send_begin() {
    while (1) {
        if (SERIAL.available() > 0) {
            char str0 = SERIAL.read();
            if (str0 == 'c') {
                break;
            }
        }
    }
    char str = 'a';
    SERIAL.write(str);
    while (1) {
        if (SERIAL.available() > 0) {
            char str1 = SERIAL.read();
            if (str1 == 'b') {
                break;
            }
        }
    }
}

/// DRIVER CODE
void setup() {
    setup_eink_triple_color_display();
    delay(10);
    send_begin();
    delay(2000);
    write_image_picture();
}