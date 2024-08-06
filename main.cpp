#include <iostream>
#include "src/Bulk.h"
#include "src/LogWriter.h"
#include "src/FileWriter.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Expected argument when launching program" << std::endl;
        return EXIT_FAILURE;
    }

    const size_t size = std::stoi(argv[1]);

    Bulk bulk{size};

    LogWriter logWriter;
    FileWriter fileWriter;

    bulk.subscribe(&logWriter);
    bulk.subscribe(&fileWriter);

    bulk.run();
}