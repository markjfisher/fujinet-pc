#ifndef _FN_CONFIG_H
#define _FN_CONFIG_H

#include <string>

#include "../sio/printer.h"

#define CONFIG_FILENAME "fnconfig.ini"
#define SD_CARD_DIR "SD"
#define WEB_SERVER_LISTEN_URL "http://0.0.0.0:8000"

#define MAX_HOST_SLOTS 8
#define MAX_MOUNT_SLOTS 8
#define MAX_PRINTER_SLOTS 4
#define MAX_TAPE_SLOTS 1
#define MAX_PB_SLOTS 16

#define BASE_TAPE_SLOT 0x1A

#define HOST_SLOT_INVALID -1

#define HSIO_DISABLED_INDEX -1  // HSIO disabled, use standard speed only

#define CONFIG_DEFAULT_NETSIO_PORT 9997

class fnConfig
{
public:
    enum host_types
    {
        HOSTTYPE_SD = 0,
        HOSTTYPE_TNFS,
        HOSTTYPE_INVALID
    };
    typedef host_types host_type_t;
    host_type_t host_type_from_string(const char *str);

    enum mount_modes
    {
        MOUNTMODE_READ = 0,
        MOUNTMODE_WRITE,
        MOUNTMODE_INVALID
    };
    typedef mount_modes mount_mode_t;
    mount_mode_t mount_mode_from_string(const char *str);

    enum mount_types
    {
        MOUNTTYPE_DISK = 0,
        MOUNTTYPE_TAPE
    };
    typedef mount_types mount_type_t;

    enum serial_command_pin
    {
        SERIAL_COMMAND_NONE = 0,
        SERIAL_COMMAND_DSR,
        SERIAL_COMMAND_CTS,
        SERIAL_COMMAND_RI,
        SERIAL_COMMAND_INVALID
    };
    // typedef serial_command_pin serial_command_pin_t;
    serial_command_pin serial_command_from_string(const char *str);

    enum serial_proceed_pin
    {
        SERIAL_PROCEED_NONE = 0,
        SERIAL_PROCEED_DTR,
        SERIAL_PROCEED_RTS,
        SERIAL_PROCEED_INVALID
    };
    // typedef serial_proceed_pin serial_proceed_pin_t;
    serial_proceed_pin serial_proceed_from_string(const char *str);

    // GENERAL
    std::string get_general_devicename() { return _general.devicename; };
    int get_general_hsioindex() { return _general.hsio_index; };
    std::string get_general_timezone() { return _general.timezone; };
    bool get_general_rotation_sounds() { return _general.rotation_sounds; };
    std::string get_network_midimaze_host() { return _network.midimaze_host; };
    bool get_general_config_enabled() { return _general.config_enabled; };
    void store_general_devicename(const char *devicename);
    void store_general_hsioindex(int hsio_index);
    void store_general_timezone(const char *timezone);
    void store_general_rotation_sounds(bool rotation_sounds);
    void store_general_config_enabled(bool config_enabled);
    bool get_general_boot_mode() { return _general.boot_mode; }
    void store_general_boot_mode(uint8_t boot_mode);
    void store_midimaze_host(const char host_ip[64]);
    std::string get_general_interface_url() { return _general.interface_url; };
    void store_general_interface_url(const char *url);
    std::string get_general_config_path() { return _general.config_file_path; };
    void store_general_config_path(const char *file_path);
    std::string get_general_SD_path() { return _general.SD_dir_path; };
    void store_general_SD_path(const char *dir_path);

    const char * get_network_sntpserver() { return _network.sntpserver; };

    // SERIAL PORT
    std::string get_serial_port() { return _serial.port; };
    serial_command_pin get_serial_command() { return _serial.command; };
    serial_proceed_pin get_serial_proceed() { return _serial.proceed; };
    void store_serial_port(const char *port);
    void store_serial_command(serial_command_pin command_pin);
    void store_serial_proceed(serial_proceed_pin proceed_pin);

