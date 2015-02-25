/****************************************************************
BadgerHack_Breakout.ino

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, please
buy us a round!

Distributed as-is; no warranty is given.
****************************************************************/

#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>

// Constants
#define DEBUG          1
#define FPS            60
#define SENSITIVITY    100
#define X_MAX          127        

// Pin definitions
#define RNG_SEED_PIN  2
#define X_PIN         0
#define Y_PIN         1
#define BUTTON_1_PIN  3
#define BUTTON_2_PIN  4

// Global variables
byte led_pins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pins for LEDs
uint16_t horz_zero;
uint16_t vert_zero;

// Setup
void setup() {
  
#if DEBUG
  Serial.begin(9600);
  Serial.println(F("Breakout demo for BadgerHack"));
#endif

  // Initialize and clear display
  Plex.init(led_pins);
  Plex.clear();
  Plex.display();
  
  // Seed our random number generator
  randomSeed(analogRead(2));
  
  // Calibrate our joystick by finding the center
  horz_zero = analogRead(X_PIN);
  vert_zero = analogRead(Y_PIN);
}

// Loop - play the game forever
void loop() {
  
  // Play the game inifinity times
  playGame();
}

/****************************************************************
 * Functions
 ***************************************************************/

// Play the game
void playGame() {
  
  boolean playing = true;
  unsigned long frame_start;
  uint8_t millis_per_frame = 1000/FPS;
  int16_t paddle_move;
  int16_t paddle_x = X_MAX / 2;
  
  while ( playing ) {
    
    // For each frame, aim for refresh rate
    frame_start = millis();
    
    // Read the value of the joystick and map to a movement
    paddle_move = analogRead(X_PIN) - horz_zero;
    paddle_move = paddle_move / SENSITIVITY;
#if DEBUG
    Serial.print("Moving: ");
    Serial.println(paddle_move);
#endif
    
    // Move the paddle, but don't go past the edges
    paddle_x = paddle_x + paddle_move;
    if ( paddle_x <= 0 ) {
      paddle_x = 0;
    }
    if ( paddle_x >= X_MAX ) {
      paddle_x = X_MAX;
    }
    
    // Draw the paddle
    Plex.clear();
    Plex.pixel(7, map(paddle_x, 0, X_MAX, 6, 0));
    Plex.display();
    
    // Wait until we reach our target end of frame
    while ( millis() < frame_start + millis_per_frame ) {
      delay(1);
    }
 #if 0
   Serial.print("FPS: ");
   Serial.println( 1000 / (millis() - frame_start) );
 #endif
  
  }
}
