int pin = A0;
int LED_pins[] = {2, 3, 4};
int LED_thresholds[] = {725, 1600, 2475};
int LED_limits[] = {1600, 2475, 3000};

int fixed_resistance = 100;
float total_voltage = 3.3;
float voltage_read = 0;

float soln_resistance = 0;
float soln_micro_conductance = 0;
float soln_concentration = 0;

// Given a conductance in micro siemens, get concentration in ppm;
float getConcentration(float micro_conductance)
{
  return 0.6 * micro_conductance; 
}

// If a concentration of a solution in ppm is larger than or equal to its respective threshold, and less than or equal to its respective threshold, then turn the respective LED on; 
// the respective variables are associated with each other based on their indexes from the integer arrays: LED_pins[], LED_thresholds[], and LED_limits[]; 
void runLEDs(int soln_concentration)
{
  for(int i = 0; i < 3; i++)
  {
    if(soln_concentration >= LED_thresholds[i] && soln_concentration <= LED_limits[i])
    {
      // Turn respective LED on.
      digitalWrite(LED_pins[i], HIGH); 
    }
    else
    {
      // Turn respective LED off.
      digitalWrite(LED_pins[i], LOW); 
    }
  }
}

void setup() {
  // Establish serial communication at 9600 baud.
  Serial.begin(9600);

  for(int i = 0; i < 3; i++)
  {
    // Assign LED pins to an OUTPUT mode.
    pinMode(LED_pins[i], OUTPUT);
  }
}

void loop() {
  // Voltage is proportional to an analog scale from 0 - 1023, and the analog value read can be used to calculate the voltage drop across the probes when testing a solution.
  voltage_read = total_voltage * ((float)analogRead(pin)/675.18);
 
  // Calculate the resistance of the solution, as it is the variable resistor in the voltage divider.
  soln_resistance = ((float)voltage_read * fixed_resistance) / (total_voltage - voltage_read); 
  // Calculate conductance, the inverse of resistance, and convert it to micro seimens
  soln_micro_conductance = 1000000 / soln_resistance; 
  // Get the concentration of the solution.
  soln_concentration = getConcentration(soln_micro_conductance);

  // Power LEDs based on the concentration of the solution
  runLEDs(soln_concentration);
  
  // Print the conductance and concentration to Serial:
  Serial.print("Resistance (ohms): "); Serial.println(soln_resistance);
  Serial.print("Conductance (micro G): "); Serial.println(soln_micro_conductance);
  Serial.print("Concentration (ppm): "); Serial.println(soln_concentration); 

  delay(1000);
}
