#include  <stdio.h>



#include "VWTranslater.h"
#include "testFunc.h"
#include "getopt.h"


#ifdef WIN32
#ifdef _DEBUG 
#include "vld.h" 
#endif
#endif


#define VERSION "v1.0"
#define EXE_NAME "VWTranslator"
#define DEFAULT_OUT_FILE "TrResourceTable.h"

/* holler :
fake varargs -- need to do this way because we wind up calling through
more levels of indirection than vanilla varargs can handle, and not all
machines have vfprintf/vsyslog/whatever!  6 params oughta be enough. */
void holler (char *str, char *p1=NULL, char *p2=NULL, char *p3=NULL, char *p4=NULL, char *p5=NULL, char *p6=NULL)
{
	fprintf (stderr, str, p1, p2, p3, p4, p5, p6);
	fprintf (stderr, "\n");
	fflush (stderr);
} /* holler */

inline void display_version(void)
{
	printf("[%s %s by ChenPeiquan]\n", VERSION, EXE_NAME);
}

void display_usage(void)
{
	puts("VWTranslator - convert XML to header file");
	puts("usage:  VWTranslator [-o outfile] -i inputfile1 inputfile2");
}

void help_me(void)
{
	display_usage();
	holler("options:");
	holler ("\
	-i file1 file2	input XML file\n\
	-o file		output header file\n\
	-v		display the version information\n\
	-h		help");
}

int main(int argc, char **argv)
{
	char x = 0;
	int m_inputfileIndex =0;
	//int m_outfileIndex = 0;
	std::string strOutfile = DEFAULT_OUT_FILE;
	int m_endIndex =0;
	VWTextTranslator m_VWTraslator;

	if( 1== argc )
	{
		display_version();
		display_usage();
	}
	else
	{
		printf("argc:%d; %s\n", argc, argv[0]);
		display_version();
	}


	while ((x = getopt (argc, argv, "o:i:vh?")) != EOF)
	{
// 		printf("optind:%d\n",optind);
// 		printf("optarg:%s\n",optarg);
		m_endIndex = optind;
		switch(x)
		{
		case 'o':
			strOutfile = argv[optind-1];
			break;
		case 'i':
			m_inputfileIndex = optind - 1;
			m_VWTraslator.readFileToDatas(argv[optind-1]);
			//printf("file1:%s; file2:%s\n", argv[optind-1], argv[optind]);
			break;
		case 'h':
		case '?':
			help_me();
			break;
		case 'v':
			display_version();
			//display_usage();
			break;
		default:
			break;
		}
	}

	//printf("optind:%d;optopt:%c;end:%d\n",optind, optopt, m_endIndex);
	
	int iFileCount = 0;
	if( m_endIndex < argc )
	{
		iFileCount = argc - optind;
	}
	else
	{
		iFileCount = m_endIndex - optind;
	}

	for(int i=0; i<(iFileCount);i++)
	{
		m_VWTraslator.readFileToDatas(argv[optind+i]);
	}


	if( m_VWTraslator.writeDatasToFile(strOutfile.c_str()) )
    {
#ifdef WIN32
		puts("Generate Header file sucess!");
#else
        puts("\033[31mGenerate Header file sucess!\033[0m \n");
#endif
    }

#if WIN32 && _DEBUG
	getchar();
#endif

	return (0);
}
