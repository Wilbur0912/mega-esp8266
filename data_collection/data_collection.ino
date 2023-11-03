int FSR_in[9] = {
  A0, A1, A2, A3, A4, A5, A6, A7, A8
};

int FSR_avg[9][100];
float last_avg[9] = {0};
int FSR_index = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  handleFSR();
}

void handleFSR() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 9; i++) {
    int val = analogRead(FSR_in[i]);
    int last = FSR_avg[i][(FSR_index+99)%100];
    float diff = val / 1.0 / last;
    float avg;
    if(diff > 1.1 || diff < 0.9) {
      for(int j = 0; j < 100; j++) {
        FSR_avg[i][j] = val;
      }
      avg = val;
    } else {
      avg = last_avg[i] + (val - FSR_avg[i][FSR_index]) / 100.0;
      FSR_avg[i][FSR_index] = val;
    }
    last_avg[i] = avg;
    Serial.print(avg);
    Serial.print(",");
  }
  FSR_index = (FSR_index + 1) % 100;
}