//|-------------------------------------------------------
//|              Copyright (C) 1993 Reuters               
//|       1400 Kensington Road, Oak Brook IL  60521       
//| All rights rsvd.Duplication & distribution prohibited 
//|-------------------------------------------------------
//
// Author: 
// Created: 
// Version: 1.0
//

#ifndef _rtr_xdb_h 
#define _rtr_xdb_h


// Synopsis:
//
// Description:
//
// See Also:
//
// Inherits:
//

#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include "rtr/eli_Xlib.h"
#include "rtr/eli_Xresource.h"
#include "rtr/eli_Xlibint.h"
#include "rtr/eli_Xos.h"
#include "rtr/platform.h"

typedef long Signature;

#define QUARKQUANTUM 600;/* how much to extend quarkToStringTable by */
#define NEVERFREETABLESIZE 8180
#define HASHTABLESIZE 1024
#define HASHTABLEMASK 1023
#define HASHSIZE 64
#define HASHMASK 63
#define HashIndex(quark)(quark & HASHMASK)

typedef struct memoryNode *memoryNodePtr;
struct memoryNode {
	memoryNodePtr next;
	char* addr;
};

typedef struct _NodeRec *Node;
typedef struct _NodeRec {
	Node next;
	Signature sig;
	XrmQuark quark;
	XrmString name;
} NodeRec;

typedef bool (*DBEnumProc)(XrmBindingList,XrmQuarkList,XrmRepresentation,XrmValuePtr,caddr_t);

typedef struct _XrmHashBucketRec {
	XrmHashBucket next;       /* Next entry in this hash chain    */
	XrmQuark quark;      /* Quark for string    */
	XrmRepresentation   type;       /* Representation of value (if any)     */
	XrmValue value;      /* Value of this node (if any)    */
	XrmHashTable tables[2];  /* Hash table pointers for tight, loose */
	char hasValues[2]; /* Do any buckets in table have value */
} XrmHashBucketRec;

typedef struct _GRNData {
	char *name;
	XrmRepresentation type;
	XrmValuePtr value;
} GRNData;

class RTRXDb
{
public:

	// Constructor
	RTRXDb();

	// Destructor
	~RTRXDb();

	bool initDb(const char *filePath);
	
	int Value(const char* class_name, const char* id_name, char* eif_buf, int buf_size);

private:

    XrmDatabase     _db;
	XrmQuark		_nextQuark;/* next available quark number */
	XrmString*		_quarkToStringTable;
	int				_maxQuarks;/* max names in current quarkToStringTable */
	char*			_neverFreeTable;
	unsigned int	_neverFreeTableSize;
	memoryNodePtr	_tableMemory;
	Node			_nodeTable[HASHTABLESIZE];
	char*			_resourceQuarks;
	int				_maxResourceQuark;

	XrmQuark		XrmQString;

	char* Xpermalloc(unsigned int length);

	XrmDatabase XrmNewDatabase();

	void XrmDestroyDatabase(XrmDatabase rdb);
	void XrmFreeResource();
	void XrmFreeTables();

	bool XrmGetFileDatabase(const char *fileName);
	void PutLineResources(XrmDatabase *pdb, char *((*get_line)(char *buf,  int nchars, caddr_t dp)), caddr_t closure);

	int XrmAllocMoreQuarkToStringTable();
	XrmQuark XrmStringToQuark(const char *name);
	XrmString XrmQuarkToString(XrmQuark quark);
	void XrmStringToQuarkList(const char  *name, XrmQuarkList quarks);
	void XrmStringToBindingQuarkList(const char *name, XrmBindingList bindings, XrmQuarkList quarks);

	bool XrmGetResource(const char *name_str, const char *class_str, XrmString* pType_str, XrmValuePtr pValue);
	bool XrmQGetResource(XrmQuarkList names, XrmQuarkList classes, XrmRepresentation* pType, XrmValuePtr pValue);
	bool GetEntry(XrmHashTable tight, XrmHashTable loose, XrmQuarkList names, XrmRepresentation *type, XrmValuePtr value);

	void XrmQPutResource(XrmDatabase *pdb, XrmBindingList bindings, XrmQuarkList quarks, XrmRepresentation type, XrmValuePtr value);
	void PutEntry(XrmHashBucket bucket, XrmBindingList bindings, XrmQuarkList quarks, XrmRepresentation type, XrmValuePtr value);

	void PrintBindingQuarkList(XrmBindingList bindings, XrmQuarkList quarks, FILE *stream);
	bool DumpEntry(XrmBindingList bindings, XrmQuarkList quarks, XrmRepresentation type, XrmValuePtr value, FILE *stream);
	void PrintQuarkList(XrmQuarkList quarks, FILE *stream);
	void DumpSearchList(XrmNameList names, XrmClassList classes, XrmSearchList searchList);

	void XrmMergeDatabases(XrmDatabase __new, XrmDatabase *into);
	void Merge(XrmHashBucket __new, XrmHashBucket old);

	RTRXDb(const RTRXDb&);
};

#endif  // _rtr_xdb_h

