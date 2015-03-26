#include <string>

class earthquake
{
    
    public:
        std::string setEvent_ID ();
        std::string setDate ();
        std::string setTime ();
        std::string setTime_Zone ();
        std::string setEqkName ();
        std::string setLon ();
        std::string setLat ();
        std::string setdepth ();
        std::string setMag_type_string ();
        float setMag_size ();
        
    private:
        std::string Event_ID;
        std::string Date;
        std::string Time;
        std::string Time_Zone;
        std::string EqkName;
        std::string Lon;
        std::string Lat;
        std::string depth;
        std::string Mag_type_string;
        float Mag_size;
};

