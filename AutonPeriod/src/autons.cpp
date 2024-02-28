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
  Hang.setVelocity(200, rpm);
  Intake.spin(forward);
  chassis.drive_distance(50);
  chassis.drive_distance(-3);
  chassis.drive_settle_error = 5;
  chassis.drive_settle_time = 1;
  chassis.turn_to_angle(75);
  Intake.spin(reverse);
  wait(0.2, seconds);
  FrontWings.set(true);
  // Open Fromt Wings
  chassis.drive_distance(25);
  // Close Front Wings
  FrontWings.set(false);
  chassis.drive_distance(-10.2);
  chassis.turn_to_angle(30);
  chassis.drive_distance(-57.5);
  chassis.turn_to_angle(-60);
  chassis.drive_distance(12);
  // Open Back Wings
  BackLeft.set(true);
  wait(0.2, seconds);
  chassis.drive_distance(-22);
  wait(0.5, seconds);
  //close back wings
  BackLeft.set(false);
  chassis.drive_distance(-5);
  chassis.left_swing_to_angle(-105);
  chassis.drive_distance(-35);
  BackRight.set(true);
  chassis.turn_to_angle(-90);
}  

void defensive_side_auton_2(){
  chassis.set_drive_constants(300, 1.0, 0.4, 10.0, 1.0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(40, .4, .03, 3, 15);
  chassis.drive_settle_error = 5;
  chassis.drive_settle_time = 1;
  Hang.setStopping(hold);
  Hang.setVelocity(100, percent);
  chassis.drive_distance(18);
  // Open Back Wings
  BackLeft.set(true);
  wait(0.5, seconds);
  chassis.drive_distance(-22);
  BackLeft.set(false);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-38);
  BackRight.set(true);
  chassis.turn_to_angle(-30);
}

void offensive_side_auton_1(){
  chassis.set_drive_constants(300, 1.0, 0.4, 10.0, 1.0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(40, .4, .03, 3, 15);
  chassis.drive_settle_error = 5;
  chassis.drive_settle_time = 1;
  Hang.setVelocity(100, percent);
  Intake.setVelocity(100, percent);
  Intake.spin(forward);
  // Hang.spinFor(reverse, 300,  degrees);
  wait(0.3, seconds);
  chassis.drive_distance(-31);
  chassis.left_swing_to_angle(-45);
  BackLeft.set(true);
  chassis.drive_distance(-20);
  wait(0.1, seconds);
  BackLeft.set(false);
  chassis.drive_distance(-4);
  chassis.left_swing_to_angle(-80);
  chassis.drive_distance(-20);
  chassis.drive_distance(12);
  chassis.turn_to_angle(100);
  Intake.spin(reverse);
  chassis.drive_distance(18);
  Intake.stop();
  chassis.drive_distance(-15);
  chassis.turn_to_angle(23);
  Intake.spin(forward);
  chassis.drive_distance(50);
  chassis.turn_to_angle(155);
  Intake.spin(reverse);
  chassis.drive_distance(12);
  wait(0.1, seconds);
  chassis.turn_to_angle(50);
  Intake.spin(forward);
  chassis.drive_distance(24);
  chassis.drive_distance(-3);
  chassis.turn_to_angle(180);
  Intake.spin(reverse);
  FrontWings.set(true);
  chassis.drive_distance(37);
  chassis.drive_distance(-15);
}

void offensive_side_auton_2(){
  chassis.set_drive_constants(300, 1.0, 0.4, 10.0, 1.0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(40, .4, .03, 3, 15);
  chassis.drive_settle_error = 5;
  chassis.drive_settle_time = 1;
  Intake.setVelocity(200, rpm);
  // Open Front Wings
  // FrontWings.set(true);
  // wait(0.3, seconds);
  // FrontWings.set(false);
  Intake.spin(forward);
  chassis.drive_distance(51);
  wait(0.15, seconds);
  chassis.drive_distance(-50);
  Intake.spin(reverse);
  chassis.turn_to_angle(50);
  chassis.turn_to_angle(-73);
  Intake.spin(forward);
  chassis.drive_distance(37);
  chassis.drive_distance(-35.5);
  chassis.left_swing_to_angle(-118);
  BackLeft.set(true);
  chassis.drive_distance(-19);
  BackLeft.set(false);
  chassis.left_swing_to_angle(-158);
  chassis.drive_distance(-20);
  chassis.drive_distance(12);
  chassis.turn_to_angle(23);
  Intake.spin(reverse);
  chassis.drive_distance(18);
  chassis.drive_distance(-15);
  chassis.turn_to_angle(-49);
  Intake.spin(forward);
  chassis.drive_distance(50);
  chassis.turn_to_angle(80);
  Intake.spin(reverse);
  FrontWings.set(true);
  chassis.drive_distance(50);
}
