/**
 * \ingroup liteqmi
 * \ingroup wda
 * \file wda.h
 */
#ifndef __LITEQMI_WDA_H__
#define __LITEQMI_WDA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

void helper_get_wda_resp_ctx(
        uint8_t *rsp,
        uint32_t len,
        unpack_qmi_t *pCtx
        );

/**
 * \ingroup wda
 * 
 *  Structure to set data format for RMNET QMAP
 *
 *  @param  pQos_format
 *		- Configured QOS data format.
 *			- 0 – QOS flow header is not present (default)
 *			- 1 – QOS flow header is present
 *  @param pQlink_prot 
 *          - 0x01 – 802.3 Ethernet mode (Not supported)
 *			- 0x02 – IP mode (Default)
 *  @param pUl_data_aggregation_protocol 
 *			- 0x00 – UL data aggregation is disabled (default)
 *			- 0x01 – UL TLP is enabled
 *			- 0x02 – UL QC_NCM is enabled
 *			- 0x03 – UL MBIM is enabled
 *			- 0x04 – UL RNDIS is enabled
 *			- 0x05 – UL QMAP is enabled
 *			- 0x06 – UL QMAP V2 is enabled
 *			- 0x07 – UL QMAP V3 is enabled
 *			- 0x08 – UL QMAP V4 is enabled
 *			- 0x09 – UL QMAP V5 is enabled			
 *  @param pDL_data_aggregation_protocol
 *          - 0x00 – DL data aggregation is disabled(Default)
 *			- 0x05 – DL QMAP is enabled
 *			- 0x00 – DL data aggregation is disabled (default)
 *			- 0x01 – DL TLP is enabled
 *			- 0x02 – DL QC_NCM is enabled
 *			- 0x03 – DL MBIM is enabled
 *			- 0x04 – DL RNDIS is enabled
 *			- 0x05 – DL QMAP is enabled
 *			- 0x06 – DL QMAP V2 is enabled
 *			- 0x07 – DL QMAP V3 is enabled
 *			- 0x08 – DL QMAP V4 is enabled
 *			- 0x09 – DL QMAP V5 is enabled
 *	@param pNdp_signature
 *			- Uses the default value based on the data aggregation protocol.
 *  @param pDl_data_aggregation_max_datagrams 
 *          - Maximum number of datagrams in a single aggregated packet on downlink.
 *			  The value applies to all downlink data aggregation protocols when downlink
 *			  data aggregation is enabled. Zero means no limit.
 *  @param pDl_data_aggregation_max_size 
 *          - Maximum size in bytes of a single aggregated packet allowed on downlink.
 *			  The value applies to all downlink data aggregation protocols when downlink
 *			  data aggregation is enabled.
 *  @param pEp_type
 *			- Peripheral endpoint type.
 * 				- 0x00 – Reserved
 * 				- 0x01 – High-speed inter-chip interface
 * 				- 0x02 – High-speed universal serial bus
 * 				- 0x03 – Peripheral component interconnect express
 * 				- 0x04 – Embedded
 * 				- 0x05 – BAM demux All other values are reserved and are ignored. 
 *  @param pIface_id 
 *			- Peripheral interface number (0x08 for Sierra modems)
 *  @param pQos_header_format 
 *          - QOS header format to use on the uplink, on all the protocols, if QOS is enabled.
 *				- 0x00 – Reserved
 *				- 0x01 – QOS 6 byte default header
 *				- 0x02 – QOS 8 byte header
 *	@param pDl_minimum_padding
 *			- Indicates the minimum padding bytes added in between aggregated downlink QMAP packets.
 *  @param Flow_Control 
 *          - Indicates whether flow control will be done by the TE.
 * 			– 0 - Flow control will not be done by the TE (Default)
 *			- 1 - Flow control will be done by the TE (Default)
 *  @param pUl_data_aggregation_max_size
 * 			- Maximum size in bytes of a single aggregated packet allowed on uplink. The value applies only
 * 			  to QMAP uplink data aggregation protocol when it is enabled.
 *	@param 	pTcp_coalescing
 *			- Specifies whether TCP coalescing is enabled or disabled on the modem.
 *				- FALSE – Disable TCP coalecsing (default).
 *				- TRUE – Enable TCP coalescing
 *	@param  pUdp_coalescing
 * 			- Specifies whether UDP coalescing is enabled or disabled on the modem.
 *				- FALSE – Disable UDP coalecsing (default).
 *				- TRUE – Enable UDP coalescing
 */
