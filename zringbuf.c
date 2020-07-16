#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "zringbuf.h"

void zringbuf_init(struct zringbuf *buffer)
{
	buffer->tail_index = 0;
	buffer->head_index = 0;
}

void zringbuf_queue(struct zringbuf *buffer, char data)
{
	/* Is buffer full? */
	if (zringbuf_is_full(buffer)) {
		/* Is going to overwrite the oldest byte */
		/* Increase tail index */
		buffer->tail_index = ((buffer->tail_index + 1) % buffer->size);
	}

	/* Place data in buffer */
	buffer->buffer[buffer->head_index] = data;
	buffer->head_index = ((buffer->head_index + 1) % buffer->size);
}

void zringbuf_queue_arr(struct zringbuf *buffer, const char *data, size_t size)
{
	/* Add bytes; one by one */
	size_t i;
	for (i = 0; i < size; i++) {
		zringbuf_queue(buffer, data[i]);
	}
}

bool zringbuf_dequeue(struct zringbuf *buffer, char *data)
{
	if (zringbuf_is_empty(buffer)) {
		/* No items */
		return false;
	}

	/* Optionally skip reading data and just 'consume' the buffer */
	if (data != NULL) {
		*data = buffer->buffer[buffer->tail_index];
	}
	buffer->tail_index = ((buffer->tail_index + 1) % buffer->size);
	return true;
}

size_t zringbuf_dequeue_arr(struct zringbuf *buffer, char *data, size_t len)
{
	if (zringbuf_is_empty(buffer)) {
		/* No items */
		return 0;
	}

	char *data_ptr = data;
	size_t cnt = 0;
	while ((cnt < len) && zringbuf_dequeue(buffer, data_ptr)) {
		cnt++;
		data_ptr++;
	}
	return cnt;
}

bool zringbuf_peek(struct zringbuf *buffer, char *data, size_t index)
{
	if (index >= zringbuf_size_used(buffer)) {
		/* No items at index */
		return false;
	}

	/* Add index to pointer */
	const size_t data_index = ((buffer->tail_index + index) % buffer->size);
	*data = buffer->buffer[data_index];
	return true;
}

bool zringbuf_is_empty(struct zringbuf *buffer)
{
	return buffer->head_index == buffer->tail_index;
}

bool zringbuf_is_full(struct zringbuf *buffer)
{
	return zringbuf_size_used(buffer) == zringbuf_capacity(buffer);
}

size_t zringbuf_size_used(struct zringbuf *buffer)
{
	const size_t sbm = buffer->head_index - buffer->tail_index + buffer->size;
	return sbm % buffer->size;
}

size_t zringbuf_capacity(struct zringbuf *buffer)
{
	return buffer->size - 1;
}
