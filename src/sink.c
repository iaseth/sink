#include "sink.h"

#include <string.h>
#include <curl/curl.h>

int debug = 0;

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

struct SinkableObject {
	int line_number;

	char *local_path;
	char *remote_path;
	char *remote_content;

	struct SinkableObject *next;
	struct SinkableObject *prev;
};

struct Sink {
	struct SinkableObject *first_object;
	struct SinkableObject *last_object;
};

void delete_sinkable_object (struct SinkableObject *object) {
	free(object->local_path);
	free(object->remote_path);
	if (object->remote_content != NULL) {
		free(object->remote_content);
	}
	free(object);
}

struct Sink *get_new_sink () {
	FILE *fp = fopen(sinkfile_names[0], "r");

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
			}
		} else {
			DEBUG_MESSAGE("Found: %s\n", sinkfile_names[1]);
		}
	} else {
		DEBUG_MESSAGE("Found: %s\n", sinkfile_names[0]);
	}

	struct Sink *sink = malloc(sizeof (struct Sink));
	sink->first_object = NULL;
	sink->last_object = NULL;

	char s1[MAX_CHAR] = "";
	char s2[MAX_CHAR] = "";

	int n1 = 0;
	int n2 = 0;

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
					object->line_number = line_number;
					object->remote_content = NULL;

					object->local_path = malloc((n1+1) * sizeof(char));
					strcpy(object->local_path, s1);
					object->remote_path = malloc((n2+1) * sizeof(char));
					strcpy(object->remote_path, s2);

					add_object_to_sink(sink, object);
				}
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
	if (sink->first_object == NULL) {
		sink->first_object = object;
		sink->last_object = object;
		object->next = NULL;
		object->prev = NULL;
	} else {
		sink->last_object->next = object;
		object = sink->last_object;
		sink->last_object = object;
	}
}

void print_sink (struct Sink *sink) {
	struct SinkableObject *object = sink->first_object;
	int index = 0;
	while (object != NULL) {
		printf("%d. '%s' -=-=- '%s' [on L%d]\n", index+1, object->local_path, object->remote_path, object->line_number);
		object = object->next;
		index++;
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

