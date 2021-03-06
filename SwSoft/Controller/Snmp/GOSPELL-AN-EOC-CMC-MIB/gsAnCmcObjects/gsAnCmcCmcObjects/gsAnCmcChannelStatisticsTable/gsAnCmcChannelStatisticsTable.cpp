/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */

#include "SystemInclude.h"
#include "BcmController.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "Debug.h"
#include "ChannelMgt.h"

#include "gsAnCmcChannelStatisticsTable.h"
using namespace std;

#define UsAndDs 20
#define DS 128
#define US 129

typedef struct CmcChannelStatisticsT
{
    uint8_t ChIndex; 
    int ChIfIndex; 
    int ChDir;
    int ChId;
    int ChSpeed;
    int ChBandWidth;    
    int ChUtilization;
}ChannelStatisticsT;
ChannelStatisticsT ChannelStatistics[UsAndDs];

/** Initializes the gsAnCmcChannelStatisticsTable module */
void InitGsAnCmcChannelStatisticsTable(void)
{
    const oid TablOid[] = {1,3,6,1,4,1,22764,1015,9026,2,2,5};
    const size_t TablOidLen = OID_LENGTH(TablOid); 

    netsnmp_iterator_info *iinfo;
    netsnmp_handler_registration *reg;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("gsAnCmcChannelStatisticsTable:init", "initializing table gsAnCmcChannelStatisticsTable\n"));

    reg = netsnmp_create_handler_registration(
              "gsAnCmcChannelStatisticsTable", CmcChannelStatisticsTableHandler, 
              TablOid, TablOidLen,
              HANDLER_CAN_RONLY
              );

    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    netsnmp_table_helper_add_indexes(table_info,
                           ASN_INTEGER,  /* index: gsAnCmcChannelStatisticsIndex */
                           0);
    table_info->min_column = ColChannelStaticsIfIndex;// ColChannelStaticsIndex
    table_info->max_column = ColChannelStaticsUtilization;
    
    iinfo = SNMP_MALLOC_TYPEDEF( netsnmp_iterator_info );
    iinfo->get_first_data_point = ChannelStatisticsTableGetFirst;
    iinfo->get_next_data_point = ChannelStatisticsTableGetNext;
    iinfo->table_reginfo = table_info;
    
    netsnmp_register_table_iterator( reg, iinfo );

    /* Initialise the contents of the table here */
}

/* Example iterator hook routines - using 'get_next' to do most of the work */
netsnmp_variable_list *
ChannelStatisticsTableGetFirst(void **my_loop_context,
                          void **my_data_context,
                          netsnmp_variable_list *put_index_data,
                          netsnmp_iterator_info *mydata)
{
    dbgstrm << "Start." << endl;

    int j = 0;
    BASE_ErrCode ret;
    CMCOAM_UsChannelCfgT UScfg;
    CMCOAM_DsChannelCfgT DScfg;
    ChannelStatisticsT *ChannelStatisticsP = ChannelStatistics;

    for (ret = MgtChannelGetFirstUpstreamSettings(&UScfg);
            ret == BASE_OK;
            ret = MgtChannelGetNextUpstreamSettings(&UScfg, &UScfg))
    {
        ChannelStatisticsP->ChIndex = j++; 
        ChannelStatisticsP->ChIfIndex = UScfg.ifindex; 
        ChannelStatisticsP->ChDir = US; 
        ChannelStatisticsP->ChId = UScfg.us_ch_id; 
        ChannelStatisticsP->ChSpeed = 0; 
        ChannelStatisticsP->ChBandWidth = UScfg.width; 
        ChannelStatisticsP->ChUtilization = 0; 

        ++ChannelStatisticsP;
    }

    for (ret = MgtChannelGetFirstDownstreamSettings(&DScfg);
            ret == BASE_OK;
            ret = MgtChannelGetNextDownstreamSettings(&DScfg, &DScfg))
    {
        ChannelStatisticsP->ChIndex = j++; 
        ChannelStatisticsP->ChIfIndex = DScfg.ifindex; 
        ChannelStatisticsP->ChDir = DS; 
        ChannelStatisticsP->ChId = DScfg.ds_ch_id; 
        ChannelStatisticsP->ChSpeed = 0; 
        ChannelStatisticsP->ChBandWidth = 0; 
        ChannelStatisticsP->ChUtilization = 0; 

        ++ChannelStatisticsP;
    }

    *my_loop_context = ChannelStatistics;
    return ChannelStatisticsTableGetNext(my_loop_context, my_data_context, 
                                put_index_data,  mydata);
}

