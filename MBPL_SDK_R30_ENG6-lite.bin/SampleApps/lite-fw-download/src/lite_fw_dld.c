#include "lite_fw_dld.h"
#include "dev_util.h"
#include "sysinfo.h"
#include "MbimLogging.h"
#include "QmuxLogging.h"
#include "errno.h"
#include "time.h"
#include "sys/time.h"

#define debug 0

/*
 * To indicate device nodes are created manually
 */

#ifdef API
static bool bDMreset = false;
#endif
static FILE *fpLogFile = NULL;
static int  iUARTMode = -1;


void PrintUsage()
{
    printf( "\r\n" );
    printf( "App usage: \r\n\r\n" );
    printf( " <appName> -f <FW path> -s <File name> -c <QMI/MBIM mode> -d <QDL Port> -p <QMI/MBIM device path> -P <USB device location path> -t <Download type> -w <FW image preference> -n <PRI image preference> -m <chipset> -l <Log file path> -x <Image type> -h -a -o -r -F\n\n" );
    printf( "  -f --fwpath <folder to firmware images>\n" );
    printf( "       This specifies the folder location of the firmware images to be downloaded. This option is mandatory.\n" );
    printf( "       Example: -f Images\n\n");
    printf( "  -s --singlefile <File name>\n");
    printf( "       This optional command specifies one single file from the firmware folder to be downloaded.\n");
    printf( "       Once used, the application will ignore other files from the firmware folder.\n");
    printf( "       This option needs to be used together with option -f.\n");
    printf( "       Example: -s SWIX55C_01.07.08.00.cwe\n\n");
    printf( "  -c --devmode <QMI/MBIM>\n");
    printf( "       This optinal command is obsolete.  It specifies the mode of the device, MBIM or QMI.\n");
    printf( "       The application will determine the mode if this option is not specified.\n");
    printf( "       Example: -c QMI\n\n");
    printf( "  -d --qdl <QDL port path>\n");
    printf( "       Specifies the QDL port path when modem switches to BOOT and HOLD mode to download firmware.\n");
    printf( "       Example: -d /dev/mhiqdl0\n\n");
    printf( "  -p --devpath <QMI/MBIM device path>\n");
    printf( "       Specifies the QMI or MBIM device path.\n");
    printf( "       Example: -p /dev/mhi_0306_00.01.00_pipe_12\n\n");
    printf( "  -P --usbpath <USB device location path>\n");
    printf( "       Specifies the USB device location info in a format of bus#-port# or bus#-hub#.port#.\n");
    printf( "       When this option is in use, both -d and -p options are ignored.\n");
    printf( "       This feature only applies to 9x50/9x07/SDX55 based modems in USB mode.\n");
    printf( "       For 9x30 based devices, it only works if devices are connected via USB2.\n");
    printf( "       Example: -P 2-9 or -P 1-1.2 or -P /sys/bus/usb/devices/2-9\n\n");
    printf( "  -t --type <Download type>\n");
    printf( "       Specifies the FW download type, image switching or non image switching.\n");
    printf( "       - 1: Single FW image switching where the FW image will be placed in a FW slot\n");
    printf( "       - 2: Non image switching FW download where FW images will not be placed in FW slots\n");
    printf( "       - 3: Multi-FW image switching where the FW images will be placed in FW slots\n");
    printf( "            This value implies a force download (no explicit -F option required) and\n");
    printf( "            has to be used together with -w/-n combination to indicate the desired image preferences\n");
    printf( "       Example: -t 2\n\n");
    printf( "  -w --cwe <FW image pref>\n");
    printf( "       Specifies the file name of firmware image preference.\n");
    printf( "       This option has to be used in pair with option -n.\n");
    printf( "       Example: -w SWIX55C_01.07.08.00.cwe\n\n");
    printf( "  -n --nvu <PRI image pref>\n");
    printf( "       Specifies the file name of carrier PRI image preference.\n");
    printf( "       This option has to be used in pair with option -w.\n");
    printf( "       Example: -n SWIX55C_01.07.08.00_GENERIC_016.003_000.nvu\n\n");
    printf( "  -m --modelfamily <chipset> \n" );
    printf( "       This optional command is obsolete.  It specifies the device chipset family.\n");
    printf( "       The application will determine the chipset family if this option is not specified.\n");
//    printf( "          - 0: Auto Detect (default value)\n" );
    printf( "       - 1: 9x15 Family\n" );
//    printf( "          - 2: WP9x15 Family\n" );    
    printf( "       - 3: 9x30 Family\n" );
    printf( "       - 4: 9x07 or 9x50 or SDX55 Family\n" );
//    printf( "          - 5: 9x06 Family\n\n" );
    printf( "       Example: -m 3\n\n");
    printf( "  -l --logfile <Log file> \n" );
    printf( "       Specify custom log path.  If not used, the log is saved in fwdwl.log file.\n" );
    printf( "       Example: -l log.txt\n\n");
    printf( "  -x --deleteimages <Image type>\n");
    printf( "       Delete all device stored images which have the specified image type.\n");
    printf( "       -0: FW images\n");
    printf( "       -1: PRI images\n");
    printf( "       -255: All images\n");
    printf( "       Example: -x 255\n\n");
    printf( "  -R --retry <number of device connection retries>\n");
    printf( "       Specify number of device connection retries after a FW download.\n");
    printf( "       The retry interval is 5 seconds.  The application retries 48 times\n");
    printf( "       if this option is omitted.\n");
    printf( "       Example: -R 5\n\n");
    printf( "  -D --syncdelay <number of seconds to delay>\n");
    printf( "       Specify number of seconds to delay after application sends control sync request to device.\n");
    printf( "       Zero indicates no delay.  The default is to delay 1 second if this option is omitted.\n");
    printf( "       Example: -D 3\n\n");
    printf( "  -a --autosim\n");
    printf( "       This option enables device AUTO-SIM image switching feature.\n\n");
    printf( "  -o --openwrt\n");
    printf( "       This option indicates applicatin is running on an OpenWrt platform.\n\n");
    printf( "  -h --help  \n" );
    printf( "       This option prints the usage instructions.\n\n" );
    printf( "  -v --version\n");
    printf( "       This option prints the application binary version.\n\n");
    printf( "  -F --force\n");
    printf( "       This option requests force FW download on an image switch.\n\n");
    printf( "  -i --fileinfo\n");
    printf( "       This option displays the file info of the images specified with -f option.\n");
    printf( "       The application will exit without performing FW downloads.\n\n");
    printf( "  -b --blocksize <read block size> \n" );
    printf( "       File Read Block Size in bytes.\n" );
    printf( "       Example: -b 4096\n\n");
    printf( "  -r --reset\n");
    printf( "       Resets device when device is in BOOT AND HOLD mode.\n");
    printf( "       This option only applies to devices that use Sahara protocol in BOOT AND HOLD mode,\n");
    printf( "       including 9x50, 9x07, SDX55 and SDX62/65 based devices.\n\n");
//    printf( "  -e --debuglogsflag  \n" );
//    printf( "       - 0 : Disable debug logs.\n" );
//    printf( "       - 1 : Enable debug logs.\n" );
//    printf( "       Example: -e 1\n\n");
//    printf( "  -u --enable/disable UART mode on firehose protocol  \n" );
//    printf( "           - 0 : Disable.\n" );
//    printf( "           - 1 : Enable.\n\n" );
//    printf( " This operation only supports when modem is in App mode.\n" );
//    printf( " Don't use this option when modem is already in QDL mode.\n" );
//    printf( " This option should not be used in normal download operation.\n" );
//    printf( " Modem will not be reset on QDL mode\n\n" );
}

