#include "vex.h"

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}

void drivevelocity(int vel){
  L1.setVelocity(vel, percent);
  L2.setVelocity(vel, percent);
  L3.setVelocity(vel, percent);
  R1.setVelocity(vel, percent);
  R2.setVelocity(vel, percent);
  R3.setVelocity(vel, percent);

}


void fd(int unit){
  float desiredposition = unit*1300/24;
  L1.setPosition(0,degrees);
  L2.setPosition(0,degrees);
  L3.setPosition(0,degrees);
  R1.setPosition(0,degrees);
  R2.setPosition(0,degrees);
  R3.setPosition(0,degrees);
  wait(5,msec);
  drivevelocity(60);
  L1.spinToPosition(desiredposition,degrees,false);
  L2.spinToPosition(desiredposition,degrees,false);
  L3.spinToPosition(desiredposition,degrees,false);
  R1.spinToPosition(desiredposition,degrees,false);
  R2.spinToPosition(desiredposition,degrees,false);
  R3.spinToPosition(desiredposition,degrees);
}

void defensive_side_auton_1(){
  chassis.set_drive_constants(300, 1.0, 0.4, 10.0, 1.5);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(40, .4, .03, 3, 15);
  Intake.setVelocity(200, rpm);
  Intake.spin(forward);
  chassis.drive_distance(50);
  chassis.drive_distance(-2);
  chassis.drive_settle_error = 5;
  chassis.drive_settle_time = 1;
  chassis.turn_to_angle(75);
  // Open Fromt Wings
  chassis.drive_distance(22);
  // Close Front Wings
  chassis.drive_distance(-5.2);
  chassis.turn_to_angle(30);
  chassis.drive_distance(-61);
  chassis.turn_to_angle(-60);
  chassis.drive_distance(10);
  // Open Back Wings
  chassis.drive_distance(-24);
  //close back wings
  chassis.left_swing_to_angle(-105);
  chassis.drive_distance(-33);
  //spin hang

}  

void defensive_side_auton_2(){
  chassis.set_drive_constants(300, 1.0, 0.4, 10.0, 1.0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(40, .4, .03, 3, 15);
  chassis.drive_settle_error = 5;
  chassis.drive_settle_time = 1;
  //chassis.drive_distance(12);
  // Open Back Wings
  // BackWings.set(true);
  chassis.drive_distance(-20);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-40);
  // Lift the lift
}

void offensive_side_auton_1(){
  chassis.set_drive_constants(300, 1.0, 0.4, 10.0, 1.0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(40, .4, .03, 3, 15);
  chassis.drive_settle_error = 5;
  chassis.drive_settle_time = 1;
  Intake.setVelocity(70,percent);
  Intake.spinFor(forward, 270,degrees,false);
  wait(100,msec);
  fd(-30);
  chassis.left_swing_to_angle(-45);
  fd(-18);
  chassis.turn_to_angle(-90);
  fd(-12);
  fd(12);
  chassis.turn_to_angle(90);
  fd(12);
}

void offensive_side_auton_2(){
  chassis.set_drive_constants(300, 1.0, 0.4, 10.0, 1.0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(40, .4, .03, 3, 15);
  // Open Front Wings
  Intake.spin(forward);
  chassis.drive_distance(64);
  wait(0.4, seconds);
  chassis.turn_to_angle(123);
  Intake.spin(reverse);
  chassis.drive_distance(30);
  chassis.drive_distance(-20);
  chassis.turn_to_angle(-100);
  
}

void offensive_auton(){
  Intake.setVelocity(70,percent);
  Intake.spinFor(forward, 270,degrees,false);
  wait(200,msec);
  fd(-32);


}
