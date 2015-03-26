
#include <string>


class Station_Info 
{
    public:
        std::string setNetwork_Code ();
        std::string setStn_code ();
        std::string setBand_Type ();
        std::string setInst_Type ();
        std::string setOrient ();
        

    public:
        std::string Network_Code;
        std::string Stn_code;
        std::string Band_Type;
        std::string Inst_Type;
        std::string Orient;
};
