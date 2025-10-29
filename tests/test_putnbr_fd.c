// test_putnbr_fd.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    const char *path = "tmp_putnbr.txt";
    int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0600);
    if (fd < 0) return 1;
    ft_putnbr_fd(-42, fd);
    lseek(fd,0,SEEK_SET);
    char buf[16] = {0};
    int n = read(fd, buf, 15);
    close(fd); unlink(path);
    if (n <= 0) { fprintf(stderr,"FAIL: putnbr_fd read\n"); return 2; }
    if (strcmp(buf,"-42")!=0) { fprintf(stderr,"FAIL: putnbr_fd -> '%s'\n", buf); return 3; }
    printf("test_putnbr_fd: OK\n");
    return 0;
}
