#include "PicoParser.hxx"

template <typename T>
auto vectorToPtr(std::vector<T> &data) -> std::tuple<T *, int> {
  int size = data.size();
  T *dataPtr = new T[size];
  std::copy(data.begin(), data.end(), dataPtr);
  return std::make_tuple(dataPtr, size);
};

PicoParser::PicoParser(const ModularPicoScenesRxFrame &raw) {
  this->raw = raw;
};

auto PicoParser::getLibpicoCsi() -> LibpicoCsi {
  auto rawCsi = this->raw.csiSegment->getCSI();

  LibpicoCsi csi;

  csi.deviceType = static_cast<uint16_t>(rawCsi->deviceType);
  csi.packetFormat = static_cast<int8_t>(rawCsi->packetFormat);
  csi.firmwareVersion = static_cast<uint8_t>(rawCsi->deviceType);
  csi.cbw = static_cast<uint16_t>(rawCsi->cbw);
  csi.antSelection = rawCsi->antSel;

  csi.carrierFreq = rawCsi->carrierFreq;
  csi.samplingRate = rawCsi->samplingRate;

  auto subcarrierIndices = vectorToPtr<int16_t>(rawCsi->subcarrierIndices);
  csi.subcarrierIndicesPtr = std::get<0>(subcarrierIndices);
  csi.subcarrierIndicesSize = std::get<1>(subcarrierIndices);

  csi.subcarrierBandwidth = rawCsi->subcarrierBandwidth;
  csi.subcarrierOffset = rawCsi->subcarrierOffset;
  csi.nTones = rawCsi->dimensions.numTones;

  csi.nTx = rawCsi->dimensions.numTx;
  csi.nRx = rawCsi->dimensions.numRx;
  csi.nEss = rawCsi->dimensions.numESS;
  csi.nCsi = rawCsi->dimensions.numCSI;

  auto magnitude = vectorToPtr<float>(rawCsi->magnitudeArray.array);
  auto phase = vectorToPtr<float>(rawCsi->phaseArray.array);
  csi.magnitudePtr = std::get<0>(magnitude);
  csi.magnitudeSize = std::get<1>(magnitude);
  csi.phasePtr = std::get<0>(phase);
  csi.phaseSize = std::get<1>(phase);

  return csi;
}
