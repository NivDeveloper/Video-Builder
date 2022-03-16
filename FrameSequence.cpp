#include "FrameSequence.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>

namespace PKNNIV001{

    FrameSequence::FrameSequence(void){};
    FrameSequence::~FrameSequence(){
        for(auto o:imageSequence){
            delete [] o;
            
        }
        //delete mem;
    };

    void readfile(std::ifstream &file, std::string header){

        file.seekg(0,file.end);
        std::streampos h{header.length()};
        std::streampos si = file.tellg()-h;
        //char *memblock = new char[si];
        PKNNIV001::setmem(si);
        //delete memblock;
        file.seekg(int(header.length())+1, std::ios::beg);
        file.read (getmem(), si);
    }
	

    void FrameSequence::extract( int sx, int sy, int ex, int ey, int fw, int fh, int width, int height){
    
        //for each frame append to imagesequence list
        
        int fx = sx;
        int fy = sy;
        int fno = 0;
        
        //float mingrad = (ey-sy)/(ex-sx);
        
        int l = 0;
        while(fx!=ex || fy!=ey){
            //read in fx, fy
            //std::cout << fx << " = " << ex << "and" << fy << " = " << ey << std::endl;
            char ** frame = new char*[fh] ;
            //std::cout << "fx=" << fx << "   fy=" << fy << std::endl;
            for(int h = 0; h<fh;++h){
                frame[h] = new char[fw];
                for(int w =0; w<fw;++w){
                    //check if out of bounds
                    frame[h][w] = 255-getmem()[fy*width+fx+w+h*width];
                    
                    //std::cout << w << ":" << h << "   ";
                    
                }
            }
            ++l;
            //std::cout << frame[100][100];
            imageSequence.push_back(frame);
            
            //delete [] frame;
            int tempx= 0;
            int tempy= 0;
            //find distnce between end and current frame pos
            
            //find which direction to move
            //loop over all surrounding blocks
            double running = 100000;
            float framedist=std::sqrt(std::pow((ex-fx),2)+std::pow((ey-fy),2));
            for(int x = -1;x<=1;++x){
                for(int y= -1;y<=1;++y){
                    //distance between iterating frame pos and end
                    
                    float dist = std::sqrt(std::pow((ex-(fx+x)),2)+std::pow((ey-(fy+y)),2));
                    if(dist<framedist){
                        //calc gradient diff
                        double currgdiff = std::abs(
                            (float(ey-(fy+y))/(ex-(fx+x)))
                            -(float(ey-sy)/(ex-sx)));

                            if(currgdiff<running || (((fy+y)==ey)&&((fx+x)==ex))){
                                //std::cout << x << std::endl;
                                running = currgdiff;
                                tempx = x;
                                tempy = y;
                                //std::cout << x << ":" << y << "  "<< dist<<"   ";
                            }
                        
                          
                    }
                }
            }
            fx += tempx;
            fy += tempy;

        }
        //std::cout << l << ": " << std::endl;
    }


    void FrameSequence::printToFiles(int width, int height){
        std::streampos wid{width};
        int i= 0;
        system("rm images/*");
        //std::cout << "number of frames ";// << imageSequence.size();
        for(auto o:imageSequence){
            i++;
            
            //std::cout << imageSequence.size() << std::endl;
            std::stringstream name;
            name << "images/" 
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
                    //std::cout << "writing";
                    //std::cout << o[h][w];
                    //std::cout << sizeof(o);
                    file.write(&o[h][w],1);
                }
                //"  " << h << ":" << w<< "   " ;// 
                //std::cout << std::endl;
            }
            file.close();
        }

    }

}
