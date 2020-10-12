#include "sink.h"

#include <string.h>
#include <curl/curl.h>

int debug = false;

void turn_on_debug () {
	debug = true;
}

void turn_off_debug () {
	debug = false;
}

char sinkfile_names[3][10] = {
	"sinkfile",
	"sink.sink",
	"sink"
};

int trim_right (char *str) {
	int n = 0;
	int last_nonspace_index = 0;
	char *ch = str;
	while (*(++ch) != '\0') {
		n++;
		if (*ch != ' ') {
			last_nonspace_index = n;
		}
	}

	str[last_nonspace_index+1] = '\0';
	return last_nonspace_index + 1;
}



struct Sink {
	int label_count;
	int object_count;
	char filename[MAX_FILENAME_LENGTH];

	struct SinkableObject *first_object;
	struct SinkableObject *last_object;

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
};

struct SinkableObject {
	struct Sink *sink;
	int index;
	int line_number;

	char *local_path;
	char *remote_path;
	char *remote_content;

	struct SinkableObject *next;
	struct SinkableObject *prev;
};



struct Sink *get_new_sink () {
	FILE *fp = fopen(sinkfile_names[0], "r");
	char filename[MAX_FILENAME_LENGTH];

	if (fp == NULL) {
		DEBUG_MESSAGE("Not found: %s\n", sinkfile_names[0]);
		fp = fopen(sinkfile_names[1], "r");
		if (fp == NULL) {
			DEBUG_MESSAGE("Not found: %s\n", sinkfile_names[1]);
			fp = fopen(sinkfile_names[2], "r");
			if (fp == NULL) {
				DEBUG_MESSAGE("Not found: %s\n", sinkfile_names[2]);
				return NULL;
			} else {
				DEBUG_MESSAGE("Found: %s\n", sinkfile_names[2]);
				strcpy(filename, sinkfile_names[2]);
			}
		} else {
			DEBUG_MESSAGE("Found: %s\n", sinkfile_names[1]);
			strcpy(filename, sinkfile_names[1]);
		}
	} else {
		DEBUG_MESSAGE("Found: %s\n", sinkfile_names[0]);
		strcpy(filename, sinkfile_names[0]);
	}

	struct Sink *sink = malloc(sizeof (struct Sink));
	strcpy(sink->filename, filename);
	sink->object_count = 0;
	sink->first_object = NULL;
	sink->last_object = NULL;

	char s1[MAX_CHAR] = "";
	char s2[MAX_CHAR] = "";

	int n1 = 0;
	int n2 = 0;

	int object_index = 0;
	int line_number = 1;
	bool equals_found = false;

	char ch;
	while (true) {
		ch = fgetc(fp);

		if (ch == '\n' || ch == EOF) {
			s1[n1] = '\0';
			s2[n2] = '\0';

			n1 = trim_right(s1);
			n2 = trim_right(s2);

			if (equals_found) {
				if (n1 > 0 && n2 > 0) {
					struct SinkableObject *object = malloc(sizeof(struct SinkableObject));
					object->sink = sink;
					object->index = object_index++;
					object->line_number = line_number;
					object->remote_content = NULL;

					object->local_path = malloc((n1+1) * sizeof(char));
					strcpy(object->local_path, s1);
					object->remote_path = malloc((n2+1) * sizeof(char));
					strcpy(object->remote_path, s2);

					add_object_to_sink(sink, object);
				}
			} else if (s1[0] == '[' && s1[n1-1] == ']' && n1 < MAX_LABELNAME_LENGTH) {
				printf("Label: %s\n", s1);
			}

			s1[0] = '\0';
			s2[0] = '\0';
			n1 = 0;
			n2 = 0;

			if (ch == EOF) {
				break;
			} else {
				line_number++;
				equals_found = false;
			}
		} else {
			if (!equals_found && ch == '=') {
				equals_found = true;
			} else {
				if (equals_found){
					if (ch == ' ' && n2 == 0) {
						//
					} else {
						s2[n2++] = ch;
					}
				} else {
					if (ch == ' ' && n1 == 0) {
						//
					} else {
						s1[n1++] = ch;
					}
				}
			}
		}
	}

	fclose(fp);
	return sink;
}

void add_object_to_sink (struct Sink *sink, struct SinkableObject *object) {
	object->next = NULL;
	if (sink->first_object == NULL) {
		sink->first_object = object;
		sink->last_object = object;
		object->prev = NULL;
	} else {
		sink->last_object->next = object;
		object->prev = sink->last_object;
		sink->last_object = object;
	}
	sink->object_count++;
}

void print_sink (struct Sink *sink) {
	struct SinkableObject *object = sink->first_object;
	while (object != NULL) {
		printf("%d. '%s' -=-=- '%s' [on L%d]\n", object->index+1, object->local_path, object->remote_path, object->line_number);
		object = object->next;
	}
}

void sync_sink (struct Sink *sink) {
	if (sink == NULL) {
		printf("Sink is NULL!\n");
		return;
	} else if (sink->object_count == 0) {
		printf("Sink is empty!\n");
		return;
	}

	printf("sync_sink called on --> '%s'\n", sink->filename);
	struct SinkableObject *object = sink->first_object;
	while (object != NULL) {
		sync_object(object);
		object = object->next;
	}
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

void delete_sink (struct Sink *sink) {
	struct SinkableObject *object = sink->first_object;
	while (object != NULL) {
		if (object->next == NULL) {
			DELETE_SINKABLE_OBJECT(object);
		} else {
			object = object->next;
			DELETE_SINKABLE_OBJECT(object->prev);
		}
	}
	free(sink);
}

void delete_sinkable_object (struct SinkableObject *object) {
	free(object->local_path);
	free(object->remote_path);
	if (object->remote_content != NULL) {
		free(object->remote_content);
	}
	free(object);
}


