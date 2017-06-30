#include <iostream>
#include <math.h>
#define PI 3.14
using namespace std;

namespace thermo{
  //public:
    double a(double, double);//declare the function before!!
    double b(double, double);
    double alpha(double);
    double vp_Antonie(double a, double b, double c, double T){
      return exp(a - b/(T+c));
    }
    
    double SRK_P(double T, double P, double omega, double V){
      //return 0;
      a(T,P);
    }
    
    double a(double T, double P){
      return 0.42747*pow(8.314*T,2)/P;
    }
    
    double b(double T, double P){
      return 0.08664*8.314*T/P;
    }
    
    double alpha(double omega, double Tr){
      double m = 0.48508+1.55171*omega-0.1561*pow(omega,2);
      return pow(1+m*(1-sqrt(Tr)),2);
    }
    
    double nr(){
      double xn = 1.5, xn1;
      double tolerance = 0.001;
      for(int i =1; i < 10; i++){
        xn1 =xn - (pow(xn,3)+(4*pow(xn,2))-10)/(3*pow(xn,2)+ 8*xn);
        cout << xn << endl;
        if(abs(xn1 - xn) < tolerance)
          break;
        
        xn = xn1;
      }
      return xn;
    }
    
    double nr_srk(double R, double T, double P,double alpha, double a, double b){
      double vn, vn1;
      vn = 0.01*R*T/P;//Initial guess from ideal gas law
      double tolerance = 0.001;
      
      double f_v, df_v;
      
      
      for(int i =1; i < 50; i++){
        
        f_v = P - (R*T/(vn - b)) + (alpha*a/(vn*(vn+b)));
        df_v = (R*T/pow(vn - b,2)) + (alpha*a*(2*vn + b)/pow(vn*(vn+b),2));
        
        vn1 =vn - f_v/df_v;
        
        cout << vn << endl;
        if(abs(vn1 - vn) < tolerance)
          break;
        
        vn = vn1;
      }
      return vn;
    }
    
    
    
    
}

namespace compLibrary{
  struct components{
    int compID;
    string name;// use std::string along with the string header
    double molWt, Tc, Pc, vc, zc, omega;
  };
  
