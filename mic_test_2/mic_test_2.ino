const int microphonePin = A0;
const int bfsz = 1; // buffer size

int buffer[bfsz]; // declare buffer array
int wptr=0; // pointer for index check

int last_time;

void setup() {
  Serial.begin(9600);

  // initialize buffer array with zeros
  for(int i = 0; i < bfsz; i++) buffer[i] = 0;
}


void loop() {
  Serial.println(millis() - last_time);
  last_time = millis();
  
  long moav = 0; // moving average

  // reset pointer(index) if exceeds buffer length
  if (wptr == bfsz){
    wptr = 0;
  }else{
    wptr += 1;
  }

  // write microphone reading into currentbuffer index
  buffer[wptr] = analogRead(microphonePin);

  // caclculate moving average
  for(int j = 0; j < bfsz; j++) moav += buffer[j];  
  moav = moav / bfsz;

  // print moving average value
  Serial.print("Moving Average =");
  Serial.println(moav);
}
