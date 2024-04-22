// SPDX-License-Identifier: GPL-2.0-only
// Novatek NT36672C JDI Panel Driver
// Copyright (c) 2024, Patriot-06 <mbmc172@gmail.com>

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <drm/display/drm_dsc.h>
#include <drm/display/drm_dsc_helper.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct oppo19696jdi_nt36672c_1080_2400_90fps {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct drm_dsc_config dsc;
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline
struct oppo19696jdi_nt36672c_1080_2400_90fps *to_oppo19696jdi_nt36672c_1080_2400_90fps(struct drm_panel *panel)
{
	return container_of(panel, struct oppo19696jdi_nt36672c_1080_2400_90fps, panel);
}

static void oppo19696jdi_nt36672c_1080_2400_90fps_reset(struct oppo19696jdi_nt36672c_1080_2400_90fps *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(3000, 4000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(1000, 2000);
}

static int oppo19696jdi_nt36672c_1080_2400_90fps_on(struct oppo19696jdi_nt36672c_1080_2400_90fps *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_generic_write_seq(dsi, 0xff, 0xc0);
	mipi_dsi_generic_write_seq(dsi, 0x4b, 0x1f);
	usleep_range(10000, 11000);
	mipi_dsi_generic_write_seq(dsi, 0xff, 0xc0);
	mipi_dsi_generic_write_seq(dsi, 0x4b, 0x0e);
	mipi_dsi_generic_write_seq(dsi, 0xff, 0x2a);
	mipi_dsi_generic_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_generic_write_seq(dsi, 0x27, 0x80);
	mipi_dsi_generic_write_seq(dsi, 0x28, 0xfd);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xc0, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xc2, 0x1b, 0xa0);
	mipi_dsi_generic_write_seq(dsi, 0xff, 0x23);
	mipi_dsi_generic_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_generic_write_seq(dsi, 0x00, 0x80);
	mipi_dsi_generic_write_seq(dsi, 0x07, 0x00);
	mipi_dsi_generic_write_seq(dsi, 0x08, 0x01);
	mipi_dsi_generic_write_seq(dsi, 0x09, 0x0f);
	mipi_dsi_generic_write_seq(dsi, 0x0a, 0x00);
	mipi_dsi_generic_write_seq(dsi, 0x0b, 0x00);
	mipi_dsi_generic_write_seq(dsi, 0x0c, 0x00);
	mipi_dsi_generic_write_seq(dsi, 0x0d, 0x00);
	mipi_dsi_generic_write_seq(dsi, 0x10, 0x50);
	mipi_dsi_generic_write_seq(dsi, 0x11, 0x01);
	mipi_dsi_generic_write_seq(dsi, 0x12, 0x95);
	mipi_dsi_generic_write_seq(dsi, 0x15, 0x68);
	mipi_dsi_generic_write_seq(dsi, 0x16, 0x0b);
	mipi_dsi_generic_write_seq(dsi, 0x30, 0xfa);
	mipi_dsi_generic_write_seq(dsi, 0x31, 0xf9);
	mipi_dsi_generic_write_seq(dsi, 0x32, 0xf8);
	mipi_dsi_generic_write_seq(dsi, 0x33, 0xf7);
	mipi_dsi_generic_write_seq(dsi, 0x34, 0xf6);
	mipi_dsi_generic_write_seq(dsi, 0x35, 0xf5);
	mipi_dsi_generic_write_seq(dsi, 0x36, 0xf3);
	mipi_dsi_generic_write_seq(dsi, 0x37, 0xf2);
	mipi_dsi_generic_write_seq(dsi, 0x38, 0xf1);
	mipi_dsi_generic_write_seq(dsi, 0x39, 0xf0);
	mipi_dsi_generic_write_seq(dsi, 0x3a, 0xed);
	mipi_dsi_generic_write_seq(dsi, 0x3b, 0xeb);
	mipi_dsi_generic_write_seq(dsi, 0x3d, 0xe9);
	mipi_dsi_generic_write_seq(dsi, 0x3f, 0xe7);
	mipi_dsi_generic_write_seq(dsi, 0x40, 0xe6);
	mipi_dsi_generic_write_seq(dsi, 0x41, 0xe5);
	mipi_dsi_generic_write_seq(dsi, 0x45, 0xea);
	mipi_dsi_generic_write_seq(dsi, 0x46, 0xe0);
	mipi_dsi_generic_write_seq(dsi, 0x47, 0xd6);
	mipi_dsi_generic_write_seq(dsi, 0x48, 0xce);
	mipi_dsi_generic_write_seq(dsi, 0x49, 0xc7);
	mipi_dsi_generic_write_seq(dsi, 0x4a, 0xc2);
	mipi_dsi_generic_write_seq(dsi, 0x4b, 0xbe);
	mipi_dsi_generic_write_seq(dsi, 0x4c, 0xbb);
	mipi_dsi_generic_write_seq(dsi, 0x4d, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x4e, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x4f, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x50, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x51, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x52, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x53, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x54, 0xb9);
	mipi_dsi_generic_write_seq(dsi, 0x58, 0xdc);
	mipi_dsi_generic_write_seq(dsi, 0x59, 0xd3);
	mipi_dsi_generic_write_seq(dsi, 0x5a, 0xca);
	mipi_dsi_generic_write_seq(dsi, 0x5b, 0xc1);
	mipi_dsi_generic_write_seq(dsi, 0x5c, 0xb8);
	mipi_dsi_generic_write_seq(dsi, 0x5d, 0xb0);
	mipi_dsi_generic_write_seq(dsi, 0x5e, 0xa8);
	mipi_dsi_generic_write_seq(dsi, 0x5f, 0x9f);
	mipi_dsi_generic_write_seq(dsi, 0x60, 0x94);
	mipi_dsi_generic_write_seq(dsi, 0x61, 0x90);
	mipi_dsi_generic_write_seq(dsi, 0x62, 0x8b);
	mipi_dsi_generic_write_seq(dsi, 0x63, 0x86);
	mipi_dsi_generic_write_seq(dsi, 0x64, 0x7f);
	mipi_dsi_generic_write_seq(dsi, 0x65, 0x7b);
	mipi_dsi_generic_write_seq(dsi, 0x66, 0x77);
	mipi_dsi_generic_write_seq(dsi, 0x67, 0x73);
	mipi_dsi_generic_write_seq(dsi, 0xa0, 0x11);
	mipi_dsi_generic_write_seq(dsi, 0xff, 0x10);
	mipi_dsi_generic_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_generic_write_seq(dsi, 0x51, 0x0f, 0xff);
	mipi_dsi_generic_write_seq(dsi, 0x53, 0x2c);
	mipi_dsi_generic_write_seq(dsi, 0x55, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x01, 0x66);
	mipi_dsi_dcs_write_seq(dsi, 0x06, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x07, 0x38);
	mipi_dsi_dcs_write_seq(dsi, 0x69, 0x91);
	mipi_dsi_dcs_write_seq(dsi, 0x89, 0x17);
	mipi_dsi_dcs_write_seq(dsi, 0x95, 0xd1);
	mipi_dsi_dcs_write_seq(dsi, 0x96, 0xd1);
	mipi_dsi_dcs_write_seq(dsi, 0xf2, 0x64);
	mipi_dsi_dcs_write_seq(dsi, 0xf4, 0x64);
	mipi_dsi_dcs_write_seq(dsi, 0xf6, 0x64);
	mipi_dsi_dcs_write_seq(dsi, 0xf8, 0x64);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xb0,
			       0x00, 0x00, 0x00, 0x1e, 0x00, 0x47, 0x00, 0x67,
			       0x00, 0x82, 0x00, 0x99, 0x00, 0xae, 0x00, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0xb1,
			       0x00, 0xd1, 0x01, 0x09, 0x01, 0x32, 0x01, 0x73,
			       0x01, 0xa2, 0x01, 0xed, 0x02, 0x26, 0x02, 0x27);
	mipi_dsi_dcs_write_seq(dsi, 0xb2,
			       0x02, 0x60, 0x02, 0x9e, 0x02, 0xc8, 0x02, 0xfa,
			       0x03, 0x20, 0x03, 0x49, 0x03, 0x59, 0x03, 0x68);
	mipi_dsi_dcs_write_seq(dsi, 0xb3,
			       0x03, 0x7b, 0x03, 0x91, 0x03, 0xac, 0x03, 0xc5,
			       0x03, 0xd6, 0x03, 0xd8, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb4,
			       0x00, 0x00, 0x00, 0x1e, 0x00, 0x47, 0x00, 0x67,
			       0x00, 0x82, 0x00, 0x99, 0x00, 0xae, 0x00, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0xb5,
			       0x00, 0xd1, 0x01, 0x09, 0x01, 0x32, 0x01, 0x73,
			       0x01, 0xa2, 0x01, 0xed, 0x02, 0x26, 0x02, 0x27);
	mipi_dsi_dcs_write_seq(dsi, 0xb6,
			       0x02, 0x60, 0x02, 0x9e, 0x02, 0xc8, 0x02, 0xfa,
			       0x03, 0x20, 0x03, 0x49, 0x03, 0x59, 0x03, 0x68);
	mipi_dsi_dcs_write_seq(dsi, 0xb7,
			       0x03, 0x7b, 0x03, 0x91, 0x03, 0xac, 0x03, 0xc5,
			       0x03, 0xd6, 0x03, 0xd8, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb8,
			       0x00, 0x00, 0x00, 0x1e, 0x00, 0x47, 0x00, 0x67,
			       0x00, 0x82, 0x00, 0x99, 0x00, 0xae, 0x00, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0xb9,
			       0x00, 0xd1, 0x01, 0x09, 0x01, 0x32, 0x01, 0x73,
			       0x01, 0xa2, 0x01, 0xed, 0x02, 0x26, 0x02, 0x27);
	mipi_dsi_dcs_write_seq(dsi, 0xba,
			       0x02, 0x60, 0x02, 0x9e, 0x02, 0xc8, 0x02, 0xfa,
			       0x03, 0x20, 0x03, 0x49, 0x03, 0x59, 0x03, 0x68);
	mipi_dsi_dcs_write_seq(dsi, 0xbb,
			       0x03, 0x7b, 0x03, 0x91, 0x03, 0xac, 0x03, 0xc5,
			       0x03, 0xd6, 0x03, 0xd8, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x21);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xb0,
			       0x00, 0x00, 0x00, 0x1e, 0x00, 0x47, 0x00, 0x67,
			       0x00, 0x82, 0x00, 0x99, 0x00, 0xae, 0x00, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0xb1,
			       0x00, 0xd1, 0x01, 0x09, 0x01, 0x32, 0x01, 0x73,
			       0x01, 0xa2, 0x01, 0xed, 0x02, 0x26, 0x02, 0x27);
	mipi_dsi_dcs_write_seq(dsi, 0xb2,
			       0x02, 0x60, 0x02, 0x9e, 0x02, 0xc8, 0x02, 0xfa,
			       0x03, 0x20, 0x03, 0x49, 0x03, 0x59, 0x03, 0x68);
	mipi_dsi_dcs_write_seq(dsi, 0xb3,
			       0x03, 0x7b, 0x03, 0x91, 0x03, 0xac, 0x03, 0xc5,
			       0x03, 0xd6, 0x03, 0xd8, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb4,
			       0x00, 0x00, 0x00, 0x1e, 0x00, 0x47, 0x00, 0x67,
			       0x00, 0x82, 0x00, 0x99, 0x00, 0xae, 0x00, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0xb5,
			       0x00, 0xd1, 0x01, 0x09, 0x01, 0x32, 0x01, 0x73,
			       0x01, 0xa2, 0x01, 0xed, 0x02, 0x26, 0x02, 0x27);
	mipi_dsi_dcs_write_seq(dsi, 0xb6,
			       0x02, 0x60, 0x02, 0x9e, 0x02, 0xc8, 0x02, 0xfa,
			       0x03, 0x20, 0x03, 0x49, 0x03, 0x59, 0x03, 0x68);
	mipi_dsi_dcs_write_seq(dsi, 0xb7,
			       0x03, 0x7b, 0x03, 0x91, 0x03, 0xac, 0x03, 0xc5,
			       0x03, 0xd6, 0x03, 0xd8, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb8,
			       0x00, 0x00, 0x00, 0x1e, 0x00, 0x47, 0x00, 0x67,
			       0x00, 0x82, 0x00, 0x99, 0x00, 0xae, 0x00, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0xb9,
			       0x00, 0xd1, 0x01, 0x09, 0x01, 0x32, 0x01, 0x73,
			       0x01, 0xa2, 0x01, 0xed, 0x02, 0x26, 0x02, 0x27);
	mipi_dsi_dcs_write_seq(dsi, 0xba,
			       0x02, 0x60, 0x02, 0x9e, 0x02, 0xc8, 0x02, 0xfa,
			       0x03, 0x20, 0x03, 0x49, 0x03, 0x59, 0x03, 0x68);
	mipi_dsi_dcs_write_seq(dsi, 0xbb,
			       0x03, 0x7b, 0x03, 0x91, 0x03, 0xac, 0x03, 0xc5,
			       0x03, 0xd6, 0x03, 0xd8, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x24);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x01, 0x0f);
	mipi_dsi_dcs_write_seq(dsi, 0x03, 0x0c);
	mipi_dsi_dcs_write_seq(dsi, 0x05, 0x1d);
	mipi_dsi_dcs_write_seq(dsi, 0x08, 0x2f);
	mipi_dsi_dcs_write_seq(dsi, 0x09, 0x2e);
	mipi_dsi_dcs_write_seq(dsi, 0x0a, 0x2d);
	mipi_dsi_dcs_write_seq(dsi, 0x0b, 0x2c);
	mipi_dsi_dcs_write_seq(dsi, 0x11, 0x17);
	mipi_dsi_dcs_write_seq(dsi, 0x12, 0x13);
	mipi_dsi_dcs_write_seq(dsi, 0x13, 0x15);
	mipi_dsi_dcs_write_seq(dsi, 0x15, 0x14);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0x17, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0x1b, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x1d, 0x1d);
	mipi_dsi_dcs_write_seq(dsi, 0x20, 0x2f);
	mipi_dsi_dcs_write_seq(dsi, 0x21, 0x2e);
	mipi_dsi_dcs_write_seq(dsi, 0x22, 0x2d);
	mipi_dsi_dcs_write_seq(dsi, 0x23, 0x2c);
	mipi_dsi_dcs_write_seq(dsi, 0x29, 0x17);
	mipi_dsi_dcs_write_seq(dsi, 0x2a, 0x13);
	mipi_dsi_dcs_write_seq(dsi, 0x2b, 0x15);
	mipi_dsi_dcs_write_seq(dsi, 0x2f, 0x14);
	mipi_dsi_dcs_write_seq(dsi, 0x30, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0x31, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0x32, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x34, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0x35, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x36, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x37, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0x4d, 0x1b);
	mipi_dsi_dcs_write_seq(dsi, 0x4e, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x4f, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x53, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x71, 0x30);
	mipi_dsi_dcs_write_seq(dsi, 0x79, 0x11);
	mipi_dsi_dcs_write_seq(dsi, 0x7a, 0x82);
	mipi_dsi_dcs_write_seq(dsi, 0x7b, 0x96);
	mipi_dsi_dcs_write_seq(dsi, 0x7d, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x80, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x81, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x82, 0x13);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x31);
	mipi_dsi_dcs_write_seq(dsi, 0x85, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x86, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x87, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x90, 0x13);
	mipi_dsi_dcs_write_seq(dsi, 0x92, 0x31);
	mipi_dsi_dcs_write_seq(dsi, 0x93, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x94, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x95, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x9c, 0xf4);
	mipi_dsi_dcs_write_seq(dsi, 0x9d, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xa0, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0xa2, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0xa3, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xa4, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xa5, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xc9, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xd9, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0xe9, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x25);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x19, 0xe4);
	mipi_dsi_dcs_write_seq(dsi, 0x21, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x66, 0xd8);
	mipi_dsi_dcs_write_seq(dsi, 0x68, 0x50);
	mipi_dsi_dcs_write_seq(dsi, 0x69, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0x6b, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x6d, 0x0d);
	mipi_dsi_dcs_write_seq(dsi, 0x6e, 0x48);
	mipi_dsi_dcs_write_seq(dsi, 0x72, 0x41);
	mipi_dsi_dcs_write_seq(dsi, 0x73, 0x4a);
	mipi_dsi_dcs_write_seq(dsi, 0x74, 0xd0);
	mipi_dsi_dcs_write_seq(dsi, 0x76, 0x83);
	mipi_dsi_dcs_write_seq(dsi, 0x77, 0x62);
	mipi_dsi_dcs_write_seq(dsi, 0x79, 0x81);
	mipi_dsi_dcs_write_seq(dsi, 0x7d, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x7e, 0x15);
	mipi_dsi_dcs_write_seq(dsi, 0x7f, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x4d);
	mipi_dsi_dcs_write_seq(dsi, 0xcf, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0xd6, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0xd7, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0xef, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x84);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x26);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x80, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x81, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0x83, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x85, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x86, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x87, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x8a, 0x1a);
	mipi_dsi_dcs_write_seq(dsi, 0x8b, 0x11);
	mipi_dsi_dcs_write_seq(dsi, 0x8c, 0x24);
	mipi_dsi_dcs_write_seq(dsi, 0x8e, 0x42);
	mipi_dsi_dcs_write_seq(dsi, 0x8f, 0x11);
	mipi_dsi_dcs_write_seq(dsi, 0x90, 0x11);
	mipi_dsi_dcs_write_seq(dsi, 0x91, 0x11);
	mipi_dsi_dcs_write_seq(dsi, 0x9a, 0x81);
	mipi_dsi_dcs_write_seq(dsi, 0x9b, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x9c, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x9d, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x9e, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x27);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x01, 0x60);
	mipi_dsi_dcs_write_seq(dsi, 0x20, 0x81);
	mipi_dsi_dcs_write_seq(dsi, 0x21, 0xea);
	mipi_dsi_dcs_write_seq(dsi, 0x25, 0x82);
	mipi_dsi_dcs_write_seq(dsi, 0x26, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x6e, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x70, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x71, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x72, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x75, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x76, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x77, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x7d, 0x09);
	mipi_dsi_dcs_write_seq(dsi, 0x7e, 0x5f);
	mipi_dsi_dcs_write_seq(dsi, 0x80, 0x23);
	mipi_dsi_dcs_write_seq(dsi, 0x82, 0x09);
	mipi_dsi_dcs_write_seq(dsi, 0x83, 0x5f);
	mipi_dsi_dcs_write_seq(dsi, 0x88, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x89, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0xa5, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0xa6, 0x23);
	mipi_dsi_dcs_write_seq(dsi, 0xa7, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xb6, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0xe3, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xe4, 0xe0);
	mipi_dsi_dcs_write_seq(dsi, 0xe5, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xe6, 0x70);
	mipi_dsi_dcs_write_seq(dsi, 0xe9, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xea, 0x2f);
	mipi_dsi_dcs_write_seq(dsi, 0xeb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xec, 0x98);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x2a);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x00, 0x91);
	mipi_dsi_dcs_write_seq(dsi, 0x03, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0x07, 0x52);
	mipi_dsi_dcs_write_seq(dsi, 0x0a, 0x60);
	mipi_dsi_dcs_write_seq(dsi, 0x0c, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0x0d, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x0e, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x0f, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x11, 0x58);
	mipi_dsi_dcs_write_seq(dsi, 0x15, 0x0e);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x79);
	mipi_dsi_dcs_write_seq(dsi, 0x19, 0x0d);
	mipi_dsi_dcs_write_seq(dsi, 0x1a, 0xf2);
	mipi_dsi_dcs_write_seq(dsi, 0x1b, 0x14);
	mipi_dsi_dcs_write_seq(dsi, 0x1d, 0x36);
	mipi_dsi_dcs_write_seq(dsi, 0x1e, 0x55);
	mipi_dsi_dcs_write_seq(dsi, 0x1f, 0x55);
	mipi_dsi_dcs_write_seq(dsi, 0x20, 0x55);
	mipi_dsi_dcs_write_seq(dsi, 0x28, 0x0a);
	mipi_dsi_dcs_write_seq(dsi, 0x29, 0x0b);
	mipi_dsi_dcs_write_seq(dsi, 0x2a, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x2b, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x2d, 0x08);
	mipi_dsi_dcs_write_seq(dsi, 0x2f, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x30, 0x47);
	mipi_dsi_dcs_write_seq(dsi, 0x31, 0x23);
	mipi_dsi_dcs_write_seq(dsi, 0x33, 0x25);
	mipi_dsi_dcs_write_seq(dsi, 0x34, 0xff);
	mipi_dsi_dcs_write_seq(dsi, 0x35, 0x2c);
	mipi_dsi_dcs_write_seq(dsi, 0x36, 0x75);
	mipi_dsi_dcs_write_seq(dsi, 0x37, 0xfb);
	mipi_dsi_dcs_write_seq(dsi, 0x38, 0x2e);
	mipi_dsi_dcs_write_seq(dsi, 0x39, 0x73);
	mipi_dsi_dcs_write_seq(dsi, 0x3a, 0x47);
	mipi_dsi_dcs_write_seq(dsi, 0x46, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x47, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x4a, 0xf0);
	mipi_dsi_dcs_write_seq(dsi, 0x4e, 0x0e);
	mipi_dsi_dcs_write_seq(dsi, 0x4f, 0x8b);
	mipi_dsi_dcs_write_seq(dsi, 0x52, 0x0e);
	mipi_dsi_dcs_write_seq(dsi, 0x53, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x54, 0x14);
	mipi_dsi_dcs_write_seq(dsi, 0x56, 0x36);
	mipi_dsi_dcs_write_seq(dsi, 0x57, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x58, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x59, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x60, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x61, 0x0a);
	mipi_dsi_dcs_write_seq(dsi, 0x62, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x63, 0xed);
	mipi_dsi_dcs_write_seq(dsi, 0x65, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x66, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x67, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x68, 0x4d);
	mipi_dsi_dcs_write_seq(dsi, 0x6a, 0x0a);
	mipi_dsi_dcs_write_seq(dsi, 0x6b, 0xc9);
	mipi_dsi_dcs_write_seq(dsi, 0x6c, 0x1d);
	mipi_dsi_dcs_write_seq(dsi, 0x6d, 0xe5);
	mipi_dsi_dcs_write_seq(dsi, 0x6e, 0xc6);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0x1e);
	mipi_dsi_dcs_write_seq(dsi, 0x70, 0xe4);
	mipi_dsi_dcs_write_seq(dsi, 0x71, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x7a, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x7b, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x7c, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x7d, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x7f, 0xe0);
	mipi_dsi_dcs_write_seq(dsi, 0x83, 0x0e);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x8b);
	mipi_dsi_dcs_write_seq(dsi, 0x87, 0x0e);
	mipi_dsi_dcs_write_seq(dsi, 0x88, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x89, 0x14);
	mipi_dsi_dcs_write_seq(dsi, 0x8b, 0x36);
	mipi_dsi_dcs_write_seq(dsi, 0x8c, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x8d, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x8e, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x95, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x96, 0x0a);
	mipi_dsi_dcs_write_seq(dsi, 0x97, 0x12);
	mipi_dsi_dcs_write_seq(dsi, 0x98, 0x92);
	mipi_dsi_dcs_write_seq(dsi, 0x9a, 0x0a);
	mipi_dsi_dcs_write_seq(dsi, 0x9b, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x9c, 0x49);
	mipi_dsi_dcs_write_seq(dsi, 0x9d, 0x98);
	mipi_dsi_dcs_write_seq(dsi, 0x9e, 0x5f);
	mipi_dsi_dcs_write_seq(dsi, 0xa0, 0xff);
	mipi_dsi_dcs_write_seq(dsi, 0xa2, 0x3a);
	mipi_dsi_dcs_write_seq(dsi, 0xa3, 0xd9);
	mipi_dsi_dcs_write_seq(dsi, 0xa4, 0xfa);
	mipi_dsi_dcs_write_seq(dsi, 0xa5, 0x3c);
	mipi_dsi_dcs_write_seq(dsi, 0xa6, 0xd7);
	mipi_dsi_dcs_write_seq(dsi, 0xa7, 0x49);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x2c);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x00, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x01, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x02, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x03, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0x04, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0x05, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0x0d, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x0e, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x1b);
	mipi_dsi_dcs_write_seq(dsi, 0x17, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x18, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x19, 0x4b);
	mipi_dsi_dcs_write_seq(dsi, 0x2a, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x3b, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x4d, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0x4e, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x53, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x54, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x55, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x56, 0x0f);
	mipi_dsi_dcs_write_seq(dsi, 0x58, 0x0f);
	mipi_dsi_dcs_write_seq(dsi, 0x59, 0x0f);
	mipi_dsi_dcs_write_seq(dsi, 0x61, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x62, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x6a, 0x15);
	mipi_dsi_dcs_write_seq(dsi, 0x6b, 0x37);
	mipi_dsi_dcs_write_seq(dsi, 0x6c, 0x37);
	mipi_dsi_dcs_write_seq(dsi, 0x6d, 0x37);
	mipi_dsi_dcs_write_seq(dsi, 0x7e, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x9d, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0x9e, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0xf0);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x5a, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x25);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x18, 0x22);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0xe0);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x35, 0x82);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0xc0);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x9c, 0x11);
	mipi_dsi_dcs_write_seq(dsi, 0x9d, 0x11);
	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x35, 0x00);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	usleep_range(10000, 11000);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}

	return 0;
}