  static components s1[468] ={
  {1,"1,1,1-TRIFLOUROETHANE",84.041,346.2,37.1,221,0.289,0.257},
  {2,"1,1,2,2-TETRACHLORO-1,2-DIFLUOROETHANE",203.831,551,0,0,0,0},
  {3,"1,1,2-TRICHLOROETHANE",133.405,602,41,294,0.24,0.22},
  {4,"1,1,2-TRIMETHYLCLOPENTANE",112.216,579.5,29,0,0,0.252},
  {5,"1,1,3-TRIMETHYLCLOPENTANE",112.216,569.5,27.9,0,0,0.211},
  {6,"1,1-DICHLORO-1,2,2,2-TETRAFLUOROETHANE",170.922,418.6,32.6,294,0.279,0},
  {7,"1,1-DICHLOROETHANE",98.96,523,50,240,0.28,0.248},
  {8,"1,1-DIFLOUROETHANE",66.051,386.6,44.4,181,0.253,0.266},
  {9,"1,1-DIFLUOROETHYLENE",64.035,302.8,44,154,0.273,0},
  {10,"1,1-DIMETHYLCYCLOHEXANE",112.216,591,29.3,416,0.25,0.238},
  {11,"1,1-DIMETHYLCYCLOPENTANE",98.189,547,34,360,0.27,0.273},
  {12,"1,2,2-TRICHLORO-1,1,2TRIFLUOROETHANE",187.38,487.2,33.7,304,0.256,0.252},
  {13,"1,2,3,4-TETRAHYDRONAPHTHALENE",132.206,719,34.7,0,0,0.303},
  {14,"1,2,3-TRICHLOROPROPANE",147.432,651,39,348,0.25,0.31},
  {15,"1,2,3-TRIMETHYLBENZENE",120.195,664.5,34.1,430,0.27,0.39},
  {16,"1,2,4,5-TETRAMETHYLBEENZENE",134.222,675,29,480,0.25,0.426},
  {17,"1,2,4-TRIMETHYLBENZENE",120.195,649.1,31.9,430,0.258,0.39},
  {18,"1,2-BUTADIENE",54.092,443.7,44.4,219,0.267,0.255},
  {19,"1,2-DICHLORO-1,1,2,2-TETRAFLUOROETHANE",170.922,418.9,32.2,293,0.275,0.255},
  {20,"1,2-DICHLOROETHANE",98.96,561,53,220,0.25,0.286},
  {21,"1,2-DICHLOROPROPANE",112.987,577,44,226,0.21,0.24},
  {22,"1,2-DIMETHOXYETHANE",90.123,536,38.2,271,0.235,0.371},
  {23,"1,2-PENTADIENE",68.119,503,40.2,276,0.269,0.173},
  {24,"1,2-PROPANEDIOL",76.096,625,60,237,0.28,0},
  {25,"1,3,5-TRIMETHYLBENZENE",120.195,637.3,30.9,433,0.26,0.398},
  {26,"1,3-BUTADIENE",54.092,425,42.7,221,0.27,0.195},
  {27,"1,3-PROPANEDIOL",76.096,658,59,241,0.26,0},
  {28,"1,4 DIOXANE",88.107,587,51.4,238,0.254,0.288},
  {29,"1,4-DIETHYLBENZENE",134.222,657.9,27.7,480,0.25,0.403},
  {30,"1,4-PENTADIENE",68.119,478,37.4,276,0.263,0.104},
  {31,"1,5 HEXADIENE",82.146,507,34,328,0.26,0.16},
  {32,"1-BUTENE",56.108,419.6,39.7,240,0.277,0.187},
  {33,"1-BUTYNE",54.092,463.7,46.5,220,0.27,0.05},
  {34,"1-CHLORO-1,1-DIFLUOROETHANE",100.496,410.2,40.7,231,0.279,0},
  {35,"1-CHLOROBUTANE",92.569,542,36.4,312,0.255,0.218},
  {36,"1-DECANOL",158.285,700,22,600,0.23,0},
  {37,"1-DECENE",140.27,615,21.8,650,0.28,0.491},
  {38,"1-DODECENE",168.324,657,18.3,0,0,0.558},
  {39,"1-EICOSANOL",298.555,770,12,0,0,0},
  {40,"1-HEPTANOL",116.204,633,30,435,0.25,0.56},
  {41,"1-HEPTENE",98.189,537.2,28,440,0.28,0.358},
  {42,"1-HEXADECENE",224.432,717,13.2,0,0,0.721},
  {43,"1-HEXANOL",102.177,610,40,381,0.3,0.56},
  {44,"1-HEXENE",84.162,504,31.3,350,0.26,0.285},
  {45,"1-METHYL-1-ETHYLCYCLOPENTANE",112.216,592,29.5,0,0,0.25},
  {46,"1-METHYL-2-ETHYLBENZENE",120.195,651,30,460,0.26,0.294},
  {47,"1-METHYL-2-ISOPROPYLBENZENE",134.222,670,28.6,0,0,0.277},
  {48,"1-METHYL-2-ISOPROPYLBENZENE",134.222,666,29,0,0,0.279},
  {49,"1-METHYL-3-ETHYLBENZENE",120.195,637,28,490,0.26,0.36},
  {50,"1-METHYL-4-ETHYLBENZENE",120.195,640,29,470,0.26,0.322},
  {51,"1-METHYL-4-ISOPROPYLBENZENE",134.222,653,27.9,0,0,0.371},
  {52,"1-METHYLNAPHTHALENE",142.201,772,35.2,445,0.25,0.334},
  {53,"1-NONENE",126.243,592,23.1,580,0.28,0.43},
  {54,"1-OCTADECANOL",270.501,747,14,0,0,0},
  {55,"1-OCTADECENE",252.486,739,11.2,0,0,0.807},
  {56,"1-OCTANOL",130.231,58,34,490,0.31,0.53},
  {57,"1-OCTENE",112.216,566.6,25.9,464,0.26,0.386},
  {58,"1-PENTADECENE",210.405,704,14.4,0,0,0.682},
  {59,"1-PENTANOL",88.15,586,38,326,0.26,0.58},
  {60,"1-PENTENE",70.135,464.7,40,300,0.31,0.245},
  {61,"1-PENTYNE",68.119,493.4,40,278,0.275,0.164},
  {62,"1-PROPANOL",60.096,536.7,51,218.5,0.253,0.624},
  {63,"1-TERADECENE",196.378,689,15.4,0,0,0.644},
  {64,"1-TRANS-3-PENTADIENE",68.119,496,39.4,275,0.266,0.175},
  {65,"1-TRIDECENE",182.351,674,16.8,0,0,0.598},
  {66,"1-UNDECENE",154.297,637,19.7,0,0,0.518},
  {67,"2,2 DIMETHYL BUTANE",86.178,488.7,30.4,359,0.272,0.231},
  {68,"2,2,3 TRIMETHYLPETANE",114.232,563.4,26.9,436,0.254,0.297},
  {69,"2,2,3,3-TETRAMETHYLHEPTANE",142.286,623.1,24.8,0,0,0.36},
  {70,"2,2,3,3-TETRAMETHYLPENTANE",128.259,607.6,27,0,0,0.279},
  {71,"2,2,3,4-TETRAMETHYLPENTANE",128.259,592.7,25.7,0,0,0.311},
  {72,"2,2,3-TRIMETHYLBUTANE",100.205,531.1,29.2,398,0.267,0.251},
  {73,"2,2,3-TRIMETHYLHEXANE",128.259,588,24.6,0,0,0.332},
  {74,"2,2,4 TRIMETHYLPENTANE",114.232,543.9,25.3,468,0.266,0.303},
  {75,"2,2,4,4-TETRAMETHYLPENTANE",128.259,574.7,24.5,0,0,0.315},
  {76,"2,2,4-TRIMETHYLHEXANE",128.259,573.7,23.4,0,0,0.321},
  {77,"2,2,5,5-TETRAMETHYLHEPTANE",142.286,581.5,21.6,0,0,0.374},
  {78,"2,2,5-TRIMETHYLHEXANE",128.259,568,23,519,0.26,0.357},
  {79,"2,2-DIMETHYL PROPANE",72.151,433.8,31.6,303,0.269,0.197},
  {80,"2,2-DIMETHYL-1-PROPANOL",88.15,549,39,319,0.28,0},
  {81,"2,2-DIMETHYLHEXANE",114.232,549.8,25,478,0.264,0.338},
  {82,"2,2-DIMETHYLPENTANE",100.205,520.4,27.4,416,0.267,0.289},
  {83,"2,3 DIMETHYL BUTANE",86.178,499.9,30.9,358,0.27,0.247},
  {84,"2,3,3 TRIMETHYLPENTANE",114.232,573.5,27.8,455,0.269,0.29},
  {85,"2,3,3,4-TETRAMETHYLPENTANE",128.259,607.6,26.8,0,0,0.299},
  {86,"2,3,3-TRIMETHYL-1-BUTENE",98.189,533,28.6,400,0.26,0.192},
  {87,"2,3,4 TRIMETHYLPENTANE",114.232,56.3,26.9,461,0.267,0.317},
  {88,"2,3-DIMETHYL-1-BUTENE",84.162,501,32,343,0.27,0.221},
  {89,"2,3-DIMETHYL-2-BUTENE",84.162,524,33.2,351,0.27,0.239},
  {90,"2,3-DIMETHYLHEXANE",114.232,563.4,25.9,468,0.262,0.346},
  {91,"2,3-DIMETHYLPENTANE",100.205,537.3,28.7,393,0.256,0.299},
  {92,"2,3-DIMETHYLPYRIDINE",107.156,655.4,0,0,0,0},
  {93,"2,3-XYLENOL",122.167,722.8,0,0,0,0},
  {94,"2,4-DIMETHYLHEXANE",114.232,553.5,25.2,472,0.262,0.343},
  {95,"2,4-DIMETHYLPENTANE",100.205,519.7,27,418,0.265,0.306},
  {96,"2,4-XYLENOL",122.167,707.6,0,0,0,0},
  {97,"2,5-DIMETHYLHEXANE",114.232,550,24.5,42,0.262,0.352},
  {98,"2,5-DIMETHYLPYRIDINE",107.156,644.2,0,0,0,0},
  {99,"2,5-XYLENOL",122.167,723,0,0,0,0},
  {100,"2,6-XYLENOL",122.167,701,0,0,0,0},
  {101,"2-BUTANOL",74.123,536,41.4,268,0.252,0.576},
  {102,"2-BUTYNE",54.092,488.6,50.2,221,0.277,0.124},
  {103,"2-CHLOROBUTANE",92.569,520.6,39,305,0.28,0.3},
  {104,"2-ETHYLHEXANOL",130.231,613,27.2,494,0.267,0},
  {105,"2-METHYL BUTANE",72.151,460.4,33.4,306,0.271,0.227},
  {106,"2-METHYL PENTANE",86.178,497.5,29.7,367,0.267,0.279},
  {107,"2-METHYL-1,3-BUTADIENE",68.119,484,38,276,0.264,0.164},
  {108,"2-METHYL-1-BUTANOL",88.15,571,38,322,0.26,0.7},
  {109,"2-METHYL-1-BUTENE",70.135,465,34,294,0.262,0.232},
  {110,"2-METHYL-2-BUTENE",70.135,470,34,318,0.28,0.285},
  {111,"2-METHYL-2-PENTENE",84.162,518,32.4,351,0.27,0.229},
  {112,"2-METHYL-3-ETHYLPENTANE",114.232,567,26.7,443,0.254,0.33},
  {113,"2-METHYLHEPTANE",114.232,559.6,24.5,488,0.26,0.378},
  {114,"2-METHYLHEXANE",100.205,530.3,27,421,0.261,0.33},
  {115,"2-METHYLNAPHTHALENE",142.201,761,34.6,462,0.26,0.382},
  {116,"2-OCTANOL",130.231,637,27,494,0.26,0.52},
  {117,"3,3,5-TRIMETHYLHEPTANE",142.286,609.6,22.9,0,0,0.388},
  {118,"3,3-DIETHYLPENTANE",128.259,610,26.4,0,0,0.338},
  {119,"3,3-DIMETHYL-1-BUTENE",84.162,490,32.1,340,0.27,0.121},
  {120,"3,3-DIMETHYLHEXANE",114.232,562,26.2,443,0.252,0.321},
  {121,"3,3-DIMETHYLPENTANE",100.205,536.3,29.1,414,0.274,0.27},
  {122,"3,4 DIMETHYLHEXANE",114.232,568.8,26.6,466,0.265,0.338},
  {123,"3,4-DIMETHYLPYRIDINE",107.156,683.8,0,0,0,0},
  {124,"3,4-XYLENOL",122.167,729.8,0,0,0,0},
  {125,"3,5-DIMETHYLPYRIDINE",107.156,667.2,0,0,0,0},
  {126,"3,5-XYLENOL",122.167,715.6,0,0,0,0},
  {127,"3-ETHYLHEXANE",114.232,565.4,25.7,455,0.252,0.361},
  {128,"3-ETHYLPENTANE",100.205,540.6,28.5,416,0.267,0.31},
  {129,"3-METHYL PENTANE",86.178,504.4,30.8,367,0.273,0.275},
  {130,"3-METHYL-1,2-BUTADIENE",68.119,496,40.6,267,0.266,0.16},
  {131,"3-METHYL-1-BUTANOL",88.15,579.5,38,329,0.26,0.58},
  {132,"3-METHYL-1-BUTENE",70.135,450,34.7,300,0.282,0.209},
  {133,"3-METHYL-2-BUTANOL",88.15,545,39,319,0.28,0.5},
  {134,"3-METHYL-3-ETHYLPENTANE",114.232,576.6,27.7,455,0.267,0.304},
  {135,"3-METHYL-CIS-2-PENTENE",84.162,518,32.4,351,0.27,0.269},
  {136,"3-METHYLHEPTANE",114.232,563.6,25.1,464,0.252,0.369},
  {137,"3-METHYLHEXANE",100.205,535.2,27.8,404,0.256,0.324},
  {138,"3-METHYL-TRANS-2-PENTENE",84.162,521,32.5,350,0.27,0.207},
  {139,"4- METHYL PYRIDINE",93.129,646,44,311,0.26,0.27},
  {140,"4-METHYL-CIS-2-PENTENE",84.162,490,30,360,0.27,0.29},
  {141,"4-METHYLHEPTANE",114.232,561.7,25.1,476,0.259,0.369},
  {142,"4-METHYL-TRANS-2-PENTENE",84.162,493,30,360,0.27,0.29},
  {143,"ACETALDEHYDE",44.054,461,55,154,0.22,0.303},
  {144,"ACETIC ACID",60.052,594.4,57.1,171,0.2,0.454},
  {145,"ACETIC ANHYDRIDE",102.089,569,46.2,290,0.287,0},
  {146,"ACETONE",58.08,508.1,46.4,209,0.232,0.309},
  {147,"ACETONITRILE",41.053,548,47.7,173,0.184,0.321},
  {148,"ACETYL CHLORIDE",78.498,508,58,204,0.28,0.344},
  {149,"ACETYLENE",26.038,308.3,60.6,113,0.271,0.184},
  {150,"ACROLEIN",56.064,506,51,0,0,0.33},
  {151,"ACRYLIC ACID",72.064,615,56,210,0.23,0.56},
  {152,"ACRYLONITRILE",53.064,536,45,210,0.21,0.35},
  {153,"ALLYL ALCOHOL",58.08,545,56.4,203,0.256,0.63},
  {154,"ALLYL CHLORIDE",76.526,514,47,234,0.26,0.13},
  {155,"ALLYL CYANIDE",67.091,585,39,265,0.22,0.39},
  {156,"ALPHA-METHYL STYRENE",118.179,654,33.6,397,0.25,0},
  {157,"AMMONIA",17.031,405.6,111.3,72.5,0.242,0.25},
  {158,"ANILINE",93.129,699,52.4,270,0.247,0.382},
  {159,"ANTHRACENE",178.234,883,0,0,0,0},
  {160,"ARGON",39.948,150.8,48.1,74.9,0.291,-0.004},
  {161,"BENZALDEHYDE",106.124,695,46,0,0,0.32},
  {162,"BENZENE",78.114,562.1,48.3,259,0.271,0.212},
  {163,"BENZOIC ACID",122.124,752,45,341,0.25,0.62},
  {164,"BENZONITRILE",103.124,699.4,41.6,0,0,0.36},
  {165,"BENZYL ALCOHOL",108.14,677,46,334,0.28,0.71},
  {166,"BORON TRICHLORIDE",117.169,452,38.2,0,0,0.15},
  {167,"BORON TRIFLUORIDE",67.805,260.8,49.2,0,0,0.42},
  {168,"BROMINE",159.808,584,102,127,0.27,0.132},
  {169,"BROMOBENZENE",157.01,670,44.6,324,0.263,0.249},
  {170,"BUTYL BENZOATE",178.232,723,26,561,0.25,0.58},
  {171,"BUTYL ETHER",130.231,580,25,500,0.26,0.5},
  {172,"BUTYRONITRILE",69.107,582.2,37.4,285,0.223,0.371},
  {173,"C,C,T-1,2,4-TRIMETHYLCYCLOPENTANE",112.216,579,284,0,0,0.277},
  {174,"C,T,C-1,2,4-TRIMETHYLCYCLOPENTANE",112.216,571,27.7,0,0,0.246},
  {175,"CAPRYLONITRILE",153.269,622,32.1,0,0,0},
  {176,"CARBON DIOXIDE",44.01,304.2,72.8,94,0.274,0.225},
  {177,"CARBON DISULFIDE",76.131,552,78,170,0.293,0.115},
  {178,"CARBON MONOXIDE",28.018,32.9,34.5,93.1,0.295,0.049},
  {179,"CARBON TETRACHLORIDE",153.823,556.4,45,276,0.272,0.194},
  {180,"CARBON TETRAFLUORIDE",88.005,227.6,36.9,140,0.277,0.191},
  {181,"CARBONYL SULFIDE",60.07,375,58,140,0.26,0.099},
  {182,"CHLORINE",70.906,417,76,124,0.275,0.073},
  {183,"CHLOROBENZENE ",112.559,632.4,44.6,308,0.265,0.249},
  {184,"CHLORODIFLUOROMETHANE",86.469,369.2,49.1,165,0.267,0.215},
  {185,"CHLOROFORM",119.378,536.4,54,239,0.293,0.216},
  {186,"CHLOROPENTAFLUOROETHANE",154.467,353.2,31.2,252,0.271,0.253},
  {187,"CHLOROTRIFLUOROMETHANE",104.459,302,38.7,180,0.282,0.18},
  {188,"CIS-1,2-DIMETHYLCYCLOHEXANE",112.216,606,29.3,0,0,0.236},
  {189,"CIS-1,2-DIMETHYLCYCLOPENTANE",98.189,564.8,34,368,0.27,0.269},
  {190,"CIS-1,3-DIMETHYLCYCLOHEXANE",112.216,591,29.3,0,0,0.224},
  {191,"CIS-1,4-DIMETHYLCYCLOHEXANE",112.216,598,29.3,0,0,0.234},
  {192,"CIS-2-BUTENE",56.108,435.6,41.5,234,0.272,0.202},
  {193,"CIS-2-HEXENE",84.162,518,32.4,351,0.27,0.256},
  {194,"CIS-2-PENTENE",70.135,476,36,300,0.28,0.24},
  {195,"CIS-3-HEXENE",84.162,517,32.4,350,0.27,0.225},
  {196,"CIS-DECALIN",138.254,702.2,31,0,0,0.23},
  {197,"CYANOGEN",52.035,400,59,0,0,0.24},
  {198,"CYCLOBUTANE",56.108,459.9,49.2,210,0.274,0.209},
  {199,"CYCLOHEPTANE",98.189,589,36.7,390,0.3,0.336},
  {200,"CYCLOHEXANE",84.162,553.4,40.2,308,0.273,0.213},
  {201,"CYCLOHEXANOL",100.161,625,37,327,0.24,0.55},
  {202,"CYCLOHEXANONE",95.145,629,38,312,0.23,0.443},
  {203,"CYCLOHEXENE",82.146,560.4,42.9,292,0.27,0.21},
  {204,"CYCLOPENTANE",70.135,511.6,44.5,260,0.276,0.192},
  {205,"CYCLOPENTANONE",84.118,626,53,268,0.28,0.35},
  {206,"CYCLOPENTENE",68.119,506,0,0,0,0},
  {207,"CYCLOPROPANE",42.081,397.8,54.2,170,0.282,0.264},
  {208,"DEUTERIUM",4.032,38.4,16.4,60.3,0.314,-0.13},
  {209,"DEUTERIUM OXIDE",20.031,644,213.8,55.6,0.225,0},
  {210,"DIBROMOMETHANE",173.835,583,71,0,0,0},
  {211,"DIBUTYLAMINE",129.247,596,25,517,0.26,0.59},
  {212,"DIBUTYL-O-PHTHALATE",278.35,0,0,0,0,0},
  {213,"DICHLORODIFLUOROMETHANE",120.914,385,40.7,217,0.28,0.176},
  {214,"DICHLOROMETHANE",84.933,510,60,193,0.277,0.193},
  {215,"DICHLOROMONOFLUOROMETHANE",102.923,451.6,51,197,0.272,0.202},
  {216,"DIETHYL AMINE",45.085,437.6,52.4,187,0.272,0.288},
  {217,"DIETHYL AMINE",73.139,496.6,36.6,301,0.27,0.299},
  {218,"DIETHYL DISULFIDE",122.244,642,0,0,0,0},
  {219,"DIETHYL KETONE",86.134,561,36.9,336,0.269,0.347},
  {220,"DIETHYL SULFIDE",90.18,557,39.1,318,0.272,0.3},
  {221,"DIETHYLENE GLYCOL",106.122,681,6,316,0.26,0},
  {222,"DIHEXYL ETHER",186.339,657,18,720,0.24,0.7},
  {223,"DIISOPROPYL ETHER",102.177,500,28.4,386,0.267,0.34},
  {224,"DIMETHYL ETHER",46.069,400,53,178,0.287,0.192},
  {225,"DIMETHYL OXALATE",118.09,628,39.3,0,0,0},
  {226,"DIMETHYL SULFIDE",62.13,503,54.6,201,0.266,0.19},
  {227,"DIPHENYL",154.212,789,38,502,0.295,0.364},
  {228,"DIPHENYL ETHER",170.211,766,31,0,0,0.44},
  {229,"DIPHENYLMETHANE",168.239,29.4,0,0,0,0.471},
  {230,"DIPROPYLAMINE",101.193,550,31,407,0.28,0.455},
  {231,"DODECANOL",186.339,679,19,718,0.24,0},
  {232,"ETHANE",30.07,305.4,48.2,148,0.285,0.098},
  {233,"ETHANOL",46.069,516.2,63,167,0.248,0.635},
  {234,"ETHYL ACETATE",88.107,523.2,37.8,286,0.252,0.363},
  {235,"ETHYL ACRYLATE",100.118,552,37,320,0.261,0.4},
  {236,"ETHYL AMINE",45.085,456,55.5,178,0.264,0.284},
  {237,"ETHYL BENZOATE",150.178,697,32,451,0.25,0.48},
  {238,"ETHYL BROMIDE",108.966,503.8,61.5,215,0.32,0.254},
  {239,"ETHYL BUTYL ETHER",102.177,531,30,390,0.27,0.4},
  {240,"ETHYL BUTYRATE",116.16,566,31,395,0.26,0.47},
  {241,"ETHYL CHLORIDE",64.515,460.4,52,199,0.274,0.19},
  {242,"ETHYL ETHER",74.123,466.7,35.9,280,0.262,0.281},
  {243,"ETHYL FLUORIDE",48.06,375.3,49.6,169,0.272,0.238},
  {244,"ETHYL FORMATE",74.08,508.4,46.8,229,0.257,0.283},
  {245,"ETHYL ISOBUTYRATE",116.16,553,30,410,0.27,0.427},
  {246,"ETHYL MERCAPTAN",62.134,499,54.2,207,0.274,0.19},
  {247,"ETHYL PROPIONATE",102.134,546,33.2,345,0.256,0.395},
  {248,"ETHYL PROPYL ETHER",88.15,500.6,32.1,0,0,0.331},
  {249,"ETHYLBENZENE",106.168,617.1,35.6,374,0.263,0.301},
  {250,"ETHYLCYCLOHEXANE",112.216,609,29.9,450,0.27,0.243},
  {251,"ETHYLCYCLOPENTANE",98.189,569.5,33.5,375,0.269,0.283},
  {252,"ETHYLENE",28.054,282.4,49.7,129,0.276,0.085},
  {253,"ETHYLENE GLYCOL",62.069,645,76,186,0.27,0},
  {254,"ETHYLENE IMINE",43.069,0,0,0,0,0},
  {255,"ETHYLENE OXIDE",44.054,469,71,140,0.258,0.2},
  {256,"ETHYLENEDIAMINE",60.099,593,62,206,0.26,0.51},
  {257,"FLUORINE",37.997,144.3,51.5,66.2,0.288,0.048},
  {258,"FLUOROBENZENE",96.104,560.1,44.9,271,0.265,0.245},
  {259,"FORMALDEHYDE",30.026,408,65,0,0,0.253},
  {260,"FORMIC ACID",46.025,580,0,0,0,0},
  {261,"FURAN",68.075,490.2,54.3,218,0.294,0.204},
  {262,"GLYCEROL",92.095,726,66,255,0.28,0},
  {263,"HELIUM-4",4.003,5.2,2.2,57.3,0.301,-0.387},
  {264,"HEPTADECANOL",256.474,736,14,0,0,0},
  {265,"HYDRAZINE",32.045,653,145,96.1,0.26,0.328},
  {266,"HYDROGEN",2.016,33.2,12.8,65,0.305,-0.22},
  {267,"HYDROGEN BROMIDE",80.912,363.2,84.4,100,0.283,0.063},
  {268,"HYDROGEN CHLORIDE",36.461,324.6,82,81,0.249,0.12},
  {269,"HYDROGEN CYANIDE",27.026,456.8,53.2,139,0.197,0.407},
  {270,"HYDROGEN FLUORIDE",20.006,461,64,69,0.12,0.372},
  {271,"HYDROGEN IODIDE",127.912,424,82,131,0.309,0.05},
  {272,"HYDROGEN SULFIDE",34.08,373.2,88.2,98.5,0.284,0.1},
  {273,"IODINE",253.808,819,115,155,0.265,0.299},
  {274,"IODOBENZENE",204.011,721,44.6,351,0.265,0.246},
  {275,"ISOBUTANE",58.124,408.1,36,263,0.283,0.176},
  {276,"ISOBUTANOL",74.123,547.7,42.4,273,0.257,0.588},
  {277,"ISOBUTYL ACETATE",116.16,561,30,414,0.27,0.479},
  {278,"ISOBUTYL AMINE",73.139,516,42,284,0.28,0},
  {279,"ISOBUTYL FORMATE",102.134,551,38.3,350,0.296,0.39},
  {280,"ISOBUTYLBENZENE",134.222,650,31,480,0.28,0.378},
  {281,"ISOBUTYLCYCLOHEXANE",140.27,659,30.8,0,0,0.319},
  {282,"ISOBUTYLENE",56.108,417.9,39.5,239,0.275,0.19},
  {283,"ISOBUTYRALDEHYDE",72.107,513,41,274,0.27,0.35},
  {284,"ISOBUTYRIC ACID",88.107,609,40,292,0.23,0.61},
  {285,"ISOPROPYL ALCOHOL",60.096,508.3,47,220,0.248,0},
  {286,"ISOPROPYL AMINE",59.112,476,50,229,0.29,0.297},
  {287,"ISOPROPYL CHLORIDE",78.542,485,46.6,230,0.269,0.232},
  {288,"ISOPROPYLBENZENE",120.195,631,31.7,428,0.26,0.335},
  {289,"ISOPROPYLCYCLOHEXANE",126.243,640,28,0,0,0.237},
  {290,"ISOPROPYLCYCLOPENTANE",112.216,601,29,0,0,0.24},
  {291,"KETENE",42.038,380,64,145,0.3,0.207},
  {292,"KRYPTON",83.8,209.4,54.3,91.2,0.288,-0.002},
  {293,"MALEIC ANHYDRIDE",98.058,0,0,0,0,0},
  {294,"M-CRESOL",108.14,705.8,45,310,0.241,0.464},
  {295,"M-DICHLOROBENZENE",147.004,684,38,359,0.24,0.26},
  {296,"METHANE",16.043,190.6,45.4,99,0.288,0.008},
  {297,"METHANOL",32.042,512.6,79.9,118,0.224,0.559},
  {298,"METHYCYCLOPENTANE",84.162,532.7,37.4,319,0.273,0.239},
  {299,"METHYL ACETATE",74.08,506.8,46.3,228,0.254,0.324},
  {300,"METHYL ACETYLENE",40.065,402.4,55.5,164,0.276,0.218},
  {301,"METHYL ACRYLATE",86.091,536,42,265,0.25,0.35},
  {302,"METHYL AMINE",31.058,430,73.6,140,0.292,0.275},
  {303,"METHYL BENZOATE",136.151,692,36,396,0.25,0.43},
  {304,"METHYL BROMIDE",94.939,464,85,0,0,0.273},
  {305,"METHYL BUTYRATE",102.134,554.4,34.3,340,0.257,0.382},
  {306,"METHYL CHLORIDE",50.488,416.3,65.9,139,0.268,0.156},
  {307,"METHYL ETHYL ETHER",60.096,437.8,43.4,221,0.267,0.236},
  {308,"METHYL ETHYL KETONE",72.107,535.6,41,267,0.249,0.329},
  {309,"METHYL ETHYL SULFIDE",76.157,533,42,0,0,0},
  {310,"METHYL FLUORIDE",34.033,317.8,58,124,0.275,0.19},
  {311,"METHYL FORMATE",60.052,487.2,59.2,172,0.255,0.252},
  {312,"METHYL HYDRAZINE",46.072,567,79.3,271,0.462,0},
  {313,"METHYL IODIDE",141.939,528,65,190,0.285,0.172},
  {314,"METHYL ISOBUTYL KETONE",100.161,571,32.3,371,0.26,0.4},
  {315,"METHYL ISOBUTYRATE",102.134,540.8,33.9,339,0.259,0.367},
  {316,"METHYL ISOCYANATE",57.052,491,55,0,0,0.278},
  {317,"METHYL ISOPROPYL KETONE",86.134,553.4,38,310,0.259,0.349},
  {318,"METHYL MERCAPTAN",48.107,470,71.4,145,0.268,0.155},
  {319,"METHYL N-PROPYL KETONE",86.134,564,38.4,301,0.25,0.348},
  {320,"METHYL PHENYL ETHER",108.14,641,41.2,0,0,0},
  {321,"METHYL PHENYL KETONE",120.151,701,38,376,0.25,0.42},
  {322,"METHYL PROPIONATE",88.107,530.6,39.5,282,0.256,0.352},
  {323,"METHYLAL",76.096,497,0,0,0,0},
  {324,"METHYLCYCLOHEXANE",98.189,572.1,34.3,368,0.269,0.233},
  {325,"M-ETHYLPHENOL",122.167,716.4,0,0,0,0},
  {326,"METHYLPHENYLAMINE",107.156,701,51.3,0,0,0},
  {327,"MONOETHANOLAMINE",61.084,614,44,196,0.17,0},
  {328,"MORPHOLINE",87.122,618,54,253,0.27,0.37},
  {329,"M-TERPHENYL",230.31,924.8,34.6,784,0.358,0},
  {330,"M-TOLUIDINE",107.156,709,41,343,0.24,0.406},
  {331,"M-XYLENE",106.168,617,35,376,0.26,0.331},
  {332,"N,N-DIMETHYLANILINE",121.183,687,35.8,0,0,0},
  {333,"NAPHTHALENE",128.174,748.4,40,410,0.267,0.302},
  {334,"N-BUTANE",58.124,425.2,37.5,255,0.274,0.193},
  {335,"N-BUTANOL",74.123,562.9,43.6,274,0.259,0.59},
  {336,"N-BUTYL AMINE",73.139,524,41,288,0.27,0.396},
  {337,"N-BUTYL-ACETATE",116.161,571,32.3,371,0.26,0.4},
  {338,"N-BUTYLANILINE",149.236,721,28,518,0.25,0},
  {339,"N-BUTYLBENZENE",134.222,660.5,28.5,497,0.261,0.392},
  {340,"N-BUTYLCYCLOHEXANE",140.27,667,31.1,0,0,0.362},
  {341,"N-BUTYRALDEHYDE",72.107,524,40,278,0.26,0.352},
  {342,"N-BUTYRIC ACID",88.107,628,52,292,0.295,0.67},
  {343,"N-DECANE",142.286,617.6,20.8,603,0.247,0.49},
  {344,"N-DECYCLCYCLOPENTANE",210.405,723.8,15,0,0,0.654},
  {345,"N-DECYCYCLOHEXANE",224.432,750,13.4,0,0,0.583},
  {346,"N-DODECENE",170.34,658.3,18,713,0.24,0.562},
  {347,"N-DODECYCLOPENTANE",238.459,750,12.8,0,0,0.719},
  {348,"N-EICOSANE",282.556,767,11,0,0,0.907},
  {349,"NEON",20.183,44.4,27.2,41.7,0.311,0},
  {350,"N-HEPTADECANE",240.475,733,13,1000,0.22,0.77},
  {351,"N-HEPTANE",100.205,540.2,27,432,0.263,0.351},
  {352,"N-HEPTYLCYCLOPENTANE",168.324,679,19.2,0,0,0.515},
  {353,"N-HEXADECANE",226.448,717,14,0,0,0.742},
  {354,"N-HEXADECYLCYCLOPENTANE",294.567,791,9.6,0,0,0.861},
  {355,"N-HEXANE",86.178,507.4,29.3,370,0.26,0.296},
  {356,"N-HEXYLCYCLOPENTANE",154.297,660.1,21.1,0,0,0.476},
  {357,"NITRIC OXIDE",30.006,180,64,58,0.25,0.607},
  {358,"NITROGEN",28.013,126.2,33.5,89.5,0.29,0.04},
  {359,"NITROGEN DIOXIDE",46.006,431.4,100,170,0.48,0.86},
  {360,"NITROGEN TRIFLUORIDE",71.002,234,44.7,0,0,0.132},
  {361,"NITROMETHANE",61.041,588,62.3,173,0.224,0.346},
  {362,"NITROSYL CHLORIDE",65.459,440,90,139,0.35,0.318},
  {363,"NITROUS OXIDE",44.013,309.6,71.5,97.4,0.274,0.16},
  {364,"N-NONADECANE",268.529,756,11,0,0,0.827},
  {365,"N-NONANE",128.259,594.6,22.8,548,0.26,0.444},
  {366,"N-NONYCLYCLOPENTANE",196.378,710.5,16.3,0,0,0.61},
  {367,"N-OCTADECANE",254.502,745,11.9,0,0,0.79},
  {368,"N-OCTANE",114.232,568.8,24.5,492,0.259,0.394},
  {369,"N-OCTYLCYCLOPENTANE",182.351,694,17.7,0,0,0.564},
  {370,"N-PENTADECANE",212.421,707,15,880,0.23,0.706},
  {371,"N-PENTADECYLCYCLOPENTANE",280.54,780,10.1,0,0,0.833},
  {372,"N-PENTANE",72.151,469.6,33.3,304,0.262,0.251},
  {373,"N-PROPYL ACETATE",102.134,549.4,32.9,345,0.252,0.392},
  {374,"N-PROPYL AMINE",59.112,497,46.8,233,0.267,0.229},
  {375,"N-PROPYL FORMATE",88.107,538,40.1,285,0.259,0.315},
  {376,"N-PROPYL PROPIONATE",116.161,578,0,0,0,0},
  {377,"N-PROPYLBENZENE",120.195,638.3,31.6,440,0.265,0.344},
  {378,"N-PROPYLCYCLOHEXANE",126.243,639,27.7,0,0,0.258},
  {379,"N-PROPYLCYCLOPENTANE",112.216,603,29.6,425,0.25,0.335},
  {380,"N-TETRADECANE",198.394,694,16,830,0.23,0.679},
  {381,"N-TETRADECYCLOPENT",266.513,772,11.1,0,0,0.789},
  {382,"N-TRIDECANE",184.367,675.8,17,780,0.24,0.623},
  {383,"N-TRIDECYLCYCLOPENTANE",252.486,761,11.9,0,0,0.755},
  {384,"N-UNDECENE",156.313,638.8,19.4,660,0.24,0.535},
  {385,"N-VALERIC ACID",102.134,651,38,340,0.24,0.616},
  {386,"O-CRESOL",108.14,697.6,49.4,282,0.24,0.443},
  {387,"O-DICHLOROBENZENE",147.004,697.3,40.5,360,0.225,0.272},
  {388,"O-ETHYLPHENOL",122.167,703,0,0,0,0},
  {389,"O-TERPHENYL",230.31,891,38.5,769,0.405,0},
  {390,"O-TOLUIDINE",107.156,694,37,343,0.26,0.435},
  {391,"OXYGEN",31.999,154.6,49.8,73.4,0.288,0.021},
  {392,"O-XYLENE",106.168,630.2,36.8,369,0.263,0.314},
  {393,"OZONE",47.998,261,55,88.9,0.288,0.215},
  {394,"P-CRESOL",108.14,704.6,50.8,0,0,0.515},
  {395,"P-DICLOROBENZENE",147.004,685,39,372,0.26,0.27},
  {396,"PERFLUOROBENZENE",186.056,516.7,32.6,0,0,0.4},
  {397,"PERFLUOROCYCLOHEXANE",300.047,457.2,24,0,0,0},
  {398,"PERFLUOROETHANE",100.016,306.4,38.9,175,0.271,0.226},
  {399,"PERFLUOROETHANE",138.012,292.8,0,224,0,0},
  {400,"PERFLUOROMETHYLCYCLOHEXANE",350.055,486.8,23,0,0,0.482},
  {401,"PERFLUORO-N-HEPTANE",388.051,474.8,16,664,0.273,0.56},
  {402,"PERFLUORO-N-HEXANE",338.044,451.7,18.8,442,0.224,0.73},
  {403,"P-ETHYLPHENOL",122.167,716.4,0,0,0,0},
  {404,"PHENANTHRENE",178.234,878,0,0,0,0},
  {405,"PHENETOLE",122.167,647,33.8,0,0,0},
  {406,"PHENOL",94.113,694.2,60.5,229,0.24,0.44},
  {407,"PHOSGENE",98.916,455,56,190,0.28,0.204},
  {408,"PHOSPHORUS TRICHLORIDE",137.333,563,0,260,0,0},
  {409,"PHTHALIC ANHYDRIDE",148.118,810,47,368,0.26,0},
  {410,"PIPERIDINE",85.15,594,47,289,0.28,0.25},
  {411,"PROPADIENE",40.065,393,54,162,0.271,0.313},
  {412,"PROPANE",44.097,369.8,41.9,203,0.281,0.152},
  {413,"PROPIONALDEHYDE",58.08,496,47,223,0.26,0.313},
  {414,"PROPIONIC ACID",74.08,612,53,230,0.242,0.536},
  {415,"PROPIONITRILE",55.08,564.4,41.3,230,0.205,0.318},
  {416,"PROPYL CHLORIDE",78.542,503,45.2,254,0.278,0.23},
  {417,"PROPYLENE",42.081,365,45.6,181,0.275,0.148},
  {418,"PROPYLENE OXIDE",58.08,482.2,48.6,186,0.228,0.269},
  {419,"P-TERPHENYL",230.31,926,32.8,779,0.336,0},
  {420,"P-TOLUIDINE",107.156,667,0,0,0,0},
  {421,"P-XYLENE",106.168,616.2,34.7,379,0.26,0.324},
  {422,"PYRIDINE",79.102,620,55.6,254,0.277,0.24},
  {423,"PYRROLE",67.091,640,0,0,0,0},
  {424,"PYRROLIDINE",71.123,568.6,55.4,249,0.296,0},
  {425,"SEC-BUTYLBENZENE",134.222,664,29.1,0,0,0.274},
  {426,"SEC-BUTYLCYCLOHEXANE",140.27,669,26.4,0,0,0.264},
  {427,"SILICON TETRACHLORIDE",169.898,507,37,326,0.29,0.264},
  {428,"SILICON TETRAFLUORIDE",104.08,259,36.7,0,0,0},
  {429,"STYRENE",104.152,647,39.4,0,0,0.257},
  {430,"SUCCINIC ACID",118.09,0,0,0,0,0},
  {431,"SULFUR DIOXIDE",64.063,430.8,77.8,122,0.268,0.251},
  {432,"SULFUR HEXAFLUORIDE",146.05,318.7,37.1,198,0.281,0.286},
  {433,"SULFUR TRIOXIDE",80.058,491,81,130,0.26,0.41},
  {434,"TERT-BUTANOL",74.123,506.2,39.2,275,0.259,0.618},
  {435,"TERT-BUTYL CHLORIDE",92.569,507,39,295,0.28,0.19},
  {436,"TERT-BUTYLBENZENE",134.222,660,29.3,0,0,0.265},
  {437,"TERT-BUTYLCYCLOHEXANE",140.27,659,26.3,0,0,0.252},
  {438,"TETRACHLOROETHYLENE",165.834,620,44,290,0.25,0},
  {439,"TETRAHYDROFURAN",72.107,540.2,51.2,224,0.259,0},
  {440,"THIOPHENE",84.136,579.4,56.2,219,0.259,0.2},
  {441,"TOLUENE",92.141,591.7,40.6,316,0.264,0.257},
  {442,"TRANS-1,2-DIMETHYLCYCLOHEXANE",112.216,596,29.3,0,0,0.242},
  {443,"TRANS-1,2-DIMETHYLCYCLOPENTANE",98.189,553.2,34,362,0.27,0.269},
  {444,"TRANS-1,3-DIMETHYLCYCLOHEXANE",112.216,598,29.3,0,0,0.189},
  {445,"TRANS-1,4-DIMETHYLCYCLOHEXANE",112.216,590,29.3,0,0,0.242},
  {446,"TRANS-2-BUTENE",56.108,428.6,40.5,238,0.274,0.214},
  {447,"TRANS-2-HEXENE",84.162,516,32.3,351,0.27,0.242},
  {448,"TRANS-2-OCTENE",112.216,580,27.3,0,0,0.35},
  {449,"TRANS-2-PENTENE",70.135,475,36.1,300,0.28,0.237},
  {450,"TRANS-3-HEXENE",84.162,519.9,32.1,350,0.26,0.227},
  {451,"TRANS-DECALIN",138.254,690,31,0,0,0.27},
  {452,"TRIBUTYLAMINE",185.355,643,18,0,0,0},
  {453,"TRICHLOROETHYLENE",131.389,571,48.5,256,0.265,0.213},
  {454,"TRICHLOROFLUOROMETHANE",37.368,471.2,43.5,248,0.279,0.188},
  {455,"TRIETHYLAMINE",101.193,535,30,390,0.27,0.329},
  {456,"TRIFLUOROACETIC ACID",114.024,491.3,32.2,0,0,0},
  {457,"TRIFLUOROBROMOMETHANE",148.91,340.2,39.2,200,0.28,0},
  {458,"TRIMETHYL AMINE",59.112,433.2,40.2,254,0.287,0.195},
  {459,"VALERALDEHYDE",86.134,554,35,333,0.26,0.4},
  {460,"VINYL ACETATE",86.091,525,43,265,0.26,0.34},
  {461,"VINYL CHLORIDE",62.499,429.7,55.3,169,0.265,0.122},
  {462,"VINYL ETHYL ETHER",72.107,475,40.2,260,0.27,0},
  {463,"VINYL FLUORIDE",46.044,327.8,51.7,144,0.277,0},
  {464,"VINYL FORMATE",72.064,475,57,210,0.31,0.55},
  {465,"VINYL METHYL ETHER",58.08,436,47,205,0.27,0.34},
  {466,"VINYLACETYLENE",52.076,455,49,202,0.26,0.092},
  {467,"WATER",18.015,647.3,217.6,56,0.229,0.344},
  {468,"XENON",131.3,289.7,57.6,118,0.286,0.002}
};
  
