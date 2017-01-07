#include <Servo.h>

volatile int throttle = 0;
volatile int pitch = 0;
volatile int roll = 0;
volatile int yaw = 0;

struct PID pitch_pid;
struct PID roll_pid;
struct PID yaw_pid;

struct Orientation init_orientation;

struct motorStruct {
  int left_front;
  int right_front;
  int left_back;
  int right_back;
};

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("System Setting Up");
  Serial.println("Attaching Interrupts");
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
  init_orientation = imu_update();
  Serial.println("System Up");
}

void loop() {
  struct Orientation error = orientation_diff(init_orientation, current_orientation());
  int new_pitch = update_pid(pitch_pid, error.pitch) + pitch;
  Serial.print("New Pitch:\t")
  Serial.println(new_pitch);
  int new_roll = update_pid(roll_pid, error.roll) + roll;
  Serial.print("New Roll:\t")
  Serial.println(new_roll);
  int new_yaw = update_pid(yaw_pid, error.yaw) + yaw;
  Serial.print("New Yaw:\t")
  Serial.println(new_yaw);
  struct motorStruct motor_data = create_motor_struct(throttle, new_pitch, new_roll, new_yaw);
  update_motors(motor_data);
}
