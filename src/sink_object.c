#include "sink_object.h"



void reset_object (struct SinkableObject *object) {
	object->label = NULL;
	object->index = 0;
	object->line_number = 0;

	object->local_path = NULL;
	object->remote_path = NULL;
	object->remote_content = NULL;

	object->next = NULL;
	object->prev = NULL;
}

void sync_object (struct SinkableObject *object) {
	if (object == NULL) {
		printf("Called sync_object() on NULL!\n");
		return;
	}

	MESSAGE_SINKABLE_OBJECT("Called sync_object()");
	download_object(object);
	save_object_to_disk(object);
}

void download_object (struct SinkableObject *object) {
	if (object == NULL) {
		printf("Cannot download NULL object!\n");
		return;
	}
}

void save_object_to_disk (struct SinkableObject *object) {
	if (object == NULL) {
		printf("Cannot save NULL object!\n");
		return;
	}

	if (object->remote_content == NULL) {
		MESSAGE_SINKABLE_OBJECT("Cannot save to disk as remote content is empty!");
		return;
	}
}

void delete_sinkable_object (struct SinkableObject *object) {
	free(object->local_path);
	free(object->remote_path);
	if (object->remote_content != NULL) {
		free(object->remote_content);
	}
	free(object);
}


