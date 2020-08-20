#include <Engine.h>

int main(int, char**) {
	Engine::Create().Run();
	Engine::Destroy();
	return 0;
}
