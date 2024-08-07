#include "api.hxx"

auto getLibpicoCsiFromBuffer(const uint8_t *buffer, const uint32_t len,
                             const bool interp = false) -> LibpicoCsi {
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

auto freeLibpicoCsi(LibpicoCsi parsedCsi) -> bool {
  try {
    delete[] parsedCsi.subcarrierIndicesPtr;
    parsedCsi.subcarrierIndicesPtr = nullptr;
    delete[] parsedCsi.magnitudePtr;
    parsedCsi.magnitudePtr = nullptr;
    delete[] parsedCsi.phasePtr;
    parsedCsi.phasePtr = nullptr;
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Caught an exception: " << e.what() << std::endl;
    return false;
  }
}
