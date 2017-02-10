typedef struct StructPID {
  float p;
  float d;
  float i;
  float last_time;
  float rolling_error;
  float last_error;
} PID;

PID create_pid(float p, float d, float i);
int update_pid(PID * pid, float error);
