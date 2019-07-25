#include <linux/module.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

unsigned long long test(unsigned long long msr)
{
	unsigned long long res = 0;

	__asm__ volatile
	(
		"movq	%1, %%rcx"		"\n\t"
		"rdmsr"				"\n\t"
		"shlq	$32, %%rdx"		"\n\t"
		"orq	%%rdx, %%rax"		"\n\t"
		"movq	%%rax, %0"
		:"=m" (res)
		:"r" (msr)
		:"memory", "%rax", "%rcx",  "%rdx"
	);

	return res;
}

static int __init testinit(void)
{
	unsigned long long tsc = 0;

	tsc = test(0x10);

	printk("tsc[%llu]\n", tsc);

	return 0;
}

static void __exit testexit(void)
{
}

module_init(testinit);
module_exit(testexit);
