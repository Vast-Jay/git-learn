#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct rtc_time {
    unsigned int year;
    unsigned int mon;
    unsigned int day;
    unsigned int hour;
    unsigned int min;
    unsigned int sec;
};

int main(void)
{
    int fd;
    int len, ret;
    struct rtc_time tm;

    fd = open("/dev/rtc1-demo", O_RDWR);
    if (fd == -1) {
        printf("cannot open file..\n");
        exit(1);
    }

    len = sizeof(struct rtc_time);
    if ((ret = read(fd, &tm, len)) < len) {
        printf("read error!\n");
        exit(1);
    }

    printf("%d:%d:%d\n", tm.hour, tm.min, tm.sec);
    close(fd);

    return 0;
}