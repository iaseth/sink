#ifndef SINK_COMMON_H
#define SINK_COMMON_H

#define DEBUG_MESSAGE(...) if (debug_is_on()) {printf(__VA_ARGS__);}

#define true 1
#define false 0
#define bool int

void turn_on_debug ();
void turn_off_debug ();

bool debug_is_on ();
bool debug_is_off ();


#endif