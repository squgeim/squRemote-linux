/*
 * sim.hpp
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

#include "uinput.hpp"
#include "vcodes.hpp"

class keybd: private vcodes {
    int* keys;
    int llp;
    void pos(const char*,int&,int&,int&);
    bool ok;
    
    public:
	keybd(const char* buf);
	~keybd();
	void exe();
	bool ismod();
	void err(const char*);
};

void keybd::err(const char* e) {
    std::cout<<e<<std::endl;
    ok=false;
    //exit(1);
}

void keybd::pos(const char* buf,int& ps,int& tot,int& len) {
    tot=0,ps=-1,len=0;
    for(int i=0;;i++) {
	if(buf[i]=='+') {ps=i;tot++;}
	if(buf[i]=='\0') {len=i;break;}
    }
}

keybd::keybd(const char* buf) {
    char **k;
    int ps,len,tot;
    ok=true;
    
    pos(buf,ps,tot,len);
    if(tot>=2) error("Invalid input 1");
    
    if(ps!=-1) {
	llp=2;
	k= new char*[2];
	k[0]=new char[ps+1+10];
	k[1]=new char[len-ps+10];
	int j=0,i;
	for(i=0;i<ps;i++,j++) {
	    k[0][i]=buf[j];
	}
	k[0][i]='\0';
	for(i=0,j++;j<=len;i++,j++) {
	    k[1][i]=buf[j];
	}
	keys = new int[2];
	keys[0] = vcode(k[0]);
	if(keys[0]==-1) err("Invalid input 2");
	keys[1] = vcode(k[1]);
	if(keys[1]==-1) err("Invalid input 3");
	
	delete[] k[0];
	delete[] k[1];
	delete k;
    }
    else {
	llp=1;
	keys = new int[1];
	keys[0] = vcode(buf);
	if(keys[0]==-1) err("Invalid input ");
    }
}

keybd::~keybd() {
    delete[] keys;
}

void keybd::exe() {
    if(ok) {
	uinput ui(keys,llp);
	for(int i=0;i<llp;i++) {
	    //std::cout<<keys[i]<<std::endl;
	    ui.wrt(keys[i],1);
	}
	for(int i=llp-1;i>=0;i--) {
	    //std::cout<<keys[i]<<std::endl;
	    ui.wrt(keys[i],0);
	}
	ui.syn();
    }
}