 //Propane  Tc = 369.9 K, pc = 42.0 atm, and ω = 0.152
}

class composition{
  public:
    double z[3];
    
    double checkSum(){
      double sum = 0.0;
      for(int i = 0; i< 3; i++){
        sum+=z[i];
      }
      
      if(sum == 1.0)
        return 1.0;
      else 
        return -1.0;
    }
    
    double getMolWeight(){
      double MW = 0.0;
      for(int i=0; i< 3; i++){
        MW += z[i]*1;//"1" should be replaced by the MW of the compound
      }
      
      return 0;
    }
};


//Boundary Class
class boundary: public composition{
  public:
    double pressureIn;
    double temperatureIn;
    double pressureOut;
    double density;
    double elevation;
    
    
    
    double effectivePressure(double p, double el){
      return (p + el*1000*9.80665/1000);
    }


};

//PID Controller Class
class PID{
  public:
    double PV, SP, CO;
    double error, Kc=0.5, Ti=2.0, Td;

    double controlPID(double dt, double pv, double sp, double integral){

      error = pv - sp;
      CO = Kc*error + Kc*integral/Ti;
      return CO/100.0;
    }

    double errorIntegral(double dt, double pv, double sp, double iError){
       return iError+(pv-sp)*dt;
    }
};

//Pipe Class
class pipe: public composition{
  public:
    double dInner, dOuter;
    double pipeLen;
    
