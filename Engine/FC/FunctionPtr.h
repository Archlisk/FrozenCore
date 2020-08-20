#pragma once

template<typename Tc, typename Tf>
struct MethodPtr {
	
	MethodPtr(Tc& obj, Tf func)
		: obj(obj), func(func) {}
	
	template<typename... Targs>
	void Call(Targs... args) {
		(obj.*func)(args...);
	}
	
	template<typename... Targs>
	void operator () (Targs... args) {
		(obj.*func)(args...);
	}
	
	Tc& obj;
	Tf func;
};



template<typename T>
struct FunctionPtr {
	FunctionPtr() {}
	FunctionPtr(T* func)
		: func(func) {}
	
	template<typename... Targs>
	void Call(Targs... args) {
		func(args...);
	}
	
	template<typename... Targs>
	void operator () (Targs... args) {
		func(args...);
	}
	
	T* func;
};
