#include "app.hpp"

int main() {
    App app(1280, 720);
    while (app.update()) {}
    app.shutdown();
    return 0;
}
