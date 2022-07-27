#ifndef PNM_H
#define PNM_H

#include <vector>
#include <stdio.h>
#include <ostream>
#include "pixel.h"
#include <memory>

class pnm
{
public:
    enum pnmType{ pbm, pgm, ppm };
    pnm(enum pnm::pnmType type);
    ~pnm();
    virtual int getMagicNumber() = 0;
    int save(std::string targetFolder);
    static std::unique_ptr<pnm> read(std::string sourceFolder);
    virtual int format() = 0;
    virtual void pushToRow(int targetRowNumber, std::unique_ptr<BINARYpixel> pixel) =0;
    virtual void pushToRow(int targetRowNumber, std::unique_ptr<GRAYpixel> pixel) =0;
    virtual void pushToRow(int targetRowNumber, std::unique_ptr<RGBpixel> pixel) =0;
private:
    pnmType pnmType;
};

class pbm : pnm{
public:
    pbm(int width, int height);
    ~pbm();
    int getMagicNumber() override;
    void pushToRow(int targetRowNumber, std::unique_ptr<BINARYpixel> pixel) override;
private:
    int width, height;
    std::vector< std::vector< std::unique_ptr<BINARYpixel>>> map;
};

class pgm : pnm{
public:
    pgm(int width, int height, int range);
    ~pgm();
    int getMagicNumber() override;
    void pushToRow(int targetRowNumber, std::unique_ptr<GRAYpixel> pixel) override;
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr<GRAYpixel>>> map;
};

class ppm : pnm{
public:
    ppm(int width, int height, int range);
    ~ppm();
    int getMagicNumber() override;
    void pushToRow(int targetRowNumber, std::unique_ptr<RGBpixel> pixel) override;
private:
    int width, height, range;
    std::vector< std::vector< std::unique_ptr< RGBpixel>>> map;
};

#endif