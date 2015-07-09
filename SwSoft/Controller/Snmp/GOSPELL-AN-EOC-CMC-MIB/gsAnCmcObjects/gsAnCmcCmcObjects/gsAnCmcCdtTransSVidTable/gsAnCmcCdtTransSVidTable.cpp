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
#include "CnuServiceMgt.h"

#include "gsAnCmcCdtTransSVidTable.h"
using namespace std;

typedef struct CmcCdtTransSVidEntry
{
    int CdtCos;
    int CdtTransSVid;
    char CdtTransSVidRowStatus;
}CdtTransSVidEntryT;
CdtTransSVidEntryT CdtTransSVidEntry;

/** Initialize the gsAnCmcCdtTransSVidTable table by defining its contents and how it's structured */
void InitGsAnCmcCdtTransSVidTable(void)
{
    const oid CmcCdtTransSVidTableOid[] = {1,3,6,1,4,1,22764,1015,9026,2,2,2};
    const size_t CmcCdtTransSVidTableOidLen   = OID_LENGTH(CmcCdtTransSVidTableOid);

    netsnmp_iterator_info *iinfo;
    netsnmp_handler_registration *reg;
    netsnmp_table_registration_info *table_info;

    DEBUGMSGTL(("gsAnCmcCdtTransSVidTable:init", "initializing table gsAnCmcCdtTransSVidTable\n"));

    reg = netsnmp_create_handler_registration("gsAnCmcCdtTransSVidTable",
        CmcCdtTransSVidTableHandler,
        CmcCdtTransSVidTableOid,
        CmcCdtTransSVidTableOidLen,
        HANDLER_CAN_RWRITE        );

    table_info = SNMP_MALLOC_TYPEDEF( netsnmp_table_registration_info );
    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER, 0);
    table_info->min_column = ColCmcCdtTransSVid;
    table_info->max_column = ColCmcCdtTransSVidRowStatus;
    
    iinfo = SNMP_MALLOC_TYPEDEF( netsnmp_iterator_info );
    iinfo->get_first_data_point = CmcCdtTransSVidTableGetFirst;
    iinfo->get_next_data_point = CmcCdtTransSVidTableGetNext;
    iinfo->table_reginfo = table_info;
    
    netsnmp_register_table_iterator( reg, iinfo );
}

/* Example iterator hook routines - using 'get_next' to do most of the work */
netsnmp_variable_list* CmcCdtTransSVidTableGetFirst(void **my_loop_context,
    void **my_data_context,
    netsnmp_variable_list *put_index_data,
    netsnmp_iterator_info *mydata)
{
    dbgstrm << "Start." << endl;

    BASE_ErrCode errCode;

    CdtTransSVidEntryT *entryP = &CdtTransSVidEntry; 
    entryP->CdtCos = 1;
    entryP->CdtTransSVid = 1;
    entryP->CdtTransSVidRowStatus = 1;    

    errCode = BASE_OK;
    if ( BASE_OK != errCode )
    {
        dbgstrm << "GetFirstVid error." << endl;
        *my_loop_context = NULL;
        *my_data_context = NULL;
        return NULL;
    }

    dbgstrm << "Index=" << entryP->CdtCos << endl;    
    snmp_set_var_value(put_index_data, &entryP->CdtCos, sizeof(uint32_t));

    *my_loop_context = (void *)entryP;
    *my_data_context = (void *)entryP;
    return put_index_data;   
}

netsnmp_variable_list* CmcCdtTransSVidTableGetNext(void **my_loop_context,
    void **my_data_context,
    netsnmp_variable_list *put_index_data,
    netsnmp_iterator_info *mydata)
{
    dbgstrm << "Start." << endl;

    if (NULL == *my_loop_context)
    {
        dbgstrm << "No more Next Vid ." << endl;
        *my_loop_context = NULL;
        *my_data_context = NULL;
        return NULL;         
    }
    CdtTransSVidEntryT *entryP  = (CdtTransSVidEntryT *) (*my_loop_context);

    BASE_ErrCode errCode;   
    errCode = BASE_ERROR; 
    if ( BASE_OK != errCode )
    {
        dbgstrm << "GetNextVid error." << endl;
        *my_loop_context = NULL;
        *my_data_context = NULL;
        return NULL; 
    }

    dbgstrm << "Index=" << entryP->CdtCos << endl;
    snmp_set_var_value(put_index_data, &entryP->CdtCos, sizeof(uint32_t));
    
    *my_loop_context = (void *)entryP;
    *my_data_context = (void *)entryP;
    return put_index_data; 
}

