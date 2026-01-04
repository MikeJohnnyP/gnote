#include "LoadLibrary.h"
#include "Core/Logger/Logger.h"
#include "pch.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace Gnote
{
#ifndef _WIN32
void *loadLibrary(const char *libraryPath)
{
    if (!libraryPath)
    {
        CORE_LOG_ERROR("Library path is null.");
        GNOTE_CORE_ASSERT(libraryPath, "Library path is null.");
        return nullptr;
    }
    void *handle = dlopen(libraryPath, RTLD_NOW);
    if (!handle)
    {
        CORE_LOG_ERROR("Cannot load library {0}: {1}", libraryPath, dlerror());
        GNOTE_CORE_ASSERT(handle, "");
        return nullptr;
    }
    return handle;
}
void *loadFunction(void *handle, const char *symbol)
{
    if (!handle)
    {
        CORE_LOG_ERROR("Invalid library handle.");
        GNOTE_CORE_ASSERT(handle, "");
        return nullptr;
    }
    dlerror(); // Clear any existing error
    void *func = dlsym(handle, symbol);
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        CORE_LOG_ERROR("Cannot load symbol: {0}", dlsym_error);
        GNOTE_CORE_ASSERT(!dlsym_error, "");
        return nullptr;
    }
    return func;
}
void unloadLibrary(void *handle)
{
    if (handle)
    {
        dlclose(handle);
    }
}
#endif
#ifdef _WIN32
void *loadLibrary(const char *libraryPath)
{
    if (!libraryPath)
    {
        CORE_LOG_ERROR("Library path is null.");
        GNOTE_CORE_ASSERT(libraryPath, "Library path is null.");
        return nullptr;
    }
    HMODULE handle = LoadLibraryA(libraryPath);
    if (!handle)
    {
        CORE_LOG_ERROR("Cannot load library {0}: {1}", libraryPath, dlerror());
        GNOTE_CORE_ASSERT(handle, "");
        return nullptr;
    }
    return (void *)handle;
}
void *loadFunction(void *handle, const char *symbol)
{
    if (!handle)
    {
        CORE_LOG_ERROR("Invalid library handle.");
        GNOTE_CORE_ASSERT(handle, "");
        return nullptr;
    }
    FARPROC func = GetProcAddress((HMODULE)handle, symbol);
    if (!func)
    {
        CORE_LOG_ERROR("Cannot load symbol: {0}", dlsym_error);
        GNOTE_CORE_ASSERT(!dlsym_error, "");
        return nullptr;
    }
    return (void *)func;
}
void unloadLibrary(void *handle)
{
    if (handle)
    {
        FreeLibrary((HMODULE)handle);
    }
}
#endif
} // namespace Gnote
