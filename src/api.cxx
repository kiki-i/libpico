#include "api.hxx"

auto getLibpicoCsiFromBuffer(const uint8_t *buffer, const uint32_t len,
                             const bool interp = true) -> LibpicoCsi {
  auto out = LibpicoCsi{};
  out.returnCode = -1;

  try {
    auto raw = ModularPicoScenesRxFrame::fromBuffer(buffer, len, interp);
    if (raw.has_value()) {
      out = PicoParser(raw.value()).getLibpicoCsi();
      out.returnCode = 0;
    }
  } catch (const std::exception &e) {
    std::cerr << "Caught an exception: " << e.what() << std::endl;
  }
  return out;
}

auto freeLibpicoCsi(LibpicoCsi libpicoCsi) -> bool {
  try {
    delete[] libpicoCsi.subcarrierIndicesPtr;
    libpicoCsi.subcarrierIndicesPtr = nullptr;
    delete[] libpicoCsi.csiRealPtr;
    libpicoCsi.csiRealPtr = nullptr;
    delete[] libpicoCsi.csiImagPtr;
    libpicoCsi.csiImagPtr = nullptr;
    delete[] libpicoCsi.magnitudePtr;
    libpicoCsi.magnitudePtr = nullptr;
    delete[] libpicoCsi.phasePtr;
    libpicoCsi.phasePtr = nullptr;
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Caught an exception: " << e.what() << std::endl;
    return false;
  }
}
