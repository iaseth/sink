#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MESSAGE(...) if (debug == 1) {printf(__VA_ARGS__);}

int debug = 1;

char sinkfile_names[3][10] = {
	"sinkfile",
	"sink.sink",
	"sink"
};

struct SinkableObject {
	char *local_path;
	char *remote_path;
	char *remote_content;

	struct SinkableObject *next;
	struct SinkableObject *prev;
};

struct Sink {
	struct SinkableObject *first_object;
};

struct Sink *getNewSink () {
	FILE *fp = fopen(sinkfile_names[0], "r");

	if (fp == NULL) {
		DEBUG_MESSAGE("Not found: %s\n", sinkfile_names[0]);
		fp = fopen(sinkfile_names[1], "r");
		if (fp == NULL) {
			DEBUG_MESSAGE("Not found: %s\n", sinkfile_names[1]);
			fp = fopen(sinkfile_names[2], "r");
			if (fp == NULL) {
				DEBUG_MESSAGE("Not found: %s\n", sinkfile_names[2]);
				return NULL;
			} else {
				DEBUG_MESSAGE("Found: %s\n", sinkfile_names[2]);
			}
		} else {
			DEBUG_MESSAGE("Found: %s\n", sinkfile_names[1]);
		}
	} else {
		DEBUG_MESSAGE("Found: %s\n", sinkfile_names[0]);
	}
	return NULL;
}

void printSink (struct Sink *sink) {
	//
}

int main(int argc, char const *argv[])
{
	struct Sink *sink;
	sink = getNewSink();
	return 0;
}
