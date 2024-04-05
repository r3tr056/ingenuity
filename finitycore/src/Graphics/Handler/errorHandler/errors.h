
#ifndef FINITY_GUI_ERRORS_H
#define FINITY_GUI_ERRORS_H

#include <string>

class ErrorHandler {
private:
    std::string message;
    std::string targetFile;
    std::string targetInstance;
    std::string affectedInstance;

    enum class ErrorType {
        NONE = 0,
    };
};

#endif //FINITY_GUI_ERRORS_H
