#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/setup.h>
#include <soc/qcom/lge/board_lge.h>
#include <linux/slab.h>

static char updated_command_line[COMMAND_LINE_SIZE];

static void cmdline_proc_patch(char *cmd, const char *flag, const char *val)
{
	size_t flag_len, val_len;
	char *start, *end;

	start = strstr(cmd, flag);
	if (!start)
		return;

	flag_len = strlen(flag);
	val_len = strlen(val);
	end = start + flag_len + strcspn(start + flag_len, " ");
	memmove(start + flag_len + val_len, end, strlen(end) + 1);
	memcpy(start + flag_len, val, val_len);
}

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_puts(m, updated_command_line);
	seq_putc(m, '\n');
	return 0;
}

static int cmdline_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cmdline_proc_show, NULL);
}

static const struct file_operations cmdline_proc_fops = {
	.open		= cmdline_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_cmdline_init(void)
{
	strcpy(updated_command_line, saved_command_line);

#ifdef CONFIG_MACH_LGE
	if (lge_get_boot_mode() == LGE_BOOT_MODE_CHARGERLOGO)
		 cmdline_proc_patch(updated_command_line, "androidboot.mode", "charger");
#endif

	/*
	 * Patch various flags from command line seen by userspace in order to
	 * pass SafetyNet checks.
	 */
	 cmdline_proc_patch(updated_command_line, "androidboot.flash.locked=", "1");
	 cmdline_proc_patch(updated_command_line, "androidboot.verifiedbootstate=", "green");
	 cmdline_proc_patch(updated_command_line, "androidboot.veritymode=", "enforcing");

	proc_create("cmdline", 0, NULL, &cmdline_proc_fops);
	return 0;
}
fs_initcall(proc_cmdline_init);
