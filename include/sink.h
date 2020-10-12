#ifndef SINK_H
#define SINK_H

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MESSAGE(...) if (debug == 1) {printf(__VA_ARGS__);}

#define CREATE_SINK(x) struct Sink *x; x = get_new_sink();
#define DELETE_SINK(x) delete_sink(x);x=NULL;

#define DELETE_SINK_LABLE(x) delete_sink_label(x);x=NULL;
#define DELETE_SINKABLE_OBJECT(x) delete_sinkable_object(x);x=NULL;

#define MESSAGE_SINKABLE_OBJECT(...) printf("(%d of %d) %s [%s] ---> ", (object->index+1), object->label->sink->object_count, object->local_path, object->remote_path); printf(__VA_ARGS__); printf("\n");

#define MAX_CHAR 500
#define MAX_FILENAME_LENGTH 50
#define MAX_LABELNAME_LENGTH 50

#define true 1
#define false 0
#define bool short

void turn_on_debug ();
void turn_off_debug ();

struct Sink;
struct SinkLabel;
struct SinkableObject;




struct Sink {
	int label_count;
	int object_count;
	char filename[MAX_FILENAME_LENGTH];

	struct SinkLabel *first_label;
	struct SinkLabel *last_label;
};

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

struct SinkableObject {
	struct SinkLabel *label;
	int index;
	int line_number;

	char *local_path;
	char *remote_path;
	char *remote_content;

	struct SinkableObject *next;
	struct SinkableObject *prev;
};

void reset_sink (struct Sink *sink);
void reset_object (struct SinkableObject *object);

struct Sink *get_new_sink ();

void add_label_to_sink (struct Sink *sink, struct SinkLabel *label);
void add_object_to_label (struct SinkLabel *label, struct SinkableObject *object);

void print_sink (struct Sink *sink);
void print_label (struct SinkLabel *label);

void sync_sink (struct Sink *sink);
void sync_label (struct SinkLabel *label);
void sync_object (struct SinkableObject *object);
void download_object (struct SinkableObject *object);
void save_object_to_disk (struct SinkableObject *object);

void delete_sink (struct Sink *sink);
void delete_sink_label (struct SinkLabel *label);
void delete_sinkable_object (struct SinkableObject *object);



#endif