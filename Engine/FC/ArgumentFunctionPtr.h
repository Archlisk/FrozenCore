#pragma once

class BaseCallablePtr {
public:
	virtual void Call() {}
};

template<typename T, typename... Targs>
class ArgumentFunctionPtr : public BaseCallablePtr {
public:
	ArgumentFunctionPtr(T func, Targs... args)
		: m_func(func), m_args(args...) {}
	
	void Call() override {
		std::apply(m_func, m_args);
	}
	
private:
	std::tuple<Targs...> m_args;
	T m_func;
};



template<typename Tc, typename Tf, typename... Targs>
class ArgumentMethodPtr : public BaseCallablePtr {
public:
	ArgumentMethodPtr(Tc obj, Tf func, Targs... args)
		: m_obj(obj), m_func(func), m_args(args...) {}
	
	void Call() override {
		std::apply(m_func, std::tuple_cat(std::make_tuple(m_obj), m_args));
	}
	
private:
	Tc m_obj;
	Tf m_func;
	std::tuple<Targs...> m_args;
};

