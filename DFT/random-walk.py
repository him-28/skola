#!/usr/bin/env python

from sys import argv
from math import *
import argparse
import random
import sys

def fmaxg(a1, a2):
	"doscstring"
	if a1 == a2 == "O":
		return 2.2
	else:
		return 2.4

def dist(atom1, atom2, csize):
	"function_docstring"
	sum = 0.0
	for x in range(3):
		dif = abs(atom2[x+1] - atom1[x+1])
		if dif > csize[x]/2.0:
			sum += (csize[x] - dif) * (csize[x] - dif)
		else:
			sum += dif * dif 
		#print atom2[x+1], atom1[x+1], dif, csize[x], sum
	#print sqrt(sum)
	return sqrt(sum)

def mean(data):
        """Return the sample arithmetic mean of data."""
        n = len(data)
        if n < 1:
                return 0.0
        return float(sum(data))/float(n) # in Python 2 use sum(data)/float(n)

def _ss(data):
        """Return sum of square deviations of sequence data."""
        c = mean(data)
        ss = sum((x-c)**2 for x in data)
        return ss

def pstdev(data):
        """Calculates the population standard deviation."""
        n = len(data)
        if n < 2:
                return 0.0
        ss = _ss(data)
        pvar = ss/(n-1) # the population variance
        return pvar**0.5

def get_next_atom(start_at_n, cur_at, last_at, length, atoms, neighbors):
	"""finds next random neighbor and checks if it is similar, skips if oxigen"""
	next = random.randint(0, neighbors[cur_at][2] - 1)
	while neighbors[cur_at][1][next] == last_at and neighbors[cur_at][2] > 1:
		next = random.randint(0, neighbors[cur_at][2] - 1)
	next = neighbors[cur_at][1][next]
	# check maximum recursion for pure TiO2 and SiO2
	# also check that we don't finish at oxigen
	if length > 100 and atoms[next][0] != 'O':
		#print "maximum recursion reached"
		return (100, next, cur_at)
	visits[cur_at] += 1
	global total_visits
	total_visits += 1
	routes[cur_at][next] += 1
	routes[next][cur_at] += 1
	#print "next atom is " + str(next) + " " + str(atoms[next][0])
	# if the next atom is oxygen, just go to it
	if atoms[next][0] == 'O':
		return get_next_atom(start_at_n, next, cur_at, length, data, neighbors)
	elif atoms[next][0] != start_at_n:
		return (length, next, cur_at)
	elif atoms[next][0] == start_at_n:
		return get_next_atom(start_at_n, next, cur_at, length + 1, data, neighbors)
	else:
		print "samothing went wrong"
		sys.exit()

parser = argparse.ArgumentParser(description='Goes over given cells and searches for linear chain length')
parser.add_argument("xyz_file")
args = parser.parse_args()

lines = [line for line in open(args.xyz_file)]
#maxg = float(argv[2])

natoms = int(lines[0])
print ("We have %i atoms" % natoms)
 
rawdata = [ lines[x].split() for x in range (2, natoms + 2) ]
data = [[rawdata[x][0], float(rawdata[x][1]), float(rawdata[x][2]), float(rawdata[x][3])] for x in range(0, natoms)]
atomtypes = set(data[x][0] for x in range(0, natoms))
nuatoms = len(atomtypes)

print atomtypes, nuatoms

neighbors = []
for i,atom1 in enumerate(data):
	neighbors.append([])
	neighbors[i].append(atom1[0])
	neighbors[i].append([])

# calculate nearest neighbors manually
csize = [float(line) for line in open("dims")]

for i,atom1 in enumerate(data):
	for j,atom2 in (enumerate(data)):
		if atom1 == atom2:
			continue
		if dist(atom1, atom2, csize) < fmaxg(atom1[0],atom2[0]):
			neighbors[i][1].append(j)
	sorted(neighbors[i][1])
	neighbors[i].append(len(neighbors[i][1]))

#print neighbors

walksSi = []
walksTi = []
N = 0
NSi = 0
NTi = 0
start_at = 64
last_at = -1

global visits
visits = [0] * 96
global routes
routes = [[0 for x in range(96)] for x in range(96)]
global total_visits
total_visits = 0

random.seed(6)
while N < 10000000:
	if total_visits > 5000000:
		break
	if data[start_at][0] != 'Si' and data[start_at][0] != 'Ti':
		print "fishy stuff going on"
	start_at_n = data[start_at][0]
	#print "starting at " + str(start_at) + str(start_at_n)
	t = get_next_atom(start_at_n, start_at, last_at, 1, data, neighbors)
	length = t[0]
	#print length
	N += 1
	if start_at_n == 'Si':
		NSi += 1
		walksSi.append(length)
	if start_at_n == 'Ti':
		NTi += 1
		walksTi.append(length)
	start_at = t[1]
	last_at = t[2]

print "Total number of walks: " + str(N)
print "Average walk: " + str(mean(walksSi + walksTi))
print "Total number of Ti walks: " + str(NTi)
print "Average walk: " + str(mean(walksTi))
print "Total number of Si walks: " + str(NSi)
print "Average walk: " + str(mean(walksSi))


print "\nTotal number of visits = " + str(sum(visits))
coord_numbers = set(x[2] for x in neighbors)
for coord in coord_numbers:
	cset = []
	atom_set = []
	Siset = []
	Tiset = []
	Oset = []
	for i,atom in enumerate(data):
		if neighbors[i][2] == coord:
			cset.append(visits[i])
			atom_set.append(data[i][0])
			if atom[0] == 'Si':
				Siset.append(visits[i])
			if atom[0] == 'Ti':
				Tiset.append(visits[i])
			if atom[0] == 'O':
				Oset.append(visits[i])
	print "Atoms in %i-coordination: %i  Ti:%i Si:%i O:%i" % (coord, len(cset), atom_set.count('Ti'), atom_set.count('Si'), atom_set.count('O'))
	print "Average number of visits for all %i-coordinated: %.0f+-%.0f" % (coord ,mean(cset) ,pstdev(cset))
	print "Average number of visits for Ti %i-coordinated: %.0f+-%.0f" % (coord ,mean(Tiset) ,pstdev(Tiset))
	print "Average number of visits for Si %i-coordinated: %.0f+-%.0f" % (coord ,mean(Siset) ,pstdev(Siset))
	print "Average number of visits for O %i-coordinated: %.0f+-%.0f" % (coord ,mean(Oset) ,pstdev(Oset))
