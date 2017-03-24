volatile int throttle_time;
volatile int pitch_time;
volatile int roll_time;
volatile int yaw_time;
volatile int kill_time;

int throttle_low;
int pitch_mid = 0;
int roll_mid = 0;
int yaw_mid = 0;

#define THROTTLE_RC_PIN 5
#define PITCH_RC_PIN 6
#define ROLL_RC_PIN 10
#define YAW_RC_PIN 11
#define KILL_RC_PIN 12

void setup_reciever() {
  attachInterrupt(THROTTLE_RC_PIN, rising_throttle, RISING);
  attachInterrupt(PITCH_RC_PIN, rising_pitch, RISING);
  attachInterrupt(ROLL_RC_PIN, rising_roll, RISING);
  attachInterrupt(YAW_RC_PIN, rising_yaw, RISING);
  // attachInterrupt(KILL_RC_PIN, rising_kill, RISING);

  delay(2000);

  LOG("Calibrating Reciever");
  calibrate_reciever();
  LOG("Reciever Calibrated");
}

void calibrate_reciever(){
  // int high_pitch = 0;
  // int low_pitch = 2000;
  // int high_roll = 0;
  // int low_roll = 2000;
  // int high_yaw = 0;
  // int low_yaw = 2000;
  //
  // int until = millis() + 5000;
  //
  // Serial.println(until);
  // while(until > millis()){
  //   // Serial.println(millis());
  //   int current_throttle = throttle;
  //   int current_pitch = pitch;
  //   int current_roll = roll;
  //   int current_yaw = yaw;
  //
  //   if(current_throttle < throttle_low){
  //     throttle_low = current_throttle;
  //   }
  //
  //   if(current_pitch > high_pitch){
  //     high_pitch = current_pitch;
  //   } else if(current_pitch < low_pitch){
  //     low_pitch = current_pitch;
  //   }
  //
  //   if(current_roll > high_roll){
  //     high_roll = current_roll;
  //   } else if(current_roll < low_roll){
  //     low_roll = current_roll;
  //   }
  //
  //   if(current_yaw > high_yaw){
  //     high_yaw = current_yaw;
  //   } else if(current_yaw < low_yaw){
  //     low_yaw = current_yaw;
  //   }
  // }

  LOG("Calibrated Maxes");
  // delay(1000);
  int i = 0;
  int p_sum = 0;
  int r_sum = 0;
  int y_sum = 0;
  int t_sum = 0;
  for(i = 0; i < 10; i++){
    p_sum += pitch;
    r_sum += roll;
    y_sum += yaw;
    t_sum += throttle;
    delay(200);
  }

  pitch_mid = p_sum / 10;
  roll_mid = r_sum / 10;
  yaw_mid = y_sum / 10;
  throttle_low = t_sum / 10;

  char p_string[100];
  char r_string[100];
  char y_string[100];
  sprintf(p_string, "pitch_mid\t%d", pitch_mid);
  sprintf(r_string, "roll_mid\t%d", roll_mid);
  sprintf(y_string, "yaw_mid\t%d", yaw_mid);
  LOG(p_string);
  LOG(r_string);
  LOG(y_string);
}

void rising_kill() {
  kill_time = micros();
  attachInterrupt(KILL_RC_PIN, falling_kill, FALLING);
}

void falling_kill(){
  int kill = micros() - kill_time;
  char string[100];
  sprintf(string, "Kill:\t%d", kill);
  LOG(string);
  attachInterrupt(KILL_RC_PIN, rising_kill, RISING);
  // TODO: KILL LOGIC GOES HERE
}

void rising_throttle() {
  throttle_time = micros();
  attachInterrupt(THROTTLE_RC_PIN, falling_throttle, FALLING);
}

void falling_throttle() {
  throttle = micros() - throttle_time - throttle_low;
  attachInterrupt(THROTTLE_RC_PIN, rising_throttle, RISING);
}

void rising_pitch() {
  pitch_time = micros();
  attachInterrupt(PITCH_RC_PIN, falling_pitch, FALLING);
}

void falling_pitch() {
  pitch = micros() - pitch_time - pitch_mid;
  attachInterrupt(PITCH_RC_PIN, rising_pitch, RISING);
}

void rising_roll() {
  roll_time = micros();
  attachInterrupt(ROLL_RC_PIN, falling_roll, FALLING);
}

void falling_roll() {
  roll = micros() - roll_time - roll_mid;
  attachInterrupt(ROLL_RC_PIN, rising_roll, RISING);
}

void rising_yaw() {
  yaw_time = micros();
  attachInterrupt(YAW_RC_PIN, falling_yaw, FALLING);
}

void falling_yaw() {
  yaw = micros() - yaw_time - yaw_mid;
  attachInterrupt(YAW_RC_PIN, rising_yaw, RISING);
}
