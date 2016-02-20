#!/usr/bin/python

import os

for i in range(0, 12):
  print i
  os.system('java -jar MultiplayerReversi.jar  -exec bin/MultiplayerReversi  -onewindow -go -novis -line ' + repr(i))
