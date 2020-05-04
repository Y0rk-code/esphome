#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/components/oralb_ble/oralb_ble.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
  namespace oralb_brush {

    class OralbBrush : public Component, public esp32_ble_tracker::ESPBTDeviceListener {
      public:
      void set_address(uint64_t address) {
        address_ = address;
      }

      bool parse_device(const esp32_ble_tracker::ESPBTDevice &device) override {
        if (device.address_uint64() != this->address_)
          return false;

        auto res = oralb_ble::parse_oralb(device);
        if (!res.has_value())
          return false;

        if (res->protocol_version.has_value() && this->protocol_version_ != nullptr)
          this->protocol_version_->publish_state(*res->protocol_version);
        if (res->type_id.has_value() && this->type_id_ != nullptr)
          this->type_id_->publish_state(*res->type_id);
        if (res->fw_version.has_value() && this->fw_version_ != nullptr)
          this->fw_version_->publish_state(*res->fw_version);
        if (res->state.has_value() && this->state_ != nullptr)
          this->state_->publish_state(*res->state);
        if (res->is_high_pressure.has_value() && this->is_high_pressure_ != nullptr)
          this->is_high_pressure_->publish_state(*res->is_high_pressure);
        if (res->is_reduced_motor.has_value() && this->is_reduced_motor_ != nullptr)
          this->is_reduced_motor_->publish_state(*res->is_reduced_motor);
        if (res->is_professional_timer.has_value() && this->is_professional_timer_ != nullptr)
          this->is_professional_timer_->publish_state(*res->is_professional_timer);
        if (res->brush_time_seconds.has_value() && this->brush_time_seconds_ != nullptr)
          this->brush_time_seconds_->publish_state(*res->brush_time_seconds);
        if (res->mode.has_value() && this->mode_ != nullptr)
          this->mode_->publish_state(*res->mode);
        if (res->sector.has_value() && this->sector_ != nullptr)
          this->sector_->publish_state(*res->sector);
        if (res->smiley.has_value() && this->smiley_ != nullptr)
          this->smiley_->publish_state(*res->smiley);

        return true;
      }

      void dump_config() override;
      float get_setup_priority() const override { return setup_priority::DATA; }

      void set_protocol_version(sensor::Sensor *protocol_version) {
        protocol_version_ = protocol_version;
      }
      void set_type_id(sensor::Sensor *type_id) {
        type_id_ = type_id;
      }
      void set_fw_version(sensor::Sensor *fw_version) {
        fw_version_ = fw_version;
      }
      void set_state(sensor::Sensor *state) {
        state_ = state;
      }
      void set_is_high_pressure(sensor::Sensor *is_high_pressure) {
        is_high_pressure_ = is_high_pressure;
      }
      void set_is_reduced_motor(sensor::Sensor *is_reduced_motor) {
        is_reduced_motor_ = is_reduced_motor;
      }
      void set_is_professional_timer(sensor::Sensor *is_professional_timer) {
        is_professional_timer_ = is_professional_timer;
      }
      void set_brush_time_seconds(sensor::Sensor *brush_time_seconds) {
        brush_time_seconds_ = brush_time_seconds;
      }
      void set_mode(sensor::Sensor *mode) {
        mode_ = mode;
      }
      void set_sector(sensor::Sensor *sector) {
        sector_ = sector;
      }
      void set_smiley(sensor::Sensor *smiley) {
        smiley_ = smiley;
      }

      protected:
      uint64_t address_;
      sensor::Sensor *protocol_version_{nullptr};
      sensor::Sensor *type_id_{nullptr};
      sensor::Sensor *fw_version_{nullptr};
      sensor::Sensor *state_{nullptr};
      sensor::Sensor *is_high_pressure_{nullptr};
      sensor::Sensor *is_reduced_motor_{nullptr};
      sensor::Sensor *is_professional_timer_{nullptr};
      sensor::Sensor *brush_time_seconds_{nullptr};
      sensor::Sensor *mode_{nullptr};
      sensor::Sensor *sector_{nullptr};
      sensor::Sensor *smiley_{nullptr};
    };

  }  // namespace oralb_brush
}  // namespace esphome

#endif
