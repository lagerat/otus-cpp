#include <iostream>
#include "async.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Expected argument when launching program" << std::endl;
        return EXIT_FAILURE;
    }

    const size_t size = std::stoi(argv[1]);

    auto h = async::connect(size);

    async::receive(h, "1");
    async::receive(h, "\n{\n2\n3\n}\n4\n5\n6\n{\na\n");
    async::receive(h, "b\nc\nd\n}\n89\n");

    async::disconnect(h);

}