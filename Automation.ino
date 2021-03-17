 void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);// for relay
  digitalWrite(2, LOW);  // switch is off by default
 
}
void loop()
{
  while(Serial.available()>0)     //to check the input from user
  {
    int val = Serial.parseInt();
    if(val==1){
      digitalWrite(2, HIGH);
      }
    if(val==2){
      digitalWrite(2, LOW);
      }
  }
   
}
