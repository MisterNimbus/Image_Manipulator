#include "pnm.h"

///////////////////////////////////////////////////////////////////////////

pnm::pnm(enum pnm::pnmType type):pnmType(type){
}

pnm::~pnm(){
}


///////////////////////////////////////////////////////////////////////////

pbm::pbm(int width, int height): pnm(pnm::pbm), width(width), height(height){   
}

pbm::~pbm(){
}

int pbm::getMagicNumber(){
    return 4; // P4 for BINARY - P1 for ASCII
}

void pbm::pushToRow(int targetRowNumber, std::unique_ptr<BINARYpixel> pixel){
    this->map[targetRowNumber].push_back(std::move(pixel));
}

///////////////////////////////////////////////////////////////////////////

pgm::pgm(int width, int height, int range): pnm(pnm::pgm), width(width), height(height), range(range){   
}

pgm::~pgm(){
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

int ppm::getMagicNumber(){
    return 6; // P6 for BINARY - P3 for ASCII
}

void ppm::pushToRow(int targetRowNumber, std::unique_ptr<RGBpixel> pixel){
    this->map[targetRowNumber].push_back(std::move(pixel));
}
