#pragma once 

#include "Resource.hpp"
#include "String.hpp"
#include "Map.hpp"

namespace YAWN {
    class ResourceManager : public NonInstantiable {
    public:
        static void Initialize();

        static void Release();

        template<typename TResource>
        static Managed<TResource> Load(const String& filename) {
            Managed<Resource>& resource = _resources[filename];
            if (resource) {
                return resource.CastTo<TResource>();
            }

            Managed<TResource> newResource = TResource::FromFile(filename);
            resource = newResource.Get();
            return newResource;
        }

    private:
        static Map<String, Managed<Resource>> _resources;
    };
}
