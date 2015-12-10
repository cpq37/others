#include "TrResourceDefine.h"


//define string table: tring[COLUMN_COUNT]
#define SK_TR_TABLE_START char *s_StringResourceItems[ID_MAX][COLUMN_COUNT] = {
#define SK_TR_ITEM(nId, sCol0, sCol1) {sCol0, sCol1},
#define SK_TR_TABLE_END };
#include "TrResourceTable.h"

//cancel define
#undef SK_TR_TABLE_START
#undef SK_TR_ITEM
#undef SK_TR_TABLE_END

//define table:id-string[ID_MAX]
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
