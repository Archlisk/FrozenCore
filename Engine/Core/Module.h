#pragma once

class Engine;

typedef void(*OnLoadFuncPtr)(Engine&);
typedef void(*OnUpdateFuncPtr)(double);
typedef void(*OnUnloadFuncPtr)();

class Module {
public:
	Module(const std::string& path);
	
	~Module();
	
	inline void Update(double delta) {
		on_update(delta);
	}

private:
	template<typename T>
	inline T LoadSym(const std::string& sym) {
		return (T)LoadSym(sym);
	}
	
	void* LoadSym(const std::string& sym);

	void* handle;

	OnLoadFuncPtr on_load;
	OnUpdateFuncPtr on_update;
	OnUnloadFuncPtr on_unload;
};
