#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]){

	if(argc == 1){
		std::cerr << "ARGUEMENTS ARE MISSING"<< std::endl;
		return 1;
	}

	//reading in command line arguements----------------------------
	int x1,y1,x2,y2,fw,fh;
	std::string infile = argv[1];
	std::ifstream file{infile, std::ios::binary};
	std::string outname, operation;
	for(size_t i=0; i<argc;++i){
		//std::cout << argv[i] << std::endl;
		}

	for(size_t i=2; i<argc;++i){
		std::string s{argv[i]};
		if(s == "-t"){
			x1 = std::atoi(argv[i+1]);
			y1 = std::atoi(argv[i+2]);
			x2 = std::atoi(argv[i+3]);
			y2 = std::atoi(argv[i+4]);
		}
		else if(s == "-s"){
				fw = std::atoi(argv[i+1]);
				fh = std::atoi(argv[i+2]);
		}
		else if(s == "-w"){
				outname = argv[i+1];
				operation = argv[i+2];
		}
		else if(s == "-p"){
			//read in all points
		}		
	}//---------------------------------------------------------------

	std::string line;
	std::string size;
	
	//reading through header-----------
	while(true){
		std::getline(file,line);
		if(line == "255"){
			break;
		}
		 size= line;
	}
	std::stringstream ssize{size};
	ssize >> size;
	int width{std::stoi(size)};
	ssize >> size;
	int height{std::stoi(size)};
	//-------------------------------
	unsigned char **l;


	std::ofstream output{"output.pgm",std::ios::binary};
	output.close();
	return 0;
}
