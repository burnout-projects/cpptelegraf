#include <string>
#include <sstream>

std::string format_string(std::string key) {
    size_t pos = 0;
    while ((pos = key.find(',', pos)) != std::string::npos) {
        key.replace(pos, 1, "\\,");
        pos += 2;
    }
    pos = 0;
    while ((pos = key.find(' ', pos)) != std::string::npos) {
        key.replace(pos, 1, "\\ ");
        pos += 2;
    }
    pos = 0;
    while ((pos = key.find('=', pos)) != std::string::npos) {
        key.replace(pos, 1, "\\=");
        pos += 2;
    }
    return key;
}

std::string format_value(const std::string& value) {
    std::stringstream ss;
    if (value.empty()) {
        return "\"\"";
    }
    if (value[0] == '"') {
        ss << "\"" << value.substr(1, value.size() - 2) << "\"";
    } else if (value == "true" || value == "false") {
        ss << value;
    } else {
        try {
            std::stod(value);
            ss << value;
        } catch (const std::invalid_argument& ia) {
            ss << "\"" << value << "\"";
        }
    }
    return ss.str();
}