/* Command line options to firmware download tool */
const char * const short_options = "t:c:d:p:g:f:l:b:m:e:u:w:n:R:hirvaoD:FP:s:x:";

/* Command line long options for firmware download tool */
const struct option long_options[] = 
{
    {"version",         0,  NULL,   'v'},   /* Prints binary verson */
    {"type",            1,  NULL,   't'},   /* Download type */
    {"cwe",             1,  NULL,   'w'},   /* CWE FW image preference */
    {"nvu",             1,  NULL,   'n'},   /* NVU PRI image preference */
    {"singlefile",      1,  NULL,   's'},   /* Single file to be downloaded */
    {"help",            0,  NULL,   'h'},   /* Provides terse help to users */
    {"devmode",         1,  NULL,   'c'},   /* Device mode QMI or MBIM */
    {"qdl",             1,  NULL,   'd'},   /* QDL port path */
    {"devpath",         1,  NULL,   'p'},   /* QMI/MBIM device path */
    {"dmport",          1,  NULL,   'g'},   /* DM port device path */
    {"fwpath",          1,  NULL,   'f'},   /* FW files path */
    {"logfile",         1,  NULL,   'l'},   /* custom log file path */
    {"force",           0,  NULL,   'F'},   /* Force FW download on image switching */
    {"blocksize",       1,  NULL,   'b'},   /* Read Block Size */
    {"modelfamily",     1,  NULL,   'm'},   /* model family */
    {"debuglogsflag",   1,  NULL,   'e'},   /* debug logs flag */
    {"fileinfo",        0,  NULL,   'i'},   /* Display file info */
    {"retry",           1,  NULL,   'R'},   /* Number of device connection retries after FW download */
    {"reset",           0,  NULL,   'r'},   /* Reset device when device is in B&H mode */
    {"uartmode",        0,  NULL,   'u'},   /* uartmode flag */
    {"usbpath",         1,  NULL,   'P'},   /* USB device path */
    {"autosim",         0,  NULL,   'a'},   /* Enable device auto SIM image switch */
    {"openwrt",         0,  NULL,   'o'},   /* Indicating OpenWrt platforms */
    {"syncdelay",       1,  NULL,   'D'},   /* Number of seconds to delay after control sync request */
    {"deleteimages",    1,  NULL,   'x'},   /* Delete device stored images */
    {NULL,              0,  NULL,   0 }     /* End of list */
};

