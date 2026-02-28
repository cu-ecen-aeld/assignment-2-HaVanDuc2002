#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    openlog("writer", LOG_PID, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: %d. Expected 2 arguments (file path and text string).", argc - 1);
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Error opening file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: could not open file %s: %s\n", writefile, strerror(errno));
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    ssize_t nr = write(fd, writestr, strlen(writestr));
    if (nr == -1) {
        syslog(LOG_ERR, "Error writing to file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: could not write to file %s: %s\n", writefile, strerror(errno));
        close(fd);
        closelog();
        return 1;
    } else if ((size_t)nr != strlen(writestr)) {
        syslog(LOG_ERR, "Partial write to file %s: wrote %zd of %zu bytes", writefile, nr, strlen(writestr));
        fprintf(stderr, "Error: partial write to file %s\n", writefile);
        close(fd);
        closelog();
        return 1;
    }

    close(fd);
    closelog();

    return 0;
}
