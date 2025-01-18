#include "my_realization.h"
#include <stdarg.h>
#include <stddef.h>

static char digit_to_char(size_t digit)
{
    return (char)('0' + digit);
}

static size_t write_octal(size_t num, char *dst, size_t offset, size_t n)
{
    if (num == 0)
    {
        if (n > 0 && offset < (n - 1))
        {
            dst[offset] = '0';
        }
        return 1;
    }

    size_t temp = num;
    size_t len = 0;
    while (temp > 0)
    {
        temp /= 8;
        len++;
    }
    
    size_t power = 1;
    for (size_t i = 1; i < len; i++)
    {
        power *= 8;
    }

    for (size_t i = 0; i < len; i++)
    {
        size_t digit = num / power;  
        num = num % power;

        if (n > 0 && offset < (n - 1))
        {
            dst[offset] = digit_to_char(digit);
        }
        offset++;
        power /= 8;
    }

    return len;
}

static size_t copy_string(const char *src, char *dst, size_t offset, size_t n)
{
    size_t len = 0;
    while (src[len] != '\0')
    {
        if (n > 0 && offset + len < (n - 1))
        {
            dst[offset + len] = src[len];
        }
        len++;
    }
    return len;
}

int my_snprintf(char *dst, size_t n, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    size_t written = 0;
    size_t total_len = 0;

    const char *p = format;
    while (*p != '\0')
    {
        if (*p == '%')
        {
            p++;
            if (*p == '\0')
            {
                break;
            }

            if (*p == 's')
            {
                const char *str_arg = va_arg(args, const char *);
                if (!str_arg)
                {
                    continue;
                }
                size_t len = copy_string(str_arg, dst, written, n);
                written += len;
                total_len += len;
            }
            else if (*p == 'o')
            {
                size_t num = va_arg(args, size_t);
                size_t len = write_octal(num, dst, written, n);
                written += len;
                total_len += len;
            }
            else
            {
                if (n > 0 && written < (n - 1))
                {
                    dst[written] = '%';
                }
                written++;
                total_len++;

                if (*p != '\0')
                {
                    if (n > 0 && written < (n - 1))
                    {
                        dst[written] = *p;
                    }
                    written++;
                    total_len++;
                }
            }
        }
        else
        {
            if (n > 0 && written < (n - 1))
            {
                dst[written] = *p;
            }
            written++;
            total_len++;
        }
        p++;
    }
    if (n > 0)
    {
        size_t end_index = (written < n) ? written : (n - 1);
        dst[end_index] = '\0';
    }

    va_end(args);

    return total_len;
}
