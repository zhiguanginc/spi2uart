/*
 * SPI2UART program for HT45B0F
 *
 * Wrote by Michael Li
 * QQ:13458499
 * Mail: michael_li@dspa.com.tw
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/wait.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#include "gpio.h"
#include "pindev.h"

static int major = 20;

static int pin_open(struct inode *inode, struct file *file)
{
	return 0;
}


static int pin_release(struct inode *inode, struct file *file)
{
	return 0;
}


static int pin_ioctl(struct inode *inode, struct file *filp,
                     unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	ST_GPIO stGPIO;

	if ((DSPG_GPIOA_WRITE == cmd) || (DSPG_GPIOB_WRITE == cmd) || (DSPG_GPIOC_WRITE == cmd)
	                || (DSPG_GPIOA_SYSMUX == cmd) || (DSPG_GPIOB_SYSMUX == cmd) || (DSPG_GPIOC_SYSMUX == cmd)
	                || (DSPG_GPIOA_SYSPAD == cmd) || (DSPG_GPIOB_SYSPAD == cmd) || (DSPG_GPIOC_SYSPAD == cmd)
	                || (DSPG_GPIOA_READ == cmd) || (DSPG_GPIOB_READ == cmd) || (DSPG_GPIOC_READ == cmd))
	{
		ret = copy_from_user(&stGPIO, arg, sizeof(stGPIO));
	}

	switch (cmd)
	{
	case DSPG_GPIOA_WRITE:
		printk(KERN_INFO"DSPG_GPIOA_WRITE: write %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_direction_gpioa(stGPIO.iPin, 1);
		if (stGPIO.iVal)
			set_gpioa(stGPIO.iPin);
		else
			clear_gpioa(stGPIO.iPin);
		break;

	case DSPG_GPIOB_WRITE:
		printk(KERN_INFO"DSPG_GPIOB_WRITE: write %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_direction_gpiob(stGPIO.iPin, 1);
		if (stGPIO.iVal)
			set_gpiob(stGPIO.iPin);
		else
			clear_gpiob(stGPIO.iPin);
		break;

	case DSPG_GPIOC_WRITE:
		printk(KERN_INFO"DSPG_GPIOC_WRITE: write %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_direction_gpioc(stGPIO.iPin, 1);
		if (stGPIO.iVal)
			set_gpioc(stGPIO.iPin);
		else
			clear_gpioc(stGPIO.iPin);
		break;

	case DSPG_GPIOA_SYSMUX:
		printk(KERN_INFO"DSPG_GPIOA_SYSMUX: sysmux %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_sysmux_gpioa(stGPIO.iPin, stGPIO.iVal);
		break;

	case DSPG_GPIOB_SYSMUX:
		printk(KERN_INFO"DSPG_GPIOB_SYSMUX: sysmux %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_sysmux_gpiob(stGPIO.iPin, stGPIO.iVal);
		break;

	case DSPG_GPIOC_SYSMUX:
		printk(KERN_INFO"DSPG_GPIOC_SYSMUX: sysmux %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_sysmux_gpioc(stGPIO.iPin, stGPIO.iVal);
		break;

	case DSPG_GPIOA_SYSPAD:
		printk(KERN_INFO"DSPG_GPIOA_SYSPAD: syspad %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_syspad_gpioa(stGPIO.iPin, stGPIO.iVal);
		break;

	case DSPG_GPIOB_SYSPAD:
		printk(KERN_INFO"DSPG_GPIOB_SYSPAD: syspad %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_syspad_gpiob(stGPIO.iPin, stGPIO.iVal);
		break;

	case DSPG_GPIOC_SYSPAD:
		printk(KERN_INFO"DSPG_GPIOC_SYSPAD: syspad %d %d\n", stGPIO.iPin, stGPIO.iVal);
		set_syspad_gpioc(stGPIO.iPin, stGPIO.iVal);
		break;

		/* it's OK, and the syspad register is needed.
		set_sysmux_gpiob(stGPIO.iPin, 1);
		set_direction_gpiob(stGPIO.iPin, 0);
		set_syspad_gpiob(stGPIO.iPin, 0);
		*/
		/*
		set_direction_gpioa(stGPIO.iPin, 0);
		stGPIO.iVal = get_gpioa(stGPIO.iPin);

		ret = copy_to_user((void __user *)arg, &stGPIO, sizeof(stGPIO));
		if (ret == 0)
			printk(KERN_INFO"DSPG_GPIOA_READ: read %d = %d\n", stGPIO.iPin, stGPIO.iVal);
		else
			printk(KERN_INFO"DSPG_GPIOA_READ: error\n");
		*/

	case DSPG_GPIOA_READ:
		config_gpioa(stGPIO.iPin, SYSMUX_GPIOA, GPIOA_DIR_INPUT, SYSPAD_PULL_UP, -1);
		stGPIO.iVal = get_gpioa(stGPIO.iPin);

		ret = copy_to_user((void __user *)arg, &stGPIO, sizeof(stGPIO));
		if (ret == 0)
			printk(KERN_INFO"DSPG_GPIOA_READ: read %d = %d\n", stGPIO.iPin, stGPIO.iVal);
		else
			printk(KERN_INFO"DSPG_GPIOA_READ: error\n");
			
		break;

	case DSPG_GPIOB_READ:
		config_gpiob(stGPIO.iPin, SYSMUX_GPIOB, GPIOB_DIR_INPUT, SYSPAD_PULL_UP, -1);
		stGPIO.iVal = get_gpiob(stGPIO.iPin);

		ret = copy_to_user((void __user *)arg, &stGPIO, sizeof(stGPIO));
		if (ret == 0)
			printk(KERN_INFO"DSPG_GPIOB_READ: read %d = %d\n", stGPIO.iPin, stGPIO.iVal);
		else
			printk(KERN_INFO"DSPG_GPIOB_READ: error\n");

		break;

	case DSPG_GPIOC_READ:
		config_gpioc(stGPIO.iPin, SYSMUX_GPIOC, GPIOC_DIR_INPUT, SYSPAD_PULL_UP, -1);
		stGPIO.iVal = get_gpioc(stGPIO.iPin);

		ret = copy_to_user((void __user *)arg, &stGPIO, sizeof(stGPIO));
		if (ret == 0)
			printk(KERN_INFO"DSPG_GPIOC_READ: read %d = %d\n", stGPIO.iPin, stGPIO.iVal);
		else
			printk(KERN_INFO"DSPG_GPIOC_READ: error\n");
			
		break;

	default:
		ret = -EINVAL;
	}

	return ret;
}

static struct file_operations pin_fops =
{
	.owner = THIS_MODULE,
	.ioctl = pin_ioctl,
	.open  = pin_open,
	.release = pin_release,
};

static int pin_init(void)
{
	int ret;

	ret = register_chrdev(major, "pin_dev", &pin_fops);
	if (ret < 0)
	{
		printk(KERN_INFO"could not register pin device!\n");
		return -1;
	}

	printk(KERN_INFO"pin device registered. major: %d.\n", major);

	return 0;
}

static void __exit pin_exit(void)
{
	unregister_chrdev(major, "pin_dev");
}

module_init(pin_init);
module_exit(pin_exit);

MODULE_AUTHOR("Michael Li");
MODULE_LICENSE("GPL");


