#!/usr/bin/python

import sys
import socket
import struct
import time

local_port = 5006


family = socket.AF_INET
connect_tuple = ( 'localhost', local_port )

s = socket.socket( family, socket.SOCK_DGRAM )
s.connect( connect_tuple )

if len(sys.argv)>1:

        note1 = int(sys.argv[1]);
        
        # Note ON
        bytes = struct.pack( "BBBB", 0xaa, note1, 0x30, 0x40 )
        s.send( bytes )

        time.sleep(1);

        # Note OFF
        bytes = struct.pack( "BBBB", 0xaa, 0x80, 0x30, 0x40 )
        s.send( bytes )

s.close()

print "Sent";

