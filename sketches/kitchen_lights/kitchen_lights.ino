#include <Adafruit_NeoPixel.h>

#define DATA_PIN 6

#define RED Adafruit_NeoPixel::Color(255, 0, 0)
#define GREEN Adafruit_NeoPixel::Color(0, 255, 0)
#define BLUE Adafruit_NeoPixel::Color(0, 0, 255)
#define ORANGE Adafruit_NeoPixel::Color(150, 255, 0)
#define PINK Adafruit_NeoPixel::Color(200, 0, 255)
#define TEAL Adafruit_NeoPixel::Color(0, 255, 50)
#define BLACK Adafruit_NeoPixel::Color(0, 0, 0)

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

int num_pixels = 57;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(num_pixels, DATA_PIN, NEO_GRB + NEO_RGB);

// char[] mode = "MONO-RED";

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {

// @TODO: add serial communication for raspberry pi control.
  // if (Serial.available() > 0) {
  //     char inChar = Serial.read();
  //     if (inChar == (int) 'r') {
  //     }
  // }

  color_wipe(RED, 30);
  color_wipe(GREEN, 30);
  color_wipe(BLUE, 30);
  color_wipe(ORANGE, 30);
  color_wipe(PINK, 30);
  color_wipe(TEAL, 30);

  fade(TEAL, RED, 10);
  delay(1000);
  fade(RED, GREEN, 10);
  delay(1000);
  fade(GREEN, BLUE, 10);
  delay(1000);
  fade(BLUE, ORANGE, 10);
  delay(1000);
  fade(ORANGE, PINK, 10);
  delay(1000);

  shuttle(ORANGE, BLUE, 20);
  shuttle(ORANGE, BLUE, 20);
  shuttle(ORANGE, BLUE, 20);
  shuttle(ORANGE, BLUE, 20);
  
  // double_shuttle(GREEN, RED, 20);
  // double_shuttle(GREEN, RED, 20);
  // double_shuttle(GREEN, RED, 20);
  // double_shuttle(GREEN, RED, 20);

  // stack(GREEN, RED, 20);
}

void set_color(uint32_t c) {
  set_section_color(0, num_pixels, c);
}

void set_section_color(int start, int end, uint32_t c) {
  for (uint16_t i = start; i < end; i++) {
    strip.setPixelColor(i, c);
  }
  
  strip.show();
}

void flash(uint32_t c) {
  set_color(c);
  delay(200 );

  set_color(BLACK);
  delay(200 );
}

void multi_flash(uint32_t c, int count) {
  for (int i = 0; i < count; i++) {
    flash(c);
  }
}

void flash_all(int count) {
  multi_flash(RED, count);
  multi_flash(GREEN, count);
  multi_flash(BLUE, count);
  multi_flash(ORANGE, count);
  multi_flash(PINK, count);
  multi_flash(TEAL, count);
}

void color_wipe(uint32_t c, uint8_t wait) {
  for (int i = 0; i < num_pixels; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void shuttle(uint32_t background, uint32_t shuttle, uint8_t wait) {
  set_color(background);

  for (int i = 0; i < num_pixels; i++) {
    strip.setPixelColor(i, shuttle);
    strip.setPixelColor(i + 1, shuttle);
    strip.setPixelColor(i + 2, shuttle);
    strip.setPixelColor(i - 1 % num_pixels, background);

    strip.show();
    delay(wait);
  }
}

void double_shuttle(uint32_t background, uint32_t shuttle, uint8_t wait) {
  set_color(background);

  for (int i = 0; i < num_pixels; i++) {
    strip.setPixelColor(i, shuttle);
    strip.setPixelColor(i + 1, shuttle);
    strip.setPixelColor(i + 2, shuttle);
    strip.setPixelColor(i - 1 % num_pixels, background);

    strip.setPixelColor(num_pixels - i, shuttle);
    strip.setPixelColor(num_pixels - i - 1, shuttle);
    strip.setPixelColor(num_pixels - i - 2, shuttle);
    strip.setPixelColor(num_pixels - i + 1 % num_pixels, background);

    strip.show();
    delay(wait);
  }
}

void stack(uint32_t background, uint32_t stack, uint8_t wait) {
  for (int i = 0; i < num_pixels; i++) {
    set_color(background);
    set_section_color(0, i, stack);

    for (int j = num_pixels; j > i; j--) {
      strip.setPixelColor(j, stack);
      strip.setPixelColor((j - 1), stack);
      strip.setPixelColor((j - 2), stack);
      set_section_color(j + 1, num_pixels, background);

      strip.show();
      delay(wait);
    }
  }
}

void fade(uint32_t from, uint32_t to, uint8_t wait) {
  float from_r = (float) (uint8_t) (from >> 16),
      from_g = (float) (uint8_t) (from >> 8),
      from_b = (float) (uint8_t) from;

  float to_r = (float) (uint8_t) (to >> 16),
      to_g = (float) (uint8_t) (to >> 8),
      to_b = (float) (uint8_t) to;

  float steps = 100;

  float delta_r = get_fade_delta(from_r, to_r, steps),
      delta_g = get_fade_delta(from_g, to_g, steps),
      delta_b = get_fade_delta(from_b, to_b, steps);

  for (int i = 0; i < steps; i++) {
    from_r = from_r + delta_r;
    from_g = from_g + delta_g;
    from_b = from_b + delta_b;

    uint32_t c = Adafruit_NeoPixel::Color((uint8_t) from_r, (uint8_t) from_g, (uint8_t) from_b);
    set_color(c);
    delay(wait);
  }
}

float get_fade_delta(float from, float to, float steps) {
  return (float) ((to - from) / steps);
}
