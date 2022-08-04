#ifndef PNM_H
#define PNM_H

#include <vector>
#include <stdio.h>
#include <iostream>
#include "./pixel.h"
#include <memory>
#include <bitset>

class pbm;
class pgm;
class ppm;

class pnm
{
public:
    pnm(int width, int height, int range);
    virtual ~pnm();
    static pnm * read(std::string * sourceFolder);
    
    virtual std::string getMagicNumber() = 0;
    virtual std::string print() = 0;
    virtual int save(std::string* fileName) = 0;
    virtual void pushToRow(int TargetRow, int val1, int val2 = 0, int val3 = 0) = 0;

    friend std::ostream& operator<<(std::ostream& os, ppm& ppm);
    friend std::ostream& operator<<(std::ostream& os, pgm& pgm);
    friend std::ostream& operator<<(std::ostream& os, pbm& pbm);


protected:
    int width, height, range;
    std::vector<std::vector<std::unique_ptr<pixel>>> map = {};
};

class pbm : public pnm{
public:
    pbm(int width, int height);
    ~pbm();
    std::string getMagicNumber() override;
    int save(std::string* fileName) override;
    std::string print() override;
    void pushToRow(int targetRow, int val1, int val2 = 0, int val3 = 0) override;

    friend std::ostream& operator<<(std::ostream& os, pbm& pbm);
private:
};

class pgm : public pnm{
public:
    pgm(int width, int height, int range);
    ~pgm();
    std::string getMagicNumber() override;
    int save(std::string* fileName) override;
    std::string print() override;
    void pushToRow(int targetRow, int val1, int val2 = 0, int val3 = 0) override;

    friend std::ostream& operator<<(std::ostream& os, pgm& pgm);
private:
};

class ppm : public pnm{
public:
    ppm(int width, int height, int range);
    ~ppm();
    std::string getMagicNumber() override;
    int save(std::string* fileName) override;
    std::string print() override;
    void pushToRow(int targetRow, int val1, int val2 = 0, int val3 = 0) override;

    friend std::ostream& operator<<(std::ostream& os, ppm& ppm);
private:
};

#endif