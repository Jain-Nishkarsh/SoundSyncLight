int x;
String str;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
}
int arr[3];

void split(String inarr){
  String substr;
  int count = 0;
  for (int i = 0; i < inarr.length(); i++){
    if (inarr[i] != ' '){
      substr.concat(inarr[i]);
      // Serial.println("wtf");
    }
    else if (inarr[i] == ' '){
      arr[count] = substr.toInt();
      count++;
      substr = "";
      // Serial.println("sup");
    }
  }
  arr[count] = substr.toInt();
}

void loop() {
  if (Serial.available() > 0) {
    delay(5);
    str = Serial.readStringUntil('\n');
    split(str);

    Serial.println(str);

    analogWrite(26, arr[0]);
    analogWrite(25, arr[1]);
    analogWrite(27, arr[2]);
  }

  // there is a cat
  // it goes meow
  // then it gib pussy

  // for (int i = 0; i < 256; i++){
  //   analogWrite(9, i);
  //   analogWrite(10, i);
  //   analogWrite(11, i);
  //   delay(10);
  // }
}