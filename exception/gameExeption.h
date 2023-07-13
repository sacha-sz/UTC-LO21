#ifndef SRC_GAMEEXEPTION_H
#define SRC_GAMEEXEPTION_H

#include <exception>

class gameException: public std::exception {
    public:
        explicit gameException(std::string const& i):info(i){}

        [[nodiscard]] const char* what() const noexcept override
        {
            return info.c_str();
        }

    private:
        std::string info;
};

#endif //SRC_GAMEEXEPTION_H