    double tempIn, tempOut, tempAvg;

    double getflowIn(double p1, double p2, double k){
      return k*sqrt(p1-p2);
    }

};

//Valve inherits Pipe class
class valve : public pipe{
  public:
    double Cvmax;

    double flowArea(){
      return (PI*0.25*dInner*dInner);
    }

    double flowVolume(){
      return (PI*dInner*pipeLen);
    }

    double getflowIn(double p1, double p2, double opening){//Overriding the method for flow calculation
      if(opening > 1.0)
        opening = 1.0;
      if(opening <0.0)
        opening = 0.0;
      return opening*Cvmax*sqrt(p1-p2);
    }



};

class heatxch : public pipe{
  public:
      double fitRes;
      double heatDuty;
      double Tin, TOut;
      
      double hxArea;
      double U;
      
      double getflowIn(double p1, double p2, double fitr){//Overriding the method for flow calculation
      if(fitr <0.0)
        fitr = 0.0;
      
      return fitr*sqrt(p1-p2);
      }
      
      double getOutletTemp(double dt, double fin, double T, double q){
       if(fin <= 0.0)
        return T;
       else
        return T +(dt*q/(fin*4.187));
      }
      
      double getLMTD(double Thot1, double Thot2, double Tcold1, double Tcold2){
        return ((Thot1 - Tcold1)-(Thot2 - Tcold2))/log((Thot1 - Tcold1)/(Thot2 - Tcold2));
      }
    

};