#define SYS_FS_TTY_PATH "/sys/class/tty/"
#define SYS_FS_TTY_SERIAL_PATH "/device/GobiSerial/ttyUSB"
#define SYS_FS_TTY_DEVICE_MODULE "/device/driver/"


const char * UdevRuleMmIgnore = "SUBSYSTEM==\"usb\", ATTRS{idVendor}==\"1199\", GROUP=\"users\", MODE=\"0666\", ENV{ID_MM_DEVICE_IGNORE}=\"1\"";

#if 0
int UpdateTTYUSBPath(char *qdl_dev_path)
{
    DIR *dir;
    struct dirent *ent;
    struct stat statbuf;
    char buf[1024];
    char linkpath[1024];
    ssize_t len;
    if ((dir = opendir (SYS_FS_TTY_PATH)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            snprintf(linkpath,1023,"%s%s",SYS_FS_TTY_PATH,ent->d_name);
            if (lstat(linkpath, &statbuf) != 0)
                continue;
            if ((len = readlink(linkpath, buf, sizeof(buf)-1)) != -1)
            {
                buf[len] = '\0';
                if(strstr(buf,".0/ttyUSB"))
                {
                    snprintf(linkpath,1023,"%s%s%s%s/driver",SYS_FS_TTY_PATH,ent->d_name,SYS_FS_TTY_DEVICE_MODULE, ent->d_name);
                    if (lstat(linkpath, &statbuf) != 0)
                         continue;
                    if ((len = readlink(linkpath, buf, sizeof(buf)-1)) != -1)
                    {
                        buf[len] = '\0';
                        if(strstr(buf,"GobiSerial"))
                        {
                            snprintf(qdl_dev_path,MAX_PATH_LEN-1,"/dev/%s",ent->d_name);
                            if (debug)
                                fprintf(stderr,"---Auto TTY PATH:%s---\n",qdl_dev_path);
                            break;
                        }
                    }
                }
            }
        }
        closedir (dir);
    }
    else
    {
        return -1;
    }
    return 0;
}

