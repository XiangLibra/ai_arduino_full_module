void setup(){
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
}

void loop(){
  analogWrite(D5, 128); //用半速轉動2秒
  analogWrite(D6, 0);
  delay(2000);

  analogWrite(D5, 0);   //停止2秒
  analogWrite(D6, 0);
  delay(2000);

    analogWrite(D5, 255);//用全速轉動2秒
  analogWrite(D6, 0);
  delay(2000);

  analogWrite(D5, 0);   //停止2秒
  analogWrite(D6, 0);
  delay(2000);


  
  analogWrite(D5, 0);   //用半速反轉2秒
  analogWrite(D6, 128);
  delay(2000);

  analogWrite(D5, 0);   //停止2秒
  analogWrite(D6, 0);
  delay(2000);


    analogWrite(D5, 0); //用全速反轉2秒
  analogWrite(D6, 255);
  delay(2000);

  analogWrite(D5, 0);   //停止2秒
  analogWrite(D6, 0);
  delay(2000);
}
