void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<5; i++) {
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(7, LOW);
    delay(500);
  }
  digitalWrite(7, HIGH);
  while(1){} // infinite loop
 }
