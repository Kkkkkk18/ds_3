#include <iostream>
#include <chrono>
#include <thread>

volatile char* variable = nullptr;


void read(long step) {
    for (long i = 0; i < step; ++i) {
        volatile char value = variable[i * 4 * 1024];
        if (i % 1000 == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

void write(long step) {
    for (long i = 0; i < step; ++i) {
        variable[i * 4 * 1024] = '$';
        if (i % 1000 == 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

int main(int argc, char const* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage" << argv[0] <<"[read(r) / write(w)]" << std::endl;
        return 1;
    }

    variable = new (std::nothrow) volatile char[3ULL * 1024 * 1024 * 1024];


    const long step = (3ULL * 1024 * 1024 * 1024) / 4 * 1024;

    if (std::strcmp(argv[1], "r") == 0) {
        read(step);

    }
    else  if (std::strcmp(argv[1], "w") == 0) {
        write(step);
    }

    delete[] variable;
    return 0;

}
