#include  <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
//#include <regext.h>


#include "xml/dom/tinyxml.h"
#include "strFunc.h"


#ifdef WIN32

#ifdef _DEBUG 
#include "vld.h" 
#endif

#define TEST_XML_PATH "D:\\Projects\\LocalLanguage\\language res\\MIBG__GP_2217_20151125\\Chinese_CN.xml"
#define TEXT_OUT	  "D:\\Projects\\LocalLanguage\\language res\\test.txt"

#else
#define TEST_XML_PATH "./language res/MIBG__GP_2217_20151125/Russisch.xml"
#endif

typedef struct TextNode
{
	std::string LangID;
	std::string Text;
	std::string langCode;
	int	    ID;
	TextNode* next;
}TEXTNODE;


int main(void)
{

    
	std::vector<TEXTNODE> textList;
	const char* filename = TEST_XML_PATH;
	TiXmlDocument mXMLFile;
	TiXmlElement* root;   //表示XML文件的根节点
	FILE* fp = fopen(filename,"r");

	if(fp) //存在XML文件
	{
		mXMLFile = TiXmlDocument(filename);
		if(mXMLFile.LoadFile(TIXML_ENCODING_LEGACY)) //文档加载成功
		{
			root = mXMLFile.RootElement();
			std::string langCode = root->Attribute("langCode");
			TiXmlElement* child = root->FirstChildElement("LangID");
			TEXTNODE tempNode;
			tempNode.langCode = langCode;
			tempNode.next = NULL;
			tempNode.ID = 0;
			for (child;child;child = child->NextSiblingElement())
			{
				tempNode.langCode = langCode;
				tempNode.next = NULL;
				tempNode.LangID = child->Attribute("ID");
				tempNode.Text = child->Attribute("Text");
				textList.push_back(tempNode);

				tempNode.ID++;
			}
		}

		fclose(fp);
		fp = NULL;
	}
    
	getchar();
	std::vector<TEXTNODE>::iterator it = textList.begin();
	while( it != textList.end() )
	{
        //printf("%d\n", it->ID);
#ifdef WIN32
		printf("%d : %s		%s\n", it->ID, UTF8_To_string_Ex(it->LangID).c_str(), UTF8_To_string(it->Text).c_str() );
#else
        printf("%d: %s  %s\n", it->ID, insteadSpecialChar(it->LangID).c_str(), it->Text.c_str() );
#endif
		it++;
	}
    
	getchar();
	return 0;
}
