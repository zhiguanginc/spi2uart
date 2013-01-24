/*
 * SPI2UART program for HT45B0F
 *
 * Wrote by Michael Li
 * QQ:13458499
 * Mail: michael_li@dspa.com.tw
 *
 */
#ifndef __GPIO_H__
#define __GPIO_H__


#define readl(addr) (*(volatile unsigned int*)(addr))
#define writel(b,addr) ((*(volatile unsigned int *) (addr)) = (b))

/* console port */
#define PNX8181_UART2_BASE	0xc2005000
#define PNX8181_UART_FDIV_CTRL	0xc00
#define PNX8181_UART_FDIV_M	0xc04
#define PNX8181_UART_FDIV_N	0xc08

/* gpio settings */
#define PNX8181_SCON_BASE	0xC2204000
#define PNX8181_REG_SC_SYSVER	(PNX8181_SCON_BASE + 0x0)

#undef  PNX8181_SYSMUX0
#undef  PNX8181_SYSMUX1
#undef  PNX8181_SYSMUX2
#undef  PNX8181_SYSMUX3
#undef  PNX8181_SYSMUX4
#undef  PNX8181_SYSMUX5
#undef  PNX8181_SYSPAD0
#undef  PNX8181_SYSPAD1
#undef  PNX8181_SYSPAD2
#undef  PNX8181_SYSPAD3
#undef  PNX8181_SYSPAD4
#undef  PNX8181_SYSPAD5

#define PNX8181_SYSMUX0		0x0C
#define PNX8181_SYSMUX1		0x10
#define PNX8181_SYSMUX2		0x14
#define PNX8181_SYSMUX3		0x18
#define PNX8181_SYSMUX4		0x1C
#define PNX8181_SYSMUX5		0x20
#define PNX8181_SYSPAD0		0x34
#define PNX8181_SYSPAD1		0x38
#define PNX8181_SYSPAD2		0x3c
#define PNX8181_SYSPAD3		0x40
#define PNX8181_SYSPAD4		0x44
#define PNX8181_SYSPAD5		0x48

#define SYSMUX_GPIOA		0x0
#define SYSMUX_GPIOB		0x1
#define SYSMUX_GPIOC		0x1

#define SYSPAD_PULL_UP		0x0
#define SYSPAD_REPEATER		0x1
#define SYSPAD_PLAIN_INPUT	0x2
#define SYSPAD_PULL_DOWN	0x3

#undef PNX8181_GPIOA_PINS
#undef PNX8181_GPIOB_PINS
#undef PNX8181_GPIOC_PINS

#define PNX8181_GPIOA_PINS	0xc2104000
#define PNX8181_GPIOA_OUTPUT	0xc2104004
#define PNX8181_GPIOA_DIRECTION	0xc2104008

#define PNX8181_GPIOB_PINS	0xc2104200
#define PNX8181_GPIOB_OUTPUT	0xc2104204
#define PNX8181_GPIOB_DIRECTION	0xc2104208

#define PNX8181_GPIOC_PINS	0xc2104400
#define PNX8181_GPIOC_OUTPUT	0xc2104404
#define PNX8181_GPIOC_DIRECTION	0xc2104408


#define GPIOA_DIR_OUTPUT	1
#define GPIOA_DIR_INPUT		0
#define GPIOB_DIR_OUTPUT	1
#define GPIOB_DIR_INPUT		0
#define GPIOC_DIR_OUTPUT	1
#define GPIOC_DIR_INPUT		0

/* timing for CS0 (NAND) */
#define PNX8181_REG_EBI1_BASE	0xBC000000
#define PNX8181_REG_EBI1_CS0	(PNX8181_REG_EBI1_BASE + 0x00)
#define PNX8181_REG_EBI1_CS3	(PNX8181_REG_EBI1_BASE + 0x60)
#define PNX8181_EBI_MAIN_OFF	0x00
#define PNX8181_EBI_READ_OFF	0x04
#define PNX8181_EBI_WRITE_OFF	0x08
#define PNX8181_EBI_BURST_OFF	0x0C

/* irq resetting */
#define PNX8181_INTC_REQUEST	0xC1100400

#define PNX8181_DISABLEIRQ(IRQ)	writel((0x1f << 25), \
				(void *)PNX8181_INTC_REQUEST + (4 * IRQ));

#define PNX8181_INTC_PRIOMASK_IRQ	0xC1100000
#define PNX8181_INTC_PRIOMASK_FIQ	0xC1100004

/* priority for ETN over CPU for SDRAM access */
#define PNX8181_SDI_SCHED	0xC1200100
#define PNX8181_SCHED0		0x00
#define PNX8181_SCHED1		0x04
#define PNX8181_SCHED2		0x08

/* priority for SCRAM access at AHB */
#define PNX8181_SC_ARB_BASE	0xc200ea00
#define PNX8181_SC_ARB_CFG2	0x08
#define PNX8181_SC_ARB_CFG3	0x0c

/* clock settings */
#define PNX8181_REG_CGU_SCCON	0xC2200004

/* sdram configuration */
#define PNX8181_SDI_CFG_1	0xC1200000

/* Layer 2 Switch ID in Low Cost version of Vega Fire Bird */
#define L2SWITCH_ADDRESS	0x5f
#define L2_SWITCH_ID0		0x88
#define L2_SWITCH_ID1		0x31


unsigned char get_gpioa(unsigned char gpionr);
void set_gpioa(unsigned char gpionr);
void clear_gpioa(unsigned char gpionr);
void toggle_gpioa(unsigned char gpionr);
void set_direction_gpioa(unsigned char gpionr, unsigned char dir);
void set_syspad_gpioa(unsigned char gpionr, unsigned char pad);
void set_sysmux_gpioa(unsigned char gpionr, unsigned char mux);
void config_gpioa(unsigned char gpionr, unsigned char mux,
                  unsigned char dir, unsigned char pad, unsigned char value);

unsigned char get_gpiob(unsigned char gpionr);
void set_gpiob(unsigned char gpionr);
void clear_gpiob(unsigned char gpionr);
void toggle_gpiob(unsigned char gpionr);
void set_direction_gpiob(unsigned char gpionr, unsigned char dir);
void set_syspad_gpiob(unsigned char gpionr, unsigned char pad);
void set_sysmux_gpiob(unsigned char gpionr, unsigned char mux);
void config_gpiob(unsigned char gpionr, unsigned char mux,
                  unsigned char dir, unsigned char pad, unsigned char value);


unsigned char get_gpioc(unsigned char gpionr);
void set_gpioc(unsigned char gpionr);
void clear_gpioc(unsigned char gpionr);
void set_direction_gpioc(unsigned char gpionr, unsigned char dir);
void set_syspad_gpioc(unsigned char gpionr, unsigned char pad);
void set_sysmux_gpioc(unsigned char gpionr, unsigned char mux);
void config_gpioc(unsigned char gpionr, unsigned char mux,
                  unsigned char dir, unsigned char pad, unsigned char value);

void board_detect(void);
char l2_switch_present(void);
void firetux_set_led(int led, int brightness);
int print_cpuinfo(void);
int timer_init(void);


#endif
