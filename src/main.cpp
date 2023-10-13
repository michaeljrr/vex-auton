#include "main.h"
#include <string.h>
#include <math.h>


pros::ADIEncoder quadencoder ('E', 'F');
extern double X;
extern double Y;
extern double theta;
extern double encdL;
extern double encdR;
extern double torad;
extern double dleft;
extern double dright;

void printer();
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

void on_center_button() {
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
 void initialize() {
	pros::lcd::initialize();

	//while(1) {
		//std::cout << "test\n";
		//pros::delay(100);
	//}
	//pros::Task fkingodometry(Odometry); 
	//pros::Task fkingcontrol(Control);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Task printing(printer);
	pros::Task odom(Odometry);
}

std::string prevGuessPos;

void printer() {
	using namespace pros;
	Motor lf_wheel (1);
	Motor rf_wheel (9); 
	while(1) {
		//lf_wheel.move(100);
		//rf_wheel.move(100);
        std::string pX = std::to_string(X);
        std::string pY = std::to_string(Y);
		std::string pTheta = std::to_string(theta / torad);
		int guessPos =  guessMovement(dleft, dright);
		std::string nguessPos;
		//short (and heinous) converter for guessPos:
		if(guessPos == 1){nguessPos = "Moving in an arc position to the left";}
		else if(guessPos == 2){nguessPos = "Moving in an arc position to the right";}
		else if(guessPos == 3){nguessPos = "Moving in a circle clockwise";}
		else if(guessPos == 4){nguessPos = "Moving in a circle anticlockwise";}
		else if(guessPos == 5){nguessPos = "Only right wheel moving";}
		else if(guessPos == 6){nguessPos = "Only left wheel moving";}
		else if(guessPos == 7){nguessPos = "Robot not moving, stationary";}
		else if(guessPos == 8){nguessPos = "Moving forward";}
		else if(guessPos == 9){nguessPos = "Moving backward";}
		//std::string p = std::to_string(rf_wheel.get_position());
        

		//std::string rightwheel = std::to_string(rf_wheel.get_position());
		//std::string leftwheel = std::to_string(lf_wheel.get_position());
		//lcd::set_text(1,"test");
		//pros::lcd::set_text(1,print1 + "    " + print2);
		//pros::lcd::set_text(3,print3 + "    " + print4);

		//lcd::set_text(1,print1 + "   " + print2 + "   " + print3);
		//printf("X: %f           Y: %f           Theta: %f              Position Guess: %s", pX, pY, pTheta, nguessPos);
		
		//std::cout << rightwheel << "   " << leftwheel << std::endl;
		//std::cout << encdL << "    "<< encdR << std::endl;

		
		if(prevGuessPos != nguessPos){std::cout << nguessPos <<std::endl;}
		prevGuessPos = nguessPos;
		printf("X: %f          Y: %f        Theta: %f          \n", X, Y, theta/torad);
		
		delay(500);
	}
}
