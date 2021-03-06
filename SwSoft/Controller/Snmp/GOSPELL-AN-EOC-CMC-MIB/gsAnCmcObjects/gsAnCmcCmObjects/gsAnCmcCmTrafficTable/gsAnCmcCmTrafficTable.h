/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */
#ifndef GSANCMCCMTRAFFICTABLE_H
#define GSANCMCCMTRAFFICTABLE_H

/* function declarations */
void InitGsAnCmcCmTrafficTable(void);

#if defined(__cplusplus)
           extern "C"
           {
#endif  //#if defined(__cplusplus)

Netsnmp_Node_Handler CmTrafficTableHandler;
Netsnmp_First_Data_Point CmTrafficTableGetFirst;
Netsnmp_Next_Data_Point CmTrafficTableGetNext;
       
/* column number definitions for table gsAnCmcCmTrafficTable */
#define ColCmMac 1
#define ColCmIfIndex 2
#define ColCmIfInErrors 7
#define ColCmIfInOctets 3
#define ColCmIfInDiscards 6
#define ColCmIfInUcastPkts 4
#define ColCmIfInNUcastPkts 5
#define ColCmIfInUnknownProtos 8
#define ColCmIfOutOctets 9
#define ColCmIfOutErrors 13
#define ColCmIfOutDiscards 12
#define ColCmIfOutUcastPkts 10
#define ColCmIfOutNUcastPkts 11

#define NoneCm 0
#define NoneCpe 0
#define MaxCmNum 256
#define MaxCpeNum 256
#define CmTrafficIndexBegin 1
#define FirstCmTrafificArrayIndex 0
       
       
              
#if defined(__cplusplus)
           }
#endif  //#if defined(__cplusplus)
      

#endif /* GSANCMCCMTRAFFICTABLE_H */
