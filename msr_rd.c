#include <linux/module.h>
#include <linux/version.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

unsigned long __attribute__((used)) msr=0;
module_param(msr,ulong,0660);

unsigned long test(unsigned long msr2)
{
	unsigned long res = 0;

	__asm__ volatile
	(
		"movq	msr, %%rcx"		"\n\t"
		"rdmsr"				"\n\t"
		"shlq	$32, %%rdx"		"\n\t"
		"orq	%%rdx, %%rax"		"\n\t"
		"movq	%%rax, %0"
		:"=m" (res)
		:"r" (msr2)
		:"memory", "%rax", "%rcx",  "%rdx"
	);

	return res;
}

static int __init testinit(void)
{
	unsigned long tsc = 0;

	tsc = test(msr);

	printk("tsc[%lu]\n", tsc);

	return 0;
}

static void __exit testexit(void)
{
}

module_init(testinit);
module_exit(testexit);
