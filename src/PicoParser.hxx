#include "../rxs_parsing_core/CSISegment.hxx"
#include "../rxs_parsing_core/ModularPicoScenesFrame.hxx"
#include "../rxs_parsing_core/SignalMatrix.hxx"

struct ParsedCsi {
  // 1 word
  uint16_t deviceType;
  uint8_t firmwareVersion;
  int8_t packetFormat;
  uint16_t cbw;
  uint16_t antSelection; // uint8_t

  // 2 word
  uint64_t carrierFreq;
  uint64_t samplingRate;

  // 1 word
  int16_t *subcarrierIndices;

  // 1 word
  uint32_t subcarrierBandwidth;
  int16_t subcarrierOffset;
  uint16_t nTones;

  // 1 word
  uint8_t nTx;
  uint8_t nRx;
  uint16_t nEss; // uint8_t
  uint32_t nCsi; // uint16_t

  // 2 word
  float *magnitude;
  float *phase;
};

class PicoParser {
public:
  PicoParser(ModularPicoScenesRxFrame &raw);
  auto parseCsi() -> const ParsedCsi;

private:
  ModularPicoScenesRxFrame raw;
  ParsedCsi csi;
};