class pump : public pipe{
  public:
      
      int runFlag; //0 = Stop; 1= Run
      double a0, a1, a2; //Pump curve coefficients
      double speed;
      
      double suctionPressure, dischargePressure;
      
      
      double getflowIn(double p1, double p2, double a, double b, double c, double ns, int flag){
        if(flag != 0 ){
          b*= ns;
          c*= ns*ns;
        
        return (-b - sqrt(b*b-(4*a*(c-(p1-p2)))))/(2*a);// Affinity laws
          
        }
        
        return 100*sqrt(p1-p2);
        
      }
      
      double getPowerConsumed(){
        return 0;
      }
      
};

class tank: public composition{
  public:
    double diaInner, length, volume;
    double opPressure;
    double heatIn;

    double portInHeight, portOutHeight;//in absolute terms from the bottom of the tank [m]
    double portInHeight2;

    double getVolume(double di, double len){
      return PI*di*di*len*0.25;
    }

    double getOpPressure(double inH, double lev){
      return 101.325+ (lev-inH)*1000*9.80665*0.001;
    }

    double levelAccumulated(double dt, double fin, double fout, double h){
      return h+(dt*(fin-fout))/(1000.0*1.5);
    }

    double enthalpyAccumulated(double dt, double fin1, double fin2, double fout, double tankT, double q, double mass, double enthalpy){
      return dt*((fin1*4.187*(40-25) + fin2*4.187*(60-25))-(fout*4.187*(tankT -25))+q)+enthalpy;
    }
    
