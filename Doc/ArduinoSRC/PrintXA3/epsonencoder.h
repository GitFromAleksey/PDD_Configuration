#ifndef EPSONENCODER_H
#define EPSONENCODER_H

/*  The epson encoder is a rotary shaft encoder that keeps track of the position of the
 *  print head on the "page" being printed.
 *
 *  reset()             - We call this to reset our the counter - eg. when the plate is in the back and
 *                        ready to start a print.
 *  hasMoved()          - returns true if the encoder position has changed since last time we checked.
 *  possition()   - returns current possition registerd by the EpsonEncoder
 */

namespace EpsonEncoder {
    void reset();
    bool hasMoved();
    long position();
    bool isAtEdgeOfPlaten();
	void enable();
	void disable();
	void onEncA();
	void onEncB();
	void update();
}

#endif
