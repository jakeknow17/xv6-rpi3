#ifndef MEMLAYOUT_H
#define MEMLAYOUT_H

// Physical memory layout

// Addresses found in BCM2837 ARM Peripherals Document
// All addresses in that document are bus addresses, starting with 0x7E.
// To convert a bus address to physical address: 0x7Exxxxxx -> 0x3Fxxxxxx

#define MMIO_BASE       0x3F000000L

// Found in Section 2 - Auxiliaries: UART1 & SPI1, SPI2
#define AUX_IRQ             ((volatile unsigned int*)(MMIO_BASE+0x00215000)) // Auxiliary Interrupt status
#define AUX_ENABLES         ((volatile unsigned int*)(MMIO_BASE+0x00215004)) // Auxiliary enables
#define AUX_MU_IO_REG       ((volatile unsigned int*)(MMIO_BASE+0x00215040)) // Mini Uart I/O Data
#define AUX_MU_IER_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215044)) // Mini Uart Interrupt Enable
#define AUX_MU_IIR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215048)) // Mini Uart Interrupt Identify
#define AUX_MU_LCR_REG      ((volatile unsigned int*)(MMIO_BASE+0x0021504C)) // Mini Uart Line Control
#define AUX_MU_MCR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215050)) // Mini Uart Modem Control
#define AUX_MU_LSR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215054)) // Mini Uart Line Status
#define AUX_MU_MSR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215058)) // Mini Uart Modem Status
#define AUX_MU_SCRATCH      ((volatile unsigned int*)(MMIO_BASE+0x0021505C)) // Mini Uart Scratch
#define AUX_MU_CNTL_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215060)) // Mini Uart Extra Control
#define AUX_MU_STAT_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215064)) // Mini Uart Extra Status
#define AUX_MU_BAUD_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215068)) // Mini Uart Baudrate
#define AUX_SPI0_CNTL0_REG  ((volatile unsigned int*)(MMIO_BASE+0x00215080)) // SPI 1 Control register 0
#define AUX_SPI0_CNTL1_REG  ((volatile unsigned int*)(MMIO_BASE+0x00215084)) // SPI 1 Control register 1
#define AUX_SPI0_STAT_REG   ((volatile unsigned int*)(MMIO_BASE+0x00215088)) // SPI 1 Status
#define AUX_SPI0_IO_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215090)) // SPI 1 Data
#define AUX_SPI0_PEEK_REG   ((volatile unsigned int*)(MMIO_BASE+0x00215094)) // SPI 1 Peek
#define AUX_SPI1_CNTL0_REG  ((volatile unsigned int*)(MMIO_BASE+0x002150C0)) // SPI 2 Control register 0
#define AUX_SPI1_CNTL1_REG  ((volatile unsigned int*)(MMIO_BASE+0x002150C4)) // SPI 2 Control register 1
#define AUX_SPI1_STAT_REG   ((volatile unsigned int*)(MMIO_BASE+0x002150C8)) // SPI 2 Status
#define AUX_SPI1_IO_REG     ((volatile unsigned int*)(MMIO_BASE+0x002150D0)) // SPI 2 Data
#define AUX_SPI1_PEEK_REG   ((volatile unsigned int*)(MMIO_BASE+0x002150D4)) // SPI 2 Peek

