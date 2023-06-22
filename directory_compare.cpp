#include <filesystem>
#include <iostream>
#include <thread>
#include <unordered_set>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

template<typename TContainer, typename TEmplacer>
void traverse(const std::string& path, TContainer& out_paths, TEmplacer&& e) {
    for (const auto& entry : recursive_directory_iterator(path)) {
        if (!entry.is_directory()) {
            e(out_paths, entry.path().filename().c_str()); // filename should be enough i think
        }
    }
}


std::vector<std::wstring> paths1;
std::unordered_set<std::wstring> paths2;

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "to few args, path1(new) path2(old) is required" << std::endl;
        return -1;
    }

    const std::string path1 = argv[1];
    const std::string path2 = argv[2];

    std::thread traverse_t([path1] {
        traverse(path1, paths1, [](auto&& container, auto&& val) {container.emplace_back(val); });
    });

    traverse(path2, paths2, [](auto&& container, auto&& val) {container.emplace(val); });

    traverse_t.join();
    struct comparator final {
        std::thread t;
        std::vector<std::wstring> out;
        void run(std::size_t range_begin, std::size_t range_end)
        {
            t = std::thread([this, range_begin, range_end] {
                for (std::size_t i = range_begin; i < range_end; ++i) {
                    if (paths2.find(paths1[i]) == paths2.end())
                        out.emplace_back(paths1[i]);
                }
            });
        }
        comparator() = default;
    };

    const auto threads_count = std::thread::hardware_concurrency();
    const auto per_chunk = paths1.size() / threads_count;
    std::vector<comparator> comparators(threads_count);
    for (auto chunk = 0u; chunk < threads_count - 1; ++chunk)
        comparators[chunk].run(chunk * per_chunk, (chunk + 1) * per_chunk);

    comparators[threads_count - 1].run((threads_count - 1) * per_chunk, paths1.size());

    for (auto&& [t, _] : comparators)
        t.join();

    for (auto&& [_, out] : comparators)
        for (auto&& s : out)
            std::wcout << s << '\n';
}
