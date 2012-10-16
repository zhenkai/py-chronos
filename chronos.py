#!/usr/bin/env python

import chronos

def func(str):
  print str

socket = chronos.SimpleChronosSocket("/1", func)

sleep(10)
print "done"

