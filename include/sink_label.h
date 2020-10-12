#ifndef SINK_LABLE_H
#define SINK_LABLE_H

#include "sink.h"

#define MAX_LABELNAME_LENGTH 50

#define DELETE_SINK_LABLE(x) delete_sink_label(x);x=NULL;
#define MESSAGE_SINK_LABLE(...) PRINT_TAB; printf("(%d of %d) [%s] ---> ", (label->index+1), label->sink->label_count, label->name); printf(__VA_ARGS__); printf("\n");



struct SinkLabel {
	struct Sink *sink;
	int index;
	int line_number;
	int object_count;
	char name[MAX_LABELNAME_LENGTH];

	struct SinkObject *first_object;
	struct SinkObject *last_object;

	struct SinkLabel *next;
	struct SinkLabel *prev;
};



void reset_label (struct SinkLabel *label);
void add_object_to_label (struct SinkLabel *label, struct SinkObject *object);
void print_label (struct SinkLabel *label);
void sync_label (struct SinkLabel *label);
void delete_sink_label (struct SinkLabel *label);



#endif