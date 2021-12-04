

int pin = A0;
int LED_pins[] = {1, 2, 3};
int LED_thresholds[] = {725, 1600, 2475};

int fixed_resistance = 100;
float total_voltage = 3.3;
float voltage_read = 0;

float soln_resistance = 0;
float soln_micro_conductance = 0;
float soln_concentration = 0;

float getConcentration(float micro_conductance)
{
  return 0.6 * micro_conductance; 
}

void runLEDs(int soln_concentration)
{
  for(int i = 0; i < 3; i++)
  {
    if(soln_concentration >= LED_thresholds[i])
    {
      digitalWrite(LED_pins[i], HIGH); 
    }
    else
    {
      digitalWrite(LED_pins[i], LOW); 
    }
  }
}

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 3; i++)
  {
    pinMode(LED_pins[i], OUTPUT);
  }
}

void loop() {
  voltage_read = total_voltage * ((float)analogRead(pin)/675.18);
  soln_resistance = ((float)voltage_read * fixed_resistance) / (total_voltage - voltage_read); 
  
  soln_micro_conductance = 1000000 / soln_resistance; 
  soln_concentration = getConcentration(soln_micro_conductance);

  Serial.print("Voltage Drop: "); Serial.println(voltage_read);
  Serial.print("Resistance: "); Serial.println(soln_resistance); 

  

}
