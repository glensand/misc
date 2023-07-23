#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Arguments count is shitty" << std::endl;
        return -1;

    }

    constexpr std::size_t assumed_size{ 10000000 };
    std::vector<std::string> files_by_order;
    files_by_order.reserve(assumed_size);
    std::unordered_map<std::string, bool> file_to_index;
    file_to_index.reserve(assumed_size);

    for (std::size_t i{ 0 }; i < (std::size_t)argc; ++i) 
    {
        std::ifstream in(argv[i]);

        for (std::string line; std::getline(in, line); ) 
        {
            std::string token = line.substr(0, line.find(' '));

            auto&& result = file_to_index.try_emplace(token, true);

            if (result.second) 
            {
                files_by_order.emplace_back(std::move(line));
            }
        }
    }

    std::ofstream output("GameOpenOrder.log");

    for (auto&& file : files_by_order)
        output << file << '\n';

    output.close();
}
