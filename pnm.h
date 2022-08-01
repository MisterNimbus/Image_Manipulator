#ifndef PNM_H
#define PNM_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include "./pixel.h"
#include <memory>
#include <bitset>

class pnm
{
public:
    pnm();
    virtual ~pnm();
    virtual std::string getMagicNumber() = 0;
    int save(std::string targetFolder);
    static std::unique_ptr<pnm> read(std::string * sourceFolder);
    virtual int format() = 0;
    virtual std::string print() = 0;
private:
};

class pbm : public pnm{
public:
    pbm(int width, int height);
    ~pbm();
    int format() override;
    std::string getMagicNumber() override;
    void pushToRow(int targetRow, bool value);
    friend std::ostream& operator<<(std::ostream& os, pbm& pbm);
    int save(std::string* fileName);
    std::string print() override;
private:
    int width, height;
    std::vector<std::vector<std::unique_ptr<BINARYpixel>>> map = {};
};

class pgm : public pnm{
public:
    pgm(int width, int height, int range);
    ~pgm();
    int format() override;
    std::string print();
    friend std::ostream& operator<<(std::ostream& os, pgm& pgm);
    int save(std::string* fileName);
    std::string getMagicNumber() override;
    void pushToRow(int targetRow, int grayValue);
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr<GRAYpixel>>> map;
};

class ppm : public pnm{
public:
    ppm(int width, int height, int range);
    ~ppm();
    int format() override;
    std::string print();
    friend std::ostream& operator<<(std::ostream& os, ppm& ppm);
    int save(std::string* fileName);
    std::string getMagicNumber() override;
    void pushToRow(int targetRow,int valueR, int valueG, int valueB);
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr< RGBpixel>>> map;
};

#endif