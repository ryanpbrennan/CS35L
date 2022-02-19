import sys

for i in range(0, 1000000):
	char = chr((i%90)+33)
	sys.stdout.write(char)
