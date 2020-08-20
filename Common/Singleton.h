#pragma once

#define Singleton(type, constructor)					\
	public:												\
		static type& Get() {							\
			return *m_inst;								\
		}												\
														\
		template<typename... Targs>						\
		static type& Create(Targs... args) {			\
			m_inst = (type*) new char[sizeof(type)];	\
			new (m_inst) type(args...);					\
			return *m_inst;								\
		}												\
														\
		static void Destroy() {							\
			if (m_inst) {								\
				delete m_inst;							\
				m_inst = nullptr;						\
			}											\
		}												\
														\
		static void Set(type& ref) {					\
			if (m_inst) {								\
				delete m_inst;							\
			}											\
			m_inst = &ref;								\
		}												\
														\
														\
		type(type const&) = delete;						\
		type(type&&) = delete;							\
		type& operator=(type const&) = delete;			\
		type& operator=(type &&) = delete;				\
	private:											\
		type() constructor								\
		static inline type* m_inst = nullptr;
