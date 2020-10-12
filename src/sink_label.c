#include "sink_label.h"

#include "sink.h"

#include <stdlib.h>



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


