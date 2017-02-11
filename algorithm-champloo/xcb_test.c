#include <xcb.h>

int main()
{
    xcb_connection_t *c;
    c = xcb_connect(NULL, NULL);

    return 0;
}