typedef struct{
    uint8_t*        pQos_format;							//TLV 0x10
	uint32_t*       pQlink_prot;							//TLV 0x11
	uint32_t*       pUl_data_aggregation_protocol;  		//TLV 0x12
	uint32_t*       pDl_data_aggregation_protocol;			//TLV 0x13
	uint32_t*		pNdp_signature;							//TLV 0x14
	uint32_t*       pDl_data_aggregation_max_datagrams; 	//TLV 0x15
	uint32_t*       pDl_data_aggregation_max_size;			//TLV 0x16
	uint32_t*       pEp_type;								//TLV 0x17 - 1
	uint32_t*       pIface_id;								//TLV 0x17 - 2
	uint32_t*       pQos_header_format;						//TLV 0x18
	uint32_t*       pDl_minimum_padding; 					//TLV 0x19
	uint8_t*        pFlow_control;							//TLV 0x1A
	uint32_t*       pUl_data_aggregation_max_datagrams;		//TLV 0x1B
	uint32_t*       pUl_data_aggregation_max_size;			//TLV 0x1C
	uint8_t*		pTcp_coalescing;						//TLV 0x1D - 1
	uint8_t*		pUdp_coalescing;						//TLV 0x1D - 2
}pack_wda_SetDataFormat_t;

/**
 * \ingroup wda
 * 
 *  Structure to unpack the set data format response from the modem
 *
 *  @param ParamPresenceMask
 *          - Bit mask that indicates presennce of optional parameters
 *  @param Tlvresult
 *          - Unpack result.
 *          - Bit to check in ParamPresenceMask - <B>2</B>  
 *  @param  pQos_format 
 *          - Configured QOS data format. 
 *				- 0 – QOS flow header is not present (default)
 *				- 1 – QOS flow header is present
 *          - Bit to check in ParamPresenceMask - <B>16</B>   
 *  @param pLink_prot 
 *			- Configured link layer protocol. 
 * 				- 0x01 – 802.3 Ethernet mode (default)
 * 				- 0x02 – IP mode
 *			- Bit to check in ParamPresenceMask - <B>17</B>   
 *  @param pUl_data_aggregation_protocol 
 *			- Configured uplink data aggregation protocol. 
 *				- 0x00 – UL data aggregation is disabled (default)
 *				- 0x01 – UL TLP is enabled
 *				- 0x02 – UL QC_NCM is enabled
 *				- 0x03 – UL MBIM is enabled
 *				- 0x04 – UL RNDIS is enabled
 *				- 0x05 – UL QMAP is enabled
 *				- 0x06 – UL QMAP V2 is enabled
 *				- 0x07 – UL QMAP V3 is enabled
 *				- 0x08 – UL QMAP V4 is enabled
 *				- 0x09 – UL QMAP V5 is enabled			
 *			- Bit to check in ParamPresenceMask - <B>18</B>   
 *  @param pDL_data_aggregation_protocol
 *			- Configured downlink data aggregation protocol. 
 *				- 0x00 – DL data aggregation is disabled (default)
 *				- 0x01 – DL TLP is enabled
 *				- 0x02 – DL QC_NCM is enabled
 *				- 0x03 – DL MBIM is enabled
 *				- 0x04 – DL RNDIS is enabled
 *				- 0x05 – DL QMAP is enabled
 *				- 0x06 – DL QMAP V2 is enabled
 *				- 0x07 – DL QMAP V3 is enabled
 *				- 0x08 – DL QMAP V4 is enabled
 *				- 0x09 – DL QMAP V5 is enabled
 *			- Bit to check in ParamPresenceMask - <B>19</B>
 *  @param pNdp_signature
 *			- Uses the default value based on the data aggregation protocol.
 *			- Bit to check in ParamPresenceMask - <B>20</B>   
 *  @param pDl_data_aggregation_max_datagrams 
 *			- Maximum number of datagrams in a single aggregated packet on downlink.
 *			  The value applies to all downlink data aggregation protocols when downlink
 *			  data aggregation is enabled. Zero means no limit.
 *			- Bit to check in ParamPresenceMask - <B>21</B>   
 *  @param pUl_data_aggregation_max_size 
 *			- Maximum size in bytes of a single aggregated packet allowed on downlink.
 *			  The value applies to all downlink data aggregation protocols when downlink
 *			  data aggregation is enabled.
 *			- Bit to check in ParamPresenceMask - <B>22</B>
 *  @param pUl_data_aggregation_max_datagrams 
 *			- Maximum number of datagrams supported in the modem in a single aggregated packet on 
 *			  uplink for the currently configured aggregation mode. Zero means there is no limit.
 *			- Bit to check in ParamPresenceMask - <B>23</B>   
 *  @param pUl_data_aggregation_max_size 
 *			- Maximum size in bytes of a single aggregated packet allowed on uplink.
 *			- Bit to check in ParamPresenceMask - <B>24</B> 
 *  @param pQos_header_format 
 *			- Configured QOS header format used on the uplink, on all the protocols, if QOS is enabled. 
 *				- 0x00 – Reserved
 *				- 0x01 – QOS 6 byte default header
 *				- 0x02 – QOS 8 byte header
 *			- Bit to check in ParamPresenceMask - <B>25</B> 
 *  @param pDl_minimum_padding
 *			- Indicates the minimum padding bytes added in between aggregated downlink QMAP packets.
 *			- Bit to check in ParamPresenceMask - <B>26</B>   
 *  @param pFlow_control 
 *			- Configured flow control.
 *				- 0 – Flow control will not be done by the TE (default)
 *				- 1 – Flow control will be done by the TE
 *			- Bit to check in ParamPresenceMask - <B>27</B>
 *	@param 	pTcp_coalescing
 *			- Specifies whether TCP coalescing is enabled or disabled on the modem.
 *				- FALSE – Disable TCP coalecsing (default).
 *				- TRUE – Enable TCP coalescing
 *	@param  pUdp_coalescing
 * 			- Specifies whether UDP coalescing is enabled or disabled on the modem.
 *				- FALSE – Disable UDP coalecsing (default).
 *				- TRUE – Enable UDP coalescing
 *    
 */
