#include "sink_object.h"

#include "sink_common.h"

#include <curl/curl.h>



void
reset_object (struct SinkObject *object)
{
	object->label = NULL;
	object->index = 0;
	object->line_number = 0;

	object->local_path = NULL;
	object->remote_path = NULL;
	object->remote_content = NULL;

	object->next = NULL;
	object->prev = NULL;
}

void
sync_object (struct SinkObject *object)
{
	if (object == NULL) {
		printf("Called sync_object() on NULL!\n");
		return;
	}

	MESSAGE_SINKABLE_OBJECT("Called sync_object()");
	download_object(object);
	save_object_to_disk(object);
}

void
download_object (struct SinkObject *object)
{
	if (object == NULL) {
		printf("Cannot download NULL object!\n");
		return;
	}

	CURL *curl = object->label->sink->curl;
	CURLcode res;

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, object->remote_path);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		FILE *fp = fopen(object->local_path, "wb");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		res = curl_easy_perform(curl);
		fclose(fp);
		if (res != CURLE_OK) {
			MESSAGE_SINKABLE_OBJECT("Curl problems!");
		}
	}
}

void
save_object_to_disk (struct SinkObject *object)
{
	if (object == NULL) {
		printf("Cannot save NULL object!\n");
		return;
	}

	if (object->remote_content == NULL) {
		MESSAGE_SINKABLE_OBJECT("Cannot save to disk as remote content is empty!");
		return;
	}
}

void
delete_sinkable_object (struct SinkObject *object)
{
	free(object->local_path);
	free(object->remote_path);
	if (object->remote_content != NULL) {
		free(object->remote_content);
	}
	free(object);
}