    double massAccumulated(double dt, double fin, double fout, double mass){
      return mass + (dt*(fin-fout));
    }
    
    double *calcComposition(double fin1, double fin2, double massInTank, double port1[], double port2[], double tankC[], double num){
      
      static double tcomp[3];
      
      for(int i=0; i<num;i++){
        tcomp[i] = (fin1*port1[i] + fin2*port2[i] + massInTank*tankC[i])/(fin1 + fin2 + massInTank);
      }
      
      return tcomp;
    }

};

class node : public boundary{
  public:
    
    
    double initPressure, initTemperature;
    double massIn, massOut;
    
    double getPressure(double m1, double m2, double nodeP){
      double error = abs(m1-m2);
      if(error <= 0.001)
        return nodeP;
      else
      {
        
          
          nodeP+=error*10;
          
          
        
      return 0;
      }  
    }
  
};

class slider{
  public:
    double pos;
  
};


int main()
{
  
  double deltaT = 0.1;
  double flowIn = 0.0, flowOut = 0.0, tankLevel = 0.0, tankPressure = 101.325, tankTemperature = 25.0, mass = 0.0, enthalpyIn = 0.0;
  
  double flowIn1 =0.0, flowIn2 = 0.0, flowIn3 = 0.0, flowIn4 = 0.0, flowIn5 = 0.0, flowIn6 = 0.0;

  double intError = 0.0, intError2 = 0.0, intError3 = 0.0;
  
  double head = 165.9;
  
  double *tankComp;

  //Object definitions
  boundary b1, b2, b3, b4, b5, b6, b7;
  valve v1, v2, v3, v4;
  pipe pip1;
  PID pid1, pid2, pid3;
  tank t1;
  heatxch h1, h2;
  pump pu1;
  node n1;
  slider sl1, sl2;

  //Object inputs
  v1.dInner = 10.0;
  v1.dOuter = 11.0;
  v1.pipeLen = 2.0;
  v1.Cvmax = 50.0;
  pid1.CO = 0.5;

  v2.Cvmax =55.3;
  pid2.CO = 0.75;
  
  v3.Cvmax = 20.0;
  
  v4.Cvmax = 40.0;

  t1.diaInner = 2.1;
  t1.length = 5.0;

  t1.portInHeight = 3.1;
  t1.portInHeight2 = 3.2;
  t1.portOutHeight = 0.5;
  
  t1.z[0] = 1.0;
  t1.z[1] = 0.0;
  t1.z[2] = 0.0;
  
  

  t1.heatIn = 100.0;
  
  

  t1.volume = t1.getVolume(t1.diaInner, t1.length);
  //t1.opPressure = t1.getOpPressure();
  pu1.speed = 0.95;
  pu1.a0 = -0.002587798;
  pu1.a1 = -0.036577381;
  pu1.a2 = 165.9125;
  pu1.runFlag = 0;
  
  b1.pressureIn = 120.1; //in kPa
  b2.pressureOut = 101.325;
  
  b1.elevation = 5.0;// in [m]
  
  b1.temperatureIn = 40.0;
  b1.z[0] = 0.2;
  b1.z[1] = 0.5;
  b1.z[2] = 0.3;
  
  cout << b1.checkSum()<< endl;
  

  pid1.SP = 105.0;
  pid2.SP = 2.0;
  pid3.SP = 85.0;

  pid1.Kc = -0.15;
  pid1.Ti = 1.0;
  pid2.Kc = 0.5;
  pid2.Ti = 2.0;
  pid3.Kc = 1.0;
  pid3.Ti = 2.1;
  
  b3.pressureIn = 150.0;
  b3.temperatureIn = 50.0;
  
 
  
  b4.pressureOut = 120.0;
  
  b5.pressureIn = 125.6;
  b5.temperatureIn = 60.0;
  
  b5.z[0] = 0.5;
  b5.z[1] = 0.1;
  b5.z[2] = 0.4;
  
  cout << b5.checkSum()<<endl;
  
  
  b6.pressureIn = 110.0;
  b6.temperatureIn = 90.0;
  b6.elevation = 5.0;
  
  b6.z[0] = 1.0;
  b6.z[1] = 0.0;
  b6.z[2] = 0.0;
  
  b7.pressureOut = 105.0;
  b7.elevation = 3.6;
  
  sl1.pos = 0.0;
  
  n1.initPressure = 101.325;
  
  h1.fitRes =10.0;
  h1.heatDuty = 0;//Changed from 100.0 
  
  h2.fitRes = 90.0;
  h2.hxArea = 2.0;
  h2.U = 0.01;//in [kW/m^2. K]
  
  h1.Tin = h1.TOut = b3.temperatureIn;  //Initial exit temperature of the hxer 
  h2.Tin = b6.temperatureIn;
  h2.TOut = h2.Tin - 0.05;
  

  //Object linking and connections
  for(double t=0.0;t<2500.0;t+=deltaT){
    flowIn1 = v1.getflowIn(b1.effectivePressure(b1.pressureIn,b1.elevation), t1.getOpPressure(t1.portInHeight, tankLevel), pid1.controlPID(deltaT,flowIn, pid1.SP, intError2));
    flowIn3 = v3.getflowIn(b5.pressureIn,t1.getOpPressure(t1.portInHeight2, tankLevel),0.5);
    flowIn = flowIn1 + flowIn3;
    
    v1.z[0] = b1.z[0];
    v1.z[1] = b1.z[1];
    v1.z[2] = b1.z[2];
    
    v3.z[0] = b5.z[0];
    v3.z[1] = b5.z[1];
    v3.z[2] = b5.z[2];
    
    v1.tempIn = v1. tempOut = b1.temperatureIn;
    tankLevel = t1.levelAccumulated(deltaT, flowIn, flowOut, tankLevel);
    tankPressure = 101.325 + (1000*9.80665*tankLevel*0.001);
    
    mass = t1.massAccumulated(deltaT,flowIn, flowOut, mass);
    enthalpyIn = t1.enthalpyAccumulated(deltaT, flowIn1,flowIn3, flowOut, tankTemperature, t1.heatIn, mass, enthalpyIn);
    tankTemperature = 25 + enthalpyIn/(mass*4.187); //25 is reference temperature for enthalpy calculation
    tankComp = t1.calcComposition(flowIn1, flowIn3,mass,v1.z,v3.z,t1.z,3);
    
    flowOut = v2.getflowIn(tankPressure, b2.pressureOut, pid2.controlPID(deltaT,tankLevel, pid2.SP, intError));
   // v2.tempIn = v2.tempOut = tankTemperature;

    intError = pid2.errorIntegral(deltaT, tankLevel, pid2.SP, intError);
    intError2 = pid1.errorIntegral(deltaT, flowIn, pid1.SP, intError2);
    
    flowIn2 = h1.getflowIn(b3.pressureIn, b4.pressureOut, h1.fitRes);
    
    h1.TOut = h1.getOutletTemp(deltaT,flowIn2,h1.TOut,h1.heatDuty);
    
    head-=0.01;
    if(head < 110.0)
      head = 110.0;
    
    flowIn4 = pu1.getflowIn(head, 0.01, pu1.a0, pu1.a1, pu1.a2, pu1.speed, pu1.runFlag);
    
    for(int i=0;  i<3; i++){
      
      t1.z[i] =  *(tankComp + i);
      //cout << t1.z[i]<< " ";
    }
    //cout<< endl;
    //cout << t << " " << flowIn2 << " " <<h1.TOut<<endl;

    //cout << flowIn1<<" "<<flowIn3 << " " << flowOut<< " "<< tankLevel <<" " << tankPressure<< " "<<tankTemperature<<" "<<pid2.CO<<  endl;
    //cout << enthalpyIn << " " << tankTemperature  << endl;
    
    //cout <<head << " "<< flowIn4<< endl;
    
   // flowIn5 = v4.getflowIn(b6.effectivePressure(b6.pressureIn, b6.elevation), b7.effectivePressure(b7.pressureOut, b7.elevation), sl1.pos);
   flowIn5 = h2.getflowIn(b6.pressureIn,b7.pressureOut,pid3.controlPID(deltaT,h2.TOut,pid3.SP,intError3));
   intError3 = pid3.errorIntegral(deltaT,h2.TOut,pid3.SP,intError3);
   h2.heatDuty = -h2.U * h2.hxArea * h2.getLMTD(h2.Tin, h2.TOut,h1.Tin, h1.TOut);
   
   h2.TOut = h2.getOutletTemp(deltaT, flowIn5, h2.TOut, h2.heatDuty);
   h1.heatDuty = -h2.heatDuty;
   
    cout << flowIn5 << " " <<h1.Tin <<" "<< h1.TOut <<" "<< h2.Tin <<" "<< h2.TOut<<" "<<h1.heatDuty<<" "<<h2.heatDuty<< endl;
    //sl1.pos+= 0.01;
    
    //n1.effectivePressure()

  }


}
