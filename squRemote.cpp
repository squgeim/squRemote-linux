/*
 * squRemote.cpp
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

#include "server.hpp"
#include "sim.hpp"

class MyServer: public server {
    public:
    MyServer(int port):server(port){}

    void on_receive(const char* buf) {
        keybd k=buf;
        k.exe();
    }
};

int main(int argc, char **argv) {
    MyServer s(9999);
    s.serve();
    return 0;
}
