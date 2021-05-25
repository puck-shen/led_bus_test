#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/io.h>        //含有iomap函数iounmap函数
#include <asm/uaccess.h>//含有copy_from_user函数
#include <linux/device.h>//含有类相关的处理函数
#include <linux/platform_device.h>
/* 分配/设置/注册一个platform_device */

static struct resource led_resource[] = {
    [0] = {
        .start = 2,
        .end   = 2,
        .flags = IORESOURCE_MEM,
    },
};

static void led_release(struct device * dev)
{
}


static struct platform_device led_dev = {
    .name               = "myled",
    .id                 = -1,
    .num_resources      = ARRAY_SIZE(led_resource),
    .resource           = led_resource,
    .dev                = { 
    	                    .release = led_release, 
	},
};

static int led_dev_init(void)
{
	platform_device_register(&led_dev);
	return 0;
}

static void led_dev_exit(void)
{
	platform_device_unregister(&led_dev);
}

module_init(led_dev_init);
module_exit(led_dev_exit);

MODULE_LICENSE("GPL");//不加的话加载会有错误提醒
MODULE_AUTHOR("puck.shen@quectel.com");//作者
MODULE_VERSION("v02");//版本
MODULE_DESCRIPTION("This is led_dev");//简单的描述

