# Multi_ADV_FixAddr

This example shows how to create 10 iBeacons using a predefined Advertising Address. 

It takes advantage of the API sl_bt_advertiser_set_random_address and it uses option 3, which allows for Private non-resolvable random address. This type can only be used for non-connectable advertising.

There are some rules for the random address defined in the Bluetooth Core Specification. As an example the address 11:22:33:44:55:66 can be used because it starts with 0b00 (two most significant bits are zeros), so it can be set as private non-resolvable random address (address type 3) with non-connectable advertisement.


Board: Silicon Labs EFR32xG21 Radio Board (BRD4181A) + Wireless Starter Kit Mainboard Device: EFR32MG21A010F1024IM32 
Compiler: ARM GNU GCC 7.2.1
Silicon Labs SDK: 3.1.2
