#include <Engine.h>

#include <Core/Module.h>

#include <dlfcn.h>
#include <iostream>

Module::Module(const std::string& path) {
	std::cout << "Loading module '" << path << "'" << std::endl;

	handle = dlopen(path.c_str(), RTLD_LAZY);
	
	if (!handle)
		throw RuntimeException(dlerror());
	dlerror();
	
	on_load = LoadSym<OnLoadFuncPtr>("OnLoad");
	on_update = LoadSym<OnUpdateFuncPtr>("OnUpdate");
	on_unload = LoadSym<OnUnloadFuncPtr>("OnUnload");
	
	on_load(Engine::Get());
}

Module::~Module() {
	on_unload();
	dlclose(handle);
}

void* Module::LoadSym(const std::string& sym) {
	void* addr = dlsym(handle, sym.c_str());
	
	const char* error;
	if ((error = dlerror()) != NULL)
		throw RuntimeException(error);
	
	return addr;
}