    // WIFI
    bool have_wifi_info() { return _wifi.ssid.empty() == false; };
    std::string get_wifi_ssid() { return _wifi.ssid; };
    std::string get_wifi_passphrase() { return _wifi.passphrase; };
    void store_wifi_ssid(const char *ssid_octets, int num_octets);
    void store_wifi_passphrase(const char *passphrase_octets, int num_octets);
    void reset_wifi() { _wifi.ssid.clear(); _wifi.passphrase.clear(); };

    // BLUETOOTH
    void store_bt_status(bool status);
    bool get_bt_status() { return _bt.bt_status; };
    void store_bt_baud(int baud);
    int get_bt_baud() { return _bt.bt_baud; };
    void store_bt_devname(std::string devname);
    std::string get_bt_devname() { return _bt.bt_devname; };

    // HOSTS
    std::string get_host_name(uint8_t num);
    host_type_t get_host_type(uint8_t num);
    void store_host(uint8_t num, const char *hostname, host_type_t type);
    void clear_host(uint8_t num);

    // PHONEBOOK SLOTS
    std::string get_pb_host_name(const char *pbnum);
    std::string get_pb_host_port(const char *pbnum);
    std::string get_pb_entry(uint8_t n);
    bool add_pb_number(const char *pbnum, const char *pbhost, const char *pbport);
    bool del_pb_number(const char *pbnum);
    void clear_pb(void);

    // MOUNTS
    std::string get_mount_path(uint8_t num, mount_type_t mounttype = mount_type_t::MOUNTTYPE_DISK);
    mount_mode_t get_mount_mode(uint8_t num, mount_type_t mounttype = mount_type_t::MOUNTTYPE_DISK);
    int get_mount_host_slot(uint8_t num, mount_type_t mounttype = mount_type_t::MOUNTTYPE_DISK);
    void store_mount(uint8_t num, int hostslot, const char *path, mount_mode_t mode, mount_type_t mounttype = mount_type_t::MOUNTTYPE_DISK);
    void clear_mount(uint8_t num, mount_type_t mounttype = mount_type_t::MOUNTTYPE_DISK);

    // PRINTERS
    sioPrinter::printer_type get_printer_type(uint8_t num);
    int get_printer_port(uint8_t num);
    void store_printer_type(uint8_t num, sioPrinter::printer_type ptype);
    void store_printer_port(uint8_t num, int port);

    // MODEM
    void store_modem_sniffer_enabled(bool enabled);
    bool get_modem_sniffer_enabled() { return _modem.sniffer_enabled; }

    // CASSETTE
    bool get_cassette_buttons();
    bool get_cassette_pulldown();
    void store_cassette_buttons(bool button);
    void store_cassette_pulldown(bool pulldown);

    // NETSIO (Connection to Atari emulator)
    bool get_netsio_enabled() { return _netsio.netsio_enabled; }
    std::string get_netsio_host() { return _netsio.host; };
    int get_netsio_port() { return _netsio.port; };
    void store_netsio_enabled(bool enabled);
    void store_netsio_host(const char *host);
    void store_netsio_port(int port);

    void load();
    void save();

    fnConfig();

private:
    bool _dirty = false;

    int _read_line(std::stringstream &ss, std::string &line, char abort_if_starts_with = '\0');

    void _read_section_general(std::stringstream &ss);
    void _read_section_serial(std::stringstream &ss);
    void _read_section_wifi(std::stringstream &ss);
    void _read_section_bt(std::stringstream &ss);
    void _read_section_network(std::stringstream &ss);
    void _read_section_host(std::stringstream &ss, int index);
    void _read_section_mount(std::stringstream &ss, int index);
    void _read_section_printer(std::stringstream &ss, int index);
    void _read_section_tape(std::stringstream &ss, int index);    
    void _read_section_modem(std::stringstream &ss);
    void _read_section_cassette(std::stringstream &ss);
    void _read_section_phonebook(std::stringstream &ss, int index);
    void _read_section_netsio(std::stringstream &ss);