int GetTTYUSBPath(char *qdl_dev_path ,char *qdl_usb_path, unsigned int sizeofusbpath)
{
    DIR *dir;
    struct dirent *ent;
    struct stat statbuf;
    char pathbuf[1024];
    char buf[1024];
    char linkpath[1024];
    ssize_t len;
    char *pUSBPATH = NULL;
    char *ppathbuf = NULL;
    ppathbuf = (char *)&pathbuf;
    memset(qdl_usb_path,0,sizeofusbpath);
    if ((dir = opendir (SYS_FS_TTY_PATH)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            snprintf(linkpath,1023,"%s%s",SYS_FS_TTY_PATH,ent->d_name);
            if (lstat(linkpath, &statbuf) != 0)
                continue;
            if ((len = readlink(linkpath, pathbuf, sizeof(pathbuf)-1)) != -1)
            {
                pathbuf[len] = '\0';
                pUSBPATH = strstr(pathbuf,".0/ttyUSB");
                if(pUSBPATH)
                {
                    snprintf(linkpath,1023,"%s%s%s%s/driver",SYS_FS_TTY_PATH,ent->d_name,SYS_FS_TTY_DEVICE_MODULE, ent->d_name);
                    if (lstat(linkpath, &statbuf) != 0)
                         continue;
                    if ((len = readlink(linkpath, buf, sizeof(buf)-1)) != -1)
                    {
                        buf[len] = '\0';
                        if(strstr(buf,"qcserial"))
                        {
                            unsigned int length = 0;
                            snprintf(qdl_dev_path,MAX_PATH_LEN-1,"/dev/%s",ent->d_name);
                            if (debug)
                                fprintf(stderr,"---DEV TTY PATH:%s---\n",qdl_dev_path);
                            pUSBPATH = strstr(pathbuf,ent->d_name);
                            length = pUSBPATH - ppathbuf;
                            if(sizeofusbpath>length)
                            {
                                snprintf(qdl_usb_path,length+strlen(SYS_FS_TTY_PATH),"%s%s",SYS_FS_TTY_PATH, pathbuf);
                                if (debug)
                                    fprintf(stderr,"---DEV USB PATH:%s---\n",qdl_usb_path);
                            }
                            break;
                        }
                    }
                }
            }
        }
        closedir (dir);
    }
    else
    {
        return -1;
    }
    return 0;
}

int CheckTTYUSBPath(char *qdl_dev_path)
{
    DIR *dir;
    struct dirent *ent;
    struct stat statbuf;
    char buf[1024];
    char linkpath[1024];
    char devicename[64];
    int iDeviceExist = 0;
    ssize_t len;
    char *ttyName = strstr(qdl_dev_path,"/");
    if(ttyName==NULL)
        return -1;
    snprintf(devicename,63,".0/%s",ttyName+1);
    if ((dir = opendir (SYS_FS_TTY_PATH)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            snprintf(linkpath,1023,"%s%s",SYS_FS_TTY_PATH,ent->d_name);
            if (lstat(linkpath, &statbuf) != 0)
                continue;
            if ((len = readlink(linkpath, buf, sizeof(buf)-1)) != -1)
            {
                buf[len] = '\0';
                if(strstr(buf,devicename))
                {
                    iDeviceExist = 1;
                    break;
                }
            }
        }
        closedir (dir);
    }
    else
    {
        return -1;
    }
    return iDeviceExist;
}
#endif

