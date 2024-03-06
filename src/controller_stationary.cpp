#include "controller_stationary.h"
#include "synchronization.h"
#include "DataRepository.h"

#include <string>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>

using namespace std;


struct axis_state {
    short x, y;
    axis_state():x(0),y(0){}
};

void openConnection();

DataRepository* i;

int read_event(int fd, struct js_event *event)
{

    if (read(fd, event, sizeof(*event)) == sizeof(*event))
        return 0;

    return -1;
}



size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}




size_t get_button_count(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}


void initControlerStationary(){
    i = &DataRepository::getInstance();
    while(!(i->getExitStatus())){
        openConnection();
    }
    
}

void openConnection(){
    struct js_event event;
    struct axis_state axes[6];

    
    int js = open("/dev/input/js0", O_RDONLY);
    printf("js0");

    if (js == -1 || get_axis_count(js) != 6 || get_button_count(js) != 12){
        perror("Could not open joystick ODER DU HAST DEN FALSCHEN JOYSTICK GENOMMEN!!!!!! \n[der silberne gro0e mit Knüppel]");
    }

    
    while(!(i->getExitStatus()) && read_event(js, &event) == 0){
        
        if(event.type == JS_EVENT_BUTTON){
            printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
        }
        if(event.type == JS_EVENT_AXIS){
            printf("%d: %d\n",event.number, event.value);
        }

        //0 right; 1 top
        
        fflush(stdout);
    }

    close(js);
    
}
