#ifndef PNM_H
#define PNM_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <bitset>

enum PNMtype{PPM, PGM, PBM};

class PNM{
public:
    PNM(int width = 0, int height = 0, PNMtype type = PNMtype::PPM, int range = 1);
    ~PNM();

    PNMtype getType();
    int getWidth();
    int getHeight();
    int getRange();
    std::string getMagicNumber();

    int getPixelValueR(int row, int col);
    int getPixelValueG(int row, int col);
    int getPixelValueB(int row, int col);
    int getPixelValueGRAY(int row, int col);
    bool getPixelValueBINARY(int row, int col);

    void setType(PNMtype newType);
    void setWidth(int newWidth);
    void setHeight(int newHeight);
    void setRange(int newRange);

    void setPixelValueR(int row, int col, int newR);
    void setPixelValueG(int row, int col, int newG);
    void setPixelValueB(int row, int col, int newB);
    void setPixelValueRGB(int row, int col, int newR, int newG, int newB);
    
    void setPixelValueGRAY(int row, int col, int newGray);
    void setPixelValueBINARY(int row, int col, bool newBit);

    static void pnmtopng(std::string sourceFile, std::string targetFile);
    static void pngtopnm(std::string sourceFile, std::string targetFile);
    int read(std::string sourceFile); //sourceFile with extention
    int save(std::string targetFile); //targetFile without extention
    friend std::ostream& operator<<(std::ostream& os, PNM& PNM);

private:
    int width;
    int height;
    PNMtype type;
    int range;
    std::vector<std::vector<std::vector<int>>> map;
};

#endif