volatile int throttle_time;
volatile int pitch_time;
volatile int roll_time;
volatile int yaw_time;
volatile int kill_time;

int throttle_low;
int pitch_mid;
int roll_mid;
int yaw_mid;

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

  Serial.println("Calibrating Reciever");
  calibrate_reciever();
  Serial.println("Reciever Calibrated");
}

void calibrate_reciever(){
  int high_pitch = 0;
  int low_pitch = 2000;
  int high_roll = 0;
  int low_roll = 2000;
  int high_yaw = 0;
  int low_yaw = 2000;

  int until = millis() + 5000;

  while(until > millis()){
    int current_throttle = throttle_time;
    int current_pitch = pitch_time;
    int current_roll = roll_time;
    int current_yaw = yaw_time;

    if(current_throttle < throttle_low){
      throttle_low = current_throttle;
    }

    if(current_pitch > high_pitch){
      high_pitch = current_pitch;
    } else if(current_pitch < low_pitch){
      low_pitch = current_pitch;
    }

    if(current_roll > high_roll){
      high_roll = current_roll;
    } else if(current_roll < low_roll){
      low_roll = current_roll;
    }

    if(current_yaw > high_yaw){
      high_yaw = current_yaw;
    } else if(current_yaw < low_yaw){
      low_yaw = current_yaw;
    }
  }

  pitch_mid = (high_pitch + low_pitch) / 2;
  roll_mid = (high_roll + low_roll) / 2;
  yaw_mid = (high_yaw + low_yaw) / 2;
}

void rising_kill() {
  kill_time = micros();
  attachInterrupt(KILL_RC_PIN, falling_kill, FALLING);
}

void falling_kill(){
  int kill = micros() - kill_time;
  Serial.print("Kill:\t");
  Serial.println(kill);
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
