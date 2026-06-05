*This project has been created as part of the 42 curriculum by gpecelli.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a file descriptor. Each successive call to the function continues reading from where the previous one left off, making it possible to iterate through an entire file line by line with a simple loop.

The project introduces one of the most important concepts in C programming: **static variables**. A static local variable persists its value between function calls, allowing `get_next_line` to maintain a buffer (called `storage`) across invocations without using global variables.

The function handles reading from both regular files and standard input (`stdin`), and correctly returns the trailing `\n` character as part of the line — except when the file ends without one.

### Algorithm overview and justification

The implementation is split into four main functions:

1. **`read_and_archive`** — Reads chunks of data from the file descriptor into a fixed-size buffer (of `BUFFER_SIZE` bytes) and appends each chunk to the persistent `storage` string using `ft_strjoin_and_free`. This continues until either a newline character is found in `storage` or the end of file is reached. The approach avoids reading the entire file at once: as soon as a `\n` is detected in the accumulated storage, the read loop stops, keeping I/O minimal per call.

2. **`extract_line`** — Scans `storage` up to and including the first `\n` (or end of string), allocates a new string of exactly the right size, and copies the line into it. This produces the return value for the caller.

3. **`clean_storage`** — After extracting the line, saves whatever remains after the `\n` into a new allocation and frees the old `storage`. This leftover content becomes the starting point for the next call, preventing redundant reads.

4. **`del`** — A safe free helper that sets the pointer to `NULL` after freeing, used throughout for defensive memory management.

This design was chosen because it is clean, easy to reason about, and keeps memory ownership explicit. Each function has a single responsibility, which makes the logic for memory allocation and deallocation straightforward to verify and avoids double-free scenarios.

The `BUFFER_SIZE` value is compile-time configurable, meaning the function works correctly whether chunks are 1 byte or 10,000,000 bytes — the logic does not depend on the buffer size being any particular value.

---

## Instructions

### Compilation

Compile with a custom buffer size using the `-D BUFFER_SIZE=n` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test
```

The project can also be compiled without the flag; the default buffer size is `42` as defined in `get_next_line.h`.

### Usage example

First, generate a test file by running **`man 3 printf > printf.txt`** in your terminal, then insert it in the main, compile and run:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		count;
	int		set_line;

	set_line = 20;
	count = 1;
	fd = open("./file.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open the file.\n");
		return (1);
	}
	printf("--- TEST (BUFFER_SIZE: %d) ---\n", BUFFER_SIZE);
	printf("--- TEST (Number of line: %d) ---\n", set_line);
	while (count <= set_line && (line = get_next_line(fd)) != NULL)
	{
	    printf("Line %d: %s\n", count++, line);
	    free(line);
	}
	printf("\n--- END TEST ---\n");
	close(fd);
	return (0);
}
```

### Files

| File | Description |
|---|---|
| `get_next_line.c` | Core logic: `get_next_line`, `read_and_archive`, `extract_line`, `clean_storage`, `del` |
| `get_next_line_utils.c` | Helper functions: `ft_strlen`, `ft_strchr`, `ft_strdup`, `ft_strjoin_and_free`, `row_len` |
| `get_next_line.h` | Header with prototypes and `BUFFER_SIZE` definition |

---

## Resources

- [C static variables — cppreference](https://en.cppreference.com/w/c/language/storage_duration)
- [read() system call — man7.org](https://man7.org/linux/man-pages/man2/read.2.html)
- [File descriptors explained — GNU libc manual](https://www.gnu.org/software/libc/manual/html_node/File-Descriptors.html)
- [Memory management in C — Valgrind documentation](https://valgrind.org/docs/manual/mc-manual.html)

### AI usage

AI was used as a general learning guide during this project — specifically to better understand how static variables work across function calls, and to reason through memory management: when to allocate, when to free, and how to avoid double-free or use-after-free bugs. AI was not used to generate any code directly. All implementation decisions and the code itself were written independently.

Testing and leak detection were performed using the following compiler flags:

```bash
cc -Wall -Wextra -Werror -g3 -fsanitize=address,undefined -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test
```

`-g3` provides full debug symbols and macro information, while `-fsanitize=address,undefined` detects memory leaks, buffer overflows, use-after-free, and undefined behaviour at runtime.
