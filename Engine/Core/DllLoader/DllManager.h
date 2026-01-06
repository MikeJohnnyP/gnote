#pragma once
#include "Core/Logger/Logger.h"
#include "LoadLibrary.h"
#include "pch.h"

namespace Gnote
{

struct HandleInfo
{
    void *handle;
    time_t lastModTime;
    std::string path;
};

class GNOTE_API DllManager
{
  public:
    static DllManager *getInstance()
    {
        return m_instance;
    }

    static void Init();
    static void Shutdown();

    static bool LoadDll(const std::string &moduleName, const std::string &path);
    static void UnloadDll(const std::string &moduleName);

    template <typename T> static T GetStructModuleAPI(const std::string &moduleName, const std::string &createFuncName)
    {
        GNOTE_CORE_ASSERT(std::is_pointer<T>::value, "T must be a pointer type");
        DllManager *instance = getInstance();
        auto cacheIt = instance->structAPICache.find(moduleName);
        if (cacheIt != instance->structAPICache.end())
        {
            CORE_LOG_INFO("Using cached API for module: {0}", moduleName);
            return reinterpret_cast<T>(cacheIt->second);
        }
        auto it = instance->loadedDlls.find(moduleName);
        if (it != instance->loadedDlls.end())
        {
            void *func = loadFunction(it->second.handle, createFuncName.c_str());
            if (func)
            {
                using CreateFuncType = T (*)();
                CreateFuncType createFunc = reinterpret_cast<CreateFuncType>(func);
                T api = createFunc();
                instance->structAPICache[moduleName] = reinterpret_cast<void *>(api);
                return api;
            }
            else
            {
                GNOTE_CORE_ASSERT(false, "Failed to load function: {0}", createFuncName);
            }
        }
        return nullptr;
    }

    static void UpdateDlls();

  private:
    DllManager()
    {
    }
    ~DllManager();
    DllManager(const DllManager &) = delete;
    DllManager &operator=(const DllManager &) = delete;

    static DllManager *m_instance;
    std::unordered_map<std::string, HandleInfo> loadedDlls;
    std::unordered_map<std::string, void *> structAPICache;
};
} // namespace Gnote
