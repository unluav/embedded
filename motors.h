typedef struct StructmotorStruct {
  int left_front;
  int right_front;
  int left_back;
  int right_back;
} motorStruct;

void attach_motors();
motorStruct create_motor_struct(int throttle, int pitch, int roll, int yaw);
void calibrate_motors();
int scope_motor_values(int in);
void print_motor_struct(motorStruct data);
void update_motors(motorStruct data);
