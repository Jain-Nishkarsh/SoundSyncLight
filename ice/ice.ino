int x;
String str;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}
int arr[3];

int split(String inarr){
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
  while (!Serial.available());
  delay(5);
  str = Serial.readStringUntil('\n');
  split(str);

  analogWrite(9, arr[0]);
  analogWrite(10, arr[1]);
  analogWrite(11, arr[2]);

  // for (int i = 0; i < 256; i++){
  //   analogWrite(9, i);
  //   analogWrite(10, i);
  //   analogWrite(11, i);
  //   delay(10);
  // }
}