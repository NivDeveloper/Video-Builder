#include "FrameSequence.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>

namespace PKNNIV001{

    FrameSequence::FrameSequence(void){};   //constructor

    FrameSequence::~FrameSequence(){        //destructor
        for(auto o:imageSequence){          //deletes all pointers holding frames
            delete [] o;                    //once object is destroyed
            
        }
    };

    void readfile(std::ifstream &file, std::string header){
        //reading in contents of source image to the heap
        file.seekg(0,file.end);
        int length = header.length();
        std::streampos h{length};
        std::streampos si = file.tellg()-h;
        PKNNIV001::setmem(si);  //setting memory size to hold entire source image
        //only read from after header
        file.seekg(int(header.length())+1, std::ios::beg);
        file.read (getmem(), si);
    }
    

	void FrameSequence::writeFrame(int fh, int fw, int fx, int fy, int width, int height){
        //writing frame to vector of frames
        char ** frame = new char*[fh];

        for(int h = 0; h<fh;++h){
            frame[h] = new char[fw];
            for(int w =0; w<fw;++w){
                //check if out of bounds
                if((fx+w)<0 || (fx+w)>width || (fy+h)<0 || (fy+h)>height){
                    frame[h][w] = '\0'; //make all out of bounds black
                }
                else if(operation == "invert" || operation == "reinvert"){
                    frame[h][w] = 255-getmem()[fy*width+fx+w+h*width];  //inverting image
                }
                else{
                    frame[h][w] = getmem()[fy*width+fx+w+h*width];  //write normally to frame
                }
                
                    
            }
        }
        imageSequence.push_back(frame); //appending frame to list of frames
    }

    void FrameSequence::extract( int sx, int sy, std::vector<int> ex, std::vector<int> ey, int fw, int fh, int width, int height){
        //finding correct path and writing it to vector
        int nsx,nsy;
        for(size_t end = 0; end < ex.size();++end){

            //for each frame append to imagesequence list
            if(end==0){
                nsx = sx;
                nsy= sy;
            }
            else{
                nsx = ex[end-1];
                nsy = ey[end-1];
            }
            int fx = nsx;
            int fy = nsy;
            
            while(fx!=ex[end] || fy!=ey[end]){

                writeFrame(fh,fw,fx,fy,width, height);
                int tempx= 0;
                int tempy= 0;
                //loop over all surrounding blocks
                double running = 100000;
                float framedist=std::sqrt(
                    std::pow(
                        (ex[end]-fx),2)
                    +
                    std::pow(
                        (ey[end]-fy),2)
                    );

                for(int x = -1;x<=1;++x){
                    for(int y= -1;y<=1;++y){

                        //distance between iterating frame pos and end
                        float dist = std::sqrt(
                            std::pow(
                                (ex[end]-(fx+x)),2)
                            +
                            std::pow(
                                (ey[end]-(fy+y)),2)
                            );

                        if(dist<framedist){
                            //calc gradient diff
                            if((ex[end]-nsx) ==0 ){
                                tempx = 0;
                                tempy = y;
                                
                                
                            }else if((ex[end]-(fx+x))==0){
                                tempx = x;
                                tempy = y;
                            }
                            else{
                                double currgdiff = std::abs(
                                    (float(ey[end]-(fy+y))/(ex[end]-(fx+x)))
                                    -(float(ey[end]-nsy)/(ex[end]-nsx)));

                                if(currgdiff<running) 
                                    {//(((fy+y)==ey)&&((fx+x)==ex)))
                                
                                    running = currgdiff;
                                    tempx = x;
                                    tempy = y;
                                }
                            }
                            
                            
                            
                        }
                    }
                }
                fx += tempx;
                fy += tempy;
                
            }

        }
        
    }


    void FrameSequence::printToFiles(int width, int height){

        std::streampos wid{width};
        int i;
        if(operation == "reverse" || operation == "reinvert"){
            i = imageSequence.size();
        }else{
            i = 1;
        }
        
        
        for(auto o:imageSequence){

            if(operation == "reverse" || operation == "reinvert"){
                i--;
            }else{
                i++;
            }
            std::stringstream name;//<< "images/"
            name  
                << oname 
                << std::right 
                << std::setw(4) 
                << std::setfill('0') 
                << i 
                << ".pgm";

            std::ofstream file{name.str(), std::ios::binary};
            file << "P5" << std::endl;
            file << width << " " << height << std::endl;
            file << "255" << std::endl;
            
            for(size_t h = 0; h< height;++h){
                for(size_t w = 0;w<width;++w){
                    file.write(&o[h][w],1);
                }
            }
            file.close();
        }

    }

}
