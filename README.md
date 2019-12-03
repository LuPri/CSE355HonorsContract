# CSE355HonorsContract

# Overview

This repository contains a C++ program that acts a simulator for a simple Turing Machine following the definition of a Turing Machine given by Michael Sipser in textbook Introduction to the Theory of Computation. This program will asks the user to provide the name of a file that contains the description of a Turing Machine. The program will then allow the user to give input strings. Then, the program will print out the calculation trace of the Turing Machine at each step until it reaches the accept or reject state. Note that you can cause an infinite loop if you give the description of a recognizable language.   

# Input File Format:

The input files for the Turing machine simulator must be given in the following format in order for the program to read in the Turing machine correctly.

Line 1: Number that represents how many states the Turing Machine has including the accept state. Do not include the reject state.

Line 2: A list of all the states of the Turing Machine separated by a single space. The number of states should match the number given in line 1.

Line 3: Number that represents how many symbols the alphabet of the Turing Machine has.

Line 4: A list of alphabet symbols separated by a single space. The number of symbols should match the number given in line 3.

Line 5: Number that represents the number of tape symbols that are not part of the alphabet. 

Line 6: A list of tape symbols separated by a single space. The first symbol must be the blank symbol. The program will assume that the first symbol in this line will be the symbol used to denote a blank for the Turing machine. 

Line 7: Number that represents the number of transitions in the transition function for the Turing Machine.

Lines 8 to x: The following lines will include all the transitions for the Turing Machine. Each transition must be its own line. The transitions must follow the following format: <current state> <symbol read> -> <new state> <overwrite symbol> <movement>  where each component is separated by a space and the arrow is mandatory. The <current state> and <new state> have to be replaced by a valid state given in line 2. The <symbol read> and <overwrite symbol> have to be replaced with a valid symbol for the tape alphabet. If you do not want to overwrite the <symbol read> with a new symbol, make sure to write that same symbol as the <overwrite symbol>. You cannot leave the <overwrite symbol> empty. The <movement> should be replaced with either an R to indicate that the tape moves right or L to indicate that the tape moves left. This simulator does not support a state-put transition. Do not include any transition that leads to reject state. The program will automatically assume that any missing transition leads to the reject state.

Line x +1: The next line after the last transition should the start state of the Turing Machine. The state should be part of the states provided in line 2.

Line x+2: The final line should include the accept state of the Turing Machine.

# Demo:

To run the simulator with the given demos, download the turingmachinesimulator.cc file and the 3 text files containing the demo Turing Machines. Compile turingmachinesimulator.cc in your compiler of choice. Make sure that the text files are saved in the same folder in which the program is being run, or make sure you know the filepath of where the program can find the text files. When you run the program, it will ask you to provide the text file that contains the Turing Machine you want to run. You can provide turing1.txt, turing2.txt, or turing3.txt

turing1.txt:

This demo contains the description of a Turing Machine that accepts all strings with 2^n number of  0s. After the program has read in the file, it will print the description of the Turing machine and then ask you to provide a string you want to test. Type in the string you want to test, and press enter. If the given string contains characters that are not part of the Turing Machine’s alphabet, you will given “Invalid input message”. Otherwise, the program will print out the tape of the Turing Machine for all the steps of the computation ending with an accept or reject.

After calculating whether the string is accepted by the Turing Machine, the program will ask if you want to test another string. If you want to test another string, input “1” and press enter. Otherwise input “0” and press enter. After this, you will be asked if you want to test another Turing Machine. Input  “1” and press enter and provide the program with the name of the file you want to read next. Otherwise, input “0” and press enter to terminate the program. 

turing2.txt:

This demo contains the description of a Turing Machine that accepts all strings of the form w#w where w is a string made up of 0s and 1s. After the program has read in the file, it will print the description of the Turing machine and then ask you to provide a string you want to test. Type in the string you want to test, and press enter. If the given string contains characters that are not part of the Turing Machine’s alphabet, you will given “Invalid input message”. Otherwise, the program will print out the tape of the Turing Machine for all the steps of the computation ending with an accept or reject.

After calculating whether the string is accepted by the Turing Machine, the program will ask if you want to test another string. If you want to test another string, input “1” and press enter. Otherwise input “0” and press enter. After this, you will be asked if you want to test another Turing Machine. Input  “1” and press enter and provide the program with the name of the file you want to read next. Otherwise, input “0” and press enter to terminate the program. 

turing3.txt:

This demo contains the description of a Turing Machine that accepts all strings of the form a^I b^j c^k where i, j, k >0 and i*j= k. In other words, this Turing Machine accepts strings where the number of c’s are equal to the number of a^s times the number of b^s and the string if formatted so all the a’s are in the front, all the b’s follow the a’s, and all the c’s follow the b’s. After the program has read in the file, it will print the description of the Turing machine and then ask you to provide a string you want to test. Type in the string you want to test, and press enter. If the given string contains characters that are not part of the Turing Machine’s alphabet, you will given “Invalid input message”. Otherwise, the program will print out the tape of the Turing Machine for all the steps of the computation ending with an accept or reject.

After calculating whether the string is accepted by the Turing Machine, the program will ask if you want to test another string. If you want to test another string, input “1” and press enter. Otherwise input “0” and press enter. After this, you will be asked if you want to test another Turing Machine. Input  “1” and press enter and provide the program with the name of the file you want to read next. Otherwise, input “0” and press enter to terminate the program. 

Note that for all machines you test the empty string is represented by giving the blank symbol as an input. For example, if the blank symbol of your tape alphabet is '-' then you would input '-' as the string you want to test if you want to test the empty string.  
