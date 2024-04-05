
#include "finPch.h"
#include "application.h"

int main(void) {
	auto app = std::make_unique<Application>("OPENGL renderer");
	app->loop();

	return 0;
}