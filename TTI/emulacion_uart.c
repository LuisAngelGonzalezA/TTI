    /*

    https://es.pinout.xyz/pinout/uart

    */


    #include <stdio.h>
    #include <string.h>
    #include <errno.h>
    #include <wiringPi.h>
    #include <wiringSerial.h>
    int main ()
    {  

    int fd ;
    int count ;
    char ch[100];


     fd = serialOpen ("/dev/ttyAMA0", 9600);
     wiringPiSetup ();
    printf (" -------after wiringPiSetup----\n") ;
    serialPuts(fd,"hi dear"); //Sends the nul-terminated string to the serial device
    delay(2000);
    serialPrintf(fd,ch); //Emulates the system printf function to the serial device
    printf ("%s", ch) ;    
    printf (" -------end main----\n") ;
    return 0 ;
    }
