#include <YAWN/Reflection.hpp>

using namespace YAWN;

Map<Id, Type> Reflection::_types;

void Reflection::Initialize() {
}

void Reflection::Release() {
}

Type& Reflection::GetType(Id typeId) {
    return _types[typeId];
}
