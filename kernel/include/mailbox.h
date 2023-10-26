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

// Tags
#define MBOX_VC_GET_FW_REV      0x00000001 // VideoCore - Get firmware revision
#define MBOX_HW_GET_BRD_MODEL   0x00010001 // Hardware - Get board model
#define MBOX_HW_GET_BRD_REV     0x00010002 // Hardware - Get board revision
#define MBOX_HW_GET_BRD_MAC     0x00010003 // Hardware - Get board MAC address
#define MBOX_HW_GET_BRD_SERIAL  0x00010004 // Hardware - Get board serial
#define MBOX_HW_GET_ARM_MEM     0x00010005 // Hardware - Get ARM memory
#define MBOX_HW_GET_VC_MEM      0x00010006 // Hardware - Get VC memory
#define MBOX_HW_GET_CLOCKS      0x00010007 // Hardware - Get clocks
#define MBOX_CFG_GET_CMD_LINE   0x00050001 // Config - Get command line
#define MBOX_SRM_GET_DMA_CHNLS  0x00060001 // Shared Resource Management - Get DMA Channels
#define MBOX_PWR_GET_PWR_STATE  0x00020001 // Power - Get power state
#define MBOX_PWR_GET_TIMING     0x00020002 // Power - Get timing
#define MBOX_PWR_SET_PWR_STATE  0x00020003 // Power - Set timing
#define MBOX_CLK_GET_CLK_STATE  0x00030001 // Clock - Get clock state
#define MBOX_CLK_SET_CLK_STATE  0x00038001 // Clock - Set clock state
#define MBOX_CLK_GET_CLK_RATE   0x00030002 // Clock - Set clock rate
#define MBOX_CLK_SET_CLK_RATE   0x00038002 // Clock - Get clock rate
#define MBOX_CLK_GET_LED_STATUS 0x00030041 // Clock - Get onboard LED status
#define MBOX_CLK_TST_LED_STATUS 0x00034041 // Clock - Test onboard LED status
#define MBOX_CLK_SET_LED_STATUS 0x00038041 // Clock - Set onboard LED status
#define MBOX_CLK_GET_CLK_RATE_M 0x00030047 // Clock - Get clock rate measured

// Device IDs
#define MBOX_DEV_ID_SD_Card     0x00000000
#define MBOX_DEV_ID_UART0       0x00000001
#define MBOX_DEV_ID_UART1       0x00000002
#define MBOX_DEV_ID_USB HCD     0x00000003
#define MBOX_DEV_ID_I2C0        0x00000004
#define MBOX_DEV_ID_I2C1        0x00000005
#define MBOX_DEV_ID_I2C2        0x00000006
#define MBOX_DEV_ID_SPI         0x00000007
#define MBOX_DEV_ID_CCP2TX      0x00000008

// Clock IDs
#define MBOX_CLK_ID_RESERVED    0x000000000
#define MBOX_CLK_ID_EMMC        0x000000001
#define MBOX_CLK_ID_UART        0x000000002
#define MBOX_CLK_ID_ARM         0x000000003
#define MBOX_CLK_ID_CORE        0x000000004
#define MBOX_CLK_ID_V3D         0x000000005
#define MBOX_CLK_ID_H264        0x000000006
#define MBOX_CLK_ID_ISP         0x000000007
#define MBOX_CLK_ID_SDRAM       0x000000008
#define MBOX_CLK_ID_PIXEL       0x000000009
#define MBOX_CLK_ID_PWM         0x00000000a
#define MBOX_CLK_ID_HEVC        0x00000000b
#define MBOX_CLK_ID_EMMC2       0x00000000c
#define MBOX_CLK_ID_M2MC        0x00000000d
#define MBOX_CLK_ID_PIXEL_BVB   0x00000000e

#define MBOX_REQUEST            0x0 // Code to tell a mailbox to process a request
#define MBOX_TAG_LAST           0x0 // Last value in a message buffer

int write_mailbox(unsigned char, unsigned int *);
unsigned long get_board_serial(void);
unsigned int set_device_clock_rate(unsigned int clock_id, unsigned int clock_rate, unsigned int skip_setting_turbo);