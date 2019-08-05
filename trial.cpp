#include <iostream>
#include <string>
#include <regex>

bool validateOutput(const std::string& ip, const bool& output) {

	std::regex reg("(aa|abb)*b");
	return (std::regex_match(ip, reg) xor output)? false : true;
	
}

int main() {

	bool flag = false, checkIfValid = false;
	int a = 0, b = 0, e = 0;
	std::string input = "";

	while(true) {
		a = 0; b = 0, e = 0;

		std::cout << "\n Enter a string of a's and b's:";
		std::getline(std::cin,input);
		int len = input.length();

		if(input == "exit") exit(0);

		for(int i = 0; i < len; i++) {
			flag = true;
			switch(input[i]) {				
				case 'a':
					a++; b = 0;				
					if(i == len-1) flag = false; // if it ends with a
					if(i != 0) if(input[i-1] != 'a' and input[i+1] != 'a' and input[i+1] != 'b') flag = false; // checking for a
					break;
				case 'b':
					b++;
					if(len == 2) { flag = false; break; } // if len is 2
					if(i != len-1 and a % 2 == 0 and a != 0) { flag = false; break; } // b in between without string end
					a = 0;
					if(i == 0 and i != len-1) {	flag = false; break; } // if it starts from b
					if(b > 2 and i != len-1) {	flag = false; break; }	// more than 2 bs without string end				
					if(b % 2 == 0 and i == len-1) { flag = false; break; } // even b's with string end 
					break;
				default: flag = false;		
					
			}
			if(flag == false) {
				e++;
				if(input[i] != 'a' && input[i] != 'b') std::cout << "Unaccepted Char at" << i << "\n";
				else std::cout << "Position of " << input[i] << " at " << i << " is invalid" << "\n";
			}

		}
		if(e == 0) { std::cout << "\n Valid \n"; checkIfValid = true; }
 		else { std::cout << "\n Invalid \n"; checkIfValid = false; }

 		std::cout << "\n Validating output with C++ Standard Library REGEX:";
		bool isValid = validateOutput(input, checkIfValid);

		if(isValid) std::cout << "\n Code is Correct!";
		else std::cout << "\n Some error in code";

	}

	return 0;
}

/*

FAIL-CASES FOR A :

	* If it ends with 'a' 
	* If there is anything other than 'a' and 'b' in the next position


FAIL-CASES FOR B:

	* If there are even numbers of 'b' with the string ending 
	* If len of string is two
	* If there is a single 'b' in between without string ending
	* If input starts from 'b'
	* If there are more than 2 'b's in between without string end

*/