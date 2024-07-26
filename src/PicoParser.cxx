#include "PicoParser.hxx"

PicoParser::PicoParser(ModularPicoScenesRxFrame &raw) {
  this->raw = raw;
  this->csi = this->parseCsi();
};

auto PicoParser::parseCsi() -> const ParsedCsi {
  auto rawCsi = this->raw.csiSegment->getCSI();

  ParsedCsi csi;

  csi.deviceType = static_cast<uint16_t>(rawCsi->deviceType);
  csi.packetFormat = static_cast<int8_t>(rawCsi->packetFormat);
  csi.firmwareVersion = static_cast<uint8_t>(rawCsi->deviceType);
  csi.cbw = static_cast<uint16_t>(rawCsi->cbw);
  csi.antSelection = rawCsi->antSel;

  csi.carrierFreq = rawCsi->carrierFreq;
  csi.samplingRate = rawCsi->samplingRate;

  csi.subcarrierIndices = rawCsi->subcarrierIndices.data();

  csi.subcarrierBandwidth = rawCsi->subcarrierBandwidth;
  csi.subcarrierOffset = rawCsi->subcarrierOffset;
  csi.nTones = rawCsi->dimensions.numTones;

  csi.nTx = rawCsi->dimensions.numTx;
  csi.nRx = rawCsi->dimensions.numRx;
  csi.nEss = rawCsi->dimensions.numESS;
  csi.nCsi = rawCsi->dimensions.numCSI;

  csi.magnitude = rawCsi->magnitudeArray.array.data();
  csi.phase = rawCsi->phaseArray.array.data();

  return csi;
}
