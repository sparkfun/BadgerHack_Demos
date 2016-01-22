/**
 * BadgerHack Sensor add on kit
 * Sarah Al-Mutlaq @ SparkFun Electronics
 * January 22, 2016
 * 
 * Scrolls temp reading and soil moisture across the Badger's LED array.
 * 
 * License: http://opensource.org/licenses/MIT
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *NOTE: for this add on kit, you will want to power the badger
 *through its USB port, so that you know you have 3.3V instead 
 *of an unknown amount from a battery pack, which would make 
 *the temperature reading less accurate. 
 */

#include <SparkFun_LED_8x7.h>
#include <Chaplex.h>



// Global variables
static byte led_pins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pins for LEDs
const int moisturePin = A0;     //signal pin from the moisture sensor
                                //is hooked up to pin A0 on the badger
const int temperaturePin = A4;  //singnal pin from temp sensor is 
                                //hooked up to pin A4 of the badger        

void setup() {
  
  // Initialize LED array
  Plex.init(led_pins);

  // Clear display
  Plex.clear();
  Plex.display();
}

void loop() {
  
  float voltage;

  // First we'll measure the voltage at the temperature analog pin. Normally
  // we'd use analogRead(), which returns a number from 0 to 1023.
  // Here we've written a function (further down) called
  // getVoltage() that returns the true voltage (0 to 5 Volts)
  // present on an analog input pin.

  voltage = getVoltage(temperaturePin);

  // Now we'll convert the voltage to degrees Celsius.
  // This formula comes from the temperature sensor datasheet:
  float tempC = (voltage - 0.5) * 100.0;
   // While we're at it, let's convert degrees Celsius to Fahrenheit.
  // This is the classic C to F conversion formula:
  float tempF = tempC * (9.0/5.0) + 32.0;
  char temperature[10];
  char str_tempC[6];
  char str_tempF[6];

  //This converts the floating variable of temperature to a 
  //sting so that we can print that on the array:

  /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
  dtostrf(tempF, 4, 2, str_tempF);
  sprintf(temperature,"Temp: %s F", str_tempF);

  //dtostrf(tempC, 4, 2, str_tempC);               //Uncomment these lines and
  //sprintf(temperature,"Temp: %s C", str_tempC);  //comment the previous lines 
                                                   //If you want to see temp in C
  
  //This prints the string we just made to the badger array:
  Plex.scrollText(temperature, 1);

  //wait for 5.7 secounds while scrolling temp:
  delay(5700); 

  //Read the value of the moisture sensor and print that directly 
  //to the badger array:

  int sensorValue = analogRead(moisturePin);
  char moisture[20];
  
  sprintf(moisture, "Moisture level: %i", sensorValue);

  Plex.scrollText(moisture, 1);

  //wait for 11 seconds while scrolling moisture level:
  delay(11000); 

  // Stop scrolling the text
  Plex.stopScrolling();
  delay(2000);
}

float getVoltage(int pin)
{
  // This function has one input parameter, the analog pin number
  // to read. You might notice that this function does not have
  // "void" in front of it; this is because it returns a floating-
  // point value, which is the true voltage on that pin (0 to 5V).
  
  // You can write your own functions that take in parameters
  // and return values. Here's how:
  
    // To take in parameters, put their type and name in the
    // parenthesis after the function name (see above). You can
    // have multiple parameters, separated with commas.
    
    // To return a value, put the type BEFORE the function name
    // (see "float", above), and use a return() statement in your code
    // to actually return the value (see below).
  
    // If you don't need to get any parameters, you can just put
    // "()" after the function name.
  
    // If you don't need to return a value, just write "void" before
    // the function name.

  // Here's the return statement for this function. We're doing
  // all the math we need to do within this statement:

   
  return ((analogRead(pin) * 0.0048875855327468) * (3.3/5));
  
  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 3.3 value that is the true voltage
  // being read at that pin.
  //If you are using a 5V device just erase the "*(3.3/5)" in
  //the above equation.
}

