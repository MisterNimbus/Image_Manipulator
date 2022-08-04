#ifndef PIXEL_H
#define PIXEL_H
#include <ostream>
#include <fstream>
#include <string>

class pixel {
private:
public:
    pixel(int val1 = 0, int val2 =0, int val3=0);
    ~pixel();
    std::uint8_t formatRGB(); 
    std::uint8_t formatGRAY(); 
    std::uint8_t formatBINARY(); 
    std::string outputRGB();
    std::string outputGRAY();
    std::string outputBINARY();
    void setRGB(int R, int G, int B);
    void setR(int R);
    void setG(int G);
    void setB(int B);
    void setGRAY(int gray);
    void setBINARY(bool bit);
    int getR();
    int getG();
    int getB();
    int getGRAY();
    bool getBit();
protected:
    int values[3] = {0,0,0};
};
#endif