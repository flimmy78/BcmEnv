/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */
#include "SystemInclude.h"
#include "BcmController.h"

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "Debug.h"
#include "ChannelMgt.h"

#include "gsAnCmcSystem.h"
using namespace std;

/** Initializes the gsAnCmcSystem module */
void InitGsAnCmcSystem(void)
{
    const oid CmcChannelBindingOid[] = { 1,3,6,1,4,1,22764,1015,9026,2,2,1,1 };
    const oid CmcUpFrequencyStandardOid[] = { 1,3,6,1,4,1,22764,1015,9026,2,2,1,2 };
    const oid CmcDownFrequencyStandardOid[] = { 1,3,6,1,4,1,22764,1015,9026,2,2,1,3 };

  DEBUGMSGTL(("gsAnCmcSystem", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration(
                               "gsAnCmcChannelBinding", HandleCmcChannelBinding,
                               CmcChannelBindingOid, OID_LENGTH(CmcChannelBindingOid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration(
                               "gsAnCmcUpFrequencyStandard", HandleCmcUpFrequencyStandard,
                               CmcUpFrequencyStandardOid, OID_LENGTH(CmcUpFrequencyStandardOid),
                               HANDLER_CAN_RWRITE
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration(
                               "gsAnCmcDownFrequencyStandard", HandleCmcDownFrequencyStandard,
                               CmcDownFrequencyStandardOid, OID_LENGTH(CmcDownFrequencyStandardOid),
                               HANDLER_CAN_RWRITE
        ));
}

int
HandleCmcChannelBinding(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    U8 ChannelBinding = ChannelBindEnable;//Only snmp can configure cmc to Enable 

    switch(reqinfo->mode) 
    {
        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                    &ChannelBinding, sizeof(ChannelBinding));
            break;

        case MODE_SET_RESERVE1:

            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:
            if (0)
            {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:               
            break;

        case MODE_SET_ACTION:           
            
            if (1) 
            {
                netsnmp_set_request_error(reqinfo, requests,SNMP_ERR_BADVALUE);
            }
            break;

        case MODE_SET_COMMIT:            
            if (0) 
            {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:
            if (0) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:
            snmp_log(LOG_ERR, "unknown mode (%d) in HandleCmcChannelBinding\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
HandleCmcUpFrequencyStandard(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    dbgstrm << "Start." << endl;

    int ret;
    U8 UpFrequencyStandard = UsEuroStd; //Only snmp can configure cmc to UsEuroStd 
    
    switch(reqinfo->mode) 
    {
        case MODE_GET:
            
            ret = BASE_OK; 
            if ( ret != BASE_OK ) 
            {
                dbgstrm << "GET CmcUpFrequencyStandard error." << endl;
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_GENERR );
            }
            
            dbgstrm << "GET CmcUpFrequencyStandard ok." << endl;
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &UpFrequencyStandard, sizeof(U8));
            break;

        case MODE_SET_RESERVE1:

            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:

            if (0) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:
            break;

        case MODE_SET_ACTION:

            ret = BASE_ERROR; 
            if (ret != BASE_OK) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_BADVALUE);
            }
            break;

        case MODE_SET_COMMIT:

            if (0) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:

            if (0) {

                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:

            snmp_log(LOG_ERR, "unknown mode (%d) in HandleCmcUpFrequencyStandard\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
HandleCmcDownFrequencyStandard(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    U8 DownFrequencyStandard = DsEuroStd; //Only snmp can configure cmc to DsEuroStd 
    
    switch(reqinfo->mode) {

        case MODE_GET:
            ret = BASE_OK; 
            if ( ret != BASE_OK ) 
            {
                dbgstrm << "GET CmcDownFrequencyStandard error." << endl;
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_GENERR );
            }
            
            dbgstrm << "GET CmcDownFrequencyStandard ok." << endl;
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     &DownFrequencyStandard, sizeof(U8));
            break;

        case MODE_SET_RESERVE1:
            
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                netsnmp_set_request_error(reqinfo, requests, ret );
            }
            break;

        case MODE_SET_RESERVE2:

            if (0) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_RESOURCEUNAVAILABLE);
            }
            break;

        case MODE_SET_FREE:

            break;

        case MODE_SET_ACTION:

            ret = BASE_ERROR; 
            if (ret != BASE_OK) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_BADVALUE);
            }
            break;

        case MODE_SET_COMMIT:

            if (0) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_COMMITFAILED);
            }
            break;

        case MODE_SET_UNDO:

            if (0) {
                netsnmp_set_request_error(reqinfo, requests, SNMP_ERR_UNDOFAILED);
            }
            break;

        default:

            snmp_log(LOG_ERR, "unknown mode (%d) in HandleCmcDownFrequencyStandard\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}