#pragma once

#include <FC/Map.h>
#include <FC/Vector.h>
#include <FC/String.h>

class Lexer;

class Config 
{
public:

	struct Value 
	{
		typedef Map<String, Value>	ObjectType;
		typedef Vector<Value>		ArrayType;
		typedef String				StringType;
	
		typedef Ref<Map<String, Value>>	ObjectPtr;
		typedef Ref<Vector<Value>>		ArrayPtr;
		typedef Ref<String>				StringPtr;
		
		enum class Type {
			Object,
			Array,
			Value,
			None
		};
		
		Value() {}
		Value(Type type) {
			switch(type) {
				case Type::Object:
					m_children = std::make_unique<ObjectType>();
					break;
					
				case Type::Array:
					m_elements = std::make_unique<ArrayType>();
					break;
					
				case Type::Value:
					m_value = std::make_unique<StringType>();
					break;
					
				case Type::None:
					break;
			}
		}
		
		Value(const Value& other) {
			m_children = other.m_children;
			m_elements = other.m_elements;
			m_value = other.m_value;
		}
		
		const Value& operator[](const String& key) const {
			return m_children.get()->operator[](key);
		}
		
		const Value& operator[](u32 index) const {
			return m_elements.get()->operator[](index);
		}
		
		f32 FloatValue() const { return atof(m_value->c_str()); }
		i32 IntValue() const { return atoi(m_value->c_str()); }
		const String& StringValue() const { return *m_value.get(); }
		const ArrayType& Array() const { return *m_elements.get(); }
		const ObjectType& Object() const { return *m_children.get(); }
		
		Type GetType() {
			if (m_children.get())
				return Type::Object;
			if (m_elements.get())
				return Type::Array;
			if (m_value.get())
				return Type::Value;
			return Type::None;
		}
		
		void AddChild(const String& key, const Value& child) {
			if (GetType() != Type::Object)
				return;
			
			m_children->insert(std::make_pair(key, child));
		}
		
		void AddElement(const Value& elem) {
			if (GetType() != Type::Array)
				return;
				
			m_elements->push_back(elem);
		}
		
		void SetValue(const String& val) {
			m_value = std::make_unique<StringType>(val);
		}
		
		StringPtr m_value = nullptr;
		ObjectPtr m_children = nullptr;
		ArrayPtr m_elements = nullptr;
	};

	Config(const String& path);
	
	const Value& operator[](const String& key) { return root[key]; }

private:
	Value root = Value::Type::Object;

	static void ParseEntry(Lexer& lexer, Value& parent);
	static Value ParseValue(Lexer& lexer);
};
