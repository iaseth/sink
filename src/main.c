//#include <stdio.h>

#include "sink.h"

int main (int argc, char const *argv[]) {
	CREATE_SINK(sink);

	print_sink(sink);
	//sync_sink(sink);
	//print_sink(sink);

	DELETE_SINK(sink);
	return 0;
}
