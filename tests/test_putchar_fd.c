// test_putchar_fd.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    const char *path = "tmp_putchar.txt";
    int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0600);
    if (fd < 0) { perror("open"); return 1; }
    ft_putchar_fd('X', fd);
    lseek(fd, 0, SEEK_SET);
    char buf[2] = {0};
    read(fd, buf, 1);
    close(fd); unlink(path);
    if (buf[0] != 'X') { fprintf(stderr,"FAIL: putchar_fd\n"); return 2; }
    printf("test_putchar_fd: OK\n");
    return 0;
}
