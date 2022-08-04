#include "pnm.h"
#include <memory>
#include <iostream>
#include <fstream>

///////////////////////////////////////////////////////////////////////////

pnm::pnm(int width, int height,int range):width(width),height(height),range(range){
}

pnm::~pnm(){
}

pnm * pnm::read(std::string * sourceFile){
    
    std::string pnmMagicNumberBuffer = "", widthBuffer="", heightBuffer="", rangeBuffer="";
    std::fstream file;
    file.open(* sourceFile, std::fstream::in | std::fstream::binary);
    if(file.fail()){
        std::cout << std::endl << std::endl << "FAILED" << std::endl ;
    }
    file >> pnmMagicNumberBuffer;
    file >> widthBuffer;
    file >> heightBuffer;

    if(pnmMagicNumberBuffer == "P4"){
        pnm * PBMptr = new pbm(stoi(widthBuffer),stoi(heightBuffer));
            unsigned char B;
            std::bitset<8> bitset;
            for(int y=0; y < stoi(heightBuffer); y++){
                for(int x=0; x < stoi(widthBuffer); x+=8){
                    file >> B;
                    bitset = int(B);
                    int i = 7;
                    int k = 0;
                    if(x>=stoi(widthBuffer)){
                        k = x - stoi(widthBuffer);
                    }
                    for(i=7;i>=k;i--){
                        if(bitset[i]==true){
                            PBMptr->pushToRow(y,1);
                        }else{
                            PBMptr->pushToRow(y,0);
                        }
                    }
                }
            }
        file.close();
        std::cout << &PBMptr;
        return PBMptr;
    }
    else if (pnmMagicNumberBuffer == "P5"){ // BU PGM
        file >> rangeBuffer;
        pnm * NEWpgm(new pgm(stoi(widthBuffer),stoi(heightBuffer),stoi(rangeBuffer)));
        int gray;
        for(int y=0; y < stoi(heightBuffer); y++){
            for(int x=0; x < stoi(widthBuffer); x++){
            file >> gray;
            if(gray == 10){gray = 11;}
            std::cout << gray;
            NEWpgm->pushToRow(y,gray);
            }
        }
        file.close();
        return NEWpgm;
    }
    else if (pnmMagicNumberBuffer == "P6"){ //
        file >> rangeBuffer;
        pnm * NEWppm(new ppm(stoi(widthBuffer),stoi(heightBuffer),stoi(rangeBuffer)));
        int R,G,B;
        for(int y=0; y < stoi(heightBuffer); y++){
            for(int x=0; x < stoi(widthBuffer); x++){
            file >> R;
            if(R == 10){R = 11;}            
            file >> G;
            if(G == 10){G = 11;}
            file >> B;
            if(B == 10){B = 11;}
            NEWppm->pushToRow(y,R,G,B);
            }
        }
        file.close();
        return NEWppm;
    }
    return NULL;
}

std::string pnm::print(){
    std::string result = "";
        for(int y=0; y < this->height; y++){
            for (int x = 0; x< this->width; x++){
                result += this->map[y][x]->outputRGB() + " - ";
            }
            result += "\n";
        }
    return result;
}


///////////////////////////////////////////////////////////////////////////

pbm::pbm(int width, int height): pnm(width,height,1){
    this->map.resize(height);
}

pbm::~pbm(){
}


std::string pbm::print(){
    std::string result = "";
        for(int y=0; y < this->height; y++){
            for (int x = 0; x< this->width; x++){
                result += this->map[y][x]->getBit() + " - ";
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
                os << pnm.map[y][x]->getBit() << " - ";
            }
            os << std::endl;
        }
    return os;
}

std::string pbm::getMagicNumber(){
    return "P4"; // P4 for BINARY - P1 for ASCII
}

void pbm::pushToRow(int targetRow, int val1, int val2, int val3){
    this->map[targetRow].push_back(std::move(std::make_unique<pixel>(val1)));
}

///////////////////////////////////////////////////////////////////////////

pgm::pgm(int width, int height, int range): pnm(width,height,range){   
    this->map.resize(height);
}

pgm::~pgm(){
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
            file << uint8_t(this->map[y][x]->getGRAY());
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
                result += this->map[y][x]->outputGRAY() + " - ";
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
                os << pnm.map[y][x]->outputGRAY() << " - ";
            }
            os << std::endl;
        }
    return os;
}

std::string pgm::getMagicNumber(){
    return "P5"; // P5 for BINARY - P2 for ASCII
}

void pgm::pushToRow(int targetRow, int val1, int val2, int val3){
    this->map[targetRow].push_back(std::move(std::make_unique<pixel>(val1)));
}

///////////////////////////////////////////////////////////////////////////

ppm::ppm(int width, int height, int range): pnm(width,height,range){   
    this->map.resize(height);
}

ppm::~ppm(){
}


std::string ppm::print(){
    std::string result = "";
        for(int y=0; y < this->height; y++){
            for (int x = 0; x< this->width; x++){
                result += this->map[y][x]->outputRGB() + " - ";
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
            os << pnm.map[y][x]->outputRGB() << " - ";
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

void ppm::pushToRow(int targetRow, int val1, int val2, int val3){
    this->map[targetRow].push_back(std::move(std::make_unique<pixel>(val1,val2,val3)));
}
