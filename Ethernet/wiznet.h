/*
 * WIZNET.h
 *
 * Created: 12/22/2011 9:44:43 AM
 *  Author: Administrator
 */ 

#include <stdint.h>

#ifndef WIZNET_H_
#define WIZNET_H_

// Wiznet W5100 Op Code
#define WIZNET_WRITE_OPCODE 0xF0
#define WIZNET_READ_OPCODE 0x0F

// Wiznet W5100 Memory
#define gS0_RX_BASE 0x6000
#define gS0_TX_BASE 0x4000

#define gSn_RX_MASK(i)		(1<<(((wiznet_read(RMSR) << 6-(2*i))>>6)+10))-1
#define gSn_TX_MASK(i)		(1<<(((wiznet_read(TMSR) << 6-(2*i))>>6)+10))-1

#define gS1_RX_BASE			gS0_RX_BASE + gSn_RX_MASK(0) + 1
#define gS1_TX_BASE         gS0_TX_BASE + gSn_RX_MASK(0) + 1

#define gS2_RX_BASE			gS1_RX_BASE + gSn_RX_MASK(1) + 1
#define gS2_TX_BASE         gS1_TX_BASE + gSn_RX_MASK(1) + 1

#define gS3_RX_BASE			gS2_RX_BASE + gSn_RX_MASK(2) + 1
#define gS3_TX_BASE         gS2_TX_BASE + gSn_RX_MASK(2) + 1

// Wiznet W5100 Register Addresses
#define MR         0x0000      // Mode Register
#define GAR        0x0001      // Gateway Address: 0x0001 to 0x0004
#define SUBR       0x0005      // Subnet mask Address: 0x0005 to 0x0008
#define SAR        0x0009      // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR       0x000F      // Source IP Address: 0x000F to 0x0012
#define RMSR       0x001A      // RX Memory Size Register
#define TMSR       0x001B      // TX Memory Size Register

/* Socket 0 Registers */
#define S0_MR	   0x0400      // Socket 0: Mode Register Address
#define S0_CR	   0x0401      // Socket 0: Command Register Address
#define S0_IR	   0x0402      // Socket 0: Interrupt Register Address
#define S0_SR	   0x0403      // Socket 0: Status Register Address
#define S0_PORT    0x0404      // Socket 0: Source Port: 0x0404 to 0x0405
#define S0_DIPR	   0x040C	   // Socket 0 : Destination IP : 0x040C to 0x040F
#define S0_DPORT   0x0410      // Socket 0 : Destination Port : 0x0410 to 0x0411
#define S0_TX_FSR  0x0420      // Socket 0: Tx Free Size Register: 0x0420 to 0x0421
#define S0_TX_RD   0x0422      // Socket 0: Tx Read Pointer Register: 0x0422 to 0x0423
#define S0_TX_WR   0x0424      // Socket 0: Tx Write Pointer Register: 0x0424 to 0x0425
#define S0_RX_RSR  0x0426      // Socket 0: Rx Received Size Pointer Register: 0x0425 to 0x0427
#define S0_RX_RD   0x0428      // Socket 0: Rx Read Pointer: 0x0428 to 0x0429

/* Socket 1 Registers */
#define S1_MR	   0x0500      // Socket 1: Mode Register Address
#define S1_CR	   0x0501      // Socket 1: Command Register Address
#define S1_IR	   0x0502      // Socket 1: Interrupt Register Address
#define S1_SR	   0x0503      // Socket 1: Status Register Address
#define S1_PORT    0x0504      // Socket 1: Source Port: 0x0504 to 0x0505
#define S1_DIPR	   0x050C	   // Socket 1 : Destination IP : 0x050C to 0x050F
#define S1_DPORT   0x0510      // Socket 1 : Destination Port : 0x0510 to 0x0511
#define S1_TX_FSR  0x0520      // Socket 1: Tx Free Size Register: 0x0520 to 0x0521
#define S1_TX_RD   0x0522      // Socket 1: Tx Read Pointer Register: 0x0522 to 0x0523
#define S1_TX_WR   0x0524      // Socket 1: Tx Write Pointer Register: 0x0524 to 0x0525
#define S1_RX_RSR  0x0526      // Socket 1: Rx Received Size Pointer Register: 0x0525 to 0x0527
#define S1_RX_RD   0x0528      // Socket 1: Rx Read Pointer: 0x0528 to 0x0529

