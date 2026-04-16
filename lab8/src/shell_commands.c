#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>

static int cmd_skywatch_status(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "SkyWatch Status:");
    shell_print(sh, " Uptime: %lld ms",
    k_uptime_get());
    shell_print(sh, " Threads: main, sensor, app");
    return 0;
}

static int cmd_skywatch_version(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "SkyWatch Weather Station");
    shell_print(sh, " Build: " __DATE__ " " __TIME__);
    shell_print(sh, " Board: %s", CONFIG_BOARD);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_skywatch,
    SHELL_CMD(status, NULL,
        "Show SkyWatch status",
        cmd_skywatch_status),
    SHELL_CMD(version, NULL,
        "Show version info",
        cmd_skywatch_version),
SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(skywatch, &sub_skywatch, "SkyWatch commands", NULL);