void print_version()
{
    fprintf(stderr, "Application version: %s\n", VERSION_STRING);
    litefw_syslog_proxy(eLOG_DEBUG, VERSION_STRING);
}

int parseSwitches( int argc, char **argv, struct _userOptions *puserOptData)
{
    if (NULL == puserOptData)
        return eLITE_FWDWL_APP_ERR_INVALID_ARG;

    int next_option;

    /* Parse the command line before doing anything else */
    do
    {
        /* Read the next option until there are no more */
        next_option = getopt_long( argc, argv,
                                   short_options,
                                   long_options, NULL );

        switch( next_option )
        {
            case 'v':
                /* Print binary version */
                print_version();
                exit(eLITE_FWDWL_APP_OK);
                break;

            case 'F':
                puserOptData->force_download = true;
                break;

            case 'x':
                puserOptData->delete_images = true;
                puserOptData->image_type_to_delete = atoi(optarg);
                break;

            case 'o':
                puserOptData->is_openwrt = true;
                break;

            case 'h':
                /* Print usage information */
                PrintUsage();
                exit (eLITE_FWDWL_APP_OK);
                break;

            case 'a':
                puserOptData->enable_auto_sim = true;
                break;

            case 'P':
                /* Caller specified USB location path in bus-port format */
                if (optarg[strlen(optarg) - 1] == '/')
                {
                    // Remove the last '/'
                    optarg[strlen(optarg) - 1] = 0;
                }

                {
					char* p = strrchr(optarg, '/');
					strncpy(puserOptData->usb_path, p ? p + 1 : optarg, USB_PATH_LEN - 1);
                }
                
                break;

            case 'c':
                /* caller specifies the mode*/
                if (strcmp(optarg, "MBIM") == 0 || strcmp(optarg, "QMI") == 0)
                {
                    strncpy (puserOptData->dev_mode_str,optarg,DEV_MODE_STR_LEN-1);
                }
                break;

            case 'd':
                /* caller specifies the QDL port*/
                strncpy (puserOptData->qdl_dev_path,optarg,MAX_PATH_LEN-1);
                break;

            case 'p':
                /* caller specifies the QMI/MBIM device*/
                strncpy (puserOptData->dev_path,optarg,MAX_PATH_LEN-1);
                break;

            case 'g':
                /* caller specifies the DM port */
                strncpy (puserOptData->dm_path, optarg, MAX_PATH_LEN-1);
                break;

            case 'f':
                /* caller specifies the FW path*/
                strncpy (puserOptData->fw_image_path,optarg,MAX_PATH_LEN-1);
                break;

            case 'w':
                /* caller specified cwe FW image preference */
                strncpy(puserOptData->cwe_image_pref, optarg, NAME_MAX - 1);
                break;

            case 'n':
                /* caller specified nvu PRI image preference */
                strncpy(puserOptData->nvu_image_pref, optarg, NAME_MAX - 1);
                break;

            case 's':
                /* caller specified only one file needs to be downloaded */
                strncpy(puserOptData->single_file, optarg, NAME_MAX - 1);
                break;

            case '?':
                /* Caller has used an invalid option */
                printf("\nInvalid option\n" );

                /* Print the usage info and exit */
                PrintUsage();
                exit(eLITE_FWDWL_APP_OK);
                break;

            case 'l':
                /* Log file path*/
                strncpy (puserOptData->log_file_path,optarg,MAX_PATH_LEN-1);
                break;

            case 'b':
                puserOptData->lBlockSize= atol(optarg);
                break;

            case 'D':
                puserOptData->sync_delay = atoi(optarg);
                break;

            case 'm':
                puserOptData->modelfamily = atoi(optarg);
                break;

            case 't':
                puserOptData->download_type = atoi(optarg);
                break;

            case 'e':
                litefw_logsenable(atoi(optarg));
                break;

            case 'R':
                puserOptData->num_of_dev_retries = atoi(optarg);
                break;

            case 'r':
                puserOptData->reset_device = true;
                break;

            case 'u':
                iUARTMode = atoi(optarg);
                if(iUARTMode!=1)
                    iUARTMode = 0;
                if(iUARTMode == 1)
                {
                    iUARTMode = eQDL_MODE_UART0;
                }
                break;

            case 'i':
                puserOptData->show_img_info = true;
                break;

            case -1:
                /* Done with options list */
                break;

            default:
                exit(eLITE_FWDWL_APP_OK);
                break;
        }
    }
    while( next_option != -1 );
    return eLITE_FWDWL_APP_OK;
}

