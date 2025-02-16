#include "except.hpp"

#include <exception>
#include <iostream>

int app::except::React() {
    try {
        throw;
    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown error" << '\n';
    }
    return 1;
}
