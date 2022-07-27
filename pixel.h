#ifndef PIXEL_H
#define PIXEL_H
#include <ostream>
#include <fstream>
#include <string>

class pixel {
private:
public:
    pixel();
    ~pixel();
    virtual std::uint8_t format() = 0; 
};


class RGBpixel : pixel
{
private:
    int R;
    int G;
    int B;
public:
    RGBpixel(int R = 0, int G = 0, int B = 0);
    ~RGBpixel();
    int getR();
    int getG();
    int getB();
    void setR(int newR);
    void setG(int newG);
    void setB(int newB);
    std::uint8_t format() override;
};

class GRAYpixel : pixel
{
private:
    int gray;
public:
    GRAYpixel(int gray = 0);
    ~GRAYpixel();
    int getGray();
    void setGray(int newGray);
    std::uint8_t format() override;
};

class BINARYpixel  : pixel
{
private:
    bool bit;
public:
    BINARYpixel(bool bit = false);
    ~BINARYpixel();
    int getBit();
void setBit(bool newBit);
    std::uint8_t format() override;
};

#endif