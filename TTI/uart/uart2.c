#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>                     //Used for UART
#include <fcntl.h>                      //Used for UART
#include <termios.h>            //Used for UART

int main (int argc, char* argv[])
{
        int fd, retv;
        struct termios options;
        char str[10]="0xe1";

        if (argc != 2)
        {
                fprintf (stderr, "Usage: %s /dev/ttyx\n", argv[0]);
                exit (1);
        }

        fd = open (argv[1], O_RDWR | O_NOCTTY);
        if (fd < 0)
        {
                perror ("Serial file couldn't be opend !");
                return -1;
        }

        tcgetattr(fd, &options);
        options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;               //<Set baud rate
        options.c_iflag = IGNPAR;
        options.c_oflag = 0;
        options.c_lflag = 0;
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd, TCSANOW, &options);

        retv = write(fd, str, strlen(str));
        printf ("Sent bytes: %d\n", retv);

        return 0;
}