/*
 * SPI2UART program for HT45B0F
 *
 * Wrote by Michael Li
 * QQ:13458499
 * Mail: michael_li@dspa.com.tw
 *
 */
#include "gpio.h"


/* GPIO A */
unsigned char get_gpioa(unsigned char gpionr)
{
    return (readl((void *)PNX8181_GPIOA_PINS) >> gpionr) & 1;
}

void set_gpioa(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOA_OUTPUT) | (1 << gpionr)),
           (void *)PNX8181_GPIOA_OUTPUT);
}

void clear_gpioa(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOA_OUTPUT) & ~(1 << gpionr)),
           (void *)PNX8181_GPIOA_OUTPUT);
}

void toggle_gpioa(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOA_OUTPUT) ^ (1 << gpionr)),
           (void *)PNX8181_GPIOA_OUTPUT);
}

void set_direction_gpioa(unsigned char gpionr, unsigned char dir)
{
    if (dir)
        writel(readl((void *)PNX8181_GPIOA_DIRECTION) | (1 << gpionr),
               (void *)PNX8181_GPIOA_DIRECTION);
    else
        writel(readl((void *)PNX8181_GPIOA_DIRECTION) & ~(1 << gpionr),
               (void *)PNX8181_GPIOA_DIRECTION);
}

void set_syspad_gpioa(unsigned char gpionr, unsigned char pad)
{
    pad &= 0x3;
    if (gpionr < 16)
    {
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD0))& ~(0x3 << (2 * gpionr))) | (pad << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD0));
    }
    else
    {
        gpionr -= 16;
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD1))
                & ~(0x3 << (2 * gpionr)))
               | (pad << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD1));
    }
}

void set_sysmux_gpioa(unsigned char gpionr, unsigned char mux)
{
    mux &= 0x3;
    if (gpionr < 16)
    {
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX0))
                & ~(0x3 << (2 * gpionr)))
               | (mux << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX0));
    }
    else
    {
        gpionr -= 16;
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX1))
                & ~(0x3 << (2 * gpionr)))
               | (mux << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX1));
    }
}

void config_gpioa(unsigned char gpionr, unsigned char mux, unsigned char dir,
                  unsigned char pad, unsigned char value)
{
    set_sysmux_gpioa(gpionr, mux);
    set_direction_gpioa(gpionr, dir);
    set_syspad_gpioa(gpionr, pad);

    if (value)
        set_gpioa(gpionr);
    else
        clear_gpioa(gpionr);
}

/* PORT B */
unsigned char get_gpiob(unsigned char gpionr)
{
    return (readl((void *)PNX8181_GPIOB_PINS) >> gpionr) & 1;
}

void set_gpiob(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOB_OUTPUT) | (1 << gpionr)),
           (void *)PNX8181_GPIOB_OUTPUT);
}

void clear_gpiob(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOB_OUTPUT) & ~(1 << gpionr)),
           (void *)PNX8181_GPIOB_OUTPUT);
}
void toggle_gpiob(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOB_OUTPUT) ^ (1 << gpionr)),
           (void *)PNX8181_GPIOB_OUTPUT);
}

void set_direction_gpiob(unsigned char gpionr, unsigned char dir)
{
    if (dir)
        writel(readl((void *)PNX8181_GPIOB_DIRECTION) | (1 << gpionr),
               (void *)PNX8181_GPIOB_DIRECTION);
    else
        writel(readl((void *)PNX8181_GPIOB_DIRECTION) & ~(1 << gpionr),
               (void *)PNX8181_GPIOB_DIRECTION);
}


void set_syspad_gpiob(unsigned char gpionr, unsigned char pad)
{
    pad &= 0x3;
    if (gpionr < 16)
    {
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD2))
                & ~(0x3 << (2 * gpionr)))
               | (pad << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD2));
    }
    else
    {
        gpionr -= 16;
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD3))
                & ~(0x3 << (2 * gpionr)))
               | (pad << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD3));
    }
}

void set_sysmux_gpiob(unsigned char gpionr, unsigned char mux)
{
    mux &= 0x3;
    if (gpionr < 16)
    {
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX2))
                & ~(0x3 << (2 * gpionr)))
               | (mux << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX2));
    }
    else
    {
        gpionr -= 16;
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX3))
                & ~(0x3 << (2 * gpionr)))
               | (mux << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX3));
    }
}

void config_gpiob(unsigned char gpionr, unsigned char mux, unsigned char dir,
                  unsigned char pad, unsigned char value)
{
    set_sysmux_gpiob(gpionr, mux);
    set_direction_gpiob(gpionr, dir);
    set_syspad_gpiob(gpionr, pad);

    if (value)
        set_gpiob(gpionr);
    else
        clear_gpiob(gpionr);
}

/* PORT C */
unsigned char get_gpioc(unsigned char gpionr)
{
    return (readl((void *)PNX8181_GPIOC_PINS) >> gpionr) & 1;
}

void set_gpioc(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOC_OUTPUT) | (1 << gpionr)),
           (void *)PNX8181_GPIOC_OUTPUT);
}

void clear_gpioc(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOC_OUTPUT) & ~(1 << gpionr)),
           (void *)PNX8181_GPIOC_OUTPUT);
}
void toggle_gpioc(unsigned char gpionr)
{
    writel((readl((void *)PNX8181_GPIOC_OUTPUT) ^ (1 << gpionr)),
           (void *)PNX8181_GPIOC_OUTPUT);
}

void set_direction_gpioc(unsigned char gpionr, unsigned char dir)
{
    if (dir)
        writel(readl((void *)PNX8181_GPIOC_DIRECTION) | (1 << gpionr),
               (void *)PNX8181_GPIOC_DIRECTION);
    else
        writel(readl((void *)PNX8181_GPIOC_DIRECTION) & ~(1 << gpionr),
               (void *)PNX8181_GPIOC_DIRECTION);
}


void set_syspad_gpioc(unsigned char gpionr, unsigned char pad)
{
    pad &= 0x3;
    if (gpionr < 16)
    {
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD4))
                & ~(0x3 << (2 * gpionr)))
               | (pad << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD4));
    }
    else
    {
        gpionr -= 16;
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD5))
                & ~(0x3 << (2 * gpionr)))
               | (pad << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSPAD5));
    }
}

void set_sysmux_gpioc(unsigned char gpionr, unsigned char mux)
{
    mux &= 0x3;
    if (gpionr < 16)
    {
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX4))
                & ~(0x3 << (2 * gpionr)))
               | (mux << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX4));
    }
    else
    {
        gpionr -= 16;
        writel((readl((void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX5))
                & ~(0x3 << (2 * gpionr)))
               | (mux << (2 * gpionr)),
               (void *)(PNX8181_SCON_BASE + PNX8181_SYSMUX5));
    }
}

void config_gpioc(unsigned char gpionr, unsigned char mux, unsigned char dir,
                  unsigned char pad, unsigned char value)
{
    set_sysmux_gpioc(gpionr, mux);
    set_direction_gpioc(gpionr, dir);
    set_syspad_gpioc(gpionr, pad);

    if (value)
        set_gpioc(gpionr);
    else
        clear_gpioc(gpionr);
}
