#ifndef _FRAMESEQUENCE_H_
#define _FRAMESEQUENCE_H_
#include <vector>
#include <string>
#include <iostream>

namespace PKNNIV001{

	class FrameSequence{
	
	public:
		std::vector<unsigned char **> imageSequence;
		FrameSequence(void);
		~FrameSequence();
	
	
	
	};


}



#endif
