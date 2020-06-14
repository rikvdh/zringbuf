#ifndef ZRINGBUF_H__
#define ZRINGBUF_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define ZRINGBUF_DECL(name, size) \
	static char name##_data[size]; \
	static struct zringbuf name = { name##_data, size, 0, 0 };

/**
 * Structure which holds a ring buffer
 */
struct zringbuf {
	/** Buffer memory. */
	char *buffer;
	size_t size;
	/** Index of tail. */
	size_t tail_index;
	/** Index of head. */
	size_t head_index;
};

/**
 * Initializes the ring buffer
 * This function can also be used to reset the buffer, it does not clear the data
 */
void zringbuf_init(struct zringbuf *buffer);

/**
 * Adds a byte to a ring buffer
 * @param data The byte to add
 */
void zringbuf_queue(struct zringbuf *buffer, char data);

/**
 * Adds an array of bytes to a ring buffer
 * @param data A pointer to the array of bytes to place in the queue
 * @param size The size of the array
 */
void zringbuf_queue_arr(struct zringbuf *buffer, const char *data, size_t size);

/**
 * Returns the oldest byte in a ring buffer
 * @param data A pointer to the location at which the data should be placed.
 * @return 1 if data was returned; 0 otherwise.
 */
bool zringbuf_dequeue(struct zringbuf *buffer, char *data);

/**
 * Returns the len oldest bytes in a ring buffer
 * @param data A pointer to the array at which the data should be placed.
 * @param len The maximum number of bytes to return.
 * @return The number of bytes returned.
 */
size_t zringbuf_dequeue_arr(struct zringbuf *buffer, char *data, size_t len);
/**
 * Peeks a ring buffer, i.e. returns an element without removing it
 * @param data A pointer to the location at which the data should be placed.
 * @param index The index to peek.
 * @return 1 if data was returned; 0 otherwise.
 */
bool zringbuf_peek(struct zringbuf *buffer, char *data, size_t index);

/**
 * Returns whether a ring buffer is empty
 * @return true for empty, false otherwise
 */
bool zringbuf_is_empty(struct zringbuf *buffer);

/**
 * Returns whether the ring buffer is full
 * @return true when full, false otherwise
 */
bool zringbuf_is_full(struct zringbuf *buffer);

/**
 * Returns the number of used bytes in the buffer
 * @return used bytes
 */
size_t zringbuf_size_used(struct zringbuf *buffer);

/**
 * Returns the buffer-capacity (n - 1)
 */
size_t zringbuf_capacity(struct zringbuf *buffer);

#endif /* ZRINGBUF_H__ */