    enum section_match
    {
        SECTION_GENERAL,
        SECTION_WIFI,
        SECTION_BT,
        SECTION_HOST,
        SECTION_MOUNT,
        SECTION_PRINTER,
        SECTION_NETWORK,
        SECTION_TAPE,
        SECTION_MODEM,
        SECTION_CASSETTE,
        SECTION_PHONEBOOK,
        SECTION_SERIAL,
        SECTION_NETSIO,
        SECTION_UNKNOWN
    };
    section_match _find_section_in_line(std::string &line, int &index);
    bool _split_name_value(std::string &line, std::string &name, std::string &value);

    const char * _host_type_names[HOSTTYPE_INVALID] = {
        "SD",
        "TNFS"
    };
    const char * _mount_mode_names[MOUNTMODE_INVALID] = {
        "r",
        "w"
    };

    const char * _serial_command_pin_names[SERIAL_COMMAND_INVALID] = {
        "none",
        "DSR",
        "CTS",
        "RI"
    };

    const char * _serial_proceed_pin_names[SERIAL_PROCEED_INVALID] = {
        "none",
        "DTR",
        "RTS"
    };

    struct host_info
    {
        host_type_t type = HOSTTYPE_INVALID;
        std::string name;
    };

    struct mount_info
    {
        int host_slot = HOST_SLOT_INVALID;
        mount_mode_t mode = MOUNTMODE_INVALID;
        std::string path;
    };

    struct printer_info
    {
        sioPrinter::printer_type type = sioPrinter::printer_type::PRINTER_INVALID;
        int port = 0;
    };

/*
     802.11 standard speficies a length 0 to 32 octets for SSID.
     No character encoding is specified, and all octet values are valid including
     zero. Although most SSIDs are treatred as ASCII strings, they are not subject
     to those limitations.
     We set asside 33 characters to allow for a zero terminator in a 32-char SSID
     and treat it as string instead of an array of arbitrary byte values.
     
     Similarly, the PSK (passphrase/password) is 64 octets.
     User-facing systems will typically take an 8 to 63 ASCII string and hash
     that into a 64 octet value. Although we're storing that ASCII string,
     we'll allow for 65 characters to allow for a zero-terminated 64 char
     string.
*/
    struct wifi_info
    {
        std::string ssid;
        std::string passphrase;
    };

    struct bt_info
    {
        bool bt_status = false;
        int bt_baud = 19200;
        std::string bt_devname = "FujiNetSIO2BT";
    };

    struct network_info
    {
        char sntpserver [40];
        char midimaze_host [64];
    };

    struct general_info
    {
        std::string devicename = "fujinet";
        int hsio_index = SIO_HISPEED_INDEX;
        std::string timezone;
        bool rotation_sounds = true;
        bool config_enabled = true;
        int boot_mode = 0;
        std::string interface_url = WEB_SERVER_LISTEN_URL; // default URL to serve web interface
        std::string config_file_path = CONFIG_FILENAME; // default path to load/save config file (program CWD)
        std::string SD_dir_path = SD_CARD_DIR; // default path to load/save config file
    };

    struct serial_info
    {
        std::string port;
        serial_command_pin command = SERIAL_COMMAND_DSR;
        serial_proceed_pin proceed = SERIAL_PROCEED_DTR;
    };

    struct netsio_info
    {
        bool netsio_enabled = false;
        std::string host = "";
        int port = CONFIG_DEFAULT_NETSIO_PORT;
    };

    struct modem_info
    {
        bool sniffer_enabled = false;
    };

    struct cassette_info
    {
        bool pulldown = false;
        bool button = false;
    };

    struct phbook_info
    {
        std::string phnumber;
        std::string hostname;
        std::string port;
    };

    host_info _host_slots[MAX_HOST_SLOTS];
    mount_info _mount_slots[MAX_MOUNT_SLOTS];
    printer_info _printer_slots[MAX_PRINTER_SLOTS];
    mount_info _tape_slots[MAX_TAPE_SLOTS];

    wifi_info _wifi;
    bt_info _bt;
    network_info _network;
    general_info _general;
    modem_info _modem;
    cassette_info _cassette;
    serial_info _serial;
    netsio_info _netsio;

    phbook_info _phonebook_slots[MAX_PB_SLOTS];
};

extern fnConfig Config;

#endif //_FN_CONFIG_H
