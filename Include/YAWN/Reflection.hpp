#pragma once 

#include "Map.hpp"
#include "TypeInfo.hpp"
#include "String.hpp"
#include "Variant.hpp"

namespace YAWN {
    typedef void(*FieldSetter)(void*, const Variant&);
    typedef void(*FieldGetter)(const void*, Variant&);

    class Field {
    public:
        Field(FieldSetter setter, FieldGetter getter)
            : _setter(setter), _getter(getter) {
        }

        Field(const Field&) = default;
        Field& operator=(const Field&) = default;

        FieldSetter Setter() const {
            return _setter;
        }

        FieldGetter Getter() const {
            return _getter;
        }

    private:
        FieldSetter _setter = nullptr;
        FieldGetter _getter = nullptr;
    };

    class Type {
    public:
        Map<String, Field> Fields;
    };

    template<class T>
    class Meta : public NonCopyable {
    public:
        Meta(Type& type) : _type(type) {}

        template<auto Setter, auto Getter>
        void AddField(const String& name) {
            const auto setter = [](void* ptr, const Variant& variant) {
                T* obj = (T*)ptr;
                (obj->*Setter)(variant);
            };

            const auto getter = [](const void* ptr, Variant& variant) {
                const T* obj = (const T*)ptr;
                variant = (obj->*Getter)();
            };

            _type.Fields.Insert(name, Field(setter, getter));
        }

    private:
        Type& _type;
    };

    class Reflection : public NonInstantiable {
    public:
        static void Initialize();

        static void Release();

        template<class T>
        static void RegisterType(const String& name) {
            const Id id = TypeId<T>();
            Type& type = _types[id];

            T::Register(Meta<T>(type));
        }
        
        template<class T>
        static Type& GetType() {
            return GetType(TypeId<T>());
        }

        static Type& GetType(Id typeId);

    private:
        static Map<Id, Type> _types;
    };
}