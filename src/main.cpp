#include "app.h"

int main() {
    App app("OpenGLearn", 800, 600);
    while (app.update()) {}
    app.shutdown();
    return 0;
}
