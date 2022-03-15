#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]){
	std::ofstream output{"output.pgm",std::ios::binary};
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
	std::stringstream header;
	
	
	//reading through header-----------
	while(true){
		std::getline(file,line);
		std::cout << line << std::endl;
		//output << line << std::endl;
		header << line << std::endl;
		if(line == "255"){
			break;
		}
		
		 size= line;
		 std::cout << line;
	}
	output << header.str() << std::endl;
	std::stringstream ssize{size};
	ssize >> size;
	int width{std::stoi(size)};
	ssize >> size;
	int height{std::stoi(size)};
	std::cout << "width" << width << std::endl;
	std::cout << "heightis" << height <<  std::endl;

	//--------
	char **l = new char*[height];
	char **f = new char*[height];
	//std::stringstream ss;
	

	//reading in file-----------
	file.seekg(0,file.end);
	std::streampos h{header.str().length()};
	std::streampos si = file.tellg()-h;

    char *memblock = new char [si];
    file.seekg(int(header.str().length())+1, std::ios::beg);
    file.read (memblock, si);
	//output.write(memblock, si);
    file.close();
	
	//--------------------------
	for(size_t r = 0; r<height;++r){
		for(size_t c=0; c<width;++c){
			output.write(&memblock[(r*width)+c],1);
		}
		
	}
	std::cout << "END" << std::endl;


	
	output.close();
	return 0;
}
