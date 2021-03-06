/* ***************************************************************************
 * widget_base.c -- the widget base operation set.
 *
 * Copyright (C) 2012-2014 by
 * Liu Chao
 *
 * This file is part of the LCUI project, and may only be used, modified, and
 * distributed under the terms of the GPLv2.
 *
 * (GPLv2 is abbreviation of GNU General Public License Version 2)
 *
 * By continuing to use, modify, or distribute this file you indicate that you
 * have read the license and understand and accept it fully.
 *
 * The LCUI project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GPL v2 for more details.
 *
 * You should have received a copy of the GPLv2 along with this file. It is
 * usually in the LICENSE.TXT file, If not, see <http://www.gnu.org/licenses/>.
 * ****************************************************************************/

/* ****************************************************************************
 * widget_base.c -- 部件的基本操作集。
 *
 * 版权所有 (C) 2012-2014 归属于
 * 刘超
 *
 * 这个文件是LCUI项目的一部分，并且只可以根据GPLv2许可协议来使用、更改和发布。
 *
 * (GPLv2 是 GNU通用公共许可证第二版 的英文缩写)
 *
 * 继续使用、修改或发布本文件，表明您已经阅读并完全理解和接受这个许可协议。
 *
 * LCUI 项目是基于使用目的而加以散布的，但不负任何担保责任，甚至没有适销性或特
 * 定用途的隐含担保，详情请参照GPLv2许可协议。
 *
 * 您应已收到附随于本文件的GPLv2许可协议的副本，它通常在LICENSE.TXT文件中，如果
 * 没有，请查看：<http://www.gnu.org/licenses/>.
 * ****************************************************************************/

#include <LCUI_Build.h>
#include <LCUI/LCUI.h>
#include <LCUI/widget_build.h>

#define NEW_ONE(TYPE) (TYPE*)malloc(sizeof(TYPE))

/**
 * $ 可以看成是 Self，指当前模块(Widget)、函数的操作对象，这样省的手工为每个函
 * 数名加 Widget_ 前缀了。
 */
#define $(FUNC_NAME) Widget_##FUNC_NAME

LCUI_Widget LCUIRootWidget = NULL;	/**< 根级部件 */

/** 新建一个GUI部件 */
LCUI_Widget $(New)( const char *type_name )
{
	LCUI_Widget widget = NEW_ONE(struct LCUI_WidgetFull);
	widget->base.border.all = NULL;
	widget->base.border.radius.all = NULL;
	widget->base.background.color = NULL;
	widget->base.background.image = NULL;
	widget->base.background.origin = NULL;
	widget->base.background.position = NULL;
	widget->base.background.size = NULL;
	return widget;
}

/* 获取当前点命中的最上层可见部件 */
LCUI_Widget $(At)( LCUI_Widget widget, int x, int y )
{
	int i, n;
	LCUI_Widget target = NULL;

	do {
		n = LinkedList_GetTotal( &widget->children_show );
		for( i=0; i<n; ++i ) {
			LinkedList_Goto( &widget->children_show, i );
			target = (LCUI_Widget)
			LinkedList_Get( &widget->children_show );
			if( !target->style.visible ) {
				continue;
			}
			if( target->style.x.px <= x && target->style.y.px
			 && target->style.x.px + x < target->style.w.px
			 && target->style.y.px + x < target->style.h.px ) {
				widget = target;
				break;
			 }
		}
	} while( i >= n );

	return target;
}

/** 获取部件当前占用的矩形区域 */
void $(GetRect)( LCUI_Widget widget, LCUI_Rect *rect )
{
	if( widget ) {
		rect->x = widget->style.x.px;
		rect->x = widget->style.y.px;
		rect->w = widget->style.w.px;
		rect->h = widget->style.h.px;
		return;
	}
	rect->x = 0;
	rect->y = 0;
	rect->w = 0;
	rect->h = 0;
}

/** 获取部件当前可见的矩形区域 */
void $(GetValidRect)( LCUI_Widget widget, LCUI_Rect *rect )
{
	LCUI_Rect container_rect;
	$(GetRect)( widget, rect );
	while( widget ) {
		$(GetRect)( widget->parent, &container_rect );
		if( rect->x < 0 ) {
			rect->w = rect->w + rect->x;
			rect->x = 0;
		}
		if( rect->y < 0 ) {
			rect->h = rect->h + rect->y;
			rect->y = 0;
		}
		if( rect->x + rect->w > container_rect.w ) {
			rect->w = container_rect.w - rect->x;
		}
		if( rect->y + rect->h > container_rect.h ) {
			rect->h = container_rect.h - rect->y;
		}
		/** 参照物改变，区域的坐标需要加上父部件的坐标 */
		rect->x += container_rect.x;
		rect->y += container_rect.y;
		/** 切换至上一级部件 */
		widget = widget->parent;
	}
}
