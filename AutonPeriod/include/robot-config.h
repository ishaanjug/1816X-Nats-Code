using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor L1;
extern motor L2;
extern motor L3;
extern motor R1;
extern motor R2;
extern motor R3;
extern inertial Inertial;
extern controller Controller1;
extern motor_group Hang;
extern digital_out BackLeft;
extern motor Intake;
extern digital_out BackRight;
extern digital_out FrontWings;
extern digital_out PTO;
extern digital_out Ratchet;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );