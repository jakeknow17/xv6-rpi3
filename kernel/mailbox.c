#include "types.h"
#include "memlayout.h"
#include "aarch64.h"
#include "mailbox.h"

#define MAIL_BASE       (MMIO_BASE+0xB880)	// Base address for the mailbox registers

#define MAIL0_READ      ((volatile unsigned int*)(MAIL_BASE+0x00)) // Never write to this mailbox
#define MAIL0_POLL      ((volatile unsigned int*)(MAIL_BASE+0x10))
#define MAIL0_SENDER    ((volatile unsigned int*)(MAIL_BASE+0x14))
#define MAIL0_STATUS    ((volatile unsigned int*)(MAIL_BASE+0x18))
#define MAIL0_CONFIG    ((volatile unsigned int*)(MAIL_BASE+0x1C))
#define MAIL1_WRITE     ((volatile unsigned int*)(MAIL_BASE+0x20)) // Never read from this mailbox
#define MAIL1_POLL      ((volatile unsigned int*)(MAIL_BASE+0x30))
#define MAIL1_SENDER    ((volatile unsigned int*)(MAIL_BASE+0x34))
#define MAIL1_STATUS    ((volatile unsigned int*)(MAIL_BASE+0x38))
#define MAIL1_CONFIG    ((volatile unsigned int*)(MAIL_BASE+0x3C))

#define MAIL_SUCCESS    0x80000000 // Failure is all other values
#define MAIL_FULL       0x80000000
#define MAIL_EMPTY      0x40000000


// Makes a mailbox call, using the given channel and data array.
// Blocks until it receives a response. Returns 0 on failure, non-zero on success.
void write_mailbox(uint8 channel, uint32 *data)
{
    // Upper 28 bits contain the address of the buffer (this must be 16-byte aligned).
    // Lower 4 bits contain the mailbox channel.
    uint32 r = (uint32)(((uint64)data & ~0xF) | (channel & 0xF));

    // Wait until the mailbox is empty
	while (*MAIL1_STATUS & MAIL_FULL) { nop(); } // TODO: Check if this should be MAIL1_STATUS or MAIL0_STATUS

	// Write the value to the requested channel
	*MAIL1_WRITE = r;

    // Wait for a response
    for (;;)
    {
        // Wait until the mailbox is full
        while (*MAIL0_STATUS & MAIL_EMPTY) { nop(); }

        // Check if the message matches the expected channel
        if ((uint8)(*MAIL0_READ & 0xF) == channel)
            return data[1] == MAIL_SUCCESS;
    }
}