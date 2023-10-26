// Mailbox channels
#define MBOX_CH_POWER   0 // power management
#define MBOX_CH_FB      1 // framebuffer
#define MBOX_CH_VUART   2 // virtual UART
#define MBOX_CH_VCHIQ   3 // VCHIQ
#define MBOX_CH_LEDS    4 // LEDs
#define MBOX_CH_BTNS    5 // Buttons
#define MBOX_CH_TOUCH   6 // Touch screen
#define MBOX_CH_COUNT   7 // <unlisted>
#define MBOX_CH_PROP    8 // Property tags

void write_mailbox(unsigned char, unsigned int *);