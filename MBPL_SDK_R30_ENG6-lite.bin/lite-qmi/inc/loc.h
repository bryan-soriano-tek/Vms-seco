/**
 * \ingroup liteqmi
 * \ingroup loc
 * \file loc.h
 */

#ifndef __LITEQMI_LOC_H__
#define __LITEQMI_LOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdint.h>

/*! maximum string size*/
#define LOC_UINT8_MAX_STRING_SZ 255
/*! maximum number of GNSS station ID buffer*/
#define LOC_MAX_DGNSS_STATIONID 32
/*! maximum number of GNSS used signal type buffer*/
#define LOC_MAX_GNSS_USEDSIGNALTYPE 32
/*! maximum number of jammer indicator buffer*/
#define LOC_MAX_JAMMERINDICATOR 20
/*!
 * \def LOCEVENTMASKPOSITIONREPORT
 * The control point must enable this mask to receive 
 * position report event indications.
 */
#define LOCEVENTMASKPOSITIONREPORT            0x00000001
/*!
 * \def LOCEVENTMASKGNSSSVINFO
 * The control point must enable this mask to receive 
 * satellite report event indications. These reports 
 * are sent at a 1 Hz rate.
 */
#define LOCEVENTMASKGNSSSVINFO                0x00000002
/*!
 * \def LOCEVENTMASKNMEA
 * The control point must enable this mask to receive 
 * NMEA reports for position and satellites in view. 
 * The report is at a 1 Hz rate.
 */
#define LOCEVENTMASKNMEA                      0x00000004
/*!
 * \def LOCEVENTMASKNINOTIFYVERIFYREQ
 * The control point must enable this mask to receive 
 * NI Notify/Verify request event indications.
 */
#define LOCEVENTMASKNINOTIFYVERIFYREQ         0x00000008
/*!
 * \def LOCEVENTMASKINJECTTIMEREQ
 * The control point must enable this mask to receive 
 * time injection request event indications.
 */
#define LOCEVENTMASKINJECTTIMEREQ             0x00000010
/*!
 * \def LOCEVENTMASKINJECTPREDICTEDORBITSREQ
 * The control point must enable this mask to receive 
 * predicted orbits request event indications.
 */
#define LOCEVENTMASKINJECTPREDICTEDORBITSREQ  0x00000020
/*!
 * \def LOCEVENTMASKINJECTPOSITIONREQ
 * The control point must enable this mask to receive 
 * position injection request event indications.
 */
#define LOCEVENTMASKINJECTPOSITIONREQ         0x00000040
/*!
 * \def LOCEVENTMASKENGINESTATE
 * The control point must enable this mask to receive 
 * engine state report event indications.
 */
#define LOCEVENTMASKENGINESTATE               0x00000080
/*!
 * \def LOCEVENTMASKFIXSESSIONSTATE
 * The control point must enable this mask to receive 
 * fix session status report event indications.
 */
#define LOCEVENTMASKFIXSESSIONSTATE           0x00000100
/*! 
 * \def LOCEVENTMASKWIFIREQ
 * The control point must enable this mask to receive 
 * Wi-Fi position request event indications.
 */
#define LOCEVENTMASKWIFIREQ                   0x00000200
/*!
 \def LOCEVENTMASKSENSORSTREAMINGREADYSTATUS
 * The control point must enable this mask to receive 
 * notifications from the location engine indicating 
 * its readiness to accept data from the 
 * sensors (accelerometer, gyroscope, etc.).
 */
#define LOCEVENTMASKSENSORSTREAMINGREADYSTATUS  0x00000400
/*!
 * \def LOCEVENTMASKTIMESYNCREQ
 * The control point must enable this mask to receive 
 * time sync requests from the GPS engine. 
 * Time sync enables the GPS engine to synchronize 
 * its clock with the sensor processor's clock.
 */
#define LOCEVENTMASKTIMESYNCREQ               0x00000800
/*!
 * \def LOCEVENTMASKSETSPISTREAMINGREPORT
 * The control point must enable this mask to receive 
 * Stationary Position Indicator (SPI) 
 * streaming report indications.
 */
#define LOCEVENTMASKSETSPISTREAMINGREPORT     0x00001000
/*!
 * \def LOCEVENTMASKLOCATIONSERVERCONNECTIONREQ
 * The control point must enable this mask
 * to receive location server requests. These
 * requests are generated when the service
 * wishes to establish a connection with a
 * location server.
 */
#define LOCEVENTMASKLOCATIONSERVERCONNECTIONREQ  0x00002000
/*!
 * \def LOCEVENTMASKNIGEOFENCENOTIFICATION
 * The control point must
 * enable this mask to receive notifications
 * related to network-initiated Geofences.
 * These events notify the client when a
 * network-initiated Geofence is added,
 * deleted, or edited.
 */
#define LOCEVENTMASKNIGEOFENCENOTIFICATION    0x00004000
/*!
 * \def LOCEVENTMASKGEOFENCEGENALERT
 * The control point must
 * enable this mask to receive Geofence
 * alerts. These alerts are generated to
 * inform the client of the changes that may
 * affect a Geofence, for example, if GPS is
 * turned off or if the network is
 * unavailable.
 */
#define LOCEVENTMASKGEOFENCEGENALERT          0x00008000
/*!
 * \def LOCEVENTMASKGEOFENCEBREACHNOTIFICATION
 * The control point must enable this mask to
 * receive notifications when a Geofence is
 * breached. These events are generated
 * when a UE enters or leaves the perimeter
 * of a Geofence. This breach report is for a
 * single Geofence.
 */
#define LOCEVENTMASKGEOFENCEBREACHNOTIFICATION  0x00010000
/*!
 * \def LOCEVENTMASKPEDOMETERCONTROL
 * The control point must
 * enable this mask to register for
 * pedometer control requests from the
 * location engine. The location engine
 * sends this event to control the injection
 * of pedometer reports.
 */
#define LOCEVENTMASKPEDOMETERCONTROL          0x00020000
/*!
 * \def LOCEVENTMASKMOTIONDATACONTROL
 * The control point must
 * enable this mask to register for motion
 * data control requests from the location
 * engine. The location engine sends this
 * event to control the injection of motion
 * data.
 */
#define LOCEVENTMASKMOTIONDATACONTROL         0x00040000
/*!
 * \def LOCEVENTMASKBATCHFULLNOTIFICATION
 * The control point must enable this
 * mask to receive notification when a
 * batch is full. The location engine sends
 * this event to notify of Batch Full for
 * ongoing batching session.
 */
#define LOCEVENTMASKBATCHFULLNOTIFICATION     0x00080000
/*!
 * \def LOCEVENTMASKLIVEBATCHEDPOSITIONREPORT
 * The control point must
 * enable this mask to receive position
 * report indications along with an ongoing
 * batching session. The location engine
 * sends this event to notify the batched
 * position report while a batching session
 * is ongoing.
 */
#define LOCEVENTMASKLIVEBATCHEDPOSITIONREPORT 0x00100000
/*!
 * \def LOCEVENTMASKINJECTWIFIAPDATAREQ
 * The control point must enable this mask
 * to receive Wi-Fi Access Point (AP) data
 * inject request event indications.
 */
#define LOCEVENTMASKINJECTWIFIAPDATAREQ       0x00200000
/*!
 * \def LOCEVENTMASKGEOFENCEBATCHBREACHNOTIFICATION
 * The control point must enable this mask to
 * receive notifications when a Geofence is
 * breached. These events are generated
 * when a UE enters or leaves the perimeter
 * of a Geofence. This breach notification
 * is for multiple Geofences. Breaches
 * from multiple Geofences are all batched
 * and sent in the same notification.
 */
#define LOCEVENTMASKGEOFENCEBATCHBREACHNOTIFICATION 0x00400000
/*!
 * \def LOCEVENTMASKVEHICLEDATAREADYSTATUS
 * The control point must
 * enable this mask to receive notifications
 * from the location engine indicating its
 * readiness to accept vehicle data (vehicle
 * accelerometer, vehicle angular rate,
 * vehicle odometry, etc.).
 */
#define LOCEVENTMASKVEHICLEDATAREADYSTATUS    0x00800000
/*! 
 \def LOCEVENTMASKGNSSMEASUREMENTREPORT
 * The control point must
 * enable this mask to receive system clock
 * and satellite measurement report events
 * (system clock, SV time, Doppler, etc.).
 * Reports are generated only for the GNSS
 * satellite constellations that are enabled
 * using QMI_LOC_SET_GNSS_
 * CONSTELL_REPORT_CONFIG(Not yet supported).
 */
#define LOCEVENTMASKGNSSMEASUREMENTREPORT     0x01000000
/*!
 * \def LOCEVENTMASKINVALIDVALUE
 * Invalid Event Mask
 */
#define LOCEVENTMASKINVALIDVALUE              0xFFFFFFFF

/*!Maximum number of sensor data*/
#define  MAX_SENSOR_DATA_LEN       64
/*!Maximum number sample time offset*/
#define  MAX_TEMP_DATA_LEN         64
/*!Size of NMEA setence buffer*/
#define  MAX_LOC_NMEA_STR_LEN      201

/*!Maximum size of expanded GNSS SV Used list*/
#define MAX_Expanded_SVS           16
/*!Maximum size of satellies signal types list*/
#define MAX_SATELLITES_SIGNAL_TYPES 20

/*!Maximum size of URL string including terminating NULL.*/
#define MAX_URL_ADDR_STR_LEN 256
#define MAX_GNSS_SINGNAL_TYPES 255

/**
 * \ingroup loc
 *
 * LOC session status operation result.
 */
enum {
    eQMI_LOC_SESS_STATUS_SUCCESS=0,
    eQMI_LOC_SESS_STATUS_IN_PROGRESS=1,
    eQMI_LOC_SESS_STATUS_FAILURE=2,
    eQMI_LOC_SESS_STATUS_TIMEOUT=3,
};

/**
 * \ingroup loc
 * 
 * This structure contains the Application Information
 *
 * @param applicationProvider_len
 *        - Length of the Application Provider
 *
 * @param pAplicationProvider
 *        - Application Provider
 *        - Depends upon the Length of application Provider
 *
 * @param applicationName_len
 *        - Length of Application Name
 *
 * @param pAppName
 *        - Application Name
 *        - Depends upon the Length of application Name
 *
 * @param applicationVersion_valid
 *        - Specifies whether the application version string contains a
 *          valid value
 *        - 0x00 (FALSE) Application version string is invalid
 *        - 0x01 (TRUE) Application version string is valid
 *
 * @param applicationVersion_len
 *        - Length of Application Version
 *
 * @param pApplicationVersion
 *        - Application Version
 *        - Depends upon the Length of application Version
 *
 */
typedef struct 
{
    uint8_t applicationProvider_len;
    uint8_t *pAplicationProvider;
    uint8_t applicationName_len;
    uint8_t *pAppName;
    uint8_t applicationVersion_valid;
    uint8_t applicationVersion_len;
    uint8_t *pApplicationVersion;
}loc_LocApplicationInfo;

/**
 * \ingroup loc
 *
 * This structure contains the GNSS power mode option
 *
 * @param powerMode
 *			- GNSS power mode option to let the client choose the power-accuracy trade-off.
 *			 - Values:
 *				- eQMI_LOC_POWER_MODE_IMPROVED_ ACCURACY (1) - The GNSS receiver operates in full power mode (non-DPO).
 *				- eQMI_LOC_POWER_MODE_NORMAL (2) - The GNSS receiver operates with GNSS receiver autonomously duty cycling while meeting position criteria.
 *				- eQMI_LOC_POWER_MODE_BACKGROUND_DEFINED_POWER (3) - The GNSS receiver duty cycles at a variable rate to meet the target power budget.
 *				- The power budget is defined as 1/N of the GNSS full power during 1 Hz navigation. N = timeBetweenMeasurement/1000.
 *				- eQMI_LOC_POWER_MODE_BACKGROUND_ DEFINED_TIME (4) - The GNSS receiver duty cycles at a fixed time interval.
 *				- eQMI_LOC_POWER_MODE_BACKGROUND_KEEP_WARM (5) - The GNSS receiver operates in very-low power (less than 1mA) duty cycling  mode, to keep GNSS receiver warm for faster signal acquisition & tracking.
 *
 *	@param timeBetweenMeasurement
 *				- Maximum time interval between measurements, applies to the BACKGROUND_DEFINED_POWER and BACKGROUND_DEFINED_TIME power modes. For BACKGROUND_DEFINED_POWER,
 *				- set timeBetweenMeasurement to 1000 * N; timeBetweenMeasurement is ignored for the other power modes.
 *				- Units: Milliseconds
*/
typedef struct
{
	uint32_t powerMode;
	uint32_t timeBetweenMeasurement;
}loc_LocGNSSPowerMode;


/**
 * \ingroup loc
 * 
 * This structure contains the Delete LOC SV Info
 *
 * @param id
 *        - LOC SV ID of the satellite whose data is to be
 *          deleted
 *        - Range:
 *           - For GPS: 1 to 32
 *           - For SBAS: 33 to 64
 *           - For GLONASS: 65 to 96
 *
 * \param system
 *        - Indicates to which constellation this loc_SV belongs
 *        - Valid values:
 *           - eQMI_LOC_SV_SYSTEM_GPS (1) - GPS satellite
 *           - eQMI_LOC_SV_SYSTEM_GALILEO (2) - GALILEO satellite
 *           - eQMI_LOC_SV_SYSTEM_SBAS (3) - SBAS satellite
 *           - eQMI_LOC_SV_SYSTEM_COMPASS (4) - COMPASS satellite
 *           - eQMI_LOC_SV_SYSTEM_GLONASS (5) - GLONASS satellite
 *           - eQMI_LOC_SV_SYSTEM_BDS (6) - BDS satellite
 *           - eQMI_LOC_SV_SYSTEM_QZSS (7) - QZSS satellite
 *           - eQMI_LOC_SV_SYSTEM_NAVIC (8) - NavIC satellite
 *
 * \param mask
 *        - Indicates whether to delete the ephemeris or almanac for a satellite.
 *         - Valid values:
 *           - QMI_LOC_MASK_DELETE_EPHEMERIS (0x01) - Delete ephemeris for the satellite
 *           - QMI_LOC_MASK_DELETE_ALMANAC (0x02) - Delete almanac for the satellite
 */
typedef struct
{
    uint16_t    id;
    uint32_t   system;
    uint8_t    mask;
}loc_SV;

/**
 * \ingroup loc
 * 
 * This structure contains the elements of Delete LOC SV Info
 *
 * \param len
 *        - Number of sets of the following elements in struct loc_SV:
 *           - gnssSvId
 *           - system
 *           - deleteSvInfoMask
 *
 * \param pSV
 *        - Pointer to struct loc_SV. See \ref loc_SV for more information
 *
 */

typedef struct
{
    uint8_t    len;
    loc_SV      *pSV;
}loc_SVInfo;

/**
 * \ingroup loc
 * 
 * This structure contains the GNSS data
 *
 * \param mask
 *        - Mask for the GNSS data that is to be deleted
 *        - Valid values:
 *           - QMI_LOC_MASK_DELETE_GPS_SVDIR (0x00000001) - Mask to
 *             delete GPS SVDIR
 *           - QMI_LOC_MASK_DELETE_GPS_SVSTEER (0x00000002) - Mask to
 *             delete GPS SVSTEER 
 *           - QMI_LOC_MASK_DELETE_GPS_TIME (0x00000004) - Mask to
 *             delete GPS time
 *           - QMI_LOC_MASK_DELETE_GPS_ALM_CORR (0x00000008) - Mask to
 *             delete almanac correlation
 *           - QMI_LOC_MASK_DELETE_GLO_SVDIR (0x00000010) - Mask to
 *             delete GLONASS SVDIR
 *           - QMI_LOC_MASK_DELETE_GLO_SVSTEER (0x00000020) - Mask to
 *             delete GLONASS SVSTEER
 *           - QMI_LOC_MASK_DELETE_GLO_TIME (0x00000040) - Mask to
 *             delete GLONASS time
 *           - QMI_LOC_MASK_DELETE_GLO_ALM_CORR (0x00000080) - Mask to
 *             delete GLONASS almanac correlation
 *           - QMI_LOC_MASK_DELETE_SBAS_SVDIR (0x00000100) - Mask to
 *             delete SBAS SVDIR
 *           - QMI_LOC_MASK_DELETE_SBAS_SVSTEER (0x00000200) - Mask to
 *             delete SBAS SVSTEER
 *           - QMI_LOC_MASK_DELETE_POSITION (0x00000400) - Mask to
 *             delete position estimate
 *           - QMI_LOC_MASK_DELETE_TIME (0x00000800) - Mask to
 *             delete time estimate
 *           - QMI_LOC_MASK_DELETE_IONO (0x00001000) - Mask to
 *             delete IONO
 *           - QMI_LOC_MASK_DELETE_UTC (0x00002000) - Mask to
 *             delete UTC estimate
 *           - QMI_LOC_MASK_DELETE_HEALTH (0x00004000) - Mask to
 *             delete SV health record
 *           - QMI_LOC_MASK_DELETE_SADATA (0x00008000) - Mask to
 *             delete SADATA
 *           - QMI_LOC_MASK_DELETE_RTI (0x00010000) - Mask to
 *             delete RTI
 *           - QMI_LOC_MASK_DELETE_SV_NO_EXIST (0x00020000) - Mask to
 *             delete SV_NO_EXIST
 *           - QMI_LOC_MASK_DELETE_FREQ_BIAS_EST (0x00040000) - Mask to
 *             delete frequency bias estimate
 *           - QMI_LOC_MASK_DELETE_BDS_SVDIR (0x00080000) - Mask to
 *             delete BDS SVDIR
 *           - QMI_LOC_MASK_DELETE_BDS_SVSTEER (0x00100000) - Mask to
 *             delete BDS SVSTEER
 *           - QMI_LOC_MASK_DELETE_BDS_TIME (0x00200000) - Mask to
 *             delete BDS time
 *           - QMI_LOC_MASK_DELETE_BDS_ALM_CORR (0x00400000) - Mask to
 *             delete BDS almanac correlation
 *           - QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_GPS (0x00800000) -
 *             Mask to delete GNSS SV blacklist GPS
 *           - QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_GLO (0x01000000) -
 *             Mask to delete GNSS SV blacklist GLO
 *           - QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_BDS (0x02000000) -
 *             Mask to delete GNSS SV blacklist BDS
 *           - QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_GAL (0x04000000) - 
 *              Mask to delete GNSS SV blacklist Galileo
 *           - QMI_LOC_MASK_DELETE_GAL_SVDIR (0x08000000) - 
 *              Mask to delete Galileo SVDIR
 *           - QMI_LOC_MASK_DELETE_GAL_SVSTEER (0x10000000) - 
 *              Mask to delete Galileo SVSTEER
 *           - QMI_LOC_MASK_DELETE_GAL_TIME (0x20000000) - 
 *              Mask to delete Galileo time
 *           - QMI_LOC_MASK_DELETE_GAL_ALM_CORR (0x40000000) - 
 *              Mask to delete Galileo almanac correlation
 */    
typedef struct
{
    uint64_t   mask;
}loc_GnssData;

/**
 * \ingroup loc
 * 
 * This structure contains the cell database
 *
 * \param mask
 *        - Mask for the cell database assistance data that is to be deleted
 *        - Valid values:
 *           - 0x00000001 - DELETE_CELLDB_POS
 *           - 0x00000002 - DELETE_CELLDB_LATEST_GPS_POS
 *           - 0x00000004 - DELETE_CELLDB_OTA_POS
 *           - 0x00000008 - DELETE_CELLDB_EXT_REF_POS
 *           - 0x00000010 - DELETE_CELLDB_TIMETAG
 *           - 0x00000020 - DELETE_CELLDB_CELLID
 *           - 0x00000040 - DELETE_CELLDB_CACHED_CELLID
 *           - 0x00000080 - DELETE_CELLDB_LAST_SRV_CELL
 *           - 0x00000100 - DELETE_CELLDB_CUR_SRV_CELL
 *           - 0x00000200 - DELETE_CELLDB_NEIGHBOR_INFO
 *
 */

typedef struct
{
    uint32_t   mask;
}loc_CellDb;

/**
 * \ingroup loc
 * 
 * This structure contains the clock Info
 *
 * \param mask
 *        - Mask for the clock information assistance data that is to be deleted
 *        - Valid bitmasks:
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_TIME_EST (0x00000001) - Mask to
 *             delete time estimate from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_FREQ_EST (0x00000002) - Mask to
 *             delete frequency estimate from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_WEEK_NUMBER (0x00000004) - Mask to
 *             delete week number from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_RTC_TIME (0x00000008) - Mask to
 *             delete RTC time from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_TIME_TRANSFER (0x00000010) - Mask to
 *             delete time transfer from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GPSTIME_EST (0x00000020) - Mask to
 *             delete GPS time estimate from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLOTIME_EST (0x00000040) - Mask to
 *             delete GLONASS time estimate from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLODAY_NUMBER (0x00000080) - Mask to
 *             delete GLONASS day number from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLO4YEAR_NUMBER (0x00000100) - Mask to
 *             delete GLONASS four year number from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLO_RF_GRP_DELAY (0x00000200) - Mask to
 *             delete GLONASS RF GRP delay from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_DISABLE_TT (0x00000400) - Mask to
 *             delete disable TT from clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GG_LEAPSEC (0x00000800) - Mask to
 *             delete a BDS time estimate from the clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GG_GGTB (0x00001000) - Mask to
 *             delete a BDS time estimate from the clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_BDSTIME_EST (0x00002000) - Mask to
 *             delete a BDS time estimate from the clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GB_GBTB (0x00004000) - Mask to delete
 *             Glonass-to-BDS time bias-related information from the clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_BG_BGTB (0x00008000) - Mask to delete
 *             BDS-to-GLONASS time bias-related information from the clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_BDSWEEK_NUMBER (0x00010000) - Mask to
 *             delete the BDS week number from the clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_BDS_RF_GRP_DELAY (0x00020000) - Mask to
 *             delete the BDS RF GRP delay from the clock information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GALTIME_EST (0x00040000) -
 *              Delete a Galileo time estimate
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GALTOGPS_TB (0x00080000) -
 *              Delete Galileo-to-GPS time bias-related information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GALTOGLO_TB (0x00100000) -
 *              Delete Galileo-to-GLO time bias-related information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GALTOBDS_TB (0x00200000) -
 *              Delete Galileo-to-BDS time bias-related information
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GALWEEK_NUMBER (0x00800000) -
 *              Delete the Galileo week number
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_GAL_RF_GRP_DELAY (0x01000000) -
 *              Delete the Galileo RF GRP delay
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_NAVIC_TIME_EST (0x02000000) -
 *              Delete a NavIC time estimate
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_NAVIC_WEEK_NUMBER (0x04000000) -
 *              Delete the NavIC week number
 *           - QMI_LOC_MASK_DELETE_CLOCK_INFO_NAVIC_RF_GRP_DELAY (0x08000000) -
 *              Delete the NavIC RF GRP delay
 */

typedef struct
{
    uint32_t   mask;
}loc_ClkInfo;

/**
 * \ingroup loc
 * 
 * This structure contains the BDS SV Info
 *
 * \param id
 *        - SV ID of the satellite whose data is to be deleted.
 *           - Range for BDS: 201 to 237
 *
 * \param mask
 *        - Indicates if the ephemeris or almanac for a satellite is to be deleted
 *        - Valid values:
 *           - QMI_LOC_MASK_DELETE_EPHEMERIS (0x01) - Delete ephemeris for the satellite
 *           - QMI_LOC_MASK_DELETE_ALMANAC (0x02) - Delete almanac for the satellite
 *
*/

typedef struct
{
    uint16_t    id;
    uint8_t    mask;
}loc_BdsSV;

/**
 * \ingroup loc
 * 
 * This structure contains the number of sets of the BDS SVN Info
 *
 * \param len
 *        - Number of sets of the following elements:
 *           - gnssSvId
 *           - deleteSvInfoMask
 *
 * \param pSV
 *        - Pointer to struct loc_BdsSV. See \ref loc_BdsSV for more information
 *
*/

typedef struct
{
    uint8_t    len;
    loc_BdsSV   *pSV;
}loc_BdsSVInfo;

/**
 * \ingroup loc
 * 
 * This structure contains the GAL SV Info
 *
 * \param gnssSvId
 *        - SV ID of the satellite whose data is to be deleted.
 *          - Range for GAL: 301 to 336
 * 
 * \param deleteSvInfoMask
 *        - Indicates whether to delete the ephemeris or almanac for a satellite.
 *          - Valid values:
 *            - QMI_LOC_MASK_DELETE_EPHEMERIS (0x01) - Delete ephemeris for the satellite
 *            - QMI_LOC_MASK_DELETE_ALMANAC (0x02) - Delete almanac for the satellite
 *
*/
typedef struct
{
    uint16_t   gnssSvId;
    uint8_t    deleteSvInfoMask;
}loc_GalSV;

/**
 * \ingroup loc
 * 
 * This structure contains the number of sets of the BDS SVN Info
 *
 * \param deleteGalSvInfoList_len
 *        - Number of sets of the loc_GalSV elements:
 *
 * \param pGalSV
 *        - Pointer to struct loc_GalSV. See \ref loc_GalSV for more information
 *
*/
typedef struct
{
    uint8_t    deleteGalSvInfoList_len;
    loc_GalSV  *pGalSV;
}loc_GalSVInfo;

/**
 * \ingroup loc
 * 
 * This structure contains the Delete QZSS-L1S data
 *
 * \param deleteQzssL1sDataFlag
 *        - Indicates whether to delete QZSS-L1S data; If the flag is set, delete data from all QZSS-L1S satellite.
 */

typedef struct
{
    uint8_t   deleteQzssL1sDataFlag;
}loc_QzSsL1sdata;

/**
 * \ingroup loc
 * 
 *  This structure contains the Parameter for RegisterEvents
 *
 *  \param  eventRegister
 *          - Specifies the events that the control point is interested
 *          in receiving.
 *          -Values
 *             - 0x00000001 - to receive position report event
 *                            indications
 *             - 0x00000002 - to receive satellite report event
 *                            indications.These reports are sent
 *                            at a 1 Hz rate.
 *             - 0x00000004 - to receive NMEA reports for position
 *                            and satellites in view.The report is
 *                            at a 1 Hz rate.
 *             - 0x00000008 - to receive NI Notify/Verify request
 *                            event indications
 *             - 0x00000010 - to receive time injection request
 *                            event indications.
 *             - 0x00000020 - to receive predicted orbits request
 *                            event indications.
 *             - 0x00000040 - to receive position injection request
 *                            event indications.
 *             - 0x00000080 - to receive engine state report event
 *                            indications.
 *             - 0x00000100 - to receive fix session status report
 *                            event indications.
 *             - 0x00000200 - to receive Wi-Fi position request
 *                            event indications.
 *             - 0x00000400 - to receive notifications from the location
 *                            engine indicating its readiness to accept
 *                            data from the sensors(accelerometer, gyroscope, etc.).
 *             - 0x00000800 - to receive time sync requests from
 *                            the GPS engine. Time sync enables the
 *                            GPS engine to synchronize its clock
 *                            with the sensor processor’s clock.
 *             - 0x00001000 - to receive Stationary Position Indicator (SPI)
 *                            streaming report indications.
 *             - 0x00002000 - to receive location server requests.
 *                            These requests are generated when
 *                            the service wishes to establish a
 *                            connection with a location server.
 *             - 0x00004000 - to receive notifications related
 *                            to network-initiated Geofences. These
 *                            events notify the client when a network-initiated
 *                            Geofence is added, deleted, or edited.
 *             - 0x00008000 - to receive Geofence alerts. These alerts
 *                            are generated to inform the client of
 *                            the changes that may affect a Geofence,
 *                            e.g., if GPS is turned off or if the
 *                            network is unavailable.
 *             - 0x00010000 - to receive notifications when a Geofence
 *                            is breached. These events are generated
 *                            when a UE enters or leaves the perimeter
 *                            of a Geofence. This breach report is for
 *                            a single Geofence.
 *             - 0x00020000 - to register for pedometer control requests
 *                            from the location engine. The location
 *                            engine sends this event to control the
 *                            injection of pedometer reports.
 *             - 0x00040000 - to register for motion data control requests
 *                            from the location engine. The location
 *                            engine sends this event to control the
 *                            injection of motion data.
 *             - 0x00080000 - to receive notification when a batch is full.
 *                            The location engine sends this event to
 *                            notify of Batch Full for ongoing batching
 *                            session.
 *             - 0x00100000 - to receive position report indications
 *                            along with an ongoing batching session.
 *                            The location engine sends this event to
 *                            notify the batched position report while
 *                            a batching session is ongoing.
 *             - 0x00200000 - to receive Wi-Fi Access Point (AP) data
 *                            inject request event indications.
 *             - 0x00400000 - to receive notifications when a Geofence
 *                            is breached. These events are generated
 *                            when a UE enters or leaves the perimeter
 *                            of a Geofence. This breach notification
 *                            is for multiple Geofences. Breaches from
 *                            multiple Geofences are all batched and
 *                            sent in the same notification.
 *             - 0x00800000 - to receive notifications from the location
 *                            engine indicating its readiness to accept
 *                            vehicle data (vehicle accelerometer,
 *                            vehicle angular rate, vehicle odometry, etc.).
 *             - 0x01000000 - to receive system clock and satellite
 *                            measurement report events (system clock,
 *                            SV time, Doppler, etc.).
 *             - 0x02000000 - to receive satellite position reports
 *                            as polynomials.Reports are generated only
 *                            for the GNSS satellite constellations that
 *                            are enabled using QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG.
 *             - 0x40000000 - The control point must enable this mask to receive requests for time zone information from the
 *                             service. These events are generated when there is a need for time zone information in the service.
 *                             QMI_LOC_EVENT_MASK_GET_TIME_ZONE_REQ
 *             - 0x80000000 - The control point must enable this mask to receive asynchronous events related to batching.
 *                            QMI_LOC_EVENT_MASK_BATCHING_STATUS
 *             - 0x100000000 - The location service internal status report mask.
 *                              QMI_LOC_EVENT_MASK_INTERNAL_STATUS_REPORT
 *             - 0x200000000 - The control point must enable this mask to receive asynchronous events for short range node
 *                              (SRN) RSSI scans, for example, BT, BTLE, NFC, etc.
 *                              QMI_LOC_EVENT_MASK_INJECT_SRN_AP_DATA_REQ
 *             - 0x400000000 - The control point must enable this mask to receive the position report event indications that
 *                              contain a GNSS only position.
 *                              QMI_LOC_EVENT_MASK_GNSS_ONLY_POSITION_REPORT
 *             - 0x800000000 - The control point must enable this mask to receive the FDCL service request.
 *                              QMI_LOC_EVENT_MASK_FDCL_SERVICE_REQ
 *             - 0x1000000000 - The control point must enable this mask to receive the DC report event indications that contain
 *                              Disaster & Crisis Reports 
 *                              QMI_LOC_EVENT_MASK_DC_REPORT
 *             - 0x2000000000 - The control point must enable this mask to receive asynchronous events related to the engine
 *                              lock state
 *                              QMI_LOC_EVENT_MASK_ENGINE_LOCK_STATE
 *             - 0x4000000000 - The control point must enable this mask to receive unpropagated fix
 *                              QMI_LOC_EVENT_MASK_UNPROPAGATED_POSITION_REPORT
 *             - 0x8000000000 - The control point must enable this mask to receive the base station observed data service
 *                              request
 *                              QMI_LOC_EVENT_MASK_BS_OBS_DATA_SERVICE_REQ
 *             - 0x10000000000 - The control point must enable this mask to receive the ephemeris data for all GNSS constellations
 *                              QMI_LOC_EVENT_MASK_EPHEMERIS_REPORT
 *             - 0x20000000000 - The control point must enable this mask to receive the upcoming leap second information from the service
 *                               QMI_LOC_EVENT_MASK_NEXT_LS_INFO_REPORT
 *             - 0x40000000000 - The control point must enable this mask to receive the BAND MEASUREMENT METRICS from the ME
 *                               QMI_LOC_EVENT_MASK_GET_BAND_MEASUREMENT_METRICS
 *             - 0x80000000000 - The control point must enable this mask to receive system clock and satellite measurement
 *                               report events (system clock, SV time, Doppler, etc.) at a rate greater than 1hz. Reports
 *                               are generated only for the GNSS satellite constellations that are enabled using
 *                               QMI_LOC_EVENT_MASK_GNSS_NHZ_MEASUREMENT_REPORT
 *             - 0x100000000000 - The control point must enable this mask to receive the QMI_LOC_EVENT_REPORT indication.
 *                                Multiple events can be registered by ORing the individual masks and sending them in this
 *                                TLV. All unused bits in this mask must be set to 0.
 *                                QMI_LOC_EVENT_MASK_GNSS_EVENT_REPORT
 * 
 *  \param  clientStrId_len
 *          - Client Identification String length
 * 
 *  \param  pClientStrId
 *          - Client Identification String
 *          - String identification of this client. This string is sent to the application framework in the
 *            QMI_LOC_LOCATION_REQUEST_NOTIFICATION_IND indication.
 *            - Type: NULL-terminated string
 *            - Maximum string length (including NULL terminator): 5 
 * 
 *  \param  pClientType
 *          - Client Type
 *          - If not specified, defaults to NFW client. If specifically set as the NFW or PRIVILEGED client, the control point
 *            must set the value for enablePosRequestNotification.
 *          - Note: Location requests from privileged client(s) are always allowed, regardless of user privacy settings.
 *          - This may violate OEM, carrier, or government privacy requirements. Contact privacy counsel for advice before choosing “privileged” as the clientType.
 *            - Valid values:
 *              - eQMI_LOC_CLIENT_AFW (1) - Application FrameWork client
 *              - eQMI_LOC_CLIENT_NFW (2) - Non-AFW client
 *              - eQMI_LOC_CLIENT_PRIVILEGED (3) - Privileged client
 *
 *  \param pEnablePosRequestNotification
 *          - If not specified, defaults to FALSE. If set to TRUE, each positioning request made by this client generates a notification to
 *          - the application framework. The value is ignored when the client registers as an AFW client.
 * 
 *  \note   Multiple events can be registered by OR the individual masks and sending
 *          them in this TLV. All unused bits in this mask must be set to 0.
 *
 */
 
typedef struct{
    uint64_t eventRegister;
    uint8_t  clientStrId_len;
    char     *pClientStrId;
    uint32_t *pClientType;
    uint8_t  *pEnablePosRequestNotification;
}pack_loc_EventRegister_t;

/**
 * \ingroup loc
 * 
 * This structure contains Event Register unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t         Tlvresult;
    swi_uint256_t    ParamPresenceMask;
}unpack_loc_EventRegister_t;


/**
 * \ingroup loc
 * 
 * Event Register pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_EventRegister(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_EventRegister_t     *reqArg
);

/**
 * \ingroup loc
 * 
 * Event Register unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_EventRegister(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_EventRegister_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains the Parameter External Power Source State pack.
 *
 *  \param  extPowerState
 *          - Specifies the Power state; injected by the control
 *            point.
 *          - Values
 *             - 0 - Device is not connected to an external power
 *                   source
 *             - 1 - Device is connected to an external power source
 *             - 2 - Unknown external power state
 */


