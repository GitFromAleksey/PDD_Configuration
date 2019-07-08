#ifndef MOTOR_H
#define MOTOR_H

/*  The stepper motor is what moves our platen
 *
 * takeStepUp()  - steps the motor one step forward
 * takeStepRevers()   - steps the motor one step in reverse
 * resetPosition()    - resets the position tracking.
 * position()         - returns the position of our motor
 * disable()          - turn off the power for the stepper motor
 */

namespace StepperMotor {
    void takeStepUp();
    void takeStepDown();
    void resetPosition();
    long position();
    void disable();
};

#endif
