

#define IM_DEBUGGING

#include "readscene.h"

#define SHADOW_RAY 0
#define REGULAR_RAY 1


void Readscene:: read_wavefront_file (
                          const char *file,
                          std::vector< int > &tris,
                          std::vector< float > &verts)
{
    
    cout<<"read_wavefile"<<endl;
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
            
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
        }
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
    }
    
    in.close();
    
    //   std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << std::endl;
}

void
Readscene:: writeRgba (const char fileName[],
           const Rgba *pixels,
           int width,
           int height
           )
{
    RgbaOutputFile file (fileName,width,height, WRITE_RGBA);  /* define width and height of new file*/
    file.setFrameBuffer (pixels, 1, width);
    file.writePixels (height);
}


// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float getTokenAsFloat (string inString, int whichToken)
{
    
    float thisFloatVal = 0.;    // the return value
    
    if (whichToken == 0) {
        cerr << "error: the first token on a line is a character!" << endl;
        exit (-1);
    }
    
    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char [inString.size () + 1];
    
    strcpy (cstr, inString.c_str());
    
    char *p = strtok (cstr, " ");      /* split string using " " as delimiter */
    if (p == 0) {
        cerr << "error: the line has nothing on it!" << endl;
        exit (-1);
    }
    
    for (int i = 0; i < whichToken; i++) {
        p = strtok (0, " ");
        if (p == 0) {
            cerr << "error: the line is not long enough for your token request!" << endl;
            exit (-1);
        }
    }
    
    thisFloatVal = atof (p);   /* Convert string to double */
    
    delete[] cstr;
    
    return thisFloatVal;
}


void deleteTree(BVHNode *root){
    if(root){
        deleteTree(dynamic_cast<BVHNode*>(root->getLeftNode()));
        deleteTree(dynamic_cast<BVHNode*>(root->getRightNode()));
        delete root;
    }
}

Camera ca;
std::vector<Surface *> surface_list;
std::vector<Light *>light_list;
std::vector<float> v_list;
std::vector<int > tris_list;
Light * ambientLight;
BVHNode *root;

