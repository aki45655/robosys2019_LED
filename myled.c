#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Akito Ogura");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;


static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char c;
	int j;
	if(copy_from_user(&c,buf,sizeof(char)))
		return -EFAULT;
	int i = c - '0';
	if(c == 'L'){
		gpio_base[10] = 1 << 25;
	}
	else if (c == 'H'){
		gpio_base[7] = 1 << 25;
	}
	else if ('1' <= c && c <= '9'){ 
		for(j = 0; j < 10; j++){
			gpio_base[7] = 1 << 25;
			msleep(i*100);
			gpio_base[10] = 1 << 25;
			msleep(i*100);
		}
	}

	return 1;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write
};

static int __init init_mod(void)
{
	int retval;

	gpio_base = ioremap_nocache(0x3f200000, 0xA0);
	const u32 led = 25;
	const u32 index  = led/10;
	const u32 shift = (led%10)*3;//15
	const u32 mask = ~(0x7 <<shift);//ビットNOT
	gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);


	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0)
		printk(KERN_ERR "dlloc_chrdev_region.\n");

	
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0)
	{
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}
	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));
	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
