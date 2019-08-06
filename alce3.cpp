#include <iostream>
#include <string>
#include <regex>

bool validateOutput(const std::string& ip, const bool& output) {

	std::regex reg("(aba+|abab+)");
	return (std::regex_match(ip, reg) xor output)? false : true;
	
}

int main() {

	std::string input = "";
	bool flag = false, checkIfValid = false; 
	int e = 0;
	while(true) {
		
		e = 0;
		std::cout << "\n Enter language:";
		std::getline(std::cin, input);
		int len = input.length();
		if(input == "exit") exit(0);

		for(int i = 0; i < len; i++) {
			flag = true;
			if(len == 3) {
				if(input[0] != 'a' or input[1] != 'b' or input[2] != 'a') flag = false;	
				else flag = true;
			}					
			else {
			
				switch(input[3]) {
					case 'a':						
						if(i > 3 and input[i] != 'a') { flag = false; break; }						
					break;
					case 'b':						
						if(i > 3 and input[i] != 'b') { flag = false; break; }
					break;
					default: flag = false;
					break;
				}
			}

			if(flag == false) {
				e++;
				if(input[i] != 'a' && input[i] != 'b') std::cout << "Unaccepted Char at" << i << "\n";
				else std::cout << "Position of " << input[i] << " at " << i << " is invalid" << "\n";
			}

		}
		if(e == 0) { std::cout << "\n Valid Input \n"; checkIfValid = true; }
 		else { std::cout << "\n Invalid Input, Please Check Your String And Try Again \n"; checkIfValid = false; }

 		std::cout << "\n ***** Validating Output With C++ Standard Library REGEX ***** \n";
		bool isValid = validateOutput(input, checkIfValid);

		if(isValid) std::cout << "\n Code Is Correct! \n";
		else std::cout << "\n Some Error In Code \n";

	}

	return 0;
}
