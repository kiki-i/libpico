#include <algorithm>

#define META_HAS_DATA_STANDARD_HEADER (1U << 0)
#define META_HAS_DATA_RX_BASIC        (1U << 1)
#define META_HAS_DATA_RXEXTRAINFO     (1U << 2)
#define META_HAS_DATA_CSI             (1U << 3)
struct LibpicoMeta {
  uint8_t hasData;
} __attribute__((packed));

struct ieee80211MacFrameHeaderControlField {
  uint16_t version;
  uint16_t type;
  uint16_t subtype;
  uint16_t toDS;
  uint16_t fromDS;
  uint16_t moreFrags;
  uint16_t retry;
  uint16_t powerMgmt;
  uint16_t more;
  uint16_t protect;
  uint16_t order;
} __attribute__((packed));
struct LibpicoStandardHeader {
  ieee80211MacFrameHeaderControlField controlField;
  uint8_t addr1[6];
  uint8_t addr2[6];
  uint8_t addr3[6];
  uint16_t frag;
  uint16_t seq;
} __attribute__((packed));

struct LibpicoRxSBasic {
  uint16_t deviceType;
  uint64_t tstamp;
  uint64_t systemTime;
  int16_t centerFreq;
  int16_t controlFreq;
  uint16_t cbw;
  uint8_t packetFormat;
  uint16_t pktCbw;
  uint16_t guardInterval;
  uint8_t mcs;
  uint8_t numSTS;
  uint8_t numESS;
  uint8_t numRx;
  int8_t noiseFloor;
  int8_t rssi;
} __attribute__((packed));

#define EXTRAINFO_HAS_LENGTH           (1U << 0)
#define EXTRAINFO_HAS_VERSION          (1U << 1)
#define EXTRAINFO_HAS_MACADDR_CUR      (1U << 2)
#define EXTRAINFO_HAS_MACADDR_ROM      (1U << 3)
#define EXTRAINFO_HAS_CHANSEL          (1U << 4)
#define EXTRAINFO_HAS_BMODE            (1U << 5)
#define EXTRAINFO_HAS_EVM              (1U << 6)
#define EXTRAINFO_HAS_TXCHAINMASK      (1U << 7)
#define EXTRAINFO_HAS_RXCHAINMASK      (1U << 8)
#define EXTRAINFO_HAS_TXPOWER          (1U << 9)
#define EXTRAINFO_HAS_CF               (1U << 10)
#define EXTRAINFO_HAS_TXTSF            (1U << 11)
#define EXTRAINFO_HAS_LASTHWTXTSF      (1U << 12)
#define EXTRAINFO_HAS_CHANNELFLAGS     (1U << 13)
#define EXTRAINFO_HAS_TXNESS           (1U << 14)
#define EXTRAINFO_HAS_TUNINGPOLICY     (1U << 15)
#define EXTRAINFO_HAS_PLLRATE          (1U << 16)
#define EXTRAINFO_HAS_PLLREFDIV        (1U << 17)
#define EXTRAINFO_HAS_PLLCLKSEL        (1U << 18)
#define EXTRAINFO_HAS_AGC              (1U << 19)
#define EXTRAINFO_HAS_ANTENNASELECTION (1U << 20)
#define EXTRAINFO_HAS_SAMPLINGRATE     (1U << 21)
#define EXTRAINFO_HAS_CFO              (1U << 22)
#define EXTRAINFO_HAS_SFO              (1U << 23)
struct LibpicoRxExtraInfo {
  uint32_t featureCode;
  uint16_t length;
  uint64_t version;
  uint8_t macAddrRom[6];
  uint8_t macAddrCur[6];
  uint32_t channelSelect;
  uint8_t bmode;
  int8_t evm[20];
  uint8_t txChainMask;
  uint8_t rxChainMask;
  uint8_t txPower;
  uint64_t cf;
  uint32_t txTsf;
  uint32_t lastHwTxTsf;
  uint16_t channelFlags;
  uint8_t txNess;
  uint8_t tuningPolicy;
  uint16_t pllRate;
  uint8_t pllRefdiv;
  uint8_t pllClockSelect;
  uint8_t agc;
  uint8_t antSelect[3];
  uint64_t samplingRate;
  int32_t cfo;
  int32_t sfo;
} __attribute__((packed));

struct LibpicoCsi {
  uint16_t deviceType;
  uint8_t firmwareVersion;
  int8_t packetFormat;
  uint16_t cbw;
  uint64_t carrierFreq;
  uint64_t samplingRate;
  uint32_t subcarrierBandwidth;
  uint8_t antSelect;
  int16_t subcarrierOffset;

  uint16_t nTones;
  uint8_t nTx;
  uint8_t nRx;
  uint8_t nEss;
  uint16_t nCsi;

  int16_t *subcarrierIndicesPtr;
  int64_t subcarrierIndicesSize;

  float *csiRealPtr;
  float *csiImagPtr;
  int64_t csiSize;

  float *magnitudePtr;
  int64_t magnitudeSize;

  float *phasePtr;
  int64_t phaseSize;
} __attribute__((packed));

struct LibpicoRaw {
  LibpicoMeta meta;

  LibpicoStandardHeader standardHeader;
  LibpicoRxSBasic rxSBasic;
  LibpicoRxExtraInfo rxExtraInfo;
  LibpicoCsi csi;
} __attribute__((packed));
