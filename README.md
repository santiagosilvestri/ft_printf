*This project was created as part of the 42 curriculum by sasilves.*

# ft_printf

`ft_printf` is a custom implementation of the standard C `printf()` function. The project introduces variadic functions, formatted output, recursive number conversion, and the creation of a reusable static library.

## Description

The objective of this project is to recreate the essential behavior of `printf()` for a defined group of conversions. The resulting function writes formatted output to the standard output and returns the total number of characters printed.

The implementation does not reproduce the buffering system of the original `printf()`. Instead, every character is written directly with the `write()` system call.

```c
int ft_printf(const char *format, ...);
```

The project produces the following static library:

```text
libftprintf.a
```

## Supported conversions

| Conversion | Description |
|---|---|
| `%c` | Prints a single character. |
| `%s` | Prints a null-terminated string. |
| `%p` | Prints a pointer address in lowercase hexadecimal format. |
| `%d` | Prints a signed decimal integer. |
| `%i` | Prints a signed decimal integer. |
| `%u` | Prints an unsigned decimal integer. |
| `%x` | Prints an unsigned integer in lowercase hexadecimal format. |
| `%X` | Prints an unsigned integer in uppercase hexadecimal format. |
| `%%` | Prints a percent sign. |

A null string is printed as `(null)`, while a null pointer is printed as `(nil)`.

## Project structure

```text
.
├── Makefile
├── ft_printf.c
├── ft_functions.c
└── ft_printf.h
```

- `ft_printf.c` contains the main parser and the conversion dispatcher.
- `ft_functions.c` contains the output and number-conversion helper functions.
- `ft_printf.h` contains the public prototypes and required includes.
- `Makefile` compiles the source files and creates `libftprintf.a`.

## Algorithm and design choices

### Format-string parsing

`ft_printf()` reads the format string from left to right using an index. Normal characters are written immediately. When a `%` character is found, the next character is interpreted as a conversion specifier and passed to `ft_set_format()`.

This sequential approach was selected because the mandatory part only requires a small and fixed set of conversions. It keeps the parser direct, readable, and easy to extend.

### Variadic arguments

The function uses the `va_list` type and the following macros from `<stdarg.h>`:

- `va_start()` initializes access to the unnamed arguments.
- `va_arg()` retrieves the next argument using the type required by the conversion.
- `va_end()` finishes the traversal of the variadic argument list.

The private `ft_set_format()` function acts as a dispatcher. It associates each supported conversion with the correct helper function and extracts the argument with the expected type.

### Number conversion

Decimal and hexadecimal values are printed with `ft_print_base()`. The function selects one of these digit sets:

```text
0123456789
0123456789abcdef
0123456789ABCDEF
```

The conversion is recursive:

1. If the number is greater than or equal to the base length, the function first prints the quotient.
2. It then prints the digit represented by the remainder.
3. Each recursive call contributes to the final character count.

This method avoids dynamic memory allocation and temporary conversion buffers. Its time complexity is proportional to the number of digits, `O(log_b(n))`, and its recursive stack usage follows the same order.

### Signed integers

`ft_print_number()` copies the received `int` into a `long`. This allows the function to safely negate `INT_MIN`, whose positive value cannot be represented by an `int`. Negative values print a leading minus sign before being passed to the unsigned base converter.

### Pointers

Pointers are printed with the `0x` prefix followed by their value in lowercase hexadecimal. A null pointer is handled separately and printed as `(nil)`.

### Character count

Every helper returns the number of characters it printed. `ft_printf()` adds these values and returns the total, following the behavior required by the original `printf()` function during normal output.

### Data structures

No custom structure or dynamically allocated buffer is required for the mandatory implementation. The project uses:

- a `va_list` to traverse variadic arguments;
- an integer index to parse the format string;
- an integer accumulator to store the number of printed characters;
- constant digit strings for base conversion.

A larger parser structure would be useful for flags, width, and precision, but it would add unnecessary complexity to the current mandatory scope.

## Instructions

### Compilation

Clone the repository and run:

```bash
make
```

This compiles the source files with:

```text
-Wall -Wextra -Werror
```

and creates `libftprintf.a` in the root directory.

### Makefile rules

| Command | Action |
|---|---|
| `make` or `make all` | Builds `libftprintf.a`. |
| `make clean` | Removes object files. |
| `make fclean` | Removes object files and the library. |
| `make re` | Rebuilds the project from scratch. |

### Usage

Include the header in a C source file:

```c
#include "ft_printf.h"

int main(void)
{
    int value;

    value = 42;
    ft_printf("Character: %c\n", 'A');
    ft_printf("String: %s\n", "Hello, 42!");
    ft_printf("Integer: %d\n", -42);
    ft_printf("Unsigned: %u\n", 42U);
    ft_printf("Hexadecimal: %x\n", 255U);
    ft_printf("Pointer: %p\n", &value);
    ft_printf("Percent: %%\n");
    return (0);
}
```

Compile the test program with the library:

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o test_printf
```

Run it with:

```bash
./test_printf
```

## Testing

The implementation can be tested by printing the same values with both `ft_printf()` and the original `printf()`, then comparing their output and return values.

Useful cases include:

- zero and negative numbers;
- `INT_MIN` and `INT_MAX`;
- `UINT_MAX`;
- lowercase and uppercase hexadecimal values;
- empty and null strings;
- valid and null pointers;
- several conversions in a single format string;
- the literal percent conversion.

Example:

```c
#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
    int ft_result;
    int original_result;

    ft_result = ft_printf("Value: %d | Hex: %x | Text: %s\n",
            -42, 255U, "hello");
    original_result = printf("Value: %d | Hex: %x | Text: %s\n",
            -42, 255U, "hello");
    printf("ft_printf: %d | printf: %d\n", ft_result, original_result);
    return (0);
}
```

## Resources

- `man 3 printf` - behavior and return value of the original formatted-output function.
- `man 3 stdarg` - variadic arguments and the `va_*` macros.
- `man 2 write` - low-level output through file descriptors.
- [cppreference: Variadic functions](https://en.cppreference.com/w/c/variadic)
- [cppreference: printf family](https://en.cppreference.com/w/c/io/fprintf)
- [GNU C Library Manual: Formatted Output](https://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html)

### Use of AI

AI tools were used as a learning and review assistant to discuss variadic arguments, and the structure and wording of this README.

## Author

**Santiago Silvestri** - `sasilves`
