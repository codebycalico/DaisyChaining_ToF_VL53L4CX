#include <FastLED.h>

#define LED_STRIP_PIN 5

// Total number of LEDS in strip, then divided into sections by tube.
#define NUM_LEDS_TOTAL 20
#define NUM_LEDS_TUBE_1 10
#define NUM_LEDS_TUBE_2 10

// Define the array of LEDs for the entire strip.
CRGBArray <NUM_LEDS_TOTAL> ledStrip;

// Split the LED strip array into specific sections
// coordinating to each section filled up by reaching the
// top of each tube.
CRGB* tube1_array = &ledStrip[0];
CRGB* tube2_array = &ledStrip[NUM_LEDS_TUBE_1];

void setupLEDStrip() {
    // Initialize LED strip.
    FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(ledStrip, NUM_LEDS_TOTAL);

    // Set brightness to full and the full LED strip to "black" (off).
    FastLED.setBrightness(255);
    fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
    FastLED.show();
}

// Function to light up specific sections of the total LED strip
// based on how many tubes have been completed.
void lightSections(uint8_t tubesCompleted) {
    switch(tubesCompleted) {
        // No tubes have been completed.
        case 0:
            fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
            FastLED.show();
            break;
        
        // The first tube has been completed.
        case 1:
            fill_solid(tube1_array, NUM_LEDS_TUBE_1, CRGB::Red);
            fill_solid(tube2_array, NUM_LEDS_TUBE_2, CRGB::Black);
            FastLED.show();
            break;

        // The second tube has been completed.
        case 2:
            fill_solid(tube1_array, NUM_LEDS_TUBE_1, CRGB::Red);
            fill_solid(tube2_array, NUM_LEDS_TUBE_2, CRGB::Red);
            FastLED.show();
            break;

        // Default state is turning the full LED strip off.
        default:
            fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
            break;
    }
}

void gameCompleted() {
    fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
    FastLED.show();

    for(int i = 0; i < NUM_LEDS_TOTAL; i++) {
        ledStrip[i] = CRGB::Red;
        FastLED.show();
        delay(50);
    }

    for(int i = 0; i < NUM_LEDS_TOTAL; i++) {
        ledStrip[i] = CRGB::Black;
        FastLED.show();
        delay(50);
    }

    for(int i = 0; i < 3; i++) {
        fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Red);
        FastLED.show();
        delay(100);
    
        fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
        FastLED.show();
        delay(100);
    }
}