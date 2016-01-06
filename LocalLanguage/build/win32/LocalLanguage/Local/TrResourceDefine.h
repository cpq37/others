/*******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公�?

* All rights reserved

* 文件�? TrResourceDefine.h

* 编写�? ChenPeiquan

* 编写日期: 

* 简要描�? 字符串资源管�?

* 修改记录: 

*********************************************************************************/

#pragma once
#include <string>
#ifdef WIN32
//#include <../../include/UICore/StringTranslator.h>
//#include <../../include/UIFrame/SVPApplication.h>
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

//定义字符表string[COLUMN_COUNT]
#define SK_TR_TABLE_START  char const * const s_StringResourceItems[ID_MAX][COLUMN_COUNT] = {
#define SK_TR_ITEM(nId, sCol0, sCol1) {sCol0, sCol1},
#define SK_TR_TABLE_END };
#include "TrResourceTable.h"

//取消定义
#undef SK_TR_TABLE_START
#undef SK_TR_ITEM
#undef SK_TR_TABLE_END
/*
//定义二维表id-string[ID_MAX]
#define SK_TR_TABLE_START ISkStringTranslator::StringItem s_Items[ID_MAX] = {
#define SK_TR_ITEM(nId, sCol0, sCol1) {nId, s_StringResourceItems[nId]},
#define SK_TR_TABLE_END };
#include "TrResourceTable.h"


#undef SK_TR_TABLE_START
#undef SK_TR_ITEM
#undef SK_TR_TABLE_END


ISkStringTranslator::StringItem *GetStringItems()
{
	return s_Items;
}


#define SK_TR_SET_TABLE (App()->GetStringTranslator()->SetStirngTable(GetStringItems(), ID_MAX, COLUMN_COUNT))
#define SK_TR_SETTLED_COLUMN(nCol) (App()->GetStringTranslator()->SettledColumn(nCol))
#define	SK_TR(nId) (App()->GetStringTranslator()->GetString(nId))

const char* GetVWString(int nId)
{
	unsigned int lang_id = 0;
	SVP_GetLanguage( lang_id);
	//SVP_INFO("CPQ->lang_id:%d", lang_id);
	SK_TR_SETTLED_COLUMN( LID_ZH_CN == lang_id ? 0 : 1 ); 
	return SK_TR(nId);
}

SVPString string_replace(const SVPString&s1, const SVPString&s2, const SVPString&s3)
{
	SVPString retStr = s1;
	SVPString::size_type pos=0;
	SVPString::size_type a=s2.size();
	SVPString::size_type b=s3.size();
	while((pos=retStr.find(s2,pos))!=std::string::npos)
	{
		retStr.replace(pos,a,s3);
		pos+=b;
	}

	return retStr;
}
*/

