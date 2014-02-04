/*
 * uinput.hpp
 * 
 * Copyright 2014 Shreya Dahal <squgeim@outlook.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include <cstdio>
#include <fcntl.h>
#include <errno.h>
#ifndef _INPUT_H
    #include <linux/input.h>
#endif
#ifndef _UINPUT_H_
    #include <linux/uinput.h>
#endif

class uinput {
    int fd;
    struct uinput_user_dev uidev;
    struct input_event ev;
    
    public:
    uinput(int*,int);
    ~uinput();
    void wrt(int vcode, int val);
    void syn();
};

uinput::uinput(int* keys, int llp) {
    char *files[2] = {(char*)"/dev/uinput",(char*)"/dev/input/uinput"};
    int i=0;
    do {
	fd = open(files[i], O_WRONLY | O_NONBLOCK);
	i++;
    }while(fd<0&&i<2);
    
    if(fd < 0)
        error("error: open");
    if(ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)
        error("error: ioctl");
    for(int i=0; i<llp; i++) {
	if(ioctl(fd, UI_SET_KEYBIT, keys[i]) < 0)
            error("error: ioctl");
    }
    if(ioctl(fd, UI_SET_EVBIT, EV_SYN) < 0)
        error("error: ioctl");
	
    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "squremote");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor  = 0x1;
    uidev.id.product = 0x1;
    uidev.id.version = 1;

    if(write(fd, &uidev, sizeof(uidev)) < 0)
        error("error: write");

    if(ioctl(fd, UI_DEV_CREATE) < 0)
        error("error: ioctl");	
}

uinput::~uinput() {
    if(ioctl(fd, UI_DEV_DESTROY) < 0)
	error("error: ioctl");
    close(fd);
}

void uinput::wrt(int vcode, int val) {
    memset(&ev, 0, sizeof(struct input_event));
    ev.type = EV_KEY;
    ev.code = vcode;
    ev.value = val;
    if(write(fd, &ev, sizeof(struct input_event)) < 0)
	error("error: write");
    usleep(10000);
}

void uinput::syn() {
    memset(&ev, 0, sizeof(struct input_event));
    ev.type = EV_SYN;
    ev.code = 0;
    ev.value = 0;
    if(write(fd, &ev, sizeof(struct input_event)) < 0)
	error("error: write");
    usleep(10000);
}
