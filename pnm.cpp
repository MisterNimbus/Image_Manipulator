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

std::ostream& operator<<(std::ostream& os, pbm& pnm){
        os << pnm.getMagicNumber() << std::endl;
        os << pnm.height << " " << pnm.width << std::endl;
        for(int y=0; y < pnm.height; y++){
            for (int x = 0; x< pnm.width; x++){
                os << pnm.map[y][x]->output() << " - ";
            }
            os << std::endl;
        }
    return os;
}

std::string pbm::getMagicNumber(){
    return "P4"; // P4 for BINARY - P1 for ASCII
}

void pbm::pushToRow(int targetRow, bool value){
    this->map[targetRow].push_back(std::move(std::make_unique<BINARYpixel>(value)));
}

///////////////////////////////////////////////////////////////////////////

pgm::pgm(int width, int height, int range): pnm(pnm::pgm), width(width), height(height), range(range){   
    this->map.resize(height);
}

pgm::~pgm(){
}

int pgm::format(){
return 0;
}

std::string pgm::print(){
    std::string result = "";
        for(int y=0; y < this->height; y++){
            for (int x = 0; x< this->width; x++){
                result += this->map[y][x]->output() + " - ";
            }
            result += "\n";
        }
    return result;
}

std::ostream& operator<<(std::ostream& os, pgm& pnm){
        os << pnm.getMagicNumber() << std::endl;
        os << pnm.height << " " << pnm.width << " " << pnm.range << std::endl;
        for(int y=0; y < pnm.height; y++){
            for (int x = 0; x< pnm.width; x++){
                os << pnm.map[y][x]->output() << " - ";
            }
            os << std::endl;
        }
    return os;
}

std::string pgm::getMagicNumber(){
    return "P5"; // P5 for BINARY - P2 for ASCII
}

void pgm::pushToRow(int targetRow, int grayValue){
    this->map[targetRow].push_back(std::move(std::make_unique<GRAYpixel>(grayValue)));
}

///////////////////////////////////////////////////////////////////////////

ppm::ppm(int width, int height, int range): pnm(pnm::ppm), width(width), height(height), range(range){   
    this->map.resize(height);
}

ppm::~ppm(){
}

int ppm::format(){
return 0;

}


std::string ppm::print(){
    std::string result = "";
        for(int y=0; y < this->height; y++){
            for (int x = 0; x< this->width; x++){
                result += this->map[y][x]->output() + " - ";
            }
            result += "\n";
        }
    return result;
}

std::ostream& operator<<(std::ostream& os, ppm& pnm){
        os << pnm.getMagicNumber() << std::endl;
        os << pnm.height << " " << pnm.width << " " << pnm.range << std::endl;
        for(int y=0; y < pnm.height; y++){
            for (int x = 0; x< pnm.width; x++){
                os << pnm.map[y][x]->output() << " - ";
            }
            os << std::endl;
        }
    return os;
}

std::string ppm::getMagicNumber(){
    return "P6"; // P6 for BINARY - P3 for ASCII
}

void ppm::pushToRow(int targetRow, int valueR, int valueG, int valueB){
    this->map[targetRow].push_back(std::move(std::make_unique<RGBpixel>(valueR,valueG,valueB)));
}
