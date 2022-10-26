#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	try{
		ifstream ifile(argv[1]); //take in file based on argument

		int base;
		string d;
		string n;
		string code;
		ifile>>base>>d>>n; //take in base, private key, and modulus
		BigInt first(d,base);
		BigInt second(n,base);

		string answer = "";
		while(ifile.fail() ==false){ //while file doesn't fail: decrypt
			ifile>>code;
			BigInt decodedmessage(code,base);
			decodedmessage.modulusExp(first,second);
			answer = answer+(char)decodedmessage.to_int();
		}
		answer.pop_back();
		cout << answer << endl; //cout answer
	}

	catch (const exception& except){ //catch expection throws
		cout << except.what() <<endl;
		return -1;
	}

  
	return 0;
}
