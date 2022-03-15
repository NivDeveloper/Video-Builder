#include "FrameSequence.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>

namespace PKNNIV001{

    FrameSequence::FrameSequence(void){};
    FrameSequence::~FrameSequence(){};

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
        float min=std::sqrt(std::pow((ex-sx),2)+std::pow((ey-sy),2));
        int fx = sx;
        int fy = sy;
        int fno = 0;
        
        while(fx!=ex && fy!=ey){
            //read in fx, fy
            //std::cout << fx << " = " << ex << "and" << fy << " = " << ey << std::endl;
            char ** frame = new char*[fh] ;
            int l = 0;
            for(int h = 0; h<fh;++h){
                frame[h] = new char[fw];
                for(int w =0; w<fw;++w){
                    frame[h][w] =  getmem()[fy*width+fx+w+h*width];
                    //std::cout << l << ":";
                    //std::cout << w << ":" << h << "   ";
                    ++l;
                }
            }
           
            imageSequence.push_back(frame);
            delete [] frame;
            for(int x = -1;x<2;++x){
                for(int y= -1;y<2;++y){
                     
                    float dist = std::sqrt(std::pow((ex-(fx+x)),2)+std::pow((ey-(fy+y)),2));
                    if(dist<min){
                        min = dist;
                        fx += x;
                        fy += y;
                        //std::cout << "x=" << fx << " and y=" <<fy << std::endl;
                    }
                }
            }

        }
    }


    void FrameSequence::printToFiles(int width, int height){
        std::streampos wid{width};
        int i= 0;
        for(auto o:imageSequence){
            i++;
            std::cout << imageSequence.size() << std::endl;
            std::stringstream name;
            name << "images/" << oname << i << ".pgm";
            std::ofstream file{name.str(), std::ios::binary};
            file << "P5" << std::endl;
            file << width << " " << height << std::endl;
            file << "255" << std::endl;
            for(size_t h = 0; h< height;++h){
                file.write(o[h],wid);
                
                //"  " << h << ":" << w<< "   " ;// 
                //std::cout << std::endl;
            }
            file.close();
        }

    }

}
