#include "pixel.h"

///////////////////////////////////////////////////////////////////////////

pixel::pixel(int val1, int val2, int val3){
    values[0] = val1;
    values[1] = val2;
    values[2] = val3;
}

pixel::~pixel(){

}

///////////////////////////////////////////////////////////////////////////

std::uint8_t pixel::formatRGB(){
    return std::uint8_t(this->values[0]) + std::uint8_t(this->values[1]) + std::uint8_t(this->values[2]);
}

std::string pixel::outputRGB() {
    std::string result;
    result = std::to_string(this->values[0]) + " " + std::to_string(this->values[1]) + " " + std::to_string(this->values[2]);
    return result;
}

void pixel::setRGB(int R, int G, int B){
    values[0] = R;
    values[1] = G;
    values[2] = B;
}

void pixel::setR(int R){
    values[0] = R;
}

void pixel::setG(int G){
    values[1] = G;
}

void pixel::setB(int B){
    values[2] = B;
}

int pixel::getR(){
    return values[0];
}

int pixel::getG(){
    return values[1];
}

int pixel::getB(){
    return values[2];
}

///////////////////////////////////////////////////////////////////////////


std::uint8_t pixel::formatGRAY(){
    return std::uint8_t(this->values[0]);
}

std::string pixel::outputGRAY() {
    std::string result;
    result = std::to_string(this->values[0]);
    return result;
}

void pixel::setGRAY(int gray){
    values[0] = gray;
}

int pixel::getGRAY(){
    return values[0];
}

///////////////////////////////////////////////////////////////////////////

std::uint8_t pixel::formatBINARY(){
    return std::uint8_t(this->values[0]);
}

std::string pixel::outputBINARY() {
    std::string result;
    result = std::to_string(this->values[0]);
    return result;
}

void pixel::setBINARY(bool bit){
    if(bit==false){
        values[0]=0;
    }
    else
    {
        values[0]=1;
    }
}

bool pixel::getBit(){
    if(values[0]==0){
        return false;
    }
    else
    {
        return true;
    }
}