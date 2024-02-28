#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor L1 = motor(PORT11, ratio6_1, true);
motor L2 = motor(PORT12, ratio6_1, true);
motor L3 = motor(PORT13, ratio6_1, true);
motor R1 = motor(PORT20, ratio6_1, false);
motor R2 = motor(PORT19, ratio6_1, false);
motor R3 = motor(PORT18, ratio6_1, false);
inertial Inertial = inertial(PORT17);
controller Controller1 = controller(primary);
motor HangMotorA = motor(PORT14, ratio18_1, false);
motor HangMotorB = motor(PORT9, ratio18_1, false);
motor_group Hang = motor_group(HangMotorA, HangMotorB);
digital_out BackLeft = digital_out(Brain.ThreeWirePort.F);
motor Intake = motor(PORT16, ratio18_1, false);
digital_out BackRight = digital_out(Brain.ThreeWirePort.G);
digital_out FrontWings = digital_out(Brain.ThreeWirePort.E);
digital_out PTO = digital_out(Brain.ThreeWirePort.B);
digital_out Ratchet = digital_out(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1RightShoulderControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonR1/ButtonR2 status to control Intake
      if (Controller1.ButtonR1.pressing()) {
        Intake.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        Intake.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control Hang
      if (Controller1.ButtonX.pressing()) {
        Hang.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        Hang.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        Hang.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
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