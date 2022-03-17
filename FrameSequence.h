#ifndef _FRAMESEQUENCE_H_
#define _FRAMESEQUENCE_H_
#include <vector>
#include <string>
#include <iostream>

namespace PKNNIV001{

	static char * mem;
	static void setmem(int size){mem = new char[size];};
	static char * getmem(){return mem;};
	void readfile(std::ifstream &file, std::string header);

	class FrameSequence{
	
	public:
		std::vector<char **> imageSequence;
		std::string oname, operation;
		
		FrameSequence(void);
		~FrameSequence();

		void extract(int sx, int sy, std::vector<int> ex, std::vector<int> ey, int fw, int fh, int width, int height);
		void readfile(std::ifstream file, std::string header);
		void printToFiles(int width, int height );
		void writeFrame(int fh, int fw, int fx, int fy, int width, int height);
	
	};


}



#endif
