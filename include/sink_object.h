#ifndef SINK_OBJECT_H
#define SINK_OBJECT_H

#include "sink.h"

#define DELETE_SINKABLE_OBJECT(x) delete_sinkable_object(x);x=NULL;
#define MESSAGE_SINKABLE_OBJECT(...) printf("(%d of %d) %s [%s] ---> ", (object->index+1), object->label->sink->object_count, object->local_path, object->remote_path); printf(__VA_ARGS__); printf("\n");



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

void reset_object (struct SinkableObject *object);

void sync_object (struct SinkableObject *object);
void download_object (struct SinkableObject *object);
void save_object_to_disk (struct SinkableObject *object);
void delete_sinkable_object (struct SinkableObject *object);


#endif