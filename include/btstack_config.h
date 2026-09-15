#ifndef _BTSTACK_CONFIG_H
#define _BTSTACK_CONFIG_H

// System Properties
#define HAVE_ASSERT

// Embedded Platform Properties
#define HAVE_EMBEDDED_TIME_MS

// BTstack properties
#define ENABLE_SOFTWARE_AES128
#define ENABLE_LE_PERIPHERAL
#define ENABLE_PRINTF_HEXDUMP

// Memory configuration directives
#define HCI_ACL_PAYLOAD_SIZE 10000
#define MAX_NR_HCI_CONNECTIONS 2
#define MAX_ATT_DB_SIZE 512

// Non-volatile memory directives
#define NVM_NUM_DEVICE_DB_ENTRIES 10

#endif