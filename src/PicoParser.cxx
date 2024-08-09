#include "PicoParser.hxx"

void splitComplexVector(const std::vector<ComplexFloatData> &complexVector,
                        std::vector<float> &realVector,
                        std::vector<float> &imagVector) {

  realVector.reserve(complexVector.size());
  imagVector.reserve(complexVector.size());

  for (const auto &complexNumber : complexVector) {
    realVector.push_back(complexNumber.real());
    imagVector.push_back(complexNumber.imag());
  }
}

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

  LibpicoCsi libpicoCsi;

  libpicoCsi.deviceType = static_cast<uint16_t>(rawCsi->deviceType);
  libpicoCsi.packetFormat = static_cast<int8_t>(rawCsi->packetFormat);
  libpicoCsi.firmwareVersion = static_cast<uint8_t>(rawCsi->deviceType);
  libpicoCsi.cbw = static_cast<uint16_t>(rawCsi->cbw);
  libpicoCsi.antSelection = rawCsi->antSel;

  libpicoCsi.carrierFreq = rawCsi->carrierFreq;
  libpicoCsi.samplingRate = rawCsi->samplingRate;

  auto subcarrierIndices = vectorToPtr<int16_t>(rawCsi->subcarrierIndices);
  libpicoCsi.subcarrierIndicesPtr = std::get<0>(subcarrierIndices);
  libpicoCsi.subcarrierIndicesSize = std::get<1>(subcarrierIndices);

  libpicoCsi.subcarrierBandwidth = rawCsi->subcarrierBandwidth;
  libpicoCsi.subcarrierOffset = rawCsi->subcarrierOffset;
  libpicoCsi.nTones = rawCsi->dimensions.numTones;

  libpicoCsi.nTx = rawCsi->dimensions.numTx;
  libpicoCsi.nRx = rawCsi->dimensions.numRx;
  libpicoCsi.nEss = rawCsi->dimensions.numESS;
  libpicoCsi.nCsi = rawCsi->dimensions.numCSI;

  auto csiVector = rawCsi->CSIArray.array;
  libpicoCsi.csiSize = csiVector.size();

  auto csiRealVector = std::vector<float>();
  auto csiImagVector = std::vector<float>();
  splitComplexVector(csiVector, csiRealVector, csiImagVector);
  auto csiReal = vectorToPtr<float>(csiRealVector);
  auto csiImag = vectorToPtr<float>(csiImagVector);

  libpicoCsi.csiRealPtr = std::get<0>(csiReal);
  libpicoCsi.csiImagPtr = std::get<0>(csiImag);

  auto magnitude = vectorToPtr<float>(rawCsi->magnitudeArray.array);
  auto phase = vectorToPtr<float>(rawCsi->phaseArray.array);
  libpicoCsi.magnitudePtr = std::get<0>(magnitude);
  libpicoCsi.phasePtr = std::get<0>(phase);

  return libpicoCsi;
}
