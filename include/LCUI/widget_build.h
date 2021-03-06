﻿/* ***************************************************************************
 * widget_build.h -- system APIs for GUI widget.
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
 * widget_build.h -- GUI部件的系统操作函数，主要用于widget开发。
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

#ifndef __LCUI_WIDGET_BUILD_H__
#define __LCUI_WIDGET_BUILD_H__

LCUI_BEGIN_HEADER

typedef struct {
	double px;
	double scale;
	int which;
} PixelOrScale;

typedef struct LCUI_WidgetFull* LCUI_Widget;

#include <LCUI/gui/widget_base.h>

/** 部件样式 */
typedef struct LCUI_WidgetStyle {
	LCUI_BOOL visible;			/**< 是否可见 */
	int position;				/**< 定位方式 */
	int dock;				/**< 停靠位置 */
	PixelOrScale x, y;			/**< 当前坐标 */
	PixelOrScale offset_x, offset_y;	/**< 水平、垂直坐标偏移量 */
	union {
		PixelOrScale w, width;		/**< 部件区域宽度 */
	};
	union {
		PixelOrScale h, height;		/**< 部件区域高度 */
	};
	enum {
		CONTENT_BOX,
		BORDER_BOX,
		PADDING_BOX
	} box_sizing;

	struct {
		PixelOrScale top, right, bottom, left;
	} margin, padding;		/**< 外边距, 内边距 */

	struct {
		LCUI_Graph image;	/**< 背景图 */
		LCUI_Color color;	/**< 背景色 */
	
		struct {
			LCUI_BOOL x, y;
		} repeat;		/**< 背景图是否重复 */

		int clip;		/**< 背景图的裁剪方式 */

		struct {
			StyleVar x, y;
		} position;		/**< 定位方式 */
		struct {
			PixelOrScale w, h;
		} size;
		int origin;		/**< 相对于何种位置进行定位 */
	} background;

	struct {
		int x, y;		/**< 位置 */
		int blur;		/**< 模糊距离 */
		int spread;		/**< 扩散大小 */
		LCUI_Color color;	/**< 颜色 */
	} shadow;			/**< 阴影 */

	struct {
		struct {
			int width;
			int style;
			LCUI_Color color;
		} top, right, bottom, left;
		unsigned int top_left_radius;
		unsigned int top_right_radius;
		unsigned int bottom_left_radius;
		unsigned int bottom_right_radius;
	} border;			/**< 边框 */

	float opacity;			/**< 不透明度，有效范围从 0.0 （完全透明）到 1.0（完全不透明） */
	struct {
		struct {
			float x, y;
		} scale;		/**< 2D 缩放 */
		float rotate;		/**< 2D 旋转角度 */
	} transform;

} LCUI_WidgetStyle;

/** 部件结构（完整版） */
struct LCUI_WidgetFull {
	LCUI_WidgetBase		base;		/**< 基础数据及操作集 */
	LCUI_WidgetStyle	style;		/**< 样式 */
	char			*type_name;	/**< 类型名称 */
	LCUI_BOOL		autosize;	/**< 指定是否自动调整自身的大小，以适应内容的大小 */
	LCUI_BOOL		focus;		/**< 指定该部件是否需要焦点 */
	LCUI_Widget		focus_widget;	/**< 获得焦点的子部件 */

	LCUI_Widget		parent;		/**< 父部件 */
	LinkedList		children;	/**< 子部件 */
	LinkedList		children_show;	/**< 子部件的显示顺序 */
	LCUI_EventBox		event;		/**< 事件记录 */
	LCUI_DirtyRectList	dirty_rects;	/**< 记录无效区域（脏矩形） */
	void			*private_data;	/**< 私有数据 */
};

typedef union LCUI_WidgetTaskData {
	struct {
		int x, y; 
	} move;				/**< 移动位置 */
	struct {
		int width, height;
	} resize;			/**< 调整大小 */
	struct {
		LCUI_BOOL visible;
	} show;				/**< 显示/隐藏 */
	void *data;			/**< 自定义任务数据 */
} LCUI_WidgetTaskData;			/**< 部件任务数据 */

typedef struct LCUI_WidgetTask {
	int type;
	LCUI_Widget target;
	LCUI_WidgetTaskData data;
} LCUI_WidgetTask;

LCUI_END_HEADER

#include <LCUI/gui/widget_task.h>
#include <LCUI/gui/widget_event.h>
#include <LCUI/gui/widget_paint.h>

#endif