typedef struct{
	swi_uint256_t  ParamPresenceMask;
	uint16_t       Tlvresult;
    uint8_t*        pQos_format;							//TLV 0x10
	uint32_t*       pQlink_prot;							//TLV 0x11
	uint32_t*       pUl_data_aggregation_protocol;  		//TLV 0x12
	uint32_t*       pDl_data_aggregation_protocol;			//TLV 0x13
	uint32_t*		pNdp_signature;							//TLV 0x14
	uint32_t*       pDl_data_aggregation_max_datagrams; 	//TLV 0x15
	uint32_t*       pDl_data_aggregation_max_size;			//TLV 0x16
	uint32_t*       pUl_data_aggregation_max_datagrams;		//TLV 0x17
	uint32_t*       pUl_data_aggregation_max_size;			//TLV 0x18		
	uint32_t*		pQos_header_format;						//TLV 0x19
	uint32_t*       pDl_minimum_padding; 					//TLV 0x1A
	uint8_t*        pFlow_control;							//TLV 0x1B
	uint8_t*		pTcp_coalescing;						//TLV 0x1C - 1
	uint8_t*		pUdp_coalescing;						//TLV 0x1C - 2
}unpack_wda_SetDataFormat_t;

/**
 * \ingroup wda
 * 
 * Set data format pack
 *  Configure data format to use with QMAP
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wda_SetDataFormat(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_wda_SetDataFormat_t *reqArg
);

/**
 * \ingroup wda
 * 
 * Set data format unpack
 *  Configure data format to use with QMAP
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wda_SetDataFormat(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_wda_SetDataFormat_t *pOutput
);

/**
 * \ingroup wda
 * 
 *  Structure to get configured data format
 *
 *  @param  ep_type
 *         	- Peripheral endpoint type.
 * 			  - Values:
 *				- DATA_EP_TYPE_RESERVED (0x00) – Reserved
 *				- DATA_EP_TYPE_HSIC (0x01) – High-speed inter-chip interface
 *				- DATA_EP_TYPE_HSUSB (0x02) – High-speed universal serial bus
 *				- DATA_EP_TYPE_PCIE (0x03) – Peripheral component interconnect express
 *				- DATA_EP_TYPE_EMBEDDED (0x04) – Embedded
 *				- DATA_EP_TYPE_BAM_DMUX (0x05) – BAM demux
 *				- All other values are reserved and are ignored.
 *  @param  iface_id
 * 			- Peripheral interface number.
 */
typedef struct{
	uint32_t ep_type;
	uint32_t iface_id;	
}pack_wda_GetDataFormat_t;

