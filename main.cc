//
//  main.cc
//  hw1
//
//  Created by liliang on 2/13/16.
//  Copyright © 2016 liliang. All rights reserved.
//

//
// the main just makes sure that there is an argument passed, which is
// supposed to be the scenefile.
//

#include "readscene.h"
int main (int argc, char *argv[])
{
    
    if (argc != 5) {
        cerr << "useage: raytra scenefilename output_path pRayNum sRayNum" << endl;
        return -1;
    }

    Readscene rs;
    clock_t tStart = clock();
    rs.parseSceneFile (argv[1], argv[2], argv[3], argv[4]);
    double tend =(double)(clock() - tStart)/CLOCKS_PER_SEC;
    cout<<"Done!" <<endl;
    cout<<"Time taken: " << tend <<endl;
    // Dear TA, the deletion of pointers is in readscene.cc (after writeRgba() )
    return 0;
}

