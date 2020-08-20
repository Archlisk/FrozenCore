#pragma once

#define Singleton(type)									\
	public:												\
		static inline type& Get() {						\
			return *m_inst;								\
		}												\
														\
		static type& Create() {							\
			m_inst = new type();						\
			m_inst->Init();								\
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
		type() {}										\
		static inline type* m_inst = nullptr;
