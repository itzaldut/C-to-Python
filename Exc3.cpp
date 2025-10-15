#include <cstddef>

extern "C" {
    size_t count3d_cpp(size_t n) {
        size_t count = 0;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                for (size_t k = j + 1; k < n; ++k) {
                    ++count;
                }
            }
        }
        return count;
    }
}

