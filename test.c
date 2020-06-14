#include "zringbuf.h"

#include <stdint.h>
#include <string.h>
#include <assert.h>

ZRINGBUF_DECL(buf, 100)

int main(void)
{
	// Check if new buffer is empty
	assert(true == zringbuf_is_empty(&buf));
	assert(false == zringbuf_is_full(&buf));
	assert(0 == zringbuf_size_used(&buf));

	// Fill the buffer to capacity - 1
	for (int i = 0; i < zringbuf_capacity(&buf) - 1; i++) {
		zringbuf_queue(&buf, 'a');
		assert(false == zringbuf_is_empty(&buf));
		assert(false == zringbuf_is_full(&buf));
		assert((i + 1) == zringbuf_size_used(&buf));
	}
	// Add one char to buffer and check for full
	zringbuf_queue(&buf, 'a');
	assert(false == zringbuf_is_empty(&buf));
	assert(true == zringbuf_is_full(&buf));
	assert(zringbuf_capacity(&buf) == zringbuf_size_used(&buf));

	// Add another and check if still full (this overwrites)
	zringbuf_queue(&buf, 'b');
	assert(false == zringbuf_is_empty(&buf));
	assert(true == zringbuf_is_full(&buf));
	assert(zringbuf_capacity(&buf) == zringbuf_size_used(&buf));

	char ch;

	// Retrieve all a's (minus 1 which was overwritten by a 'b')
	for (int i = 0; i < zringbuf_capacity(&buf) - 1; i++) {
		assert(true == zringbuf_dequeue(&buf, &ch));
		assert('a' == ch);
		assert(false == zringbuf_is_full(&buf));
		assert(false == zringbuf_is_empty(&buf));
	}

	// And the last written 'b'
	assert(true == zringbuf_dequeue(&buf, &ch));
	assert('b' == ch);
	assert(false == zringbuf_is_full(&buf));
	assert(true == zringbuf_is_empty(&buf));
	assert(0 == zringbuf_size_used(&buf));

    return 0;
}
