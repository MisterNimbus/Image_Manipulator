#include "pnm.h"
#include <memory>
#include <iostream>
#include <fstream>

///////////////////////////////////////////////////////////////////////////

PNM::PNM(int width, int height, PNMtype type, int range):
width(width),height(height),type(type),range(range)
{
    this->map.resize(height);
    for(int row=0; row<height; row++){
        this->map[row].resize(width);
        for(int col = 0; col < width; col++){
            if(type==PNMtype::PPM){
                this->map[row][col].resize(3);
            }else{
                this->map[row][col].resize(1);
            }
        }
    }
}

PNM::~PNM(){

}

PNMtype PNM::getType(){
    return this->type;
}

int PNM::getWidth(){
    return this->width;
}

int PNM::getHeight(){
    return this->height;
}

int PNM::getRange(){
    return this->range;
}

std::string PNM::getMagicNumber(){
    switch(this->type){
    case PNMtype::PPM: return "P6"; break;
    case PNMtype::PGM: return "P5"; break;
    case PNMtype::PBM: return "P4"; break;
    }
    return "";
}

int PNM::getPixelValueR(int row, int col){
    if(row >= this->height or col >= this->width){
        std::cout << "ERROR! : Requested Pixel out of bounds." <<std::endl;
        return 0;
    }
    return this->map[row][col][0];
}

int PNM::getPixelValueG(int row, int col){
    if(row >= this->height or col >= this->width){
        std::cout << "ERROR! : Requested Pixel out of bounds." <<std::endl;
        return 0;
    }
    return this->map[row][col][1];
}

int PNM::getPixelValueB(int row, int col){
    if(row >= this->height or col >= this->width){
        std::cout << "ERROR! : Requested Pixel out of bounds." <<std::endl;
        return 0;
    }
    return this->map[row][col][2];
}

int PNM::getPixelValueGRAY(int row, int col){
    if(row >= this->height or col >= this->width){
        std::cout << "ERROR! : Requested Pixel out of bounds." <<std::endl;
        return 0;
    }
    return this->map[row][col][0];
}

bool PNM::getPixelValueBINARY(int row, int col){
    if(row >= this->height or col >= this->width){
        std::cout << "ERROR! : Requested Pixel out of bounds." <<std::endl;
        return 0;
    }
    if(this->map[row][col][0] ==0){
        return false;
    }
    else{ 
        return true;
    }
}

void PNM::setType(PNMtype newType){
    this->type = newType;
    for(int row=0; row<this->height; row++){
        for(int col = 0; col < this->width; col++){
            if(newType==PNMtype::PPM){
                this->map[row][col].resize(3);
            }else{
                this->map[row][col].resize(1);
            }
        }
    }
}

void PNM::setWidth(int newWidth){
    this->width = newWidth;
    for(int row=0; row<this->height; row++){
        this->map[row].resize(newWidth);
    }
}
void PNM::setHeight(int newHeight){
    this->height = newHeight;
    this->map.resize(newHeight);
}

void PNM::setRange(int newRange){
    this->range = newRange;
}

void PNM::setPixelValueR(int row, int col, int newR){
    if(this->type == PNMtype::PPM){
        this->map[row][col][0] = newR;
    }else{
        std::cout<< "ERROR! : Incompatible PNM Type -> setPixelValueR requires PPM" << std::endl;
    }
}
void PNM::setPixelValueG(int row, int col, int newG){
    if(this->type == PNMtype::PPM){
        this->map[row][col][1] = newG;
    }else{
        std::cout<< "ERROR! : Incompatible PNM Type -> setPixelValueG requires PPM" << std::endl;
    }
}
void PNM::setPixelValueB(int row, int col, int newB){
    if(this->type == PNMtype::PPM){
        this->map[row][col][2] = newB;
    }else{
        std::cout<< "ERROR! : Incompatible PNM Type -> setPixelValueB requires PPM" << std::endl;
    }
}

void PNM::setPixelValueRGB(int row, int col, int newR, int newG, int newB){
    if(this->type == PNMtype::PPM){
        this->map[row][col][0] = newR;
        this->map[row][col][1] = newG;
        this->map[row][col][2] = newB;
    }else{
        std::cout<< "ERROR! : Incompatible PNM Type -> setPixelValueRGB requires PPM" << std::endl;
    }
}
    
void PNM::setPixelValueGRAY(int row, int col, int newGray){
    if(this->type == PNMtype::PGM){
        this->map[row][col][0] = newGray;
    }else{
        std::cout<< "ERROR! : Incompatible PNM Type -> setPixelValueGRAY requires PGM" << std::endl;
    }
}

void PNM::setPixelValueBINARY(int row, int col,bool newBit){
    if(this->type == PNMtype::PBM){
        if(newBit){
            this->map[row][col][0] = 1;
        }else{
            this->map[row][col][0] = 0;
        }
    }else{
        std::cout<< "ERROR! : Incompatible PNM Type -> setPixelValueBINARY requires PBM" << std::endl;
    }
}

void PNM::pnmtopng(std::string sourceFile, std::string targetFile)
{
    std::string command = "netpbm_bin\\.\\pnmtopng " + sourceFile + ">" + targetFile;
    system(command.c_str());
}

