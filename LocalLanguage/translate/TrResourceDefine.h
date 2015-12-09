/*******************************************************************************

* Copyright (c) 2014，德赛西威汽车电子有限公司

* All rights reserved

* 文件名: StringResourceMgr.h

* 编写者: 潘荣涛 Never_More

* 编写日期: 

* 简要描述: 字符串资源管理

* 修改记录: 

*********************************************************************************/

#pragma once
#include <string>
#ifdef WIN32
#include <../../include/UICore/StringTranslator.h>
#include <../../include/UIFrame/SVPApplication.h>
#else
#include <UICore/StringTranslator.h>
#include <UIFrame/SVPApplication.h>
#endif
using namespace std;

#define COLUMN_COUNT	2

//定义Id
#define SK_TR_TABLE_START typedef enum {
#define SK_TR_ITEM(nId, sCol0, sCol1) nId,
#define SK_TR_TABLE_END ID_MAX } SK_TR_ID;
#include "TrResourceTable.h"

//取消定义
#undef SK_TR_TABLE_START
#undef SK_TR_ITEM
#undef SK_TR_TABLE_END

ISkStringTranslator::StringItem *GetStringItems();

#define SK_TR_SET_TABLE (App()->GetStringTranslator()->SetStirngTable(GetStringItems(), ID_MAX, COLUMN_COUNT))
#define SK_TR_SETTLED_COLUMN(nCol) (App()->GetStringTranslator()->SettledColumn(nCol))
#define	SK_TR(nId) (App()->GetStringTranslator()->GetString(nId))