static int oppo19696jdi_nt36672c_1080_2400_90fps_off(struct oppo19696jdi_nt36672c_1080_2400_90fps *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq(dsi, 0xff, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0xfb, 0x01);

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	usleep_range(10000, 11000);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static int oppo19696jdi_nt36672c_1080_2400_90fps_prepare(struct drm_panel *panel)
{
	struct oppo19696jdi_nt36672c_1080_2400_90fps *ctx = to_oppo19696jdi_nt36672c_1080_2400_90fps(panel);
	struct device *dev = &ctx->dsi->dev;
	struct drm_dsc_picture_parameter_set pps;
	int ret;

	if (ctx->prepared)
		return 0;

	oppo19696jdi_nt36672c_1080_2400_90fps_reset(ctx);

	ret = oppo19696jdi_nt36672c_1080_2400_90fps_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	drm_dsc_pps_payload_pack(&pps, &ctx->dsc);

	ret = mipi_dsi_picture_parameter_set(ctx->dsi, &pps);
	if (ret < 0) {
		dev_err(panel->dev, "failed to transmit PPS: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_compression_mode(ctx->dsi, true);
	if (ret < 0) {
		dev_err(dev, "failed to enable compression mode: %d\n", ret);
		return ret;
	}

	msleep(28); /* TODO: Is this panel-dependent? */

	ctx->prepared = true;
	return 0;
}

static int oppo19696jdi_nt36672c_1080_2400_90fps_unprepare(struct drm_panel *panel)
{
	struct oppo19696jdi_nt36672c_1080_2400_90fps *ctx = to_oppo19696jdi_nt36672c_1080_2400_90fps(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = oppo19696jdi_nt36672c_1080_2400_90fps_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode oppo19696jdi_nt36672c_1080_2400_90fps_mode = {
	.clock = (1080 + 73 + 12 + 40) * (2400 + 32 + 2 + 30) * 120 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 73,
	.hsync_end = 1080 + 73 + 12,
	.htotal = 1080 + 73 + 12 + 40,
	.vdisplay = 2400,
	.vsync_start = 2400 + 32,
	.vsync_end = 2400 + 32 + 2,
	.vtotal = 2400 + 32 + 2 + 30,
	.width_mm = 69,
	.height_mm = 152,
};

static int oppo19696jdi_nt36672c_1080_2400_90fps_get_modes(struct drm_panel *panel,
							   struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &oppo19696jdi_nt36672c_1080_2400_90fps_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs oppo19696jdi_nt36672c_1080_2400_90fps_panel_funcs = {
	.prepare = oppo19696jdi_nt36672c_1080_2400_90fps_prepare,
	.unprepare = oppo19696jdi_nt36672c_1080_2400_90fps_unprepare,
	.get_modes = oppo19696jdi_nt36672c_1080_2400_90fps_get_modes,
};

static int oppo19696jdi_nt36672c_1080_2400_90fps_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct oppo19696jdi_nt36672c_1080_2400_90fps *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &oppo19696jdi_nt36672c_1080_2400_90fps_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	/* This panel only supports DSC; unconditionally enable it */
	dsi->dsc = &ctx->dsc;

	ctx->dsc.dsc_version_major = 1;
	ctx->dsc.dsc_version_minor = 1;

	/* TODO: Pass slice_per_pkt = 2 */
	ctx->dsc.slice_height = 20;
	ctx->dsc.slice_width = 540;
	/*
	 * TODO: hdisplay should be read from the selected mode once
	 * it is passed back to drm_panel (in prepare?)
	 */
	WARN_ON(1080 % ctx->dsc.slice_width);
	ctx->dsc.slice_count = 1080 / ctx->dsc.slice_width;
	ctx->dsc.bits_per_component = 8;
	ctx->dsc.bits_per_pixel = 8 << 4; /* 4 fractional bits */
	ctx->dsc.block_pred_enable = true;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	return 0;
}

static void oppo19696jdi_nt36672c_1080_2400_90fps_remove(struct mipi_dsi_device *dsi)
{
	struct oppo19696jdi_nt36672c_1080_2400_90fps *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id oppo19696jdi_nt36672c_1080_2400_90fps_of_match[] = {
	{ .compatible = "mdss,x3-jdi-nt36672c" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, oppo19696jdi_nt36672c_1080_2400_90fps_of_match);

static struct mipi_dsi_driver oppo19696jdi_nt36672c_1080_2400_90fps_driver = {
	.probe = oppo19696jdi_nt36672c_1080_2400_90fps_probe,
	.remove = oppo19696jdi_nt36672c_1080_2400_90fps_remove,
	.driver = {
		.name = "panel-novatek-nt36672c",
		.of_match_table = oppo19696jdi_nt36672c_1080_2400_90fps_of_match,
	},
};
module_mipi_dsi_driver(oppo19696jdi_nt36672c_1080_2400_90fps_driver);

MODULE_AUTHOR("Patriot-06 <mbmc172@gmail.com>");
MODULE_DESCRIPTION("DRM driver for NOVATEK JDI NT36672C panel with DSC");
MODULE_LICENSE("GPL");
