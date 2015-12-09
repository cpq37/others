#ifndef  __VWTranslator_H
#define  __VWTranslator_H

#include <string.h>
#include <vector>

class VWTranslator
{
public:
	VWTranslator() {}
	virtual ~VWTranslator() {}

	virtual bool readFileToDatas(const char* infile) = 0;
	virtual bool writeDatasToFile(const char* outfile) = 0;
};


class VWTextTranslator : public VWTranslator
{
public:
	typedef struct TextNode
	{
		std::string LangID;
		std::string Text;
		std::string langCode;
		int	    ID;
		TextNode* next;
		TextNode() :LangID(""),Text(""),langCode(""),ID(0),next(NULL) {}
	}TEXTNODE;

	typedef struct LanguageText
	{
		std::string langCode;
		std::vector<TEXTNODE*> textList;		//need to change to pointer

	}LANTEXTS;

	VWTextTranslator() {}
	~VWTextTranslator();

	virtual bool readFileToDatas(const char* infile) /*override*/;
	virtual bool writeDatasToFile(const char* outfile)/* override*/;

protected:
	TEXTNODE* findPrevNode(TEXTNODE& nextNode) const;

private:
	std::vector<LANTEXTS*> allLanTexts;
};


#endif // __VWTranslator_H
