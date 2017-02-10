#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define RADIANS_TO_DEGREES(x) x * 57.2958

#define MICROSEC_TO_HERTZ(x) (1.0/x)

Adafruit_BNO055 orient = Adafruit_BNO055();

void imu_initialize(){
  Serial.println(orient.begin());
  if (!orient.begin()){
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

Orientation current_orientation(){
  sensors_event_t event;
  orient.getEvent(&event);

  // heading and roll are swapped because the imu is on wrong
  return {
    .pitch = event.orientation.pitch,
    .roll = event.orientation.heading,
    .yaw = event.orientation.roll
  };
}

Orientation orientation_diff(Orientation *x, Orientation *y){
  return {
    .pitch = x->pitch - y->pitch,
    .roll = x->roll - y->roll,
    .yaw = x->yaw - y->yaw
  };
}