/* Socket 2 Registers */
#define S2_MR	   0x0600      // Socket 2: Mode Register Address
#define S2_CR	   0x0601      // Socket 2: Command Register Address
#define S2_IR	   0x0602      // Socket 2: Interrupt Register Address
#define S2_SR	   0x0603      // Socket 2: Status Register Address
#define S2_PORT    0x0604      // Socket 2: Source Port: 0x0604 to 0x0605
#define S2_DIPR	   0x060C	   // Socket 2 : Destination IP : 0x060C to 0x060F
#define S2_DPORT   0x0610      // Socket 2 : Destination Port : 0x0610 to 0x0611
#define S2_TX_FSR  0x0620      // Socket 2: Tx Free Size Register: 0x0620 to 0x0621
#define S2_TX_RD   0x0622      // Socket 2: Tx Read Pointer Register: 0x0622 to 0x0623
#define S2_TX_WR   0x0624      // Socket 2: Tx Write Pointer Register: 0x0624 to 0x0625
#define S2_RX_RSR  0x0626      // Socket 2: Rx Received Size Pointer Register: 0x0625 to 0x0627
#define S2_RX_RD   0x0628      // Socket 2: Rx Read Pointer: 0x0628 to 0x0629

/* Socket 3 Registers */
#define S3_MR	   0x0700      // Socket 3: Mode Register Address
#define S3_CR	   0x0701      // Socket 3: Command Register Address
#define S3_IR	   0x0702      // Socket 3: Interrupt Register Address
#define S3_SR	   0x0703      // Socket 3: Status Register Address
#define S3_PORT    0x0704      // Socket 3: Source Port: 0x0704 to 0x0705
#define S3_DIPR	   0x070C	   // Socket 3 : Destination IP : 0x070C to 0x070F
#define S3_DPORT   0x0410      // Socket 3 : Destination Port : 0x0710 to 0x0711
#define S3_TX_FSR  0x0720      // Socket 3: Tx Free Size Register: 0x0720 to 0x0671
#define S3_TX_RD   0x0722      // Socket 3: Tx Read Pointer Register: 0x0722 to 0x0723
#define S3_TX_WR   0x0724      // Socket 3: Tx Write Pointer Register: 0x0724 to 0x0725
#define S3_RX_RSR  0x0726      // Socket 3: Rx Received Size Pointer Register: 0x0725 to 0x0727
#define S3_RX_RD   0x0728      // Socket 3: Rx Read Pointer: 0x0728 to 0x0729

#define TXBUFADDR  0x4000      // W5100 Send Buffer Base Address
#define RXBUFADDR  0x6000      // W5100 Read Buffer Base Address
// S(n)_MR values
#define MR_CLOSE	  0x00    // Unused socket
#define MR_TCP		  0x01    // TCP
#define MR_UDP		  0x02    // UDP
#define MR_IPRAW	  0x03	  // IP LAYER RAW SOCK
#define MR_MACRAW	  0x04	  // MAC LAYER RAW SOCK
#define MR_PPPOE	  0x05	  // PPPoE
#define MR_ND		  0x20	  // No Delayed Ack(TCP) flag
#define MR_MULTI	  0x80	  // support multicating
// S(n)_CR values
#define CR_OPEN          0x01	  // Initialize or open socket
#define CR_LISTEN        0x02	  // Wait connection request in tcp mode(Server mode)
#define CR_CONNECT       0x04	  // Send connection request in tcp mode(Client mode)
#define CR_DISCON        0x08	  // Send closing reqeuset in tcp mode
#define CR_CLOSE         0x10	  // Close socket
#define CR_SEND          0x20	  // Update Tx memory pointer and send data
#define CR_SEND_MAC      0x21	  // Send data with MAC address, so without ARP process
#define CR_SEND_KEEP     0x22	  // Send keep alive message
#define CR_RECV          0x40	  // Update Rx memory buffer pointer and receive data
// S(n)_SR values
#define SOCK_CLOSED      0x00     // Closed
#define SOCK_INIT        0x13	  // Init state
#define SOCK_LISTEN      0x14	  // Listen state
#define SOCK_SYNSENT     0x15	  // Connection state
#define SOCK_SYNRECV     0x16	  // Connection state
#define SOCK_ESTABLISHED 0x17	  // Success to connect
#define SOCK_FIN_WAIT    0x18	  // Closing state
#define SOCK_CLOSING     0x1A	  // Closing state
#define SOCK_TIME_WAIT	 0x1B	  // Closing state
#define SOCK_CLOSE_WAIT  0x1C	  // Closing state
#define SOCK_LAST_ACK    0x1D	  // Closing state
#define SOCK_UDP         0x22	  // UDP socket
#define SOCK_IPRAW       0x32	  // IP raw mode socket
#define SOCK_MACRAW      0x42	  // MAC raw mode socket
#define SOCK_PPPOE       0x5F	  // PPPOE socket
#define TX_BUF_MASK      0x07FF   // Tx 2K Buffer Mask:
#define RX_BUF_MASK      0x07FF   // Rx 2K Buffer Mask:
#define NET_MEMALLOC     0x05     // Use 2K of Tx/Rx Buffer

/*
	Initializes the W5100 Controller.
*/
void w5100_init(void);

/*
	Write command to W5100 controller.
*/
void wiznet_write(uint16_t addr,uint8_t data);

/*
	Read command from W5100 controller.
*/
unsigned char wiznet_read(uint16_t addr);

#endif /* WIZNET_H_ */