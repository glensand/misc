#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using string_set_t = std::unordered_set<std::string>;

auto load_textures(std::istream& input) {
	std::unordered_set<std::string> resulting_resources;

	bool found_first_line{ false };
	for (std::string line; std::getline(input, line); ) {
		if (found_first_line && line.find("Total size") != std::string::npos)
			break;
		if (!found_first_line) {
			if (line.find("all textures") != std::string::npos)
				found_first_line = true;
		} else {
			const auto first_delimiter_index = line.find('/');
			if (first_delimiter_index != std::string::npos) {
				const auto second_delimiter_index = line.find(',', first_delimiter_index);
				const auto count_assumed = second_delimiter_index - first_delimiter_index;
				const auto count = std::min(line.size() - first_delimiter_index, count_assumed);
				auto&& resource = line.substr(first_delimiter_index, count);
				resulting_resources.emplace(resource);
			}
		}
	}
	return resulting_resources;
}

void print_diff(const string_set_t& set_a, const string_set_t& set_b){
	std::ofstream out("diff");
    for(auto&& resource_a : set_a) {
        if (set_b.count(resource_a) == 0) {
			out << resource_a << std::endl;
        }
    }
	out.close();
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "You input sucks" << std::endl;
		return -1;
	}

	const std::string file_name_a = argv[1];

	std::ifstream file_a(file_name_a);
	if (!file_a.is_open()) {
		std::cout << "The file with given name: [" << file_name_a << "] could not be opened" << std::endl;
		return -1;
	}

	auto&& resource_a = load_textures(file_a);
	file_a.close();

	const std::string file_name_b = argv[2];

	std::ifstream file_b(file_name_b);
	if (!file_b.is_open()) {
		std::cout << "The file with given name: [" << file_name_b << "] could not be opened" << std::endl;
		return -1;
	}

	auto&& resource_b = load_textures(file_b);
	file_b.close();

	print_diff(resource_a, resource_b);
}
