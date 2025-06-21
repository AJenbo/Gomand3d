#include <stdio.h>
#include "binload.h"
#include "global.h"

Handle BinaryHandleHead=NULL;

LPVOID LoadVertex(Handle Binary,long No,LPVOID Buffer)
{ 
	char *address;
	long Length;
	if(No>*(long*)Binary->BinaryStart)
		return NULL;
	address=((char *)Binary->BinaryStart)+No*8+4;
	Length=*(((long*)address)+1)-*(long *)address+4;
	memcpy(Buffer,address+*(long *)address,Length);
	return ((char *)Buffer)+Length;
}

LPVOID LoadTriangle(Handle Binary,long No,LPVOID Buffer)
{ 
	char * address;
	long Length;
	if(No>*(long*)Binary->BinaryStart)
		return NULL;
	address=((char *)Binary->BinaryStart)+No*8+8;
	Length=*(((long*)address)+1)-*(long *)address+4;
	memcpy(Buffer,address+*(long *)address,Length);
	return ((char *)Buffer)+Length;
}

DWORD GetSize(Handle Binary,long No)
{
	long * address;
	address=(long*)Binary->BinaryStart;
	if(No>*address)
		return 0;
	return (address[No*2+3]-address[No*2+1]+8);
}

DWORD GetVCount(Handle Binary,long No)
{
	long * address;
	address=(long*)Binary->BinaryStart;
	if(No>*address)
		return 0;
	return (address[No*2+2]-address[No*2+1]+4);	
}

DWORD GetTCount(Handle Binary,long No)
{
	long * address;
	address=(long*)Binary->BinaryStart;
	if(No>*address)
		return 0;
	return (address[No*2+3]-address[No*2+2]+4);	
}

Handle CreateBinary(LPSTR FileName)
{
/*
	Handle Temp,Temp1;
	HANDLE File;
	Temp=(Handle)malloc(sizeof(struct _MyBinaryHandle));
	Temp->Next=NULL;
	Temp->Flag=0;
	if(BinaryHandleHead==NULL)
		BinaryHandleHead=Temp;
	else
	{
		Temp1=BinaryHandleHead;
		while(Temp1->Next!=NULL)
			Temp1=Temp1->Next;
		Temp1->Next=Temp;
	}
	File=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(!File)
		return NULL;
	File=CreateFileMapping(File,NULL,PAGE_READONLY,0,0,FileName);
	if(!File)
		return NULL;
	Temp->BinaryStart=MapViewOfFile(File,FILE_MAP_READ,0,0,0);
	if(!Temp->BinaryStart)
		return NULL;
	return Temp;
*/
	Handle Temp,Temp1;
	FILE *File;
	long Length,Test;
	LPVOID TempAdd;
	Temp=(Handle)malloc(sizeof(struct _MyBinaryHandle));
	Temp->Next=NULL;
	Temp->Flag=0;
	if(BinaryHandleHead==NULL)
		BinaryHandleHead=Temp;
	else
	{
		Temp1=BinaryHandleHead;
		while(Temp1->Next!=NULL)
			Temp1=Temp1->Next;
		Temp1->Next=Temp;
	}
	File=fopen(FileName,"rb");
	if(File==NULL)
	{
		BYDumpInfo("**********************************");
		BYDumpInfo("Couldn't open file");
		BYDumpInfo(FileName);
		BYDumpInfo("**********************************");
		return NULL;
	}
	if(fseek(File,0L,SEEK_END))
	{
		BYDumpInfo("**********************************");
		BYDumpInfo("bad file");
		BYDumpInfo(FileName);
		BYDumpInfo("**********************************");
		return NULL;
	}
	Length=ftell(File);
	if(!Length)
	{
		BYDumpInfo("**********************************");
		BYDumpInfo("bad file");
		BYDumpInfo(FileName);
		BYDumpInfo("**********************************");
		return NULL;
	}
	fseek(File,0L,SEEK_SET);
	TempAdd=malloc(Length);
	if(TempAdd==NULL)
	{
		BYDumpInfo("**********************************");
		BYDumpInfo("bad file");
		BYDumpInfo(FileName);
		BYDumpInfo("**********************************");
		return NULL;
	}
	Test=ftell(File);
	Length=fread(TempAdd,1,Length,File);
	Temp->BinaryStart=TempAdd;
	fclose(File);
	return Temp;
}

BOOL DeleteBinary(Handle Binary)
{
	Handle Temp;
	Temp=BinaryHandleHead;
	if(BinaryHandleHead==Binary)
		BinaryHandleHead=BinaryHandleHead->Next;
	else
	{
		while((Temp->Next!=Binary)&&(Temp->Next!=NULL))
		{
			Temp=Temp->Next;
		}
		if(Temp->Next==NULL)
			return FALSE;
		Temp->Next=Binary->Next;
	}
	free(Binary->BinaryStart);
	free(Binary);
	return TRUE;
}
