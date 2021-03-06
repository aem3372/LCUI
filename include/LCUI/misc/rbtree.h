﻿/* ***************************************************************************
 * rbtree.h -- Red Black Trees
 * 
 * Copyright (C) 2014 by Liu Chao <lc-soft@live.cn>
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
 * ***************************************************************************/
 
/* ****************************************************************************
 * rbtree.h -- 红黑树
 *
 * 版权所有 (C) 2014 归属于 刘超 <lc-soft@live.cn>
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
 * ***************************************************************************/

#ifndef __RBTREE_H__
#define __RBTREE_H__

LCUI_BEGIN_HEADER

typedef struct LCUI_RBTreeNodeRec_ LCUI_RBTreeNode;

struct LCUI_RBTreeNodeRec_ {
        unsigned char color;
        int key;
        void *data;
        LCUI_RBTreeNode *parent, *left, *right;
};

typedef struct LCUI_RBTreeRec_ {
        int total_node;
	int need_free_data;
	int (*judge)(void*, const void*);
	void (*destroy)(void*);
        LCUI_RBTreeNode *root;
} LCUI_RBTree;

__inline int RBTree_GetTotal( LCUI_RBTree *rbt )
{
        return rbt->total_node; 
}

__inline void RBTree_OnJudge( LCUI_RBTree *rbt, int (*func)(void*,const void*) )
{
	rbt->judge = func;
}

__inline void RBTree_OnDestroy( LCUI_RBTree *rbt, void (*func)(void*) )
{
	rbt->destroy = func;
}

__inline void RBTree_SetDataNeedFree( LCUI_RBTree *rbt, int is_true )
{
	rbt->need_free_data = is_true;
}

/** 初始化红黑树 */
LCUI_API void RBTree_Init( LCUI_RBTree *rbt );

/** 销毁红黑树 */
LCUI_API void RBTree_Destroy( LCUI_RBTree *rbt );

/** 获取第一个结点 */
LCUI_API LCUI_RBTreeNode *RBTree_First( const LCUI_RBTree *rbt );

/** 获取下一个结点 */
LCUI_API LCUI_RBTreeNode *RBTree_Next( const LCUI_RBTreeNode *node );

LCUI_API LCUI_RBTreeNode* RBTree_Search( LCUI_RBTree* rbt, int key );
LCUI_API void* RBTree_GetData( LCUI_RBTree* rbt, int key );
LCUI_API LCUI_RBTreeNode* RBTree_Insert( LCUI_RBTree *rbt, int key, void *data );
LCUI_API int RBTree_Erase( LCUI_RBTree *rbt, int key );

LCUI_API int RBTree_CustomErase( LCUI_RBTree *rbt, const void *keydata );
LCUI_API LCUI_RBTreeNode* RBTree_CustomSearch( LCUI_RBTree* rbt, const void *keydata );
LCUI_API void* RBTree_CustomGetData( LCUI_RBTree* rbt, const void *keydata );
LCUI_API LCUI_RBTreeNode* RBTree_CustomInsert( LCUI_RBTree *rbt, const void *keydata, void *data );

LCUI_END_HEADER

#endif
