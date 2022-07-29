#include "pnm.h"
#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////////

pnm::pnm(enum pnm::pnmType type):pnmType(type){
}

pnm::~pnm(){
}

///////////////////////////////////////////////////////////////////////////

pbm::pbm(int width, int height): pnm(pnm::pbm), width(width), height(height){
    this->map.resize(height);
}

pbm::~pbm(){
}

int pbm::format(){
    return 0;
}

std::string pbm::print(){
std::string result = "";
    for(int y=0; y < this->height; y++){
        for (int x = 0; x< this->width; x++){
            result += this->map[y][x]->output() + " - ";
        }
        result += "\n";
    }
return result;
}

int pbm::getMagicNumber(){
    return 4; // P4 for BINARY - P1 for ASCII
}

void pbm::pushToRow(int targetRow, bool value){
    this->map[targetRow].push_back(std::move(std::make_unique<BINARYpixel>(value)));
}

///////////////////////////////////////////////////////////////////////////

pgm::pgm(int width, int height, int range): pnm(pnm::pgm), width(width), height(height), range(range){   
}

pgm::~pgm(){
}

int pgm::format(){
return 0;
}
int pgm::getMagicNumber(){
    return 5; // P5 for BINARY - P2 for ASCII
}

void pgm::pushToRow(int targetRowNumber, std::unique_ptr<GRAYpixel> pixel){
    this->map[targetRowNumber].push_back(std::move(pixel));
}

///////////////////////////////////////////////////////////////////////////

ppm::ppm(int width, int height, int range): pnm(pnm::ppm), width(width), height(height), range(range){   
}

ppm::~ppm(){
}

int ppm::format(){
return 0;

}

int ppm::getMagicNumber(){
    return 6; // P6 for BINARY - P3 for ASCII
}

void ppm::pushToRow(int targetRowNumber, std::unique_ptr<RGBpixel> pixel){
    this->map[targetRowNumber].push_back(std::move(pixel));
}
