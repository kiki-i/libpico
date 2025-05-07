#include <algorithm>
#include <optional>

#include "../rxs_parsing_core/CSISegment.hxx"
#include "../rxs_parsing_core/ModularPicoScenesFrame.hxx"
#include "../rxs_parsing_core/SignalMatrix.hxx"

#include "libpicoFrame.hxx"

class PicoParser {
public:
  PicoParser(const ModularPicoScenesRxFrame &);
  auto getLibpicoRaw(LibpicoRaw *) -> void;

private:
  const ModularPicoScenesRxFrame &raw;

  auto getLibpicoStandardHeader(LibpicoStandardHeader &) -> void;
  auto getLibpicoRxSBasic(LibpicoRxSBasic &) -> void;
  auto getLibpicoRxExtraInfo(LibpicoRxExtraInfo &) -> void;
  auto getLibpicoCsi(LibpicoCsi &) -> void;
};
