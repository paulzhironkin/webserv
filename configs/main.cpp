#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Функция разделяет строку по символу '/' и возвращает вектор частей
std::vector<std::string> splitPath(const std::string& path) {
    std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string part;

    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }

    return parts;
}

// Функция сравнивает адресную строку с шаблоном
bool pathMatch(const std::string& requestPath, const std::string& pattern) {
    std::vector<std::string> requestParts = splitPath(requestPath);
    std::vector<std::string> patternParts = splitPath(pattern);

    size_t minSize = std::min(requestParts.size(), patternParts.size());

    for (size_t i = 0; i < minSize; ++i) {
        if (requestParts[i] != patternParts[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    std::string requestPath = "/test/123";
    std::string pattern = "/test/a";

    if (pathMatch(requestPath, pattern)) {
        std::cout << "Совпадение найдено!" << std::endl;
    } else {
        std::cout << "Совпадение не найдено!" << std::endl;
    }

    return 0;
}
