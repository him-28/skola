#!/usr/bin/env python

import os
import fnmatch

cwd = os.getcwd()
case = os.path.basename(cwd) 

def parse_ene(f, d):
   """parses energy files"""
   maxval = d[0]
   kmaxval = d[1]
   kmaxvalpos = d[2]
   mincond = d[3]
   kmincond = d[4]
   kmincondpos = d[5]
   s = 0

   for line in f:
      if len(line) == 88:
         k = int(line[59:67])
         kx = float(line[:19])
         ky = float(line[20:38])
         kz = float(line[39:57])
         s = 1
         continue
      if s == 1:
         l = line.split()
         bindex = int(l[0])
         if bindex == nvalbands:
            ene = float(l[1])
            if ene > maxval:
               maxval = ene
               kmaxval = k
               kmaxvalpos = [kx, ky, kz]
         if bindex == nvalbands + 1:
            ene = float(l[1])
            if ene < mincond:
               mincond = ene
               kmincond = k
               kmincondpos = [kx, ky, kz]

   return [maxval, kmaxval, kmaxvalpos, mincond, kmincond, kmincondpos]

p = 1
suf = ""

for file in os.listdir('.'):
   if fnmatch.fnmatch(file, case + '.in2c'):
      suf = "c"

f = open(case + ".in2" + suf, "r")
nvalbands = 0

for i,line in enumerate(f):
   if i == 1:
      ne = float(line.split()[1])
      nvalbands = ne / 2
      break

maxval = -1000.0
kmaxval = 0
kmaxvalpos = 0
mincond = 1000.0
kmincond = 0
kmincondpos = 0

d = [maxval, kmaxval, kmaxvalpos, mincond, kmincond, kmincondpos]

if p == 0:
   f = open(case + ".energy", "r")
   d = parse_ene(f, d)
else:
   for file in os.listdir('.'):
      if fnmatch.fnmatch(file, case + '.energy_*'):
         f = open(file, "r")
         d = parse_ene(f, d)

print "GAP: " + str((d[3] - d[0]) * 13.605698066)
if d[1] == d[4]:
   print "Direct gap"
else:
   print "Indirect gap"

print "Top od the valence band at kpoint " + str(d[1]), d[2]
print "Bottom of the conduction band at kpoint " + str(d[4]), d[5] 
