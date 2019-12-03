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

turingMachine read_secen_tuple(string file);
void printMachine(turingMachine machine);

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
			newFunction.currentState = state;
			newFunction.currentSymbol= symbol;
			newFunction.newState = nextState;
			newFunction.overwriteSymbol= overwrite;
			if(direct.compare("R") == 0)
				newFunction.move = RIGHT;
			else if(direct.compare("L") == 0)
				newFunction.move = LEFT;
			else
				newFunction.move = ERROR;
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
	int run= 1;
	while(run ==1){
		cout<<"Please enter the name of the file containing the Turing Machine information.\n";
		string file;
		cin>>file;
		turingMachine machine =read_seven_tuple(file);
		printMachine(machine);
		int loop =1;
		while(loop==1){
			cout<<"Please enter string you want to test.\n";
			string input;
			cin>>input;
			vector<char> tape= checkInput(machine.alphabet, input, machine.gamma.at(0));
			if(tape.size() == input.length())
				simulate(machine, tape);
			cout<<"Please enter 1 if you want to test another string in the language.\n";
			cin>> loop;
		}
		cout<<"Please enter 1 if you want to read another Turing Machine file.\n";
		cin>>run;
	}
}