// Found in Section 5 - External Mass Media Controller
#define EMMC_ARG2           ((volatile unsigned int*)(MMIO_BASE+0x00300000)) // ACMD23 Argument 
#define EMMC_BLKSIZECNT     ((volatile unsigned int*)(MMIO_BASE+0x00300004)) // Block Size and Count 
#define EMMC_ARG1           ((volatile unsigned int*)(MMIO_BASE+0x00300008)) // Argument 
#define EMMC_CMDTM          ((volatile unsigned int*)(MMIO_BASE+0x0030000c)) // Command and Transfer Mode 
#define EMMC_RESP0          ((volatile unsigned int*)(MMIO_BASE+0x00300010)) // Response bits 31 : 0 
#define EMMC_RESP1          ((volatile unsigned int*)(MMIO_BASE+0x00300014)) // Response bits 63 : 32 
#define EMMC_RESP2          ((volatile unsigned int*)(MMIO_BASE+0x00300018)) // Response bits 95 : 64 
#define EMMC_RESP3          ((volatile unsigned int*)(MMIO_BASE+0x0030001c)) // Response bits 127 : 96 
#define EMMC_DATA           ((volatile unsigned int*)(MMIO_BASE+0x00300020)) // Data 
#define EMMC_STATUS         ((volatile unsigned int*)(MMIO_BASE+0x00300024)) // Status 
#define EMMC_CONTROL0       ((volatile unsigned int*)(MMIO_BASE+0x00300028)) // Host Configuration bits 
#define EMMC_CONTROL1       ((volatile unsigned int*)(MMIO_BASE+0x0030002c)) // Host Configuration bits 
#define EMMC_INTERRUPT      ((volatile unsigned int*)(MMIO_BASE+0x00300030)) // Interrupt Flags 
#define EMMC_IRPT_MASK      ((volatile unsigned int*)(MMIO_BASE+0x00300034)) // Interrupt Flag Enable 
#define EMMC_IRPT_EN        ((volatile unsigned int*)(MMIO_BASE+0x00300038)) // Interrupt Generation Enable 
#define EMMC_CONTROL2       ((volatile unsigned int*)(MMIO_BASE+0x0030003c)) // Host Configuration bits 
#define EMMC_FORCE_IRPT     ((volatile unsigned int*)(MMIO_BASE+0x00300050)) // Force Interrupt Event 
#define EMMC_BOOT_TIMEOUT   ((volatile unsigned int*)(MMIO_BASE+0x00300070)) // Timeout in boot mode 
#define EMMC_DBG_SEL        ((volatile unsigned int*)(MMIO_BASE+0x00300074)) // Debug Bus Configuration 
#define EMMC_EXRDFIFO_CFG   ((volatile unsigned int*)(MMIO_BASE+0x00300080)) // Extension FIFO Configuration 
#define EMMC_EXRDFIFO_EN    ((volatile unsigned int*)(MMIO_BASE+0x00300084)) // Extension FIFO Enable 
#define EMMC_TUNE_STEP      ((volatile unsigned int*)(MMIO_BASE+0x00300088)) // Delay per card clock tuning step 
#define EMMC_TUNE_STEPS_STD ((volatile unsigned int*)(MMIO_BASE+0x0030008c)) // Card clock tuning steps for SDR 
#define EMMC_TUNE_STEPS_DDR ((volatile unsigned int*)(MMIO_BASE+0x00300090)) // Card clock tuning steps for DDR 
#define EMMC_SPI_INT_SPT    ((volatile unsigned int*)(MMIO_BASE+0x003000f0)) // SPI Interrupt Support 
#define EMMC_SLOTISR_VER    ((volatile unsigned int*)(MMIO_BASE+0x003000fc)) // Slot Interrupt Status and Version 

// Found in Section 6 - General Purpose I/O (GPIO)
#define GPFSEL0         ((volatile unsigned int*)(MMIO_BASE+0x00200000)) // GPIO Function Select 0
#define GPFSEL1         ((volatile unsigned int*)(MMIO_BASE+0x00200004)) // GPIO Function Select 1
#define GPFSEL2         ((volatile unsigned int*)(MMIO_BASE+0x00200008)) // GPIO Function Select 2
#define GPFSEL3         ((volatile unsigned int*)(MMIO_BASE+0x0020000C)) // GPIO Function Select 3
#define GPFSEL4         ((volatile unsigned int*)(MMIO_BASE+0x00200010)) // GPIO Function Select 4
#define GPFSEL5         ((volatile unsigned int*)(MMIO_BASE+0x00200014)) // GPIO Function Select 5
#define GPSET0          ((volatile unsigned int*)(MMIO_BASE+0x0020001C)) // GPIO Pin Output Set 0
#define GPSET1          ((volatile unsigned int*)(MMIO_BASE+0x00200020)) // GPIO Pin Output Set 1
#define GPCLR0          ((volatile unsigned int*)(MMIO_BASE+0x00200028)) // GPIO Pin Output Clear 0
#define GPCLR1          ((volatile unsigned int*)(MMIO_BASE+0x0020002C)) // GPIO Pin Output Clear 1
#define GPLEV0          ((volatile unsigned int*)(MMIO_BASE+0x00200034)) // GPIO Pin Level 0
#define GPLEV1          ((volatile unsigned int*)(MMIO_BASE+0x00200038)) // GPIO Pin Level 1
#define GPEDS0          ((volatile unsigned int*)(MMIO_BASE+0x00200040)) // GPIO Pin Event Detect Status 0
#define GPEDS1          ((volatile unsigned int*)(MMIO_BASE+0x00200044)) // GPIO Pin Event Detect Status 1
#define GPREN0          ((volatile unsigned int*)(MMIO_BASE+0x0020004C)) // GPIO Pin Rising Edge Detect Enable 0
#define GPREN1          ((volatile unsigned int*)(MMIO_BASE+0x00200050)) // GPIO Pin Rising Edge Detect Enable 1
#define GPFEN0          ((volatile unsigned int*)(MMIO_BASE+0x00200058)) // GPIO Pin Falling Edge Detect Enable 0
#define GPFEN1          ((volatile unsigned int*)(MMIO_BASE+0x0020005C)) // GPIO Pin Falling Edge Detect Enable 1
#define GPHEN0          ((volatile unsigned int*)(MMIO_BASE+0x00200064)) // GPIO Pin High Detect Enable 0
#define GPHEN1          ((volatile unsigned int*)(MMIO_BASE+0x00200068)) // GPIO Pin High Detect Enable 1
#define GPLEN0          ((volatile unsigned int*)(MMIO_BASE+0x00200070)) // GPIO Pin Low Detect Enable 0
#define GPLEN1          ((volatile unsigned int*)(MMIO_BASE+0x00200074)) // GPIO Pin Low Detect Enable 1
#define GPAREN0         ((volatile unsigned int*)(MMIO_BASE+0x0020007C)) // GPIO Pin Async. Rising Edge Detect 0
#define GPAREN1         ((volatile unsigned int*)(MMIO_BASE+0x00200080)) // GPIO Pin Async. Rising Edge Detect 1
#define GPAFEN0         ((volatile unsigned int*)(MMIO_BASE+0x00200088)) // GPIO Pin Async. Falling Edge Detect 0
#define GPAFEN1         ((volatile unsigned int*)(MMIO_BASE+0x0020008C)) // GPIO Pin Async. Falling Edge Detect 1
#define GPPUD           ((volatile unsigned int*)(MMIO_BASE+0x00200094)) // GPIO Pin Pull-up/down Enable
#define GPPUDCLK0       ((volatile unsigned int*)(MMIO_BASE+0x00200098)) // GPIO Pin Pull-up/down Enable Clock 0
#define GPPUDCLK1       ((volatile unsigned int*)(MMIO_BASE+0x0020009C)) // GPIO Pin Pull-up/down Enable Clock 1

