#include	<stdio.h>
#include	"cmdline.h"

/* "aD:dFfHhL:lm:n:PpqR:rS:stVv" */
static option const options[] = {
	{ "buffer-audio",	'a', 'a', 0 },
	{ "data-directory",	'D', 'D', 1 },
	{ "list-directories",	'd', 'd', 2 },
	{ "full-screen",	'F', 'F', 0 },
	{ "no-frame-skip",	'f', 'f', 0 },
	{ "histogram",		'H', 'H', 0 },
	{ "levelset-directory",	'L', 'L', 1 },
	{ "list-levelsets",	'l', 'l', 0 },
	{ "mud-sucking",	'm', 'm', 1 },
	{ "volume",		'n', 'n', 1 },
	{ "pedantic",		'P', 'P', 0 },
	{ "no-passwords",	'p', 'p', 0 },
	{ "quiet",		'q', 'q', 0 },
	{ "resource-directory",	'R', 'R', 1 },
	{ "read-only",		'r', 'r', 0 },
	{ "save-directory",	'S', 'S', 1 },
	{ "list-scores",	's', 's', 0 },
	{ "list-times",		't', 't', 0 },
	{ "version-info",	'V', 'V', 0 },
	{ "version",		'v', 'v', 0 },
	{ 0, 0, 0, 0 }
};

static int optcallback(int opt, char const *val, void *data)
{
    static int	n = 0;

    switch (opt) {
      case 0:
	printf("arg %d == \"%s\"\n", ++n, val);
	break;
      case 'D':
      case 'L':
      case 'R':
      case 'S':
      case 'm':
      case 'n':
	printf("-%c == \"%s\"\n", opt, val);
	break;
      case 'H':
      case 'f':
      case 'F':
      case 'p':
      case 'q':
      case 'r':
      case 'P':
      case 'a':
      case 'l':
      case 's':
      case 't':
      case 'h':
      case 'v':
      case 'V':
	printf("-%c == true\n", opt);
	break;
      case 'd':
	printf("-%c == ", opt);
	if (val)
	    printf("\"%s\"\n", val);
	else
	    printf("true\n");
	break;
      case ':':	printf("no argument for \"%s\"\n", val);	break;
      case '=':	printf("invalid argument \"%s\"\n", val);	break;
      case '?':	printf("invalid option \"%s\"\n", val);		break;
      default:
	printf("!! bad callback parameters: callback(%d, ", opt);
	if (val)
	    printf("\"%s\")\n", val);
	else
	    printf("NULL)\n");
	break;
    }
    return 0;
    (void)data;
}

int main(int argc, char *argv[])
{
    char	buf[256];
    int		n;

    if (argc == 1) {
	while (fgets(buf, sizeof buf - 1, stdin)) {
	    makecmdline(buf, &argc, &argv);
	    for (n = argv[0] ? 0 : 1 ; n < argc ; ++n)
		printf("arg %d == <%s>\n", n, argv[n]);
	    if (argv[argc])
		printf("arg %d == <%s> !!\n", argc, argv[argc]);
	}
    } else {
	n = readoptions(options, argc, argv, optcallback, NULL);
	if (n)
	    printf("readoptions returned %d\n", n);
    }

    return 0;
}
