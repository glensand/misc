#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> extract_lines_with_token(std::istream& input, const std::string& token);

int main(int argc, char *argv[]) {
	if(argc < 2){
		std::cout << "To few argumens were given, please use these comand: parser.exe filename" << std::endl;
		return -1;
	}

	const auto* const file_name = argv[1];
	std::ifstream input(file_name);
	if(!input.is_open()){
		std::cout << "The file with given name: [" << file_name << "] could not be openned" << std::endl;
		return -1;
	}

	const std::string token = argc == 3 ? argv[2] : "Warning";
	
	auto&& lines = extract_lines_with_token(input, token);
	input.close();

	std::ofstream output(file_name + token);
	for(auto&& line : lines)
		output << line << std::endl;
	output.close();

	return 0;
}

std::vector<std::string> extract_lines_with_token(std::istream& input, const std::string& token){
	std::vector<std::string> lines;
	for (std::string line; std::getline(input, line); ){
		if(line.find(token) != std::string::npos){
			lines.emplace_back(std::move(line));
		}
	}
	return lines;
}