// Found in Section 12 - System Timer
#define SYS_TIMER_CS    ((volatile unsigned int*)(MMIO_BASE+0x00003000)) // System Timer Control/Status
#define SYS_TIMER_CLO   ((volatile unsigned int*)(MMIO_BASE+0x00003004)) // System Timer Counter Lower 32 bits
#define SYS_TIMER_CHI   ((volatile unsigned int*)(MMIO_BASE+0x00003008)) // System Timer Counter Higher 32 bits
#define SYS_TIMER_C0    ((volatile unsigned int*)(MMIO_BASE+0x0000300c)) // System Timer Compare 0
#define SYS_TIMER_C1    ((volatile unsigned int*)(MMIO_BASE+0x00003010)) // System Timer Compare 1
#define SYS_TIMER_C2    ((volatile unsigned int*)(MMIO_BASE+0x00003014)) // System Timer Compare 2
#define SYS_TIMER_C3    ((volatile unsigned int*)(MMIO_BASE+0x00003018)) // System Timer Compare 3

// Found in Section 13 - UART
#define PL011_DR        ((volatile unsigned int*)(MMIO_BASE+0x00201000)) // Data Register
#define PL011_RSRECR    ((volatile unsigned int*)(MMIO_BASE+0x00201040)) // RSRECR
#define PL011_FR        ((volatile unsigned int*)(MMIO_BASE+0x00201018)) // Flag register
#define PL011_ILPR      ((volatile unsigned int*)(MMIO_BASE+0x00201020)) // not in use
#define PL011_IBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201024)) // Integer Baud rate divisor
#define PL011_FBRD      ((volatile unsigned int*)(MMIO_BASE+0x00201028)) // Fractional Baud rate divisor
#define PL011_LCRH      ((volatile unsigned int*)(MMIO_BASE+0x0020102c)) // Line Control register
#define PL011_CR        ((volatile unsigned int*)(MMIO_BASE+0x00201030)) // Control register
#define PL011_IFLS      ((volatile unsigned int*)(MMIO_BASE+0x00201034)) // Interupt FIFO Level Select Register
#define PL011_IMSC      ((volatile unsigned int*)(MMIO_BASE+0x00201038)) // Interupt Mask Set Clear Register
#define PL011_RIS       ((volatile unsigned int*)(MMIO_BASE+0x0020103c)) // Raw Interupt Status Register
#define PL011_MIS       ((volatile unsigned int*)(MMIO_BASE+0x00201040)) // Masked Interupt Status Register
#define PL011_ICR       ((volatile unsigned int*)(MMIO_BASE+0x00201044)) // Interupt Clear Register
#define PL011_DMACR     ((volatile unsigned int*)(MMIO_BASE+0x00201048)) // DMA Control Register
#define PL011_ITCR      ((volatile unsigned int*)(MMIO_BASE+0x00201080)) // Test Control register
#define PL011_ITIP      ((volatile unsigned int*)(MMIO_BASE+0x00201084)) // Integration test input reg
#define PL011_ITOP      ((volatile unsigned int*)(MMIO_BASE+0x00201088)) // Integration test output reg
#define PL011_TDR       ((volatile unsigned int*)(MMIO_BASE+0x0020108c)) // Test Data reg

#endif /* MEMLAYOUT_H */