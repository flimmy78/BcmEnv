/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */
#ifndef GSCABLEDOCSSERVICEFLOWCFGTABLE_H
#define GSCABLEDOCSSERVICEFLOWCFGTABLE_H

/* column number definitions for table gsCableDocsServiceFlowCfgTable */
#define ColumnCMIndex 1
#define ColumnSFsfid 2
#define ColumnSFsid 3
#define ColumnSFCmMac 4
#define ColumnSFDirect 5
#define ColumnSFPrimary 6

#define NoneCm 0
#define MaxCMNum 256

/* function declarations */
void InitGsCableDocsServiceFlowCfgTable(void);

#if defined(__cplusplus)
extern "C"
{
#endif  //#if defined(__cplusplus)
       
Netsnmp_Node_Handler DocsServiceFlowCfgHandler;
Netsnmp_First_Data_Point  DocsServiceFlowCfgGetFirst;
Netsnmp_Next_Data_Point   DocsServiceFlowCfgGetNext;

#if defined(__cplusplus)
}
#endif  //#if defined(__cplusplus)


#endif /* GSCABLEDOCSSERVICEFLOWCFGTABLE_H */