netsnmp_variable_list *
ChannelStatisticsTableGetNext(void **my_loop_context,
                          void **my_data_context,
                          netsnmp_variable_list *put_index_data,
                          netsnmp_iterator_info *mydata)
{
    dbgstrm << "Start." << endl;
    
    ChannelStatisticsT *ChStaticsP = (ChannelStatisticsT *)*my_loop_context;
    if (NULL == ChStaticsP)
    {
        dbgstrm << "No more next ChannelStatistics." << endl;    
        *my_loop_context = NULL;
        *my_data_context = NULL;
        return NULL;
    }
    
    if (ChStaticsP < ChannelStatistics + UsAndDs)
    {
        snmp_set_var_value(put_index_data, &ChStaticsP->ChIndex, sizeof(uint8_t));
        *my_data_context = ChStaticsP++;
        *my_loop_context = ChStaticsP;
        return put_index_data;
    }

    *my_loop_context = NULL;
    *my_data_context = NULL;
    return NULL;
}

int CmcChannelStatisticsTableGet(netsnmp_mib_handler               *handler,
                                                    netsnmp_handler_registration      *reginfo,
                                                    netsnmp_agent_request_info        *reqinfo,
                                                    netsnmp_request_info              *requests)
{
    //BASE_ErrCode errCode;

    char *UsChanName[4] = {"UsChan1", "UsChan2", "UsChan3", "UsChan4"};
    char *DsChanName[16] = {"DsChan1", "DsChan2", "DsChan3", "DsChan4", 
                                                "DsChan5", "DsChan6", "DsChan7", "DsChan8",
                                                "DsChan9", "DsChan10", "DsChan11", "DsChan12",
                                                "DsChan13", "DsChan14", "DsChan15", "DsChan16"};

    ChannelStatisticsT *Entry;    
    netsnmp_request_info *request;
    netsnmp_table_request_info *tableInfo;
    
    dbgstrm << "Start." << endl; 

    /*
     * Read-support (also covers GetNext requests)
     */
    for (request = requests; request; request = request->next) 
    {
        Entry = (ChannelStatisticsT*)netsnmp_extract_iterator_context(request);
      
        if ( NULL == Entry )
        {
            dbgstrm << "entry is NULL" << endl;
            netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHINSTANCE);
            continue;
        }

        dbgstrm << "index=" << Entry->ChIndex << endl;
        tableInfo = netsnmp_extract_table_info(request);
        switch (tableInfo->colnum) 
        {
            case ColChannelStaticsIndex:                
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER, Entry->ChIndex);
            break;
            
            case ColChannelStaticsIfIndex:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER, Entry->ChIfIndex);
            break;

            case ColChannelStaticsDir:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER, Entry->ChDir);
            break;

              case ColChannelStaticsId:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER, Entry->ChId);
            break;            
            
            case ColChannelStaticsName:
            {
                if (Entry->ChDir == US)
                    snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                      UsChanName[Entry->ChId - 1], 7 ); 
                
                if (Entry->ChDir == DS)
                    if (strlen(DsChanName[Entry->ChId - 1]) < 8)
                        snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          DsChanName[Entry->ChId - 1], 7 ); 
                    else
                        snmp_set_var_typed_value( request->requestvb, ASN_OCTET_STR,
                                          DsChanName[Entry->ChId - 1], 8 ); 
            } 
            break;            

            case ColChannelStaticsSpeed:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER, Entry->ChSpeed);
            break;   
            
            case ColChannelStaticsWidth:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER, Entry->ChBandWidth);
            break;   
            
            case ColChannelStaticsUtilization:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER, Entry->ChUtilization);
            break;   
            
            default:
                netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
            break;
        }   
    }
    return SNMP_ERR_NOERROR;
}

