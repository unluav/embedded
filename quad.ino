#include <Servo.h>
#include <string.h>
#include "imu.h"
#include "pid.h"
#include "motors.h"

#define PITCH_P 100.0
#define PITCH_I 0.0
#define PITCH_D 0.0
#define ROLL_P 100.0
#define ROLL_I 0.0
#define ROLL_D 0.0
#define YAW_P 100.0
#define YAW_I 0.0
#define YAW_D 0.0

// #define SERIAL
#define RADIO

#ifdef SERIAL
  #define SETUP_LOGGER Serial.begin(9600); while(!Serial);
  #define LOG(x) Serial.println(x);
#endif

#ifdef RADIO
  #define SETUP_LOGGER setup_radio();
  #define LOG(x) radio_write(x);
#endif

volatile int throttle = 0;
volatile int pitch = 0;
volatile int roll = 0;
volatile int yaw = 0;

PID pitch_pid;
PID roll_pid;
PID yaw_pid;

Orientation init_orientation;

void setup() {
  SETUP_LOGGER;
  LOG("System Setting Up");
  LOG("Setting Up Reciever");
  setup_reciever();
  LOG("Calibrating Motors");
  attach_motors();
  calibrate_motors();
  LOG("Creating pids");
  pitch_pid = create_pid(PITCH_P, PITCH_I, PITCH_D);
  roll_pid = create_pid(ROLL_P, ROLL_I, ROLL_D);
  yaw_pid = create_pid(YAW_P, YAW_I, YAW_D);
  LOG("Setting up IMU");
  imu_initialize();
  LOG("Fetching Initial Position");
  init_orientation = current_orientation();
  LOG("System Up");
}

void loop() {
  Orientation current_orient = current_orientation();
  Orientation error = orientation_diff(&init_orientation, &current_orient);
  int new_pitch = update_pid(&pitch_pid, error.pitch) + pitch;
  int new_roll = update_pid(&roll_pid, error.roll) + roll;
  char status_string[100];
  sprintf(status_string, "New Pitch:\t%i\tNew Roll:\t%i", new_pitch, new_roll);
  // char * status_string = strformat("New Pitch:\t%d\tNew Roll:\t%d", new_pitch, new_roll);
  LOG(status_string);

  // Yaw pid is disabled for reasons...
  //
  // int new_yaw = update_pid(&yaw_pid, error.yaw) + yaw;
  // Serial.print("\tNew Yaw:\t");
  // Serial.println(new_yaw);
  //
  motorStruct motor_data = create_motor_struct(throttle, new_pitch, new_roll, 0);
  update_motors(motor_data);
  delay(500);
}