/**
 * \ingroup wda
 * 
 *  Structure to unpack get data format response
 *
 *  @param ParamPresenceMask
 *          - Bit mask that indicates presennce of optional parameters
 *  @param Tlvresult
 *          - Unpack result.
 *          - Bit to check in ParamPresenceMask - <B>2</B>  
 *  @param  QoSDataFormat header presence
 *          - Inidcates if QoS header is used or not 
 * 			- 0 - Not Used (Default)
 * 			- 1 - Used (Not supported)
 *          - Bit to check in ParamPresenceMask - <B>16</B>   
 *  @param Link_Protocol 
 *          - 0x01 – 802.3 Ethernet mode (Not supported)
 *			- 0x02 – IP mode (Default)
 *          - Bit to check in ParamPresenceMask - <B>17</B>   
 *  @param UL_Data_Aggregation_Protocol 
 *          - 0x00 – UL data aggregation is disabled(Default)
 *			- 0x05 – UL QMAP is enabled
 *          - Bit to check in ParamPresenceMask - <B>18</B>   
 *  @param DL_Data_Aggregation_Protocol 
 *          - 0x00 – DL data aggregation is disabled(Default)
 *			- 0x05 – DL QMAP is enabled
 *          - Bit to check in ParamPresenceMask - <B>19</B>   
 *  @param DL_Data_Aggregation_Max_Datagrams 
 *          - Number of aggregated QMAP datagrams in a single DL packet
 *          - Bit to check in ParamPresenceMask - <B>21</B>   
 *  @param DL_Data_Aggregation_Max_Size 
 *          - Maximum size in bytes of a single aggregated packet allowed on downlink.
 *          - Bit to check in ParamPresenceMask - <B>22</B>
 *  @param UL_Data_Aggregation_Max_Datagrams 
 *          - Number of aggregated QMAP datagrams in a single UL packet
 *          - Bit to check in ParamPresenceMask - <B>23</B>   
 *  @param UL_Data_Aggregation_Max_Size 
 *          - Maximum size in bytes of a single aggregated packet allowed on uplink.
 *          - Bit to check in ParamPresenceMask - <B>24</B> 
 *  @param DL_Padding 
 *			- Specifies the minimum padding bytes to be added in between aggregated downlink QMAP packets. 
 *			- Default: 0
 *          - Bit to check in ParamPresenceMask - <B>26</B>   
 *  @param Flow_Control 
 *          - Indicates whether flow control will be done by the TE.
 * 			– 0 - Flow control will not be done by the TE (Default)
 *			- 1 - Flow control will be done by the TE (Default)
 *          - Bit to check in ParamPresenceMask - <B>27</B>   
 *  @param 	pTcp_coalescing
 *			- Specifies whether TCP coalescing is enabled or disabled on the modem.
 *			- FALSE – Disable TCP coalecsing (default).
 *			- TRUE – Enable TCP coalescing
 *          - Bit to check in ParamPresenceMask - <B>28</B>   
 *	@param  pUdp_coalescing
 * 			- Specifies whether UDP coalescing is enabled or disabled on the modem.
 *			- FALSE – Disable UDP coalecsing (default).
 *			- TRUE – Enable UDP coalescing
 *          - Bit to check in ParamPresenceMask - <B>28</B>   
 */
typedef struct{
	swi_uint256_t  ParamPresenceMask;
	uint16_t       Tlvresult;
    uint8_t        Qos_format;
	uint32_t       Qlink_prot;
	uint32_t       Ul_data_aggregation_protocol;
	uint32_t       Dl_data_aggregation_protocol;
	uint32_t	   Ndp_signature;			
	uint32_t       Dl_data_aggregation_max_datagrams;
	uint32_t       Dl_data_aggregation_max_size;
	uint32_t       Ul_data_aggregation_max_datagrams;
	uint32_t       Ul_data_aggregation_max_size;		
	uint32_t	   Qos_header_format;			
	uint32_t       Dl_minimum_padding;				
	uint8_t        Flow_control;		
	uint8_t		   Tcp_coalescing;			
	uint8_t		   Udp_coalescing;
}unpack_wda_GetDataFormat_t;


