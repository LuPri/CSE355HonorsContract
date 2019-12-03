#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef enum{ LEFT = 0, RIGHT, ERROR} direction;

typedef struct transitions{
	string currentState;
	char currentSymbol;
	string newState;
	char overwriteSymbol;
	direction move;
} transitions;

typedef struct turingMachine{
	vector <string> states;
	vector <char> alphabet;
	vector <char> gamma;
	vector <transitions> function;
	string start;
	string accept;
}turingMachine;

void printMachine(turingMachine machine);

bool checkValidity(char symbol, vector<char> alphabet){
	bool valid = true;
	for(int i=0; i< alphabet.size(); i++){
		if(alphabet.at(i) == symbol)
			valid = false;
	}
	return valid;
}

bool checkState(string state, vector <string> states){
	bool valid = false;
	for(int i=0; i<states.size(); i++){
		if(state.compare(states.at(i)) == 0)
			valid = true;
	}
	return valid;
}

bool checkTapeAlphabet(char symbol, vector<char> gamma){
	bool valid = false;
	for( int i=0; i<gamma.size(); i++){
		if(symbol == gamma.at(i))
			valid = true;
	}
	return valid;
}

turingMachine read_seven_tuple(string file){
	int states;
	int alphabet;
	int gamma;
	int transition;
	ifstream fileReader;
	fileReader.open(file);
	if(fileReader.is_open()){
		fileReader>> states;
		turingMachine machine;
		for(int i =0; i< states; i++){
			string temp;
			fileReader >>temp;
			machine.states.push_back(temp);
		}
		fileReader >> alphabet;
		for(int i = 0; i<alphabet; i++){
			char temp;
			fileReader >> temp;
			machine.alphabet.push_back(temp);
		}
		fileReader>> gamma;
		for(int i=0; i<gamma; i++){
			char temp;
			fileReader>>temp;
			bool valid = checkValidity(temp, machine.alphabet);
			if(!valid){
				cout<<"The tape alphabet provided includes symbols given in the language alphabet. PLease make sure your tape alphabet is composed of unique symbols that are not part of the language alphabet.\n";
				exit(1);
			}
			machine.gamma.push_back(temp);
		}
		for(int i =0; i< machine.alphabet.size(); i++)
			machine.gamma.push_back(machine.alphabet.at(i));
		fileReader >> transition;
		for(int i =0; i<transition; i++){
			transitions newFunction;
			string state;
			char symbol;
			string arrow;
			string nextState;
			char overwrite;
			string direct;
			fileReader >> state;
			fileReader >>  symbol;
			fileReader >> arrow;
			fileReader >> nextState;
			fileReader >> overwrite;
			fileReader >> direct;
			bool valid = checkState(state, machine.states);
			if(!valid){
				cout<<"File contains an invalid state on the left hand side of a transition that was not provided in the Turing Machine definition.\n";
				exit(1);
			}
			valid = checkState(nextState, machine.states);
			if(!valid){
				cout<<"File contains an invalid state on the right hand side of a transition that was not provided in the Turing Machine definition.\n";
				exit(1);
			}
			valid = checkTapeAlphabet(symbol, machine.gamma);
			if(!valid){
				cout<<"File contains an invalid symbol on the left hand side of a transition that is not part of the tape alphabet given in the Turing Machine definition.\n";
				exit(1);
			}
			valid = checkTapeAlphabet(overwrite, machine.gamma);
			if(!valid){
				cout<<"File contains an invalid symbol on the right hand side of a transition that is not part of the tape alphabet given in the Turing Machine definition.\n";
				exit(1);
			}
			newFunction.currentState = state;
			newFunction.currentSymbol= symbol;
			newFunction.newState = nextState;
			newFunction.overwriteSymbol= overwrite;
			if(direct.compare("R") == 0)
				newFunction.move = RIGHT;
			else if(direct.compare("L") == 0)
				newFunction.move = LEFT;
			else{
				cout<<"File contains invalid movement option. Please make sure you only have R or L in your transitions.\n";
				exit(1);
			}
			machine.function.push_back(newFunction);
		}
		fileReader >> machine.start;
		fileReader >> machine.accept;
		fileReader.close();
		return machine;
	}
	else{
		cout<<"File could not be found."<<endl;
		exit(1);
	}
}


