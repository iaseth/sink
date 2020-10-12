#ifndef SINK_OBJECT_H
#define SINK_OBJECT_H

#include "sink.h"

#define DELETE_SINKABLE_OBJECT(x) delete_sinkable_object(x);x=NULL;
#define MESSAGE_SINKABLE_OBJECT(...) PRINT_TAB; PRINT_TAB; printf("(%d of %d) %s [%s] ---> ", (object->index+1), object->label->sink->object_count, object->local_path, object->remote_path); printf(__VA_ARGS__); printf("\n");



struct SinkObject {
	struct SinkLabel *label;
	int index;
	int line_number;

	char *local_path;
	char *remote_path;
	char *remote_content;

	struct SinkObject *next;
	struct SinkObject *prev;
};

void reset_object (struct SinkObject *object);

void sync_object (struct SinkObject *object);
void download_object (struct SinkObject *object);
void save_object_to_disk (struct SinkObject *object);
void delete_sinkable_object (struct SinkObject *object);


#endif