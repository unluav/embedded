#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define RADIANS_TO_DEGREES(x) x * 57.2958

#define MICROSEC_TO_HERTZ(x) (1.0/x)

Adafruit_BNO055 orient = Adafruit_BNO055();

struct Orientation {
  float pitch;
  float roll;
  float yaw;
};

void imu_initialize(){
  Serial.println(orient.begin());
  if (!orient.begin()){
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

struct Orientation current_orientation()
{
  sensors_event_t event;
  orient.getEvent(&event);

  return {
    .pitch = event.orientation.pitch,
    .roll = event.orientation.roll,
    .yaw = event.heading
  };
}

struct Orientation orientation_diff(struct Orientation *x, struct Orientation *y){
  return {
    .pitch = x->pitch - y->pitch,
    .roll = x->roll - y->roll,
    .yaw = x->yaw - y->yaw
  };
}
