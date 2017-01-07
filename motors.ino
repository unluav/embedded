#define LEFT_FRONT_MOTOR A3
#define RIGHT_FRONT_MOTOR A1
#define LEFT_BACK_MOTOR A2
#define RIGHT_BACK_MOTOR A0

Servo left_front_motor;
Servo right_front_motor;
Servo left_back_motor;
Servo right_back_motor;

struct motorStruct zero_struct {0,0,0,0};
struct motorStruct max_struct {2000, 2000, 2000, 2000};

void attach_motors(){
  left_front_motor.attach(LEFT_FRONT_MOTOR);
  right_front_motor.attach(RIGHT_FRONT_MOTOR);
  left_back_motor.attach(LEFT_BACK_MOTOR);
  right_back_motor.attach(RIGHT_BACK_MOTOR);
}

struct motorStruct create_motor_struct(int throttle, int pitch, int roll, int yaw){
  return {
    .left_front = throttle + pitch + roll + yaw,
    .right_front = throttle + pitch - roll - yaw,
    .left_back = throttle - pitch + roll - yaw,
    .right_back = throttle - pitch - roll + yaw
  };
}

void calibrate_motors(){
  update_motors(max_struct);
  delay(3000);
  update_motors(zero_struct);
  delay(3000);
}

void update_motors(motorStruct data){
  left_front_motor.writeMicroseconds(data.left_front);
  right_front_motor.writeMicroseconds(data.right_front);
  left_back_motor.writeMicroseconds(data.left_back);
  right_back_motor.writeMicroseconds(data.right_back);
}
