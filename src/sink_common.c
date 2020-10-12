#include "sink_common.h"



int debug = false;

void turn_on_debug () {
	debug = true;
}

void turn_off_debug () {
	debug = false;
}

bool debug_is_on () {
	if (debug) {
		return true;
	}
	return false;
}

bool debug_is_off () {
	if (debug) {
		return false;
	}
	return true;
}


