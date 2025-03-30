/******************************************************************************
 *
 * Copyright(c) 2007 - 2019 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/

#include <drv_types.h>

#if defined(CONFIG_RTW_WDS) || defined(CONFIG_RTW_MESH) 

int rtw_rhashtable_walk_enter(rtw_rhashtable *ht, rtw_rhashtable_iter *iter)
{
	rhashtable_walk_enter((ht), (iter));
	return 0;
}


#endif /* defined(CONFIG_RTW_WDS) || defined(CONFIG_RTW_MESH) */
