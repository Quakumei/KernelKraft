/*
 * ioctl.c - the process to use ioctl's to control the kernel module
 *
 * Until now we could have used cat for input and output. But now
 * we need to do ioctl's, which require writing our own process.
 */
/*
 * device specifics, such as ioctl numbers and the
 * major device file.
 */
#include "chardev.h"
#include <fcntl.h> /* open */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h> /* ioctl */
#include <unistd.h>    /* exit */
/*
 * Functions for the ioctl calls
 */
void ioctl_set_msg(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_SET_MSG, message);
    if (ret_val < 0)
    {
        printf("ioctl_set_msg failed:%d\n", ret_val);
        exit(-1);
    }
    putchar('\n');
}
void ioctl_write_file(int file_desc, FILE *file_write_desc){
    int ret_val;
    char message[100];
    long lSize;
    fseek (file_write_desc , 0 , SEEK_END);
    lSize = ftell (file_write_desc);
    rewind (file_write_desc);
    fread(message, 1,lSize, file_write_desc);
    message[lSize] = '\0';
    ioctl_set_msg(file_desc, message);
}
    // ret_val = ioctl(file_desc, IOCTL_SET_MSG, message);
    // if (ret_val < 0)
    // {
    //     printf("ioctl_write_file failed:%d\n", ret_val);
    //     exit(-1);
    // }



void ioctl_get_msg(int file_desc)
{
    int ret_val;
    char message[100];
    /*
     * Warning - this is dangerous because we don't tell
     * the kernel how far it's allowed to write, so it
     * might overflow the buffer. In a real production
     * program, we would have used two ioctls - one to tell
     * the kernel the buffer length and another to give
     * it the buffer to fill
     */
    ret_val = ioctl(file_desc, IOCTL_GET_MSG, message);
    if (ret_val < 0)
    {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    printf("get_msg message:%s\n", message);
}
void ioctl_get_nth_byte(int file_desc)
{
    int i;
    char c;
    printf("get_nth_byte message:");
    i = 0;
    do
    {
        c = ioctl(file_desc, IOCTL_GET_NTH_BYTE, i++);
        if (c < 0)
        {
            printf("ioctl_get_nth_byte failed at the %d'th byte:\n", i);
            exit(-1);
        }
        putchar(c);
    } while (c != 0);
    printf("\n");

    putchar('\n');
}
/*
 * Main - Call the ioctl functions
 */



int main()
{
    int file_desc, ret_val;
    char *msg = "JARKO CI/CD\n";
    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0)
    {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }
    printf("Chardev before:\n");
    ioctl_get_msg(file_desc);

    FILE * fp;
    fp = fopen("short", "r");
    if (!fp) // checking of error
			return 1;
    ioctl_write_file(file_desc, fp);

    printf("Chardev after:\n");
    ioctl_get_msg(file_desc);
    close(file_desc);
}
