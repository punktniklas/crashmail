#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include <shared/types.h>
#include <oslib/osfile.h>

osFile osOpen(char *name,ulong mode)
{
   FILE *fh;

   if(mode == MODE_NEWFILE) 
	{
		fh=fopen(name,"wb");
	}
   else if(mode == MODE_OLDFILE) 
	{
		fh=fopen(name,"rb");
	}
	else
	{
   	if(!(fh=fopen(name,"r+b")))
	      fh=fopen(name,"w+b");
	}
	
   return (osFile) fh;
}

void osClose(osFile os)
{
    fclose((FILE *)os);
}

int osGetChar(osFile os)
{
   int c;

   c=fgetc((FILE *)os);

   if(c==EOF)
      c=-1;

   return(c);
}

ulong osRead(osFile os,void *buf,ulong bytes)
{
   return fread(buf,1,bytes,(FILE *)os);
}

bool osPutChar(osFile os, char ch)
{
   if(fputc(ch,(FILE *)os)==EOF)
		return(FALSE);
		
	return(TRUE);
}

bool osWrite(osFile os,const void *buf,ulong bytes)
{
   if(fwrite(buf,1,bytes,(FILE *)os)!=bytes)
		return(FALSE);
		
	return(TRUE);
}

bool osPuts(osFile os,char *str)
{
   if(fputs(str,(FILE *)os)==EOF)
		return(FALSE);
		
	return(TRUE);
}

ulong osFGets(osFile os,char *str,ulong max)
{
   char *s;

   s=fgets(str,max,(FILE *)os);

   if(s)
   {
      if(strlen(s)>=2 && s[strlen(s)-1]==10 && s[strlen(s)-2]==13)
      {
         /* CRLF -> LF */

         s[strlen(s)-2]=10;
         s[strlen(s)-1]=0;
      }

      return (ulong)strlen(s);
   }

   return(0);
}

ulong osFTell(osFile os)
{
   return ftell((FILE *)os);
}


bool osFPrintf(osFile os,char *fmt,...)
{
   va_list args;
	int res;
	
   va_start(args, fmt);
   res=vfprintf(os,fmt,args);
   va_end(args);
	
	if(!res)
		return(FALSE);
		
	return(TRUE);
}

bool osVFPrintf(osFile os,char *fmt,va_list args)
{
	int res;
	
   res=vfprintf(os,fmt,args);
	
	if(!res)
		return(FALSE);
		
	return(TRUE);
}

void osSeek(osFile fh,ulong offset,short mode)
{
   int md;

   if(mode == OFFSET_BEGINNING)
      md=SEEK_SET;

   if(mode == OFFSET_END)
      md=SEEK_END;

   fseek((FILE *)fh,offset,md);
}