void Readscene:: parseSceneFile (char *filnam, char *output, char* rayNum, char* shadowRayNum)
{
    
    ifstream inFile(filnam);    // open the file
    string line;
    
    if (! inFile.is_open ()) {  // if it's not open, error out.
        cerr << "can't open scene file" << endl;
        exit (-1);
    }
    //l s x y z nx ny nz ux uy uz len r g b
    float sx=0, sy=0, sz=0, sr=0;            // sphere
    float cx = 0, cy=0, cz=0,cdx=0,cdy=0,cdz=0, cw=0,ch=0,cd=0,cpx=0,cpy=0;   // camera
    float pl_x=0, pl_y=0, pl_z=0, pl_r=0, pl_g=0, pl_b=0; // point light
    float a_r=0, a_g =0, a_b=0;  // ambient light
    float ar_x=0, ar_y=0, ar_z=0,ar_nx=0, ar_ny=0, ar_nz=0, ar_ux=0, ar_uy=0, ar_uz=0, ar_len=0, ar_r=0, ar_g=0, ar_b=0;
    float mdr=0, mdg=0, mdb=0, msr=0, msg=0, msb=0, ms_rough=0, mir=0, mig=0, mib=0; //material
    float plane_x=0, plane_y=0, plane_z=0,plane_d=0; // plane
    float t_ax=0, t_ay=0, t_az=0, t_bx=0,t_by=0,t_bz=0,t_cx=0,t_cy=0,t_cz=0; // triangle
   

    Material lastMaterial;
    while (! inFile.eof ()) {   // go through every line in the file until finished
        Surface *thisSurface = 0;
        BBox *thisBbox = 0;
        Light *light = 0;
        getline (inFile, line); // get the line
        
        switch (line[0])  {     // we'll decide which command based on the first character
                

            case 's':   // sphere
            {
                sx = getTokenAsFloat (line, 1);
                sy = getTokenAsFloat (line, 2);
                sz = getTokenAsFloat (line, 3);
                sr = getTokenAsFloat (line, 4);
                
                thisBbox = new BBox(sx-sr, sy-sr, sz-sr, sx+sr, sy+sr, sz+sr);
                thisSurface = new Sphere(sx,sy,sz,sr);
                thisSurface->setIndex((int)surface_list.size());
                thisSurface->setMaterial(lastMaterial);
                thisSurface->setSurfaceMin(sx-sr, sy-sr, sz-sr);
                thisSurface->setSurfaceMax(sx+sr, sy+sr, sz+sr);
                thisSurface->setbbox(*thisBbox); // must do this for mode 1
                surface_list.push_back(thisSurface);
#ifdef IM_DEBUGGING
                // if we're debugging, show what we got:
//                cout << "got a sphere with ";
//                cout << "parameters: " << sx << " " << sy << " " << sz << " " << sr << endl;
#endif
                break;
            }
                
            case 't': // triangle
            {
                t_ax = getTokenAsFloat (line, 1);
                t_ay = getTokenAsFloat (line, 2);
                t_az = getTokenAsFloat (line, 3);
                t_bx = getTokenAsFloat (line, 4);
                t_by = getTokenAsFloat (line, 5);
                t_bz = getTokenAsFloat (line, 6);
                t_cx = getTokenAsFloat (line, 7);
                t_cy = getTokenAsFloat (line, 8);
                t_cz = getTokenAsFloat (line, 9);
                
                float boxminX = fmin(t_ax,fmin(t_bx,t_cx));
                float boxmaxX = fmax(t_ax,fmax(t_bx,t_cx));
                float boxminY = fmin(t_ay,fmin(t_by,t_cy));
                float boxmaxY = fmax(t_ay,fmax(t_by,t_cy));
                float boxminZ = fmin(t_az,fmin(t_bz,t_cz));
                float boxmaxZ = fmax(t_az,fmax(t_bz,t_cz));
                
                thisBbox = new BBox(boxminX,boxminY,boxminZ,boxmaxX,boxmaxY,boxmaxZ);
             
                
                thisSurface = new Triangle(t_ax, t_ay, t_az, t_bx, t_by, t_bz, t_cx, t_cy, t_cz);
                thisSurface->setIndex((int)surface_list.size());
                thisSurface->setMaterial(lastMaterial);
                thisSurface->setSurfaceMin(boxminX, boxminY, boxminZ);
                thisSurface->setSurfaceMax(boxmaxX, boxmaxY, boxmaxZ);
                thisSurface->setbbox(*thisBbox);
                surface_list.push_back(thisSurface);
                break;
            }
                
            case 'w':{
                istringstream iss(line);
                string cmd, aw_file;
                iss>> cmd >> aw_file;
                this->read_wavefront_file(aw_file.c_str(), tris_list, v_list);
                for(unsigned int i=0; 3*i+2<tris_list.size();i++){
                    t_ax = v_list[3*tris_list[3*i]];
                    t_ay = v_list[3*tris_list[3*i]+1];
                    t_az = v_list[3*tris_list[3*i]+2];
                    t_bx = v_list[3*tris_list[3*i+1]];
                    t_by = v_list[3*tris_list[3*i+1]+1];
                    t_bz = v_list[3*tris_list[3*i+1]+2];
                    t_cx = v_list[3*tris_list[3*i+2]];
                    t_cy = v_list[3*tris_list[3*i+2]+1];
                    t_cz = v_list[3*tris_list[3*i+2]+2];
                    
                    float boxminX = fmin(t_ax,fmin(t_bx,t_cx));
                    float boxmaxX = fmax(t_ax,fmax(t_bx,t_cx));
                    float boxminY = fmin(t_ay,fmin(t_by,t_cy));
                    float boxmaxY = fmax(t_ay,fmax(t_by,t_cy));
                    float boxminZ = fmin(t_az,fmin(t_bz,t_cz));
                    float boxmaxZ = fmax(t_az,fmax(t_bz,t_cz));
                    
                    thisBbox = new BBox(boxminX,boxminY,boxminZ,boxmaxX,boxmaxY,boxmaxZ);

                    thisSurface = new Triangle(t_ax,t_ay,t_az,t_bx,t_by,t_bz,t_cx,t_cy,t_cz);
                    thisSurface->setIndex((int)surface_list.size());
                    thisSurface->setMaterial(lastMaterial);
                    thisSurface->setSurfaceMin(boxminX, boxminY, boxminZ);
                    thisSurface->setSurfaceMax(boxmaxX, boxmaxY, boxmaxZ);
                    thisSurface->setbbox(*thisBbox);
                    
                    surface_list.push_back(thisSurface);
                }
                break;
            }
                
            case 'p':   // plane
                plane_x = getTokenAsFloat (line, 1);
                plane_y = getTokenAsFloat (line, 2);
                plane_z = getTokenAsFloat (line, 3);
                plane_d = getTokenAsFloat (line, 4);
                
                thisSurface = new Plane(plane_x, plane_y, plane_z, plane_d);
                thisSurface->setMaterial(lastMaterial);
                surface_list.push_back(thisSurface);
                break;
                
                //
                // camera:
                //
            case 'c':   // camera
                // one trick here: the cameras pixel count (width, height) are integers,
                // so cast them.
                
                cx = getTokenAsFloat (line, 1);
                cy = getTokenAsFloat (line, 2);
                cz = getTokenAsFloat (line, 3);
                cdx = getTokenAsFloat (line, 4);
                cdy = getTokenAsFloat (line, 5);
                cdz = getTokenAsFloat (line, 6);
                cd  = getTokenAsFloat (line, 7);
                cw  = getTokenAsFloat (line, 8);
                ch  = getTokenAsFloat (line, 9);
                cpx = (int) getTokenAsFloat (line, 10);
                cpy = (int) getTokenAsFloat (line, 11);
                
                ca.setEye(cx, cy, cz);
                ca.setFilm(cw, ch, cpx, cpy);
                ca.setDistance(cd);
                ca.setOrientation(cdx, cdy, cdz);
                ca.setCor(ca.getOrientation());
                
                break;
                
                //
                // lights:
                //
            case 'l':   // light
                
                // slightly different from the rest, we need to examine the second param,
                // which is at the third position on the line:
                switch (line[2]) {
                    case 'p':   // point light
                        pl_x = getTokenAsFloat (line, 2);
                        pl_y = getTokenAsFloat (line, 3);
                        pl_z = getTokenAsFloat (line, 4);
                        pl_r = getTokenAsFloat (line, 5);
                        pl_g = getTokenAsFloat (line, 6);
                        pl_b = getTokenAsFloat (line, 7);
                        
                        light = new PointLight();
                        light->setPosition(pl_x, pl_y, pl_z);
                        light->setColor(pl_r, pl_g, pl_b);
                        light_list.push_back(light);
                        
                        break;
                    case 'd':   // directional light
                        break;
                    case 'a':   // ambient light
                        ambientLight = new AmbientLight();
                        a_r = getTokenAsFloat (line, 2);
                        a_g = getTokenAsFloat (line, 3);
                        a_b = getTokenAsFloat (line, 4);
                        ambientLight->setColor(a_r, a_g, a_b);
                        break;
                    case 's':
                        ar_x = getTokenAsFloat (line, 2);
                        ar_y = getTokenAsFloat (line, 3);
                        ar_z = getTokenAsFloat (line, 4);
                        ar_nx = getTokenAsFloat (line, 5);
                        ar_ny = getTokenAsFloat (line, 6);
                        ar_nz = getTokenAsFloat (line, 7);
                        ar_ux = getTokenAsFloat (line, 8);
                        ar_uy = getTokenAsFloat (line, 9);
                        ar_uz = getTokenAsFloat (line, 10);
                        ar_len = getTokenAsFloat (line,11);
                        ar_r = getTokenAsFloat (line, 12);
                        ar_g = getTokenAsFloat (line, 13);
                        ar_b = getTokenAsFloat (line, 14);
                        light = new AreaLight();
                        light->setLightDirection(ar_nx, ar_ny, ar_nz);
                        light->setUV(ar_ux, ar_uy, ar_uz);
                        light->setLen((int)ar_len);
                        light->setCenter(ar_x, ar_y, ar_z);
                        light->setColor(ar_r, ar_g, ar_b);
                        light_list.push_back(light);
                        break;
                        
                }
                
                break;
                
                //
                // materials:
                //
            case 'm':   // material
                mdr = getTokenAsFloat (line, 1);
                mdg = getTokenAsFloat (line, 2);
                mdb = getTokenAsFloat (line, 3);
                msr = getTokenAsFloat (line, 4);
                msg = getTokenAsFloat (line, 5);
                msb = getTokenAsFloat (line, 6);
                ms_rough = getTokenAsFloat (line, 7);
                mir = getTokenAsFloat (line, 8);
                mig = getTokenAsFloat (line, 9);
                mib = getTokenAsFloat (line, 10);
                lastMaterial.setDiffuse(mdr, mdg, mdb);
                lastMaterial.setSpecular(msr, msg, msb);
                lastMaterial.setRoughness(ms_rough);
                lastMaterial.setReflective(mir, mig, mib);                
                break;

                
                
            case '/':
                // don't do anything, it's a comment
                break;
                
                
                //
                // options
                //
            case 'o':   // make your own options if you wish
                break;
        }
        
    } // end while
    cout << "surface_list size: "<<surface_list.size()<<endl;
    cout << "light_list size: "<<light_list.size()<<endl;

    
    
    
    float left = -ca.getFilmWidth()/2;
    float bottom  = -ca.getFilmHeight()/2;
    Array2D<Imf::Rgba> pixels;
    pixels.resizeErase (ca.getFilmNy(), ca.getFilmNx());
    int pRayNum = *rayNum - '0';
    int pRayNum2 = pRayNum*pRayNum;
    cout<<"primaryRayNum: "<<pRayNum2<<endl;
    int pShadowRayNum =  *shadowRayNum -'0';
    cout<<"shadowRayNum: "<<pShadowRayNum*pShadowRayNum<<endl;
    
//    cout << "option: " << opt <<endl;
    
    
    // build BVH tree

    root = new BVHNode();
    cout<<"Starting building BVH tree..."<<endl;
    root = root->buildBVH(0,surface_list);
    cout<<"Building BVH tree done!"<<endl;
    cout<<"Rendering..."<<endl;

    
    
    srand ((unsigned int)time(NULL));
    for(unsigned int j=0; j<ca.getFilmNy();j++){
        for(unsigned int i=0; i<ca.getFilmNx();i++){
            Rgba &px = pixels[ca.getFilmNy()-j-1][i];
            for(int p=0; p<pRayNum; p++){
                for(int q=0; q<pRayNum; q++){
//                    float pixel_x= left+ca.getFilmWidth()*(i+0.5)/ca.getFilmNx();
//                     float pixel_y= bottom +ca.getFilmHeight()*(j+0.5)/ca.getFilmNy();
                    double r1 = (double)rand() / RAND_MAX;
                    double r2 = (double)rand() / RAND_MAX;
                    if(pRayNum == 1) r1=r2=0.5;
                    float pixel_x= left+ca.getFilmWidth()*(i+(p+r1)/pRayNum)/ca.getFilmNx();
                    float pixel_y= bottom +ca.getFilmHeight()*(j+(q+r2)/pRayNum)/ca.getFilmNy();
                    Ray r;
                    r.setDirection(ca.getCu()*pixel_x +ca.getCv()*pixel_y - ca.getCw()*ca.getDistance());
                    r.setOrigin(ca.getEye().getX(), ca.getEye().getY(), ca.getEye().getZ());
                    Rgba temp = rec(r, 0.001, std::numeric_limits<int>::max(), REGULAR_RAY, 2, 0,pShadowRayNum, *new Ray());
                    px.r+=temp.r;
                    px.g+=temp.g;
                    px.b+=temp.b;
                }
            }
            px.r /= pRayNum2;
            px.g /= pRayNum2;
            px.b /= pRayNum2;
        }
    }
    writeRgba(output, &pixels[0][0],ca.getFilmNx(),ca.getFilmNy());
    
    //delte ambient light
    if(ambientLight != NULL) delete ambientLight;
    
    //delete surface
    for (Surface * s : surface_list)
        delete s;
    //delete light
    for (Light * l : light_list)
        delete l;
    //delete BVHtree
    deleteTree(root);
}

