#pragma once

#include <stddef.h>
#include <vector>
#include <stdexcept>
#include <functional>

template<typename T>
class Register;



template<typename T>
class Handle {
public:
	Handle(const Handle<T>& other)
		: m_id(other.m_id), m_register(other.m_register) {}

	Handle(Register<T>* reg, size_t id)
		: m_id(id), m_register(reg) {}

	void operator=(const Handle<T>& other) {
		m_id = other.m_id;
		m_register = other.m_register;
	}

	T* operator->() {
		return m_register->Find(m_id);
	}
	
	T* GetPtr() const {
		return m_register->Find(m_id);
	}

	u32 GetID() const { return m_id; }
	const Register<T>& GetRegister() const { return m_register; }

private:
	u32	m_id = 0;
	Register<T>* m_register = nullptr;
};



template<typename T>
class Register {
public:
	T* Find(size_t id) {
		if (id >= m_data.size())
			throw RuntimeException("Access to invalid id");
		
		if (!m_data[id])
			throw RuntimeException("Access to deleted id");
		
		return m_data[id];
	}
	
	template<typename Th>
	Handle<Th> Add(Th* val) {
		for (void* ptr : m_data) {	// TODO: I really need to make this check faster somehow
			if (!ptr) {
				m_data.emplace_back(val);
				return GetHandle<Th>(m_data.size() - 1);
			}
		}
	
		m_data.emplace_back(val);
		return GetHandle<Th>(m_data.size() - 1);
	}
	
	template<typename Th>
	Handle<Th> Insert(Th* val, int id) {
		if (id >= m_data.size())
			throw RuntimeException("Insert on invalid id");
			
		m_data[id] = val;
		return GetHandle(id);
	}
	
	void Delete(u32 id) {
		if (id >= m_data.size())
			throw RuntimeException("Delete on invalid id");
		
		m_data[id] = nullptr;
	}
	
	void ForEach(std::function<void(T*)> func) {
		for (u32 i = 0; i < m_data.size(); i++)
			if (m_data[i])
				func(m_data[i]);
	}
	
	template<typename Th>
	Handle<Th> GetHandle(size_t id) {
		return Handle<Th>((Register<Th>*)this, id); // TODO: This is solution is kind of terrible and can cause all kinds of strange issues
	}

private:
	std::vector<T*> m_data;
};
