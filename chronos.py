#!/usr/bin/env python

from time import sleep
from chronos import SimpleChronosSocket

def func(str):
  print "Got data: " +  str

if __name__ == '__main__':
  socket = SimpleChronosSocket("/chronos", func)
  sleep(1)
  socket.publish_string("/1/2", 0, "Hello from socket.", 100)
  sleep(1)
  socket2 = SimpleChronosSocket("/chronos", func)

  sleep(1)
  print "done"

