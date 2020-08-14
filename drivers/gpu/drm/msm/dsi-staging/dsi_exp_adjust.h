/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 * Copyright (c) Sony Mobile Communications Inc. All rights reserved.
 * Copyright (c) 2014-2018, AngeloGioacchino Del Regno <kholk11@gmail.com>
 * Copyright (c) 2018, Devries <therkduan@gmail.com>
 * Copyright (c) 2020, Diab Neiroukh <lazerl0rd@thezest.dev>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef EXPOSURE_ADJUSTMENT_H
#define EXPOSURE_ADJUSTMENT_H

#define ELVSS_OFF_THRESHOLD			CONFIG_DRM_MSM_EXP_ADJUST_THR
#define EXPOSURE_ADJUSTMENT_MIN		CONFIG_DRM_MSM_EXP_ADJUST_MIN
#define EXPOSURE_ADJUSTMENT_MAX		CONFIG_DRM_MSM_EXP_ADJUST_MAX

#define PCC_BACKLIGHT_SCALE                                                    \
	(EXPOSURE_ADJUSTMENT_MAX - EXPOSURE_ADJUSTMENT_MIN) /                  \
		ELVSS_OFF_THRESHOLD

#ifdef CONFIG_DRM_MSM_EXP_ADJUST
void ea_panel_mode_ctrl(struct dsi_panel *panel, bool enable);
bool ea_panel_is_enabled(void);
u32 ea_panel_calc_backlight(u32 bl_lvl);
#else
static inline void ea_panel_mode_ctrl(struct dsi_panel *panel, bool enable)
{
}
static inline bool ea_panel_is_enabled(void)
{
	return false;
}
static inline u32 ea_panel_calc_backlight(u32 bl_lvl)
{
	return bl_lvl;
}
#endif
#endif /* EXPOSURE_ADJUSTMENT_H */
