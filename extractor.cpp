#include <iostream>
#include <string>

int main(int argc, char *argv[]){


	for (int i = 1; i < argc; i++) {
        // Technically "right" does not need to be repeated, but
        // we would probably tweak formatting more in the future
        std::cout << i << ": " << argv[i] << "\n";
    }

	
	return 0;
}
