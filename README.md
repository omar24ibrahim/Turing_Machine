# Turing Machine Simulation

In this project a simulation for how does the TM works. The way of implementing this simulation is done using C programming language.
The simulation accepts inputs from the user to build the Turing Machine by declaring its formal defining 5-tuple [States, Initial State, Final State, Alphabet, Gamma]. The simulation shows the configurations according to the input tape (provided by the user) starting from the head position (indicated by the user) and shows the encoded version of the TM.

## - Implementation

* The input tape is an array of characters (string) of pre-allocated size of 1000 characters to avoid the burden of handling continous re-allocation.
* States are represented by integers from 0 to n-1; where n is an input got from the user corresponding to the number of states this machine deals with.
* The user is then asked to enter the characters used in his alphabet and gamma sets with a condition that he fills both fields with comma separation between each character in the set without any spaces. Moreover, in the gamma set insertion, the last character represents the empty symbol in the tape and if the transition function will deal with the left-end mark (<), it should be inserted in the begining of the gamma set entry.
* The user is then asked to enter the result of each transition case by entering three fields comma separated which are: number corresponding to the next state (with considering the previously mentioned restrictions about the number of states and thier range), the new symbol to be written on tape (which shoud be from the gamma set), and one of these uppercase letters [L-->left, R-->right, Y-->accepted, N-->rejected/error] representing the taken action.
* Later on, the user is asked to enter the input tape and then indicate the head osition on the tape with considering that the index 0 refers to the left-end mark (which is not inserted by the user and gets inserted by the system automatically) and the characters inserted by the user start from index 1.
* The simulation shows the sequence of configurations done till the machine terminates whether with acceptance, rejection or error occurrence.
* The transition function is implemented as a struct created where each has 2 integer variables indicating current and next states, 2 charachter variables for the current input symbol and new symbol and an enumeration called action for the actions where [L-->1, R-->2, Y-->3, N-->4]. The machine has an array of Transactions of places equivalent to the number of gamma symbols multiplied by the number of states.
* A string of zeros and ones is printed to show the encrypted version of the TM where each symbol is represented by number of ones corresponding to its appearance in the set it belongs to and between each field and the other a zero is printed and between each transition and the other double zeros are printed.

    ex: N=2, Gamma=[a, b, #] -----> (q0,a)-->(q0,a,L), (q0,b)-->(q1,#,Y)

        Encrypted Version --------> 10101010100101101101110111

## - Restrictions

1.  Number of States > 0.
2.  Number of Gamma Symbols >= Number of Alphabet Symbols + 1.
3.  All symbols of Alphabet appear in Gamma.
4.  Last Gmma Symbol reoresents empty symbol.
5.  Left-End Mark must be inserted in the begining of Gamma if needed to be used.
6.  0 <= Initial State < Number of States.
7.  Validity of each input entered must be respected.
8.  Do not enter the left-end mark while typing the input tape. 
