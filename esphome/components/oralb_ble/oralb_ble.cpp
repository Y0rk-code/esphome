#include "oralb_ble.h"
#include "esphome/core/log.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
  namespace oralb_ble {

    static const char *TAG = "oralb_ble";

    bool parse_oralb_data_byte(const esp32_ble_tracker::adv_data_t &adv_data, OralbParseResult &result) {
      if(adv_data.size() !=  11) {
        return false;
      }

      result.protocol_version = adv_data[0];

      result.type_id = adv_data[1];
      result.fw_version = adv_data[2];

      result.state = adv_data[3];

      result.is_high_pressure = (adv_data[4] & 0x80) == 0 ? false : true;
      result.is_reduced_motor = (adv_data[4] & 0x40) == 0 ? false : true;
      result.is_professional_timer = (adv_data[4] & 0x1) == 0 ? false : true;

      result.brush_time_seconds = adv_data[5] * 60 + adv_data[6];

      result.mode = adv_data[7];

      result.sector = adv_data[8] & 0x7;
      result.smiley = adv_data[8] & 0x38 >> 3;

      return true;
    }

    optional<OralbParseResult> parse_oralb(const esp32_ble_tracker::ESPBTDevice &device) {
      bool success = false;
      OralbParseResult result {};
      for (auto &it : device.get_manufacturer_datas()) {
        bool is_oralb = it.uuid.contains(0xDC, 0x00);
        if (!is_oralb)
          continue;

        if (parse_oralb_data_byte(it.data, result))
          success = true;
      }
      if (!success)
        return {};
      return result;
    }

    bool OralbListener::parse_device(const esp32_ble_tracker::ESPBTDevice &device) {
      auto res = parse_oralb(device);
      if (!res.has_value())
        return false;

      ESP_LOGD(TAG, "Got OralB (%s):", device.address_str().c_str());

      if (res->protocol_version.has_value()) {
        ESP_LOGD(TAG, "  protocol_version: %d", *res->protocol_version);
      }
      if (res->type_id.has_value()) {
        ESP_LOGD(TAG, "  type_id: %d", *res->type_id);
      }
      if (res->fw_version.has_value()) {
        ESP_LOGD(TAG, "  fw_version: %d", *res->fw_version);
      }
      if (res->state.has_value()) {
        ESP_LOGD(TAG, "  state: %d", *res->state);
      }
      if (res->is_high_pressure.has_value()) {
        ESP_LOGD(TAG, "  is_high_pressure: %d", *res->is_high_pressure);
      }
      if (res->is_reduced_motor.has_value()) {
        ESP_LOGD(TAG, "  is_reduced_motor: %d", *res->is_reduced_motor);
      }
      if (res->is_professional_timer.has_value()) {
        ESP_LOGD(TAG, "  is_professional_timer: %d", *res->is_professional_timer);
      }
      if (res->brush_time_seconds.has_value()) {
        ESP_LOGD(TAG, "  brush_time_seconds: %d", *res->brush_time_seconds);
      }
      if (res->mode.has_value()) {
        ESP_LOGD(TAG, "  mode: %d", *res->mode);
      }
      if (res->sector.has_value()) {
        ESP_LOGD(TAG, "  sector: %d", *res->sector);
      }
      if (res->smiley.has_value()) {
        ESP_LOGD(TAG, "  smiley: %d", *res->smiley);
      }

      return true;
    }

  }  // namespace oralb_ble
}  // namespace esphome

#endif
