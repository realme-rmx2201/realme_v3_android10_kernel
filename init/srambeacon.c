/* SRAM progress beacon for GSI boot debugging */
#include <linux/init.h>
#include <linux/io.h>

#define BEACON_ADDR 0x11D700

static int __init sram_beacon_init(void)
{
    void __iomem *b = ioremap(BEACON_ADDR, 0x100);
    if (!b) return -ENOMEM;
    writel(0xBEAC0001, b);
    iounmap(b);
    pr_info("SRAMBEACON: init done @%x\n", BEACON_ADDR);
    return 0;
}
late_initcall(sram_beacon_init);

void sram_beacon_mark(unsigned int code)
{
    void __iomem *b = ioremap(BEACON_ADDR, 0x100);
    if (b) {
        writel(code, b);
        iounmap(b);
    }
}
EXPORT_SYMBOL(sram_beacon_mark);

#include <linux/notifier.h>
static int beacon_panic_cb(struct notifier_block *nb, unsigned long action, void *data)
{
    sram_beacon_mark(0xBEAC2000);
    return NOTIFY_DONE;
}
static struct notifier_block beacon_panic_nb = {
    .notifier_call = beacon_panic_cb,
    .priority = 100,
};
static int __init beacon_panic_init(void)
{
    atomic_notifier_chain_register(&panic_notifier_list, &beacon_panic_nb);
    return 0;
}
late_initcall(beacon_panic_init);
