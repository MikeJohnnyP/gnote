#include "DllManager.h"

namespace Gnote
{

std::string destroyFunctionName = "destroy";

DllManager *DllManager::m_instance = nullptr;
time_t getFileModTime(const char *path)
{
    struct stat result;
    if (stat(path, &result) == 0)
    {
        return result.st_mtime;
    }
    return 0;
}

void DllManager::Init()
{
    if (!m_instance)
    {
        m_instance = new DllManager();
    }
}

void DllManager::Shutdown()
{
    DllManager *instance = getInstance();
    for (auto &pair : instance->loadedDlls)
    {
        unloadLibrary(pair.second.handle);
    }
    instance->loadedDlls.clear();
    instance->structAPICache.clear();
}

bool DllManager::LoadDll(const std::string &moduleName, const std::string &path)
{
    if (moduleName.empty() || path.empty())
    {
        GNOTE_CORE_ASSERT(false, "Module name or path is empty!");
        return false;
    }
    void *handle = loadLibrary(path.c_str());
    DllManager *instance = getInstance();
    if (handle)
    {
        HandleInfo handleInfo = {handle, getFileModTime(path.c_str()), path};
        instance->loadedDlls[moduleName] = handleInfo;
        return true;
    }
    GNOTE_CORE_ASSERT(false, "Failed to load library: {0}", path);
    return false;
}
void DllManager::UnloadDll(const std::string &moduleName)
{
    if (moduleName.empty())
    {
        GNOTE_CORE_ASSERT(false, "Module name is empty!");
        return;
    }
    DllManager *instance = getInstance();
    auto it = instance->loadedDlls.find(moduleName);
    if (it != instance->loadedDlls.end())
    {
        // Call the destroy function if it exists
        void *func = loadFunction(it->second.handle, destroyFunctionName.c_str());
        if (func)
        {
            using DestroyFuncType = void (*)();
            DestroyFuncType destroy = reinterpret_cast<DestroyFuncType>(func);
            destroy();
        }

        unloadLibrary(it->second.handle);
        instance->loadedDlls.erase(it);
        instance->structAPICache.erase(moduleName);
    }
}

void DllManager::UpdateDlls()
{
    DllManager *instance = getInstance();
    for (auto &pair : instance->loadedDlls)
    {
        const std::string &moduleName = pair.first;
        HandleInfo &handleInfo = pair.second;
        // Use the correct file path for modification time
        time_t modTime = getFileModTime(handleInfo.path.c_str());
        if (modTime != handleInfo.lastModTime)
        {
            // Unload old library
            void *func = loadFunction(handleInfo.handle, destroyFunctionName.c_str());
            if (func)
            {
                using DestroyFuncType = void (*)();
                DestroyFuncType destroy = reinterpret_cast<DestroyFuncType>(func);
                destroy();
            }

            unloadLibrary(handleInfo.handle);
            // Load new library using the correct path
            void *newHandle = loadLibrary(handleInfo.path.c_str());
            if (newHandle)
            {
                handleInfo.handle = newHandle;
                handleInfo.lastModTime = modTime;
                // Invalidate cached API structs
                instance->structAPICache.erase(moduleName);

                CORE_LOG_INFO("Reloaded module: {0}", moduleName);
            }
            else
            {
                CORE_LOG_ERROR("Failed to reload module: {0}", moduleName);
                handleInfo.handle = nullptr; // Mark as invalid
            }
        }
    }
}

}; // namespace Gnote
