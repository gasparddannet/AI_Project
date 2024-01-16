#include "TXTWrite.h"

TXTWrite::TXTWrite(const std::string& f) : filename(f) {}

void TXTWrite::write(const std::vector<std::tuple<int, double>>& vectToWrite) {
    std::ofstream outputFile("../dataSolution/" + filename);
    for (const auto& tuple : vectToWrite) {
        outputFile << std::get<0>(tuple) << ' ' << std::get<1>(tuple) << '\n';
    }
    outputFile.close();
}

void TXTWrite::write(const std::vector<std::tuple<int, int, int, int, int, int, int>>& vectToWrite) {
    std::ofstream outputFile("../dataSolution/" + filename);
    for (const auto& tuple : vectToWrite) {
        outputFile << std::get<0>(tuple) << ' ' << std::get<1>(tuple) << ' ' << std::get<2>(tuple) << ' ' << 
        std::get<3>(tuple) << ' ' << std::get<4>(tuple) << ' ' << std::get<5>(tuple)<< ' ' << std::get<6>(tuple) << '\n';
    }
    outputFile.close();
}

void TXTWrite::write(const std::vector<double>& vectToWrite) {
    std::ofstream outputFile("../dataSolution/" + filename);
    for (const auto& d : vectToWrite) {
        outputFile << d << '\n';
    }
    outputFile.close();
}

void TXTWrite::write(const std::vector<std::tuple<int,int, int, int>>& vectToWrite, std::string titre) {
    std::ofstream outputFile("../dataSolution/" + filename);
    outputFile << titre << "\n";
    for (const auto& tuple : vectToWrite) {
        outputFile << std::get<0>(tuple) << ' ' << std::get<1>(tuple) << ' ' << std::get<2>(tuple) << ' ' << std::get<3>(tuple) << '\n';
    }
    outputFile.close();
}

void TXTWrite::setFilename(const std::string& f) {
    filename = f;
}
