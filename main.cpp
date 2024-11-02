#include<iostream>
#include<SDL2/SDL.h>
//Global variables to initialise the height and width of the  window

const int WIDTH = 800, HEIGHT = 600;

SDL_Window * gWindow =NULL;
//image data type that holds the pixels of an image and renders it
SDL_Surface*  gScreenSurface = NULL;
SDL_Surface * gCurrentSurface = NULL;
SDL_Surface* loadSurface( std::string path );




//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//fn to start i SDL
bool init()
{
    //flag to check if it works or not
    bool success = true;

    //initialises SDL
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        std::cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<std::endl;
        success = false;
    }
    else
    {
        //create window
        gWindow = SDL_CreateWindow("SDL Tutorial",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            std::cout<<"Window cant be created "<<SDL_GetError()<<std::endl;
            success = false;
        }
        else
        {
            //gets  the surface of the window

            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
        return success;
    }

}


void close()
{
    //Deallocates stuff nd cleanup
    SDL_FreeSurface(gCurrentSurface);
    gCurrentSurface = NULL;

    //destroy 
    SDL_DestroyWindow( gWindow);
    gWindow=NULL;
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    //final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format , 0);
        if(optimizedSurface == NULL)
        {
            std::cout<<"Unable to optimize image"<<std::endl;
        }
        SDL_FreeSurface(loadedSurface);

    }

    return optimizedSurface;
}

bool loadMedia()
{
    //flag to check if it loads or not
    bool success;
    //Loads Default image/surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/test.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        std::cout<<"Failed to load IMG"<<std::endl;
        success = false;
    }

    //Loads up image/surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
    {
        std::cout<<"Failed to load IMG"<<std::endl;
        success = false;
    }

     //Loads down image/surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
    {
        std::cout<<"Failed to load IMG"<<std::endl;
        success = false;
    }

     //Loads left image/surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
    {
        std::cout<<"Failed to load IMG"<<std::endl;
        success = false;
    }

     //Loads rightRIGHTmage/surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
    {
        std::cout<<"Failed to load IMG"<<std::endl;
        success = false;
    }

    return success;
}

int main(int argc,char * argv[])
{
    if( !init())
        std::cout<<"Failed to initialise"<<std::endl;
    else    
    {
        if( !loadMedia())
            std::cout<<"Failed to load media"<<std::endl;
        else
        {
            SDL_Rect strectedRect;
            strectedRect.x=0;
            strectedRect.y=0;
            strectedRect.w=WIDTH;
            strectedRect.h=HEIGHT;
          
            SDL_Event e;
            bool quit = false;
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            
            while(!quit)
            {
                while(SDL_PollEvent(&e) !=0)
                {
                    if(e.type == SDL_QUIT)
                        quit = true;

                    else if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                                break;
                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                                break;
                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                                break;
                             case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                                break;
                             default:
                                gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }
                        SDL_BlitScaled(gCurrentSurface , NULL, gScreenSurface, &strectedRect);
                        SDL_UpdateWindowSurface(gWindow);

                    }
                }
            }  
        }
    }
    close();
    return 0;
}
    
