#include "../rxs_parsing_core/CSISegment.hxx"
#include "../rxs_parsing_core/ModularPicoScenesFrame.hxx"
#include "../rxs_parsing_core/SignalMatrix.hxx"

#include <algorithm>
#include <optional>

struct LibpicoCsi {
  // 1 word
  int64_t returnCode;

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
  uint32_t subcarrierBandwidth;
  int32_t subcarrierOffset; // int16_t

  // 1 word
  uint16_t nTones;
  uint8_t nTx;
  uint8_t nRx;
  uint16_t nEss; // uint8_t
  uint16_t nCsi;

  // 2 word
  int16_t *subcarrierIndicesPtr;
  int64_t subcarrierIndicesSize;

  // 5 word
  int64_t csiSize;
  float *csiRealPtr;
  float *csiImagPtr;
  float *magnitudePtr;
  float *phasePtr;
};

class PicoParser {
public:
  PicoParser(const ModularPicoScenesRxFrame &raw);
  auto getLibpicoCsi() -> LibpicoCsi;

private:
  ModularPicoScenesRxFrame raw;
};
