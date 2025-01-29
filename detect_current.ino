float detect_current(){ //reads an average value from the solar cell

  float value = analogRead(A0);

  for(int i=0;i<500;i++){

    value = value + analogRead(A0);
    delay(10);
    
  }

  value = value / 500;
  Serial.println(value);

  return value;
  
}