int CmcCdtTransSVidTableGet(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    //BASE_ErrCode errCode;
    CdtTransSVidEntryT *entryP;
    
    netsnmp_request_info *request;
    netsnmp_table_request_info *tableInfo;
    
    dbgstrm << "Start." << endl; 

    /*
     * Read-support (also covers GetNext requests)
     */
    for (request = requests; request; request = request->next) 
    {
        entryP = (CdtTransSVidEntryT *)netsnmp_extract_iterator_context(request);    
        if ( NULL == entryP )
        {
            dbgstrm << "entry is NULL" << endl;
            netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHINSTANCE);
            continue;
        }
        dbgstrm << "index=" << entryP->CdtCos << endl;

        tableInfo = netsnmp_extract_table_info(request);
        switch (tableInfo->colnum) 
        {           
            case ColCmcCdtTransSVid:
                snmp_set_var_typed_integer(request->requestvb,
                    ASN_INTEGER,
                    entryP->CdtTransSVid);
            break;
            
            case ColCmcCdtTransSVidRowStatus:
                dbgstrm << "RowStatus=" << entryP->CdtTransSVidRowStatus << endl;
                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER,
                                            entryP->CdtTransSVidRowStatus);
            break;            
            
            default:
                netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT);
            break;
        }   
    }
    return SNMP_ERR_NOERROR;
}

int CmcCdtTransSVidTableSetReserve1(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    return SNMP_ERR_NOERROR;
}

int CmcCdtTransSVidTableSetReserve2(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    return SNMP_ERR_NOERROR;
}

int CmcCdtTransSVidTableSetFree(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    return SNMP_ERR_NOERROR;
}

int CmcCdtTransSVidTableSetUndo(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    return SNMP_ERR_NOERROR;
}
int CmcCdtTransSVidTableSetAction(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    return SNMP_ERR_NOERROR;
}
int CmcCdtTransSVidTableSetCommit(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    return SNMP_ERR_NOERROR;
}

typedef int(*CmcCdtTransSVidHandlerP)(netsnmp_mib_handler           *handler,
                                      netsnmp_handler_registration  *reginfo,
                                      netsnmp_agent_request_info    *reqinfo,
                                      netsnmp_request_info          *requests);

struct CmcCdtTransSVidHandlerDispath
{
    int mode;
    CmcCdtTransSVidHandlerP handler;
};


/** handles requests for the gsAnCmcCdtTransSVidTable table */
int
CmcCdtTransSVidTableHandler(netsnmp_mib_handler *handler,
    netsnmp_handler_registration *reginfo,
    netsnmp_agent_request_info *reqinfo,
    netsnmp_request_info *requests)
{
    dbgstrm << "Start." << endl;
    DEBUGMSGTL(("CmUniTableHandler:", "Processing request (%d)\n", reqinfo->mode));  
    static struct CmcCdtTransSVidHandlerDispath dispatch[7] =
    {
        /* Read-support (also covers GetNext requests) */
        {MODE_GET, CmcCdtTransSVidTableGet},
        /* Write-support */
        {MODE_SET_RESERVE1, CmcCdtTransSVidTableSetReserve1},
        {MODE_SET_RESERVE2, CmcCdtTransSVidTableSetReserve2},
        {MODE_SET_FREE, CmcCdtTransSVidTableSetFree},
        {MODE_SET_ACTION, CmcCdtTransSVidTableSetAction},
        {MODE_SET_UNDO, CmcCdtTransSVidTableSetUndo},
        {MODE_SET_COMMIT, CmcCdtTransSVidTableSetCommit},
    };
    size_t i;
    for (i = 0; i < sizeof(dispatch) /sizeof(struct CmcCdtTransSVidHandlerDispath); ++i)
    {
        if (reqinfo->mode == dispatch[i].mode)
        {
            int ret;
            ret = (*dispatch[i].handler)(handler, reginfo, reqinfo, requests);
            if (ret != SNMP_ERR_NOERROR)
            {
                printf("CmcCdtTransSVidTableHandler> %d operation failed, ret = %d\n",
                       dispatch[i].mode, ret);
                return ret;
            }
            break;
        }
    }
    return SNMP_ERR_NOERROR;
}
