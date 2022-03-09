struct Client{//une branche est délimité par un point plus un vecteur
    int demand;
    float x,y;
    //Client(int X,int Y,int DEMANDE);
};
struct Instance{
    int nbclient;
    int maxdemand;
    int xmap;
    int ymap;
    Client * listclient;
    Instance(int numberofclient,int Xmap,int Ymap,int Maxdemand);
    ~Instance();
    void displayinstance();
};
