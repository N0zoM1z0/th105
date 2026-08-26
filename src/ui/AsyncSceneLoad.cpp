namespace th105 {

extern "C" __declspec(dllimport) void *__stdcall CreateEventA(
    void *, int, int, const char *);
extern "C" __declspec(dllimport) unsigned __stdcall WaitForSingleObject(
    void *, unsigned);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);

struct SceneLoadEventWait {
    void *handle;
    unsigned wait_ms;

    SceneLoadEventWait()
        : handle(CreateEventA(0, 0, 0, 0)), wait_ms(0x10)
    {
    }
    ~SceneLoadEventWait()
    {
        CloseHandle(handle);
    }
    void wait()
    {
        WaitForSingleObject(handle, wait_ms);
    }
};

struct AsyncSceneThreadControl {
    unsigned char start(
        unsigned (__stdcall *thread_proc)(void *), void *context);
    unsigned char is_running();
};

extern AsyncSceneThreadControl g_async_scene_thread;
extern int g_async_scene_load_request;
unsigned __stdcall async_scene_load_worker(void *context);

unsigned char __cdecl start_async_engine_scene_load(int scene)
{
    SceneLoadEventWait event;
    while (g_async_scene_thread.is_running())
        event.wait();

    g_async_scene_load_request = scene;
    unsigned char started =
        g_async_scene_thread.start(async_scene_load_worker, 0);
    return started;
}

} // namespace th105
