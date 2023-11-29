#include <stdio.h>
#include <ctype.h>
// lower: convert input to lower case

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF) putc(c, ofp);
    /*
    Working with lines of text (text files)

        char *fgets(char *line, int maxline, FILE *fp)
            fgets reads the next input line (including the newline) from file fp into the
            character array line; at most maxline-1 characters will be read. The
            resulting line is terminated with '\0’

        int fputs(char *line, FILE *fp)
            Outputs ‘line’ to file ‘fp’ and adds a ’\n’ for us.
        We can also, fscanf and fprintf…!
    */

   /*
   Reading and writing ‘records’ (binary files)
        size_t fread(void *ptr, size_t size, size_t nobj, FILE *fp);
            • fread reads from stream into the array ptr at most nobj objects
            of size size
            • fread returns the number of objects read; this may be less than
            the number requested
            • feof and ferror must be used to determine status
        • There’s also:
            size_t fwrite(const void *ptr, size_t size, size_t nobj, FILE *fp);
   */
}

int main()
{
    int c;
    while ((c = getchar()) != EOF) putchar(tolower(c));

    FILE *inFile = fopen("input", "r"),
    *outFile = fopen("output", "w");
    if (inFile && outFile) {
        filecopy(inFile, outFile);
        fclose(outFile);
        fclose(inFile);
    }

    return 0;
}