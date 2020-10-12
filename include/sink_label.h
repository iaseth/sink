#ifndef SINK_LABLE_H
#define SINK_LABLE_H

#include "sink.h"

#define DELETE_SINK_LABLE(x) delete_sink_label(x);x=NULL;



struct SinkLabel {
	struct Sink *sink;
	int index;
	int line_number;
	int object_count;
	char name[MAX_LABELNAME_LENGTH];

	struct SinkableObject *first_object;
	struct SinkableObject *last_object;

	struct SinkLabel *next;
	struct SinkLabel *prev;
};



void reset_label (struct SinkLabel *label);
void add_object_to_label (struct SinkLabel *label, struct SinkableObject *object);
void print_label (struct SinkLabel *label);
void sync_label (struct SinkLabel *label);
void delete_sink_label (struct SinkLabel *label);



#endif