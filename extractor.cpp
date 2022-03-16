#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "FrameSequence.h"

int main(int argc, char *argv[]){
	std::vector<PKNNIV001::FrameSequence> videos;
	//std::ofstream output{"output.pgm",std::ios::binary};
	if(argc == 1){
		std::cerr << "ARGUEMENTS ARE MISSING"<< std::endl;
		return 1;
	}

	//reading in command line arguements----------------------------
	int x1,y1,x2,y2,fw,fh =0;
	std::string infile = argv[1];
	
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

			PKNNIV001::FrameSequence q =  PKNNIV001::FrameSequence();
			q.operation = argv[i+1];
			q.oname = argv[i+2];
			videos.push_back(q);
			
		}
		else if(s == "-p"){
			//read in all points
		}		
	}//---------------------------------------------------------------
	
	std::string line{""};
	std::string size{""};
	std::stringstream header{line};
	std::ifstream file{infile, std::ios::binary};
	
	//reading through header-----------
	while(true){
		std::getline(file,line);
		header << line << std::endl;
		if(line == "255"){
			break;
		}
		 size= line;
	}
	//output << header.str() << std::endl;
	std::stringstream ssize{size};
	ssize >> size;
	int width{std::stoi(size)};
	ssize >> size;
	int height{std::stoi(size)};

	//--------
	
	
	//reading in block to memory-----------
	PKNNIV001::readfile(file,header.str());
	file.close();
	//create blocks in frame
	for(auto g:videos){
		//for p just iterate over list of co ordinates
		g.extract(x1,y1,x2,y2,fw,fh, width,height);
		g.printToFiles(fw, fh);
		system("rm videos/*");
		system("ffmpeg -framerate 20 -pattern_type glob -i 'images/*.pgm' -c:v libx264 -r 30 videos/output.mp4");
	}
    
	std::cout << "END" << std::endl;
	delete [] PKNNIV001::mem;
	//output.close();
	return 0;
}
