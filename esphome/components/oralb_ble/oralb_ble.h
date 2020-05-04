#pragma once

#include "esphome/core/component.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
  namespace oralb_ble {

    struct OralbParseResult {
      optional<uint8_t> protocol_version;
      optional<uint8_t> type_id;
      optional<uint8_t> fw_version;
      optional<uint8_t> state;
      optional<bool> is_high_pressure;
      optional<bool> is_reduced_motor;
      optional<bool> is_professional_timer;
      optional<uint8_t> brush_time_seconds;
      optional<uint8_t> mode;
      optional<uint8_t> sector;
      optional<uint8_t> smiley;
    };

    bool parse_oralb_data_byte(uint8_t data_type, const uint8_t *data, uint8_t data_length, OralbParseResult &result);

    optional<OralbParseResult> parse_oralb(const esp32_ble_tracker::ESPBTDevice &device);

    class OralbListener : public esp32_ble_tracker::ESPBTDeviceListener {
      public:
      bool parse_device(const esp32_ble_tracker::ESPBTDevice &device) override;
    };

  }  // namespace oralb_ble
}  // namespace esphome

#endif
