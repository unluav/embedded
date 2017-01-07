volatile int throttle_time;
volatile int pitch_time;
volatile int roll_time;
volatile int yaw_time;
volatile int kill_time;

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
  attachInterrupt(KILL_RC_PIN, rising_kill, RISING);
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
  throttle = micros() - throttle_time;
  attachInterrupt(THROTTLE_RC_PIN, rising_throttle, RISING);
}

void rising_pitch() {
  pitch_time = micros();
  attachInterrupt(PITCH_RC_PIN, falling_pitch, FALLING);
}

void falling_pitch() {
  pitch = micros() - pitch_time;
  attachInterrupt(PITCH_RC_PIN, rising_pitch, RISING);
}

void rising_roll() {
  roll_time = micros();
  attachInterrupt(ROLL_RC_PIN, falling_roll, FALLING);
}

void falling_roll() {
  roll = micros() - roll_time;
  attachInterrupt(ROLL_RC_PIN, rising_roll, RISING);
}

void rising_yaw() {
  yaw_time = micros();
  attachInterrupt(YAW_RC_PIN, falling_yaw, FALLING);
}

void falling_yaw() {
  yaw = micros() - yaw_time;
  attachInterrupt(YAW_RC_PIN, rising_yaw, RISING);
}
