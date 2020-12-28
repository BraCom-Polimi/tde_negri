# include <stdio.h>
int TT(char c)
{ if ((c>='a'&& c<='d') || (c>='f' && c<='m'))return 1; else return 0; }
char *f ( char *s)
{ while ( TT(*s) ) s++; while ( !(TT(*s)==1)) s++; return s;
}
char *ext(char *s)
{while (TT(*s)==1) s++; return s;}
int main() {
char T[50] = "abbcepqrsabcecorretta";
char *t= ext(f(&T[3])); printf( "%s\n",t);
}