void PNM::pngtopnm(std::string sourceFile, std::string targetFile)
{
    std::string command = "netpbm_bin\\.\\pngtopnm " + sourceFile + ">" + targetFile;
    system(command.c_str());
}

//sourceFile with extention
int PNM::read(std::string sourceFile){
    std::string pnmMagicNumberBuffer = "", widthBuffer="", heightBuffer="", rangeBuffer="";
    
    std::fstream file;
    file.open(sourceFile, std::fstream::in | std::fstream::binary);
    file >> pnmMagicNumberBuffer;
    file >> widthBuffer;
    file >> heightBuffer;
    if(pnmMagicNumberBuffer == "P4"){
        this->setType(PNMtype::PBM);
    }
    else if (pnmMagicNumberBuffer == "P5"){
        this->setType(PNMtype::PGM);
        file >> rangeBuffer;
    }
    else if (pnmMagicNumberBuffer == "P6"){
        file >> rangeBuffer;
        this->setHeight(std::stoi(heightBuffer));
        this->setWidth(std::stoi(widthBuffer));
        this->setType(PNMtype::PPM);
        this->setRange(std::stoi(rangeBuffer));
        unsigned char R, G, B;
        file >> std::noskipws;
        for(int row=0; row<this->height; row++){
            for(int col = 0; col<this->width; col++){
                file >> R;
                file >> G;
                file >> B;
                // new line char (10) leads to issues in Windows as it is replaced by \n\r (2 chars long)
                //  instead of just \n while saving to a file. This is the workaround I have found.
                if((int)R == 10){
                    R = 11;
                }
                if((int)G == 10){
                    G = 11;
                }
                if((int)B == 10){
                    B = 11;
                }
                this->setPixelValueRGB(row,col,int(R),int(G),int(B));
            }
        }
    }
    file.close();
    if(file.fail()){return 1;}
    return 0;
}

//targetFile without extention
int PNM::save(std::string targetFile){
    std::ofstream file;
    std::string output;
    std::string buffer;
    switch(this->type){

        case PNMtype::PPM:
            file.open(targetFile + ".ppm", std::ios::out);
            output = this->getMagicNumber() + ' ' + std::to_string(this->width) + ' ' + std::to_string(this->height)+ ' ' + std::to_string(this->range);
            int R,G,B;
            for(int y = 0; y < this->height; y++){
                for(int x = 0; x < this->width; x++){
                    R = this->getPixelValueR(y,x);
                    G = this->getPixelValueG(y,x);
                    B = this->getPixelValueB(y,x);
                    // new line char (10) leads to issues in Windows as it is replaced by \n\r (2 chars long)
                    //  instead of just \n while saving to a file. This is the workaround I have found.
                    if(R == 10){
                        R = 11; 
                        std::cout<< "Saved R char 10 on " << x << " - " << y << std::endl;
                    }
                    if(G == 10){
                        G = 11;
                        std::cout<< "Saved G char 10 on " << x << " - " << y << std::endl;
                    }
                    if(B == 10){
                        B = 11;
                        std::cout<< "Saved B char 10 on " << x << " - " << y << std::endl;
                    }
                    buffer += uint8_t(R);
                    buffer += uint8_t(G);
                    buffer += uint8_t(B);
                }   
            }
            file << output << buffer << std::endl;
            break;

        case PNMtype::PGM:
            file.open(targetFile +".pgm", std::ios::out);
            file << this->getMagicNumber();
            file << ' ';
            file << std::to_string(this->width) << ' ' << std::to_string(this->height);
            file << ' ';
            file << std::to_string(this->range);
            file << ' ';
            for(int y = 0; y < this->height; y++){
                for(int x = 0; x < this->width; x++){
                    file << uint8_t(this->getPixelValueGRAY(y,x));
                }   
            }
            break;

        case PNMtype::PBM:
            file.open(targetFile + ".pbm", std::ios::out);
            file << this->getMagicNumber();
            file << ' ';
            file << std::to_string(this->width) << ' ' << std::to_string(this->height);
            file << ' ';
            std::bitset<8> bitset ("00000000");
            int bitsetCursor=0;
            for(int y = 0; y < this->height; y++){
                for(int x = 0; x < this->width; x++){
                    if(this->getPixelValueBINARY(y,x)){
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
            break;
    }
    file.close();
    if(file.fail()){return 1;}
    return 0;
}

std::ostream& operator<<(std::ostream& os, PNM& pnm){
    os <<std::endl << pnm.getMagicNumber() << std::endl;
    os << pnm.height << " " << pnm.width;
    if(pnm.type!=PNMtype::PBM){
        os << " " << pnm.range;
    }
    os << std::endl;
    for(int y=0; y < pnm.height; y++){
        for (int x = 0; x< pnm.width; x++){
            if(pnm.type==PNMtype::PPM){
                os << " | " << pnm.getPixelValueR(y,x) << " - " << pnm.getPixelValueG(y,x) << " - " << pnm.getPixelValueB(y,x);
            }else if(pnm.type==PNMtype::PGM){

                os << " | " << pnm.getPixelValueGRAY(y,x);
            }else if(pnm.type==PNMtype::PBM){

                os << " | " << pnm.getPixelValueBINARY(y,x);
            }
        }
        os << " |" << std::endl;
    }
    return os;
}