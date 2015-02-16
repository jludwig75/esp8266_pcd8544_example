

#include "ets_sys.h"
#include "osapi.h"
#include "c_types.h"
#include "gpio.h"
#include "os_type.h"
#include "user_config.h"
#include "user_interface.h"
#include "stdout/stdout.h"
#include "pcd8544/pcd8544.h"

static uint8_t openhardware_logo[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xe0,0xe0,0xe0,0xc0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0xe0,0xe0,0xe0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x1f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x1e,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xc0,0xc0,0xc0,0xe0,0xe0,0xe0,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x3f,0x1f,0x1f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x1f,0x3f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xf0,0xe0,0xe0,0xe0,0xc0,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x7f,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe1,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xe1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,0x7f,0x7f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x1e,0x00,0x00,0x00,0x00,0x00,0x06,0x1e,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xcf,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x1f,0x3f,0x7f,0xff,0xff,0xff,0x7f,0x7f,0x3f,0x3f,0x1f,0x3f,0x3f,0x3f,0x0f,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0f,0x3f,0x3f,0x3f,0x1f,0x3f,0x3f,0x7f,0xff,0xff,0xff,0xff,0x3f,0x3f,0x1e,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

#define user_procLcdUpdatePeriod      1000
#define user_procTaskPrio        0
#define user_procTaskQueueLen    1

static volatile os_timer_t loop_timer;
os_event_t user_procTaskQueue[user_procTaskQueueLen];
static PCD8544_Settings pcd8544_settings;

void user_init(void);
static void loop(os_event_t *events);
static void nop_procTask(os_event_t *events);

//Main code function
static void ICACHE_FLASH_ATTR
loop(os_event_t *events) {
  static bool toggle = true;
  static uint32_t loopIterations = 0;
  loopIterations+=1;
  if (loopIterations < 3) {
    PCD8544_lcdImage(openhardware_logo);
  } else if (loopIterations == 3){
    PCD8544_lcdClear();
  } else {
    os_printf("Updating display\n");
    // Draw a Box
    PCD8544_drawLine();
    int a=0;
    PCD8544_gotoXY(17,1);
    // Put text in Box
    PCD8544_lcdPrint("ESP8266");
    PCD8544_gotoXY(24,3);
    if (toggle){
      PCD8544_lcdCharacter('H');
      PCD8544_lcdCharacter('E');
      PCD8544_lcdCharacter('L');
      PCD8544_lcdCharacter('L');
      PCD8544_lcdCharacter('O');
      PCD8544_lcdCharacter(' ');
      PCD8544_lcdCharacter('=');
      // Draw + at this position
      PCD8544_gotoXY(10,3);
      PCD8544_lcdCharacter('=');
      os_delay_us(50000);
    } else {
      PCD8544_gotoXY(24,3);
      PCD8544_lcdCharacter('h');
      PCD8544_lcdCharacter('e');
      PCD8544_lcdCharacter('l');
      PCD8544_lcdCharacter('l');
      PCD8544_lcdCharacter('o');
      PCD8544_lcdCharacter(' ');
      PCD8544_lcdCharacter('-');
      // Draw - at this position
      PCD8544_gotoXY(10,3);
      PCD8544_lcdCharacter('-');
      os_delay_us(50000);
    }
    toggle = !toggle;
  }
}

/**
 * Setup program. When user_init runs the debug printouts will not always
 * show on the serial console. So i run the inits in here, 2 seconds later.
 */
static void ICACHE_FLASH_ATTR
setup(void) {
  pcd8544_settings.lcdVop = 0xB1;
  pcd8544_settings.tempCoeff = 0x04;
  pcd8544_settings.biasMode = 0x14;
  pcd8544_settings.inverse = false;

  pcd8544_settings.resetPin = 4;
  pcd8544_settings.scePin = 5;
  //pcd8544_settings.resetPin = 0;
  //pcd8544_settings.scePin = 2;

  pcd8544_settings.dcPin = 12;
  pcd8544_settings.sdinPin = 13;
  pcd8544_settings.sclkPin = 14;

  PCD8544_init(&pcd8544_settings);
  os_printf("pcd8544 lcd initiated\n");

  // Start loop timer
  os_timer_disarm(&loop_timer);
  os_timer_setfn(&loop_timer, (os_timer_func_t *) loop, NULL);
  os_timer_arm(&loop_timer, user_procLcdUpdatePeriod, true);
}

//Do nothing function
static void ICACHE_FLASH_ATTR
nop_procTask(os_event_t *events) {
  os_delay_us(10);
}

//Init function 
void ICACHE_FLASH_ATTR
user_init(void)
{
  // Make uart0 work with just the TX pin. Baud:115200,n,8,1
  // The RX pin is now free for GPIO use.
  stdout_init();

  //Set station mode
  //wifi_set_opmode(NULL_MODE); // NULL_MODE will crash the system under 0.9.5. It works with 0.9.4.

  //if you flash your device with code that sets NULL_MODE it will remain in the system
  //until you flash the device with code that actively sets opmode to something useful.

  os_timer_disarm(&loop_timer);

  // Start setup timer
  os_timer_setfn(&loop_timer, (os_timer_func_t *) setup, NULL);
  os_timer_arm(&loop_timer, user_procLcdUpdatePeriod*2, false);

  //Start no-operation os task
  system_os_task(nop_procTask, user_procTaskPrio, user_procTaskQueue, user_procTaskQueueLen);
  system_os_post(user_procTaskPrio, 0, 0);
}
