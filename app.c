/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_bluetooth.h"
#include "app_assert.h"
#include "gatt_db.h"
#include "app.h"

// Macros.
#define UINT16_TO_BYTES(n)            ((uint8_t) (n)), ((uint8_t)((n) >> 8))
#define UINT16_TO_BYTE0(n)            ((uint8_t) (n))
#define UINT16_TO_BYTE1(n)            ((uint8_t) ((n) >> 8))



static uint8_t iBeacon_1 = 0xa1;
static uint8_t iBeacon_2 = 0xa2;
static uint8_t iBeacon_3 = 0xa3;
static uint8_t iBeacon_4 = 0xa4;
static uint8_t iBeacon_5 = 0xa5;
static uint8_t iBeacon_6 = 0xa6;
static uint8_t iBeacon_7 = 0xa7;
static uint8_t iBeacon_8 = 0xa8;
static uint8_t iBeacon_9 = 0xa9;
static uint8_t iBeacon_10 = 0xaa;

#include "app_log.h"
/**************************************************************************//**
 * Set up a custom advertisement package according to iBeacon specifications.
 * The advertisement package is 30 bytes long.
 * See the iBeacon specification for further details.
 *****************************************************************************/

static void iBeacon_set_Creator(uint8_t iBeacon_set_handle, bd_addr *addr);

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  bd_addr Beacon1;
  sl_status_t sc;
  int16_t ret_power_min, ret_power_max;
  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // Set 0 dBm maximum Transmit Power.
      sc = sl_bt_system_set_tx_power(SL_BT_CONFIG_MIN_TX_POWER, 0,
                                     &ret_power_min, &ret_power_max);

      app_log("Boot\n\r");
      app_assert_status(sc);
      (void)ret_power_min;
      (void)ret_power_max;
      // Initialize iBeacon ADV data.

      Beacon1.addr[0]= 0xee;
      Beacon1.addr[1]= 0xdd;
      Beacon1.addr[2]= 0xcc;
      Beacon1.addr[3]= 0xbb;
      Beacon1.addr[4]= 0x11;
      Beacon1.addr[5]= 0x11;


      iBeacon_set_Creator(iBeacon_1,&Beacon1);

      Beacon1.addr[4]= 0x22;

      iBeacon_set_Creator(iBeacon_2,&Beacon1);

      Beacon1.addr[4]= 0x33;

      iBeacon_set_Creator(iBeacon_3,&Beacon1);

      Beacon1.addr[4]= 0x44;
      iBeacon_set_Creator(iBeacon_4,&Beacon1);

      Beacon1.addr[4]= 0x55;
      iBeacon_set_Creator(iBeacon_5,&Beacon1);

      Beacon1.addr[4]= 0x66;
      iBeacon_set_Creator(iBeacon_6,&Beacon1);

      Beacon1.addr[4]= 0x77;
      iBeacon_set_Creator(iBeacon_7,&Beacon1);

      Beacon1.addr[4]= 0x88;
      iBeacon_set_Creator(iBeacon_8,&Beacon1);

      Beacon1.addr[4]= 0x99;
      iBeacon_set_Creator(iBeacon_9,&Beacon1);

      Beacon1.addr[4]= 0xAA;
      iBeacon_set_Creator(iBeacon_10,&Beacon1);


      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

static void iBeacon_set_Creator(uint8_t iBeacon_set_handle, bd_addr *addr)
{
  sl_status_t sc;
  bd_addr out_addr;


  struct {
    uint8_t flags_len;     // Length of the Flags field.
    uint8_t flags_type;    // Type of the Flags field.
    uint8_t flags;         // Flags field.
    uint8_t mandata_ten;   // Length of the Manufacturer Data field.
    uint8_t mandata_type;  // Type of the Manufacturer Data field.
    uint8_t comp_id[2];    // Company ID field.
    uint8_t beac_type[2];  // Beacon Type field.
    uint8_t uuid[16];      // 128-bit Universally Unique Identifier (UUID). The UUID is an identifier for the company using the beacon.
    uint8_t maj_num[2];    // Beacon major number. Used to group related beacons.
    uint8_t min_num[2];    // Beacon minor number. Used to specify individual beacons within a group.
    uint8_t tx_power;      // The Beacon's measured RSSI at 1 meter distance in dBm. See the iBeacon specification for measurement guidelines.
  }
  bcn_beacon_adv_data
    = {
    // Flag bits - See Bluetooth 4.0 Core Specification , Volume 3, Appendix C, 18.1 for more details on flags.
    2,            // Length of field.
    0x01,         // Type of field.
    0x04 | 0x02,  // Flags: LE General Discoverable Mode, BR/EDR is disabled.

    // Manufacturer specific data.
    26,   // Length of field.
    0xFF, // Type of field.

    // The first two data octets shall contain a company identifier code from
    // the Assigned Numbers - Company Identifiers document.
    // 0x004C = Apple
    { UINT16_TO_BYTES(0x004C) },

    // Beacon type.
    // 0x0215 is iBeacon.
    { UINT16_TO_BYTE1(0x0215), UINT16_TO_BYTE0(0x0215) },

    // 128 bit / 16 byte UUID
    { 0xE2, 0xC5, 0x6D, 0xB5, 0xDF, 0xFB, 0x48, 0xD2, \
      0xB0, 0x60, 0xD0, 0xF5, 0xA7, 0x10, 0x96, 0xE0 },

    // Beacon major number.
    // Set to 34987 and converted to correct format.
    { UINT16_TO_BYTE1(34987), UINT16_TO_BYTE0(34987) },

    // Beacon minor number.
    // Set as 1025 and converted to correct format.
    { UINT16_TO_BYTE1(1025), UINT16_TO_BYTE0(1025) },

    // The Beacon's measured RSSI at 1 meter distance in dBm.
    // 0xD7 is -41dBm
    0xD7
    };

  // Create an advertising set.
  sc = sl_bt_advertiser_create_set(&iBeacon_set_handle);
  app_assert_status(sc);

  // Set custom advertising data.
  sc = sl_bt_advertiser_set_data(iBeacon_set_handle,
                                 0,
                                 sizeof(bcn_beacon_adv_data),
                                 (uint8_t *)(&bcn_beacon_adv_data));
  app_assert_status(sc);

  // Set advertising parameters. 100ms advertisement interval.
  sc = sl_bt_advertiser_set_timing(
    iBeacon_set_handle,
    160,     // min. adv. interval (milliseconds * 1.6)
    160,     // max. adv. interval (milliseconds * 1.6)
    0,       // adv. duration
    0);      // max. num. adv. events
  app_assert_status(sc);

   sc = sl_bt_advertiser_set_random_address ( iBeacon_set_handle,3,*addr,&out_addr) ;

   //app_assert_status(sc);
   app_log("E: 0x%04x", (int)sc);

  // Start advertising in user mode and disable connections.
  sc = sl_bt_advertiser_start(
    iBeacon_set_handle,
    advertiser_user_data,
    advertiser_non_connectable);
  app_assert_status(sc);
}

