The following is a high-level overview of Aaron Battershell's RSA encryption implementation.

General:
	• This program was written using python version 2.7.3. It expects input via the command
	line, and if none is provided the program will simply output "Wrong Input Format!" An 
	example of how this program is designed to run, is if in command line, the following 
	could be entered to produce correct output: "python RSA.py 1 2 3". The format should 
	follow: "python RSA.py input_1 [...] input_n". This program is not designed to loop, and
	therefore, after input, the program will produce output, and then terminate.

	•  Please note that when encrypting and decrypting, if the n chosen is too small
	relative to the message being used, correct output will not be produced. When a message
	is too large, the leftmost characters in the string will be lost, or giberish will be
	output during decryption.

	•  Function calls are determined based on the number of command line inputs. The following
	   is a guide (input count does not include the name of the file):
		1 input : (int) generate a prime of size a
		2 inputs: (int, int) returns two ints (x,y) such that gcd(a,b) = ax + by with y not
		  necessarily being larger than 0
		3 inputs: (int e, int p, int q) output the inverse of e 
		5 inputs: (char e, int e, int n, string m) output encrypted m
			  (char d, int d, int n, int m) output decrypted m



Low level class and function descriptions can be found in RSA.py, where they will have more contex to the reader.

Class RSA Functions:

	pow(int a, int b, int c = -1)
	_pow(map<int,int> a,b,c = -1)
	primeGen(int a)
	gcd(int a, int b)
	modInverse(int a, int b, int c)
	_etendedEuclidean(int a, int b)
	encrypt(int a, int b, string c)
	decrypt(int a, int b, int c)


File Functions:
	
	main

