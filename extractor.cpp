#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "FrameSequence.h"

int main(int argc, char *argv[]){
	std::vector<PKNNIV001::FrameSequence> videos;	//if multiple videos are requested
	if(argc == 1){
		std::cerr << "ARGUEMENTS ARE MISSING"<< std::endl;
		return 1;
	}

	//reading in command line arguements----------------------------
	int x1,y1,fw,fh =0;
	std::vector<int> x2 ,y2;		//vector of points to reach
	std::string infile = argv[1];	//name of file to read in 
	
	for(size_t i=2; i<argc;++i){	
		std::string s{argv[i]};
		if(s == "-t"){				//reading in startpos and end pos
			x1 = std::atoi(argv[i+1]);
			y1 = std::atoi(argv[i+2]);
			x2.push_back(std::atoi(argv[i+3]));
			y2.push_back(std::atoi(argv[i+4]));
		}
		else if(s == "-s"){			//reads in size of frame
			fw = std::atoi(argv[i+1]);
			fh = std::atoi(argv[i+2]);
			if(fw==0 || fh == 0){	//if invalid frame size is entered
				std::cerr << "PLEASE INPUT A VALID FRAME SIZE" << std::endl;
				return 1;
			}
		}
		else if(s == "-w"){			//read in all videos

			PKNNIV001::FrameSequence q =  PKNNIV001::FrameSequence();
			q.operation = argv[i+1];
			q.oname = argv[i+2];
			videos.push_back(q);
			
		}
		else if(s == "-p"){			//read in all points to reach
			int q=3;
			x1 = std::atoi(argv[i+1]);
			y1 = std::atoi(argv[i+2]);
			while(argv[i+q]!="-s"){
				x2.push_back(std::atoi(argv[i+q]));
				q++;
				y2.push_back(std::atoi(argv[i+q]));
				q++;
			}
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
	std::stringstream ssize{size};
	ssize >> size;
	int width{std::stoi(size)};
	ssize >> size;
	int height{std::stoi(size)};
	//--------------------------------
	
	
	//reading in block to memory-----------
	PKNNIV001::readfile(file,header.str());
	file.close();
	//-------------------------------------

	//iterate over all videos to make
	for(auto g:videos){
		//call functions to read and write frames
		g.extract(x1,y1,x2,y2,fw,fh, width,height);
		g.printToFiles(fw, fh);
		
		std::string out ="ffmpeg -framerate 20 -pattern_type glob -i 'images/"+g.oname+"*.pgm' -c:v libx264 -r 30 videos/"+g.oname+".mp4";
		//system(out.c_str());	used for personal testing
	}
    delete PKNNIV001::mem;	//delete pointer holding original image
	
	return 0;
}
