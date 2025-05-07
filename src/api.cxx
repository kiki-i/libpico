#include "api.hxx"

auto getLibpicoCsiFromBuffer(const uint8_t *buffer, const uint32_t len,
                             const bool interp = true) -> LibpicoRaw * {
  auto out = new LibpicoRaw;
  out->meta.hasData = 0;

  auto raw = ModularPicoScenesRxFrame::fromBuffer(buffer, len, interp);
  if (raw.has_value()) {
    PicoParser(raw.value()).getLibpicoRaw(out);
    out->meta.hasData |= META_HAS_DATA_STANDARD_HEADER;
    out->meta.hasData |= META_HAS_DATA_RX_BASIC;
    out->meta.hasData |= META_HAS_DATA_RXEXTRAINFO;
    out->meta.hasData |= META_HAS_DATA_CSI;
  }
  return out;
}

template <typename T> auto freePtr(T *&ptr) -> void {
  delete ptr;
  ptr = nullptr;
}
template <typename T> auto freeArray(T *&ptr) -> void {
  delete[] ptr;
  ptr = nullptr;
}

auto freeLibpicoCsi(LibpicoCsi libpicoCsi) -> void {
  freeArray(libpicoCsi.subcarrierIndicesPtr);
  freeArray(libpicoCsi.csiRealPtr);
  freeArray(libpicoCsi.csiImagPtr);
  freeArray(libpicoCsi.magnitudePtr);
  freeArray(libpicoCsi.phasePtr);
}

auto freeLibpicoRaw(LibpicoRaw *libpicoRaw) -> bool {
  try {
    freeLibpicoCsi(libpicoRaw->csi);
    freePtr(libpicoRaw);
    return true;
  } catch (const std::exception &e) {
    throw e;
    return false;
  }
}
