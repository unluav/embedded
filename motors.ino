#define LEFT_FRONT_MOTOR A3
#define RIGHT_FRONT_MOTOR A1
#define LEFT_BACK_MOTOR A2
#define RIGHT_BACK_MOTOR A0

#define MIN_MOTOR_VALUE 500
#define MAX_MOTOR_VALUE 2000

Servo left_front_motor;
Servo right_front_motor;
Servo left_back_motor;
Servo right_back_motor;

motorStruct zero_struct {0,0,0,0};
motorStruct max_struct {2000, 2000, 2000, 2000};

void attach_motors(){
  left_front_motor.attach(LEFT_FRONT_MOTOR);
  right_front_motor.attach(RIGHT_FRONT_MOTOR);
  left_back_motor.attach(LEFT_BACK_MOTOR);
  right_back_motor.attach(RIGHT_BACK_MOTOR);
}

motorStruct create_motor_struct(int throttle, int pitch, int roll, int yaw){
  return {
    .left_front = scope_motor_values(throttle + pitch - roll + yaw + 500),
    .right_front = scope_motor_values(throttle + pitch + roll - yaw + 500),
    .left_back = scope_motor_values(throttle - pitch - roll - yaw + 500),
    .right_back = scope_motor_values(throttle - pitch + roll + yaw + 500)
  };
}

void calibrate_motors(){
  update_motors(max_struct);
  delay(3000);
  update_motors(zero_struct);
  delay(3000);
}

int scope_motor_values(int in){
  if(in < MIN_MOTOR_VALUE){
    return MIN_MOTOR_VALUE;
  } else if(in > MAX_MOTOR_VALUE){
    return MAX_MOTOR_VALUE;
  } else {
    return in;
  }
}

void print_motor_struct(motorStruct data){
  Serial.print("\nLeft Front:\t");
  Serial.print(data.left_front);
  Serial.print("\tRight Front:\t");
  Serial.print(data.right_front);
  Serial.print("\tLeft Back:\t");
  Serial.print(data.left_back);
  Serial.print("\tRight Back:\t");
  Serial.println(data.right_back);
}

void update_motors(motorStruct data){
  print_motor_struct(data);
  left_front_motor.writeMicroseconds(data.left_front);
  right_front_motor.writeMicroseconds(data.right_front);
  left_back_motor.writeMicroseconds(data.left_back);
  right_back_motor.writeMicroseconds(data.right_back);
}
