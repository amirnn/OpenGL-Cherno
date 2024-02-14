#include "opengl-cherno.h"
#include <vector>
#include <string>

int main() {
    opengl_cherno();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    opengl_cherno_print_vector(vec);
}
