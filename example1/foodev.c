#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/watchdog.h>
#include <sys/bus.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/rman.h>

#include <dev/fdt/fdt_common.h>
#include <dev/ofw/openfirm.h>
#include <dev/ofw/ofw_bus.h>
#include <dev/ofw/ofw_bus_subr.h>

#include <machine/cpufunc.h>
#include <machine/machdep.h>
#include <machine/fdt.h>

struct foodev_softc 
{
	 device_t sc_dev;
};

static int
foodev_probe(device_t dev)
{
	uprintf("foodev probe\n");
	return (BUS_PROBE_DEFAULT);
}

static int
foodev_attach(device_t dev)
{
	uprintf("foodev attach\n");
	device_set_desc(dev, "Foo Device");
        struct foodev_softc *sc = device_get_softc(dev);
        sc->sc_dev = dev;
	return (bus_generic_attach(dev));
}

static int
foodev_detach(device_t dev)
{	
	bus_generic_detach(dev);
	return (0);
}

static device_method_t foodev_methods[] = {
	DEVMETHOD(device_probe, foodev_probe),
	DEVMETHOD(device_attach, foodev_attach),
	DEVMETHOD(device_detach, foodev_detach),
	DEVMETHOD_END
};

static driver_t foodev_driver = {
	"foodev",
	foodev_methods,	sizeof(struct foodev_softc),
};
static devclass_t foodev_devclass;

DRIVER_MODULE(foodev, simplebus, foodev_driver, foodev_devclass, 0, 0);

