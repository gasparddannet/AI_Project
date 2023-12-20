#ifndef TXTWRITE_H
#define TXTWRITE_H

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

class TXTWrite {
private:
    std::string filename;

public:
    TXTWrite(const std::string& filename);
    void write(const std::vector<std::tuple<int, double>>& vectToWrite);
    void write(const std::vector<std::tuple<int, int, int, int, int>>& vectToWrite);
    void write(const std::vector<double>& vectToWrite) ;
    void setFilename(const std::string& f);
};

#endif
