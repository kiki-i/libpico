#include "PicoParser.hxx"

#if defined(_WIN32)
#define API_EXPORT extern "C" __declspec(dllexport)
#else
#define API_EXPORT
#endif

API_EXPORT LibpicoCsi getLibpicoCsiFromBuffer(const uint8_t *buffer,
                                              const uint32_t len,
                                              const bool interp);

API_EXPORT bool freeLibpicoCsi(const LibpicoCsi parsedCsi);
