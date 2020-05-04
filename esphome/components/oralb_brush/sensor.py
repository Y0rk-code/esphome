import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, esp32_ble_tracker
from esphome.const import CONF_MAC_ADDRESS, CONF_PROTOCOL_VERSION, CONF_TYPE_ID, CONF_FW_VERSION, CONF_IS_HIGH_PRESSURE, \
    CONF_IS_REDUCED_MOTOR, CONF_IS_PROFESSIONAL_TIMER, CONF_BRUSH_TIME_SECONDS, CONF_MODE, \
    CONF_SECTOR, CONF_SMILEY, UNIT_EMPTY, CONF_ID, ICON_EMPTY, CONF_STATE

DEPENDENCIES = ['esp32_ble_tracker']
AUTO_LOAD = ['oralb_ble']

oralb_brush_ns = cg.esphome_ns.namespace('oralb_brush')
OralbBrush = oralb_brush_ns.class_(
    'OralbBrush', esp32_ble_tracker.ESPBTDeviceListener, cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(OralbBrush),
    cv.Required(CONF_MAC_ADDRESS): cv.mac_address,
    cv.Optional(CONF_PROTOCOL_VERSION): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_TYPE_ID): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_FW_VERSION): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_STATE): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_IS_HIGH_PRESSURE): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_IS_REDUCED_MOTOR): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_IS_PROFESSIONAL_TIMER): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_BRUSH_TIME_SECONDS): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_MODE): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_SECTOR): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
    cv.Optional(CONF_SMILEY): sensor.sensor_schema(UNIT_EMPTY, ICON_EMPTY, 0),
}).extend(esp32_ble_tracker.ESP_BLE_DEVICE_SCHEMA).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield esp32_ble_tracker.register_ble_device(var, config)

    cg.add(var.set_address(config[CONF_MAC_ADDRESS].as_hex))

    if CONF_PROTOCOL_VERSION in config:
        sens = yield sensor.new_sensor(config[CONF_PROTOCOL_VERSION])
        cg.add(var.set_protocol_version(sens))

    if CONF_TYPE_ID in config:
        sens = yield sensor.new_sensor(config[CONF_TYPE_ID])
        cg.add(var.set_type_id(sens))

    if CONF_FW_VERSION in config:
        sens = yield sensor.new_sensor(config[CONF_FW_VERSION])
        cg.add(var.set_fw_version(sens))

    if CONF_STATE in config:
        sens = yield sensor.new_sensor(config[CONF_STATE])
        cg.add(var.set_state(sens))

    if CONF_IS_HIGH_PRESSURE in config:
        sens = yield sensor.new_sensor(config[CONF_IS_HIGH_PRESSURE])
        cg.add(var.set_is_high_pressure(sens))

    if CONF_IS_REDUCED_MOTOR in config:
        sens = yield sensor.new_sensor(config[CONF_IS_REDUCED_MOTOR])
        cg.add(var.set_is_reduced_motor(sens))

    if CONF_IS_PROFESSIONAL_TIMER in config:
        sens = yield sensor.new_sensor(config[CONF_IS_PROFESSIONAL_TIMER])
        cg.add(var.set_is_professional_timer(sens))

    if CONF_BRUSH_TIME_SECONDS in config:
        sens = yield sensor.new_sensor(config[CONF_BRUSH_TIME_SECONDS])
        cg.add(var.set_brush_time_seconds(sens))

    if CONF_MODE in config:
        sens = yield sensor.new_sensor(config[CONF_MODE])
        cg.add(var.set_mode(sens))

    if CONF_SMILEY in config:
        sens = yield sensor.new_sensor(config[CONF_SMILEY])
        cg.add(var.set_smiley(sens))