void InitParams(struct _userOptions *puserOptData)
{
    if (0==strlen(puserOptData->fw_image_path) && !puserOptData->enable_auto_sim)
    {
        printf ("Firmware path is mandatory\n");
        PrintUsage();
        litefw_syslog_proxy(eLOG_DEBUG, "Firmware path is not specified, application terminates.");
        exit(eLITE_FWDWL_APP_ERR_INVALID_ARG);
    }

    if (puserOptData->show_img_info)
    {
        // HSWOEMP-2556: If the user just want to see image info, no need to check for device presence or related info.
        return;
    }
    
    if ((strlen(puserOptData->cwe_image_pref) != 0 && strlen(puserOptData->nvu_image_pref) == 0) ||
        (strlen(puserOptData->cwe_image_pref) == 0 && strlen(puserOptData->nvu_image_pref) != 0))
    {
        printf("Images preference should be specified as a pair\n");
        PrintUsage();
        litefw_syslog_proxy(eLOG_DEBUG, "Images preference is partially specified, application terminates.");
        exit(eLITE_FWDWL_APP_ERR_INVALID_ARG);
    }

    if (puserOptData->num_of_dev_retries == 0)
    {
        puserOptData->num_of_dev_retries = DEFAULT_DEV_CONN_RETRIES;
    }

    return;
}

void litefw_syslog_proxy(uint8_t lvl, const char *buff, ...)
{
    char time[64] = "Uknown time";

    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0)
    {
        struct tm * tm = localtime(&tv.tv_sec);
        if (tm != NULL)
        {
            snprintf(time, 64, "%02d:%02d:%02d.%03d", tm->tm_hour, tm->tm_min, tm->tm_sec, (int) (tv.tv_usec / 1000));
        }
    }

    if (fpLogFile!=NULL)
    {
        fprintf(fpLogFile, "[%s][%d]%s\n",time,lvl, buff);
        fflush(fpLogFile);
    }
}

