#include "PicoParser.hxx"

#if defined(_WIN32)
#define API_EXPORT extern "C" __declspec(dllexport)
#else
#define API_EXPORT extern "C" __attribute__((visibility("default")))
#endif

API_EXPORT auto getLibpicoCsiFromBuffer(const uint8_t *buffer,
                                        const uint32_t len, const bool interp)
    -> LibpicoRaw *;

API_EXPORT auto freeLibpicoRaw(LibpicoRaw *) -> bool;
