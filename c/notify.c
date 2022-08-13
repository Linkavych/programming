#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

int main(void)
{
    int length;
    int i  = 0;
    int fd;
    int wd;
    char buffer[EVENT_BUF_LEN];

    // Create the inotify instance
    fd = inotify_init();

    //check for error
    if (fd < 0)
    {
        perror("inotify_init");
    }

    // adding /tmp for now
    wd = inotify_add_watch(fd, "/tmp", IN_CREATE | IN_DELETE);

    // read to determine event changes
    length = read(fd, buffer, EVENT_BUF_LEN);

    //test for errors
    if (fd < 0)
    {
        perror("read");
    }

    // read the return of list for changes
    while (i < length) { struct inotify_event *event = (struct inotify_event *) & buffer[i];
        if (event->len)
        {
            if (event->mask & IN_CREATE)
            {
                if (event->mask & IN_ISDIR)
                {
                    printf("New directory created: %s\n", event->name);
                }
                else {
                    printf("New file created: %s\n", event->name);
                }
            }
            else if (event->mask & IN_DELETE)
            {
                if (event->mask & IN_ISDIR)
                {
                    printf("Directory deleted: %s\n", event->name);
                }
                else {
                    printf("File deleted: %s\n", event->name);
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }

    inotify_rm_watch(fd, wd);

    close(fd);
}
