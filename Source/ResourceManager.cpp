#include <YAWN/ResourceManager.hpp>

using namespace YAWN;

Map<String, Managed<Resource>> ResourceManager::_resources;

void ResourceManager::Initialize() {
}

void ResourceManager::Release() {
    _resources.Clear();
}
