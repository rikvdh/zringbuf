# zringbuf

[![Build Status](https://travis-ci.org/rikvdh/zringbuf.svg?branch=master)](https://travis-ci.org/rikvdh/zringbuf)

Zero-Allocation ring-buffer in C

## Installation


With [clib](https://github.com/clibs/clib):

```sh
clib install rikvdh/zringbuf
```

## Example

```c
#include "zringbuf.h"
#include <assert.h>

// Create ring-buffer called 'buf' with size of 100 bytes
ZRINGBUF_DECL(buf, 100)

int main(int argc, char **argv)
{
    zringbuf_queue(&buf, 'a');

    zringbuf_queue_arr(&buf, "bcd", 3);

    assert(4 == zringbuf_size_used(&buf));

    char ch;

    assert(true == zringbuf_dequeue(&buf, &ch));
    assert(ch == 'a');

    return 0;
}
```