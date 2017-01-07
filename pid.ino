struct PID {
  float p;
  float d;
  float i;
  float last_time;
  float rolling_error;
  float last_error;
}

struct PID create_pid(float p, float d, float i){
  return {
    .p = p,
    .d = d,
    .i = i,
    .last_time = micros();
    .rolling_error = 0;
    .last_error = 0;
  }
}

int update_pid(struct PID * pid, float error){
  int time = micros();
  int p_correct = pid->p * error;
  int i_error = (error * time + pid->rolling_error) / 2;
  int d_correct = (pid->last_error - error) * pid->d;
  pid->last_time = time;
  pid->rolling_error = i_error;
  pid->last_error = error;

  return (i_error * pid->i) + p_correct + d_correct;
}
