/*
 * vcodes.hpp
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

#ifndef _INPUT_H
    #include <linux/input.h>
#endif
#define TotalKeys 55

class vcodes {
    static const char *key_n[TotalKeys];
    static const int key_v[TotalKeys];

    public:
    static int vcode(const char *k);
};
    
const char *vcodes::key_n[TotalKeys] = {"play","stop","prev","next","sleft","srht","vup","vdwn","ejct",
	    "spc","up","down","left","right","\\","/","a","b","c","d","e","f","g",
	    "h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",
	    "0","1","2","3","4","5","6","7","8","9","shift","ctrl","alt"};
    
const int vcodes::key_v[TotalKeys] = {KEY_PLAYPAUSE,KEY_STOPCD,KEY_PREVIOUSSONG,KEY_NEXTSONG,KEY_REWIND,KEY_FASTFORWARD,
	    KEY_VOLUMEUP,KEY_VOLUMEDOWN,KEY_EJECTCD,KEY_SPACE,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,
	    KEY_BACKSLASH,KEY_SLASH,KEY_A,KEY_B,KEY_C,KEY_D,KEY_E,KEY_F,KEY_G,KEY_H,KEY_I,KEY_J,
	    KEY_K,KEY_L,KEY_M,KEY_N,KEY_O,KEY_P,KEY_Q,KEY_R,KEY_S,KEY_T,KEY_U,KEY_V,KEY_W,KEY_X,
	    KEY_Y,KEY_Z,KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_LEFTSHIFT,
	    KEY_LEFTCTRL,KEY_LEFTALT};

int vcodes::vcode(const char *k) {
    for(int index=0;index<TotalKeys;index++) {
	if(strcmp(key_n[index],k)==0) return key_v[index];
    }
    return -1;
}
