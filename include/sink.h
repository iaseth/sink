#ifndef SINK_H
#define SINK_H

#include <stdio.h>
#include <stdlib.h>

#include "sink_label.h"
#include "sink_object.h"

#define CREATE_SINK(x) struct Sink *x; x = get_new_sink();
#define DELETE_SINK(x) delete_sink(x);x=NULL;

#define MAX_CHAR 500
#define MAX_FILENAME_LENGTH 50



struct Sink {
	int label_count;
	int object_count;
	char filename[MAX_FILENAME_LENGTH];

	struct SinkLabel *first_label;
	struct SinkLabel *last_label;
};

void reset_sink (struct Sink *sink);

struct Sink *get_new_sink ();

void add_label_to_sink (struct Sink *sink, struct SinkLabel *label);
void print_sink (struct Sink *sink);
void sync_sink (struct Sink *sink);
void delete_sink (struct Sink *sink);



#endif