#include <stdio.h>
#include <uchardet.h>

// Runs uchardet on stdin and prints the result to stdout

int main(void)
{
    uchardet_t handle = uchardet_new();
    if (handle == NULL)
    {
        perror("uchardet_new");
        return 1;
    }

    // Read all data into uchardet
    for (;;)
    {
        char buf[4096];
        size_t len = fread(buf, 1, sizeof(buf), stdin);
        if (ferror(stdin))
        {
            perror("fread");
            uchardet_delete(handle);
            return 1;
        }

        if (uchardet_handle_data(handle, buf, len) != 0)
        {
            perror("uchardet_handle_data");
            return 1;
        }

        if (len < sizeof(buf))
            break;
    }

    // Get character set
    uchardet_data_end(handle);
    puts(uchardet_get_charset(handle));
    uchardet_delete(handle);
    return 0;
}
