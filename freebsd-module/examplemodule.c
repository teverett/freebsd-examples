#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/watchdog.h>
#include <sys/bus.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/rman.h>


static int
examplemodule_modevent(module_t mod, int type, void *unused)
{

	switch (type) {
	case MOD_LOAD:
		uprintf("Loaded examplemodule \n");
		return (0);
	case MOD_UNLOAD:
		uprintf("Unloaded examplemodule \n");
		return (0);
	}
	return (EINVAL);
}

static moduledata_t examplemodule_mod = {
        "examplemodule",
        examplemodule_modevent,
        0
};

DECLARE_MODULE(examplemodule, examplemodule_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);

