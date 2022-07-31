#include "pnm.h"
#include <memory>
#include <iostream>
#include <fstream>

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
int pbm::save(std::string* fileName){
    std::ofstream file;
    file.open(* fileName, std::ios::out);
    file << this->getMagicNumber();
    file << ' ';
    file << std::to_string(this->width) << ' ' << std::to_string(this->height);
    file << ' ';
    std::bitset<8> bitset ("00000000");
    int bitsetCursor=0;
    for(int y = 0; y < this->height; y++){
        for(int x = 0; x < this->width; x++){
            if(this->map[y][x]->getBit()){
                bitset.set(7-bitsetCursor);
            }else{
                bitset.reset(7-bitsetCursor);
            }
            bitsetCursor++;
            if(bitsetCursor==8){
                file << uint8_t(bitset.to_ullong());
                bitsetCursor = 0;
            }
        }
        if(bitsetCursor !=0){
            file << uint8_t(bitset.to_ullong());
            bitsetCursor = 0;
        }
    }
    file.close();
    if(file.fail()){return 1;}
    return 0;
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

int pgm::save(std::string* fileName){
    std::ofstream file;
    file.open(* fileName, std::ios::out);
    file << this->getMagicNumber();
    file << ' ';
    file << std::to_string(this->width) << ' ' << std::to_string(this->height);
    file << ' ';
    file << std::to_string(this->range);
    file << ' ';
    for(int y = 0; y < this->height; y++){
        for(int x = 0; x < this->width; x++){
            file << uint8_t(this->map[y][x]->getGray());
        }   
    }
    file.close();
    if(file.fail()){return 1;}
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

int ppm::save(std::string* fileName){
    std::ofstream file;
    file.open(* fileName, std::ios::out);
    file << this->getMagicNumber();
    file << ' ';
    file << std::to_string(this->width) << ' ' << std::to_string(this->height);
    file << ' ';
    file << std::to_string(this->range);
    file << ' ';
    for(int y = 0; y < this->height; y++){
        for(int x = 0; x < this->width; x++){
            file << uint8_t(this->map[y][x]->getR());
            file << uint8_t(this->map[y][x]->getG());
            file << uint8_t(this->map[y][x]->getB());
        }   
    }
    //file << std::endl;
    file.close();
    if(file.fail()){return 1;}
    return 0;
}

std::string ppm::getMagicNumber(){
    return "P6"; // P6 for BINARY - P3 for ASCII
}

void ppm::pushToRow(int targetRow, int valueR, int valueG, int valueB){
    this->map[targetRow].push_back(std::move(std::make_unique<RGBpixel>(valueR,valueG,valueB)));
}
