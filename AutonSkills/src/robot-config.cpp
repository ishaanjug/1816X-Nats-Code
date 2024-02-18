#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor L1 = motor(PORT13, ratio6_1, true);
motor L2 = motor(PORT16, ratio6_1, true);
motor L3 = motor(PORT9, ratio6_1, true);
motor R1 = motor(PORT14, ratio6_1, false);
motor R2 = motor(PORT10, ratio6_1, false);
motor R3 = motor(PORT5, ratio6_1, false);
inertial Inertial = inertial(PORT12);
motor Intake = motor(PORT11, ratio18_1, false);
controller Controller1 = controller(primary);
digital_out BackWings = digital_out(Brain.ThreeWirePort.A);
motor HangMotorA = motor(PORT15, ratio18_1, false);
motor HangMotorB = motor(PORT17, ratio18_1, false);
motor_group Hang = motor_group(HangMotorA, HangMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control Hang
      if (Controller1.ButtonL1.pressing()) {
        Hang.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        Hang.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        Hang.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}