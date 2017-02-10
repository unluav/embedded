typedef struct StructOrientation {
  float pitch;
  float roll;
  float yaw;
} Orientation;

void imu_initialize();
Orientation current_orientation();
Orientation orientation_diff(Orientation *x, Orientation *y);