typedef struct{
    uint32_t extPowerState;
}pack_loc_SetExtPowerState_t;

/**
 * \ingroup loc
 * 
 * This structure contains Set Ext Power State unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_SetExtPowerState_t;


/**
 * \ingroup loc
 * 
 * Set Ext Power State pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SetExtPowerState(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SetExtPowerState_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Set Ext Power State unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetExtPowerState(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetExtPowerState_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains the LOC Start pack
 *
 * @param sessionId
 *        - ID of the session as identified by the control point.
 *        - Range: 0 to 255
 *
 * @param pFixRecurrence[OPTIONAL]
 *        - Specifies the type of session in which the control point is interested.
 *        - If this TLV is not specified, recurrence defaults toDefaults to SINGLE.
 *        - Valid values:
 *			- eQMI_LOC_RECURRENCE_PERIODIC (1) - Request periodic position fixes
 *			- eQMI_LOC_RECURRENCE_SINGLE (2) - Request a single position fix
 *
 * @param pHorizontalAccuracyLevel[OPTIONAL]
 *        - Specifies the horizontal accuracy level required by the control point.
 *        - . If not specified, accuracy defaults to LOW.
 *        - Valid values:
 *			- eQMI_LOC_ACCURACY_LOW (1) - Low accuracy
 *			- eQMI_LOC_ACCURACY_MED (2) - Medium accuracy
 *			- eQMI_LOC_ACCURACY_HIGH (3) - High accuracy
 *
 * @param pIntermediateReportState[OPTIONAL]
 *        - Enable/Disable Intermediate Reports
 *		  - Specifies whether the control point is interested in receiving intermediate reports.
 *		  - The control point must explicitly set this field to OFF if it does not wish to receive intermediate position reports.
 *		  - Intermediate position reports are generated at 1 Hz and are ON by default. If intermediate reports are turned ON,
 *		  - the client receives position reports even if the accuracy criteria are not met.
 *		  - The status in such a position report is set to IN_PROGRESS in order for the control point to identify intermediate reports.
 *		   - Valid values:
 *			- eQMI_LOC_INTERMEDIATE_REPORTS_ON (1) - Intermediate reports are turned on
 *			- eQMI_LOC_INTERMEDIATE_REPORTS_OFF (2) - Intermediate reports are turned off
 *
 * @param pMinInterval[OPTIONAL]
 *		  - Minimum Interval Between Final Position Reports
 *        - Minimum time interval, specified by the control point,
 *          that must elapse between position reports.
 *        - Units - Milliseconds
 *        - Default - 1000 ms
 *
 * @param pApplicationInfo[OPTIONAL]
 *        - ID of the Application that Sent this Request
 *		  - Application provider, name, and version.
 *        - See \ref loc_LocApplicationInfo for more information
 *
 * @param pConfigAltitudeAssumed[OPTIONAL]
 *        - Configuration for Altitude Assumed Info in GNSS SV Info Event Info Event
 *        - Specifies the configuration to include Altitude Assumed information in the GNSS SV Info Event. When enabled, an additional GNSS SV Info event
 *		  - indication is sent to the control point that also includes the altitude assumed information.
 *		  - If not specified, the configuration defaults to ENABLED.
 *			- Valid values:
 *				- eQMI_LOC_ALTITUDE_ASSUMED_IN_GNSS_SV_INFO_ENABLED (1) - Enable Altitude Assumed information in GNSS SV Info Event.
 *				- eQMI_LOC_ALTITUDE_ASSUMED_IN_GNSS_SV_INFO_DISABLED (2) - Disable Altitude Assumed information in GNSS SV Info Event.
 *
 * @param pMinIntermediatePositionReportInterval[OPTIONAL]
 *			- Minimum Interval Between Intermediate Position Report
 *			- Minimum time interval for intermediate position reports, specified by the control point, that, between the position reports elapsed time, 
 *			- must be longer than the interval time. If this optional value is not set or set to the default value (0), the intermediate position is reported when it is ready.
 *			 - Units: Milliseconds
 *			 - Default: 0 ms
 *
 * @param pPositionReportTimeout[OPTIONAL]
 *			- Maximum Wait Time to Get a Position Report
 *			- Maximum time to work on each fix, specified by the control point. The GPS engine returns QMI_ERR_INTERNAL 
 *			- if a position cannot be obtained within the positionReportTimeout value.
 *			 - Units: Milliseconds
 *			 - Default: 255*1000 ms
 *			 - Range: 1000 - 255*1000 ms
 *
 * @param pSharePosition[OPTIONAL]
 *			- Share Position Report with Other Clients
 *			- Share the position report with the other QMI_LOC clients:
 *			- 0x00 (FALSE) - Do not share the position report
 *			- 0x01 (TRUE) – Share the position report If this optional TLV is not set, the GPS engine allows the position sharing.
 *
 * @param pReportGnssOnlyPosition[OPTIONAL]
 *			- Report GNSS Only Position
 *			- Requests the GPS engine to report positions that could be GNSS only or combined with other technologies, such as Sensors. 
 *			 - Values:
 *				- 0x00 (FALSE) - Report GNSS only positions is disabled (default)
 *				- 0x01 (TRUE) – Report GNSS only positions is enabled
 *
 * @param pGNSSPowerMode[OPTIONAL]
 *			- GNSS Power Mode If the power mode is not set by the client, 
 *			- eQMI_LOC_POWER_MODE_NORMAL is the default value. Please note that there may be other client with different powerMode setting. 
 *			- In such cases, the GNSS receiver is configured with powerMode with highest power consumption among the requesting clients.
 *			- \ref LocGNSSPowerMode for more information
 *
*/
typedef struct{
	uint8_t  sessionId;
	uint32_t *pFixRecurrence;
	uint32_t *pHorizontalAccuracyLevel;
	uint32_t *pIntermediateReportState;
	uint32_t *pMinInterval;
	loc_LocApplicationInfo *pApplicationInfo;
	uint32_t   *pConfigAltitudeAssumed;
	uint32_t   *pMinIntermediatePositionReportInterval;
	uint32_t   *pPositionReportTimeout;
	uint8_t    *pSharePosition;
	uint8_t    *pReportGnssOnlyPosition;
	loc_LocGNSSPowerMode *pGNSSPowerMode;
}pack_loc_Start_t;

/**
 * \ingroup loc
 * 
 * This structure contains Start LOC unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_Start_t;

/**
 * \ingroup loc
 * 
 * LOC Start pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_Start(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_Start_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Loc Start  unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_Start(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_Start_t *pOutput
);


/**
 * \ingroup loc
 * 
 * This structure contains Stop LOC pack
 *
 * \param sessionId
 *        - ID of the session as identified by the control point.
 *        - Range: 0 to 255
 */


typedef struct{
    uint8_t     SessionId;
}pack_loc_Stop_t;

/**
 * \ingroup loc
 * 
 * This structure contains Stop LOC unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_Stop_t;

/**
 * \ingroup loc
 * 
 * Loc Stop pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_Stop(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_Stop_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Loc Stop unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_Stop(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_Stop_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains Set Operation Mode pack
 *
 * \param mode
 *        - Valid values:
 *           - eQMI_LOC_OPER_MODE_DEFAULT (1) - Use the default engine mode
 *           - eQMI_LOC_OPER_MODE_MSB (2) - Use the MS-based mode
 *           - eQMI_LOC_OPER_MODE_MSA (3) - Use the MS-assisted mode
 *           - eQMI_LOC_OPER_MODE_STANDALONE (4) - Use Standalone mode
 *           - eQMI_LOC_OPER_MODE_CELL_ID (5) - Use cell ID; this mode is
 *             only valid for GSM/UMTS networks
 *           - eQMI_LOC_OPER_MODE_WWAN (6) - Use WWAN measurements to calculate
 *             the position; if this mode is set, AFLT will be used for 1X
 *             networks and OTDOA will be used for LTE networks
 */
typedef struct{
    uint32_t mode;
}pack_loc_SetOperationMode_t;

/**
 * \ingroup loc
 * 
 * This structure contains Set Operation Mode unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_SetOperationMode_t;

/**
 * \ingroup loc
 * 
 * Set Operation Mode pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SetOperationMode(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SetOperationMode_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Set Operation Mode unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetOperationMode(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetOperationMode_t *pOutput
);


/**
 * \ingroup loc
 * 
 * This structure contains LOC delete assist data pack
 *
 * \param deleteAllFlag
 *        - Delete All
 *        - Indicates whether to delete all assistance data.
 *        - Valid values:
 *          - 0x01 (TRUE) – Delete all assistance data; if this flag is set, 
 *          - ignore all the other information contained in the optional fields for this message
 *          - 0x00 (FALSE) – The optional fields in the message are used to determine which data to delete 
 * 
 * \param pSVInfo (optional)
 *        - Delete SV Info. See \ref loc_SVInfo for more information
 *
 * \param pGnssData (optional)
 *        - Delete GNSS Data. See \ref loc_GnssData for more information
 *
 * \param pCellDb (optional)
 *        - Delete Cell Database. See \ref loc_CellDb for more information
 *
 * \param pClkInfo (optional)
 *        - Delete Clock Info. See \ref loc_ClkInfo for more information
 *
 * \param pBdsSVInfo (optional)
 *        - Delete BDS SV Info. See \ref loc_BdsSVInfo for more information
 * 
 *  \param pGalSVInfo (optional)
 *        - Delete GAL SV Info. See \ref loc_GalSVInfo for more information
 * 
 *  \param pQzSsL1sdata (optional)
 *        - Delete QZSS-L1S data. See \ref loc_QzSsL1sdata for more information
 * 
 *  \note deleteAllFlag is assumed as true, if all optional parameters are NULL  
 */

typedef struct{
    uint8_t deleteAllFlag;
    loc_SVInfo *pSVInfo;
    loc_GnssData *pGnssData;
    loc_CellDb *pCellDb;
    loc_ClkInfo *pClkInfo;
    loc_BdsSVInfo *pBdsSVInfo;
    loc_GalSVInfo *pGalSVInfo;
    loc_QzSsL1sdata *pQzSsL1sdata;

}pack_loc_Delete_Assist_Data_t;

/**
 * \ingroup loc
 * 
 * This structure contains LOC delete assist data unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_Delete_Assist_Data_t;



/**
 * \ingroup loc
 * 
 * Delete Assistant Data pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_DeleteAssistData(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_Delete_Assist_Data_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Delete Assistant Data unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_DeleteAssistData(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_Delete_Assist_Data_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains Dilution of precision associated with this position.
 *
 *  \param  PDOP
 *          - Position dilution of precision.
 *          - Range - 1 (highest accuracy) to 50 (lowest accuracy)
 *          - PDOP = square root of (Square of HDOP + Square of VDOP2 )
 *  \param  HDOP
 *          - Horizontal dilution of precision.
 *          - Range - 1 (highest accuracy) to 50 (lowest accuracy)
 *  \param  VDOP
 *          - Vertical dilution of precision.
 *          - Range-  1 (highest accuracy) to 50 (lowest accuracy)
 *
 */

typedef struct {
	float		PDOP;
	float		HDOP;
	float		VDOP;
}loc_precisionDilution;


/**
 * \ingroup loc
 * 
 *  This structure contains Sensor Data Usage info.
 *
 *  \param  usageMask
 *          - Specifies which sensors were used in calculating the position
 *            in the position report.
 *            - Value
 *              - 0x00000001 - Accelerometer used
 *              - 0x00000002 - Gyroscope used
 *  \param  aidingIndicatorMask
 *          - Specifies which results were aided by sensors.
 *            - Value
 *             - 0x00000001 - AIDED_HEADING
 *             - 0x00000002 - AIDED_SPEED
 *             - 0x00000004 - AIDED_POSITION
 *             - 0x00000008 - AIDED_VELOCITY
 *
 */

typedef struct {
     uint32_t     usageMask;
     uint32_t     aidingIndicatorMask;
}loc_sensorDataUsage;

/**
 * \ingroup loc
 * 
 *  This structure contains SVs Used to Calculate the Fix.
 *
 *  \param  gnssSvUsedList_len
 *          - Number of sets of gnssSvUsedList
 *  \param  pGnssSvUsedList
 *          - Entry in the list contains the SV ID of a satellite
 *            used for calculating this position report.
 *          - Following information is associated with each SV ID:
 *            - GPS - 1 to 32
 *            - SBAS - 33 to 64
 *            - GLONASS - 65 to 96
 *            - QZSS - 193 to 197
 *            - BDS - 201 to 237
 *
 */

typedef struct {
     uint8_t     gnssSvUsedList_len ;
     uint16_t     gnssSvUsedList[LOC_UINT8_MAX_STRING_SZ];
}loc_svUsedforFix;

/**
 * \ingroup loc
 * 
 *  This structure contains Dilution of precision associated with this position.
 *
 *  \param  PDOP
 *          - Position dilution of precision.
 *          - Range - 0 (highest accuracy) to 50 (lowest accuracy)
 *          - PDOP = square root of (Square of HDOP + Square of VDOP2 )
 *  \param  HDOP
 *          - Horizontal dilution of precision.
 *          - Range - 0 (highest accuracy) to 50 (lowest accuracy)
 *  \param  VDOP
 *          - Vertical dilution of precision.
 *          - Range-  0 (highest accuracy) to 50 (lowest accuracy)
 *  \param  GDOP
 *          - Geometric dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 *  \param  TDOP
 *          - Time dilution of precision.
 *          - Range-  0 (highest accuracy) to 50 (lowest accuracy)
 *
 */
typedef struct {
     float PDOP;
     float HDOP;
     float VDOP;
     float GDOP;
     float TDOP;
}loc_extendedPrecisionDilution;

/**
 * \ingroup loc
 *
 *  This structure contains Differential correction source ID.
 *
 *  \param  dgnssStationId_len
 *          -  Number of sets of dgnssStationId
 *  \param  dgnssStationId
 *			- List of DGNSS station IDs providing corrections.
 *			- Range: 
 *				- SBAS: 120 to 158 and 183 to 191 
 *				- Monitoring Station: 1000-2023 (Station ID biased by 1000). 
 *				- Other values reserved. 
 *
 */
typedef struct {
	uint8_t		dgnssStationId_len;
	uint16_t	dgnssStationId[LOC_MAX_DGNSS_STATIONID];
}loc_diffCorrectionSourceID;

/**
 * \ingroup loc
 *
 *  This structure contains velocity parameters.
 *
 *  \param east 
 *			- east velocity, Units: Meters/second
 *
 *	\param north  
 *			- west velocity, Units: Meters/second
 *
 *	\param up  
 *			- up velocity, Units: Meters/second
 *
 */
typedef struct {
	float  east;
	float  north;
	float  up;
}loc_velocity;

/**
 * \ingroup loc
 *
 *  This structure contains SVs Signal Types in the SVs Used list.
 *
 *  \param  gnssSvUsedSignalTypeList_len
 *          -  Number of sets of dgnssStationId
 *  \param  gnssSvUsedSignalTypeList
 *			-  Indicates the signal type of each satellite in expandedGnssSvUsedList. The signal type list is aligned with the SVs in expandedGnssSvUsedList. 
 *			- Value of 0 means invalid. 
 *			- Valid bitmasks: 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GPS_L1CA (0x00000001) – GPS L1CA RF band 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GPS_L1C (0x00000002) – GPS L1C RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GPS_L2C_L (0x00000004) – GPS L2C_L RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GPS_L5_Q (0x00000008) – GPS L5_Q RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GLONASS_G1 (0x00000010) – GLONASS G1 (L1OF) RF band 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GLONASS_G2 (0x00000020) – GLONASS G2 (L2OF) RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GALILEO_E1_C (0x00000040) – Galileo E1_C RF band 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GALILEO_E5A_Q (0x00000080)–GalileoE5A_QRFband 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_GALILEO_E5B_Q (0x00000100) – Galileo E5B_Q RF band 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_BEIDOU_B1_I (0x00000200) – BeiDou B1_I RF band 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_BEIDOU_B1C (0x00000400) – BeiDou B1C RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_BEIDOU_B2_I (0x00000800) – BeiDou B2_I RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_BEIDOU_B2A_I (0x00001000) – BeiDou B2A_I RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_QZSS_L1CA (0x00002000) – QZSS L1CA RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_QZSS_L1S (0x00004000) – QZSS L1S RF band 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_QZSS_L2C_L (0x00008000) – QZSS L2C_L RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_QZSS_L5_Q (0x00010000) – QZSS L5_Q RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_SBAS_L1_CA (0x00020000) – SBAS L1_CA RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_NAVIC_L5 (0x00040000) – NavIC L5 RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_ TYPE_BEIDOU_B2A_Q (0x00080000) – BeiDou B2A_Q RF band
 */
typedef struct {
	uint8_t  gnssSvUsedSignalTypeList_len;
	uint64_t gnssSvUsedSignalTypeList[LOC_MAX_GNSS_USEDSIGNALTYPE];
}loc_svsSignalTypes;

/**
 * \ingroup loc
 *
 *  This structure contains Jammer Indicator GNSS Signal parameters.
 *
 *  \param agcMetricDb 
 *			- AGC metric in 0.01 dB
 *
 *	\param bpMetricDb  
 *			- BP metric in 0.01 dB
 */
typedef struct {
	int32_t  agcMetricDb;
	int32_t  bpMetricDb;
}loc_jammerIndicator;

/**
 * \ingroup loc
 *
 *  This structure contains  Jammer Indicator of each GNSS Signal Indicates the jammer indicator of each signal.
 *
 *  \param jammerIndicatorList_len
 *			- Number of sets of the agcMetricDb 
 *
 *	\param agcMetricDb
 *			- List of loc_jammerIndicator
 */
typedef struct {
	uint8_t				jammerIndicatorList_len;
	loc_jammerIndicator agcMetricDb[LOC_MAX_JAMMERINDICATOR];
}loc_jammerIndicatorList;

/**
 * \ingroup loc
 * 
 *  This structure contains Satellite Signal Types.
 *
 *  \param  gnssSvUsedSignalTypeList_len
 *          - Number of sets of the gnssSvUsedSignalTypeList
 *  \param  gnssSvUsedSignalTypeList
 *          - Indicates the signal type of each satellite in expandedGnssSvUsedList. The signal type list is aligned with the SVs in expandedGnssSvUsedList. 
 *             - Value:
 *              - 0 means invalid.
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1CA (0x00000001) - GPS L1CA RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1C (0x00000002) - GPS L1C RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L2C_L (0x00000004) - GPS L2C_L RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L5_Q (0x00000008) - GPS L5_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G1 (0x00000010) - GLONASS G1 (L1OF) RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G2 (0x00000020) - GLONASS G2 (L2OF) RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E1_C (0x00000040) - Galileo E1_C RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5A_Q (0x00000080) - Galileo E5A_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5B_Q (0x00000100) - Galileo E5B_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1_I (0x00000200) - BeiDou B1_I RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1C (0x00000400) - BeiDou B1C RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2_I (0x00000800) - BeiDou B2_I RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_I (0x00001000) - BeiDou B2A_I RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1CA (0x00002000) - QZSS L1CA RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1S (0x00004000) - QZSS L1S RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L2C_L (0x00008000) - QZSS L2C_L RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L5_Q (0x00010000) - QZSS L5_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_SBAS_L1_CA (0x00020000) - SBAS L1_CA RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_NAVIC_L5 (0x00040000) - NavIC L5 RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_Q (0x00080000) - BeiDou B2A_Q RF band
 */
typedef struct{
    uint8_t gnssSvUsedSignalTypeList_len;
    uint64_t gnssSvUsedSignalTypeList[MAX_SATELLITES_SIGNAL_TYPES];
}loc_satelliteSignalTypes;

/**
 * \ingroup loc
 * 
 *  This structure contains Expanded SVs Used to Calculate the Fix.
 *
 *  \param  expandedGnssSvUsedList_len
 *          - Number of sets of the expandedGnssSvUsedList
 *  \param  expandedGnssSvUsedList
 *          - If the service reports expandedGnssSvUsedList, gnssSvUsedList is not reported. 
 *            Each entry in the list contains the SV ID of a satellite used to calculate this position report. 
 *            The following information is associated with each SV ID.
 *             - Range:
 *               - For GPS: 1 to 32
 *               - For GLONASS: 65 to 96
 *               - For QZSS: 193 to 197
 *               - For BDS: 201 to 237
 *               - For Galileo: 301 to 336
 *               - For NavIC: 401 to 414
 */
typedef struct {
    uint8_t  expandedGnssSvUsedList_len;
    uint16_t expandedGnssSvUsedList[MAX_Expanded_SVS];
}loc_expandedSVs;

/**
 * \ingroup loc
 * 
 *  This structure contains GPS Time info.
 *
 *  \param  gpsWeek
 *          - Current GPS week as calculated from midnight, Jan. 6, 1980.
 *          - Units - Weeks
 *  \param  gpsTimeOfWeekMs
 *          - Amount of time into the current GPS week.
 *          - Units - Milliseconds
 *
 */

typedef struct {
     uint16_t     gpsWeek;
     uint32_t    gpsTimeOfWeekMs;
}loc_gpsTime;

/**
 * \ingroup loc
 * 
 *  This structure contains Event Position Report Indication unpack
 *
 *  \param  sessionStatus
 *          - Values
 *            - 0 - Session was successful
 *            - 1 - Session is still in progress; further position reports will be generated
 *                  until either the fix criteria specified by the client are met or the client
 *                  response timeout occurs.
 *            - 2 - Session failed..
 *            - 3 - Fix request failed because the session timed out.
 *            - 4 - Fix request failed because the session was ended by the user.
 *            - 5 - Fix request failed due to bad parameters in the request.
 *            - 6 - Fix request failed because the phone is offline.
 *            - 7 - Fix request failed because the engine is locked
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  sessionId
 *             - ID of the session that was specified in the Start request
 *             - Range - 0 to 255
 *             - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  \param  pLatitude
 *             - Latitude (specified in WGS84 datum)
 *             - Type - Floating point
 *             - Units - Degrees
 *             - Range - -90.0 to 90.0
 *             - Positive values indicate northern latitude
 *             - Negative values indicate southern latitude
 *             - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  \param  pLongitude
 *             - Longitude (specified in WGS84 datum)
 *             - Type - Floating point
 *             - Units - Degrees
 *             - Range - -180.0 to 180.0
 *             - Positive values indicate eastern latitude
 *             - Negative values indicate western latitude
 *             - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *   \param  pHorUncCircular
 *             - Horizontal position uncertainty.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x12</B>
 *
 *   \param  pHorUncEllipseSemiMinor
 *             - Semi-minor axis of horizontal elliptical uncertainty.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x13</B>
 *
 *   \param  pHorUncEllipseSemiMajor
 *             - Semi-major axis of horizontal elliptical uncertainty.
 *             - Units: Meters
 *             - Bit to check in ParamPresenceMask - <B>0x14</B>
 *
 *   \param  pHorUncEllipseOrientAzimuth
 *             - Elliptical horizontal uncertainty azimuth of orientation.
 *             - Units - Decimal degrees
 *             - Range - 0 to 180
 *             - Bit to check in ParamPresenceMask - <B>0x15</B>
 *
 *   \param  pHorConfidence
 *             - Horizontal uncertainty confidence.
 *             - If both elliptical and horizontal uncertainties
 *               are specified in this message, the confidence
 *               corresponds to the elliptical uncertainty.
 *             - Units - Percentage
 *             - Range 0-99
 *             - Bit to check in ParamPresenceMask - <B>0x16</B>
 *
 *   \param  pHorReliability
 *          - Values
 *            - 0 - Location reliability is not set.
 *            - 1 - Location reliability is very low; use it at
 *                  your own risk
 *            - 2 - Location reliability is low; little or no
 *                  cross-checking is possible.
 *            - 3 - Location reliability is medium; limited cross-check passed
 *            - 4 - Location reliability is high; strong cross-check passed
 *         - Bit to check in ParamPresenceMask - <B>0x17</B>
 *
 *   \param  pSpeedHorizontal
 *             - Horizontal speed.
 *             - Units - Meters/second
 *             - Bit to check in ParamPresenceMask - <B>0x18</B>
 *
 *   \param  pSpeedUnc
 *             - 3-D Speed uncertainty.
 *             - Units - Meters/second.
 *             - Bit to check in ParamPresenceMask - <B>0x19</B>
 *
 *   \param  pAltitudeWrtEllipsoid
 *             - Altitude With Respect to WGS84 Ellipsoid.
 *             - Units - Meters
 *             - Range -500 to 15883
 *             - Bit to check in ParamPresenceMask - <B>0x1A</B>
 *
 *   \param  pAltitudeWrtMeanSeaLevel
 *             - Altitude With Respect to Sea Level.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x1B</B>
 *
 *   \param  pVertUnc
 *             - Vertical uncertainty.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x1C</B>
 *
 *   \param  pVertConfidence
 *             - Vertical uncertainty confidence.
 *             - Units - Percentage
 *             - Range 0 to 99
 *             - Bit to check in ParamPresenceMask - <B>0x1D</B>
 *
 *   \param  pVertReliability
 *          - Values
 *             - 0 - Location reliability is not set.
 *             - 1 - Location reliability is very low;
 *                   use it at your own risk.
 *             - 2 - Location reliability is low; little or no
 *                   cross-checking is possible
 *             - 3 - Location reliability is medium; limited
 *                   cross-check passed
 *             - 4 - Location reliability is high; strong
 *                   cross-check passed
 *             - Bit to check in ParamPresenceMask - <B>0x1E</B>
 *
 *   \param  pSpeedVertical
 *             - Vertical speed.
 *             - Units - Meters/second
 *             - Bit to check in ParamPresenceMask - <B>0x1F</B>
 *
 *   \param  pHeading
 *             - Heading.
 *             - Units - Degree
 *             - Range 0 to 359.999
 *             - Bit to check in ParamPresenceMask - <B>0x20</B>
 *
 *   \param  pHeadingUnc
 *             - Heading uncertainty.
 *             - Units - Degree
 *             - Range 0 to 359.999
 *             - Bit to check in ParamPresenceMask - <B>0x21</B>
 *
 *   \param  pMagneticDeviation
 *             - Difference between the bearing to true north and the
 *               bearing shown on a magnetic compass. The deviation is
 *               positive when the magnetic north is east of true north.
 *             - Bit to check in ParamPresenceMask - <B>0x22</B>
 *
 *   \param  pTechnologyMask
 *          - Values
 *             - 0x00000001 - Satellites were used to generate the fix
 *             - 0x00000002 - Cell towers were used to generate the fix
 *             - 0x00000004 - Wi-Fi access points were used to generate the fix
 *             - 0x00000008 - Sensors were used to generate the fix
 *             - 0x00000010 - Reference Location was used to generate the fix
 *             - 0x00000020 - Coarse position injected into the location engine
 *                            was used to generate the fix
 *             - 0x00000040 - AFLT was used to generate the fix
 *             - 0x00000080 - GNSS and network-provided measurements were
 *                            used to generate the fix
 *          - Bit to check in ParamPresenceMask - <B>0x23</B>
 *
 *  \param  pPrecisionDilution
 *            - See \ref loc_precisionDilution for more information
 *            - Bit to check in ParamPresenceMask - <B>0x24</B>
 *
 *   \param  pTimestampUtc
 *             - UTC timestamp
 *             - Units - Milliseconds since Jan. 1, 1970
 *             - Bit to check in ParamPresenceMask - <B>0x25</B>
 *
 *   \param  pLeapSeconds
 *             - Leap second information. If leapSeconds is not available,
 *               timestampUtc is calculated based on a hard-coded value
 *               for leap seconds.
 *             - Units - Seconds
 *             - Bit to check in ParamPresenceMask - <B>0x26</B>
 *
 *  \param  pGpsTime
 *            - See \ref loc_gpsTime for more information
 *            - Bit to check in ParamPresenceMask - <B>0x27</B>
 *
 *   \param  pTimeUnc
 *             - Time uncertainty.
 *             - Units - Milliseconds
 *             - Bit to check in ParamPresenceMask - <B>0x28</B>
 *
 *   \param  pTimeSrc
 *          - Values
 *             - 0 - Invalid time.
 *             - 1 - Time is set by the 1X system.
 *             - 2 - Time is set by WCDMA/GSM time tagging.
 *             - 3 - Time is set by an external injection.
 *             - 4 - Time is set after decoding over-the-air GPS navigation
 *                   data from one GPS satellite.
 *             - 5 - Time is set after decoding over-the-air GPS navigation
 *                   data from multiple satellites.
 *             - 6 - Both time of the week and the GPS week number
 *                   are known.
 *             - 7 - Time is set by the position engine after the
 *                   fix is obtained
 *             - 8 - Time is set by the position engine after performing SFT,
 *                   this is done when the clock time uncertainty is large.
 *             - 9 - Time is set after decoding GLO satellites.
 *             - 10- Time is set after transforming the GPS to GLO time
 *             - 11- Time is set by the sleep time tag provided by
 *                   the WCDMA network.
 *             - 12- Time is set by the sleep time tag provided by the
 *                   GSM network
 *             - 13- Source of the time is unknown
 *             - 14- Time is derived from the system clock (better known
 *                   as the slow clock); GNSS time is maintained
 *                   irrespective of the GNSS receiver state
 *             - 15- Time is set after decoding QZSS satellites.
 *             - 16- Time is set after decoding BDS satellites.
 *           - Bit to check in ParamPresenceMask - <B>0x29</B>
 *
 *  \param  pSensorDataUsage
 *            - See \ref loc_sensorDataUsage for more information
 *            - Bit to check in ParamPresenceMask - <B>0x2A</B>
 *
 *   \param  pFixId
 *             - Fix count for the session. Starts with 0 and increments
 *               by one for each successive position report for a
 *               particular session.
 *             - Bit to check in ParamPresenceMask - <B>0x2B</B>
 *
 *  \param  pSvUsedforFix
 *            - See \ref loc_svUsedforFix for more information
 *            - Bit to check in ParamPresenceMask - <B>0x2C</B>
 *
 *   \param  pAltitudeAssumed
 *             - Indicates whether altitude is assumed or calculated.
 *             - Value
 *               - 0x00 - Altitude is calculated
 *               - 0x01 - Altitude is assumed
 *             - Bit to check in ParamPresenceMask - <B>0x2D</B>
 *
 *	\param pVelEnu
 *			- Velocity ENU (East, North, Up)
 *			- Values: East, North, Up velocity. Units: Meters/second 
 *          - See \ref  loc_velocity
 *             - Bit to check in ParamPresenceMask - <B>0x2E</B>
 *	\param pVelEncEnu
 *			-  Velocity Uncertainty ENU
 *			-  Values: East, North, Up velocity uncertainty. Units: Meters/second 
 *          - See \ref  loc_velocity
 *          - Bit to check in ParamPresenceMask - <B>0x2F</B>
 *	\param pNavSolutionMask
 *			- Navigation solutions that are used to calculate the GNSS position report. 
 *			- Valid bitmasks: 
 *				- QMI_LOC_NAV_MASK_SBAS_ CORRECTION_IONO (0x00000001) – Bitmask specifying whether SBAS ionospheric correction is used
 *				- QMI_LOC_NAV_MASK_SBAS_ CORRECTION_FAST (0x00000002) – Bitmask specifying whether SBAS fast correction is used
 *				- QMI_LOC_NAV_MASK_SBAS_ CORRECTION_LONG (0x00000004) – Bitmask specifying whether SBAS long-tem correction is used
 *				- QMI_LOC_NAV_MASK_SBAS_ INTEGRITY (0x00000008) – Bitmask specifying whether SBAS integrity information is used
 *				- QMI_LOC_NAV_MASK_ CORRECTION_DGNSS (0x00000010) – Bitmask specifying whether DGNSS information is used
 *				- QMI_LOC_NAV_MASK_ONLY_ SBAS_CORRECTED_SV_USED (0x00000020) – Bitmask specifying whether only SBAS corrected SVs are used for the ﬁx; if mask is not set, 
 *																				all-in-view SVs are used for ﬁx 
 *          - Bit to check in ParamPresenceMask - <B>0x30</B>
 *				
 *	\param pSensorSubTechnologyMask
 *			-  Sensor subtechnology information.
 *				- Valid bitmasks: 
 *				- QMI_LOC_SENSOR_SUB_MASK_ PDR_ENABLED (0x00000001) – Bitmask specifying whether PDR is enabled or disabled
 *				- QMI_LOC_SENSOR_SUB_MASK_ PEDOMETER_ENABLED (0x00000002) – Bitmask specifying whether a pedometer was used
 *				- QMI_LOC_SENSOR_SUB_MASK_ VEHICULAR_ENABLED (0x00000004) – Bitmask specifying whether vehicular sensor assistance is enabled or disabled
 *          - Bit to check in ParamPresenceMask - <B>0x31</B>
 *
 *	\param pGnssOnlyPosition
 *			- GNSS Only Position Report
 *				- Indicates if this position report is generated from GNSS only technology.
 *				- Values: 
 *					- 0x00 (FALSE) – Position is generated with other technologies (default)
 *					- 0x01 (TRUE) – Position is generated from GNSS technology only 
 *          - Bit to check in ParamPresenceMask - <B>0x32</B>
 *
 *	\param pExtendedPrecisionDilution
 *			- Extended Dilution of Precision Dilution of precision associated with this position.
 *          - See \ref  loc_extendedPrecisionDilution
 *          - Bit to check in ParamPresenceMask - <B>0x33</B>
 *
 *	\param pDifferentialCorrectionSourceID
 *			- Differential correction source ID.
 *          - See \ref  loc_diffCorrectionSourceID
 *          - Bit to check in ParamPresenceMask - <B>0x34</B>
 * 
 *	\param pSpoofReportMask
 *			- Spoof report 
 *				- Valid bitmasks:
 *				- QMI_LOC_POSITION_SPOOFED (0x00000001) – Set bit indicates suspected spooﬁng in position
 *				- QMI_LOC_TIME_SPOOFED (0x00000002) – Set bit indicates suspected spooﬁng in time
 *				- QMI_LOC_NAVIGATION_DATA_ SPOOFED (0x00000004) – Set bit indicates suspected spooﬁng in navigation data
 *          - Bit to check in ParamPresenceMask - <B>0x35</B>
 * 
 *	\param pExpandedSVs
 *			- Expanded SVs Used to Calculate the Fix.
 *          - See \ref  loc_expandedSVs
 *          - Bit to check in ParamPresenceMask - <B>0x36</B>
 * 
 *	\param pSVsSignalTypes
 *			- SVs Signal Types in the SVs Used list.
 *          - See \ref  loc_svsSignalTypes
 *          - Bit to check in ParamPresenceMask - <B>0x37</B>
 * 
 *	\param pJammerIndicator
 *			- Jammer Indicator of each GNSS Signal Indicates the jammer indicator of each signal. 
 *          - See \ref  loc_jammerIndicatorList
 *          - Bit to check in ParamPresenceMask - <B>0x38</B>
 *
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
	uint32_t					sessionStatus;
	uint8_t						sessionId;
	double						*pLatitude;
	double						*pLongitude;
	float						*pHorUncCircular;
	float						*pHorUncEllipseSemiMinor;
	float						*pHorUncEllipseSemiMajor;
	float						*pHorUncEllipseOrientAzimuth;
	uint8_t                     *pHorConfidence;
	uint32_t                    *pHorReliability;
	float						*pSpeedHorizontal;
	float						*pSpeedUnc;
	float						*pAltitudeWrtEllipsoid;
	float						*pAltitudeWrtMeanSeaLevel;
	float						*pVertUnc;
	uint8_t                     *pVertConfidence;
	uint32_t                    *pVertReliability;
	float						*pSpeedVertical;
	float						*pHeading;
	float						*pHeadingUnc;
	float						*pMagneticDeviation;
	uint32_t                    *pTechnologyMask;
	loc_precisionDilution       *pPrecisionDilution;
	uint64_t                    *pTimestampUtc;
	uint8_t						*pLeapSeconds;
	loc_gpsTime					*pGpsTime;
	float						*pTimeUnc;
	uint32_t                    *pTimeSrc;
	loc_sensorDataUsage         *pSensorDataUsage;
	uint32_t                    *pFixId;
	loc_svUsedforFix            *pSvUsedforFix;
	uint8_t                     *pAltitudeAssumed;
	loc_velocity				*pVelEnu;
	loc_velocity				*pVelEncEnu;
	uint64_t					*pNavSolutionMask;
	uint32_t					*pSensorSubTechnologyMask;
	uint8_t						*pGnssOnlyPosition;
	loc_extendedPrecisionDilution *pExtendedPrecisionDilution;
	loc_diffCorrectionSourceID  *pDifferentialCorrectionSourceID;
	uint64_t                    *pSpoofReportMask;
	loc_expandedSVs	            *pExpandedSVs;
	loc_svsSignalTypes          *pSvsSignalTypes;
	loc_jammerIndicatorList     *pJammerIndicator;
	uint16_t                    Tlvresult;
	swi_uint256_t               ParamPresenceMask;
}unpack_loc_PositionRpt_Ind_t;

/**
 * \ingroup loc
 * 
 * Loc Position Report Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_PositionRpt_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_PositionRpt_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Engine State field.
 *
 *  @param  engineState
 *          - Location engine state.
 *          - Valid values
 *            - 1 - Location engine is on
 *            - 2 - Loction engine is off
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t engineState;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_EngineState_Ind_t;

/**
 * \ingroup loc
 * 
 * Loc Engine State Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_EngineState_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_EngineState_Ind_t *pOutput
);


/**
 * \ingroup loc
 * 
 *  This structure contains LOC Set External Power Configure status field.
 *
 *  @param  status
 *          - Valid values
 *            - 0 - Request was completed successfully
 *            - 1 - Request failed because of a general failure.
 *            - 2 - Request failed because it is not supported.
 *            - 3 - Request failed because it contained invalid parameters
 *            - 4 - Request failed because the engine is busy
 *            - 5 - Request failed because the phone is offline
 *            - 6 - Request failed because it timed out
 *            - 7 - Request failed because an undefined configuration was requested
 *            - 8 - engine could not allocate sufficient memory
 *            - 9 - Request failed because the maximum number of
 *                  Geofences are already programmed
 *            - 10 -Location service failed because of an XTRA version-based file
 *                  format check failure
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t status;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_SetExtPowerConfig_Ind_t;

/**
 * \ingroup loc
 * 
 * Loc Set External Power Configure Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetExtPowerConfig_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetExtPowerConfig_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains Set Operation Mode unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_SLQSLOCGetBestAvailPos_t;

/**
 * \ingroup loc
 * 
 * This structure contains Set Operation Mode pack
 *
 * \param xid
 *        - Identifies the transaction.
 *        - The transaction ID is returned in the Get Best Available
 *          Position indication.
 */
