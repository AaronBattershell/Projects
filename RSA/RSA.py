#*******************************************
# Aaron Battershell 2/12/14
# Algorithms 001 : Dr Duan
# RSA encryption algorithm components
#*******************************************

import sys
import random

#*******************************************
# RSA - contains necissary functions for
#  performing RSA encryption
#*******************************************
class RSA:

	#--------------------------------------------
        # A power function with the result being 
	#  num(^exponent). Optionally, a third integer argument,
	#  mod, can be included so that this function will
	#  return num(^exponent) (MOD mod)
        #--------------------------------------------	
	def pow(self, num, exponent, mod = -1):
		powMap = {1:num}	
		return (1 if exponent < 1 else self._pow(exponent, powMap, mod))
	
	#--------------------------------------------
        # A function not meant to be called by the user, this 
        #  function is called by rsa.pow and returns
	#  powMap[1](^exponent). Optionally, a third integer 
	#  argument, mod, can be included so that this function
	#  returns powMap[1](^exponent) (MOD mod). This function
	#  uses a map, powMap, to memoize past results as to 
	#  not recalculate them. 
        #--------------------------------------------
	def _pow(self, exponent, powMap, mod = -1):
		if (exponent in powMap):
			return powMap[exponent]
		else:
			powMap[exponent] = self._pow(exponent/2, powMap, mod) * self._pow(exponent/2 + (1 if exponent%2==1 else 0), powMap, mod) 
			if (mod != -1): powMap[exponent] %= mod
			return powMap[exponent]

	#--------------------------------------------
	# Takes an integer argument of n and returns a number 
	#  likely to be prime with n digits.
	#--------------------------------------------
	def primeGen(self, size):
		found = False		
		primeNum = random.randrange(self.pow(10,size-1), self.pow(10,size)-1)
		primeNum += (1 if  primeNum % 2 == 0 else 0)  # Ensure that your primeNumber is odd 
		
		# Test your number to see if it is prime
		while not found:
			if self.pow(2, primeNum-1, primeNum) == 1 and self.pow(3, primeNum-1, primeNum) == 1:
				found = True
			else:
				primeNum += 2
		
		# If primeNum is greater than length 'size', return a new result
		return (primeNum if len(str(primeNum)) == size else self.primeGen(size))
	
        #--------------------------------------------
        # Returns the two integer arguments (x, y) such 
	#  that gcd(a, b) = ax + by. y is not guaranteed 
	#  to be greater than 0. This function calls 
	#  rsa._extendedEuclidean to get its results.
        #--------------------------------------------   
        def gcd(self, a, b):
		result = self._extendedEuclidean(a, b)
                return (result[1], result[2]) # (x, y)

	#--------------------------------------------
        # Calculates the inverse of e such that 
        #  (e * d) = 1 (MOD (p-1)*(q-1)). It is calculated
	#  by calling rsa._extendedEuclidean.
        #--------------------------------------------	
	def modInverse(self, e, p, q):
		phiN = (p-1)*(q-1)
		result = self._extendedEuclidean(e, phiN)
		return result[1] + (phiN if result[1] <= 0 else 0)	

	#--------------------------------------------
        # This function is only called by rsa.modInverse
	#  and rsa.gcd. It calculates the inverse of e such 
	#  that (e * d) = 1 (MOD (p-1)*(q-1)). 
	#  Note: Implementation of the following function
	#  was provided by Dr. Duan. It is not my own.
        #--------------------------------------------
	def _extendedEuclidean(self, a, b):
		if (b == 0): 
			return (a,1,0)
	
		(dd,xx,yy) = self._extendedEuclidean(b, a%b)
		(d, x, y ) = (dd, yy, xx - (a/b)*yy)
		return (d,x,y)

	#--------------------------------------------
        # Encrypt a string message m such that the result
        #  is ('m converted into an int')(^e) % n.
        #--------------------------------------------
	def encrypt(self, e, n, m):
		sum = 0
		for i in range(0, len(m)):
			sum += (ord(m[i]) * self.pow(128, len(m)-i-1))  		

		return self.pow(sum, e, n)

	#--------------------------------------------
        # Decrypt an integer message m such that the result 
        #  is a string.
        #--------------------------------------------
	def decrypt(self, d, n, m):
		m = self.pow(m, d, n);		

		message = ''
		while m != 0:
			message += chr(m % 128) 
			m /= 128

		#Return the string reversed
		return message[::-1]


#*******************************************
# main - Where command line arguments
#  are processed
#*******************************************
def main():
	argList = sys.argv
	rsa = RSA()

	if (len(argList) == 1 or len(argList) > 5):
		print "Wrong input format!"
	if (len(argList) == 2):
		log10pp1 = int(argList[1])
		print "Size of the prime:", log10pp1
		print "Prime:", rsa.primeGen(log10pp1)
	if (len(argList) == 3):
		a = int(argList[1])
		b = int(argList[2])
		print "a = " + str(a) + ", b = " + str(b)
		print "(x, y) =",rsa.gcd(a, b)
	if (len(argList) == 4):
		e = int(argList[1])
		p = int(argList[2])
		q = int(argList[3])
		print "e = " + str(e) + ", p = " + str(p) + ", q = " + str(q)
		print "Multiplicative inverse of e:", rsa.modInverse(e, p, q)
	if (len(argList) == 5):
		if (argList[1][0] == 'e'):
			e = int(argList[2])
			n = int(argList[3])
			m = argList[4]
			print "e = " + str(e) + ", n = " + str(n) + ", message = " + m
			print "Encription:", rsa.encrypt(e, n, m)
		elif (argList[1][0] == 'd'):
			d = int(argList[2])
			n = int(argList[3])
			m = int(argList[4])
			print "d = " + str(d) + ", n = " + str(n) + ", message = " + str(m)
			print "Decription:", rsa.decrypt(d, n, m)


#All necessary elements have been declared, call main to begin the program
main()
