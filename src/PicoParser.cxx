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

PicoParser::PicoParser(const ModularPicoScenesRxFrame &raw) : raw(raw) {};

auto PicoParser::getLibpicoRaw(LibpicoRaw *out) -> void {
  this->getLibpicoStandardHeader(out->standardHeader);
  this->getLibpicoRxSBasic(out->rxSBasic);
  this->getLibpicoRxExtraInfo(out->rxExtraInfo);
  this->getLibpicoCsi(out->csi);
}

auto PicoParser::getLibpicoStandardHeader(LibpicoStandardHeader &out) -> void {
  const auto raw = this->raw.standardHeader;

  auto &controlField = out.controlField;

  controlField.version = raw.fc.version;
  controlField.type = raw.fc.type;
  controlField.subtype = raw.fc.subtype;
  controlField.toDS = raw.fc.toDS;
  controlField.fromDS = raw.fc.fromDS;
  controlField.moreFrags = raw.fc.moreFrags;
  controlField.retry = raw.fc.retry;
  controlField.powerMgmt = raw.fc.power_mgmt;
  controlField.more = raw.fc.more;
  controlField.protect = raw.fc.protect;
  controlField.order = raw.fc.order;

  std::copy(raw.addr1.begin(), raw.addr1.end(), out.addr1);
  std::copy(raw.addr2.begin(), raw.addr2.end(), out.addr2);
  std::copy(raw.addr3.begin(), raw.addr3.end(), out.addr3);
  out.frag = raw.frag;
  out.seq = raw.seq;
}

auto PicoParser::getLibpicoRxSBasic(LibpicoRxSBasic &out) -> void {
  const auto raw = this->raw.rxSBasicSegment->getBasic();

  out.deviceType = raw.deviceType;
  out.tstamp = raw.tstamp;
  out.systemTime = raw.systemTime;
  out.centerFreq = raw.centerFreq;
  out.controlFreq = raw.controlFreq;
  out.cbw = raw.cbw;
  out.packetFormat = raw.packetFormat;
  out.pktCbw = raw.pkt_cbw;
  out.guardInterval = raw.guardInterval;
  out.mcs = raw.mcs;
  out.numSTS = raw.numSTS;
  out.numESS = raw.numESS;
  out.numRx = raw.numRx;
  out.noiseFloor = raw.noiseFloor;
  out.rssi = raw.rssi;
}

auto PicoParser::getLibpicoRxExtraInfo(LibpicoRxExtraInfo &out) -> void {
  const auto raw = this->raw.rxExtraInfoSegment->getExtraInfo();

  out.featureCode = raw.featureCode;
  out.length = raw.length;
  out.version = raw.version;
  std::copy(raw.macaddr_rom, raw.macaddr_rom + 6, out.macAddrRom);
  std::copy(raw.macaddr_cur, raw.macaddr_cur + 6, out.macAddrCur);
  out.channelSelect = raw.chansel;
  out.bmode = raw.bmode;
  std::copy(raw.evm, raw.evm + 20, out.evm);
  out.txChainMask = raw.txChainMask;
  out.rxChainMask = raw.rxChainMask;
  out.txPower = raw.txpower;
  out.cf = raw.cf;
  out.txTsf = raw.txTSF;
  out.lastHwTxTsf = raw.lastHwTxTSF;
  out.channelFlags = raw.channelFlags;
  out.txNess = raw.tx_ness;
  out.tuningPolicy = raw.tuningPolicy;
  out.pllRate = raw.pll_rate;
  out.pllRefdiv = raw.pll_refdiv;
  out.pllClockSelect = raw.pll_clock_select;
  out.agc = raw.agc;
  std::copy(raw.ant_sel, raw.ant_sel + 3, out.antSelect);
  out.samplingRate = raw.samplingRate;
  out.cfo = raw.cfo;
  out.sfo = raw.sfo;
}

auto PicoParser::getLibpicoCsi(LibpicoCsi &out) -> void {
  const auto raw = this->raw.csiSegment->getCSI();

  out.deviceType = static_cast<uint16_t>(raw->deviceType);
  out.packetFormat = static_cast<int8_t>(raw->packetFormat);
  out.firmwareVersion = static_cast<uint8_t>(raw->deviceType);
  out.cbw = static_cast<uint16_t>(raw->cbw);
  out.antSelect = raw->antSel;

  out.carrierFreq = raw->carrierFreq;
  out.samplingRate = raw->samplingRate;

  auto subcarrierIndices = vectorToPtr<int16_t>(raw->subcarrierIndices);
  out.subcarrierIndicesPtr = std::get<0>(subcarrierIndices);
  out.subcarrierIndicesSize = std::get<1>(subcarrierIndices);

  out.subcarrierBandwidth = raw->subcarrierBandwidth;
  out.subcarrierOffset = raw->subcarrierOffset;
  out.nTones = raw->dimensions.numTones;

  out.nTx = raw->dimensions.numTx;
  out.nRx = raw->dimensions.numRx;
  out.nEss = raw->dimensions.numESS;
  out.nCsi = raw->dimensions.numCSI;

  auto csiVector = raw->CSIArray.array;
  out.csiSize = csiVector.size();

  auto csiRealVector = std::vector<float>();
  auto csiImagVector = std::vector<float>();
  splitComplexVector(csiVector, csiRealVector, csiImagVector);
  auto csiReal = vectorToPtr<float>(csiRealVector);
  auto csiImag = vectorToPtr<float>(csiImagVector);

  out.csiRealPtr = std::get<0>(csiReal);
  out.csiImagPtr = std::get<0>(csiImag);

  auto magnitude = vectorToPtr<float>(raw->magnitudeArray.array);
  auto phase = vectorToPtr<float>(raw->phaseArray.array);
  out.magnitudePtr = std::get<0>(magnitude);
  out.magnitudeSize = std::get<1>(magnitude);
  out.phasePtr = std::get<0>(phase);
  out.phaseSize = std::get<1>(phase);
}
