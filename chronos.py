#!/usr/bin/env python

from time import sleep
from chronos import SimpleChronosSocket

def func(str):
  print str

socket = SimpleChronosSocket("/chronos", func)
sleep(1)
socket.publish_string("/1/2", 0, "what the heck", 100)
sleep(1)
socket.callback("self callback in the same thread")
socket2 = SimpleChronosSocket("/chronos", func)

sleep(1)
print "done"

