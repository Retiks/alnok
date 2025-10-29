// test_putendl_fd.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    const char *path = "tmp_putendl.txt";
    int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0600);
    if (fd < 0) return 1;
    ft_putendl_fd("Line", fd);
    lseek(fd,0,SEEK_SET);
    char buf[6] = {0};
    read(fd, buf, 5);
    close(fd); unlink(path);
    if (strcmp(buf,"Line\n")!=0){ fprintf(stderr,"FAIL: putendl_fd got '%s'\n", buf); return 2; }
    printf("test_putendl_fd: OK\n");
    return 0;
}
