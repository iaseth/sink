#include "sink_label.h"

#include <stdlib.h>

#include "sink_common.h"



void reset_label (struct SinkLabel *label) {
	label->sink = NULL;
	label->index = 0;
	label->object_count = 0;
	label->name[0] = '\0';

	label->first_object = NULL;
	label->last_object = NULL;

	label->next = NULL;
	label->prev = NULL;
}

void add_object_to_label (struct SinkLabel *label, struct SinkObject *object) {
	object->label = label;
	object->next = NULL;
	if (label->first_object == NULL) {
		label->first_object = object;
		label->last_object = object;
		object->prev = NULL;
	} else {
		label->last_object->next = object;
		object->prev = label->last_object;
		label->last_object = object;
	}
	label->object_count++;
	label->sink->object_count++;
}

void print_label (struct SinkLabel *label) {
	if (label == NULL) {
		printf("print_label() called with NULL!\n");
	}

	PRINT_TAB;
	printf("Label: [%s] (%d objects)\n", label->name, label->object_count);
	struct SinkObject *object = label->first_object;
	while (object != NULL) {
		PRINT_TAB; PRINT_TAB;
		printf("%d. '%s' -=-=- '%s' [on L%d]\n", object->index+1, object->local_path, object->remote_path, object->line_number);
		object = object->next;
	}
}

void sync_label (struct SinkLabel *label) {
	if (label == NULL) {
		printf("Called sync_label() on NULL!\n");
		return;
	}

	MESSAGE_SINK_LABLE("called sync_label (%s)", label->name);
	struct SinkObject *object = label->first_object;
	while (object != NULL) {
		sync_object(object);
		object = object->next;
	}
}

void delete_sink_label (struct SinkLabel *label) {
	struct SinkObject *object = label->first_object;
	while (object != NULL) {
		if (object->next == NULL) {
			DELETE_SINKABLE_OBJECT(object);
		} else {
			object = object->next;
			DELETE_SINKABLE_OBJECT(object->prev);
		}
	}
	free(label);
}


