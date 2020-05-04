#include "oralb_brush.h"
#include "esphome/core/log.h"

#ifdef ARDUINO_ARCH_ESP32

namespace esphome {
  namespace oralb_brush {

    static const char *TAG = "oralb_brush";

    void OralbBrush::dump_config() {
      ESP_LOGCONFIG(TAG, "OralbBrush");
      LOG_SENSOR("  ", "protocol_version", this->protocol_version_);
      LOG_SENSOR("  ", "type_id", this->type_id_);
      LOG_SENSOR("  ", "fw_version", this->fw_version_);
      LOG_SENSOR("  ", "state", this->state_);
      LOG_SENSOR("  ", "is_high_pressure", this->is_high_pressure_);
      LOG_SENSOR("  ", "is_reduced_motor", this->is_reduced_motor_);
      LOG_SENSOR("  ", "is_professional_timer", this->is_professional_timer_);
      LOG_SENSOR("  ", "brush_time_seconds", this->brush_time_seconds_);
      LOG_SENSOR("  ", "mode", this->mode_);
      LOG_SENSOR("  ", "sector", this->sector_);
      LOG_SENSOR("  ", "smiley", this->smiley_);
    }

  }  // namespace oralb_brush
}  // namespace esphome

#endif
