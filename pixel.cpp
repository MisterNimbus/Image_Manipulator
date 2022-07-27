#include "pixel.h"

///////////////////////////////////////////////////////////////////////////

pixel::pixel(){

}

pixel::~pixel(){

}

///////////////////////////////////////////////////////////////////////////

RGBpixel::RGBpixel(int R, int G, int B):pixel(), R( R ), G( G ), B( B ){
}

RGBpixel::~RGBpixel(){
}

int RGBpixel::getR(){
    return this->R;
    }

int RGBpixel::getG(){
    return this->G;
    }

int RGBpixel::getB(){
    return this->B;
    }

void RGBpixel::setR(int newR){
    this->R = newR;
    }

void RGBpixel::setG(int newG){
    this->G = newG;
    }

void RGBpixel::setB(int newB){
    this->B = newB;
    }

std::uint8_t RGBpixel::format(){
    return std::uint8_t(this->getR()) + std::uint8_t(this->getG()) + std::uint8_t(this->getB());
}

///////////////////////////////////////////////////////////////////////////

GRAYpixel::GRAYpixel(int gray):pixel(), gray( gray )
    {
    }

GRAYpixel::~GRAYpixel()
    {
    }

int GRAYpixel::getGray(){
    return this->gray;
    }

void GRAYpixel::setGray(int newGray){
    this->gray = newGray;
    }

std::uint8_t GRAYpixel::format(){
    return std::uint8_t(this->getGray());
}

///////////////////////////////////////////////////////////////////////////

BINARYpixel::BINARYpixel(bool bit):pixel(), bit( bit )
    {
    }

BINARYpixel::~BINARYpixel()
    {
    }

int BINARYpixel::getBit(){
    return this->bit;
    }

void BINARYpixel::setBit(bool newBit){
    this->bit = newBit;
    }

std::uint8_t BINARYpixel::format(){
    return std::uint8_t(this->getBit());
}