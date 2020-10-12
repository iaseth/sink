#ifndef SINK_H
#define SINK_H

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MESSAGE(...) if (debug == 1) {printf(__VA_ARGS__);}

#define CREATE_SINK(x) struct Sink *x; x = get_new_sink();
#define DELETE_SINK(x) delete_sink(x);x=NULL;

#define DELETE_SINKABLE_OBJECT(x) delete_sinkable_object(x);x=NULL;

#define MESSAGE_SINKABLE_OBJECT(...) printf("(%d of %d) %s [%s] ---> ", (object->index+1), object->sink->object_count, object->local_path, object->remote_path); printf(__VA_ARGS__); printf("\n");

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

void reset_sink (struct Sink *sink);
void reset_label (struct SinkLabel *label);

struct Sink *get_new_sink ();

void add_object_to_sink (struct Sink *sink, struct SinkableObject *object);

void print_sink (struct Sink *sink);

void sync_sink (struct Sink *sink);
void sync_object (struct SinkableObject *object);
void download_object (struct SinkableObject *object);
void save_object_to_disk (struct SinkableObject *object);

void delete_sink (struct Sink *sink);
void delete_sinkable_object (struct SinkableObject *object);



#endif