/**
 * \ingroup wda
 * 
 * Get data format pack
 *  Read data format settings for use with QMAP
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wda_GetDataFormat(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_wda_GetDataFormat_t *reqArg			
);


/**
 * \ingroup wda
 * 
 * Get data format unpack
 *  Read configured data format to use with QMAP
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wda_GetDataFormat(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_wda_GetDataFormat_t *pOutput
);

/**
 * \ingroup wda
 * 
 *  Structure to set WDA Set QMAP Settings
 *
 *	@param pEp_type
 *			- Peripheral endpoint type. 
 * 			  - Values:
 * 				- DATA_EP_TYPE_RESERVED (0x00) – Reserved
 * 				- DATA_EP_TYPE_HSIC (0x01) – High-speed inter-chip interface
 * 				- DATA_EP_TYPE_HSUSB (0x02) – High-speed universal serial bus
 * 				- DATA_EP_TYPE_PCIE (0x03) – Peripheral component interconnect express
 * 				- DATA_EP_TYPE_EMBEDDED (0x04) – Embedded
 * 				- DATA_EP_TYPE_BAM_DMUX (0x05) – BAM demux All other values are reserved and are ignored.
 *	@param pIface_id
 *			- Peripheral interface number. 
 *	@param pQmap_dfc
 *			- Configures the data flow control via QMAP. 
 *			  - Values:
 *				- 0 – Disables QMAP Data flow control
 *				- 1 – Enables QMAP Data flow control
 */
typedef struct{
    uint32_t*       pEp_type;
	uint32_t*       pIface_id;
	uint8_t*        pQmap_dfc;
}pack_wda_SetQmapSettings_t;

/**
 * \ingroup wda
 * 
 *  Structure to unpack the set qmap settings response from the modem
 *
 *  @param ParamPresenceMask
 *          - Bit mask that indicates presennce of optional parameters
 *  @param Tlvresult
 *          - Unpack result.
 *          - Bit to check in ParamPresenceMask - <B>3</B>  
 *  @param qmap_dfc
 *			- Indicates whether the data flow control via QMAP is enabled/disabled.
 *			  Values:
 *				0 – Disabled
 *				1 – Enabled   
 */
typedef struct{
	swi_uint256_t  ParamPresenceMask;
	uint16_t       Tlvresult;
    uint8_t*       pQmap_dfc;
}unpack_wda_SetQmapSettings_t;

/**
 * \ingroup wda
 * 
 * Set qmap settings pack
 *  Configure qmap settings to use with QMAP
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wda_SetQmapSettings(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_wda_SetQmapSettings_t *reqArg
);

/**
 * \ingroup wda
 * 
 * Set qmap settings unpack
 *  Configure qmap settings to use with QMAP
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wda_SetQmapSettings(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_wda_SetQmapSettings_t *pOutput
);

/**
 * \ingroup wda
 * 
 *  Structure to get qmap settings format
 *
 *  @param  pEp_type
 *         	- Peripheral endpoint type.
 * 			  - Values:
 *				- DATA_EP_TYPE_RESERVED (0x00) – Reserved
 *				- DATA_EP_TYPE_HSIC (0x01) – High-speed inter-chip interface
 *				- DATA_EP_TYPE_HSUSB (0x02) – High-speed universal serial bus
 *				- DATA_EP_TYPE_PCIE (0x03) – Peripheral component interconnect express
 *				- DATA_EP_TYPE_EMBEDDED (0x04) – Embedded
 *				- DATA_EP_TYPE_BAM_DMUX (0x05) – BAM demux
 *				- All other values are reserved and are ignored.
 *  @param  pIface_id
 * 			- Peripheral interface number.
 */
typedef struct{
	uint32_t* pEp_type;
	uint32_t* pIface_id;	
}pack_wda_GetQmapSettings_t;

/**
 * \ingroup wda
 * 
 *  Structure to unpack get qmap settings response
 *
 *  @param ParamPresenceMask
 *          - Bit mask that indicates presennce of optional parameters
 *  @param Tlvresult
 *          - Unpack result.
 *          - Bit to check in ParamPresenceMask - <B>2</B>  
 *  @param qmap_dfc
 *			- Indicates whether the data flow control via QMAP is enabled/disabled.
 *			  -Values:
 *				-0 – Disabled
 *				-1 – Enabled
 */
typedef struct{
	swi_uint256_t  ParamPresenceMask;
	uint16_t       Tlvresult;
    uint8_t*       pQmap_dfc;
}unpack_wda_GetQmapSettings_t;

/**
 * \ingroup wda
 * 
 * Get qmap settings pack
 *  Read qmap settings for use with QMAP
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_wda_GetQmapSettings(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_wda_GetQmapSettings_t *reqArg
);

/**
 * \ingroup wda
 * 
 * Get qmap settings unpack
 *  Read configured qmap settings to use with QMAP
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_wda_GetQmapSettings(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_wda_GetQmapSettings_t *pOutput
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif//#ifndef  __LITEQMI_WDA_H__

