#include  <stdio.h>



#include "VWTranslater.h"
#include "testFunc.h"


int main(void)
{
	VWTextTranslator testTraslator;
	testTraslator.readFileToDatas(TEST_XML_PATH0);
	testTraslator.readFileToDatas(TEST_XML_PATH1);
	testTraslator.writeDatasToFile(TEXT_OUT);
	getchar();

	return 0;
	//return test();
}