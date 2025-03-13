#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

MODULE_LICENSE ("Dual BSD/GPL") ; 
MODULE_AUTHOR("csli");
MODULE_DESCRIPTION("This is csli test module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "csli_chrdev"
static unsigned int csli_chrdev_major = 0;
static unsigned int num_of_dev = 1;
static struct cdev csli_chrdev_cdev;
static struct class *csli_chrdev_class = NULL;


ssize_t csli_chrdev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	char *val = (char*)(filp->private_data);
	int retval = 0;
	int i;
	printk(KERN_ALERT "%s\n", __func__);

	for (i = 0 ; i < count ; i++) {
		if (copy_to_user(&buf[i],val, 1)) {
			retval = -EFAULT;
			goto out;
		}
	}
	retval = count;

out:
	return (retval);
}


ssize_t csli_chrdev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	char *val = (char*)(filp->private_data);	
	int ret;
	int retval = 0;
	printk(KERN_ALERT "%s\n", __func__);

	ret = copy_from_user(val,&buf[0],count);
	if(ret != 0) {
		retval = -EFAULT;
		goto out;
	}
	else{
		retval = count;
	}
out:
	return (retval);
}


static int csli_chrdev_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "Call csli_chrdev_open\n");
	file->private_data =(char*)kmalloc(1, GFP_KERNEL);
	return 0;
}

static int csli_chrdev_close(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "Call csli_chrdev_close\n");
	kfree(file->private_data);
	return 0;
}


struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = csli_chrdev_open,
	.release = csli_chrdev_close,
	.read = csli_chrdev_read,
	.write = csli_chrdev_write,
};


static int csli_chrdev_init (void) 
{ 
	dev_t dev = MKDEV(csli_chrdev_major, 0);
	int alloc_ret = 0;
	int cdev_ret = 0;

	alloc_ret = alloc_chrdev_region(&dev, 0, num_of_dev, DRIVER_NAME);
	if(alloc_ret)
		goto error;

	csli_chrdev_major = MAJOR(dev);

	cdev_init(&csli_chrdev_cdev, &fops);
	cdev_ret = cdev_add(&csli_chrdev_cdev, dev, num_of_dev);
	if (cdev_ret)
		goto error;

	/*Create sys class*/
	csli_chrdev_class = class_create(THIS_MODULE, DRIVER_NAME); 
	if (IS_ERR(csli_chrdev_class)) {
		goto error;
	}
	/*Register sysfs*/
	device_create(csli_chrdev_class,
		NULL,
		MKDEV(csli_chrdev_major, 0),
		NULL,
		DRIVER_NAME);	

	printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, csli_chrdev_major);
	return 0;

error:
	if (cdev_ret == 0)
		cdev_del(&csli_chrdev_cdev);
	if (alloc_ret == 0)
		unregister_chrdev_region(dev,num_of_dev);
	return -1;
} 


static void csli_chrdev_exit (void) 
{
	dev_t dev = MKDEV(csli_chrdev_major, 0);

	/* unregister class */
	device_destroy(csli_chrdev_class, dev);
	class_destroy(csli_chrdev_class);

	cdev_del(&csli_chrdev_cdev);
	unregister_chrdev_region(dev, num_of_dev);
	printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME); 
} 


module_init ( csli_chrdev_init ) ; 
module_exit ( csli_chrdev_exit ) ;


