#ifndef SINK_H
#define SINK_H

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MESSAGE(...) if (debug == 1) {printf(__VA_ARGS__);}

#define CREATE_SINK(x) struct Sink *x; x = get_new_sink();
#define DELETE_SINK(x) delete_sink(x);x=NULL;

#define DELETE_SINKABLE_OBJECT(x) delete_sinkable_object(x);x=NULL;

#define MAX_CHAR 500

#define true 1
#define false 0
#define bool short

struct Sink;
struct SinkableObject;

struct Sink *get_new_sink ();

void add_object_to_sink (struct Sink *sink, struct SinkableObject *object);

void print_sink (struct Sink *sink);

void sync_sink (struct Sink *sink);
void sync_object (struct SinkableObject *object);

void delete_sink (struct Sink *sink);
void delete_sinkable_object (struct SinkableObject *object);



#endif