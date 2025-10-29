// test_putstr_fd.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    const char *path = "tmp_putstr.txt";
    int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0600);
    if (fd < 0) return 1;
    ft_putstr_fd("Hello", fd);
    lseek(fd,0,SEEK_SET);
    char buf[6] = {0};
    read(fd, buf, 5);
    close(fd); unlink(path);
    if (strcmp(buf,"Hello")!=0){ fprintf(stderr,"FAIL: putstr_fd\n"); return 2; }
    printf("test_putstr_fd: OK\n");
    return 0;
}
