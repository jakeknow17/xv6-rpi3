#include "types.h"
#include "memlayout.h"
#include "aarch64.h"
#include "mailbox.h"

#define MBOX_BASE       (MMIO_BASE+0xB880)	// Base address for the mailbox registers

#define MBOX0_READ      ((volatile unsigned int*)(MBOX_BASE+0x00)) // Never write to this mailbox
#define MBOX0_POLL      ((volatile unsigned int*)(MBOX_BASE+0x10))
#define MBOX0_SENDER    ((volatile unsigned int*)(MBOX_BASE+0x14))
#define MBOX0_STATUS    ((volatile unsigned int*)(MBOX_BASE+0x18))
#define MBOX0_CONFIG    ((volatile unsigned int*)(MBOX_BASE+0x1C))
#define MBOX1_WRITE     ((volatile unsigned int*)(MBOX_BASE+0x20)) // Never read from this mailbox
#define MBOX1_POLL      ((volatile unsigned int*)(MBOX_BASE+0x30))
#define MBOX1_SENDER    ((volatile unsigned int*)(MBOX_BASE+0x34))
#define MBOX1_STATUS    ((volatile unsigned int*)(MBOX_BASE+0x38))
#define MBOX1_CONFIG    ((volatile unsigned int*)(MBOX_BASE+0x3C))

#define MBOX_SUCCESS    0x80000000 // Failure is all other values
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000


// Makes a mailbox call, using the given channel and data array.
// Blocks until it receives a response. Returns 0 on failure, non-zero on success.
int write_mailbox(uint8 channel, uint32 *data)
{
    // Upper 28 bits contain the address of the buffer (this must be 16-byte aligned).
    // Lower 4 bits contain the mailbox channel.
    uint32 r = (uint32)(((uint64)data & ~0xF) | (channel & 0xF));

    // Wait until the mailbox is empty
	while (*MBOX1_STATUS & MBOX_FULL) { nop(); }

	// Write the value to the requested channel
	*MBOX1_WRITE = r;

    // Wait for a response
    for (;;)
    {
        // Wait until the mailbox is full
        while (*MBOX0_STATUS & MBOX_EMPTY) { nop(); }

        // Check if the message matches the expected channel
        if ((uint8)(*MBOX0_READ & 0xF) == channel)
            return data[1] == MBOX_SUCCESS;
    }
}

// Gets the board's unique serial number with a mailbox call.
uint64 get_board_serial()
{
    __attribute__ ((aligned (16))) uint32 mbox[8];
    mbox[0] = 8*4;                      // length of the full message
    mbox[1] = MBOX_REQUEST;             // this is a request message
    mbox[2] = MBOX_HW_GET_BRD_SERIAL;   // get serial number command
    mbox[3] = 0;                        // request size
    mbox[4] = 8;                        // expected response size
    mbox[5] = 0;                        // clear output buffer for u64
    mbox[6] = 0;
    mbox[7] = MBOX_TAG_LAST;            // final tag in message

    uint64 res = 0;
    if (write_mailbox(MBOX_CH_PROP, mbox))
    {
        res = (uint64)mbox[5];
        res |= ((uint64)mbox[6]) << 32;
        return res;
    }
    else
        res = 1; // qemu always uses a serial number of 0, so set this to 1 to recognize error.
    return res;
}

// Sets the clock rate for a device clock with a mailbox call.
// skip_setting_turbo can be 0 or 1. 1 asks the system to ignore any turbo settings,
// and 0 asks the system to consider turbo settings if configured.
// Returns the new clock rate, or 0 for failure.
uint32 set_device_clock_rate(uint32 clock_id, uint32 clock_rate, uint32 skip_setting_turbo)
{
    __attribute__ ((aligned (16))) uint32 mbox[8];
    mbox[0] = 9*4;                   // length of the message
    mbox[1] = MBOX_REQUEST;          // this is a request message
    mbox[2] = MBOX_CLK_SET_CLK_RATE; // set clock rate command
    mbox[3] = 12;                    // request size
    mbox[4] = 8;                     // expected response size
    mbox[5] = clock_id;
    mbox[6] = clock_rate;
    mbox[7] = skip_setting_turbo;
    mbox[8] = MBOX_TAG_LAST;         // final tag in message
    
    if (write_mailbox(MBOX_CH_PROP, mbox))
        return mbox[6];
    return 0;
}