typedef struct{
    uint32_t xid;
}pack_loc_SLQSLOCGetBestAvailPos_t;

/**
 * \ingroup loc
 * 
 * Get Best Avail position pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @note   Best Available Position Information will be sent through eQMI_LOC_GET_BEST_AVAIL_POS_IND notification.
 *		   Call unpack_loc_BestAvailPos_Ind() to unpack the Best Available Position Information
 */
int pack_loc_SLQSLOCGetBestAvailPos(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SLQSLOCGetBestAvailPos_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Get Best Avail position unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 * @note   Best Available Position Information will be sent through eQMI_LOC_GET_BEST_AVAIL_POS_IND notification.
 *		   Call unpack_loc_BestAvailPos_Ind() to unpack the Best Available Position Information 
 */
int unpack_loc_SLQSLOCGetBestAvailPos(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SLQSLOCGetBestAvailPos_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains Best Available Position
 *
 *  \param  status
 *          - Valid values:
 *             - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *             - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of
 *               a general failure
 *             - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is
 *               not supported
 *             - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because
 *               it contained invalid parameters
 *             - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine
 *               is busy
 *             - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone
 *               is offline
 *             - eQMI_LOC_TIMEOUT (6) - Request failed because it timed out
 *             - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because
 *               an undefined configuration was requested
 *             - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because
 *               the engine could not allocate sufficient memory for the request
 *             - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because
 *               the maximum number of Geofences are already programmed
 *             - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed
 *               because of an XTRA version-based file format check failure
  *             - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  xid
 *             Transaction ID that was specified in the Get Best Available Position request.
 *             - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  \param  pLatitude
 *             - Latitude (specified in WGS84 datum)
 *             - Type - Floating point
 *             - Units - Degrees
 *             - Range - -90.0 to 90.0
 *             - Positive values indicate northern latitude
 *             - Negative values indicate southern latitude
 *             - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  \param  pLongitude
 *             - Longitude (specified in WGS84 datum)
 *             - Type - Floating point
 *             - Units - Degrees
 *             - Range - -180.0 to 180.0
 *             - Positive values indicate eastern latitude
 *             - Negative values indicate western latitude
 *             - Bit to check in ParamPresenceMask - <B>0x12</B>
 *
 *   \param  pHorUncCircular
 *             - Horizontal position uncertainty.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x13</B>
 *
 *   \param  pAltitudeWrtEllipsoid
 *             - Altitude With Respect to WGS84 Ellipsoid.
 *             - Units - Meters
 *             - Range -500 to 15883
 *             - Bit to check in ParamPresenceMask - <B>0x14</B>
 *
 *   \param  pVertUnc
 *             - Vertical uncertainty.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x15</B>
 *
 *   \param  pTimestampUtc
 *             - UTC timestamp
 *             - Units - Milliseconds since Jan. 1, 1970
 *             - Bit to check in ParamPresenceMask - <B>0x16</B>
 *
 *   \param  pTimeUnc
 *             - Time uncertainty.
 *             - Units - Milliseconds
 *             - Bit to check in ParamPresenceMask - <B>0x17</B>
 *
 *   \param  pHorUncEllipseSemiMinor
 *             - Semi-minor axis of horizontal elliptical uncertainty.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x18</B>
 *
 *   \param  pHorUncEllipseSemiMajor
 *             - Semi-major axis of horizontal elliptical uncertainty.
 *             - Units: Meters
 *             - Bit to check in ParamPresenceMask - <B>0x19</B>
 *
 *   \param  pHorUncEllipseOrientAzimuth
 *             - Elliptical horizontal uncertainty azimuth of orientation.
 *             - Units - Decimal degrees
 *             - Range - 0 to 180
 *             - Bit to check in ParamPresenceMask - <B>0x1A</B>
 *
 *   \param  pHorCirConf
 *           - Horizontal circular uncertainty confidence
 *           - Units: Precent
 *           - Range: 0 to 99
 *           - Bit to check in ParamPresenceMask - <B>0x1B</B>
 *
 *   \param  pHorEllpConf
 *           - Horizontal elliptical uncertainty confidence
 *           - Units: Precent
 *           - Range: 0 to 99
 *           - Bit to check in ParamPresenceMask - <B>0x1C</B>
 *
 *   \param  pHorReliability
 *          - Values
 *            - 0 - Location reliability is not set.
 *            - 1 - Location reliability is very low; use it at
 *                  your own risk
 *            - 2 - Location reliability is low; little or no
 *                  cross-checking is possible.
 *            - 3 - Location reliability is medium; limited cross-check passed
 *            - 4 - Location reliability is high; strong cross-check passed
 *          - Bit to check in ParamPresenceMask - <B>0x1D</B>
 *
 *   \param  pSpeedHorizontal
 *             - Horizontal speed.
 *             - Units - Meters/second
 *             - Bit to check in ParamPresenceMask - <B>0x1E</B>
 *
 *   \param  pSpeedUnc
 *             - 3-D Speed uncertainty.
 *             - Units - Meters/second.
 *             - Bit to check in ParamPresenceMask - <B>0x1F</B>
 *
 *   \param  pAltitudeWrtMeanSeaLevel
 *             - Altitude With Respect to Sea Level.
 *             - Units - Meters
 *             - Bit to check in ParamPresenceMask - <B>0x20</B>
 *
 *   \param  pVertConfidence
 *             - Vertical uncertainty confidence.
 *             - Units - Percentage
 *             - Range 0 to 99
 *             - Bit to check in ParamPresenceMask - <B>0x21</B>
 *
 *   \param  pVertReliability
 *          - Values
 *             - 0 - Location reliability is not set.
 *             - 1 - Location reliability is very low;
 *                   use it at your own risk.
 *             - 2 - Location reliability is low; little or no
 *                   cross-checking is possible
 *             - 3 - Location reliability is medium; limited
 *                   cross-check passed
 *             - 4 - Location reliability is high; strong
 *                   cross-check passed
 *          - Bit to check in ParamPresenceMask - <B>0x22</B>
 *
 *   \param  pSpeedVertical
 *             - Vertical speed.
 *             - Units - Meters/second
 *             - Bit to check in ParamPresenceMask - <B>0x23</B>
 *
 *   \param  pSpeedVerticalUnc
 *           - Veritical speed
 *           - Units: Meters/second
 *           - Bit to check in ParamPresenceMask - <B>0x24</B>
 *
 *   \param  pHeading
 *             - Heading.
 *             - Units - Degree
 *             - Range 0 to 359.999
 *             - Bit to check in ParamPresenceMask - <B>0x25</B>
 *
 *   \param  pHeadingUnc
 *             - Heading uncertainty.
 *             - Units - Degree
 *             - Range 0 to 359.999
 *             - Bit to check in ParamPresenceMask - <B>0x26</B>
 *
 *   \param  pMagneticDeviation
 *             - Difference between the bearing to true north and the
 *               bearing shown on a magnetic compass. The deviation is
 *               positive when the magnetic north is east of true north.
 *             - Bit to check in ParamPresenceMask - <B>0x27</B>
 *
 *   \param  pTechnologyMask
 *          - Values
 *             - 0x00000001 - Satellites were used to generate the fix
 *             - 0x00000002 - Cell towers were used to generate the fix
 *             - 0x00000004 - Wi-Fi access points were used to generate the fix
 *             - 0x00000008 - Sensors were used to generate the fix
 *             - 0x00000010 - Reference Location was used to generate the fix
 *             - 0x00000020 - Coarse position injected into the location engine
 *                            was used to generate the fix
 *             - 0x00000040 - AFLT was used to generate the fix
 *             - 0x00000080 - GNSS and network-provided measurements were
 *                            used to generate the fix
 *          - Bit to check in ParamPresenceMask - <B>0x28</B>
 *
 *  \param  -pPrecisionDilution
 *             - See \ref loc_precisionDilution for more information
 *             - Bit to check in ParamPresenceMask - <B>0x29</B>
 *
 *  \param  -pGpsTime
 *             - See \ref loc_gpsTime for more information
 *             - Bit to check in ParamPresenceMask - <B>0x2A</B>
 *
 *  \param  pTimeSrc
 *          - Values
 *             - 0 - Invalid time.
 *             - 1 - Time is set by the 1X system.
 *             - 2 - Time is set by WCDMA/GSM time tagging.
 *             - 3 - Time is set by an external injection.
 *             - 4 - Time is set after decoding over-the-air GPS navigation
 *                   data from one GPS satellite.
 *             - 5 - Time is set after decoding over-the-air GPS navigation
 *                   data from multiple satellites.
 *             - 6 - Both time of the week and the GPS week number
 *                   are known.
 *             - 7 - Time is set by the position engine after the
 *                   fix is obtained
 *             - 8 - Time is set by the position engine after performing SFT,
 *                   this is done when the clock time uncertainty is large.
 *             - 9 - Time is set after decoding GLO satellites.
 *             - 10- Time is set after transforming the GPS to GLO time
 *             - 11- Time is set by the sleep time tag provided by
 *                   the WCDMA network.
 *             - 12- Time is set by the sleep time tag provided by the
 *                   GSM network
 *             - 13- Source of the time is unknown
 *             - 14- Time is derived from the system clock (better known
 *                   as the slow clock); GNSS time is maintained
 *                   irrespective of the GNSS receiver state
 *             - 15- Time is set after decoding QZSS satellites.
 *             - 16- Time is set after decoding BDS satellites.
 *          - Bit to check in ParamPresenceMask - <B>0x2B</B>
 *
 *  \param  -pSensorDataUsage
 *             - See \ref loc_sensorDataUsage for more information
 *             - Bit to check in ParamPresenceMask - <B>0x2C</B>
 *
 *  \param  -pSvUsedforFix
 *             - See \ref loc_svUsedforFix for more information
 *             - Bit to check in ParamPresenceMask - <B>0x2D</B>
 * 
 *	\param pExtendedPrecisionDilution
 *			- Extended Dilution of Precision Dilution of precision associated with this position.
 *          - See \ref  loc_extendedPrecisionDilution
 *          - Bit to check in ParamPresenceMask - <B>0x2E</B>
 *
 *	\param pSpoofReportMask
 *			- Spoof report 
 *				- Valid bitmasks:
 *				- QMI_LOC_POSITION_SPOOFED (0x00000001) – Set bit indicates suspected spooﬁng in position
 *				- QMI_LOC_TIME_SPOOFED (0x00000002) – Set bit indicates suspected spooﬁng in time
 *				- QMI_LOC_NAVIGATION_DATA_ SPOOFED (0x00000004) – Set bit indicates suspected spooﬁng in navigation data
 *          - Bit to check in ParamPresenceMask - <B>0x2F</B>
 * 
 *	\param pExpandedSVs
 *			- Expanded SVs Used to Calculate the Fix.
 *          - See \ref  loc_expandedSVs
 *          - Bit to check in ParamPresenceMask - <B>0x30</B>
 * 
 *  \param pSatelliteSignalTypes
 *          - Satellite Signal Types in the SVs Used List
 *          - See \ref  loc_satelliteSignalTypes
 *          - Bit to check in ParamPresenceMask - <B>0x31</B>
 * 
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */

typedef struct{
    uint32_t                    status;
    uint32_t                    *pXid;
    double                      *pLatitude;
    double                      *pLongitude;
    float                       *pHorUncCircular;
    float                       *pAltitudeWrtEllipsoid;
    float                       *pVertUnc;
    uint64_t                    *pTimestampUtc;
    float                       *pTimeUnc;
    float                       *pHorUncEllipseSemiMinor;
    float                       *pHorUncEllipseSemiMajor;
    float                       *pHorUncEllipseOrientAzimuth;
    uint8_t                     *pHorCirConf;
    uint8_t                     *pHorEllpConf;
    uint32_t                    *pHorReliability;
    float                       *pSpeedHorizontal;
    float                       *pSpeedUnc;
    float                       *pAltitudeWrtMeanSeaLevel;
    uint8_t                     *pVertConfidence;
    uint32_t                    *pVertReliability;
    float                       *pSpeedVertical;
    float                       *pSpeedVerticalUnc;
    float                       *pHeading;
    float                       *pHeadingUnc;
    float                       *pMagneticDeviation;
    uint32_t                    *pTechnologyMask;
    loc_precisionDilution       *pPrecisionDilution;
    loc_gpsTime                 *pGpsTime;
    uint32_t                    *pTimeSrc;
    loc_sensorDataUsage         *pSensorDataUsage;
    loc_svUsedforFix            *pSvUsedforFix;
    loc_extendedPrecisionDilution *pExtendedPrecisionDilution;
    uint64_t                    *pSpoofReportMask;
    loc_expandedSVs             *pExpandedSVs;
    loc_satelliteSignalTypes    *pSatelliteSignalTypes;
    uint16_t                    Tlvresult;
    swi_uint256_t               ParamPresenceMask;
}unpack_loc_BestAvailPos_Ind_t;

/**
 * \ingroup loc
 * 
 * Loc Best Avial position Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_BestAvailPos_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_BestAvailPos_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Set External Power Configure status field.
 *
 *  @param  status
 *           - Status of the Set Operation Mode request.
 *           - Valid values:
 *             - 0 - Request was completed successfully
 *             - 1 - Request failed because of a general failure
 *             - 2 - Request failed because it is not supported
 *             - 3 - Request failed because it contained invalid parameters
 *             - 4 - Request failed because the engine is busy
 *             - 5 - Request failed because the phone is offline
 *             - 6 - Request failed because it timed out
 *             - 7 - Request failed because an undefined configuration was requested
 *             - 8 - Request failed because the engine could not allocate sufficient memory for the request
 *             - 9 - Request failed because the maximum number of Geofences are already programmed
 *             - 10 - Location service failed because of an XTRA version-based file format check failure
 *           - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t status;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_SetOperationMode_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the specified operation mode.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetOperationMode_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetOperationMode_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters passed for SetLocDeleteAssistDataCallback by
 *  the device.
 *
 *  @param  status
 *          - Status of the Delete Assist Data request
 *          - Valid values:
 *             - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *             - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of
 *               a general failure
 *             - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is
 *               not supported
 *             - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because
 *               it contained invalid parameters
 *             - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine
 *               is busy
 *             - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone
 *               is offline
 *             - eQMI_LOC_TIMEOUT (6) - Request failed because it timed out
 *             - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because
 *               an undefined configuration was requested
 *             - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because
 *               the engine could not allocate sufficient memory for the request
 *             - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because
 *               the maximum number of Geofences are already programmed
 *             - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service
 *               failed because of an XTRA version-based file format check failure
 *             - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t status;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_DeleteAssistData_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the status of delete the location engine assistance data
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_DeleteAssistData_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_DeleteAssistData_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain fields in struct loc_satelliteInfo
 *
 *  @param  validMask
 *          - Bitmask indicating which of the fields in this TLV are valid. Valid bitmasks:
 *              - QMI_LOC_SV_INFO_MASK_VALID_SYSTEM (0x00000001) - System field is valid in SV information
 *              - QMI_LOC_SV_INFO_MASK_VALID_GNSS_SVID (0x00000002) - gnssSvId field is valid in SV information
 *              - QMI_LOC_SV_INFO_MASK_VALID_HEALTH_STATUS (0x00000004) - healthStatus field is valid in SV information
 *              - QMI_LOC_SV_INFO_MASK_VALID_PROCESS_STATUS (0x00000008) - processStatus field is valid in SV information
 *              - QMI_LOC_SV_INFO_MASK_VALID_SVINFO_MASK (0x00000010) - svInfoMask field is valid in SV information
 *              - QMI_LOC_SV_INFO_MASK_VALID_ELEVATION (0x00000020) - Elevation field is valid in SV information
 *              - QMI_LOC_SV_INFO_MASK_VALID_AZIMUTH (0x00000040) - Azimuth field is valid in SV information
 *              - QMI_LOC_SV_INFO_MASK_VALID_SNR (0x00000080) - SNR field is valid in SV information
 *
 *  @param  system
 *          - Indicates to which constellation this SV belongs. Valid values:
 *              - eQMI_LOC_SV_SYSTEM_GPS (1) - GPS satellite
 *              - eQMI_LOC_SV_SYSTEM_GALILEO (2) - GALILEO satellite
 *              - eQMI_LOC_SV_SYSTEM_SBAS (3) - SBAS satellite
 *              - eQMI_LOC_SV_SYSTEM_COMPASS (4) - COMPASS satellite
 *              - eQMI_LOC_SV_SYSTEM_GLONASS (5) - GLONASS satellite
 *              - eQMI_LOC_SV_SYSTEM_BDS (6) - BDS satellite
 *              - eQMI_LOC_SV_SYSTEM_QZSS (7) - QZSS satellite
 *              - eQMI_LOC_SV_SYSTEM_NAVIC (8) - NavIC satellite
 * 
 *  @param  gnssSvId
 *          - GNSS SV ID. The GPS and GLONASS SVs can be disambiguated using the system field.
 *            Range:
 *              - FOR GPS: 1 to 32
 *              - FOR GLONASS: 1 to 32
 *              - FOR SBAS: 120 to 151
 *              - for BDS: 201 to 237
 *              - For QZSS: 193 to 197
 *              - For BDS: 201 to 237
 *              - For Galileo: 301 to 336
 *              - For NavIC: 401 to 414
 * 
 *  @param  healthStatus
 *          - health status. Range: 0 - 1
 *              - 0 - unhealthy
 *              - 1 - healthy
 *
 *  @param  svStatus
 *          - SV process status. Valid values:
 *              - eQMI_LOC_SV_STATUS_IDLE (1) - SV is not being actively processed
 *              - eQMI_LOC_SV_STATUS_SEARCH (2) - The system is searching for this SV
 *              - eQMI_LOC_SV_STATUS_TRACK (3) - SV is being tracked
 *
 *  @param  svInfoMask
 *          - Indicates whether almanac and ephemeris information is available.
 *            Valid bitmasks:
 *              - 0x01 - SVINFO_HAS_EPHEMERIS
 *              - 0x02 - SVINFO_HAS_ALMANAC
 *
 *  @param  elevation
 *          - SV elevation angle.
 *              - Units: Degrees
 *              - Range: 0 to 90
 *
 *  @param  azimuth
 *          - SV azimuth angle.
 *              - Units: Degrees
 *              - Range: 0 to 360
 *
 *  @param  snr
 *           - SV signal-to-noise ratio
 *               - Units: dB-Hz
 *
 */
typedef struct
{
    uint32_t  validMask;
    uint32_t  system;
    uint16_t  gnssSvId;
    uint8_t   healthStatus;
    uint32_t  svStatus;
    uint8_t   svInfoMask;
    float     elevation;
    float     azimuth;
    float     snr;
} loc_satelliteInfo;

/**
 * \ingroup loc
 * 
 *  Contain fields in struct loc_satelliteInfo
 *
 *  @param  svListLen
 *          - number of sets of the loc_satelliteInfo
 * 
 *  @param  pLoc_satelliteInfo
 *          - satellite information 
 *          - see \ref loc_satelliteInfo 
 *          
 */
typedef struct
{
    uint8_t   svListLen;
    loc_satelliteInfo *pLoc_satelliteInfo;

} loc_satelliteInfoList;

/**
 * \ingroup loc
 * 
 *  Contain fields in struct loc_satelliteInfo
 *
 *  @param  satelliteInfo
 *           - See \ref loc_satelliteInfo
 *
 *  @param  gloFrequency
 *           - GLONASS frequency number + 8.
 *           - Valid only for GLONASS systems and must be ignored for all other systems.
 *           - Range: 1 to 14
 */
typedef struct
{
    loc_satelliteInfo satelliteInfo;
    uint8_t     gloFrequency;
} loc_expandedSatelliteInfo;

/**
 * \ingroup loc
 * 
 *  Contain fields in Expanded Satellite Information
 *  Expanded SV information list. If the service reports expandedSvList, svList is not reported.
 *
 *  @param  expandedSvList_len
 *          - number of sets of the loc_expandedSatelliteInfo instances
 * 
 *  @param  pLoc_satelliteInfo
 *          - satellite information 
 *          - see \ref loc_satelliteInfo 
 *          
 */
typedef struct
{
    uint8_t   expandedSvList_len;
    loc_expandedSatelliteInfo *pLoc_expandedSatelliteInfo;

} loc_expandedSatelliteInformation;

enum QMI_LOC_MASK_GNSS_SIGNAL_TYPE 
{
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1CA      = 0x00000001,    // GPS L1CA RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1C       = 0x00000002,     // GPS L1C RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L2C_L     = 0x00000004,    // GPS L2C_L RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L5_Q      = 0x00000008,    // GPS L5_Q RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G1    = 0x00000010,    // GLONASS G1 (L1OF) RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G2    = 0x00000020,    // GLONASS G2 (L2OF) RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E1_C  = 0x00000040,    // Galileo E1_C RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5A_Q = 0x00000080,    // Galileo E5A_Q RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5B_Q = 0x00000100,    // Galileo E5B_Q RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1_I   = 0x00000200,    // BeiDou B1_I RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1C    = 0x00000400,    // BeiDou B1C RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2_I   = 0x00000800,    // BeiDou B2_I RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_I  = 0x00001000,    // BeiDou B2A_I RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1CA     = 0x00002000,    // QZSS L1CA RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1S      = 0x00004000,    // QZSS L1S RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L2C_L    = 0x00008000,    // QZSS L2C_L RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L5_Q     = 0x00010000,    // QZSS L5_Q RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_SBAS_L1_CA    = 0x00020000,    // SBAS L1_CA RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_NAVIC_L5      = 0x00040000,    // NavIC L5 RF band
    QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_Q  = 0x00080000    // BeiDou B2A_Q RF band
};

/**
 * \ingroup loc
 * 
 *  Contain fields in Satellite Signal Type
 *
 *  @param  gnssSignalTypeList_len
 *          - Number of sets of the following gnssSignalTypeList
 * 
 *  @param  gnssSignalTypeList
 *          - Indicates the signal type of each satellite in expandedGnssSvUsedList.
 *          - The signal type list is aligned with the SVs in 
 *          - Value of 0 means invalid.
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1CA (0x00000001) - GPS L1CA RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1C (0x00000002) - GPS L1C RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L2C_L (0x00000004) - GPS L2C_L RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L5_Q (0x00000008) - GPS L5_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G1 (0x00000010) - GLONASS G1 (L1OF) RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G2 (0x00000020) - GLONASS G2 (L2OF) RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E1_C (0x00000040) - Galileo E1_C RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5A_Q (0x00000080) - Galileo E5A_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5B_Q (0x00000100) - Galileo E5B_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1_I (0x00000200) - BeiDou B1_I RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1C (0x00000400) - BeiDou B1C RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2_I (0x00000800) - BeiDou B2_I RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_I (0x00001000) - BeiDou B2A_I RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1CA (0x00002000) - QZSS L1CA RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1S (0x00004000) - QZSS L1S RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L2C_L (0x00008000) - QZSS L2C_L RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L5_Q (0x00010000) - QZSS L5_Q RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_SBAS_L1_CA (0x00020000) - SBAS L1_CA RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_NAVIC_L5 (0x00040000) - NavIC L5 RF band
 *              - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_Q (0x00080000) - BeiDou B2A_Q RF band
 */
typedef struct
{
    uint8_t   gnssSignalTypeList_len;
    uint64_t  gnssSignalTypeList[MAX_GNSS_SINGNAL_TYPES];
} loc_satelliteSignalType;

/**
 * \ingroup loc
 * 
 *  Contain the parameters passed for SetLocGnssSvInfoCallback by
 *  the device.
 *
 *  @param  altitudeAssumed
 *          - Indicates whether altitude is assumed or calculated
 *              - 0x00 (FALSE) - Valid altitude is calculated
 *              - 0x01 (TRUE) - Valid altitude is assumed; there may not be enough
 *                satellites to determine precise altitude
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  @param  pSatelliteInfoList
 *          - See @ref loc_satelliteInfoList for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  pExpandedSatelliteInfoList
 *          - See @ref loc_expandedSatelliteInformation for more information.
 *          - If the service reports Expanded Satellite Information, Satellite Information is not reported.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  @param  pSatelliteSignalType
 *          - See @ref loc_satelliteSignalType for more information.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint8_t           altitudeAssumed;
    loc_satelliteInfoList *pSatelliteInfoList;
    loc_expandedSatelliteInformation *pExpandedSatelliteInfoList;
    loc_satelliteSignalType *pSatelliteSignalType;
    uint16_t          Tlvresult;
    swi_uint256_t     ParamPresenceMask;
} unpack_loc_GnssSvInfo_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the GNSS SV Info Indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GnssSvInfo_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GnssSvInfo_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains inject UTC time parameter.
 *  \param  timeMsec
 *          - The UTC time since Jan. 1, 1970
 *
 *  \param  timeUncMsec
 *           - The time Uncertainty
 */
typedef struct{
    uint64_t timeMsec;
    uint32_t timeUncMsec;
}pack_loc_SLQSLOCInjectUTCTime_t;

typedef unpack_result_t unpack_loc_SLQSLOCInjectUTCTime_t;

/**
 * \ingroup loc
 * 
 * Pack inject UTC time.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SLQSLOCInjectUTCTime(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SLQSLOCInjectUTCTime_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack inject UTC time.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SLQSLOCInjectUTCTime(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SLQSLOCInjectUTCTime_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure specifies information regarding the altitude source
 *
 * \param source
 *        - Specifies the source of the altitude
 *        - Valid values
 *           - 0 - Source is unknown
 *           - 1 - GPS is the source
 *           - 2 - Cell ID provided the source
 *           - 3 - Source is enhanced cell ID
 *           - 4 - Wi-Fi is the source
 *           - 5 - Terrestrial source
 *           - 6 - Hybrid terrestrial source
 *           - 7 - Altitude database is the source
 *           - 8 - Barometric altimeter is the source
 *           - 9 - Other sources
 *
 * \param linkage
 *        - Specifies the dependency between the horizontal
 *          and altitude position components
 *        - Valid values
 *           - 0 - Not specified
 *           - 1 - Fully interdependent
 *           - 2 - Depends on latitude and longitude
 *           - 3 - Fully independent
 *
 * \param coverage
 *        - Specifies the region of uncertainty.
 *        - Valid values
 *           - 0 - Not specified
 *           - 1 - Altitude uncertainty is valid at the injected
 *                 horizontal position coordinates only
 *           - 2 - Altitude uncertainty applies to the position
 *                 of the device regardless of horizontal position
 *
*/
typedef struct{
    uint32_t    source;
    uint32_t    linkage;
    uint32_t    coverage;
}altSrcInfo_t;

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Inject Position parameters
 *  Please check has_<Param_Name> field for presence of optional parameters
 *
 *  \param  latitude
 *             - Optional parameter
 *             - Type - Floating point
 *             - Units - Degrees
 *             - Range - -90.0 to 90.0
 *             - Positive values indicate northern latitude
 *             - Negative values indicate southern latitude
 *
 *             - Note - This field must be specified together with
 *                        pLongitude and pHorUncCircular.
 *
 *  \param  longitude
 *             - Optional parameter
 *             - Type - Floating point
 *             - Units - Degrees
 *             - Range - -180.0 to 180.0
 *             - Positive values indicate eastern latitude
 *             - Negative values indicate western latitude
 *
 *             - Note - This field must be specified together with
 *                        pLatitude and pHorUncCircular.
 *
 *   \param  horUncCircular
 *             - Optional parameter
 *             - Horizontal position uncertainty.
 *             - Units - Meters
 *
 *             - Note - This field must be specified together with
 *                        pLatitude and pLongitude.
 *
 *   \param  horConfidence
 *             - Optional parameter
 *             - Horizontal confidence.
 *             - Units - Percent
 *             - Values
 *               - Valid Values - 1 to 99
 *               - Invalid Values - 0, 101 to 255
 *               - If 100 is received, reinterpret to 99
 *
 *             - Note - This field must be specified together with
 *                      horizontal uncertainty. If not specified
 *                      when pHorUncCircular is set, the default
 *                      value is 50.
 *
 *   \param  horReliability
 *             - Optional parameter
 *               - Values
 *                 - 0 - Location reliability is not set.
 *                 - 1 - Location reliability is very low; use it at
 *                       your own risk
 *                 - 2 - Location reliability is low; little or no
 *                       cross-checking is possible.
 *                 - 3 - Location reliability is medium; limited cross-check passed
 *                 - 4 - Location reliability is high; strong cross-check passed
 *
 *   \param  altitudeWrtEllipsoid
 *             - Optional parameter
 *             - Altitude With Respect to Ellipsoid.
 *             - Units - Meters
 *             - Values
 *               - Positive - height
 *               - Negative = depth
 *
 *   \param  altitudeWrtMeanSeaLevel
 *             - Optional parameter
 *             - Altitude With Respect to Sea Level.
 *             - Units - Meters
 *
 *   \param  vertUnc
 *             - Optional parameter
 *             - Vertical uncertainty.
 *             - Units - Meters
 *
 *             - Note - This is mandatory if either pAltitudeWrtEllipsoid
 *                      or pAltitudeWrtMeanSeaLevel is specified.
 *
 *   \param  vertConfidence
 *             - Optional parameter
 *             - Vertical confidence.
 *             - Units - Percentage
 *             - Values
 *               - Valid Values - 0 to 99
 *               - Invalid Values - 0, 100-256
 *               - If 100 is received, reinterpret to 99
 *
 *             - Note - This field must be specified together with
 *                      the vertical uncertainty. If not specified,
 *                      the default value will be 50.
 *
 *   \param  vertReliability
 *             - Optional parameter
 *               - Values
 *                  - 0 - Location reliability is not set.
 *                  - 1 - Location reliability is very low;
 *                        use it at your own risk.
 *                  - 2 - Location reliability is low; little or no
 *                        cross-checking is possible
 *                  - 3 - Location reliability is medium; limited
 *                        cross-check passed
 *                  - 4 - Location reliability is high; strong
 *                        cross-check passed
 *
 *   \param  altitudeSrcInfo
 *             - Optional parameter
 *               - Pointer to struct altitudeSrcInfo. See \ref altitudeSrcInfo for more information
 *
 *   \param  timestampUtc
 *             - Optional parameter
 *             - UTC timestamp
 *             - Units - Milliseconds since Jan. 1, 1970
 *
 *   \param  timestampAge
 *             - Optional parameter
 *             - Position age, which is an estimate of how long ago
 *               this fix was made.
 *             - Units - Milliseconds
 *
 *   \param  positionSrc
 *             - Optional parameter
 *             - Source from which this position was obtained
 *             - Valid values
 *               - 0 - Position source is GNSS
 *               - 1 - Position source is Cell ID
 *               - 2 - Position source is Enhanced Cell ID
 *               - 3 - Position source is Wi-Fi
 *               - 4 - Position source is Terrestrial
 *               - 5 - Position source is GNSS Terrestrial Hybrid
 *               - 6 - Other sources
 *
 *             - Note - If altitude is specified and the altitude
 *                      source is not specified, the engine assumes
 *                      that the altitude was obtained using the
 *                      specified position source.
 *                    - If both altitude and altitude source are
 *                      specified, the engine assumes that only
 *                      latitude and longitude were obtained using
 *                      the specified position source.
 *
 *   \param  rawHorUncCircular
 *             - Optional parameter
 *             - Horizontal position uncertainty (circular) without
 *               any optimization.
 *             - Units - Meters
 *
 *   \param  rawHorConfidence
 *             - Optional parameter
 *             - Horizontal confidence associated with raw horizontal
 *               uncertainty
 *             - Units: Percent
 *             - Values
 *               - Valid values - 1 to 99
 *               - Invalid values - 0, 101 to 255
 *               - If 100 is received, reinterpret to 99
 *
 *             - Note - This field must be specified together with
 *                      raw horizontal uncertainty. If not specified
 *                      when rawHorUncCircular is set, the default value is 50.
 */
typedef struct{
    double          latitude;
    int             has_latitude;
    double          longitude;
    int             has_longitude;
    float           horUncCircular;
    int             has_horUncCircular;
    uint8_t         horConfidence;
    int             has_horConfidence;
    uint32_t        horReliability;
    int             has_horReliability;
    float           altitudeWrtEllipsoid;
    int             has_altitudeWrtEllipsoid;
    float           altitudeWrtMeanSeaLevel;
    int             has_altitudeWrtMeanSeaLevel;
    float           vertUnc;
    int             has_vertUnc;
    uint8_t         vertConfidence;
    int             has_vertConfidence;
    uint32_t        vertReliability;
    int             has_vertRelicability;
    altSrcInfo_t    altitudeSrcInfo;
    int             has_altitudeSrcInfo;
    uint64_t        timestampUtc;
    int             has_timestampUtc;
    uint32_t        timestampAge;
    int             has_timestampAge;
    uint32_t        positionSrc;
    int             has_positionSrc;
    float           rawHorUncCircular;
    int             has_rawHorUncCircular;
    uint8_t         rawHorConfidence;
    int             has_rawHorConfidence;
}pack_loc_SLQSLOCInjectPosition_t;

typedef unpack_result_t  unpack_loc_SLQSLOCInjectPosition_t;
/**
 * \ingroup loc
 * 
 * Pack inject position.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SLQSLOCInjectPosition(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SLQSLOCInjectPosition_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack inject position.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SLQSLOCInjectPosition(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SLQSLOCInjectPosition_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains parameters to set current cradle mount configuration
 *  Please check has_<Param_Name> field for presence of optional parameters
 *
 *  \param  state
 *             - Cradle Mount State
 *             - Valid values:
 *               - 0 - Device is mounted on the cradle
 *               - 1 - Device is not mounted on the cradle
 *               - 2 - Unknown cradle mount state
 *
 *  \param  confidence
 *             - Cradle Mount Confidence (Optional)
 *             - Confidence in the Cradle Mount state expressed as a
 *               percentage.
 *             - Range - 0 to 100
 */
typedef struct{
    uint32_t    state;
    int         has_confidence;
    uint8_t     confidence;
}pack_loc_SLQSLOCSetCradleMountConfig_t;

typedef unpack_result_t  unpack_loc_SLQSLOCSetCradleMountConfig_t;

/**
 * \ingroup loc
 * 
 * Pack set cradle mount configure.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SLQSLOCSetCradleMountConfig(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SLQSLOCSetCradleMountConfig_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack set cradle mount configure.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SLQSLOCSetCradleMountConfig(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SLQSLOCSetCradleMountConfig_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure specifies information regarding the 3-Axis Sensor Data.
 * Please check has_<Param_Name> field for presence of optional parameters
 *
 * \param timeOfFirstSample
 *        - Denotes a full 32-bit time stamp of the first (oldest) sample in this message.
 *        - The time stamp is in the time reference scale that is used by the sensor time source.
 *        - Units - Milliseconds
 *
 * \param flags
 *        - Flags to indicate any deviation from the default measurement assumptions.
 *        - All unused bits in this field must be set to 0.
 *        - Valid bitmasks
 *           - 0x01 - Bitmask to specify that a sign reversal is required
 *                    while interpreting the sensor data; only applies to the
 *                    accelerometer samples
 *           - 0x02 - Bitmask to specify that the sensor time stamp is the same
 *                    as the modem time stamp
 *
 * \param sensorDataLen
 *        - Number of sets of the following elements
 *          - timeOffset
 *          - xAxis
 *          - yAxis
 *          - zAxis
 *
 * \param timeOffset
 *        - Sample time offset
 *        - Units - Milliseconds
 *
 * \param xAxis
 *        - Sensor x-axis sample.
 *        - Units Accelerometer - Meters/seconds square
 *        - Units Gyroscope - Radians/second
 *
 * \param yAxis
 *        - Sensor Y-axis sample.
 *        - Units Accelerometer - Meters/seconds square
 *        - Units Gyroscope - Radians/second
 *
 * \param xAxis
 *        - Sensor Z-axis sample.
 *        - Units Accelerometer - Meters/seconds square
 *        - Units Gyroscope - Radians/second
 */
typedef struct
{
    uint32_t    timeOfFirstSample ;
    uint8_t     flags;
    uint8_t     sensorDataLen;
    uint16_t    timeOffset[MAX_SENSOR_DATA_LEN];
    uint32_t    xAxis[MAX_SENSOR_DATA_LEN];
    uint32_t    yAxis[MAX_SENSOR_DATA_LEN];
    uint32_t    zAxis[MAX_SENSOR_DATA_LEN];
}sensorData_t;

/**
 * \ingroup loc
 * 
 * This structure specifies information regarding the Temperature Data.
 * Please check has_<Param_Name> field for presence of optional parameters
 *
 * \param timeSource
 *        - Time source of the sensor data
 *        - Valid values
 *          - 0 - Sensor time source is unspecified
 *          - 1 - Time source is common between the sensors and
 *                the location engine
 *
 * \param timeOfFirstSample
 *        - Denotes a full 32-bit time stamp of the first (oldest) sample in this message.
 *        - The time stamp is in the time reference scale that is used by the sensor time source.
 *        - Units - Milliseconds
 *
 * \param temperatureDataLen
 *        - Number of sets of the following elements
 *          - timeOffset
 *          - temperature
 *
 * \param timeOffset
 *        - Sample time offset
 *        - Units - Milliseconds
 *
 * \param temperature
 *        - Sensor temperature.
 *        - Type - Floating point
 *        - Units - Degrees Celsius
 *        - Range -50 to +100.00
 */
typedef struct
{
    uint32_t    timeSource;
    uint32_t    timeOfFirstSample;
    uint8_t     temperatureDataLen;
    uint16_t    timeOffset[MAX_TEMP_DATA_LEN];
    uint32_t    temperature[MAX_TEMP_DATA_LEN];
}tempData_t;

/**
 * \ingroup loc
 * 
 *  This structure contains parameters to inject sensor data into the GNSS location engine
 *  Please check has_<Param_Name> field for presence of optional parameters
 *
 *  \param  opaqueId
 *             - Opaque Identifier (Optional parameter)
 *             - An opaque identifier that is sent in by the client that
 *               will be echoed in the indication so the client can relate
 *               the indication to the request.
 *
 *   \param  acceleroData
 *             - 3-Axis Accelerometer Data (Optional parameter)
 *             - Pointer to struct sensorData. See \ref sensorData_t for more information
 *
 *   \param  gyroData
 *             - 3-Axis Cyroscope Data (Optional parameter)
 *             - Pointer to struct sensorData. See \ref sensorData_t for more information
 *
 *  \param  acceleroTimeSrc
 *             - 3-Axis Accelerometer Data Time Source (Optional parameter)
 *             - The location service uses this field to identify the time reference
 *               used in the accelerometer data time stamps.
 *             - If not specified, the location service assumes that the time source
 *               for the accelerometer data is unknown.
 *             - Valid values
 *                - 0 - Sensor time source is unspecified
 *                - 1 - Time source is common between the sensors and
 *                      the location engine
 *
 *  \param  gyroTimeSrc
 *             - 3-Axis Gyroscope Data Time Source (Optional)
 *             - The location service uses this field to identify the time reference
 *               used in the gyroscope data time stamps.
 *             - If not specified, the location service assumes that the time source
 *               for the gyroscope data is unknown.
 *             - Valid values
 *                - 0 - Sensor time source is unspecified
 *                - 1 - Time source is common between the sensors and
 *                      the location engine
 *
 *   \param  accelTemp
 *             - Accelerometer Temperature Data (Optional parameter)
 *             - Pointer to struct tempratureData. See \ref tempData_t for more information
 *
 *   \param  gyroTemp
 *             - Gyroscope Temperature Data (Optional parameter)
 *             - Pointer to struct tempratureData. See \ref tempData_t for more information
 *
 */
typedef struct{
    int             has_opaqueId;
    uint32_t        opaqueId;
    int             has_accleroData;
    sensorData_t    acceleroData;
    int             has_gyroData;
    sensorData_t    gyroData;
    int             has_acceleroTimeSrc;
    uint32_t        acceleroTimeSrc;
    int             has_gyroTimeSrc;
    uint32_t        gyroTimeSrc;
    int             has_accelTemp;
    tempData_t      accelTemp;
    int             has_gyroTemp;
    tempData_t      gyroTemp;
}pack_loc_SLQSLOCInjectSensorData_t;

typedef unpack_result_t  unpack_loc_SLQSLOCInjectSensorData_t;

/**
 * \ingroup loc
 * 
 * Pack inject sensor data.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SLQSLOCInjectSensorData(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SLQSLOCInjectSensorData_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack inject sensor data.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SLQSLOCInjectSensorData(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SLQSLOCInjectSensorData_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters passed for SetLocEventMaskNMEACallback by
 *  the device.
 *
 *  @param  NMEAData
 *          - NMEA string
 *          - Type - NULL terminated string
 *          - Maximum string length (including NULL terminator) - 201
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *  @param  ExpandedNmea_len [IN][OUT]
 *          - Expanded NMEA buffer size
 *          - [IN]: input buffer size
 *          - [OUT]: Expanded NMEA string characters count including NULL terminator
 *  @param  pExpandedNmea
 *          - Expanded NMEA string. If the service reports ExpandedNmea, the mandatory NMEA string is empty.
 *          - Type: NULL-terminated string
 *          - Expanded maximum string length (including NULL terminator): 4096
 * 
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    char              NMEAData[MAX_LOC_NMEA_STR_LEN];
    uint32_t          ExpandedNmea_len;
    char              *pExpandedNmea;
    uint16_t          Tlvresult;
    swi_uint256_t     ParamPresenceMask;
} unpack_loc_EventNMEA_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the NMEA Event Indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_EventNMEA_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_EventNMEA_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains parameters to Gets the location server.
 *  Please check has_<Param_Name> field for presence of optional parameters
 *
 *  \param  serverType
 *             - Type of server.
 *             - Valid values
 *               - eQMI_LOC_SERVER_TYPE_CDMA_PDE (1) - Server type is CDMA PDE
 *               - eQMI_LOC_SERVER_TYPE_CDMA_MPC (2) - Server type is CDMA MPC
 *               - eQMI_LOC_SERVER_TYPE_UMTS_SLP (3) - Server type is UMTS SLP
 *               - eQMI_LOC_SERVER_TYPE_CUSTOM_PDE (4)- Server type is custom PDE
 *
 *   \param  serverAddrTypeMask
 *             - Optional parameter
 *             - Type of address the client wants. If unspecified, the indication will
 *               contain all the types of addresses it has for the specified server type.
 *             - Valid bitmasks
 *                - 0x01 - IPv4
 *                - 0x02 - IPv6
 *                - 0x04 - URL
 */
typedef struct{
    uint32_t    serverType;
    int         has_serverAddrTypeMask;
    uint8_t     serverAddrTypeMask;
}pack_loc_SLQSLOCGetServer_t;

typedef unpack_result_t  unpack_loc_SLQSLOCGetServer_t;

/**
 * \ingroup loc
 * 
 * Pack get server.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @note   The request is acknowledged through the response, but the SUCCESS/FAILURE
 *         status is sent through \ref unpack_loc_GetServer_Ind callback
 *         If successful, the callback also contains the A-GPS server address.
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SLQSLOCGetServer(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SLQSLOCGetServer_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack get server.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SLQSLOCGetServer(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SLQSLOCGetServer_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Server IPV4 info field.
 *
 *  @param  address
 *          - IPv4 address.
 *
 *  @param  port
 *          - IPv4 port.
 */
typedef struct
{
    uint32_t  address;
    uint16_t  port;
} loc_IPv4Info;

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Get Server IPV6 info field.
 *
 *  @param  address
 *          - IPv6 address.
 *          - Type - Array of unsigned integers
 *          - Maximum length of the array - 8
 *
 *  @param  port
 *          - IPv6 port.
 */
typedef struct
{
    uint16_t address[8];
    uint32_t port;
} loc_IPv6Info;

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Get Server URL address field.
 *
 *  @param  address
 *          - Uniform Resource Locator
 *          - Type - NULL terminated string
 *          - Maximum string length (including NULL terminator) 256
 */
typedef struct
{
    char  address[256];
} loc_urlAddr;

/**
 * \ingroup loc
 * 
 *  Contain the parameters passed for SetLocGetServerCallback by
 *  the device.
 *
 *  @param  serverStatus
 *          - Status of the Get Server request.
 *          - Valid values
 *            - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *            - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *            - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *            - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *            - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *            - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *            - eQMI_LOC_TIMEOUT (6) - Request failed because it timed out
 *            - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *            - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *            - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *            - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *            - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  serverType
 *          - Type of server.
 *          - Valid values
 *            - eQMI_LOC_SERVER_TYPE_CDMA_PDE (1) - Server type is CDMA PDE
 *            - eQMI_LOC_SERVER_TYPE_CDMA_MPC (2) - Server type is CDMA MPC
 *            - eQMI_LOC_SERVER_TYPE_UMTS_SLP (3) - Server type is UMTS SLP
 *            - eQMI_LOC_SERVER_TYPE_CUSTOM_PDE (4) - Server type is custom PDE
 *          - Bit to check in ParamPresenceMask - <B>2</B>
 *
 *  @param  pIPv4AddrInfo
 *          - See @ref loc_IPv4Info for more information.
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pIPv6AddrInfo
 *          - See @ref loc_IPv6Info for more information.
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pURL
 *          - See @ref loc_urlAddr for more information.
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t         serverStatus;
    uint32_t         serverType;
    loc_IPv4Info     *pIPv4AddrInfo;
    loc_IPv6Info     *pIPv6AddrInfo;
    loc_urlAddr      *pURL;
    uint16_t         Tlvresult;
    swi_uint256_t    ParamPresenceMask;
} unpack_loc_GetServer_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the Get Server Indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GetServer_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GetServer_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Cradle Mount Config Status
 *
 *  @param  cradleMountConfigStatus
 *          - Values
 *            - 0 - Request was completed successfully
 *            - 1 - Request failed because of a general failure.
 *            - 2 - Request failed because it is not supported.
 *            - 3 - Request failed because it contained invalid parameters
 *            - 4 - Request failed because the engine is busy
 *            - 5 - Request failed because the phone is offline
 *            - 6 - Request failed because it timed out
 *            - 7 - Request failed because an undefined configuration was requested
 *            - 8 - engine could not allocate sufficient memory
 *            - 9 - Request failed because the maximum number of
 *                  Geofences are already programmed
 *            - 10 -Location service failed because of an XTRA version-based file
 *                  format check failure
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t cradleMountConfigStatus;
    uint16_t         Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_CradleMountCallback_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the Cradle Mount Indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_CradleMountCallback_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_CradleMountCallback_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Event Time Sync Reference COunter
 *
 *  @param  timeSyncRefCounter
 *          -  Sent by the location engine when it needs to synchronize
 *             location engine and control point (sensor processor) times.
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t timeSyncRefCounter;
    uint16_t         Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_EventTimeSyncCallback_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the Event Time Sync indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_EventTimeSyncCallback_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_EventTimeSyncCallback_Ind_t *pOutput
);

/**
 *  This structure contains LOC Inject Time Sync Data Status
 *
 *  @param  injectTimeSyncStatus
 *          - Values
 *            - 0 - Request was completed successfully
 *            - 1 - Request failed because of a general failure.
 *            - 2 - Request failed because it is not supported.
 *            - 3 - Request failed because it contained invalid parameters
 *            - 4 - Request failed because the engine is busy
 *            - 5 - Request failed because the phone is offline
 *            - 6 - Request failed because it timed out
 *            - 7 - Request failed because an undefined configuration was requested
 *            - 8 - engine could not allocate sufficient memory
 *            - 9 - Request failed because the maximum number of
 *                  Geofences are already programmed
 *            - 10 -Location service failed because of an XTRA version-based file
 *                  format check failure
+ *         - Bit to check in ParamPresenceMask - <B>1</B>

 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t injectTimeSyncStatus;
    uint16_t         Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_InjectTimeSyncDataCallback_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the inject time sync data indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectTimeSyncDataCallback_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectTimeSyncDataCallback_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Inject Sensor Data
 *
 *  @param  injectSensorDataStatus
 *          - Values
  *           - 0 - Request was completed successfully
 *            - 1 - Request failed because of a general failure.
 *            - 2 - Request failed because it is not supported.
 *            - 3 - Request failed because it contained invalid parameters
 *            - 4 - Request failed because the engine is busy
 *            - 5 - Request failed because the phone is offline
 *            - 6 - Request failed because it timed out
 *            - 7 - Request failed because an undefined configuration was requested
 *            - 8 - engine could not allocate sufficient memory
 *            - 9 - Request failed because the maximum number of
 *                  Geofences are already programmed
 *            - 10 -Location service failed because of an XTRA version-based file
 *                  format check failure
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  pOpaqueIdentifier[OPTIONAL]
 *             - Sent in by the client echoed so the client can
 *               relate the indication to the request.
 *             - NULL when this TLV not present
 *             - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  pAccelSamplesAccepted[OPTIONAL]
 *             - Lets the client know how many 3-axis accelerometer
 *               samples were accepted.
 *             - This field is present only if the accelerometer samples
 *               were sent in the request.
 *             - NULL when this TLV not present
 *             - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  pGyroSamplesAccepted[OPTIONAL]
 *             - Lets the client know how many 3-axis gyroscope
 *               samples were accepted.
 *             - This field is present only if the gyroscope samples
 *               were sent in the request.
 *             - NULL when this TLV not present
 *             - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *   @param  pAccelTempSamplesAccepted[OPTIONAL]
 *             - Lets the client know how many accelerometer temperature
 *               samples were accepted.
 *             - This field is present only if the accelerometer
 *               temperature samples were sent in the request.
 *             - NULL when this TLV not present
 *             - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *   @param  pGyroTempSamplesAccepted[OPTIONAL]
 *             - Lets the client know how many gyroscope temperature
 *               samples were accepted.
 *             - This field is present only if the gyroscope temperature
 *               samples were sent in the request.
 *             - NULL when this TLV not present
 *             - Bit to check in ParamPresenceMask - <B>20</B>
 *
 *   @param TlvResult
 *              - unpack result
 * 
 *   @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t injectSensorDataStatus;
    uint32_t *pOpaqueIdentifier;
    uint8_t  *pAccelSamplesAccepted;
    uint8_t  *pGyroSamplesAccepted;
    uint8_t  *pAccelTempSamplesAccepted;
    uint8_t  *pGyroTempSamplesAccepted;
    uint16_t TlvResult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_InjectSensorDataCallback_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the inject sensor data indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectSensorDataCallback_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectSensorDataCallback_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains Accelerometer Accept Ready Info
 *
 *  @param  injectEnable
 *          - GNSS location engine is ready to accept data from sensor.
 *          - Values
 *          - 0x01 - Ready to accept sensor data
 *          - 0x00 - Not ready to accept sensor data
 *
 *  @param  samplesPerBatch
 *          - number of samples per batch the GNSS location engine is to receive.
 *          - samplingFrequency = samplesPerBatch * batchesPerSecond
 *          - samplesPerBatch must be a nonzero positive value.
 *
 *  @param  batchPerSec
 *          - LTE NAS version minor
 *          - Number of sensor-data batches the GNSS location engine is to
 *            receive per second.
 *          - BatchesPerSecond must be a nonzero positive value.
 *
 */
typedef struct {
     uint8_t    injectEnable;
     uint16_t    samplesPerBatch;
     uint16_t    batchPerSec;
}loc_accelAcceptReady;

/**
 * \ingroup loc
 * 
 *  This structure contains Gyroscope Accept Ready Info
 *
 *  @param  injectEnable
 *          - GNSS location engine is ready to accept data from sensor.
 *          - Values
 *          - 0x01 - Ready to accept sensor data
 *          - 0x00 - Not ready to accept sensor data
 *
 *  @param  samplesPerBatch
 *          - number of samples per batch the GNSS location engine is to receive.
 *          - samplingFrequency = samplesPerBatch * batchesPerSecond
 *          - samplesPerBatch must be a nonzero positive value.
 *
 *  @param  batchPerSec
 *          - LTE NAS version minor
 *          - Number of sensor-data batches the GNSS location engine is to
 *            receive per second.
 *          - BatchesPerSecond must be a nonzero positive value.
 *
 */
typedef struct {
     uint8_t    injectEnable;
     uint16_t    samplesPerBatch;
     uint16_t    batchPerSec;
}loc_gyroAcceptReady;

/**
 * \ingroup loc
 * 
 *  This structure contains Accelerometer Temperature Accept Ready Info
 *
 *  @param  injectEnable
 *          - GNSS location engine is ready to accept data from sensor.
 *          - Values
 *          - 0x01 - Ready to accept sensor data
 *          - 0x00 - Not ready to accept sensor data
 *
 *  @param  samplesPerBatch
 *          - number of samples per batch the GNSS location engine is to receive.
 *          - samplingFrequency = samplesPerBatch * batchesPerSecond
 *          - samplesPerBatch must be a nonzero positive value.
 *
 *  @param  batchPerSec
 *          - LTE NAS version minor
 *          - Number of sensor-data batches the GNSS location engine is to
 *            receive per second.
 *          - BatchesPerSecond must be a nonzero positive value.
 *
 */
typedef struct {
     uint8_t    injectEnable;
     uint16_t    samplesPerBatch;
     uint16_t    batchPerSec;
}loc_accelTempAcceptReady;

/**
 * \ingroup loc
 * 
 *  This structure contains Gyroscope Temperature Accept Ready Info
 *
 *  @param  injectEnable
 *          - GNSS location engine is ready to accept data from sensor.
 *          - Values
 *          - 0x01 - Ready to accept sensor data
 *          - 0x00 - Not ready to accept sensor data
 *
 *  @param  samplesPerBatch
 *          - number of samples per batch the GNSS location engine is to receive.
 *          - samplingFrequency = samplesPerBatch * batchesPerSecond
 *          - samplesPerBatch must be a nonzero positive value.
 *
 *  @param  batchPerSec
 *          - LTE NAS version minor
 *          - Number of sensor-data batches the GNSS location engine is to
 *            receive per second.
 *          - BatchesPerSecond must be a nonzero positive value.
 *
 */
typedef struct {
     uint8_t    injectEnable;
     uint16_t    samplesPerBatch;
     uint16_t    batchPerSec;
}loc_gyroTempAcceptReady;

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Event Sensor Streaming Ready Status
 *
 *  @param  -pAccelAcceptReady[OPTIONAL]
 *          - See @ref loc_accelAcceptReady for more information
 *          - Bit to check in ParamPresenceMask - <B>16</B>
 *
 *  @param  -pGyroAcceptReady[OPTIONAL]
 *          - See @ref loc_gyroAcceptReady for more information
 *          - Bit to check in ParamPresenceMask - <B>17</B>
 *
 *  @param  -pAccelTempAcceptReady[OPTIONAL]
 *          - See @ref loc_accelTempAcceptReady for more information
 *          - Bit to check in ParamPresenceMask - <B>18</B>
 *
 *  @param  -pGyroTempAcceptReady[OPTIONAL]
 *          - See @ref loc_gyroTempAcceptReady for more information
 *          - Bit to check in ParamPresenceMask - <B>19</B>
 *
 *  @param  TlvResult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    loc_accelAcceptReady       *pAccelAcceptReady;
    loc_gyroAcceptReady        *pGyroAcceptReady;
    loc_accelTempAcceptReady   *pAccelTempAcceptReady;
    loc_gyroTempAcceptReady    *pGyroTempAcceptReady;
    uint16_t                   TlvResult;
    swi_uint256_t              ParamPresenceMask;
} unpack_loc_SensorStreamingCallback_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the Sensor streaming status indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SensorStreamingCallback_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SensorStreamingCallback_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters passed for Inject UTC time indication by
 *  the device.
 *
 *  @param  status
 *          - Status of the UTC Time Injection request
 *          - Valid values:
 *            - 0 - Request was completed successfully
 *            - 1 - Request failed because of a general failure.
 *            - 2 - Request failed because it is not supported.
 *            - 3 - Request failed because it contained invalid parameters
 *            - 4 - Request failed because the engine is busy
 *            - 5 - Request failed because the phone is offline
 *            - 6 - Request failed because it timed out
 *            - 7 - Request failed because an undefined configuration was requested
 *            - 8 - engine could not allocate sufficient memory
 *            - 9 - Request failed because the maximum number of
 *                  Geofences are already programmed
 *            - 10 -Location service failed because of an XTRA version-based file
 *                  format check failure
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * 
 *  @note    None
 *
 */
typedef struct
{
    uint32_t status;
    uint16_t         Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_InjectUTCTimeCallback_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the Inject UTC time indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectUTCTimeCallback_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectUTCTimeCallback_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters passed for LOC Inject Position indication by
 *  the device.
 *
 *  @param  status
 *          - Position Injection Status
 *          - Valid values:
 *            - 0 - Request was completed successfully
 *            - 1 - Request failed because of a general failure.
 *            - 2 - Request failed because it is not supported.
 *            - 3 - Request failed because it contained invalid parameters
 *            - 4 - Request failed because the engine is busy
 *            - 5 - Request failed because the phone is offline
 *            - 6 - Request failed because it timed out
 *            - 7 - Request failed because an undefined configuration was requested
 *            - 8 - engine could not allocate sufficient memory
 *            - 9 - Request failed because the maximum number of
 *                  Geofences are already programmed
 *            - 10 -Location service failed because of an XTRA version-based file
 *                  format check failure
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 * 
 *  @note    None
 *
 */
typedef struct
{
    uint32_t status;
    uint16_t         Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_InjectPositionCallback_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the Inject position indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectPositionCallback_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectPositionCallback_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure specifies information regarding the IPv4 address and port.
 *
 * @param IPv4Addr
 *        - IPv4 address.
 *
 * @param IPv4Port
 *        - IPv4 port.
 */
typedef struct
{
    uint32_t    IPv4Addr;
    uint16_t    IPv4Port;
}loc_IPv4Config;

/**
 * \ingroup loc
 * 
 * This structure specifies information regarding the IPv6 address and port.
 *
 * @param IPv6Addr
 *        - IPv6 address.
 *        - Type - Array of unsigned integers
 *        - Maximum length of the array: 8
 *
 * @param IPv6Port
 *        - IPv6 port.
 */
typedef struct
{
    uint16_t    IPv6Addr[8];
    uint32_t    IPv6Port;
}loc_IPv6Config;

/**
 * \ingroup loc
 * 
 * This structure specifies information regarding the URL.
 *
 * @param urlAddr
 *        - URL address.
 *        - Type - NULL-terminated string
 *        - Maximum string length (including NULL terminator) - 256
 */
typedef struct
{
    char    urlAddr[256];
}loc_URLAddrInfo;

/**
 * \ingroup loc
 * 
 *  This structure contains parameters to set A-GPS Server
 *
 *  @param  serverType
 *             - Type of server
 *             - Valid values:
 *               - 1 - Server type is CDMA PDE
 *               - 2 - Server type is CDMA MPC
 *               - 3 - Server type is UMTS SLP
 *               - 4 - Server type is custom PDE
 *
 *  @param  pIPv4Config
 *             - IPv4 address and port (Optional)
 *             -  See @ref loc_IPv4Config for more information
 *
 *  @param  pIPv6Config
 *             - IPv6 address and port (Optional)
 *             -  See @ref loc_IPv6Config for more information
 *
 *  \param  pURLAddr
 *             - Uniform Resource Locator (Optional)
 *             -  See @ref loc_URLAddrInfo for more information
 */
typedef struct{
    uint32_t                serverType;
    loc_IPv4Config          *pIPv4Config;
    loc_IPv6Config          *pIPv6Config;
    loc_URLAddrInfo         *pURLAddr;
}pack_loc_SLQSLOCSetServer_t;

typedef unpack_result_t unpack_loc_SLQSLOCSetServer_t;

/**
 * \ingroup loc
 * 
 * Pack Set server.
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @note   If multiple types of addresses are specified in the request, the IPv4 address
 *         takes precedence over the IPv6 address and the IPv6 address takes precedence
 *         over the URL address.The request is acknowledged through the response, but
 *         the SUCCESS/FAILURE status is sent through \ref unpack_loc_SetServer_Ind callback
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SLQSLOCSetServer(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SLQSLOCSetServer_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack set server.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SLQSLOCSetServer(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SLQSLOCSetServer_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters passed for SetLocSetServerCallback by
 *  the device.
 *
 *  @param  serverStatus
 *          - Status of the Get Server request.
 *          - Valid values
 *            - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *            - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *            - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *            - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *            - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *            - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *            - eQMI_LOC_TIMEOUT (6) - Request failed because it timed out
 *            - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *            - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *            - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *            - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *            - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *            - 0xffffffff - Invalid data.
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 */
typedef struct
{
    uint32_t         serverStatus;
    uint16_t         Tlvresult;
} unpack_loc_SetServer_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the Set Server Indication.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetServer_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetServer_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Event WIFI field.
 *
 *  @param  requestType
 *          - Request Types
 *             - Valid values:
 *               - eQMI_LOC_WIFI_START_PERIODIC_HI_FREQ_FIXES (0) – Start 
 *               - periodic fixes with high frequency
 *               - eQMI_LOC_WIFI_START_PERIODIC_KEEP_WARM (1) – Keep
 *               - warm for low frequency fixes without data downloads
 *               - eQMI_LOC_WIFI_STOP_PERIODIC_FIXES (2) – Stop periodic fixes request
 * 
 *  @param pTimeBetweenFixes
 *             - Time between fixes for a periodic request.
 *             - Units: Milliseconds
 * 
 *  @param pE911Mode
 *              - Specifies whether the GPS engine is in  E911 mode when this indication is sent to the client.
 *              - Valid values: 
 *                - 0x00 (FALSE) - GPS engine is not in E911 mode
 *                - 0x01 (TRUE) - GPS engine is in E911 mode
 * 
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t                    requestType;
    uint16_t                    *pTimeBetweenFixes;
    uint8_t                     *pE911Mode;
    uint16_t                    Tlvresult;
    swi_uint256_t               ParamPresenceMask;
} unpack_loc_Event_Wifi_Req_Ind_t;

/**
 * \ingroup loc
 * 
 * Event WIFI request unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_Event_Wifi_Req_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_Event_Wifi_Req_Ind_t *pOutput
);

/**
 * \ingroup loc
 *
 * LOC NMEA sentence types
 */
enum {
    QMI_LOC_NMEA_MASK_GGA = 0x00000001,
    QMI_LOC_NMEA_MASK_RMC = 0x00000002,
    QMI_LOC_NMEA_MASK_GSV = 0x00000004,
    QMI_LOC_NMEA_MASK_GSA = 0x00000008,
    QMI_LOC_NMEA_MASK_VTG = 0x00000010,
    QMI_LOC_NMEA_MASK_PQXFI = 0x00000020,
    QMI_LOC_NMEA_MASK_PSTIS = 0x00000040,
    QMI_LOC_NMEA_MASK_GLGSV = 0x00000080,
    QMI_LOC_NMEA_MASK_GNGSA = 0x00000100,
    QMI_LOC_NMEA_MASK_GNGNS = 0x00000200,
    QMI_LOC_NMEA_MASK_GARMC = 0x00000400,
    QMI_LOC_NMEA_MASK_GAGSV = 0x00000800,
    QMI_LOC_NMEA_MASK_GAGSA = 0x00001000,
    QMI_LOC_NMEA_MASK_GAVTG = 0x00002000,
    QMI_LOC_NMEA_MASK_GAGGA = 0x00004000,
    QMI_LOC_NMEA_MASK_PQGSA = 0x00008000,
    QMI_LOC_NMEA_MASK_PQGSV = 0x00010000,
    QMI_LOC_NMEA_MASK_DEBUG = 0x00020000,
    QMI_LOC_NMEA_MASK_GPDTM = 0x00040000,
    QMI_LOC_NMEA_MASK_GNGGA = 0x00080000,
    QMI_LOC_NMEA_MASK_GNRMC = 0x00100000,
    QMI_LOC_NMEA_MASK_GNVTG = 0x00200000,
    QMI_LOC_NMEA_MASK_GAGNS = 0x00400000,
    QMI_LOC_NMEA_MASK_GBGGA = 0x00800000,
    QMI_LOC_NMEA_MASK_GBGSA = 0x01000000,
    QMI_LOC_NMEA_MASK_GBGSV = 0x02000000,
    QMI_LOC_NMEA_MASK_GBRMC = 0x04000000,
    QMI_LOC_NMEA_MASK_GBVTG = 0x08000000,
    QMI_LOC_NMEA_MASK_GQGSV = 0x10000000,
    QMI_LOC_NMEA_MASK_GIGSV = 0x20000000,
    QMI_LOC_NMEA_MASK_GNDTM = 0x40000000
};

/**
 * \ingroup loc
 * 
 * This structure contains Set NMEA Types unpack
 *
 * \param nmeaTypes
 *        - Bitmasks of NMEA types to enable. 
 *          - Valid bitmasks:
 *              - QMI_LOC_NMEA_MASK_GGA (0x00000001) - Enable GGA type
 *              - QMI_LOC_NMEA_MASK_RMC (0x00000002) - Enable RMC type
 *              - QMI_LOC_NMEA_MASK_GSV (0x00000004) - Enable GSV type
 *              - QMI_LOC_NMEA_MASK_GSA (0x00000008) - Enable GSA type
 *              - QMI_LOC_NMEA_MASK_VTG (0x00000010) - Enable VTG type
 *              - QMI_LOC_NMEA_MASK_PQXFI (0x00000020) - Enable PQXFI type
 *              - QMI_LOC_NMEA_MASK_PSTIS (0x00000040) - Enable PSTIS type
 *              - QMI_LOC_NMEA_MASK_GLGSV (0x00000080) - Enable GLGSV type
 *              - QMI_LOC_NMEA_MASK_GNGSA (0x00000100) - Enable GNGSA type
 *              - QMI_LOC_NMEA_MASK_GNGNS (0x00000200) - Enable GNGNS type
 *              - QMI_LOC_NMEA_MASK_GARMC (0x00000400) - Enable GARMC type
 *              - QMI_LOC_NMEA_MASK_GAGSV (0x00000800) - Enable GAGSV type
 *              - QMI_LOC_NMEA_MASK_GAGSA (0x00001000) - Enable GAGSA type
 *              - QMI_LOC_NMEA_MASK_GAVTG (0x00002000) - Enable GAVTG type
 *              - QMI_LOC_NMEA_MASK_GAGGA (0x00004000) - Enable GAGGA type
 *              - QMI_LOC_NMEA_MASK_PQGSA (0x00008000) - Enable PQGSA type
 *              - QMI_LOC_NMEA_MASK_PQGSV (0x00010000) - Enable PQGSV type
 *              - QMI_LOC_NMEA_MASK_DEBUG (0x00020000) - Enable DEBUG NMEA type
 *              - QMI_LOC_NMEA_MASK_GPDTM (0x00040000) - Enable GPDTM type
 *              - QMI_LOC_NMEA_MASK_GNGGA (0x00080000) - Enable GNGGA type
 *              - QMI_LOC_NMEA_MASK_GNRMC (0x00100000) - Enable GNRMC type
 *              - QMI_LOC_NMEA_MASK_GNVTG (0x00200000) - Enable GNVTG type
 *              - QMI_LOC_NMEA_MASK_GAGNS (0x00400000) - Enable GAGNS type
 *              - QMI_LOC_NMEA_MASK_GBGGA (0x00800000) - Enable GBGGA type
 *              - QMI_LOC_NMEA_MASK_GBGSA (0x01000000) - Enable GBGSA type
 *              - QMI_LOC_NMEA_MASK_GBGSV (0x02000000) - Enable GBGSV type
 *              - QMI_LOC_NMEA_MASK_GBRMC (0x04000000) - Enable GBRMC type
 *              - QMI_LOC_NMEA_MASK_GBVTG (0x08000000) - Enable GBVTG type
 *              - QMI_LOC_NMEA_MASK_GQGSV (0x10000000) - Enable GQGSV type
 *              - QMI_LOC_NMEA_MASK_GIGSV (0x20000000) - Enable GIGSV type
 *              - QMI_LOC_NMEA_MASK_GNDTM (0x40000000) - Enable GNDTM type
 */

typedef struct{
    uint32_t nmeaTypes;
}pack_loc_NmeaTypes_t;

typedef unpack_result_t unpack_loc_NmeaTypes_t;

/**
 * \ingroup loc
 * 
 * Set NMEA Types pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SetNmeaTypes(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_NmeaTypes_t   *reqArg);

/**
 * \ingroup loc
 * 
 * Set NMEA Types unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetNmeaTypes(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_NmeaTypes_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Set External Power Configure status field.
 *
 *  @param  status
 *          - Status of Set NMEA Types request.
 *              - Valid values:
 *                - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *                - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *                - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *                - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *                - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *                - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *                - eQMI_LOC_TIMEOUT (6) - Request failed because it timed out
 *                - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined 
 *                                                      configuration was requested
 *                - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine 
 *                                                     could not allocate sufficient memory for the request
 *                - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of
 *                                                      Geofences are already programmed
 *                - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because
 *                                                  of an XTRA version-based file format check failure 
 *				  - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *                - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct
{
    uint32_t status;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_SetNmeaTypes_Ind_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the specified operation mode.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetNmeaTypes_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetNmeaTypes_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Set External Power Configure status field.
 *
 *  @param  status
 *          - Status of Set NMEA Types request.
 *              - Valid values:
 *                  - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *                  - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *                  - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *                  - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *                  - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *                  - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *                  - eQMI_LOC_TIMEOUT (6) - Request failed because it timed out
 *                  - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined 
 *                                                      configuration was requested
 *                  - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine 
 *                                                     could not allocate sufficient memory for the request
 *                  - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of
 *                                                      Geofences are already programmed
 *                  - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because
 *                                                  of an XTRA version-based file format check failure 
 *                  - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *              - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *	@param  nmeaSentenceType
 *			- NMEA Sentence Types
 *			- NMEA types to enable. Valid bitmasks:
 *              - QMI_LOC_NMEA_MASK_GGA (0x00000001) - Enable GGA type
 *              - QMI_LOC_NMEA_MASK_RMC (0x00000002) - Enable RMC type
 *              - QMI_LOC_NMEA_MASK_GSV (0x00000004) - Enable GSV type
 *              - QMI_LOC_NMEA_MASK_GSA (0x00000008) - Enable GSA type
 *              - QMI_LOC_NMEA_MASK_VTG (0x00000010) - Enable VTG type
 *              - QMI_LOC_NMEA_MASK_PQXFI (0x00000020) - Enable PQXFI type
 *              - QMI_LOC_NMEA_MASK_PSTIS (0x00000040) - Enable PSTIS type
 *              - QMI_LOC_NMEA_MASK_GLGSV (0x00000080) - Enable GLGSV type
 *              - QMI_LOC_NMEA_MASK_GNGSA (0x00000100) - Enable GNGSA type
 *              - QMI_LOC_NMEA_MASK_GNGNS (0x00000200) - Enable GNGNS type
 *              - QMI_LOC_NMEA_MASK_GARMC (0x00000400) - Enable GARMC type
 *              - QMI_LOC_NMEA_MASK_GAGSV (0x00000800) - Enable GAGSV type
 *              - QMI_LOC_NMEA_MASK_GAGSA (0x00001000) - Enable GAGSA type
 *              - QMI_LOC_NMEA_MASK_GAVTG (0x00002000) - Enable GAVTG type
 *              - QMI_LOC_NMEA_MASK_GAGGA (0x00004000) - Enable GAGGA type
 *              - QMI_LOC_NMEA_MASK_PQGSA (0x00008000) - Enable PQGSA type
 *              - QMI_LOC_NMEA_MASK_PQGSV (0x00010000) - Enable PQGSV type
 *              - QMI_LOC_NMEA_MASK_DEBUG (0x00020000) - Enable DEBUG NMEA type
 *              - QMI_LOC_NMEA_MASK_GPDTM (0x00040000) - Enable GPDTM type
 *              - QMI_LOC_NMEA_MASK_GNGGA (0x00080000) - Enable GNGGA type
 *              - QMI_LOC_NMEA_MASK_GNRMC (0x00100000) - Enable GNRMC type
 *              - QMI_LOC_NMEA_MASK_GNVTG (0x00200000) - Enable GNVTG type
 *              - QMI_LOC_NMEA_MASK_GAGNS (0x00400000) - Enable GAGNS type
 *              - QMI_LOC_NMEA_MASK_GBGGA (0x00800000) - Enable GBGGA type
 *              - QMI_LOC_NMEA_MASK_GBGSA (0x01000000) - Enable GBGSA type
 *              - QMI_LOC_NMEA_MASK_GBGSV (0x02000000) - Enable GBGSV type
 *              - QMI_LOC_NMEA_MASK_GBRMC (0x04000000) - Enable GBRMC type
 *              - QMI_LOC_NMEA_MASK_GBVTG (0x08000000) - Enable GBVTG type
 *              - QMI_LOC_NMEA_MASK_GQGSV (0x10000000) - Enable GQGSV type
 *              - QMI_LOC_NMEA_MASK_GIGSV (0x20000000) - Enable GIGSV type
 *              - QMI_LOC_NMEA_MASK_GNDTM (0x40000000) - Enable GNDTM type
 *              - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *
 */
typedef struct
{
    uint32_t status;
    uint32_t nmeaSentenceType;
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_GetNmeaTypes_Ind_t;

/**
 * \ingroup loc
 * 
 * Set NMEA Types pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GetNmeaTypes(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen);

/**
 * \ingroup loc
 * 
 * Set NMEA Types unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GetNmeaTypes(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_NmeaTypes_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the specified operation mode.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GetNmeaTypes_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GetNmeaTypes_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Set Event Enject Time pack
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_EventInjectTime(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen);


/**
 * \ingroup loc
 * 
 *  This structure holds information related broadcast SMS Warning Area Coordinate
 *
 *  @param  serverUrl_len
 *          - Number of sets of the serverUrl
 *
 *  @param  serverUrl
 *          - Assistance server URL.
 *            Type: NULL-terminated string
 *            Maximum string length (including NULL terminator): 256

 */
typedef struct
{
	uint8_t serverUrl_len;
	char serverUrl[MAX_URL_ADDR_STR_LEN];
} loc_AssistanceServerURL;

/**
 * \ingroup loc
 * 
 *  @param  pDelayThreshold
 *          - The time server is to be skipped if a one-way delay to the server exceeds this threshold.
 *          - Units: Milliseconds
 * 
 * @param   pAssitanceServerUrlList_len
 *          - Number of sets of the AssistanceServerURL instances
 * 
 * @param   pAssistanceServerURLList
 *          - Pointer to tyhe list of Assistance Server URL
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t                    *pDelayThreshold;
    uint8_t                     *pAssitanceServerUrlList_len;
    loc_AssistanceServerURL     *pAssistanceServerURLList;
    uint16_t                    Tlvresult;
    swi_uint256_t               ParamPresenceMask;
} unpack_loc_EventInjectTime_Ind_t;

/**
 * \ingroup loc
 * 
 * This structure contains LOC Event Inject Time unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_EventInjectTime_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the Time Server Info.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_EventInjectTime_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_EventInjectTime_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains Set Operation Mode pack
 *
 * \param masterClientKey
 *        - Master Client 32-bit Key
 */
typedef struct{
    uint32_t masterClientKey;
}pack_loc_RegisterMasterClient_t;

/**
 * \ingroup loc
 * 
 * This structure contains Set Operation Mode unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_RegisterMasterClient_t;

/**
 * \ingroup loc
 * 
 * Register Master Client
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_RegisterMasterClient(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_RegisterMasterClient_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Register Master Client unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_RegisterMasterClient(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_RegisterMasterClient_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Register Master Client Status callback function.
 *
 *  \param  status[OUT]
 *          - Status of the master client registration
 *            - Valid values:
 *              - eQMI_LOC_REGISTER_MASTER_CLIENT_SUCCESS (0) - Request was completed successfully - the associated
 *                                                            control point is now the master client
 *              - eQMI_LOC_REGISTER_MASTER_CLIENT_INVALID_KEY (1) - Request failed because the supplied master key 
 *                                                              is invalid
 *              - eQMI_LOC_REGISTER_MASTER_CLIENT_ALREADY_HAVE_MASTER_CLIENT (2) - Request failed because there is 
 *                                                              already a master client registered
 *              - eQMI_LOC_REGISTER_MASTER_CLIENT_INTERNAL_FAILURE (3) - Request failed due to unforeseen internal error.
 *  \param Tlvresult
 *        - Unpack result.
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t status;
    uint16_t Tlvresult;
    swi_uint256_t  ParamPresenceMask;
} unpack_loc_RegisterMasterClient_Ind_t;

/**
 * \ingroup loc
 * 
 * Register Master Client unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_RegisterMasterClient_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_RegisterMasterClient_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains Inject Supl Certificate pack
 *
 * \param suplCertId
 *        - Certificate ID of the SUPL certificate.
 *          - Units: Bytes
 *          - Range: 0 to 9
 * \param suplCertData_len
 *       - Number of sets of the following suplCertData
 * \param pSuplCertData
 *        - SUPL certificate contents.
 *          - Type: Array of bytes
 *          - Maximum certificate size: 2000 bytes
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
	uint8_t        suplCertId;
    uint16_t       suplCertData_len;
    uint8_t        *pSuplCertData;
    swi_uint256_t  ParamPresenceMask;
}pack_loc_InjectSuplCertificate_t;

/**
 * \ingroup loc
 * 
 * This structure contains Inject Supl Certificate unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 */
typedef struct{
    uint16_t       Tlvresult;
}unpack_loc_InjectSuplCertificate_t;

/**
 * \ingroup loc
 * 
 * Inject Supl Certificate
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_InjectSuplCertificate(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_InjectSuplCertificate_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack Inject Supl Certificate
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectSuplCertificate(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectSuplCertificate_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains Inject Supl Certificate pack
 *
 * \param pSuplCertId
 *        - Certificate ID of the SUPL certificate.
 *          - Units: Bytes
 *          - Range: 0 to 9
 */
typedef struct{
	uint8_t        *pSuplCertId;
}pack_loc_DeleteSuplCertificate_t;


/**
 * \ingroup loc
 * 
 * Delete Supl Certificate
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pReqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_DeleteSuplCertificate(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_DeleteSuplCertificate_t *pReqArg
);

/**
 * \ingroup loc
 * 
 * This structure contains Delete Supl Certificate unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 */
typedef struct{
    uint16_t       Tlvresult;
}unpack_loc_DeleteSuplCertificate_t;

/**
 * \ingroup loc
 * 
 * Unpack Delete Supl Certificate
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_DeleteSuplCertificate(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_DeleteSuplCertificate_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Inject Supl Certificate Status callback function.
 *
 *  @param  status[OUT]
 *          - Status of the Inject SUPL Certificate request.
 *             - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE(1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER(3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient 
 *                                                 memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are 
 *                                                     already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA
 *                                                          version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *          - See \ref qmTlvResult
*/
typedef struct
{
    uint32_t status;
    uint16_t Tlvresult;
} unpack_loc_InjectSuplCertificate_Ind_t;

/**
 * \ingroup loc
 * 
 * Inject Supl Certificate Ind unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectSuplCertificate_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectSuplCertificate_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Delete Supl Certificate Status callback function.
 *
 *  @param  status[OUT]
 *          - Status of the Delete SUPL Certificate request.
 *             - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE(1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER(3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient 
 *                                                 memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are 
 *                                                     already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA
 *                                                          version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 * 
 *  @param  Tlvresult
 *          - unpack result
 * 
 *          - See \ref qmTlvResult
 */
typedef struct
{
    uint32_t status;
    uint16_t Tlvresult;
} unpack_loc_DeleteSuplCertificate_Ind_t;

/**
 * \ingroup loc
 * 
 * Register Delete Supl Certificate Ind unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_DeleteSuplCertificate_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_DeleteSuplCertificate_Ind_t *pOutput
);

/**
 * \ingroup loc
 *
 * This structure contains Set GNSS Constell Report Config pack
 *
 *  \param  pMeasReportConfig
 *          - GNSS measurement report constellation control.
 *			- Valid values:
 *				- eQMI_SYSTEM_GPS (0x01) - Enable GPS
 *				- eQMI_SYSTEM_GLO (0x02) - Enable GLONASS
 *				- eQMI_SYSTEM_BDS (0x04) - Enable BDS
 *				- eQMI_SYSTEM_GAL (0x08) - Enable Galileo
 *				- eQMI_SYSTEM_QZSS (0x10) - Enable QZSS
 *
 *	\param pSvPolyReportConfig
 *			- SV polynomial report constellation control.
 *			- Valid values:
 *				- eQMI_SYSTEM_GPS (0x01) - Enable GPS
 *				- eQMI_SYSTEM_GLO (0x02) - Enable GLONASS
 *				- eQMI_SYSTEM_BDS (0x04) - Enable BDS
 *				- eQMI_SYSTEM_GAL (0x08) - Enable Galileo
 *				- eQMI_SYSTEM_QZSS (0x10) - Enable QZSS
 *
 *	\param pReportFullEphemerisDb
 *			- Request indicating that the client needs complete ephemeris.
 *
 *	\param pReportFullSvPolyDb
 *			- Request indicating that the client needs complete SV polynomials.
 *
 *	\param pReportFullIonoDb
 *			- Request indicating client needs complete Iono.
 */
typedef struct {
	uint64_t   *pMeasReportConfig;
	uint64_t   *pSvPolyReportConfig;
	uint8_t	   *pReportFullEphemerisDb;
	uint8_t	   *pReportFullSvPolyDb;
	uint8_t	   *pReportFullIonoDb;
}pack_loc_SetGnssConstellReportConfig_t;

/**
 * \ingroup loc
 *
 * Pack Sets satellite constellations of interest for reporting
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SetGnssConstellReportConfig(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_SetGnssConstellReportConfig_t   *reqArg
);

typedef unpack_result_t unpack_loc_GnssConstellReportConfig_t;

/**
 * \ingroup loc
 *
 * Unpack Sets satellite constellations of interest for reporting
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetGnssConstellReportConfig(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_loc_GnssConstellReportConfig_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters fo NI Geofence notification
 *
 *  \param  geofenceId
 *          - Geofence ID
 *              - ID of the Geofence for which this notification was generated.
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  \param  operationType
 *          - Operation Type.
 *          - Operation for which this notification was generated.
 *           - Valid values:
 *              - eQMI_LOC_NI_GEOFENCE_ADDED (1) - An NI Geofence was added
 *              - eQMI_LOC_NI_GEOFENCE_DELETED (2) - An NI Geofence was deleted
 *              - eQMI_LOC_NI_GEOFENCE_EDITED (3) – An NI Geofence was edited; the control point can query the Geofence to find the its current state
 *          - Bit to check in ParamPresenceMask - <B>0x02</B>
 *
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t geofenceId;
    uint32_t operationType;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
} unpack_loc_NiGeofenceInd_t;

/**
 * \ingroup loc
 * 
 * NI Geofence Notification Ind unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_NiGeofenceNotification_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_NiGeofenceInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters fo Geofence general alert notification
 *
 *  \param  geofenceAlert
 *          - Specifies the Geofence general alert type.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_GEN_ALERT_GNSS_UNAVAILABLE (1) - GNSS is unavailable and GNSS position fixes cannot be used to monitor Geofences
 *              - eQMI_LOC_GEOFENCE_GEN_ALERT_GNSS_AVAILABLE (2) - GNSS is now available and GNSS postion fixes can be used to monitor Geofences
 *              - eQMI_LOC_GEOFENCE_GEN_ALERT_OOS (3) - The engine is out of service and no cell ID coverage information is available
 *              - eQMI_LOC_GEOFENCE_GEN_ALERT_TIME_INVALID (4) - The engine has an invalid time
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 *  \note    None
 *
 */
typedef struct 
{
    uint32_t geofenceAlert;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceGenAlertInd_t;

/**
 * \ingroup loc
 * 
 * Geofence General Alert Notification Ind unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceGerAlert_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceGenAlertInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters fo Geofence position
 *  Position of the client when it breached the Geofence. This TLV is included if the client configures the Geofence to
 *  report position. The position is reported at the same confidence level that was specified in the Add Circular Geofence request.
 *
 *  @param  timestampUtc
 *          - UTC timestamp.
 *          - Units: Milliseconds since Jan. 1, 1970
 *
 *  @param  latitude
 *          - Latitude (specified in WGS84 datum).
 *          - Type: Floating point
 *          - Units: Degrees
 *          - Range: -90.0 to 90.0
 *          - Positive values indicate northern latitude
 *          - Negative values indicate southern latitude
 *  
 *  @param  longitude
 *          - Longitude (specified in WGS84 datum).
 *          - Type: Floating point
 *          - Units: Degrees
 *          - Range: -180.0 to 180.0
 *              - Positive values indicate eastern longitude
 *              - Negative values indicate western longitude
 *
 *  @param horUncEllipseSemiMinor
 *         - Semi-minor axis of horizontal elliptical uncertainty.  Units: Meters 
 * 
 *  @param horUncEllipseSemiMajor
 *         - Semi-major axis of horizontal elliptical uncertainty.  Units: Meters
 * 
 *  @param horUncEllipseOrientAzimuth
 *         - Elliptical horizontal uncertainty azimuth of orientation.
 *         - Units: Decimal degrees. Range: 0 to 180
 * 
 *  @param speedHorizontal_valid
 *         - Indicates whether the Horizontal speed field contains valid information.
 *         - 0x01 (TRUE) - Horizontal speed is valid
 *         - 0x00 (FALSE) - Horizontal speed is invalid and is to be ignored
 * 
 *  @param speedHorizontal
 *         - Horizontal speed. Units: Meters/second
 * 
 *  @param altitudeWrtEllipsoid_valid 
 *          - Indicates whether the altitude field contains valid information.
 *              - 0x01 (TRUE) – Altitude field is valid
 *              - 0x00 (FALSE) – Altitude field is invalid and is to be ignored
 * 
 *  @param altitudeWrtEllipsoid
 *          - Altitude with respect to the WGS84 ellipsoid.
 *          - Units: Meters, Range: -500 to 15883
 * 
 *  @param vertUnc_valid
 *          - Indicates whether the Vertical Uncertainty field contains valid information.
 *              - 0x01 (TRUE) – Vertical Uncertainty field is valid
 *              - 0x00 (FALSE) – Vertical Uncertainty field is invalid and is to be ignored
 * 
 *  @param vertUnc
 *          - Vertical uncertainty. Units: Meters
 * 
 *  @param speedVertical_valid
 *          - Indicates whether the Vertical Speed field contains valid information.
 *          - 0x01 (TRUE) – Vertical Speed field is valid
 *          - 0x00 (FALSE) – Vertical Speed field is invalid and is to be ignored,
 * 
 *  @param speedVertical
 *          - Vertical speed.
 *          - Units: Meters/second 
 * 
 *  @param heading_valid
 *          - Indicates whether the Heading field contains valid information.
 *          - 0x01 (TRUE) - Heading field is valid
 *          - 0x00 (FALSE) – Heading field is invalid and is to be ignored
 * 
 *  @param heading
 *          - Heading.
 *          - Units: Degrees, Range: 0 to 359.999
 * 
 * \note    None
 *
 */
typedef struct 
{
    uint64_t timestampUtc;
    double latitude;
    double longitude;
    float horUncEllipseSemiMinor;
    float horUncEllipseSemiMajor;
    float horUncEllipseOrientAzimuth;
    uint8_t speedHorizontal_valid;
    float speedHorizontal;
    uint8_t altitudeWrtEllipsoid_valid;
    float altitudeWrtEllipsoid;
    uint8_t vertUnc_valid;
    float vertUnc;
    uint8_t speedVertical_valid;
    float speedVertical;
    uint8_t heading_valid;
    float heading;
}QmiGeofencePosition_t;

/**
 * \ingroup loc
 * 
 *  Contain the parameters fo Geofence breach notification
 *
 *  @param  geofenceId
 *          - ID of the Geofence for which this notification was generated.
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  @param  breachType
 *          - The type of breach that generated this event.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_BREACH_TYPE_ENTERING (1) – Denotes that a client entered the Geofence
 *              - eQMI_LOC_GEOFENCE_BREACH_TYPE_LEAVING (2) – Denotes that a client left the Geofence
 *          - Bit to check in ParamPresenceMask - <B>0x02</B>
 * 
 *  @param pGeofencePosition
 *          - Geofence Position
 *          - Position of the client when it breached the Geofence. This TLV is included if the client configures the Geofence to
 *          - report position. The position is reported at the same confidence level that was specified in the Add Circular Geofence request.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  @param pBreachConfidence
 *          - Given a breach event, the confidence determines the probability that the breach happened at the Geofence boundary. 
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_CONFIDENCE_LOW (0x01) - Geofence engine indicates a breach with low confidence; 
 *                this setting results in lower power usage, and it can impact the yield because incorrect breach events can be sent
 *              - eQMI_LOC_GEOFENCE_CONFIDENCE_MED (0x02) - (Default) Geofence engine indicates a breach with medium confidence
 *              - eQMI_LOC_GEOFENCE_CONFIDENCE_HIGH (0x03) - Geofence engine indicates a breach with high confidence; 
 *                this setting results in higher power usage
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t geofenceId;
    uint32_t breachType;
    QmiGeofencePosition_t *pGeofencePosition;
    uint32_t *pBreachConfidence;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceBreachInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Breach Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceBreach_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceBreachInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters for Geofence Proximity notification
 *
 *  \param  proximityType
 *          - Geofence Breach Type
 *          - Valid values:
 *              - eQMI_LOC_GEOFENCE_PROXIMITY_TYPE_IN (1) - Denotes that a client is in proximity of the Geofence
 *              - eQMI_LOC_GEOFENCE_PROXIMITY_TYPE_OUT (2) - Denotes that a client is out of proximity of the Geofence
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  \param  geofenceId
 *          - Identifier of the Geofence that is in proximity to the handset.
 *          - Bit to check in ParamPresenceMask - <B>0x02</B>
 * 
 *  \param pContextId
 *          - Geofence Context ID 
 *          - Identifier for the context of the Geofence to which the handset is in proximity. 
 *          - A single Geofence may be associated with different contexts.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t proximityType;
    uint32_t geofenceId;
    uint32_t *pContextId;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceProximityInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Proximity Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceProximity_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceProximityInd_t *pOutput
);

/**
 * \ingroup loc
 * Qmi Loc Add Circular Geofence Req
 *
 *  \param  latitude
 *          - Latitude of the center of the Geofence.
 *
 *	\param longtitude
 *			- Longitude of the center of the Geofence.
 *
 *	\param radius
 *			- Radius of the circular Geofence in meters.
 */
typedef struct 
{
   double latitude;
   double longtitude;
   uint32_t  radius;
}CircularGeofenceArguments_t;

/**
 * \ingroup loc
 * 
 * Qmi Loc Add Circular Geofence Req
 *
 *  \param  transactionId
 *          - Transaction ID.
 *			- Identifies the transaction. The transaction ID is returned in the Add Circular Geofence indication.
 *
 *	\param circularGeofenceArguments
 *			- Circular Geofence Arguments.
 *			- see \ref CircularGeofenceArguments_t
 *
 *	\param breachMask
 *          - Breach Event Mask
 *			- Specifies the breach events in which the client is interested.
 *            - Valid values:
 *              - 0x01 – GEOFENCE_BREACH_ENTERING_MASK
 *              - 0x02 – GEOFENCE_BREACH_LEAVING_MASK
 *
 *	\param includePosition
 *			- Specifies whether the Geofence engine is to include the position in a breach event.
 *           - Valid values:
 *              - 0x01 (TRUE) - Position is reported with the breach event
 *              - 0x00 (FALSE) - Position is not reported with the breach event.
 * 
 *  \param pResponsiveness
 *          - Responsiveness
 *          - Specifies the rate of detection for a Geofence breach. This may impact the time lag between the actual breach event and when it is reported.
 *          - This parameter has power implications and must be fine-tuned to optimize power savings.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_LOW (0x01) - The Geofence is monitored for a breach at a low rate of 15 minutes. 
 *                The gap between the actual breach and the time it is reported is higher. This setting results in lower power usage.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_MED (0x02) - The Geofence is monitored for a breach at a medium rate of 2 minutes. This is the default setting.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_HIGH (0x03) - The Geofence is monitored for a breach at a high rate of 10 seconds. 
 *                The gap between the actual breach and the time it is reported is low. This results in higher power usage.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_ULTRA_HIGH (0x04) - The Geofence is monitored for a breach at a very high rate of 1 second.
 *                The gap between the actual breach and the time it is reported is very low. This results in very high power usage. 
 *                This setting must be avoided whenever possible because of the drastic power implications.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_CUSTOM (0x05) - The Geofence is monitored for a breach at a user defined rate.
 *                The gap between the actual breach and the time it is reported depends on the user setting. The power implication is inversely proportional 
 *                to the responsiveness value set by the user. The higher the responsiveness value, the lower the power implications, and vice-versa.
 * 
 *  \param pConfidence
 *          - Confidence
 *          - Given a breach event, the confidence determines the probability that the breach happened at the Geofence boundary.
 *          - This parameter has power implications and must be fine-tuned to optimize power savings.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_CONFIDENCE_LOW (0x01) - Geofence engine indicates a breach with low confidence; this setting results in lower power usage,
 *                  and it can impact the yield because incorrect breach events can be sent 
 *              - eQMI_LOC_GEOFENCE_CONFIDENCE_MED (0x02) - (Default) Geofence engine indicates a breach with medium confidence
 *              - eQMI_LOC_GEOFENCE_CONFIDENCE_HIGH (0x03) - Geofence engine indicates a breach with high confidence; this setting results in higher power usage
 * 
 *  \param  pCustomResponsivenessValue
 *          - Custom Responsiveness Value
 *          - Specifies in seconds the user-defined rate of detection for a Geofence breach. This may impact the time lag between the actual breach event and when it is reported.
 *          - The gap between the actual breach and the time it is reported depends on the user setting. The power implication is inversely proportional to the responsiveness value set by the user.
 *          - The higher the responsiveness value, the lower the power implications, and vice-versa. If this field is set, the responsiveness is always treated as
 *          - eQMI_LOC_GEOFENCE_RESPONSIVENESS_CUSTOM. The minimum value supported in this field is 1 second, and the maximum value is 65535 seconds.
 *          - An error is returned if an attempt is made to set this to an unsupported value. If this field is set, the responsiveness is always treated as
 *          - eQMI_LOC_GEOFENCE_RESPONSIVENESS_CUSTOM, which means that the other responsiveness types, such as eQMI_LOC_GEOFENCE_RESPONSIVENESS_LOW, 
 *          - eQMI_LOC_GEOFENCE_RESPONSIVENESS_MEDIUM, eQMI_LOC_GEOFENCE_RESPONSIVENESS_HIGH, and eQMI_LOC_GEOFENCE_RESPONSIVENESS_ULTRA_HIGH are all disregarded.
 *          - If this field is not set, the responsiveness is treated as eQMI_LOC_GEOFENCE_RESPONSIVENESS_LOW, eQMI_LOC_GEOFENCE_RESPONSIVENESS_MEDIUM,
 *          - eQMI_LOC_GEOFENCE_RESPONSIVENESS_HIGH, or eQMI_LOC_GEOFENCE_RESPONSIVENESS_ULTRA_HIGH.
 * 
 *  \param pDwellTime
 *          - Dwell Time of Geofence
 *          - Dwell time is the time in seconds a user spends in the Geofence before a dwell event is sent.
 * 
 *  \param pDwellTypeMask
 *          - Type of dwell event in which the user is interested.
 *           - Valid values:
 *              - QMI_LOC_GEOFENCE_DWELL_TYPE_INSIDE_MASK (0x01) - If this mask is set, a dwell event is reported when a user dwells inside the Geofence for a specified time
 *              - QMI_LOC_GEOFENCE_DWELL_TYPE_OUTSIDE_MASK (0x02) - If this mask is set, a dwell event is reported when a user dwells outside the Geofence for a specified time
 */
typedef struct 
{
   uint32_t                     transactionId;
   CircularGeofenceArguments_t  circularGeofenceArguments;
   uint8_t	                    breachMask;
   uint8_t                      includePosition;
   uint32_t	                    *pResponsiveness;
   uint32_t                     *pConfidence;
   uint32_t                     *pCustomResponsivenessValue;
   uint32_t                     *pDwellTime;
   uint8_t                      *pDwellTypeMask;
}pack_loc_GeofenceAddCircularReq_t;

/**
 * \ingroup loc
 *
 * Pack Geofence Add Circular 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceAddCircular(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceAddCircularReq_t   *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceAddCircularReq_t;

/**
 * \ingroup loc
 *
 * Unpack Sets satellite constellations of interest for reporting
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_pack_loc_GeofenceAddCircular(
	uint8_t *pResp,
	uint16_t respLen,
	unpack_loc_GeofenceAddCircularReq_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters for Geofence Add Circular notification
 *
 *  \param  status
 *          - Add Circular Geofence Status
 *          - Status of the Add Circular Geofence request.
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  \param  pTransactionId
 *          - Transaction ID that was specified in the Add Circular Geofence request. This parameter is always present when the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param pGeofenceId
 *          - Geofence ID 
 *          - Geofence identifier allocated by the engine. The client must include this identifier in all transactions pertaining to this Geofence.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pTransactionId;
    uint32_t *pGeofenceId;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceAddCircularInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Add Circular Notification Ind unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceAddCircular_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceAddCircularInd_t *pOutput
);

/** 
 * \ingroup loc
 * 
 * Qmi Loc Add Circular Geofence Req
 *
 *  \param  geofenceId
 *          - Transaction ID.
 *			- Identifier for the Geofence that is to delete.
 *
 *	\param transactionId
 *			- Identifies the transaction. The QMI_LOC_DELETE_GEOFENCE_IND indication returns the transaction ID.
 *  */
typedef struct 
{
   uint32_t	geofenceId;
   uint32_t transactionId;

}pack_loc_GeofenceDeleteReq_t;

/**
 * \ingroup loc
 *
 * Pack Geofence Delete
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceDelete(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceDeleteReq_t   *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceDeleteResp_t;

/**
 * \ingroup loc
 * 
 *  Geofence Delete unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceDelete(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceDeleteResp_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters for Geofence Delete notification
 *
 *  \param  status
 *          - Delete Geofence Status
 *          - Status of the QMI_LOC_DELETE_GEOFENCE_REQ request.
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because  the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  \param pGeofenceId
 *          - Geofence ID 
 *          - Identifier for the Geofence that was deleted.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param  pTransactionId
 *          - Transaction ID that was specified in the Delete Geofence request. This parameter is always present when the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct 
{
    uint32_t status;
    uint32_t *pGeofenceId;
    uint32_t *pTransactionId;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceDeleteInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Delete Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceDelete_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceDeleteInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Qmi Loc Query Geofence Req
 *
 *  \param geofenceId
 *          - Geofence ID
 *          - Identifier for the Geofence that to query.
 * 
 *  \param  transactionId
 *          - Transaction ID.
 *			- Identifies the transaction. The Query Geofence indication returns the transaction ID.
 */
typedef struct 
{
   uint32_t geofenceId;
   uint32_t transactionId;

}pack_loc_GeofenceQueryReq_t;

/**
 * \ingroup loc
 *
 * Pack geofence Query
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceQuery(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceQueryReq_t   *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceQueryResp_t;

/**
 * \ingroup loc
 * 
 *  Geofence Query unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceQuery(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceQueryResp_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters for Geofence Query notification
 *
 *  \param  status
 *          - Delete Geofence Status
 *          - Status of the QMI_LOC_DELETE_GEOFENCE_REQ request.
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because  the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
  *          - Bit to check in ParamPresenceMask - <B>0x01</B>
* 
 *  \param geofenceId
 *          - Geofence ID 
 *          - Identifier for the Geofence that was deleted.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param  transactionId
 *          - Transaction ID that was specified in the Delete Geofence request. This parameter is always present when the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  \param  pGeofenceOrigin
 *          - Originator of the Geofence.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_ORIGIN_NETWORK (1) - Geofence was initiated by a network-initiated client
 *              - eQMI_LOC_GEOFENCE_ORIGIN_DEVICE (2) - Geofence was initiated by the device
  *          - Bit to check in ParamPresenceMask - <B>0x12</B>
* 
 *  \param  pPosWrtGeofence
 *          - Indicates whether the client is currently inside or outside the Geofence.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_POSITION_INSIDE (0x01) - Position is inside a Geofence
 *              - eQMI_LOC_GEOFENCE_POSITION_OUTSIDE (0x02) - Position is outside a Geofence
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>
 * 
 *  \param  pCircularGeofenceArguments
 *          - Circular Geofence Parameters
 *          - See \ref CircularGeofenceArguments_t
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>
 * 
 *  \param  pGeofenceState
 *          - Geofence State
 *          - Specifies whether to actively monitor the Geofenced.
 *            - Valid values:
 *              - eQMI_LOC_GEOFENCE_STATE_ACTIVE (1) - Geofence is being actively monitored
 *              - eQMI_LOC_GEOFENCE_STATE_SUSPEND (2) - Geofence monitoring is suspended
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>
 * 
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pGeofenceId;
    uint32_t *pTransactionId;
    uint32_t *pGeofenceOrigin;
    uint32_t *pPosWrtGeofence;
    CircularGeofenceArguments_t *pCircularGeofenceArguments;
    uint32_t *pGeofenceState;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceQueryInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Query Indication unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceQuery_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceQueryInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Qmi Loc Edit Geofence Req
 *
 *  \param  geofenceId
 *          - Goefence ID.
 *			- Identifier for the Geofence to edit..
 *  
 *  \param  transactionId
 *          - Transaction ID.
 *			- Transaction ID specified in the Edit Geofence request. This parameter is always present when the status field is set to SUCCESS.
 * 
 *  \param pGeofenceState
 *          - Specifies whether to actively monitor the Geofence.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_STATE_ACTIVE (1) - Geofence is being actively monitored
 *              - eQMI_LOC_GEOFENCE_STATE_SUSPEND (2) - Geofence monitoring is suspended
 * 
 *  \param pBreachMask
 *          - Breach Event Mask
 *          - Specifies the breach events in which the client is interested.
 *           - Valid values:
 *              - 0x01 - GEOFENCE_BREACH_ENTERING_MASK
 *              - 0x02 - GEOFENCE_BREACH_LEAVING_MASK
 * 
 *  \param pResponsiveness
 *          - Responsiveness
 *          - Specifies the rate of detection for a Geofence breach. This may impact the time lag between the actual breach event and when it is reported.
 *          - This parameter has power implications and must be fine-tuned to optimize power savings.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_LOW (0x01) - The Geofence is monitored for a breach at a low rate of 15 minutes. 
 *                The gap between the actual breach and the time it is reported is higher. This setting results in lower power usage.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_MED (0x02) - The Geofence is monitored for a breach at a medium rate of 2 minutes. This is the default setting.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_HIGH (0x03) - The Geofence is monitored for a breach at a high rate of 10 seconds. 
 *                The gap between the actual breach and the time it is reported is low. This results in higher power usage.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_ULTRA_HIGH (0x04) - The Geofence is monitored for a breach at a very high rate of 1 second.
 *                The gap between the actual breach and the time it is reported is very low. This results in very high power usage. 
 *                This setting must be avoided whenever possible because of the drastic power implications.
 *              - eQMI_LOC_GEOFENCE_RESPONSIVENESS_CUSTOM (0x05) - The Geofence is monitored for a breach at a user defined rate.
 *                The gap between the actual breach and the time it is reported depends on the user setting. The power implication is inversely proportional 
 *                to the responsiveness value set by the user. The higher the responsiveness value, the lower the power implications, and vice-versa.
 */
typedef struct 
{
   uint32_t geofenceId;
   uint32_t transactionId;
   uint32_t *pGeofenceState;
   uint8_t  *pBreachMask;
   uint32_t *pResponsiveness;

}pack_loc_GeofenceEditReq_t;

/**
 * \ingroup loc
 *
 * Pack geofence Edit
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceEdit(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceEditReq_t   *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceEditResp_t;

/**
 * \ingroup loc
 * 
 *  Geofence Edit unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceEdit(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceEditResp_t *pOutput
);

/**
 * \ingroup cbk
 * 
 *  Contain the parameters for Geofence Delete notification
 *
 *  \param  status
 *          - Delete Geofence Status
 *          - Status of the QMI_LOC_EDIT_GEOFENCE_REQ request.
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because  the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  \param pGeofenceId
 *          - Geofence ID 
 *          - Identifier for the Geofence that was edited.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param pTransactionId
 *          - Transaction ID
 *          - Identifies the transaction. The transaction ID is specified in the Edit Geofence request.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  \param pFailedParams
 *          - Failed Parameters
 *          - Specified only when the status is not set to SUCCESS. If the mask corresponding to a field is set, it indicates that the Geofence parameter could not be edited.
 *           - Valid values:
 *              - 0x00000001 – GEOFENCE_PARAM_MASK_GEOFENCE_STATE
 *              - 0x00000002 – GEOFENCE_PARAM_MASK_BREACH_MASK
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pGeofenceId;
    uint32_t *pTransactionId;
    uint32_t *pFailedParams;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceEditInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Edit Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceEdit_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceEditInd_t *pOutput
);

/**
 * Qmi Loc NI Get Geofence ID List Req
 *
 *  \param  transactionId
 *          - Transaction ID.
 *			- Identifies the transaction. The same transaction ID is returned in the Get NI Geofence ID List indication.
 */
typedef struct 
{
   uint32_t transactionId;

}pack_loc_GetNiGeofenceIdListReq_t;

/**
 * \ingroup loc
 *
 * Pack geofence Edit
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GetNiGeofenceIdList(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GetNiGeofenceIdListReq_t *reqArg
);

typedef unpack_result_t unpack_loc_GetNiGeofenceIdListReq_t;

/**
 * \ingroup loc
 * 
 * Unpack inject UTC time.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GetNiGeofenceIdList(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GetNiGeofenceIdListReq_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters for NI Geofence ID List
 *
 *  \param  niGeofenceIdList_len
 *          - Number of sets of the niGeofenceIdList.
 * 
 *  \param  niGeofenceIdList
 *          - List containing the NI Geofence IDs.
 *          - Type: Array of unsigned 32-bit integers 
 *          - Maximum NI Geofence ID List length: 16
 */
typedef struct 
{
    uint8_t niGeofenceIdList_len;
    uint32_t niGeofenceIdList[16];
}QmiGeofenceNiGeofenceIDList_t;

/**
 * \ingroup loc
 * 
 *  Contain the parameters for NI Geofence Get ID List notification
 *
 *  \param status
 *          - Get NI Geofence ID List Status
 *          - Status of the Get NI Geofence ID List request.
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 * 
 *  \param  pTransactionId
 *          - Transaction ID that was specified in the Delete Geofence request. This parameter is always present when the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param  pGeofenceNiGeofenceIDList
 *          - NI Geofence ID List
 *          - See \ref QmiGeofenceNiGeofenceIDList
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  \param  Tlvresult
 *          - unpack result
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pTransactionId;
    QmiGeofenceNiGeofenceIDList_t *pGeofenceNiGeofenceIDList;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceNiGetIdListInd_t;

/**
 * \ingroup loc
 * 
 * Get Geofence NI List Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceNiGetIdList_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceNiGetIdListInd_t *pOutput
);

/**
 * Geofence Motion State ans Speed Information.
 *
 *  \param motionState
 *          - Motion state for which information is being configured.
 *              - eQMI_LOC_MOTION_STATE_UNKNOWN (0) - Device state is not known
 *              - eQMI_LOC_MOTION_STATE_STATIONARY (1) - Device state is Stationary
 *              - eQMI_LOC_MOTION_STATE_IN_MOTION (2) - Device state is In Motion
 * 
 *  \param motionStateSpeed
 *          - Motion state speed in milliseconds.
 *          - These are positive floating values. The state speed must be configured carefully.
 *          - Very low speed configuration for a state may result in missing Geofence breaches in some scenarios.
 *          - Typical motion state speeds:
 *              - Stationary speed - 0 meters/sec
 *              - Fiddle speed - 0 meters/sec
 *              - Walk speed - 3 meters/sec
 *              - Run speed - 8 meters/sec
 *              - Drive speed - 56 meters/sec
 */
typedef struct
{
    uint32_t motionState;
    float motionStateSpeed;
}GeofenceMotionStateSpeedInfo_t;

/**
 * Geofence Motion State Information Motion state information (for example, motion state speed) that the Geofence engine is to use.
 *
 *	\param motionStateInfo_len
 *			- Number of sets of the  and geofenceMotionStateSpeedList.
 *  \param geofenceMotionStateSpeedList
 *          - Motion state and speed information list.
 */
typedef struct
{
    uint8_t motionStateInfo_len;
    GeofenceMotionStateSpeedInfo_t *pGeofenceMotionStateSpeedList;
}GeofenceMotionInfo_t;

/**
 * Qmi Loc Set Geofence Engin Config Req
 *
 *	\param transactionId
 *			- Identifies the transaction. The QMI_LOC_DELETE_GEOFENCE_IND indication returns the transaction ID.
 *	\param pGnssUnavailableIndicationTimeout;
 *          - In a bad GNSS environment, this is the timeout after which the Geofence engine sends out a GNSS Unavailable indication.
 *          - The GNSS Unavailable indication is sent under the following conditions:
 *          - If gnssUnavailableIndicationTimeout is less than gnssPositionSessionTimeout, the GNSS Unavailable timeout indication is sent after gnssPositionSessionTimeout expires
 *          - If gnssPositionSessionTimeout is less than gnssUnavailableIndicationTimeout, the GNSS Unavailable timeout indication is sent after gnssUnavailableIndicationTimeout expires Type 
 *	\param pMaxGeofences 
 *          - Max Geofences Length Value
 *          - Identifies the maximum number of Geofences that the Geofence enginer can support. If this number is less than the currently deployed Geofences, this command fails.
 *          - If the command succeeds, the engine supports the maximum number of Geofences requested, provided there is enough memory to support that many Geofences.
 *          - Increasing this value to a very large number in a constrained memory environment might affect other modules negatively. 
 *          - This value is determined by phone manufacturers. The default value is 200.
 *	\param pEnableMotionDetectionSources
 *          - Enable Motion Detection Sources
 *          - Identifies the sources that the Geofence engine can enable for motion detection.
 *          - The sources of motion detection that the Geofence enginer enable are dependent on the platform. These sources are only set once at boot time, they are not
 *          - expected to change after that. Any attempt to set the value of the motion detection sources at runtime results in an undefined behavior.
 *          - Valid values:
 *          - QMI_LOC_MOTION_DETECTION_SOURCE_SENSORS (0x00000001) - Sensors are used for motion detection
 *          - QMI_LOC_MOTION_DETECTION_SOURCE_WIFI (0x00000002) - Wi-Fi is used for motion detection
 *          - QMI_LOC_MOTION_DETECTION_SOURCE_WWAN (0x00000004) - Wireless WAN is used for motion detection
 *	\param pEnableCpiUsage
 *          - Enable Coarse Position Injection Usage
 *          - Indicates whether the Geofence engine uses external Coarse Position Injection (CPI).
 *              - 0x01 (TRUE) - CPI is enabled (default)
 *              - 0x00 (FALSE) - CPI is disabled
 *	\param pGnssPositionSessionTimeout
 *          - GNSS Position QOS Session Timeout
 *          -Identifies the session timeout value (in seconds) for requesting a position in a bad GNSS environment.
 *           - Valid values:
 *              - If the gnssUnavailableIndicationTimeout value is less than gnssPositionSessionTimeout, in a bad GNSS environment,
 *              - the GNSS Unavailable timeout indication is sent after gnssPositionSessionTimeout expires.
 *              - If gnssPositionSessionTimeout is less than gnssUnavailableIndicationTimeout, in a bad GNSS environment,
 *              - the GNSS Unavailable timeout indication is sent after gnssUnavailableIndicationTimeout expires.              
 *	\param pGnssPositionMaxPuncAcceptable
 *          - GNSS Position Maximum Position Uncertainity Acceptable 
 *          - GNSS maximum position uncertainity in meters acceptable by the Geofence engine.
 *           - Valid values:
 *              - All positive values
 *	\param pMediumResponsivenessValue
 *          - Medium Responsiveness Value
 *          - Medium responsiveness value in seconds that the Geofence engine uses for all medium responsiveness Geofences in the Geofence engine.
 *            - Valid values:
 *              - Positive values (in seconds)
 *              - If the value is configured for less than 30 seconds, the value is set at 30 seconds
 *              - If the value is configured for more than 600 seconds, the value is set at 600 seconds
 *              - Default - The Geofence engine uses 120 seconds as the medium responsiveness value If the medium responsiveness value is changed,
 *              - the responsiveness of the existing medium responsiveness Geofence does not change until the next position fix, 
 *              - which is based on the previous medium responsiveness setting.
 *	\param pChalGnssEnvMinCpiWaitInterval
 *          - Challenging GNSS Environment Minimum CPI Wait Interval
 *          - Number of seconds that the Geofence engine is to wait between CPI requests in challenging a GNSS environment.
 *            - Valid values:
 *              - Positive values (in seconds)
 *	\param pGeofenceMotionStateInfo
 *          - Geofence Motion State Information Motion state information (for example, motion state speed) that the Geofence engine is to use.
 */
typedef struct 
{
    uint32_t transactionId;
    uint32_t *pGnssUnavailableIndicationTimeout;
    uint32_t *pMaxGeofences; 
    uint32_t *pEnableMotionDetectionSources;
    uint8_t *pEnableCpiUsage;
    uint32_t *pGnssPositionSessionTimeout;
    uint32_t *pGnssPositionMaxPuncAcceptable;
    uint32_t *pMediumResponsivenessValue;
    uint32_t *pChalGnssEnvMinCpiWaitInterval;
    GeofenceMotionInfo_t *pGeofenceMotionStateInfo;
}pack_loc_GeofenceSetEngineConfigReq_t;

/**
 * \ingroup loc
 *
 * Pack geofence Edit
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceSetEngineConfig(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceSetEngineConfigReq_t *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceSetEngineConfigResp_t;

/**
 * \ingroup loc
 * 
 * Unpack inject UTC time.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceSetEngineConfig(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceSetEngineConfigResp_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Qmi Loc Get Geofence Engine Configuration Req
 *
 *  \param  transactionId
 *          - Transaction ID.
 *			- Identifies the transaction. The transaction ID is returned with the Get Geofence Engine Configuration indication.
 */
typedef struct 
{
   uint32_t transactionId;

}pack_loc_GeofenceGetEngineConfigReq_t;

/**
 * \ingroup loc
 *
 * Pack geofence Edit
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceGetEngineConfig(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceGetEngineConfigReq_t *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceGetEngineConfigResp_t;

/**
 * \ingroup loc
 * 
 * Unpack inject UTC time.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceGetEnginConfig(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceGetEngineConfigResp_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters for Geofence Set EnginE Configuration notification
 *
 *  \param  status
 *          - Set Geofence Engine Configuration Status.
 *          - Status of the Set Geofence Engine Configuration request.
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because  the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  \param  pTransactionId
 *          - Transaction ID that was specified in the Set Geofence Configuration request. This parameter is always present if the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param Tlvresult
 *        - Unpack result.
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pTransactionId;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceSetEngineConfigInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Set Engine Configuration Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceSetEngineConfig_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceSetEngineConfigInd_t *pOutput
);

/**
 * \ingroup cbk
 * 
 *  Contain the parameters for Geofence get EnginE Configuration notification
 *
 *  \param  status
 *          - Set Geofence Engine Configuration Status.
 *          - Status of the Set Geofence Engine Configuration request.
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because  the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  \param  pTransactionId
 *          - Transaction ID that was specified in the Get Geofence Engine Configuration request.
 *          - This parameter is always present if the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  \param pGnssUnavailableIndicationTimeout
 *          - In a bad GNSS environment, the timeout after which the Geofence engine sends out a GNSS unavailable indication. 
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  \param pMaxGeofences
 *          - Identifies the maximum number of Geofences that are currently supported in the Geofence engine.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 *  \param pEnabledMotionDetectionSources
 *          - Identifies the sources that are currently enabled for motion detection by the Geofence engine.
 *           - Valid values:
 *              - QMI_LOC_MOTION_DETECTION_SOURCE_SENSORS (0x00000001) - Sensors are used for motion detection
 *              - QMI_LOC_MOTION_DETECTION_SOURCE_WIFI (0x00000002) - Wi-Fi is used for motion detection
 *              - QMI_LOC_MOTION_DETECTION_SOURCE_WWAN (0x00000004) - Wireless WAN is used for motion detection
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>
 * 
 *  \param pEnabledCpiUsage
 *          - Enabled for CPI Position Injection Usage
 *          - Indicates whether CPI usage is enabled.
 *              - 0x01 (TRUE) – CPI usage is enabled
 *              - 0x00 (FALSE) – CPI usage is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>
 * 
 *  \param Tlvresult
 *        - Unpack result.
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pTransactionId;
    uint32_t *pGnssUnavailableIndicationTimeout;
    uint32_t *pMaxGeofences;
    uint32_t *pEnabledMotionDetectionSources;
    uint8_t *pEnabledCpiUsage;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceGetEngineConfigInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Get Engine Configuration Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceGetEngineConfig_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceGetEngineConfigInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Qmi Loc Geofence Add Context Req
 *
 *  \param  ssid_len
 *          - Number of sets of the ssid
 *  \param ssid
 *          - NULL-terminated SSID string of the Wi-Fi AP. Its maximum length according to the ASCII standard is 32 octets.
 */
typedef struct 
{
   uint8_t ssid_len;
   uint8_t ssid[32];
}Geofence_SsidString_t;

/**
 * \ingroup loc
 * 
 * Qmi Loc Geofence WIFI AP SSID String
 *
 *  \param  wifiApSsidInfo_len
 *          - Number of sets of the ssidString
 * 
 *  \param pSsidString
 *          - See \ref Geofence_SsidString_t
 */
typedef struct 
{
    uint8_t wifiApSsidInfo_len;
    Geofence_SsidString_t *pSsidString;
}Geofence_WifiApSsidStringList_t;


/**
 * \ingroup loc
 * 
 * Geofence WIFI AP MAC String
 *
 *  \param  wifiApMacAddressList_len
 *          - Number of sets of the following wifiApMacAddress
 * 
 *  \param wifiApMacAddress
 *          - MAC address of the Wi-Fi AP. 
 */
typedef struct 
{
    uint8_t wifiApMacAddressList_len;
    uint8_t wifiApMacAddress[6];
}Geofence_WifiApMacStringList_t;

/**
 * \ingroup loc
 * 
 * Geofence TDSCDMA Cell ID List for the Geofence Identifies the TDSCDMA cell on which the device is currently camped.
 *
 *  \param  mcc
 *          - TDSCDMA mobile country code.
 * 
 *  \param mnc
 *          - TDSCDMA mobile network code.
 * 
 *  \param cid
 *          - TDSCDMA cell identity.
 * 
 *  \param lac
 *          - TDSCDMA location area code.
 */
typedef struct 
{
    uint32_t mcc;
    uint32_t mnc;
    uint32_t cid;
    uint32_t lac;
}Geofence_TDSCDMACellIDList_t;

/**
 * \ingroup loc
 * 
 * WCDMA Cell ID List for the Geofence Identifies the WCDMA cell on which the device is currently camped.
 *
 *  \param  mcc
 *          - TDSCDMA mobile country code.
 * 
 *  \param mnc
 *          - TDSCDMA mobile network code.
 * 
 *  \param cid
 *          - TDSCDMA cell identity.
 */
typedef struct 
{
    uint32_t mcc;
    uint32_t mnc;
    uint32_t cid;
}Geofence_WCDMACellID_t;

/**
 * \ingroup loc
 * 
 * WCDMA Cell ID List for the Geofence Identifies the WCDMA cell on which the device is currently camped.
 *
 *  \param  wcdmaCellIDList_len
 *          - Number of sets of the wcdmaCellID.
 * 
 *  \param pWcdmaCellID
 *          - See \ref Geofence_WCDMACellID_t.
 * 
 */
typedef struct 
{
    uint8_t wcdmaCellIDList_len;
    Geofence_WCDMACellID_t *pWcdmaCellID;
}Geofence_WCDMACellIDList_t;

/**
 * \ingroup loc
 * 
 * GSM Cell ID
 *
 *  \param  mcc
 *          - GSM mobile country code.
 * 
 *  \param mnc
 *          - GSM mobile network code.
 * 
 *  \param lac
 *          - GSM location area code.
 * 
 *  \param cid
 *          - GSM cell identification.
 * 
 */
typedef struct 
{
    uint32_t mcc;
    uint32_t mnc;
    uint32_t lac;
    uint32_t cid;
}Geofence_GSMCellID_t;

/**
 * \ingroup loc
 * 
 * GSM Cell ID List for the Geofence Identifies the GSM cell on which the device is currently camped.
 *
 *  \param  gsmCellIDList_len
 *          - Number of sets of the gsmCellID.
 * 
 *  \param pGsmCellID
 *          - See \ref Geofence_GSMCellID_t.
 * 
 */
typedef struct 
{
    uint8_t gsmCellIDList_len;
    Geofence_GSMCellID_t *pGsmCellID;
}Geofence_GSMCellIDList_t;

/**
 * \ingroup loc
 * 
 * IBeacon List of the Geofence
 *
 *  \param  uuid_len
 *          - Number of sets of the uuid.
 * 
 *  \param uuid
 *          - NULL-terminated IBeacon identifier string; a 128-bit value.
 * 
 *  \param majorNumber
 *          - IBeacon major number.
 * 
 *  \param minorNumber
 *          - IBeacon minor number.
 */
typedef struct 
{
    uint8_t uuid_len;
    uint8_t uuid[16];
    uint32_t majorNumber;
    uint32_t minorNumber;
}Geofence_IBeacon_t;

/**
 * \ingroup loc
 * 
 * GSM Cell ID List for the Geofence Identifies the GSM cell on which the device is currently camped.
 *
 *  \param  iBeaconList_len
 *          - Number of sets of the iBeacon.
 * 
 *  \param pIBeacon
 *          - See \ref Geofence_IBeacon_t.
 * 
 */
typedef struct 
{
    uint8_t iBeaconList_len;
    Geofence_IBeacon_t *pIBeacon;
}Geofence_IBeaconList_t;

/**
 * \ingroup loc
 * 
 * Qmi Loc Geofence Add Context Req
 *
 *  \param  transactionId
 *          - Transaction ID.
 *			- Identifies the transaction. The transaction ID is returned in the Add Geofence Context indication.
 *
 *	\param pGeofenceId
 *			- Geofence ID.
 *			- Geofence identifier allocated by the engine. If the Geofence ID is not provided, a Geofence is created with an Area ID list
            - only (for example, Wi-Fi only list Geofence). If the Geofence ID is provided, the added list is used as assistance data to the existing Geofence.
 *
 *	\param pWifiApSsidStringList
 *          - Wi-Fi AP SSID String
 *          - The ordering of the Wi-Fi AP SSID list should match the Wi-Fi AP MAC address list when both are provided, that is,
 *          - the first element of the Wi-Fi AP SSID list must be the SSID of the AP whose MAC address is in the first element in the Wi-Fi AP MAC address, etc.
 *          - See \ref Geofence_WifiApSsidStringList_t
 *
 *	\param pWifiApMacStringList
 *			- Wi-Fi AP MAC Address List for the Geofence The ordering of the Wi-Fi AP SSID list should match the Wi-Fi AP MAC address list 
 *          - when both are provided, that is, the first element of the Wi-Fi AP SSID list must be the SSID of the AP whose MAC address is 
 *          - in the first element in the Wi-Fi AP MAC address, etc.
 *          - See \ref Geofence_WifiApMacStringList_t
 * 
 *  \param pTDSCDMACellIDList
 *          - TDSCDMA Cell ID List for the Geofence Identifies the TDSCDMA cell on which the device is currently camped.
 *          - See \ref Geofence_TDSCDMACellIDList_t
 * 
 *  \param pWcdmaCellIDList
 *          - WCDMA Cell ID List for the Geofence Identifies the WCDMA cell on which the device is currently camped.
 *          - See \ref Geofence_WCDMACellIDList_t
 * 
 *  \param  pGsmCellIDList
 *          - GSM Cell ID List for the Geofence Identifies the GSM cell on which the device is currently camped.
 *          - See \ref Geofence_GSMCellIDList_t
 * 
 *  \param pIBeaconList
 *          - IBeacon List of the Geofence
 *          - See \ref Geofence_IBeaconList_t 
 * 
 *  \param Tlvresult
 *        - Unpack result.
 */
typedef struct 
{
    uint32_t transactionId;
    uint32_t *pGeofenceId;
    Geofence_WifiApSsidStringList_t *pWifiApSsidStringList;
    Geofence_WifiApMacStringList_t *pWifiApMacStringList;
    Geofence_TDSCDMACellIDList_t *pTDSCDMACellIDList;
    Geofence_WCDMACellIDList_t *pWcdmaCellIDList;
    Geofence_GSMCellIDList_t *pGsmCellIDList;
    Geofence_IBeaconList_t *pIBeaconList;
    uint16_t Tlvresult;
}pack_loc_GeofenceAddContextReq_t;

/**
 * \ingroup loc
 *
 * Pack Add Geofence Context
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceAddContext(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceAddContextReq_t *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceAddContextResp_t;

/**
 * \ingroup loc
 * 
 * Unpack inject UTC time.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceAddContext(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceAddContextResp_t *pOutput
);

/**
 * \ingroup cbk
 * 
 *  Contain the parameters for Geofence Add Context notification
 *
 *  \param  status
 *          - Status of the Add Geofence Context Request
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 *
 *  \param  pTransactionId
 *          - Transaction ID
 *          - Transaction ID that was specified in the Add Geofence Context request. This parameter is always present if the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param pGeofenceId
 *          - Geofence ID 
 *          - Geofence identifier allocated by the engine. If the client specifies the Geofence ID during the Add Geofence Context request,
 *          -  the same ID is returned. If the client does not specify the Geofence ID during the Add Geofence Context request, 
 *          - a new Geofence ID is created by the Geofence engine and returned.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  \param pContextId
 *          - Geofence context ID allocated by the engine. The context ID is generated by the Geofence engine to identify the context for a particular Geofence ID.
 *          - The same Geofence ID may be associated with multiple contexts.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pTransactionId;
    uint32_t *pGeofenceId;
    uint32_t *pContextId;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceAddContextInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Add context Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceAddContext_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceAddContextInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Qmi Loc Geofence Add Context Req
 *
 *  \param  transactionId
 *          - Transaction ID.
 *			- Identifies the transaction. The transaction ID is returned in the Add Geofence Context indication.
 *
 *	\param pUtcTimeOfDay
 *			- UTC Timestamp of the Day.
 *
 *	\param pTemperature
 *          - The temperature of the day in degrees Fahrenheit
 */
typedef struct 
{
    uint32_t transactionId;
    uint64_t *pUtcTimeOfDay;
    uint32_t *pTemperature;
}pack_loc_GeofenceSetEngineContextReq_t;

/**
 * \ingroup loc
 *
 * Pack Set Geofence Engine Context
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceSetEngineContext(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceSetEngineContextReq_t *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceSetEngineContextResp_t;

/**
 * \ingroup loc
 * 
 * Unpack inject UTC time.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceSetEngineContext(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceSetEngineContextResp_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Contain the parameters for Set Geofence Engine Context notification
 *
 *  \param  status
 *          - Status of the Add Geofence Context Request
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *
 *  \param  pTransactionId
 *          - Transaction ID
 *          - Transaction ID that was specified in the Add Geofence Context request. This parameter is always present if the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pTransactionId;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceSetEngineContextInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Add context Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceSetEngineContext_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceSetEngineContextInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Qmi Loc Delete Geofence Context Req
 *
 *	\param  transactionId
 *			- Identifies the transaction. The transaction ID is returned in the QMI_LOC_DELETE_GEOFENCE_CONTEXT_IND indication.
 *
 *  \param  geofenceId
 *          - Geofence ID.
 *			- Identifies the Geofence whose context is to be deleted.
 *
 *  \param  pContextId
 *          - Context ID
 *          - Identifies the context associated with the Geofence to delete. If not specified, all contexts associated with this Geofence are deleted.
 *  */
typedef struct 
{
   uint32_t transactionId;
   uint32_t geofenceId;
   uint32_t *pContextId;

}pack_loc_GeofenceDeleteContextReq_t;

/**
 * \ingroup loc
 *
 * Pack Set Geofence Engine Context
 * 
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GeofenceDeleteContext(
	pack_qmi_t  *pCtx,
	uint8_t *pReqBuf,
	uint16_t *pLen,
	pack_loc_GeofenceDeleteContextReq_t *reqArg
);

typedef unpack_result_t unpack_loc_GeofenceDeleteContextResp_t;

/**
 * \ingroup loc
 * 
 * Unpack inject UTC time.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out]  pOutput     response unpacked
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceDeleteContext(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceDeleteContextResp_t *pOutput
);

/**
 * \ingroup cbk
 * 
 *  Contain the parameters for Delete Geofence Context notification
 *
 *  \param  status
 *          - Status of the Delete Geofence Context Request
 *           - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *
 *  \param  pTransactionId
 *          - Transaction ID
 *          - Transaction ID specified in the QMI_LOC_DELETE_GEOFENCE_CONTEXT_REQ request. This parameter is always present when the status field is set to SUCCESS.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param pGeofenceId
 *          - Geofence ID 
 *          - Identifier for the Geofence whose context was deleted.
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  \param pContextId
 *          - Identifier for the context of the Geofence that was deleted.
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 *  \param Tlvresult
 *        - Unpack result.
 * 
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t status;
    uint32_t *pTransactionId;
    uint32_t *pGeofenceId;
    uint32_t *pContextId;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceDeleteContextInd_t;

/**
 * \ingroup loc
 * 
 * Geofence delete context Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceDeleteContext_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceDeleteContextInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  \param idLow 
 *          - Contains the starting ID of the Geofence  in the range of the continuous range of Geofences that were breached at the same position. 
 * 
 *  \param idHigh
 *          - Contains the ending ID of the Geofence in the range of the continuous range of Geofences that were breached at the same position.
 */
typedef struct 
{
    uint32_t idLow;
    uint32_t idHigh;
}QmiGeofenceIdLH_t;

/**
 * \ingroup loc
 * 
 *  Geofence ID Continuous Each entry in the list contains the continuous range of Geofence IDs in which a client dwelled.
 *  This list does not overlap with the discrete Geofence ID list
 *
 *  \param  geofenceIdContinuousList_len
 *          - Number of sets of QmiGeofenceIdLH
 * 
 *  \param geofenceIdLH
 *          - see \ref QmiGeofenceIdLH_t 
 */
typedef struct 
{
    uint8_t geofenceIdContinuousList_len;
    QmiGeofenceIdLH_t *pGeofenceIdLH;
}QmiGeofenceId_t;

/**
 * \ingroup loc
 * 
 *  Geofence ID Discrete
 *
 *  \param  pGeofenceIdContinuousList_len
 *          - Number of sets of the geofenceIdDiscreteList
 * 
 *  \param geofenceIdDiscreteList
 *          - This list contains the Geofence IDs in which a client dwelled. This list does not overlap with the continuous Geofence ID list.
 */
typedef struct 
{
    uint8_t geofenceIdDiscreteList_len; 
    uint32_t *pGeofenceIdDiscreteList;
}GeofenceIdDiscrete_t;

/**
 * \ingroup loc
 * 
 *  Geofence ID Discrete
 *
 *  \param timestampUtc
 *          - UTC timestamp.
 *          - Units: Milliseconds since Jan. 1, 1970 80-NV720-17 
 *  \param latitude
 *          - Latitude (specified in WGS84 datum).
 *          - Type: Floating point, Units: Degrees
 *          - Range: -90.0 to 90.0
 *          - Positive values indicate northern latitude
 *          - Negative values indicate southern latitude
 *  \param longitude 8 Longitude (specified in WGS84 datum).
 *          - Type: Floating point, Units: Degrees
 *          - Range: -180.0 to 180.0
 *          - Positive values indicate eastern longitude
 *          - Negative values indicate western longitude
 *  \param horUncEllipseSemiMinor
 *          - Semi-minor axis of horizontal elliptical uncertainty.
 *          - Units: Meters
 *  \param horUncEllipseSemiMajor
 *          - Semi-major axis of horizontal elliptical uncertainty.
 *          - Units: Meters
 *  \param horUncEllipseOrientAzimuth
 *          - Azimuth
 *          - Elliptical horizontal uncertainty azimuth of orientation.
 *          - Units: Decimal degrees
 *          - Range: 0 to 180
 *  \param speedHorizontal_valid
 *          - Indicates whether the Horizontal speed field contains valid information.
 *          - 0x01 (TRUE) - Horizontal speed is valid
 *          - 0x00 (FALSE) - Horizontal speed is invalid and is to be ignored
 *  \param speedHorizontalg_Table_ProximityType
 *          - Horizontal speed.
 *          - Units: Meters/second
 *  \param altitudeWrtEllipsoid_valid 
 *          - Indicates whether the altitude field contains valid information.
 *          - 0x01 (TRUE) - Altitude field is valid
 *          - 0x00 (FALSE) - Altitude field is invalid and is to be ignored
 *  \param altitudeWrtEllipsoid
 *          - Altitude with respect to the WGS84 ellipsoid.
 *          - Units: Meters
 *          - Range: -500 to 15883
 *  \param vertUnc_valid
 *          - Indicates whether the Vertical Uncertainty field contains valid information.
 *          - 0x01 (TRUE) - Vertical Uncertainty field is valid
 *          - 0x00 (FALSE) - Vertical Uncertainty field is invalid and is to be ignored 
 *  \param vertUnc
 *          - Vertical uncertainty.
 *          - Units: Meters
 *  \param speedVertical_valid
 *          - Indicates whether the Vertical Speed field contains valid information.
 *          - 0x01 (TRUE) - Vertical Speed field is valid
 *          - 0x00 (FALSE) - Vertical Speed field is invalid and is to be ignored 
 *  \param speedVertical
 *          - Vertical speed.
 *          - Units: Meters/second
 *  \param heading_valid
 *          - Indicates whether the Heading field contains valid information.
 *          - 0x01 (TRUE) - Heading field is valid
 *          - 0x00 (FALSE) - Heading field is invalid and is to be ignored
 *  \param heading
 *          - Heading.
 *          - Units: Degrees
 *          - Range: 0 to 359.999
 */
typedef struct 
{
    uint64_t timestampUtc;
    double latitude;
    double longitude;
    float horUncEllipseSemiMinor;
    float horUncEllipseSemiMajor;
    float horUncEllipseOrientAzimuth;    
    uint8_t speedHorizontal_valid;
    float speedHorizontal;
    uint8_t altitudeWrtEllipsoid_valid;
    float altitudeWrtEllipsoid;
    uint8_t vertUnc_valid;
    float vertUnc; 
    uint8_t speedVertical_valid;
    float speedVertical;
    uint8_t heading_valid;
    float heading;
}GeofencePosition_t;

/**
 * \ingroup loc
 * 
 * Dilution of precision associated with this position.
 * 
 *  \param  PDOP
 *          - Position dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 *          - PDOP = square root of (HDOP2 + VDOP2)
 *  \param  HDOP
 *          - Horizontal dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 *  \param  VDOP
 *          - Vertical dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 */
typedef struct 
{
    float PDOP;
    float HDOP;
    float VDOP;
}DilutionOfPrecision_t;

/**
 * \ingroup loc
 * 
 * Expanded SVs Used to Calculate the Fix.
 * 
 *  \param expandedGnssSvUsedList_len
 *          - Number of sets of the expandedGnssSvUsedList
 * 
 *  \param expandedGnssSvUsedList
 *          - Var If the service reports expandedGnssSvUsedList, gnssSvUsedList is not reported. 
 *          - Each entry in the list contains the SV ID of a satellite used to calculate this position report. 
 *          - The following information is associated with each SV ID.
 *          - Range:
 *          - For GPS: 1 to 32
 *          - For GLONASS: 65 to 96
 *          - For QZSS: 193 to 197
 *          - For BDS: 201 to 237
 *          - For Galileo: 301 to 336
 *          - For NavIC: 401 to 414
 */
typedef struct 
{
    uint8_t expandedGnssSvUsedList_len;
    uint16_t *pExpandedGnssSvUsedList;
}ExpSVsUsedCalculateFix_t;

/**
 * \ingroup loc
 * 
 * Satellite Signal Types in the SVs Used list.
 * 
 *  \param gnssSvUsedSignalTypeList_len
 *          - Number of sets of the following gnssSvUsedSignalTypeList
 * 
 *  \param pGnssSvUsedSignalTypeList
 *          - Var Indicates the signal type of each satellite in expandedGnssSvUsedList.
 *          - The signal type list is aligned with the SVs in expandedGnssSvUsedList. 
 *          - Value 0 means invalid.
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1CA (0x00000001) – GPS L1CA RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1C (0x00000002) – GPS L1C RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L2C_L (0x00000004) – GPS L2C_L RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L5_Q (0x00000008) – GPS L5_Q RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G1 (0x00000010) – GLONASS G1 (L1OF) RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G2 (0x00000020) – GLONASS G2 (L2OF) RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E1_C (0x00000040) – Galileo E1_C RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5A_Q (0x00000080) – Galileo E5A_Q RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5B_Q (0x00000100) – Galileo E5B_Q RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1_I (0x00000200) – BeiDou B1_I RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1C (0x00000400) – BeiDou B1C RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2_I (0x00000800) – BeiDou B2_I RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_I (0x00001000) – BeiDou B2A_I RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1CA (0x00002000) – QZSS L1CA RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1S (0x00004000) – QZSS L1S RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L2C_L (0x00008000) – QZSS L2C_L RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L5_Q (0x00010000) – QZSS L5_Q RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_SBAS_L1_CA (0x00020000) – SBAS L1_CA RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_NAVIC_L5 (0x00040000) – NavIC L5 RF band
 *          - QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_Q (0x00080000) – BeiDou B2A_Q RF band
 */
typedef struct 
{
    uint8_t gnssSvUsedSignalTypeList_len;
    uint64_t *pGnssSvUsedSignalTypeList;
}SatelliteSignalTypes_t;

/**
 * \ingroup loc
 * 
 * SVs Used to Calculate the Fix.
 * 
 *  \param gnssSvUsedList_len
 *          - Number of sets of the gnssSvUsedList
 * 
 *  \param pGnssSvUsedList
 *          - Var Each entry in the list contains the SV ID of a satellite used for calculating this position report.
 *          - The following information is associated with each SV ID:
 *          - Range:
 *          - For GPS: 1 to 32
 *          - For GLONASS: 65 to 96
 *          - For SBAS: 120 to 158 and 183 to 191
 *          - For QZSS: 193 to 197
 *          - For BDS: 201 to 237
 *          - For Galileo: 301 to 336
 *          - For NavIC: 401 to 414
 */
typedef struct 
{
    uint8_t gnssSvUsedList_len;
    uint16_t *pGnssSvUsedList;
}SVsUsedCalculateFix_t;

/**
 * \ingroup loc
 * 
 * Extended Dilution of Precision Dilution of precision associated with this position.
 * 
 *  \param PDOP
 *          - Position dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 *          - PDOP = square root of (HDOP2 + VDOP2)
 *  \param HDOP
 *          - Horizontal dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 *  \param VDOP
 *          - Vertical dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 *  \param GDOP
 *          - Geometric dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 *  \param TDOP
 *          - Time dilution of precision.
 *          - Range: 0 (highest accuracy) to 50 (lowest accuracy)
 */
typedef struct 
{
    float PDOP;
    float HDOP;
    float VDOP;
    float GDOP;
    float TDOP;
}ExtDilutionOfPrecision_t;

/**
 * \ingroup loc
 * 
 *  Notifies the control point of a Geofence dwell event by batching all the Geofences that were dwelled in.
 *
 * \param pDwellType
 *          - Geofence Dwell Type
 *          - Type of dwell event generated.
 *           - Valid values:
 *              - eQMI_LOC_GEOFENCE_DWELL_TYPE_INSIDE (1) - Denotes that a client dwelled inside the Geofence
 *              - eQMI_LOC_GEOFENCE_DWELL_TYPE_OUTSIDE (2) – Denotes that a client dwelled outside the Geofence
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  \param  pGeofenceId
 *          - Geofence ID Continuous Each entry in the list contains the continuous range of Geofence IDs in which a client dwelled.
 *          - This list does not overlap with the discrete Geofence ID list.
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param pGeofenceIdDiscrete
 *          - Geofence ID Discrete
 *          - see \ref GeofenceIdDiscrete 
 *          - Bit to check in ParamPresenceMask - <B>0x11</B>
 * 
 *  \param pGeofencePosition
 *          - Geofence Position The latest position calculated by the Geofence engine when the dwell notification is sent.
 *          - See \ref GeofencePosition
 *          - Bit to check in ParamPresenceMask - <B>0x12</B>
 * 
 *  \param pHeadingUnc 
 *          - Heading uncertainty.
 *          - Units: Degrees
 *          - Range: 0 to 359.999
 *          - Bit to check in ParamPresenceMask - <B>0x13</B>
 * 
 *  \param pVertUnc
 *          - Vertical uncertainty.
 *          - Units: Meters
 *          - Bit to check in ParamPresenceMask - <B>0x14</B>
 * 
 *  \param pSpeedUnc
 *          - 3-D speed uncertainty.
 *          - Units: Meters/second
 *          - Bit to check in ParamPresenceMask - <B>0x15</B>
 * 
 *  \param pHorConfidence
 *          - Horizontal uncertainty confidence.
 *          - Units: Percent
 *          - Range: 0 to 99
 *          - Bit to check in ParamPresenceMask - <B>0x16</B>
 * 
 *  \param pVertConfidence 
 *          - Vertical uncertainty confidence.
 *          - Units: Percent
 *          - Range: 0 to 99
 *          - Bit to check in ParamPresenceMask - <B>0x17</B>
 * 
 *  \param pDilutionOfPrecision
 *          - Dilution of Precision
 *          - Bit to check in ParamPresenceMask - <B>0x18</B>
 * 
 *  \param pSVsUsedCalculateFix
 *          - SVs Used to Calculate the Fix.
 *          - See \ref SVsUsedCalculateFix
 *          - Bit to check in ParamPresenceMask - <B>0x19</B>
 * 
 *  \param pExtDilutionOfPrecision
 *          - Extended Dilution of Precision Dilution of precision associated with this position
 *          - See \ref ExtDilutionOfPrecision
 *          - Bit to check in ParamPresenceMask - <B>0x1A</B>
 * 
 *  \param pExpSVsUsedCalculateFix
 *          - Expanded SVs
 *          - See \ref ExpSVsUsedCalculateFix
 *          - Bit to check in ParamPresenceMask - <B>0x1B</B>
 * 
 *  \param pSatelliteSignalTypes
 *          - Satellite Signal Types in the SVs Used list
 *          - See \ref SatelliteSignalTypes
 *          - Bit to check in ParamPresenceMask - <B>0x1C</B>
 * 
 * \param Tlvresult
 *        - Unpack result.
 * 
 * \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct 
{
    uint32_t *pDwellType;
    QmiGeofenceId_t *pGeofenceId;
    GeofenceIdDiscrete_t *pGeofenceIdDiscrete;
    GeofencePosition_t *pGeofencePosition; 
    float *pHeadingUnc;
    float *pVertUnc;
    float *pSpeedUnc;
    uint8_t *pHorConfidence;
    uint8_t *pVertConfidence;
    DilutionOfPrecision_t *pDilutionOfPrecision;
    SVsUsedCalculateFix_t *pSVsUsedCalculateFix;
    ExtDilutionOfPrecision_t *pExtDilutionOfPrecision;
    ExpSVsUsedCalculateFix_t *pExpSVsUsedCalculateFix;
    SatelliteSignalTypes_t *pSatelliteSignalTypes;
    uint16_t Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_GeofenceBatchedDwellInd_t;

/**
 * \ingroup loc
 * 
 * Geofence Batched Dwell Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GeofenceBatchedDwell_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GeofenceBatchedDwellInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains LOC Event GNSS Constell Report Configuration Indication
 *
 *  \param  status
 *          - Valid values:
 *             - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *             - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of
 *               a general failure
 *             - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is
 *               not supported
 *             - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because
 *               it contained invalid parameters
 *             - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine
 *               is busy
 *             - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone
 *               is offline
 *             - eQMI_LOC_TIMEOUT (6) - Request failed because it timed out
 *             - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because
 *               an undefined configuration was requested
 *             - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because
 *               the engine could not allocate sufficient memory for the request
 *             - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because
 *               the maximum number of Geofences are already programmed
 *             - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed
 *               because of an XTRA version-based file format check failure
 *             - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>1</B>
 *
 *  \param  Tlvresult
 *          - unpack result
 *
 *  \param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct{
    uint32_t                    status;
    uint16_t                    Tlvresult;
    swi_uint256_t               ParamPresenceMask;
}unpack_loc_SetGnssConstellReportConfig_Ind_t;

/**
 * \ingroup loc
 * 
 * Loc Set GNSS Constellations Report Configuration Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetGnssConstellReportConfig_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetGnssConstellReportConfig_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 * GNSS Receiver Clock Frequency Information
 *       
 * @param clockDrift
 *				- Receiver clock drift.  Units : Meters per second
 *
 * @param clockDriftUnc
 *				- Receiver clock drift uncertainty. Units : Meters per second
 *
 * @param sourceOfFreq
 *				- Source of the clock frequency information.
				 - Valid values:
					- eQMI_LOC_FREQ_SOURCE_INVALID(0) - Source of the frequency is invalid
					- eQMI_LOC_FREQ_SOURCE_EXTERNAL(1) - Source of the frequency is from an external injection
					- eQMI_LOC_FREQ_SOURCE_PE_CLK_REPORT(2) - Source of the frequency is from the GNSS navigation engine
					- eQMI_LOC_FREQ_SOURCE_UNKNOWN(3) - Source of the frequency is unknown
*/
typedef struct
{
	float clockDrift;
	float clockDriftUnc;
	uint32_t sourceOfFreq;
}loc_GNSSReceiverClockFreqInfo;

/**
 * \ingroup loc
 * 
 * Leap Second Information
 *  
 * @param leapSec
 *			- GPS time leap second delta to UTC time. For nonzero values of leapSecUnc, leapSec must be treated as unknown.
 *			- Units : Seconds
 *
 * @param leapSecUnc
 *			- Uncertainty for the GPS leap second.
 *			- Units : Seconds
*/
typedef struct
{
	uint8_t leapSec;
	uint8_t leapSecUnc;
}loc_LeapSecondInformation;

/**
 * \ingroup loc
 * 
 * GPS to xxx Intersystem Time Bias Information
 *  
 * @param validMask
 *			- Valid values:
 *			- QMI_LOC_SYS_TIME_BIAS_VALID (0x01) - System time bias is valid
 *			- QMI_LOC_SYS_TIME_BIAS_UNC_VALID (0x02) - System time bias uncertainty is valid
 *
 * @param timeBias
 *			- System 1 to system 2 time bias. 
 *			- Units: Milliseconds
 *
 * @param timeBiasUnc
 *			- System 1 to system 2 time bias uncertainty.
 *			- Units : Milliseconds
 *
*/
typedef struct
{
	uint8_t validMask;
	float timeBias;
	float timeBiasUnc; 
}loc_GpsIntersysTimeBias;

/**
 * \ingroup loc
 *
 * Satellite System Time Information for GPS, BDS, GAL Constellation
 *  
 * @param system
 *			- Specifies the satellite system constellation.
 *			 - Valid values:
 *				- eQMI_LOC_SV_SYSTEM_GPS (1) - GPS satellite
 *				- eQMI_LOC_SV_SYSTEM_GALILEO (2) - Galileo satellite
 *				- eQMI_LOC_SV_SYSTEM_SBAS (3) - SBAS satellite
 *				- eQMI_LOC_SV_SYSTEM_COMPASS (4) - COMPASS satellite (Deprecated)
 *				- eQMI_LOC_SV_SYSTEM_GLONASS (5) - GLONASS satellite
 *				- eQMI_LOC_SV_SYSTEM_BDS (6) - BDS satellite
 *				- eQMI_LOC_SV_SYSTEM_QZSS (7) - QZSS satellite
 *				- eQMI_LOC_SV_SYSTEM_NAVIC (8) - NavIC satellite
 *
 * @param systemWeek
 *			- Current system week. For GPS: Calculated from midnight, Jan. 6, 1980
 *			- For BDS: Calculated from 00:00:00 on January 1, 2006 of Coordinated Universal Time (UTC)
 *			- For GAL: Calculated from 00:00 UT on Sunday August 22, 1999 (midnight between August 21 and August 22) If the week is unknown, set this value to 65535.
 *			- Units: Weeks
 *
 * @param systemMsec
 *			- Amount of time into the current week.
 *			- Units: Milliseconds
 *
 * @param systemClkTimeBias
 *			- System clock time bias (submilliseconds).
 *			- Units: Milliseconds (system time = systemMsec - systemClkTimeBias)
 *
 * @param systemClkTimeUncMs
 *			- Single-sided maximum time bias uncertainty.
 *			- Units: Milliseconds
*/
typedef struct
{
	uint32_t system;
	uint16_t systemWeek;
	uint32_t systemMsec;
	float systemClkTimeBias;
	float systemClkTimeUncMs;
}loc_SatelliteSysTimeInfo;

/**
 * \ingroup loc
 * 
 * GLONASS System Time Information
 * 
 * @param gloFourYear
 *			- GLONASS four year number from 1996.
 *			- Refer to the GLONASS ICD. Applicable only for GLONASS and must be ignored for other constellations. If unknown, set this value to 255.
 *
 * @param gloDays
 *			- GLONASS day number in four years. Refer to GLONASS ICD. Applicable only for GLONASS and must be ignored for other constellations. If unknown, set this value to 65535
 *
 * @param gloMsec
 *			- GLONASS time of day in msec. Refer to the GLONASS ICD.
 *			- Units: Milliseconds
 *
 * @param gloClkTimeBias
 *			- System clock time bias (submillisecond).
 *			- Units: Milliseconds (system time = systemMsec - systemClkTimeBias)
 *
 * @param gloClkTimeUncMs
 *			- Single-sided maximum time bias uncertainty.
 *			- Units: Milliseconds
*/
typedef struct
{
	uint8_t gloFourYear;
	uint16_t gloDays;
	uint32_t gloMsec;
	float gloClkTimeBias;
	float gloClkTimeUncMs;
}loc_GlonassSystemTimeInfo;

/**
 * \ingroup loc
 * 
 * Extended Time Information
 * 
 * @param refFCount
 *			- Receiver frame counter value at a reference tick.
 *			- Units: Milliseconds
 *
 * @param systemRtc_valid
 *			- Validity indicator for the system RTC.
 *
 * @param systemRtcMs
 *			- Platform system RTC value.
 *			- Units: Milliseconds
 *
 * @param sourceOfTime 
 *			- Source of the time information.
 *			 - Valid values:
 *				- eQMI_LOC_TIME_SRC_INVALID (0) - Invalid time
 *				- eQMI_LOC_TIME_SRC_NETWORK_TIME_TRANSFER (1) - Time is set by the 1X system
 *				- eQMI_LOC_TIME_SRC_NETWORK_TIME_TAGGING (2) - Time is set by WCDMA/GSM time tagging (that is, associating network time with GPS time)
 *				- eQMI_LOC_TIME_SRC_EXTERNAL_INPUT (3) - Time is set by an external injection
 *				- eQMI_LOC_TIME_SRC_TOW_DECODE (4) - Time is set after decoding over-the-air GPS navigation data from one GPS satellite
 *				- eQMI_LOC_TIME_SRC_TOW_CONFIRMED (5) - Time is set after decoding over-the-air GPS navigation data from multiple satellites
 *				- eQMI_LOC_TIME_SRC_TOW_AND_WEEK_CONFIRMED (6) - Both time of the week and the GPS week number are known
 *				- eQMI_LOC_TIME_SRC_NAV_SOLUTION (7) - Time is set by the position engine after the fix is obtained
 *				- eQMI_LOC_TIME_SRC_SOLVE_FOR_TIME (8) - Time is set by the position engine after performing SFT; this is done when the clock time uncertainty is large
 *				- eQMI_LOC_TIME_SRC_GLO_TOW_DECODE (9) - Time is set after decoding GLO satellites
 *				- eQMI_LOC_TIME_SRC_TIME_TRANSFORM (10) - Time is set after transforming the GPS to GLO time
 *				- eQMI_LOC_TIME_SRC_WCDMA_SLEEP_TIME_TAGGING (11) - Time is set by the sleep time tag provided by the WCDMA network
 *				- eQMI_LOC_TIME_SRC_GSM_SLEEP_TIME_TAGGING (12) - Time is set by the sleep time tag provided by the GSM network
 *				- eQMI_LOC_TIME_SRC_UNKNOWN(13) - Source of the time is unknown
 *				- eQMI_LOC_TIME_SRC_SYSTEM_TIMETICK (14) - Time is derived from the system clock (better known as the slow clock); GNSS time is maintained irrespective of the GNSS receiver state
 *				- eQMI_LOC_TIME_SRC_QZSS_TOW_DECODE (15) - Time is set after decoding QZSS satellites
 *				- eQMI_LOC_TIME_SRC_BDS_TOW_DECODE (16) - Time is set after decoding BDS satellites
 *				- eQMI_LOC_TIME_SRC_GAL_TOW_DECODE (17) - Time is set after decoding GAL satellites
 *				- eQMI_LOC_TIME_SRC_NAVIC_TOW_DECODE (18) - Time is set after decoding NavIC satellites
 *
*/
typedef struct
{
	uint32_t refFCount;
	uint8_t systemRtc_valid;
	uint64_t systemRtcMs;
	uint32_t sourceOfTime;
}loc_ExtendedTimeInfo;

/**
 * \ingroup loc
 * 
 * Satellite System Measurement Report for Enabled Constellation Info
 * 
 * @param gnssSvId
 *			- GNSS SV ID. Range:	
 *			- For GPS: 1 to 32
 *			- For GLONASS: 65 to 96. When slot-number to SV ID mapping is unknown, set as 255.
 *			- For QZSS: 193 to 197
 *			- For BDS: 201 to 237
 *			- For Galileo: 301 to 336
 *			- For NavIC: 401 to 414
 *
 * @param gloFrequency
 *			- GLONASS frequency number + 8. Valid only for a GLONASS system and must be ignored for all other systems.
 *			- Range: 1 to 14
 *
 * @param svStatus
 *			- Satellite search state.
 *			 - Valid values:
 *				- eQMI_LOC_SV_STATUS_IDLE (1) - SV is not being actively processed
 *				- eQMI_LOC_SV_STATUS_SEARCH (2) - The system is searching for this SV
 *				- eQMI_LOC_SV_STATUS_TRACK (3) - SV is being tracked
 *				
 * @param validMask
 *			- Validity mask (0 = Not valid; 1 = Valid).
 *				- QMI_LOC_SV_HEALTH_VALID (0x01) - SV health information is valid
 *				- QMI_LOC_SV_MULTIPATH_EST_VALID (0x02) - Multipath estimate for SV is valid
 *				- QMI_LOC_SV_FINE_SPEED_VALID (0x04) - Fine speed for SV is valid
 *				- QMI_LOC_SV_FINE_SPEED_UNC_VALID (0x08) - Fine speed uncertainty for SV is valid
 *				- QMI_LOC_SV_CARRIER_PHASE_VALID (0x10) - Carrier phase for SV is valid
 *				- QMI_LOC_SV_SV_DIRECTION_VALID (0x20) - SV direction information for SV is valid
 *				- QMI_LOC_SV_CYCLESLIP_COUNT_VALID (0x40) - Cycle slip count information is valid
 *				- QMI_LOC_SV_LOSSOFLOCK_VALID (0x80) - Loss of lock information is valid
 *
 * @param healthStatus
 *			- Health status.
 *			- Range: 0 to 1, where 0 = unhealthy, 1 = healthy
 *
 * @param svInfoMask
 *			- Indicates whether almanac and ephemeris information is available.
 *			- Valid values:
 *				- QMI_LOC_SVINFO_MASK_HAS_EPHEMERIS (0x01) - Ephemeris is available for this SV
 *				- QMI_LOC_SVINFO_MASK_HAS_ALMANAC (0x02) - Almanac is available for this SV
 *
 * @param validMeasStatusMask
 *			- Validity mask for measurement status information.
 *			- A set bit in validMeasStatusMask indicates that the corresponding bit in measurementStatus has valid status information:
 *			 - Valid masks:
 *				- QMI_LOC_MASK_MEAS_STATUS_SM_STAT_BIT_VALID (0x00000001) - Satellite time in submilliseconds (code-phase)
 *				- QMI_LOC_MASK_MEAS_STATUS_SB_STAT_BIT_VALID (0x00000002) - Satellite sub-bit time
 *				- QMI_LOC_MASK_MEAS_STATUS_MS_STAT_BIT_VALID (0x00000004) - Satellite time in milliseconds
 *				- QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM_STAT_BIT_VALID (0x00000008) - Signal bit edge is confirmed
 *				- QMI_LOC_MASK_MEAS_STATUS_VEL_STAT_BIT_VALID (0x00000010) - Satellite Doppler is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_VEL_FINE_STAT_BIT_VALID (0x00000020) - Fine/coarse Doppler measurement indicator
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_STAT_BIT_VALID (0x00000040) - TRUE/FALSE - Lock Point is valid/invalid
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_POS_STAT_BIT_VALID (0x00000080) - TRUE/FALSE : Lock Point is positive/negative
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF_STAT_BIT_VALID (0x00000200) - Range update from satellite differences
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF_STAT_BIT_VALID (0x00000400) - Doppler update from satellite differences
 *				- QMI_LOC_MASK_MEAS_STATUS_GNSS_FRESH_MEAS_STAT_BIT_VALID (0x08000000) - TRUE - Fresh GNSS measurement observed in the last second
 *				- QMI_LOC_MASK_MEAS_STATUS_RESERVED_UNUSED_1_BIT_VALID (0x10000000) - Reserved for future use
 *				- QMI_LOC_MASK_MEAS_STATUS_RESERVED_UNUSED_2_BIT_VALID (0x20000000) - Reserved for future use
 *				- QMI_LOC_MASK_MEAS_STATUS_100MS_STAT_BIT_VALID (0x40000000) - TRUE - SV time known with 100 ms ambiguity
 *				- QMI_LOC_MASK_MEAS_STATUS_2S_STAT_BIT_VALID (0x80000000) - TRUE - SV time known with 2 seconds ambiguity MSB 0xFFC0000000000000 bits indicate the validity of DONT_USE bits
 *
 * @param measurementStatus
 *			- Bitmask indicating the SV measurement status.
 *			 - Valid bitmasks:
 *				- QMI_LOC_MASK_MEAS_STATUS_SM_VALID (0x00000001) - Satellite time in submilliseconds (code phase) is known
 *				- QMI_LOC_MASK_MEAS_STATUS_SB_VALID (0x00000002) - Satellite sub-bit time is known
 *				- QMI_LOC_MASK_MEAS_STATUS_MS_VALID (0x00000004) - Satellite time in milliseconds is known
 *				- QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM (0x00000008) - Signal bit edge is confirmed
 *				- QMI_LOC_MASK_MEAS_STATUS_VELOCITY_VALID (0x00000010) - Satellite Doppler is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_VELOCITY_FINE (0x00000020) - TRUE - Fine Doppler is measured, FALSE: Coarse Doppler is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_VALID (0x00000040) - TRUE/FALSE - Lock Point is valid/invalid
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_POS_VALID (0x00000080) - TRUE/FALSE - Lock Point is positive/negative
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF (0x00000200) - Range update from satellite differences is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF (0x00000400) - Doppler update from satellite differences is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_GNSS_FRESH_MEAS_VALID (0x08000000) - TRUE - Fresh GNSS measurement observed in last second If any MSB bit in 0xFFC0000000000000 DONT_USE is set, the measurement must not be used by the client.
 *
 * @param CNo
 *			- Carrier to noise ratio at antenna.
 *			- Units: dBHz
 *			- Scale: 0.1
 *
 * @param gloRfLoss
 *			- GLONASS RF loss reference to the antenna.
 *			- Units: dB 
 *			- Scale: 0.1
 *
 * @param measLatency
 *			- Age of the measurement. A positive value means the measurement precedes the reference time.
 *			- Units: Milliseconds
 *
 * @param svTimeMs
 *			- Satellite time in milliseconds.
 *			- For GPS, BDS, GAL, and QZSS - Range is 0 through (604800000-1)
 *			- For GLONASS - Range is 0 through (86400000-1)
 *			- Units: Milliseconds Valid when the QMI_LOC_MEAS_STATUS_MS_VALID bit is set in the measurement status.
 *			- Note: All SV times in the current measurement block are already propagated to a common reference time epoch.
 *
 * @param svTimeSubMs
 *			- Satellite time in submilliseconds. Total SV Time = svMs + svSubMs
 *			- Units: Milliseconds
 *
 * @param svTimeUncMs
 *			- Satellite time uncertainty.
 *			- Units: Milliseconds
 *
 * @param dopplerShift
 *			- Satellite Doppler.
 *			- Units: Meters per second
 *
 * @param dopplerShiftUnc
 *			- Satellite Doppler uncertainty.
 *			- Units: Meters per second
 *
 * @param dopplerAccel_valid
 *			- Validity for Doppler acceleration.
 *			
 * @param dopplerAccel
 *			- Satellite Doppler acceleration.
 *			- Units: Hz/second
 *
 * @param lossOfLock
 *			- Loss of signal lock indicator.
 *			- 0 - Signal is in continuous track
 *			- 1 - Signal is not in track
 *
 * @param multipathEstimate
 *			- Estimate of multipath in a measurement.
 *			- Units: Meters
 *
 * @param fineSpeed
 *			- Carrier phase derived speed.
 *			- Units: Meters per second
 *
 * @param fineSpeedUnc
 *			- Carrier phase derived speed uncertainty.
 *			- Units: Meters per second
 *
 * @param carrierPhase
 *			- Carrier phase measurement (L1 cycles).
 *
 * @param cycleSlipCount
 *			- Increments when a cycle slip is detected.
 *
 * @param svAzimuth
 *			- Satellite azimuth.
 *			- Units: Radians
 *			- Range: 0 to 2*pi()
 *
 * @param svElevation
 *			- Satellite elevation.
 *			- Units: Radians
 *			- Range: 0 to pi()/2
*/
typedef struct
{
	uint16_t gnssSvId;
	uint8_t gloFrequency;
	uint32_t svStatus;
	uint16_t validMask;
	uint8_t healthStatus;
	uint8_t svInfoMask;
	uint64_t validMeasStatusMask;
	uint64_t measurementStatus;
	uint16_t CNo;
	uint16_t gloRfLoss;
	uint32_t measLatency;
	uint32_t svTimeMs;
	float svTimeSubMs;
	float svTimeUncMs;
	float dopplerShift;
	float dopplerShiftUnc;
	uint8_t dopplerAccel_valid;
	float dopplerAccel;
	uint8_t lossOfLock;
	float multipathEstimate;
	float fineSpeed;
	float fineSpeedUnc;
	double carrierPhase;
	uint8_t cycleSlipCount;
	float svAzimuth;
	float svElevation;
}SatelliteSysMeasReportEnabledConst;

/**
 * \ingroup loc
 * 
 * Satellite System Measurement Report for Enabled Constellation Information List
 * 
 * @param svMeasurement_len
 *			- Number of sets of the SatelliteSysMeasReportEnabledConst items.
 *
 * @param pSatelliteSysMeasReportEnabledConst
 *			- \ref SatelliteSysMeasReportEnabledConst.
 * 
 */
typedef struct{
	uint8_t svMeasurement_len;
	SatelliteSysMeasReportEnabledConst *pSatelliteSysMeasReportEnabledConst;
}loc_SatelliteSysMeasReportEnabledConstList; 


/**
 * \ingroup loc
 *
 * SV Carrier Phase Measurement Uncertainty for Enabled Constellation Information
 *  
 * @param svCarrierPhaseUncertainty_len
 *			- Number of sets of the following pSvCarrierPhaseUncertainty
 *
 * @param pSvCarrierPhaseUncertainty
 *			- Carrier Phase Uncertainty 
 */
typedef struct{
	uint8_t svCarrierPhaseUncertainty_len;
	float *pSvCarrierPhaseUncertainty;
}loc_SvCarrierPhaseMeasurment;

/**
 * \ingroup loc
 * 
 * @param validMask
 *			- Valid values:
 *				- QMI_LOC_SYS_TIME_BIAS_VALID (0x01) - System time bias is valid
 *				- QMI_LOC_SYS_TIME_BIAS_UNC_VALID (0x02) - System time bias uncertainty is valid
 *
 * @param timeBias
 *			- System 1 to system 2 time bias.
 *			- Units: Milliseconds
 *
 * @param timeBiasUnc
 *			- System 1 to system 2 time bias uncertainty.
 *			- Units: Milliseconds
 */
typedef struct {
	uint8_t validMask;
	float timeBias;
	float timeBiasUnc;
}GPSIntrasysTimeBias;

/**
 * \ingroup loc
 * 
 * Other Code Type Name (NULL-Terminated)
 * 
 * @param otherCodeTypeName_len
 *			- Number of sets of the following elements:
 *
 * @param otherCodeTypeName
 *			- other Code Type Name.
 *			- Type: character string 
 *			- Maximum length of the array: 8 When the measurement code type eQMI_LOC_GNSS_CODE_TYPE_OTHER is used, the name of the code is specified in the char array above.
 */
typedef struct {
	uint8_t otherCodeTypeName_len;
	char otherCodeTypeName[8];
}loc_OtherCodeTypeName;

/**
 * \ingroup loc
 * 
 *
 * @param gnssSvId
 *			- GNSS SV ID. Range:
 *			- For GPS: 1 to 32
 *			- For GLONASS: 65 to 96. When slot-number to SV ID mapping is unknown, set as 255.
 *			- For QZSS: 193 to 197
 *			- For BDS: 201 to 237
 *			- For Galileo: 301 to 336
 *			- For NavIC: 401 to 41
 * @param gloFrequency
 *			- GLONASS frequency number + 8. Valid only for a GLONASS system and must be ignored for all other systems.
 *			- Range: 1 to 14
 * @param svStatus
 *			- Satellite search state. 
 *			 - Valid values:
 *				- eQMI_LOC_SV_STATUS_IDLE (1) - SV is not being actively processed
 *				- eQMI_LOC_SV_STATUS_SEARCH (2) – The system is searching for this SV
 *				- eQMI_LOC_SV_STATUS_TRACK (3) – SV is being tracked
 * @param validMask
 *			- Validity mask (0 = Not valid; 1 = Valid).
 *			- QMI_LOC_SV_HEALTH_VALID (0x01) – SV health information is valid
 *			- QMI_LOC_SV_MULTIPATH_EST_VALID (0x02) – Multipath estimate for SV is valid
 *			- QMI_LOC_SV_FINE_SPEED_VALID (0x04) – Fine speed for SV is valid
 *			- QMI_LOC_SV_FINE_SPEED_UNC_VALID (0x08) – Fine speed uncertainty for SV is valid
 *			- QMI_LOC_SV_CARRIER_PHASE_VALID (0x10) – Carrier phase for SV is valid
 *			- QMI_LOC_SV_SV_DIRECTION_VALID (0x20) – SV direction information for SV is valid
 *			- QMI_LOC_SV_CYCLESLIP_COUNT_VALID (0x40) – Cycle slip count information is valid
 *			- QMI_LOC_SV_LOSSOFLOCK_VALID (0x80) – Loss of lock information is valid
 * @param healthStatus
 *			- Health status.
 *			- Range: 0 to 1, where 0 = unhealthy, 1 = healthy
 * @param svInfoMask
 *			- Indicates whether almanac and ephemeris information is available.
 *			 - Valid values:
 *				- QMI_LOC_SVINFO_MASK_HAS_EPHEMERIS (0x01) – Ephemeris is available for this SV
 *				- QMI_LOC_SVINFO_MASK_HAS_ALMANAC (0x02) – Almanac is available for this SV
 *
 * @param validMeasStatusMask
 *			- Validity mask for measurement status information. A set bit in validMeasStatusMask
 *			- indicates that the corresponding bit in measurementStatus has valid status information:
 *			 - Valid masks:
 *				- QMI_LOC_MASK_MEAS_STATUS_SM_STAT_BIT_VALID (0x00000001) – Satellite time in submilliseconds (code-phase)
 *				- QMI_LOC_MASK_MEAS_STATUS_SB_STAT_BIT_VALID (0x00000002) – Satellite sub-bit time
 *				- QMI_LOC_MASK_MEAS_STATUS_MS_STAT_BIT_VALID (0x00000004) – Satellite time in milliseconds
 *				- QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM_STAT_BIT_VALID (0x00000008) – Signal bit edge is confirmed
 *				- QMI_LOC_MASK_MEAS_STATUS_VEL_STAT_BIT_VALID (0x00000010) – Satellite Doppler is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_VEL_FINE_STAT_BIT_VALID (0x00000020) – Fine/coarse Doppler measurement indicator
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_STAT_BIT_VALID (0x00000040) – TRUE/FALSE – Lock Point is valid/invalid
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_POS_STAT_BIT_VALID (0x00000080) – TRUE/FALSE : Lock Point is positive/negative
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF_STAT_BIT_VALID (0x00000200) – Range update from satellite differences
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF_STAT_BIT_ VALID (0x00000400) – Doppler update from satellite differences
 *				- QMI_LOC_MASK_MEAS_STATUS_GNSS_FRESH_MEAS_STAT_BIT_VALID (0x08000000) – TRUE – Fresh GNSS measurement observed in the last second
 *				- QMI_LOC_MASK_MEAS_STATUS_RESERVED_UNUSED_1_BIT_ VALID (0x10000000) – Reserved for future use
 *				- QMI_LOC_MASK_MEAS_STATUS_RESERVED_UNUSED_2_BIT_ VALID (0x20000000) – Reserved for future use
 *				- QMI_LOC_MASK_MEAS_STATUS_100MS_STAT_BIT_VALID (0x40000000) – TRUE – SV time known with 100 ms ambiguity
 *				- QMI_LOC_MASK_MEAS_STATUS_2S_STAT_BIT_VALID (0x80000000) – TRUE – SV time known with 2 seconds ambiguity MSB 0xFFC0000000000000 bits indicate the validity of DONT_USE bits.
 *
 * @param measurementStatus
 *			- Bitmask indicating the SV measurement status.
 *			 - Valid bitmasks:
 *				- QMI_LOC_MASK_MEAS_STATUS_SM_VALID (0x00000001) – Satellite time in submilliseconds (code phase) is known
 *				- QMI_LOC_MASK_MEAS_STATUS_SB_VALID (0x00000002) – Satellite sub-bit time is known
 *				- QMI_LOC_MASK_MEAS_STATUS_MS_VALID (0x00000004) – Satellite time in milliseconds is known
 *				- QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM (0x00000008) – Signal bit edge is confirmed
 *				- QMI_LOC_MASK_MEAS_STATUS_VELOCITY_VALID (0x00000010) – Satellite Doppler is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_VELOCITY_FINE (0x00000020) – TRUE – Fine Doppler is measured, FALSE: Coarse Doppler is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_VALID (0x00000040) – TRUE/FALSE – Lock Point is valid/invalid
 *				- QMI_LOC_MASK_MEAS_STATUS_LP_POS_VALID (0x00000080) – TRUE/FALSE – Lock Point is positive/negative
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF (0x00000200) – Range update from satellite differences is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF (0x00000400) – Doppler update from satellite differences is measured
 *				- QMI_LOC_MASK_MEAS_STATUS_GNSS_FRESH_MEAS_VALID (0x08000000) – TRUE – Fresh GNSS measurement observed in last second If any MSB bit in 0xFFC0000000000000
 *					  DONT_USE is set, the measurement must not be used by the client.
 *
 * @param CNo
 *			- Carrier to noise ratio at antenna.
 *			- Units: dBHz 
 *			- Scale: 0.1
 *
 * @param gloRfLoss
 *			- GLONASS RF loss reference to the antenna.
 *			- Units: dB
 *			- Scale: 0.1
 *
 * @param measLatency
 *			- Age of the measurement. A positive value means the measurement precedes the reference time.
 *			- Units: Milliseconds
 *
 * @param svTimeMs
 *			- Satellite time in milliseconds.
 *			- For GPS, BDS, GAL, and QZSS – Range is 0 through (604800000-1)
 *			- For GLONASS – Range is 0 through (86400000-1)
 *			- Units: Milliseconds Valid when the QMI_LOC_MEAS_STATUS_MS_VALID bit is set in the measurement status.
 *			  note All SV times in the current measurement block are already propagated to a common reference time epoch.
 *
 * @param svTimeSubMs
 *			- Satellite time in submilliseconds. Total SV Time = svMs + svSubMs
 *			- Units: Milliseconds
 *
 * @param svTimeUncMs
 *			- Satellite time uncertainty.
 *			- Units: Milliseconds
 *
 * @param dopplerShift
 *			- Satellite Doppler.
 *			- Units: Meters per second
 *
 * @param dopplerShiftUnc
 *			- Satellite Doppler uncertainty.
 *			- Units: Meters per second
 *
 * @param dopplerAccel_valid
 *			- Validity for Doppler acceleration.
 *
 * @param dopplerAccel
 *			- Satellite Doppler acceleration.
 *			- Units: Hz/second
 *
 * @param lossOfLock
 *			- Loss of signal lock indicator.
 *			- 0 – Signal is in continuous track
 *			- 1 – Signal is not in track
 *
 * @param multipathEstimate
 *			- Estimate of multipath in a measurement.
 *			- Units: Meters
 *
 * @param fineSpeed
 *			- Carrier phase derived speed.
 *			- Units: Meters per second
 *
 * @param fineSpeedUnc
 *			- Carrier phase derived speed uncertainty.
 *			- Units: Meters per second
 *
 * @param carrierPhase
 *			- Carrier phase measurement (L1 cycles).
 *
 * @param cycleSlipCount
 *			- Increments when a cycle slip is detected.
 *
 * @param svAzimuth
 *			- Satellite azimuth.
 *			- Units: Radians
 *			- Range: 0 to 2*pi()
 *
 * @param svElevation
 *			- Satellite elevation.
 *			- Units: Radians
 *			- Range: 0 to pi()/2
 *
 */
typedef struct
{
    uint32_t svStatus;
    uint16_t validMask;
    uint8_t healthStatus;
    uint64_t svInfoMask;
    uint8_t validMeasStatusMask;
    uint8_t measurementStatus;
    uint16_t CNo;
    uint16_t gloRfLoss;
    uint32_t measLatency;
    uint32_t svTimeMs;
    float svTimeSubMs;
    float svTimeUncMs;
    float dopplerShift;
    float dopplerShiftUnc;
    uint8_t dopplerAccel_valid;
    float dopplerAccel;
    uint8_t lossOfLock;
    float multipathEstimate;
    float fineSpeed;
    float fineSpeedUnc;
    double carrierPhase;
    uint8_t cycleSlipCount;
    float svAzimuth;
    float svElevation;
}MeasurementReportExtSVs;

/**
 * \ingroup loc
 * 
 * Measurement Report for Extended SVs List Information
 * 
 * @param extSvMeasurement_len
 *			- Number of sets of the MeasurementReportExtSVs items
 *
 * @param pMeasurementReportExtSVs
 * 			- \ref MeasurementReportExtSVs
 */
typedef struct
{
	uint8_t extSvMeasurement_len;
	MeasurementReportExtSVs *pMeasurementReportExtSVs;
}loc_MeasurementReportExtSVsList;

/**
 * \ingroup loc
 *
 * Carrier Phase Measurement Uncertainty for Extended SVs Information
 * 
 * @param extSvCarrierPhaseUncertainty_len
 *		- Number of sets of the following extSvCarrierPhaseUncertainty
 *
 * @param pExtSvCarrierPhaseUncertainty
 *		- Carrier Phase Measurement Uncertainty
 *
*/
typedef struct {
	uint8_t extSvCarrierPhaseUncertainty_len;
	float *pArrExtSvCarrierPhaseUncertainty;
}loc_CarrierPhaseMeasuUncerExtSVs;

/**
 * \ingroup loc
 * 
 * @param seqNum
 *				- Current Message Sequence Number
 *				- Current message number. Used for segmentation / assembly of measurement reports.
 *
 * @param maxMessageNum
 *				- Maximum Number of Messages to Send for Present Time Epoch
 *				- Maximum number of messages to send 	for the present time epoch. Specifies Satellite System Constellation of This Report
 *				- Specifies Satellite System Constellation of This Report
 *
 * @param system
 *				- Specifies the satellite system constellation of this report.
 *				 - Valid values:
 *					- eQMI_LOC_SV_SYSTEM_GPS(1) - GPS satellite
 *					- eQMI_LOC_SV_SYSTEM_GALILEO(2) - Galileo satellite
 *					- eQMI_LOC_SV_SYSTEM_SBAS(3) - SBAS satellite
 *					- eQMI_LOC_SV_SYSTEM_COMPASS(4) - COMPASS satellite(Deprecated)
 *					- eQMI_LOC_SV_SYSTEM_GLONASS(5) - GLONASS satellite
 *					- eQMI_LOC_SV_SYSTEM_BDS(6) - BDS satellite
 *					- eQMI_LOC_SV_SYSTEM_QZSS(7) - QZSS satellite
 *					- eQMI_LOC_SV_SYSTEM_NAVIC(8) - NavIC satellite
 *
 * @param pReceiverClockFreqInfo
 *				- GNSS Receiver Clock Frequency Information
 *				- See \ref loc_GNSSReceiverClockFreqInfo
 *
 * @param pLeapSecondInformation
 *			- Leap Second Information
 *			- See \ref loc_LeapSecondInformation
 *
 *
 * @param pGpsBdsIntersysTimeBias
 *			- GPS to BDS Intersystem Time Bias Reported when both GPS and BDS system information reporting are enabled.
 *			- System 1: GPS
 *			- System 2: BDS
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pGpsGalileoIntersystemTimeBias
 *			- GPS to Galileo Intersystem Time Bias Reported when both GPS and Galileo system information reporting are enabled.
 *			- System 1: GPS
 *			- System 2: Galileo
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pBdsGLonassIntersystemTimeBias
 *			- Reported when both BDS and GLONASS system information reporting are enabled.
 *			- System 1: BDS
 *			- System 2: GLONASS
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pGalGlonassIntersystemTimeBias
 *			- Reported when both GAL and GLONASS system information reporting are enabled.
 *			- System 1: GAL
 *			- System 2 : GLONASS
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pGalBdsIntersystemTimeBias
 *			- Reported when both GAL and BDS system information reporting are enabled.
 *			- System 1: GAL
 *			- System 2 : BDS
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pSatelliteSysTimeInfo
 *			- Satellite System Time Information for GPS, BDS, GAL Constellation
 *          - See \ref loc_SatelliteSysTimeInfo
 *
 * @param pGlonassSystemTimeInfo
 *			- GLONASS System Time Information
 *			- See \ref loc_GlonassSystemTimeInfo
 *
 * @param pExtendedTimeInfo
 *			- Extended Time Information
 *			- See \ref loc_ExtendedTimeInfo
 *
 * @param pArrSatelliteSysMeasReportEnabledConst
 *			- Satellite System Measurement Report for Enabled Constellation
 *			- See \ref loc_SatelliteSysMeasReportEnabledConstList
 *
 * @param pNumClockResets
 *			- Extended Time Information - Cumulative Number of Clock Reset
 *
 * @param pSvCarrierPhaseMeasurment
 *			- SV Carrier Phase Measurement Uncertainty for Enabled Constellation
 *			- See \ref loc_SvCarrierPhaseMeasurment
 *
 * @param pGnssSignalType
 *			- GNSS Signal Type
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1CA (0x00000001) - GPS L1CA RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L1C (0x00000002) - GPS L1C RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L2C_L (0x00000004) - GPS L2C_L RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GPS_L5_Q (0x00000008) - GPS L5_Q RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G1 (0x00000010) - GLONASS G1 (L1OF) RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GLONASS_G2 (0x00000020) - GLONASS G2 (L2OF) RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E1_C (0x00000040) - Galileo E1_C RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5A_Q (0x00000080) - Galileo E5A_Q RF band 
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_GALILEO_E5B_Q (0x00000100) - Galileo E5B_Q RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1_I (0x00000200) - BeiDou B1_I RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B1C (0x00000400) - BeiDou B1C RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2_I (0x00000800) - BeiDou B2_I RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_I (0x00001000) - BeiDou B2A_I RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1CA (0x00002000) - QZSS L1CA RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L1S (0x00004000) - QZSS L1S RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L2C_L (0x00008000) - QZSS L2C_L RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_QZSS_L5_Q (0x00010000) - QZSS L5_Q RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_SBAS_L1_CA (0x00020000) - SBAS L1_CA RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_NAVIC_L5 (0x00040000) - NavIC L5 RF band
 *				- QMI_LOC_MASK_GNSS_SIGNAL_TYPE_BEIDOU_B2A_Q (0x00080000) - BeiDou B2A_Q RF band
 *
 * @param pJammerIndicator
 *			- Jammer Indicator
 *          - See \ref loc_jammerIndicator
 *
 * @param pGPSL1L2CIntrasysTimeBias
 *			- GPS L1 - L2C Intrasystem Time Bias - GPS L1 to L2C time bias (L2C-L1).
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pGPSL1L5IntrasysTimeias
 *			- GPS L1 - L5 Intrasystem Time Bias GPS L1 to L5 time bias (L5-L1).
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pGloG1G2IntrasysTimeBias
 *			- GLO G1 - G2 Intrasystem Time Bias GLONASS G1 to G2 time bias (G2-G1).
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pBdsB1IB2AIntrasysTimeBias
 *			- BDS B1I - B2A Intrasystem Time Bias BDS B1I to B2A time bias (B2A-B1I).
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pBdsB1IB1CIntrasysTimeBias
 *			- BDS B1I - B1C Intrasystem Time Bias BDS B1I to B1C time bias (B1C-B1I).
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pGalileoE1E5AIntrasysTimeBias
 *			- Galileo E1 - E5A Intrasystem Time Bias Galileo E1 to E5a time bias (E5a-E1).
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pGalileoE1E5bIntrasysTimeBias
 *			- Galileo E1 - E5B Intrasystem Time Bias Galileo E1 to E5b time bias (E5b-E1).
 *			- See \ref loc_GpsIntersysTimeBias
 *
 * @param pNHzMeasurement
 *			- NHz indicator. 
 *			 - Valid values:
 *				- 0 indicates 1Hz measurement report
 *				- 1 indicates NHz measurement report (N > 1).  
 *
 * @param pMeasurementCodeType
 *			- GNSS Measurement Code Type
 *			- Specifies the GNSS measurement’s code type.
 *			- eQMI_LOC_GNSS_CODE_TYPE_A (0) - Galileo E1A, Galileo E6A, IRNSS L5A, IRNSS SA.
 *			- eQMI_LOC_GNSS_CODE_TYPE_B (1) - Galileo E1B, Galileo E6B, IRNSS L5B, IRNSS SB.
 *			- eQMI_LOC_GNSS_CODE_TYPE_C (2) - GPS L1 C/A, GPS L2 C/A, GLONASS G1 C/A, GLONASS G2 C/A, Galileo E1C, Galileo E6C, SBAS L1 C/A, QZSS L1 C/A, IRNSS L5C.
 *			- eQMI_LOC_GNSS_CODE_TYPE_I (3) - GPS L5 I, GLONASS G3 I, Galileo E5a I, Galileo E5b I, Galileo E5a+b I, SBAS L5 I, QZSS L5 I, BDS B1 I, BDS B2 I, BDS B3 I.
 *			- eQMI_LOC_GNSS_CODE_TYPE_L (4) - GPS L1C (P), GPS L2C (L), QZSS L1C (P), QZSS L2C (L), LEX(6) L.
 *			- eQMI_LOC_GNSS_CODE_TYPE_M (5) - GPS L1M, GPS L2M.
 *			- eQMI_LOC_GNSS_CODE_TYPE_P (6) - GPS L1P, GPS L2P, GLONASS G1P, GLONASS G2P.
 *			- eQMI_LOC_GNSS_CODE_TYPE_Q (7) - GPS L5 Q, GLONASS G3 Q, Galileo E5a Q, Galileo E5b Q, Galileo E5a+b Q, SBAS L5 Q, QZSS L5 Q, BDS B1 Q, BDS B2 Q, BDS B3 Q.
 *			- eQMI_LOC_GNSS_CODE_TYPE_S (8) - GPS L1C (D), GPS L2C (M), QZSS L1C (D), QZSS L2C (M), LEX(6) S.
 *			- eQMI_LOC_GNSS_CODE_TYPE_W (9) - GPS L1 Z-tracking, GPS L2 Z-tracking.
 *			- eQMI_LOC_GNSS_CODE_TYPE_X (10) - GPS L1C (D+P), GPS L2C (M+L), GPS L5 (I+Q), GLONASS G3 (I+Q), Galileo E1 (B+C), Galileo E5a (I+Q), Galileo E5b (I+Q), Galileo E5a+b(I+Q), Galileo E6 (B+C), SBAS
 *												L5 (I+Q), QZSS L1C (D+P), QZSS L2C (M+L), QZSS L5 (I+Q), LEX(6) (S+L), BDS B1 (I+Q), BDS B2 (I+Q), BDS B3 (I+Q), IRNSS L5 (B+C).
 *			- eQMI_LOC_GNSS_CODE_TYPE_Y (11) - GPS L1Y, GPS L2Y.
 *			- eQMI_LOC_GNSS_CODE_TYPE_Z (12) - Galileo E1 (A+B+C), Galileo E6 (A+B+C), QZSS L1-SAIF.
 *			- eQMI_LOC_GNSS_CODE_TYPE_N (13) - GPS L1 codeless, GPS L2 codeless.
 *			- eQMI_LOC_GNSS_CODE_TYPE_OTHER (255) - This code is used in case the measurement used a GNSS signal code that is not listed above.
 *
 * @param pGPSNavICIntersysTimeBias
 *			- GPS to NavIC Intersystem Time Bias Reported if both the GPS and NavIC system information reporting are enabled.
 *			- System 1: GPS
 *			- System 2: NavIC
 *          - See \ref loc_GpsIntersysTimeBias
 *
 * @param pGALNavICIntersysTimeBias
 *			- GAL to NavIC Intersystem Time Bias Reported if both the GAL and NavIC system information reporting are enabled.
 *			- System 1: GAL
 *			- System 2: NavIC
 *          - See \ref loc_GpsIntersysTimeBias
 *
 * @param pGLONavICIntersysTimeBias
 *			- GLO to NavIC Intersystem Time Bias Reported if both the GLO and NavIC system information reporting are enabled.
 *			- System 1: GLO
 *			- System 2: NavIC
 *          - See \ref loc_GpsIntersysTimeBias
 *
 * @param pBDSNavICIntersysTimeBias
 *			- BDS to NavIC Intersystem Time Bias Reported if both the BDS and NavIC system information reporting are enabled.
 *			- System 1: BDS
 *			- System 2: NavIC
 *          - See \ref loc_GpsIntersysTimeBias
 *
 * @param pArrMeasurementReportExtSVs
 *			- Measurement Report for Extended SVs.
 *			- See \ref loc_MeasurementReportExtSVsList
 *
 * @param pCarrierPhaseMeasuUncerExtSVs
 *			- Carrier Phase Measurement Uncertainty for Extended SVs
 *			- See \ref loc_CarrierPhaseMeasuUncerExtSVs
 *
 * @param pRefCountTicks
 *			- Receiver frame counter value in ticks.
 *
 * @param  Tlvresult
 *          - unpack result
 * 
 * @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
*/
typedef struct
{
	uint8_t seqNum; //1
	uint8_t maxMessageNum; //2
	uint32_t system; //3
	loc_GNSSReceiverClockFreqInfo *pReceiverClockFreqInfo; //10
	loc_LeapSecondInformation *pLeapSecondInformation; //11
	loc_GpsIntersysTimeBias *pGpsGlonassIntersysTimeBias; //12
	loc_GpsIntersysTimeBias *pGpsBdsIntersysTimeBias; //13
	loc_GpsIntersysTimeBias *pGpsGalileoIntersystemTimeBias; //14
	loc_GpsIntersysTimeBias *pBdsGLonassIntersystemTimeBias; //15
	loc_GpsIntersysTimeBias *pGalGlonassIntersystemTimeBias; //16
	loc_GpsIntersysTimeBias	*pGalBdsIntersystemTimeBias; //17
	loc_SatelliteSysTimeInfo *pSatelliteSysTimeInfo; //18
	loc_GlonassSystemTimeInfo *pGlonassSystemTimeInfo; //19
	loc_ExtendedTimeInfo *pExtendedTimeInfo; //1A
	loc_SatelliteSysMeasReportEnabledConstList *pArrSatelliteSysMeasReportEnabledConst; //1B
	uint32_t *pNumClockResets; //1C
	loc_SvCarrierPhaseMeasurment *pSvCarrierPhaseMeasurment; //1d
	uint64_t *pGnssSignalType; //1E
	loc_jammerIndicator	*pJammerIndicator; //1F
	loc_GpsIntersysTimeBias *pGPSL1L2CIntrasysTimeBias; //20
	loc_GpsIntersysTimeBias *pGPSL1L5IntrasysTimeias; //21
	loc_GpsIntersysTimeBias *pGloG1G2IntrasysTimeBias; //22
	loc_GpsIntersysTimeBias *pBdsB1IB2AIntrasysTimeBias; //23
	loc_GpsIntersysTimeBias *pBdsB1IB1CIntrasysTimeBias; //24
	loc_GpsIntersysTimeBias *pGalileoE1E5AIntrasysTimeBias; //25
	loc_GpsIntersysTimeBias *pGalileoE1E5BIntrasysTimeBias; //26
	uint8_t				*pNHzMeasurement; //27
	uint32_t			*pMeasurementCodeType; //28
	loc_OtherCodeTypeName	*pOtherCodeTypeName; //29
	loc_GpsIntersysTimeBias *pGPSNavICIntersysTimeBias; //2A
	loc_GpsIntersysTimeBias *pGALNavICIntersysTimeBias; //2B
	loc_GpsIntersysTimeBias *pGLONavICIntersysTimeBias; //2C
	loc_GpsIntersysTimeBias *pBDSNavICIntersysTimeBias; //2D
	loc_MeasurementReportExtSVsList *pArrMeasurementReportExtSVs; //2E
	loc_CarrierPhaseMeasuUncerExtSVs *pCarrierPhaseMeasuUncerExtSVs; //2F
	uint64_t *pRefCountTicks; //30
    uint16_t        Tlvresult;
    swi_uint256_t   ParamPresenceMask;
}unpack_loc_QmiCbkLocEventGnssMeasurementReportInd_t;

/**
 * \ingroup loc
 * 
 * Loc Event GNSS Measurement Report Indication unpack
 * 
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_EventGnssMeasurementReport_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_QmiCbkLocEventGnssMeasurementReportInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains Inject XTRA Data pack
 *
 *  \param  totalSize
 *          - Total size in bytes of the XTRA data to inject.
 *
 *  \param  totalParts
 *          - Total number of parts to divide the XTRA data into.
 * 
 *  \param  partNum
 *          - Number of the current XTRA data part; starts at 1.
 *
 *  \param  partData_len
 *          - Number of bytes in the current part.
 *
 *  \param  pPartData
 *          - Part data.
 *             Type: Array of bytes
 *             Maximum array length: 1024 bytes
 *
 *  \param  pFormatType
 *          - Format type (optional).
 *             Valid values: eQMI_LOC_XTRA_DATA = 0 (default)
 */
typedef struct{
	uint32_t totalSize;
    uint16_t totalParts;
    uint16_t partNum;
    uint16_t partData_len;
    uint8_t *pPartData;
    uint32_t *pFormatType;
}pack_loc_InjectXtraData_t;

/**
 * \ingroup loc
 * 
 * This structure contains Inject XTRA Data unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 */
typedef struct{
    uint16_t      Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_InjectXtraData_t;

/**
 * \ingroup loc
 * 
 * Inject XTRA Data
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_InjectXtraData(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_InjectXtraData_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack Inject XTRA Data
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectXtraData(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectXtraData_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Inject XTRA Data Status callback function.
 *
 *  @param  status[out]
 *          - Status of the Inject SUPL Certificate request.
 *             - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE(1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER(3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient 
 *                                                 memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are 
 *                                                     already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA
 *                                                          version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *
 *  @param[out]  pPartNum[Out][Optional]
 *              - Number of the XTRA data part for which this indication is sent.
 *              - Starts at 1.
 *              - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  @param[out]  pConstellationMask[Out][optional]
 *              - The constellation mask is set when the
 *                XTRA data is accepted by the modem
 *                GNSS engine. This optional TLV is only
 *                available when at least one constellation
 *                injection is successful, and it is only
 *                available in the last XTRA injection IND
 *                message. 
 *                - eQMI_SYSTEM_GPS (0x01) - Enable GPS
 *                - eQMI_SYSTEM_GLO (0x02) - Enable GLONASS
 *                - eQMI_SYSTEM_BDS (0x04) - Enable BDS
 *                - eQMI_SYSTEM_GAL (0x08) - Enable Galileo
 *                - eQMI_SYSTEM_QZSS (0x10) - Enable QZSS
 *              - Bit to check in ParamPresenceMask - <B>0x11</B>
 *
 *  @param[out] ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t status;
    uint16_t* pPartNum;
    uint64_t* pConstellationMask;   
    uint16_t  Tlvresult;   
    swi_uint256_t ParamPresenceMask;
} unpack_loc_InjectXtraDataInd_t;

/**
 * \ingroup loc
 * 
 * Inject XTRA Data Ind unpack
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectXtraData_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectXtraDataInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  @param  maxFileSizeInBytes
 *          - Maximum allowable predicted orbits file size (in bytes).
 *
 *  @param  maxPartSize
 *          - Maximum allowable predicted orbits file chunk size (in bytes).
 *
 * @param   pAssistanceServerUrlList_len
 *          - Number of sets of the AssistanceServerURL instances
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 * @param   pAssistanceServerURLList
 *          - Pointer to the list of Assistance Server URL
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 *
 *  @param  Tlvresult
 *          - unpack result
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t                    maxFileSizeInBytes;
    uint32_t                    maxPartSize;
    uint8_t                     *pAssistanceServerUrlList_len;
    loc_AssistanceServerURL     *pAssistanceServerURLList;
    uint16_t                    Tlvresult;
    swi_uint256_t               ParamPresenceMask;
} unpack_loc_EventInjectPredictedOrbits_Ind_t;

/**
 * \ingroup loc
 * 
 * This structure contains LOC Event Inject Predicted Orbits unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_EventInjectPredictedOrbits_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the Time Server Info.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_EventInjectPredictedOrbits_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_EventInjectPredictedOrbits_Ind_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains the Parameter for Query XTRA Info Request
 *
 *  \param  xtraConfig
 *          - XTRA configuration
 *          -Values
 *             - QMI_LOC_XTRA_CONFIG_DISABLE_AUTO_DOWNLOAD_TIMER (0x00000001) - Ask the engine to disable the XTRA auto download timer
 */
typedef struct{
    uint32_t xtraConfig;
}pack_loc_QueryXtraInfo_t;

/**
 * \ingroup loc
 * 
 * Query XTRA Info
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_QueryXtraInfo(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_QueryXtraInfo_t *reqArg
);

/**
 * \ingroup loc
 * 
 * This structure contains LOC Query XTRA Info unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_QueryXtraInfo_t;

/**
 * \ingroup loc
 * 
 * Unpack Inject XTRA Data
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_QueryXtraInfo(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_QueryXtraInfo_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains the Parameter for Query XTRA Info Indication
 *
 *  \param  status
 *          - Status of the query XTRA information.
 *             - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 * 
 *  \param  reportMask
 *          - XTRA Info The XTRA information returned from the engine.
 *          - Bitmask indicating which of the fields in this TLV are reported.
 *           - Valid values:
 *              - QMI_LOC_XTRA_INFO_MASK_ABS_AGE (0x00000001) - Number of hours for which the current XTRA information is valid
 *              - QMI_LOC_XTRA_INFO_MASK_REL_AGE (0x00000002) - Last XTRA data download time
 *              - QMI_LOC_XTRA_INFO_MASK_XTRA_SERVER (0x00000004) - XTRA server URLs
 *              - QMI_LOC_XTRA_INFO_MASK_NTP_SERVER (0x00000008) - Network Time Protocol (NTP) server URLs
 *              - QMI_LOC_XTRA_INFO_MASK_TIME_REQUEST (0x00000010) - Requests the control point to send QMI_LOC_INJECT_UTC_TIME_REQ to the engine
 *              - QMI_LOC_XTRA_INFO_MASK_PREF_VALID_AGE (0x00000020) - Preferred valid age
 * 
 *  \param  absAgeHrs
 *          - Number of hours for which the current XTRA information is valid. 
 *          - Units: Hours
 *  
 *  \param  relAgeInUTC
 *          - Last XTRA data download time in UTC.
 *          - Units: Milliseconds 
 * 
 *  \param  serverList_len
 *          - Number of sets of the pServerURLList instances
 * 
 *  \param  pServerURLList
 *          - Server URL list. See \ref loc_AssistanceServerURL
 * 
 *  \param  delayThreshold
 *          - Skip the time server if a one-way delay to the server exceeds this threshold.
 *          - Units: Milliseconds
 * 
 *  \param  timeServerList_len
 *          - Number of sets TimeServerURLList instances
 *  
 *  \param  pTimeServerURLList
 *          -  Time assistance server URL list. See \ref loc_AssistanceServerURL
 * 
 *  \param  timeRequest
 *          - Requests the control point to send QMI_LOC_INJECT_UTC_TIME_REQ to the engine.
 *          - 0x00 (FALSE) - The engine has the UTC time
 *          - 0x01 (TRUE) – Requests the control point to inject the UTC time to the engine
 * 
 *  \param  preferedValidAgeHrs
 *          - Preferred valid age.
 *          - Units: Hours
 * 
 *  \param  Tlvresult
 *          - Unpack result.
 * 
 *  \param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t    status;
    uint32_t    reportMask;
    uint16_t    absAgeHrs;
    uint64_t    relAgeInUTC;
    uint8_t     serverList_len;
    loc_AssistanceServerURL     *pServerURLList;
    uint32_t    delayThreshold;
    uint8_t     timeServerList_len;
    loc_AssistanceServerURL     *pTimeServerURLList;
    uint8_t     timeRequest;
    uint16_t    preferedValidAgeHrs;
    uint16_t    Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_QmiCbkLocQueryXtraInfoInd_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the Time Server Info.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_QueryXtraInfo_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_QmiCbkLocQueryXtraInfoInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * Get Xtra T-Session Control
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_GetXtraTSessionControl(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen
);

/**
 * \ingroup loc
 * 
 * This structure contains LOC Get Xtra T-Session Control unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_GetXtraTSessionControl_t;

/**
 * \ingroup loc
 * 
 * Unpack Get Xtra T-Session Control Data
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GetXtraTSessionControl(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_GetXtraTSessionControl_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains the Parameter for Get XTRA T-Session Indication
 *
 *  \param  status
 *          - Status of the query XTRA information.
 *             - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  \param  xtraTSessionControl
 *          - Enable/Disable XTRA-T
 *           - Indicates whether to enable XTRA-T:
 *              - 0x01 (TRUE) - Enable XTRA-T
 *              - 0x00 (FALSE) - Disable XTRA-T 
 *          - Bit to check in ParamPresenceMask - <B>0x10</B>
 * 
 *  \param  Tlvresult
 *          - Unpack result.
 * 
 *  \param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t    status;
    uint8_t     xtraTSessionControl;
    uint16_t    Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_QmiCbkGetXtraTSessionControlInd_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the Time Server Info.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_GetXtraTSessionControl_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_QmiCbkGetXtraTSessionControlInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains the Parameter for Set XTRA T-Session Control
 *
 *  \param  xtraTSessionControl
 *          - Enable/Disable XTRA-T
 *           - Indicates whether to enable XTRA-T:
 *              - 0x01 (TRUE) - Enable XTRA-T
 *              - 0x00 (FALSE) - Disable XTRA-T 
 */
typedef struct{
    uint8_t     xtraTSessionControl;
}pack_loc_SetXtraTSessionControl_t;

/**
 * \ingroup loc
 * 
 * Set Xtra T-Session Control
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] pSetXtraTSessionControl
 *              - Enable/Disable XTRA-T
 *              - \ref pack_loc_SetXtraTSessionControl_t
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_SetXtraTSessionControl(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_SetXtraTSessionControl_t *pSetXtraTSessionControl
);

/**
 * \ingroup loc
 * 
 * This structure contains LOC Set Xtra T-Session Control unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  @param ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t       Tlvresult;
    swi_uint256_t  ParamPresenceMask;
}unpack_loc_SetXtraTSessionControl_t;

/**
 * \ingroup loc
 * 
 * Unpack Get Xtra T-Session Control Data
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetXtraTSessionControl(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_SetXtraTSessionControl_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  This structure contains the Parameter for Set XTRA T-Session Indication
 *
 *  \param  status
 *          - Status of the query XTRA information.
 *             - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE (1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER (3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *          - Bit to check in ParamPresenceMask - <B>0x01</B>
 * 
 *  \param  Tlvresult
 *          - Unpack result.
 * 
 *  \param  ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint32_t    status;
    uint16_t    Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_QmiCbkSetXtraTSessionControlInd_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the Time Server Info.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_SetXtraTSessionControl_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_QmiCbkSetXtraTSessionControlInd_t *pOutput
);

/**
 * \ingroup loc
 * 
 * This structure contains Inject XTRA Pcid pack
 *
 *  \param  xtraPcid
 *          - XTRA PCID data.
 */
typedef struct{
	uint64_t xtraPcid;
}pack_loc_InjectXtraPcid_t;

/**
 * \ingroup loc
 * 
 * This structure contains Inject XTRA Pcid unpack
 *
 * \param Tlvresult
 *        - Unpack result.
 * 
 *  @param[out] ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct{
    uint16_t      Tlvresult;
    swi_uint256_t ParamPresenceMask;
}unpack_loc_InjectXtraPcid_t;

/**
 * \ingroup loc
 * 
 * Inject XTRA PCID
 * @param[in,out] pCtx qmi request context
 * @param[out] pReqBuf qmi request buffer
 * @param[out] pLen qmi request length
 * @param[in] reqArg request parameter
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int pack_loc_InjectXtraPcid(
    pack_qmi_t  *pCtx,
    uint8_t *pReqBuf,
    uint16_t *pLen,
    pack_loc_InjectXtraPcid_t *reqArg
);

/**
 * \ingroup loc
 * 
 * Unpack Inject XTRA PCID
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectXtraPcid(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_InjectXtraPcid_t *pOutput
);

/**
 * \ingroup loc
 * 
 *  Inject XTRA PCID Status callback function.
 *
 *  @param  status[out]
 *          - Status of the Inject SUPL Certificate request.
 *             - Valid values:
 *              - eQMI_LOC_SUCCESS (0) - Request was completed successfully
 *              - eQMI_LOC_GENERAL_FAILURE(1) - Request failed because of a general failure
 *              - eQMI_LOC_UNSUPPORTED (2) - Request failed because it is not supported
 *              - eQMI_LOC_INVALID_PARAMETER(3) - Request failed because it contained invalid parameters
 *              - eQMI_LOC_ENGINE_BUSY (4) - Request failed because the engine is busy
 *              - eQMI_LOC_PHONE_OFFLINE (5) - Request failed because the phone is offline
 *              - eQMI_LOC_TIMEOUT (6) - Request failed because it has timed out
 *              - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) - Request failed because an undefined configuration was requested
 *              - eQMI_LOC_INSUFFICIENT_MEMORY (8) - Request failed because the engine could not allocate sufficient 
 *                                                 memory for the request
 *              - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) - Request failed because the maximum number of Geofences are 
 *                                                     already programmed
 *              - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) - Location service failed because of an XTRA
 *                                                          version-based file format check failure
 *              - eQMI_LOC_GNSS_DISABLED (11) - Request failed because the location service is disabled
 *
 * \param Tlvresult
 *        - Unpack result.
 *
 *  @param[out] ParamPresenceMask
 *          - bitmask representation to indicate valid parameters.
 */
typedef struct
{
    uint32_t status;
    uint16_t  Tlvresult;   
    swi_uint256_t ParamPresenceMask;
} unpack_loc_QmiCbkInjectXtraPcidInd_t;

/**
 * \ingroup loc
 * 
 * Unpack the engine to use the Time Server Info.
 * @param[in] pResp qmi response
 * @param[in] respLen qmi response length
 * @param[out] pOutput unpacked response
 *
 * @return eQCWWAN_ERR_NONE on success, eQCWWAN_xxx error value otherwise
 *
 * @sa     See qmerrno.h for eQCWWAN_xxx error values
 */
int unpack_loc_InjectXtraPcid_Ind(
    uint8_t *pResp,
    uint16_t respLen,
    unpack_loc_QmiCbkInjectXtraPcidInd_t *pOutput
);

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif
