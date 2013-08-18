/*-
2	 * Copyright (c) 2013 Tom Everett (tom@khubla.com)
3	 * Copyright (c) 2013 Luiz Otavio O Souza.
4	 * All rights reserved.
5	 *
6	 * Redistribution and use in source and binary forms, with or without
7	 * modification, are permitted provided that the following conditions
8	 * are met:
9	 * 1. Redistributions of source code must retain the above copyright
10	 *    notice, this list of conditions and the following disclaimer.
11	 * 2. Redistributions in binary form must reproduce the above copyright
12	 *    notice, this list of conditions and the following disclaimer in the
13	 *    documentation and/or other materials provided with the distribution.
14	 *
15	 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
16	 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
17	 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
18	 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
19	 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
20	 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
21	 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
22	 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
23	 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
24	 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
25	 * SUCH DAMAGE.
26	 *
27	 */

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

