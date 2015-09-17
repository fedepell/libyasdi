#include "gpio_handler.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <sys/mman.h>

#define GPIO_SYS  "/sys/class/gpio/"
#define GPIO_SYS_PATH  "/sys/class/gpio/gpio"
#define GPIO_SYS_PATH_EXPORT  "/sys/class/gpio/export"
#define GPIO_SYS_PATH_UNEXPORT  "/sys/class/gpio/unexport"

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
void setValue(bool _Value, char* gpio_number)
{
    getValue(gpio_number);
    enableExport(true, gpio_number);
    setDirection(true, gpio_number);

    int  fd, len = strlen("1");
    if((fd = open(valuePath(gpio_number), O_WRONLY)) < 0) return;
    write(fd, (_Value ? "1" : "0"), len);
    close(fd);
}


bool getValue(char* gpio_number)
{
    FILE *file;
    file = fopen(valuePath(gpio_number), "r");
    if (file) {
        char buff[10];
        fgets(buff, 10, file);
        fclose(file);
        return ( ((strcmp(buff, "0") == 0)) ? false : true );
    }
    return false;
}

void setDirection(bool _dir, char* gpio_number)
{
    char* dir;
    dir = _dir ? "out" : "in";
    int  fd, len = strlen(dir);
    if((fd = open(directionPath(gpio_number), O_WRONLY)) < 0) return;
    write(fd, dir, len);
    close(fd);
}


void switchValue(char* gpio_number)
{
    setValue( !getValue(gpio_number), gpio_number);
}

char* gpioPath(char* gpio_number)
{
    return concat(GPIO_SYS_PATH, gpio_number);
}

char* directionPath(char* gpio_number)
{
    char filename[50];
    sprintf(filename, "%s/direction", gpioPath(gpio_number));
    char *returnValue = malloc(sizeof(char) * 50);
    strcpy(returnValue, filename);
    return returnValue;
}

char* valuePath(char* gpio_number)
{
    char filename[50];
    sprintf(filename, "%s/value", gpioPath(gpio_number));
    char *returnValue = malloc(sizeof(char) * 50);
    strcpy(returnValue, filename);
    return returnValue;
}

bool direction(char* gpio_number)
{
    enableExport(true, gpio_number);

    if (0 != access(gpioPath(gpio_number), F_OK)) {
        if (ENOENT == errno) {
            // does not exist
            return false;
        }
        if (ENOTDIR == errno) {
            return false;
        }
    }
    else
    {
        char buff[10];
        FILE *f = fopen(directionPath(gpio_number), "r");
        fgets(buff, 10, f);
        fclose(f);
        return (strcmp(buff, "out") == 0);
    }

    return false;
}

void enableExport(bool _enable, char* gpio_number)
{
    if (_enable)
    {
        if ( !exportEnabled(gpio_number) )
        {
            int  fd, len = strlen(gpio_number);
            if((fd = open(exportPath(), O_WRONLY)) < 0) return;
            write(fd, gpio_number, len);
            close(fd);
        }
    }
    else // disable
    {
        if ( exportEnabled(gpio_number) )
        {

            int  fd, len = strlen(gpio_number);
            if((fd = open(unexportPath(), O_WRONLY)) < 0) return;
            write(fd, gpio_number, len);
            close(fd);

        }
    }
}


bool exportEnabled(char* gpio_number)
{
    // an existing gpioPath means that gpio is ready for export
    if (0 != access(gpioPath(gpio_number), F_OK)) {
        if (ENOENT == errno) {
            // does not exist
            return false;
        }
        if (ENOTDIR == errno) {
            return false;
        }
    }
    return true;
}



char* exportPath()
{
    return GPIO_SYS_PATH_EXPORT;
}

char* unexportPath()
{
    return GPIO_SYS_PATH_UNEXPORT;
}
