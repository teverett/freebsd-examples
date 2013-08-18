/*-
 * Copyright (c) 2014 Tom Everett <tom@khubla.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

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

struct bcm2835_spi_softc 
{
	 device_t sc_dev;
};

static int
bcm2835_spi_probe(device_t dev)
{
	uprintf("bcm2835_spi probe\n");
	return (BUS_PROBE_DEFAULT);
}

static int
bcm2835_spi_attach(device_t dev)
{
	uprintf("bcm2835_spi attach\n");
	device_set_desc(dev, "Broadcom BCM2835 SPI");
        struct bcm2835_spi_softc *sc = device_get_softc(dev);
        sc->sc_dev = dev;
	return (bus_generic_attach(dev));
}

static int
bcm2835_spi_detach(device_t dev)
{	
	bus_generic_detach(dev);
	return (0);
}

static device_method_t bcm2835_spi_methods[] = {
	DEVMETHOD(device_probe, bcm2835_spi_probe),
	DEVMETHOD(device_attach, bcm2835_spi_attach),
	DEVMETHOD(device_detach, bcm2835_spi_detach),
	DEVMETHOD_END
};

static driver_t bcm2835_spi_driver = {
	"bcm2835_spi",
	bcm2835_spi_methods,	sizeof(struct bcm2835_spi_softc),
};
static devclass_t bcm2835_spi_devclass;

DRIVER_MODULE(bcm2835_spi, simplebus, bcm2835_spi_driver, bcm2835_spi_devclass, 0, 0);

