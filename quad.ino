#include <Servo.h>
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

volatile int throttle = 0;
volatile int pitch = 0;
volatile int roll = 0;
volatile int yaw = 0;

PID pitch_pid;
PID roll_pid;
PID yaw_pid;

Orientation init_orientation;

void setup() {
  Serial.begin(9600);
  // while(!Serial);
  Serial.println("System Setting Up");
  Serial.println("Setting Up Reciever");
  setup_reciever();
  Serial.println("Calibrating Motors");
  attach_motors();
  calibrate_motors();
  Serial.println("Creating pids");
  pitch_pid = create_pid(PITCH_P, PITCH_I, PITCH_D);
  roll_pid = create_pid(ROLL_P, ROLL_I, ROLL_D);
  yaw_pid = create_pid(YAW_P, YAW_I, YAW_D);
  Serial.println("Setting up IMU");
  imu_initialize();
  Serial.println("Fetching Initial Position");
  init_orientation = current_orientation();
  Serial.println("System Up");
}

void loop() {
  Orientation current_orient = current_orientation();
  Orientation error = orientation_diff(&init_orientation, &current_orient);
  int new_pitch = update_pid(&pitch_pid, error.pitch) + pitch;
  Serial.print("New Pitch:\t");
  Serial.print(new_pitch);
  int new_roll = update_pid(&roll_pid, error.roll) + roll;
  Serial.print("\tNew Roll:\t");
  Serial.print(new_roll);

  // Yaw pid is disabled for reasons...
  //
  // int new_yaw = update_pid(&yaw_pid, error.yaw) + yaw;
  // Serial.print("\tNew Yaw:\t");
  // Serial.println(new_yaw);
  //
  motorStruct motor_data = create_motor_struct(throttle, new_pitch, new_roll, 0);
  update_motors(motor_data);
  delay(250);
}
