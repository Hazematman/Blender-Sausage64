/***************************************************************
                             main.c
                             
Program entrypoint
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "texture.h"
#include "parser.h"
#include "dlist.h"
#include "output.h"


/*********************************
        Function Prototypes
*********************************/

static void parse_programargs(int argc, char* argv[]);


/*********************************
             Globals
*********************************/

// Model data lists
linkedList list_meshes = EMPTY_LINKEDLIST;
linkedList list_animations = EMPTY_LINKEDLIST;
linkedList list_textures = EMPTY_LINKEDLIST;

// Program settings
bool global_quiet = FALSE;
bool global_fixroot = TRUE;
bool global_binaryout = FALSE;
bool global_initialload = TRUE;
char* global_outputname = "outdlist.h";
char* global_modelname = "MyModel";
unsigned int global_cachesize = 32;

// Input file pointers
static FILE *fp_m = NULL;
static FILE *fp_t = NULL;


/*==============================
    main
    Program entrypoint function
    @param The number of extra arguments
    @param An array with the arguments
==============================*/

int main(int argc, char* argv[])
{
    lexState state = STATE_NONE;
    
    // Print the program title
    printf("======== "PROGRAM_NAME" V"PROGRAM_VERSION" ========""\n");
    
    // If no arguments are given, print the argument list
    if (argc == 1)
        terminate(
            "Program arguments:\n"
            "\t-f <File>\tThe file to load\n"
            //"\t-b \t\t(optional) Binary Display List\n" // TODO
            "\t-c <Int>\t(optional) Vertex cache size (default '32')\n"
            "\t-i \t\t(optional) Omit initial display list setup\n"
            "\t-n <Name>\t(optional) Model name (default 'MyModel')\n"
            "\t-o <File>\t(optional) Output filename (default 'outdlist.h')\n"
            "\t-q \t\t(optional) Quiet mode\n"
            "\t-r \t\t(optional) Don't add root to coordinates/translations\n"
            "\t-t <File>\t(optional) A list of textures and their data\n"
        );
     
    // Parse the command line arguments
    parse_programargs(argc, argv);
    
    // Parse the textures file if it's given
    list_append(&list_textures, &texture_none);
    if (fp_t != NULL)
        parse_textures(fp_t);
        
    // Parse the model file
    parse_sausage(fp_m);
    
    // Construct a display list
    construct_dl();
    
    // Save our model data to a file
    if (!global_binaryout)
        write_output_text();
    else
        write_output_binary();
    return 0;
}


/*==============================
    parse_programargs
    Parses the arguments passed to the program
    @param The number of extra arguments
    @param An array with the arguments
==============================*/

static void parse_programargs(int argc, char* argv[])
{
    int i;
    char errbuf[256];
    
    // Parse the arguments
    for (i=1; i<argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
                case 'f':
                    i++;
                    if (i == argc)
                        terminate("Error: Incorrect number of arguments provided for '-f'\n");
                    fp_m = fopen(argv[i], "r");
                    if (fp_m == NULL)
                    {
                        sprintf(errbuf, "Unable to open file '%s'\n", argv[i]);
                        terminate(errbuf);
                    }
                    break;
                case 't':
                    i++;
                    if (i == argc)
                        terminate("Error: Incorrect number of arguments provided for '-t'\n");
                    fp_t = fopen(argv[i], "r");
                    if (fp_t == NULL)
                    {
                        sprintf(errbuf, "Error: Unable to open file '%s'\n", argv[i]);
                        terminate(errbuf);
                    }
                    break;
                case 'c':
                    i++;
                    if (i == argc)
                        terminate("Error: Incorrect number of arguments provided for '-c'\n");
                    global_cachesize = atoi(argv[i]);
                    break;
                case 'o':
                    i++;
                    if (i == argc)
                        terminate("Error: Incorrect number of arguments provided for '-o'\n");
                    global_outputname = argv[i];
                    break;
                case 'n':
                    i++;
                    if (i == argc)
                        terminate("Error: Incorrect number of arguments provided for '-n'\n");
                    global_modelname = argv[i];
                    break;
                case 'r':
                    global_fixroot = !global_fixroot;
                    break;
                case 'q':
                    global_quiet = !global_quiet;
                    break;
                case 'b':
                    global_binaryout = !global_binaryout;
                    break;
                case 'i':
                    global_initialload = !global_initialload;
                    break;
                default:
                    sprintf(errbuf, "Error: Unknown argument '%s'\n", argv[i]);
                    terminate(errbuf);
                    break;
            }
        }
        else
        {
            sprintf(errbuf, "Error: Invalid argument '%s'\n", argv[i]);
            terminate(errbuf);
        }
    }
}


/*==============================
    terminate
    Stops the program with an optional message
    @param The message to print, or NULL
==============================*/

void terminate(char* message)
{
    if (message != NULL)
        puts(message);
    exit(0);
}