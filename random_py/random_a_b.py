# implement RANDOM(a, b) that only makes calls to RANDOM(0, 1)
# RANDOM(a, b) returns an integer in [a, b] randomly
# a and b are positive integer

import random

def random_0_1():
	return random.randint(0, 1)

def getBit(a, b):
	bit = 0
	value = 1
	diff = b - a
	while value <= diff:
		value = value << 1
		bit += 1

	return bit

def random_a_b(a, b):
	diff = b - a
	result = 0;
	bit = getBit(a, b);
	while 1:
		for i in range(0, bit):
			value = random_0_1() << i
			result = result | value
		if result > diff:
			result = 0
		else:
			break

	return a + result

# a simple test, didn't check value of a and b
a = int(input("a: "))
b = int(input("b: "))
while(a>0):
	print random_a_b(a, b)
	a = int(input("a: "))
	b = int(input("b: "))


