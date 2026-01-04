
namespace Gnote
{
void *loadLibrary(const char *libraryPath);
void *loadFunction(void *handle, const char *symbol);
void unloadLibrary(void *handle);
} // namespace Gnote
