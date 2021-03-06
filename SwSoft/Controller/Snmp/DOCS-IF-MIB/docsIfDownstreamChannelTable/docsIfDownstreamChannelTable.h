/*
 * Note: this file originally auto-generated by mib2c using
 *  : mib2c.iterate.conf 17695 2009-07-21 12:22:18Z dts12 $
 */
#ifndef _docsIfDownstreamChannelTable_h_
#define _docsIfDownstreamChannelTable_h_

void InitDocsIfDownChannelTable(void);

#if defined(__cplusplus)
extern "C"
{
#endif  //#if defined(__cplusplus)

/*
 * function declarations..
 */
Netsnmp_Node_Handler      DocsIfDownChannelHandler;

Netsnmp_First_Data_Point  DocsIfDownChannelGetFirst;
Netsnmp_Next_Data_Point   DocsIfDownChannelGetNext;

/* column number definitions for table docsIfDownstreamChannelTable */
#define ColumnDocsIfDownChannelId          1
#define ColumnDocsIfDownChannelFrequency   2
#define ColumnDocsIfDownChannelWidth       3
#define ColumnDocsIfDownChannelModulation  4
#define ColumnDocsIfDownChannelInterleave  5
#define ColumnDocsIfDownChannelPower       6
#define ColumnDocsIfDownChannelAnnex       7
#define ColumnDocsIfDownChannelStorageType 8

#if defined(__cplusplus)
}
#endif  //#if defined(__cplusplus)

#endif /* _docsIfDownstreamChannelTable_h_ */
