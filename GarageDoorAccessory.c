#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
	printf("accessory identify\n");
}

homekit_characteristic_t homeKitGarage = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t homeKitCharacteristicName = HOMEKIT_CHARACTERISTIC_(NAME, "Garage Door");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(
      .id = 1, 
      .category = homekit_accessory_category_garage, 
      .services = (homekit_service_t *[]
    ) {
      HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
          HOMEKIT_CHARACTERISTIC(NAME, "Garage Door"),
          HOMEKIT_CHARACTERISTIC(MANUFACTURER, "William Lumley"),
          HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "0123456"),
          HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266 MINI"),
          HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
          HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
          NULL
      }
    ),
		HOMEKIT_SERVICE(SWITCH, .primary=true, .characteristics=(homekit_characteristic_t*[]){
			&homeKitGarage,
			&homeKitCharacteristicName,
			NULL
		}),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
		.accessories = accessories,
		.password = "111-11-111"
};


