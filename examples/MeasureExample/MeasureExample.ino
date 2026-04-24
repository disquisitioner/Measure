// NOTE: Include the Measure library header file (which should be installed locally)
#include <Measure.hpp>

// Create a Measure object with storage for 12 retained values of measured temperature
Measure<6> Temperature;
Measure<12> CO2;
Measure <1> Humidity;

// Globals to ease gathering and manipulating sensor readings
float ambientTemperatureF, ambientHumidity, ambientCO2;
uint8_t numSamples = 0;

int led = LED_BUILTIN;  // Onboard LED

void setup() {

  int i;
  float value;

  Serial.begin(115200);
  while(!Serial);
  delay(5000);  Serial.println();

  // Set LED to be an output pin so we can blink it
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW); // and make sure it is off

  // generate random numbers for every boot cycle
  randomSeed(analogRead(0));

  // Overview -- how much room do we have for stored values?
  Serial.print("Temperature measure capacity: "); Serial.println(Temperature.getCapacity());

}

void loop() {

  int i;

  // Read (simulated) environmental values from an imaginary sensor
  readSensor();
  blinkLED();
  numSamples++;
  Serial.print("Temperature: "); Serial.println(ambientTemperatureF);
  Serial.print("Humidity.  : "); Serial.println(ambientHumidity);
  Serial.print("CO2.       : "); Serial.println(ambientCO2);


  // Include the latest simulated sensor readings in the appropriate Measure object
  Temperature.include(ambientTemperatureF);
  Humidity.include(ambientHumidity);
  CO2.include(ambientCO2);

  // Every five read values let's report min, max, and average sensor values...
  if(numSamples >= 5) {
    Serial.println("Reporting: ");
    Serial.print("Temperature:");
    Serial.print(Temperature.getAverage()); Serial.print(" avg, ");
    Serial.print(Temperature.getMin()); Serial.print(" min, ");
    Serial.print(Temperature.getMax()); Serial.println(" max");
    Serial.print("Stored: [");
    for(i=Temperature.getCapacity()-Temperature.getStored();i<Temperature.getCapacity();i++) {
      Serial.print(Temperature.getMember(i));
    }
    Serial.print("] ");
    Serial.print(Temperature.getStored()); Serial.print(" of "); 
    Serial.println(Temperature.getCapacity()); 

    Serial.print("Humidity:");
    Serial.print(Humidity.getAverage()); Serial.print(" avg, ");
    Serial.print(Humidity.getMin()); Serial.print(" min, ");
    Serial.print(Humidity.getMax()); Serial.println(" max");

    Serial.print("CO2:");
    Serial.print(CO2.getAverage()); Serial.print(" avg, ");
    Serial.print(CO2.getMin()); Serial.print(" min, ");
    Serial.print(CO2.getMax()); Serial.println(" max");
    
    // ...and the retained values to show we've kept the right number of readings in proper order
    Serial.print("Stored: [");
    for(i=0;i<Temperature.getCapacity();i++) {
      if(i != 0) Serial.print(",");
      Serial.print(Temperature.getMember(i));
    }
    Serial.print("] ");
    Serial.print(Temperature.getStored()); Serial.print(" of "); 
    Serial.println(Temperature.getCapacity());

    // Clear the Measure object for Temperature, resetting min/max/avg/count tracking
    // and emptying the retained values storage.
    Temperature.clear();
  }

  // Delay for 30 seconds
  delay(30000);

}

// Simulate a sensor that reports temperature, humidity, and CO2
void readSensor() {
  ambientTemperatureF = random(22.0,104.5);
  ambientHumidity = random(21.0,92.5);
  ambientCO2 = random(400,1400.0);
}

// Blink the onboard LED once
void blinkLED() {
  digitalWrite(led, HIGH);  // turn on
  delay(500);
  digitalWrite(led,LOW);
}


