#!/usr/bin/env python

from sys import argv
from math import *
import argparse
import re
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
def network(atoms, a1, a2):
	"""Return fraction of possible connection with given atoms"""
	a = re.findall('[A-Z][a-z]*', atoms)
	n = (len(a)**2 - len(a))/2.0
	n1 = a.count(a1)
	n2 = a.count(a2)
	if n1 == 0:
		return 0
	elif n2 == 0:
		return 0
	elif a1 == a2:
		if len(a) == 1:
			return 1.0
		return (n1**2 - n1)/2/n
	else:
		return a.count(a1)*a.count(a2)/n

parser = argparse.ArgumentParser(description='Solve XPS data into subpeaks')
group = parser.add_mutually_exclusive_group(required=True)
group.add_argument('-aim', help='path to the outputaim Wien2k file',  dest='aim_file')
group.add_argument('-geom', help='path to the xyz struct file', action='store_const', const=1)
parser.add_argument("xyz_file")
parser.add_argument("XPS_file")
args = parser.parse_args()

lines = [line for line in open(args.xyz_file)]

natoms = int(lines[0])
print ("We have %i atoms" % natoms)
 
rawdata = [ lines[x].split() for x in range (2, natoms + 2) ]
data = [[rawdata[x][0], float(rawdata[x][1]), float(rawdata[x][2]), float(rawdata[x][3])] for x in range(0, natoms)]
atomtypes = set(data[x][0] for x in range(0, natoms))
nuatoms = len(atomtypes)

print data[0]
print atomtypes, nuatoms


neighbors = []
for i,atom1 in enumerate(data):
	neighbors.append([])
	neighbors[i].append(atom1[0])
	neighbors[i].append([])

# calculate nearest neighbors manually
if args.geom:
	csize = [float(line) for line in open("dims")]

	for i,atom1 in enumerate(data):
		for atom2 in data:
			if atom1 == atom2:
				continue
			if dist(atom1, atom2, csize) < fmaxg(atom1[0],atom2[0]):
				neighbors[i][1].append(atom2[0])
		sorted(neighbors[i][1])
		neighbors[i].append(len(neighbors[i][1]))
		neighbors[i][1] = "".join(neighbors[i][1])

# get nearest neighbors from aim output file 
if args.aim_file:
	for line in open(args.aim_file):
		p = line.split()
		if len(p) == 14 and p[0] == ':PC' and p[7] == '-1':
			at1 = -int(p[10])-1
			at2 = -int(p[12])-1
			#print at1,at2
			neighbors[at1][1].append(at2)
			neighbors[at2][1].append(at1)
	for n in neighbors:
		print n[1]
		a = set(n[1])
		n[1] = [] 
		for at in a:
			n[1].append(data[at][0])
	
#print neighbors

# find all unique neighboir configuration for each atom	
cnumtypes = []
for i,atomtype in enumerate(atomtypes):
	cnumtypes.append([atomtype])
	cnumtypes[i].append([])
	for atom in neighbors:
		if atom[0] == atomtype:
			cnumtypes[i][1].append(atom[1])	
	cnumtypes[i][1] = set(cnumtypes[i][1])
	cnumtypes[i].append([])
	cnumtypes[i].append([])
#print cnumtypes

# open XPS data
lines = [float(line) for line in open(args.XPS_file)]			 
	
sigma = 0.4
s = sqrt(2 * pi)
c = 1.0 / sigma / s / natoms

min = min(lines) - 6 * sigma
max = max(lines) + 6 * sigma
step = 0.01

out = []
out.append(["energy"])
for a in cnumtypes:
	out[0].append(a)
out[0].append("total")
#print out[0]

