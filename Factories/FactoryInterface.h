#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <dlfcn.h>
#include <iostream>

template <typename BaseType>
class FactoryInterface {
public:
    using CreateFunc = BaseType* (*)();
    using DestroyFunc = void (*)(BaseType*);

    virtual ~FactoryInterface() {
        unloadAll();
    }

    bool load(const std::string& name, const std::string& libPath) {
        if (m_instances.count(name)) {
            std::cerr << "Plugin '" << name << "' already loaded.\n";
            return false;
        }

        void* handle = dlopen(libPath.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "dlopen failed: " << dlerror() << "\n";
            return false;
        }

        CreateFunc createFunc = reinterpret_cast<CreateFunc>(dlsym(handle, getCreateSymbolName().c_str()));
        if (!createFunc) {
            std::cerr << "dlsym failed (create): " << dlerror() << "\n";
            dlclose(handle);
            return false;
        }

        DestroyFunc destroyFunc = reinterpret_cast<DestroyFunc>(dlsym(handle, getDestroySymbolName().c_str()));
        if (!destroyFunc) {
            std::cerr << "dlsym failed (destroy): " << dlerror() << "\n";
            dlclose(handle);
            return false;
        }

        BaseType* instance = createFunc();
        std::shared_ptr<BaseType> smartPtr(instance, destroyFunc);

        m_instances[name] = smartPtr;
        m_handles[name] = handle;
        return true;
    }

    std::shared_ptr<BaseType> get(const std::string& name) const {
        auto it = m_instances.find(name);
        if (it != m_instances.end()) {
            return it->second;
        }
        return nullptr;
    }

    void unloadAll() {
        m_instances.clear(); // ensures destroyFunc is called before dlclose
        for (auto& [name, handle] : m_handles) {
            if (handle) {
                dlclose(handle);
            }
        }
        m_handles.clear();
    }

protected:
    virtual std::string getCreateSymbolName() const = 0;
    virtual std::string getDestroySymbolName() const = 0;

    std::unordered_map<std::string, std::shared_ptr<BaseType>> m_instances;
    std::unordered_map<std::string, void*> m_handles;
};
