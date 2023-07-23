#ifndef SRC_GAMEEXEPTION_H
#define SRC_GAMEEXEPTION_H

#include <exception>
#include <utility>

class gameException: public std::exception {
    public:
        explicit gameException(std::string  i):info(std::move(i)){}

        [[nodiscard]] const char* what() const noexcept override
        {
            return info.c_str();
        }

    private:
        std::string info;
};

#endif //SRC_GAMEEXEPTION_H