void printMachine(turingMachine machine){
	cout<< "Set of States = { ";
	for(int i=0; i<machine.states.size(); i++)
		cout<< machine.states.at(i)<< " ";
	cout<< "}"<<endl;
	cout<< "Alphabet: { ";
	for(int i=0; i<machine.alphabet.size(); i++)
		cout<< machine.alphabet.at(i)<<" ";
	cout<< "}"<<endl;
	cout<< "Gamma: { ";
	for(int i=0; i< machine.gamma.size(); i++)
		cout<< machine.gamma.at(i)<< " ";
	cout << "}"<<endl;
	cout<< "Transitions:"<<endl;
	for(int i=0; i<machine.function.size(); i++){
		cout<<" (" << machine.function.at(i).currentState;
		cout<<" " << machine.function.at(i).currentSymbol;
		cout<<") = ("<<machine.function.at(i).newState;
		cout<<" "<<machine.function.at(i).overwriteSymbol;
		if(machine.function.at(i).move == RIGHT)
			cout<< " R)"<<endl;
		else if(machine.function.at(i).move == LEFT)
			cout<< " L)"<<endl;
		else
			cout<< " E)"<<endl;
	}
	cout<< "Start State: " << machine.start<<endl;
	cout<< "Accept State: " <<machine.accept<<endl;
	cout<< "Reject State: qreject\n"; 
}

vector<char> checkInput(vector <char> alphabet, string input, char blank){
	vector<char> tape;
	bool print= false;
	if(input.length() == 1 && input[0] == blank){
		tape.push_back(input[0]);
		return tape;
	}
	for(int i = 0; i<input.length(); i++){
		int j=0;
		bool notFound= true;
		while( j< alphabet.size() && notFound){
			if(alphabet.at(j) == input[i]){
				notFound = false;
				tape.push_back(input[i]);
			}
			j++;
		}
		if(notFound)
			print= true;
	}
	if(print)
		cout<<"Invalid input.\n";
	return tape;
}

transitions findTransition(char symbol, string state, vector<transitions> function){
	transitions x;
	for(int i=0; i<function.size(); i++){
		x= function.at(i);
		if(x.currentState.compare(state) == 0 && x.currentSymbol == symbol)
			return x;
	}
	x.newState = "reject";
	return x;
}

void printState(string state, int tapeHead, vector<char> tape){
	for(int i=0; i<tape.size(); i++){
		if(i == tapeHead)
			cout<< state<<" "; 
		cout<<tape.at(i)<<" ";
	}
	cout<<endl;
}
void simulate(turingMachine machine,  vector<char> tape){
	string state= machine.start;
	int tapeHead= 0;
	if(tape.size() == 0)
		tape.push_back(machine.gamma.at(0));
	printState(state, tapeHead, tape);
	bool reject = false;
	while(!(state.compare(machine.accept) == 0) && !reject){
		transitions transition= findTransition(tape.at(tapeHead), state, machine.function);
		if(transition.newState.compare("reject") == 0)
			reject= true;
		else{
			state= transition.newState;
			tape.at(tapeHead)= transition.overwriteSymbol;
			if(transition.move == LEFT){
				if(tapeHead >0)
					tapeHead --;
			}
			else if(transition.move == RIGHT){
				if(tapeHead >= tape.size()-1){
					tape.push_back(machine.gamma.at(0));
					tapeHead++;
				}
				else
					tapeHead++;
			}
			printState(state, tapeHead, tape);
		}
	}
	if(reject)
		printState("qreject", tapeHead, tape);
}

int main(){
	char run= 'y';
	while(run =='y'){
		cout<<"Please enter the name of the file containing the Turing Machine information.\n";
		string file;
		cin>>file;
		turingMachine machine =read_seven_tuple(file);
		printMachine(machine);
		char loop = 'y';
		while(loop== 'y'){
			cout<<"Please enter string you want to test.\n";
			string input;
			cin>>input;
			vector<char> tape= checkInput(machine.alphabet, input, machine.gamma.at(0));
			if(tape.size() == input.length())
				simulate(machine, tape);
			cout<<"Would you like to test another string? Please enter y for yes or n for no.\n";
			cin>> loop;
		}
		cout<<"Would you like to read in another file? Plase enter y for yes or n for no.\n";
		cin>>run;
	}
}







