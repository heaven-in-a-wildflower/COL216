#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file1("aneeket.txt");
    std::ifstream file2("output.txt");
    std::ofstream diffFile("diff.txt");

    if (!file1.is_open() || !file2.is_open() || !diffFile.is_open()) {
        std::cerr << "Unable to open one or more files." << std::endl;
        return 1;
    }

    std::string line1, line2;
    int lineNum = 1;
    bool areEqual = true;

    while (std::getline(file1, line1) && std::getline(file2, line2)) {
        if (line1 != line2) {
            diffFile << "Difference at line " << lineNum << ":" << std::endl;
            diffFile << "File 1: " << line1 << std::endl;
            diffFile << "File 2: " << line2 << std::endl;
            areEqual = false;
        }
        lineNum++;
    }

    if (areEqual) {
        diffFile << "Files are identical." << std::endl;
    }

    file1.close();
    file2.close();
    diffFile.close();

    std::cout << "Differences written to diff.txt." << std::endl;

    return 0;
}
