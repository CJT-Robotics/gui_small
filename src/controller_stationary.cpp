#include "controller_stationary.h"
#include "synchronization.h"
#include "DataRepository.h"

#include <string>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>


/**
 * Reads a joystick event from the joystick device.
 *
 * Returns 0 on success. Otherwise -1 is returned.
 */
int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    /* Error, could not read full event. */
    return -1;
}

/**
 * Returns the number of axes on the controller or 0 if an error occurs.
 */
size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

/**
 * Returns the number of buttons on the controller or 0 if an error occurs.
 */
size_t get_button_count(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}

/**
 * Current state of an axis.
 */
struct axis_state {
    short x, y;
};

/**
 * Keeps track of the current axis state.
 *
 * NOTE: This function assumes that axes are numbered starting from 0, and that
 * the X axis is an even number, and the Y axis is an odd number. However, this
 * is usually a safe assumption.
 *
 * Returns the axis that the event indicated.
 */
size_t get_axis_state(struct js_event *event, struct axis_state axes[10])
{
    size_t axis = event->number / 2;

    if (axis < 10)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}

using namespace std;

void openConnection();

DataRepository* i;

void initControlerStationary(){
    i = &DataRepository::getInstance();
    while(!(i->getExitStatus())){
        openConnection();
    }
    
}

void openConnection(){
    const char *device;
    int js;
    struct js_event event;
    struct axis_state axes[10] = {0};
    size_t axis;

    printLine("VIETNAM");
    device = "/dev/input/js1";
    
    js = open(device, O_RDONLY);
    

    if (js == -1)
        perror("Could not open joystick");

    /* This loop will exit if the controller is unplugged. */
    
    while(!(i->getExitStatus()) && read_event(js, &event) == 0){
        
    switch (event.type)
        {
            case JS_EVENT_BUTTON:
                printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
                break;
            case JS_EVENT_AXIS:
                if(event.number % 2 == 0){
                    printf("%d: %d\n",event.number, event.value);
                }else{
                    printf("%d: %d\n", event.number, event.value);
                }
                break;
            default:
                /* Ignore init events. */
                break;
        }

        //0 right; 1 top
        
        fflush(stdout);
    }

    close(js);
    
}
