from sys import argv
from math import *

def atcharge(x):
    return {
        'O': 8.0,
        'Ti': 22.0,
    }[x]

n = 1
scale = 0.0
a = []
b = []
c = []
el = []
eln = []
cline = 0
cords = []
nat = 0

with open(argv[1]) as f:
	for line in f:
		line = ' '.join(line.split())
		if len(line) < 1:
			break
		if line[0] == "#":
			continue
		if n == 1:
			scale = float(line) * 1.889725989
			#print("%.6f" % scale)
		if n == 2:
			a = line.split(" ")
		if n == 3:
			b = line.split(" ")
		if n == 4:
			c = line.split(" ")
		if n == 5:
			el = line.split(" ")
		if n == 6: 
			eln = line.split(" ")
			for i, x in enumerate(eln):
				eln[i] = int(x)
			nat = sum(eln)
			#print nat
		if line.find("Direct") >= 0:
			#print n
			cline = n + 1
			n += 1
			continue
		if cline > 0 and n - cline <= nat:
			#print n, cline, nat
			cords.append(line.split(" "))
			for i, x in enumerate(cords[n - cline]):
				if i < 3:
					cords[n - cline][i] = float(x) #* 1.889725989 / scale
		n += 1
		

for i, val in enumerate(a):
	a[i] = float(val)

print("generated using script")
print("P   LATTICE,NONEQUIV.ATOMS%4.i    1 P1      " % nat)
print("MODE OF CALC=RELA unit=bohr")
print("%10.6f%10.6f%10.6f 90.000000 90.000000 90.000000" % (scale, scale, scale))
atindx = 0
cumul = 0
for i,at in enumerate(cords):
	print("ATOM%4i: X=%10.8f Y=%10.8f Z=%10.8f" % (-(i + 1), at[0], at[1], at[2]))
	print("          MULT= 1          ISPLIT=15")
	print("%-2s         NPT=  781  R0=.000050000 RMT=   2.00000   Z:%10.5f" % (el[atindx], atcharge(el[atindx])))
	print("LOCAL ROT MATRIX:    1.0000000 0.0000000 0.0000000")
	print("                     0.0000000 1.0000000 0.0000000")
	print("                     0.0000000 0.0000000 1.0000000")
	cumul += 1
	if cumul == eln[atindx]:
		atindx += 1
		cumul = 0  
print("   0      NUMBER OF SYMMETRY OPERATIONS")	