int CmcChannelStatisticsTableSetReserve1(netsnmp_mib_handler      *handler,
                             netsnmp_handler_registration      *reginfo,
                             netsnmp_agent_request_info        *reqinfo,
                             netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;    
}

int CmcChannelStatisticsTableSetReserve2(netsnmp_mib_handler      *handler,
                             netsnmp_handler_registration      *reginfo,
                             netsnmp_agent_request_info        *reqinfo,
                             netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}


int CmcChannelStatisticsTableSetFree(netsnmp_mib_handler               *handler,
                             netsnmp_handler_registration      *reginfo,
                             netsnmp_agent_request_info        *reqinfo,
                             netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

int CmcChannelStatisticsTableSetUndo(netsnmp_mib_handler               *handler,
                            netsnmp_handler_registration      *reginfo,
                            netsnmp_agent_request_info        *reqinfo,
                            netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}
int CmcChannelStatisticsTableSetAction(netsnmp_mib_handler               *handler,
                             netsnmp_handler_registration      *reginfo,
                             netsnmp_agent_request_info        *reqinfo,
                             netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}
int CmcChannelStatisticsTableSetCommit(netsnmp_mib_handler               *handler,
                             netsnmp_handler_registration      *reginfo,
                             netsnmp_agent_request_info        *reqinfo,
                             netsnmp_request_info              *requests)
{
    return SNMP_ERR_NOERROR;
}

typedef int(*CmcChannelStatisticsHandlerP)(netsnmp_mib_handler           *handler,
                                      netsnmp_handler_registration  *reginfo,
                                      netsnmp_agent_request_info    *reqinfo,
                                      netsnmp_request_info          *requests);

struct CmcChannelStatisticsHandlerDispath
{
    int mode;
    CmcChannelStatisticsHandlerP handler;
};

/** handles requests for the gsAnCmcCdtTransSVidTable table */
int
CmcChannelStatisticsTableHandler(
                        netsnmp_mib_handler               *handler,
                        netsnmp_handler_registration      *reginfo,
                        netsnmp_agent_request_info        *reqinfo,
                        netsnmp_request_info              *requests) 
{
    dbgstrm << "Start." << endl;
    DEBUGMSGTL(("CmcChannelStatisticsHandler:", "Processing request (%d)\n", reqinfo->mode));  
    static struct CmcChannelStatisticsHandlerDispath dispatch[7] =
    {
        /* Read-support (also covers GetNext requests) */
        {MODE_GET, CmcChannelStatisticsTableGet},
        /* Write-support */
        {MODE_SET_RESERVE1, CmcChannelStatisticsTableSetReserve1},
        {MODE_SET_RESERVE2, CmcChannelStatisticsTableSetReserve2},
        {MODE_SET_FREE, CmcChannelStatisticsTableSetFree},
        {MODE_SET_ACTION, CmcChannelStatisticsTableSetAction},
        {MODE_SET_UNDO, CmcChannelStatisticsTableSetUndo},
        {MODE_SET_COMMIT, CmcChannelStatisticsTableSetCommit},
    };
    size_t i;
    for (i = 0; i < sizeof(dispatch) /sizeof(struct CmcChannelStatisticsHandlerDispath); ++i)
    {
        if (reqinfo->mode == dispatch[i].mode)
        {
            int ret;
            ret = (*dispatch[i].handler)(handler, reginfo, reqinfo, requests);
            if (ret != SNMP_ERR_NOERROR)
            {
                printf("CmcChannelStatisticsHandler> %d operation failed, ret = %d\n",
                       dispatch[i].mode, ret);
                return ret;
            }
            break;
        }
    }
    return SNMP_ERR_NOERROR;
}