void print_time()
{
    time_t T = time(NULL);
    struct tm* tm = localtime(&T);

    char sys_time[128] = "";
	if (tm)
		sprintf(sys_time, "System date/time: %02d/%02d/%04d %2d:%02d:%02d",
			tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
	else
		strcpy(sys_time, "System date/time: unknown");

	litefw_syslog_proxy(eLOG_DEBUG, sys_time);
}

void start_logging(struct _userOptions * puserOptData, int argc, char * argv[])
{
    char file_access_opt[4] = "";

    if (strlen(puserOptData->log_file_path) == 0)
    {
        strcpy(puserOptData->log_file_path, "fwdwl.log");
        strcpy(file_access_opt, "w");
    }
    else
    {
        strcpy(file_access_opt, "a+");
    }

    fpLogFile = fopen(puserOptData->log_file_path, file_access_opt);
    if(fpLogFile==NULL)
    {
        fprintf(stderr,"Log File Error %s!",puserOptData->log_file_path);
    }
    else
    {
        litefw_set_log_func(&litefw_syslog_proxy);
        helper_set_log_func(&litefw_syslog_proxy);
        set_litembim_logger_func(&litefw_syslog_proxy);
        set_liteqmux_logger_func(&litefw_syslog_proxy);
        set_log_func(&litefw_syslog_proxy);
    }

    print_time();
    print_version();

    log_mods_info();

    for (int i = 0; i < argc; i++)
    {
        litefw_syslog_proxy(eLOG_DEBUG, argv[i]);
    }
}

int parse_ps_outputline(char * line, char * pn)
{
    char pid[PID_NAME_SIZE] = "";
    char * tmp = NULL;

    if (pn == NULL)
    {
        return -1;
    }

    if (strstr(line, pn))
    {
        tmp = strtok(line," \n");
        if (tmp == NULL)
        {
            return -1;
        }

        if (strlen(tmp) >= PID_NAME_SIZE)
        {
            return -1;
        }

        strncpy(pid, tmp, PID_NAME_SIZE - 1);

        if (atoi(pid) != getpid())
        {
            return atoi(pid);
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int get_pid_of(char * pn)
{
    char line[MAX_LINE_LEN] = "";
    int pid = -1;
    FILE * cmd = NULL;

    cmd = popen("ps -e", "r");
    if (cmd != NULL)
    {
        setbuf(cmd, NULL);
        /* ps -e or ps displays output like this :
           PID TTY       TIME    CMD
           1   ?        00:00:07 init
           2   ?        00:00:00 kthreadd
    
           - First line is ignored, From each subsequent line
             PID, TTY, TIME and CMD is fetched
           - PID and CMD value is stored
           - If CMD matches with pn, pid is returned
           */
        while(fgets(line, MAX_LINE_LEN, cmd) == NULL);
    
        /* Traverse each line in the output of "ps -e" */
        while (fgets(line, MAX_LINE_LEN, cmd) != NULL)
        {
            /* Parse each line of PID and CMD value */
            pid  = parse_ps_outputline(line, pn);
            if (pid != -1)
            {
                /* we found the target process */
                break;
            }
        }
 
        //flush to avoid pclose hang
        while (fgets(line, MAX_LINE_LEN, cmd) != NULL);
        /* pclose ps */
        pclose( cmd );
    }
    else
    {
        litefw_syslog_proxy(eLOG_DEBUG, "popen \"ps -e\" failed");
    }

    return pid;
}

int check_modem_manager()
{
    int rc = 0;

    if (get_pid_of("ModemManager") > 0 || get_pid_of("modem-manager") > 0)
    {
        char str[256 ] = "";
        FILE * fp = fopen("/etc/udev/rules.d/99-sierrawireless-modem.rules", "r");

        if (fp != NULL)
        {
            if (fgets(str, 256, fp) == NULL || strstr(str, UdevRuleMmIgnore) == NULL)
            {
                rc = eLITE_FWDWL_APP_ERR_MODEM_MANAGER_CONFLICT;
            }

            fclose(fp);
        }
        else
        {
            rc = eLITE_FWDWL_APP_ERR_MODEM_MANAGER_CONFLICT;
        }
        
    }

    if (rc == eLITE_FWDWL_APP_ERR_MODEM_MANAGER_CONFLICT)
    {
        printf("lite-fw-download does not work with ModemManager.\n");
        printf("You can uninstall or kill the running process by:\n");
        printf("  sudo apt remove modemmanager\n");
        printf("  sudo killall ModemManager\n");
        printf("  sudo systemctl stop ModemManager\n");
        printf("  sudo systemctl disable ModemManager\n");
    }

    return rc;
}

int display_images_info(struct _userOptions * pUserOptData)
{
    int image_list_size = 0;
    image_node_t * images_list = NULL;
    if (!get_image_list(pUserOptData, &image_list_size, &images_list, true))
    {
        return eLITE_FWDWL_APP_ERR_INVALID_ARG;
    }
    
    if (image_list_size == 0)
    {
        printf("There is no image for displaying file info.\n");
        return eLITE_FWDWL_APP_ERR_NO_IMAGE_TO_DOWNLOAD;
    }

    image_node_t * pTemp = NULL;
    int ret = 0;

    do
    {
        pTemp = images_list;

        if (!pTemp)
        {
            litefw_syslog_proxy(eLOG_DEBUG, "image_list end reached when displaying images info");
            break;
        }
        else
        {
            litefw_FirmwareInfo img_info;
            memset(&img_info, 0, sizeof(litefw_FirmwareInfo));

            ret = litefw_ExtractImageParamsByFile(pTemp->full_file_name, &img_info);
            if (ret == 0)
            {
                char temp[256] = "";
                snprintf(temp, 256, "Image: %s", pTemp->full_file_name);
                litefw_syslog_proxy(eLOG_DEBUG, temp);

                memset(temp, 0, 256);
                snprintf(temp, 256, "Model ID: %s", img_info.szModelid_str);
                litefw_syslog_proxy(eLOG_DEBUG, temp);

                memset(temp, 0, 256);
                snprintf(temp, 256, "FW version: %s", img_info.szFwversion_str);
                litefw_syslog_proxy(eLOG_DEBUG, temp);

                memset(temp, 0, 256);
                snprintf(temp, 256, "Carrier string: %s", img_info.szCarrier_str);
                litefw_syslog_proxy(eLOG_DEBUG, temp);

                memset(temp, 0, 256);
                snprintf(temp, 256, "Carrier PRI version: %s", img_info.szCarrierPriversion_str);
                litefw_syslog_proxy(eLOG_DEBUG, temp);

                memset(temp, 0, 256);
                snprintf(temp, 256, "Package ID: %s", img_info.szPackageid_str);
                litefw_syslog_proxy(eLOG_DEBUG, temp);

                memset(temp, 0, 256);
                snprintf(temp, 256, "SKU: %s", img_info.szSku_str);
                litefw_syslog_proxy(eLOG_DEBUG, temp);

                printf("Image: %s\n", pTemp->full_file_name);
                printf("Model ID: %s\n", img_info.szModelid_str);
                printf("FW version: %s\n", img_info.szFwversion_str);
                printf("Carrier string: %s\n", img_info.szCarrier_str);
                printf("Carrier PRI version: %s\n", img_info.szCarrierPriversion_str);
                printf("Package ID: %s\n", img_info.szPackageid_str);
                printf("SKU: %s\n", img_info.szSku_str);
            }

            images_list = images_list->next;
        }
    } while (true);

    return eLITE_FWDWL_APP_OK;
}

int main( int argc, char *argv[])
{
    setbuf(stderr,NULL);

    /* Parse the command line switches  */
    struct _userOptions userOptData;
    memset(&userOptData, 0, sizeof(userOptData));
    userOptData.sync_delay = DEFAULT_SYNC_REQ_DELAY;
    parseSwitches(argc, argv, &userOptData);

//    UpdateTTYUSBPath((char*)&userOptData.qdl_dev_path);
//    GetTTYUSBPath((char*)&userOptData.qdl_dev_path,(char*)&userOptData.qdl_usb_path,MAX_USB_PATH_LEN);
    start_logging(&userOptData, argc, argv);

    int ret = eLITE_FWDWL_APP_UNDEFINED;
    if (!userOptData.is_openwrt)
    {
        ret = check_modem_manager();
        if (ret == eLITE_FWDWL_APP_ERR_MODEM_MANAGER_CONFLICT)
        {
            litefw_syslog_proxy(eLOG_DEBUG, "Conflict with modem manager");
            return ret;
        }
    }

    if (!userOptData.reset_device && !userOptData.delete_images)
    {
        InitParams(&userOptData);
    }

    litefw_SetReadBlockSize(userOptData.lBlockSize);
    
    if (userOptData.show_img_info)
    {
        ret = display_images_info(&userOptData);
    }
    else
    {
        ret = litefw_download (userOptData);
    }

    if(fpLogFile!=NULL)
    {
        fclose(fpLogFile);
    }

    return ret; 
}
