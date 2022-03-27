/*
 * Keyboard code for RaveBeast (see https://github.com/flamepygmy/RaveBeast)
 * (c) 2022- Jani Vaarala
 * 
 * This source code released under MIT license.
 *
 */

/* Smaller value, less latency but higher change of multiple transitions instead of just one */
#define DEBOUNCE_TIME_IN_MS 25

#define NUM_KEYS            23

#include <Keyboard.h>

// Change your keymapping here to your liking, this is like this because historically my key bindings have been like this for Destiny 2
static int pintokeymapping[] =
{
  15, KEY_TILDE,     // 1st row left
  16, KEY_1,         // 1st row 2nd from left
  17, KEY_2,         // 1st row middle
  18, KEY_3,         // 1st row 2nd from right
  19, KEY_4,         // 1st row right

  10, KEY_TAB,       // 2nd row left
  11, KEY_Q,         // 2nd row 2nd from left
  12, KEY_W,         // 2nd row middle
  13, KEY_E,         // 2nd row 2nd from right
  14, KEY_R,         // 2nd row right

  5, KEY_CAPS_LOCK,  // 3rd row left
  6, KEY_A,          // 3rd row 2nd from left
  7, KEY_S,          // 3rd row middle
  8, KEY_D,          // 3rd row 2nd from right
  9, KEY_F,          // 3rd row right

  0, KEY_LEFT_SHIFT, // 4th row left
  1, KEY_Z,          // 4th row 2nd from left
  2, KEY_X,          // 4th row middle
  3, KEY_C,          // 4th row 2nd from right
  4, KEY_V,          // 4th row right
  
  21, KEY_5,         // thumb section - top
  22, KEY_6,         // thumb section - middle
  20, KEY_7          // thumb section - bottom
};

bool          current_stable_keystate[NUM_KEYS];                     // false = not pressed, true = pressed
unsigned long timestamp_oldest_state_change_with_same_sample_value[NUM_KEYS];  // 0 = no current active state change sample

void setup()
{
  int i;
  for(i=0;i<NUM_KEYS;i++)
  {
    int pin = pintokeymapping[i*2];

#if defined(ARDUINO_ARCH_STM32F1)
    pinMode(pin, (WiringPinMode)INPUT_PULLUP);
#else
    pinMode(pin, INPUT_PULLUP);
#endif
  }

  delay(1000);

  for(i=0;i<NUM_KEYS;i++)
  {
    int pin = pintokeymapping[i*2];
    current_stable_keystate[i]                              = digitalRead(pin);
    timestamp_oldest_state_change_with_same_sample_value[i] = 0;
  }
}

void loop()
{
  for(int i=0;i<NUM_KEYS;i++)
  {
    unsigned long timestamp;
    unsigned long delta;

    int           pin                  = pintokeymapping[i*2];
    unsigned char current_stable_state = current_stable_keystate[i];
    bool          current_state        = digitalRead(pin);

    unsigned long loopmillis = millis();

    if(current_state != current_stable_state)
    {
      // possibly bouncing to a new stable state
      timestamp = timestamp_oldest_state_change_with_same_sample_value[i];
      if(timestamp == 0)
      {
        // this is first sample of the new stable state
        timestamp_oldest_state_change_with_same_sample_value[i] = loopmillis;
      }
      else
      {
        // this wasn't the first sample that is different from the current stable state, check our time window
        delta = loopmillis - timestamp;
        if(delta > DEBOUNCE_TIME_IN_MS)
        {
          // we've been stable long enough, mark it as a new stable state
          current_stable_keystate[i]                              = current_state;
          timestamp_oldest_state_change_with_same_sample_value[i] = 0;

          if(current_state)
          { 
            // emit key pressed
            Keyboard.release(pintokeymapping[i*2+1]);
          }
          else
          {
            // emit key released
            Keyboard.press(pintokeymapping[i*2+1]);
          }
        }
      }
    }
    else
    {
      // if current state is the same as stable state, then nothing has changed or we just came back down during bouncing
      // in either case we must reset timestamp
      timestamp_oldest_state_change_with_same_sample_value[i] = 0;
    }
  }
}
