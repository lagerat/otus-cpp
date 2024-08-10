#include "src/FileScanner.h"
#include "src/DuplicatesFinder.h"

int main(int argc, const char *argv[])
{
    try
    {
        bool isRecursive = false;

        po::options_description opt_desc("Allowed options");
        opt_desc.add_options()
                ("help",                                                                           "Print this message")
                ("block",       po::value<std::size_t>()->required()->default_value(5),      "Block size (in kylobytes) used to compare files (at least 1)")
                ("hash",        po::value<std::string>()->required()->default_value("crc32"),"Hash algorithm used to compare byte blocks, one of 'crc32', 'crc16'")
                ("minSize",     po::value<std::size_t>()->required()->default_value(1),      "Minimum file size to compare")
                ("dirToScan",   po::value<std::vector<std::string>>()->required()->multitoken(),"Directories to search duplicates into")
                ("dirToExclude",po::value<std::vector<std::string>>()->multitoken(),            "Direcroties to exclude from search")
                ("Masks",       po::value<std::vector<std::string>>()->multitoken(),            "Include only files corresponding to these Masks in search")
                ("recursive",   po::bool_switch(&isRecursive),                               "Use this option to enable recursive subdirectory scanning");

        po::variables_map var_map;
        try
        {
            auto parsed = po::command_line_parser(argc, argv)
                    .options(opt_desc)
                    .run();
            po::store(parsed, var_map);
            if (var_map.count("help") != 0)
            {
                std::cout << opt_desc << "\n";
                return 0;
            }
            po::notify(var_map);
        }
        catch (const po::error& err)
        {
            std::cerr << "Error while parsing command-line arguments: "
                      << err.what() << "\nPlease use --help to see help message\n";
            return 1;
        }
        DuplicatesFinder finder(var_map);
        finder.Run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}