// NOTE: Include the Measure library header file (which should be installed locally)
#include <Measure.hpp>

// Create Measure objects for our sensor readings, and with arbitrarily 
// different amounts of retained storage just to demo how that works
Measure<6> Temperature;  // Manage temperature readings with retained storage for 6
Measure<12> CO2;         // Manage carbon dioxide readings with retained storage for 12
Measure Humidity;        // Manage humidity readings, defaults to 1 retained storage location

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
  Serial.print("Humidity measure capacity   : "); Serial.println(Humidity.getCapacity());
  Serial.print("CO2 measure capacity        : "); Serial.println(CO2.getCapacity());

}

void loop() {

  int i;

  // Read (simulated) environmental values from an imaginary sensor
  readSensor();
  blinkLED();
  numSamples++;
  Serial.print("Temperature: "); Serial.print(ambientTemperatureF);
  Serial.print(", Humidity: "); Serial.print(ambientHumidity);
  Serial.print(", CO2: "); Serial.println(ambientCO2);

  // Include the latest simulated sensor readings in the appropriate Measure object
  Temperature.include(ambientTemperatureF);
  Humidity.include(ambientHumidity);
  CO2.include(ambientCO2);

  // Every five read values let's report min, max, and average sensor values over
  // those five reads.  Also display the retained storage for each Measure to show
  // how the values there are managed
  if(numSamples >= 5) {
    Serial.println("Reporting: ");
    Serial.print("Temperature: ");
    Serial.print(Temperature.getAverage()); Serial.print(" avg, ");
    Serial.print(Temperature.getMin()); Serial.print(" min, ");
    Serial.print(Temperature.getMax()); Serial.println(" max");
    Serial.print("    Stored: [");
    for(i=0;i<Temperature.getCapacity();i++) {
      if(i != 0) Serial.print(",");
      Serial.print(Temperature.getMember(i));
    }
    Serial.print("] ");
    Serial.print(Temperature.getStored()); Serial.print(" of "); 
    Serial.println(Temperature.getCapacity()); 

    Serial.print("Humidity: ");
    Serial.print(Humidity.getAverage()); Serial.print(" avg, ");
    Serial.print(Humidity.getMin()); Serial.print(" min, ");
    Serial.print(Humidity.getMax()); Serial.println(" max");
    Serial.print("    Stored: [");
    for(i=0;i<Humidity.getCapacity();i++) {
      if(i != 0) Serial.print(",");
      Serial.print(Humidity.getMember(i));
    }
    Serial.print("] ");
    Serial.print(Humidity.getStored()); Serial.print(" of "); 
    Serial.println(Humidity.getCapacity()); 

    Serial.print("CO2: ");
    Serial.print(CO2.getAverage()); Serial.print(" avg, ");
    Serial.print(CO2.getMin()); Serial.print(" min, ");
    Serial.print(CO2.getMax()); Serial.println(" max");
    Serial.print("    Stored: [");
    for(i=0;i<CO2.getCapacity();i++) {
      if(i != 0) Serial.print(",");
      Serial.print(CO2.getMember(i));
    }
    Serial.print("] ");
    Serial.print(CO2.getStored()); Serial.print(" of "); 
    Serial.println(CO2.getCapacity()); 

    // Clear the Measure objects, resetting min/max/avg/count tracking
    // but preserving the retained values storage. (To clear retained
    // storage need to call the deleteRetained() method explicitly.)
    Temperature.clear();
    Humidity.clear();
    CO2.clear();
    numSamples = 0;
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


