#include "app.hpp"

int main() {
    App app(1280, 720);
    // App app(640, 480);
    while (app.update()) {}
    app.shutdown();
    return 0;
}