# iterate over list of unique atoms
for nat,type in enumerate(cnumtypes):
	#open file for writing
	fname = type[0] + "-XPS-peaks.txt"
	f = open(fname, "w")
	f2 = open(type[0] + "-stats.txt", "w")
	f3 = open(type[0] + "-XPS-peaks-imp.txt", "w")
	
	#make header
	out = []
	out.append(["energy"])
	for a in type[1]:
		out[0].append(a)
	out[0].append("total")
	f.write(" ".join(out[0]) + "\n")

	#make header for combined peaks
	out2 = []
	out2.append("\n")
	f3.write("energy Ti-O-Ti Ti-O-Si Si-O-Si total\n")
	sumTiTi = 0.0
	sumTiSi = 0.0
	sumSiSi = 0.0

	# calculate one energy step at a time
	a = 1
	for x in [min + p * step for p in range(int(ceil((max - min) / step)))]:
		#print x,
		out.append([x])
		out2.append([x])
		out2[a].append(0.0)
		out2[a].append(0.0)
		out2[a].append(0.0)
		
		xsum = 0.0
		# go over all atomic environments
		for j,neighbor_type in enumerate(type[1]):
			out[a].append(0.0)
			# go over all calculated XPS positions
			# FIXME: use the original XPS output and check also atom types	
			for i,l in enumerate(lines):
				if data[i][0] == type[0] and cmp(neighbor_type,neighbors[i][1]) == 0:
					tmp = c * e ** ( -0.5 * ((x - l) / sigma) * ((x - l) / sigma))
					out[a][j + 1] += tmp
					if network(neighbor_type,'Ti','Ti')+ network(neighbor_type,'Ti','Si') + network(neighbor_type,'Si','Si') > 1.0:
						print neighbor_type, network(neighbor_type,'Ti','Ti'), network(neighbor_type,'Ti','Si'), 
						sys.exit()
					out2[a][1] += tmp * network(neighbor_type,'Ti','Ti')
					sumTiTi += step * tmp * network(neighbor_type,'Ti','Ti')
					out2[a][2] += tmp * network(neighbor_type,'Ti','Si')
					sumTiSi += step * tmp * network(neighbor_type,'Ti','Si')
					out2[a][3] += tmp * network(neighbor_type,'Si','Si')
					sumSiSi += step * tmp * network(neighbor_type,'Si','Si')
			#print out[a][j + 1],
			xsum += out[a][j + 1] 
		#print total,
		out[a].append(xsum)
		out2[a].append(xsum)
		f.write(" ".join(format(x, ".4f") for x in out[a]) + "\n")
		f3.write(" ".join(format(x, ".4f") for x in out2[a]) + "\n")
		
		a += 1

	TiOTi = []
	SiOSi = []
	SiOTi = []
	f2.write("------- All types -------\n\n")
	for j,neighbor_type in enumerate(type[1]):
		type[2].append([])
		for i,l in enumerate(lines):
			if data[i][0] == type[0] and cmp(neighbor_type,neighbors[i][1]) == 0:
				type[2][j].append(float(l))
				if neighbor_type.find("Si") == -1:
					TiOTi.append(float(l))
				elif neighbor_type.find("Ti") == -1:
					SiOSi.append(float(l))
				else:
					SiOTi.append(float(l))
   
		type[3].append([len(type[2][j]), mean(type[2][j]), pstdev(type[2][j])])
		f2.write(neighbor_type + "\n")
		f2.write("number of atoms in this configuration: " + str(type[3][j][0]) + "\n")
		f2.write("average position: " + str(type[3][j][1]) + "\n")
		f2.write("position stdev: " + str(type[3][j][2]) + "\n")
		f2.write("list of positions: " + "\n")
		f2.write("\n".join(str(x) for x in type[2][j]) + "\n\n")

	f2.write("\n------- Simplified types -------\n\n")
	f2.write("only Ti neighbors (Ti-O-Ti)\n")
	f2.write("number of atoms in this configuration: " + str(len(TiOTi)) + "\n")
	f2.write("average position: " + str(mean(TiOTi)) + "\n")
	f2.write("position stdev: " + str(pstdev(TiOTi)) + "\n")
	f2.write("list of positions: " + "\n")
	f2.write("\n".join(str(x) for x in TiOTi) + "\n\n")

	f2.write("only Si neighbors (Si-O-Si)\n")
	f2.write("number of atoms in this configuration: " + str(len(SiOSi)) + "\n")
	f2.write("average position: " + str(mean(SiOSi)) + "\n")
	f2.write("position stdev: " + str(pstdev(SiOSi)) + "\n")
	f2.write("list of positions: " + "\n")
	f2.write("\n".join(str(x) for x in SiOSi) + "\n\n")

	f2.write("Mixed neighbors (Si-O-Ti)\n")
	f2.write("number of atoms in this configuration: " + str(len(SiOTi)) + "\n")
	f2.write("average position: " + str(mean(SiOTi)) + "\n")
	f2.write("position stdev: " + str(pstdev(SiOTi)) + "\n")
	f2.write("list of positions: " + "\n")
	f2.write("\n".join(str(x) for x in SiOTi) + "\n\n")

	f2.write("\n------- Improved distribution into types -------\n\n")
	f2.write("only Ti neighbors (Ti-O-Ti)\n")
	f2.write("number of atoms in this configuration: " + str(sumTiTi * 96) + "\n")
	f2.write("Mixed neighbors (Ti-O-Si)\n")
	f2.write("number of atoms in this configuration: " + str(sumTiSi * 96) + "\n")
	f2.write("only Si neighbors (Si-O-Si)\n")
	f2.write("number of atoms in this configuration: " + str(sumSiSi * 96) + "\n")
	