Imf::Rgba Readscene:: rec(Ray& r, float min_t, float max_t, int ray_type, int recurse_limit, int lightIndex, int shadowRayNum, Ray& sNormal){
    Rgba R;
    R.r=0;R.g=0;R.b=0;R.a=1;
    
    bool surfaceIntersect = false;
    float minT =std::numeric_limits<int>::max();
    int surfaceIndex=-1;
    
    if(recurse_limit == 0) return R;
    
    if(ray_type == SHADOW_RAY){
        

//        root->bboxIntersect(r, minT, surfaceIndex);
//        if(minT >=min_t && minT <=max_t) return R;
        bool find = false;
        if(root->shadowIntersect(r, max_t,find)) return R;

        Color color =light_list[lightIndex]->getColor(r,sNormal);
        float max_t2 = (max_t+1)*(max_t+1);
        R.r = color.getR()/max_t2;
        R.g = color.getG()/max_t2;
        R.b = color.getB()/max_t2;
        return R;
    }


    // render using BVH
    root->bboxIntersect(r, minT, surfaceIndex);
      if(surfaceIndex >=0)surfaceIntersect =true;

    
    Material m;
    Ray surfaceNormal, bsector;;
    Point minIntersect;
    
    if(surfaceIntersect){
        
            m = surface_list[surfaceIndex]->getMaterial();

            minIntersect.setPosition(r.getOrigin()+r.getDir()*minT);
            surfaceNormal = surface_list[surfaceIndex]->getNormalAtIntersect(minIntersect);
        
//           // two-sided lighting
//            if(dot_product(r.getDir(), surfaceNormal.getDir()) >0)
//                surfaceNormal.reverse();
        
        
        for(unsigned int i=0; i<light_list.size(); i++){
            Light *pl = light_list[i];
            std::vector<Ray* > ray_list = surface_list[surfaceIndex]->getRayToLight(minIntersect, pl, shadowRayNum);
            for(unsigned int j=0; j<ray_list.size();j++){
                Rgba L_rgb;
                L_rgb.r=0;L_rgb.g=0;L_rgb.b=0;L_rgb.a=1;
                float distance = ray_list[j]->getLen();
                Rgba temp1 = rec(*ray_list[j],min_t, distance, SHADOW_RAY,1,i, shadowRayNum, surfaceNormal);
                L_rgb.r = temp1.r;
                L_rgb.g = temp1.g;
                L_rgb.b = temp1.b;
                Vector v_plus_l;
                v_plus_l.setDirection(r.reverse().getDir()+ray_list[j]->getDir());
                bsector.setDirection(v_plus_l);
                
                float n_dot_l = dot_product(surfaceNormal.getDir(),ray_list[j]->getDir() );
                n_dot_l = max((float) 0,n_dot_l);
                
                
                float n_dot_b =dot_product(surfaceNormal.getDir(), bsector.getDir());
                n_dot_b = pow( max((float)0, n_dot_b),m.getRoughness());
                
                R.r += (m.getDiffuse().getR() * L_rgb.r*n_dot_l + m.getSpecular().getR()*L_rgb.r*n_dot_b)/ray_list.size();
                R.g += (m.getDiffuse().getG() * L_rgb.g*n_dot_l + m.getSpecular().getG()*L_rgb.g*n_dot_b)/ray_list.size();
                R.b += (m.getDiffuse().getB() * L_rgb.b*n_dot_l + m.getSpecular().getB()*L_rgb.b*n_dot_b)/ray_list.size();
            }
            for(Ray* r: ray_list){
                delete r;
            }
        } // end for loop of light
        
            if(m.isReflective){
                Ray reflect_r;
                float d_N = dot_product(r.getDir(),surfaceNormal.getDir());
                Vector _2d_NN = surfaceNormal.getDir()*(-2*d_N);
                reflect_r.setDirection(r.getDir()+_2d_NN);
                reflect_r.setOrigin(minIntersect);
                
                Rgba new_R =  rec(reflect_r, min_t, max_t, REGULAR_RAY, recurse_limit-1,0, shadowRayNum, sNormal);
                R.r += m.getReflective().getR()*new_R.r;
                R.g += m.getReflective().getG()*new_R.g;
                R.b += m.getReflective().getB()*new_R.b;
            }
        
          // ambient light
//        if(ambientLight != NULL){
//            R.r += m.getDiffuse().getR()*ambientLight->getColor().getR();
//            R.g += m.getDiffuse().getG()*ambientLight->getColor().getG();
//            R.b += m.getDiffuse().getB()*ambientLight->getColor().getB();
//        }
        
    } // end if
    else {
        R.r=0;R.g=0;R.b=0;R.a=1;
    }
    return R;
}

