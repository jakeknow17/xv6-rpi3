// Physical memory layout

// Addresses found in BCM2837 ARM Peripherals Document
// All addresses in that document are bus addresses, starting with 0x7E.
// To convert a bus address to physical address: 0x7Exxxxxx -> 0x3Fxxxxxx

#define MMIO_BASE       0x3F000000L

// Found in Section 2 - Auxiliaries: UART1 & SPI1, SPI2
#define AUX_IRQ             ((volatile unsigned int*)(MMIO_BASE+0x00215000L)) // Auxiliary Interrupt status
#define AUX_ENABLES         ((volatile unsigned int*)(MMIO_BASE+0x00215004L)) // Auxiliary enables
#define AUX_MU_IO_REG       ((volatile unsigned int*)(MMIO_BASE+0x00215040L)) // Mini Uart I/O Data
#define AUX_MU_IER_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215044L)) // Mini Uart Interrupt Enable
#define AUX_MU_IIR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215048L)) // Mini Uart Interrupt Identify
#define AUX_MU_LCR_REG      ((volatile unsigned int*)(MMIO_BASE+0x0021504CL)) // Mini Uart Line Control
#define AUX_MU_MCR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215050L)) // Mini Uart Modem Control
#define AUX_MU_LSR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215054L)) // Mini Uart Line Status
#define AUX_MU_MSR_REG      ((volatile unsigned int*)(MMIO_BASE+0x00215058L)) // Mini Uart Modem Status
#define AUX_MU_SCRATCH      ((volatile unsigned int*)(MMIO_BASE+0x0021505CL)) // Mini Uart Scratch
#define AUX_MU_CNTL_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215060L)) // Mini Uart Extra Control
#define AUX_MU_STAT_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215064L)) // Mini Uart Extra Status
#define AUX_MU_BAUD_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215068L)) // Mini Uart Baudrate
#define AUX_SPI0_CNTL0_REG  ((volatile unsigned int*)(MMIO_BASE+0x00215080L)) // SPI 1 Control register 0
#define AUX_SPI0_CNTL1_REG  ((volatile unsigned int*)(MMIO_BASE+0x00215084L)) // SPI 1 Control register 1
#define AUX_SPI0_STAT_REG   ((volatile unsigned int*)(MMIO_BASE+0x00215088L)) // SPI 1 Status
#define AUX_SPI0_IO_REG     ((volatile unsigned int*)(MMIO_BASE+0x00215090L)) // SPI 1 Data
#define AUX_SPI0_PEEK_REG   ((volatile unsigned int*)(MMIO_BASE+0x00215094L)) // SPI 1 Peek
#define AUX_SPI1_CNTL0_REG  ((volatile unsigned int*)(MMIO_BASE+0x002150C0L)) // SPI 2 Control register 0
#define AUX_SPI1_CNTL1_REG  ((volatile unsigned int*)(MMIO_BASE+0x002150C4L)) // SPI 2 Control register 1
#define AUX_SPI1_STAT_REG   ((volatile unsigned int*)(MMIO_BASE+0x002150C8L)) // SPI 2 Status
#define AUX_SPI1_IO_REG     ((volatile unsigned int*)(MMIO_BASE+0x002150D0L)) // SPI 2 Data
#define AUX_SPI1_PEEK_REG   ((volatile unsigned int*)(MMIO_BASE+0x002150D4L)) // SPI 2 Peek


// Found in Section 6 - General Purpose I/O (GPIO)
#define GPFSEL0         ((volatile unsigned int*)(MMIO_BASE+0x00200000L)) // GPIO Function Select 0
#define GPFSEL1         ((volatile unsigned int*)(MMIO_BASE+0x00200004L)) // GPIO Function Select 1
#define GPFSEL2         ((volatile unsigned int*)(MMIO_BASE+0x00200008L)) // GPIO Function Select 2
#define GPFSEL3         ((volatile unsigned int*)(MMIO_BASE+0x0020000CL)) // GPIO Function Select 3
#define GPFSEL4         ((volatile unsigned int*)(MMIO_BASE+0x00200010L)) // GPIO Function Select 4
#define GPFSEL5         ((volatile unsigned int*)(MMIO_BASE+0x00200014L)) // GPIO Function Select 5
#define GPSET0          ((volatile unsigned int*)(MMIO_BASE+0x0020001CL)) // GPIO Pin Output Set 0
#define GPSET1          ((volatile unsigned int*)(MMIO_BASE+0x00200020L)) // GPIO Pin Output Set 1
#define GPCLR0          ((volatile unsigned int*)(MMIO_BASE+0x00200028L)) // GPIO Pin Output Clear 0
#define GPCLR1          ((volatile unsigned int*)(MMIO_BASE+0x0020002CL)) // GPIO Pin Output Clear 1
#define GPLEV0          ((volatile unsigned int*)(MMIO_BASE+0x00200034L)) // GPIO Pin Level 0
#define GPLEV1          ((volatile unsigned int*)(MMIO_BASE+0x00200038L)) // GPIO Pin Level 1
#define GPEDS0          ((volatile unsigned int*)(MMIO_BASE+0x00200040L)) // GPIO Pin Event Detect Status 0
#define GPEDS1          ((volatile unsigned int*)(MMIO_BASE+0x00200044L)) // GPIO Pin Event Detect Status 1
#define GPREN0          ((volatile unsigned int*)(MMIO_BASE+0x0020004CL)) // GPIO Pin Rising Edge Detect Enable 0
#define GPREN1          ((volatile unsigned int*)(MMIO_BASE+0x00200050L)) // GPIO Pin Rising Edge Detect Enable 1
#define GPFEN0          ((volatile unsigned int*)(MMIO_BASE+0x00200058L)) // GPIO Pin Falling Edge Detect Enable 0
#define GPFEN1          ((volatile unsigned int*)(MMIO_BASE+0x0020005CL)) // GPIO Pin Falling Edge Detect Enable 1
#define GPHEN0          ((volatile unsigned int*)(MMIO_BASE+0x00200064L)) // GPIO Pin High Detect Enable 0
#define GPHEN1          ((volatile unsigned int*)(MMIO_BASE+0x00200068L)) // GPIO Pin High Detect Enable 1
#define GPLEN0          ((volatile unsigned int*)(MMIO_BASE+0x00200070L)) // GPIO Pin Low Detect Enable 0
#define GPLEN1          ((volatile unsigned int*)(MMIO_BASE+0x00200074L)) // GPIO Pin Low Detect Enable 1
#define GPAREN0         ((volatile unsigned int*)(MMIO_BASE+0x0020007CL)) // GPIO Pin Async. Rising Edge Detect 0
#define GPAREN1         ((volatile unsigned int*)(MMIO_BASE+0x00200080L)) // GPIO Pin Async. Rising Edge Detect 1
#define GPAFEN0         ((volatile unsigned int*)(MMIO_BASE+0x00200088L)) // GPIO Pin Async. Falling Edge Detect 0
#define GPAFEN1         ((volatile unsigned int*)(MMIO_BASE+0x0020008CL)) // GPIO Pin Async. Falling Edge Detect 1
#define GPPUD           ((volatile unsigned int*)(MMIO_BASE+0x00200094L)) // GPIO Pin Pull-up/down Enable
#define GPPUDCLK0       ((volatile unsigned int*)(MMIO_BASE+0x00200098L)) // GPIO Pin Pull-up/down Enable Clock 0
#define GPPUDCLK1       ((volatile unsigned int*)(MMIO_BASE+0x0020009CL)) // GPIO Pin Pull-up/down Enable Clock 1

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
