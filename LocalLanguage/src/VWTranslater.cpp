#include "VWTranslater.h"
#include "strFunc.h"

#include "xml/dom/tinyxml.h"


#include <fstream>
#include <iostream>
#include <exception>

VWTextTranslator::~VWTextTranslator()
{
	std::vector<LANTEXTS*>::iterator itLan = allLanTexts.begin();
	while( itLan != allLanTexts.end() )
	{
		std::vector<TEXTNODE*>::iterator it = (*itLan)->textList.begin();
		while( it != (*itLan)->textList.end() )
		{	
			if( *it )
			{
				delete (*it);
				(*it) = NULL;
			}
			it++;
		}

		if( *itLan )
		{
			delete (*itLan);
			(*itLan) = NULL;
		}
		itLan++;
	}
}

bool VWTextTranslator::readFileToDatas(const char* infile) 
{
	TiXmlDocument mXMLFile;
	TiXmlElement* root;   //表示XML文件的根节点
	

	FILE* fp = fopen(infile,"r");
	if(fp) //存在XML文件
	{
		LANTEXTS* languageTexts = new LANTEXTS;
		mXMLFile = TiXmlDocument(infile);
		if(mXMLFile.LoadFile(TIXML_ENCODING_LEGACY)) //文档加载成功
		{
			root = mXMLFile.RootElement();
			std::string langCode = root->Attribute("langCode");
			languageTexts->langCode = langCode;
			TiXmlElement* child = root->FirstChildElement("LangID");
			
			for (child;child;child = child->NextSiblingElement())
			{
				TEXTNODE* tempNode = new TEXTNODE;
				tempNode->langCode = langCode;
				tempNode->next = NULL;
				tempNode->ID = languageTexts->textList.size();
				tempNode->langCode = langCode;
				tempNode->LangID = child->Attribute("ID");
				tempNode->Text = child->Attribute("Text");
				tempNode->next = NULL;
				TEXTNODE* pPrevNode = findPrevNode(*tempNode);
				if( pPrevNode ) 
				{
					tempNode->ID = pPrevNode->ID;
				}
				
				if( NULL == findTheSameNode(languageTexts->textList, *tempNode) )
				{
					languageTexts->textList.push_back(tempNode);
				}
				else
				{
					delete tempNode;
				}
			}
		}

		fclose(fp);
		fp = NULL;
		allLanTexts.push_back(languageTexts);
	}
	else
	{
		printf("open file:\"%s\" fail!\n", infile);
		return false;
	}

	
	return true;
}


bool VWTextTranslator::writeDatasToFile(const char* outfile)
{
    std::ofstream outFile;
    try
    {
        if( allLanTexts.size() )
        {
            outFile.open(outfile,std::ios::out|std::ios::binary);

            if( !outFile )
            {
                printf("open file:\"%s\" fail!\n", outfile);
                return false;
            }
            std::vector<TEXTNODE*>::iterator it = (*allLanTexts.begin())->textList.begin();
            outFile << ("SK_TR_TABLE_START") << std::endl;
            while( it != (*allLanTexts.begin())->textList.end() )
            {
                if( *it )
                {
                    outFile << "SK_TR_ITEM(" << insteadSpecialChar((*it)->LangID) << ", \"" << string_replace((*it)->Text, "\"","\\\"") << "\"";
                    TEXTNODE* pNextNode = (*it)->next;
                    while( pNextNode )
                    {
                        outFile << ", \"" << string_replace(pNextNode->Text, "\"", "\\\"") << "\"";
                        pNextNode = pNextNode->next;
                    }
                    outFile<< ")" << std::endl;
                    it++;
                }

            }
            outFile << "SK_TR_TABLE_END" << std::endl;
            outFile.close();
        }
        else
        {
            return false;
        }

    }
    catch(std::exception& e)
    {
        std::cout << "fail: " << e.what() << std::endl;  
        return false;
    }

    return true;
}

VWTextTranslator::TEXTNODE* VWTextTranslator::findPrevNode(TEXTNODE& nextNode) const
{

    if(allLanTexts.size() > 0)
    {
        LANTEXTS* prevLang =  allLanTexts.back();
        TEXTNODE* tempNode = prevLang->textList.at(nextNode.ID);
        if( 0 == tempNode->LangID.compare(nextNode.LangID ) )
		{
			tempNode->next = &nextNode;
			return tempNode;
		}
		else
		{
			std::vector<TEXTNODE*>::iterator it = prevLang->textList.begin();
			while( it != prevLang->textList.end() )
			{
				if( *it )
				{
					if( 0 == (*it)->LangID.compare(nextNode.LangID) )
					{
						(*it)->next = &nextNode;
						return *it;
					}
				}

				it++;
			}
		}
	}
	else
	{
		return NULL;
	}

	return NULL;
}

VWTextTranslator::TEXTNODE* VWTextTranslator::findTheSameNode(std::vector<TEXTNODE*> &textlist,TEXTNODE& nextNode) const
{
	if(textlist.size() > 0)
	{
		std::vector<TEXTNODE*>::iterator it = textlist.begin();
		while( it != textlist.end() )
		{
			if( *it )
			{
				if( 0 == (*it)->LangID.compare(nextNode.LangID) )
				{
					(*it)->next = &nextNode;
					return *it;
				}
			}

			it++;
		}
	}
	else
	{
		return NULL;
	}

	return NULL;
}
