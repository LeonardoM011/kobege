#include "PrintError.h"

int PrintError::PrintLn(int num, std::string err) {
	std::cout << "Error " << num << ": " << err << "." << std::endl;
	return 1;
}
