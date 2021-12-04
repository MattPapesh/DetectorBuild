void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pin = A0;

  int fixed_resistance = 100; 
  float total_voltage = 3.3; 
  float voltage_read = total_voltage * ((float)analogRead(pin)/675.18);
  float soln_resistance = ((float)voltage_read * fixed_resistance) / (total_voltage - voltage_read); 

  Serial.print("Voltage Drop: "); Serial.println(voltage_read);
  Serial.print("Resistance: "); Serial.println(soln_resistance); 

}
