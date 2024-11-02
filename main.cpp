#include<iostream>
#include<SDL2/SDL.h>
//Global variables to initialise the height and width of the  window

const int WIDTH = 800, HEIGHT = 600;

SDL_Window * gWindow =NULL;
//image data type that holds the pixels of an image and renders it
SDL_Surface*  gScreenSurface = NULL;
SDL_Surface * gHelloWorld = NULL;

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

bool loadMedia()
{
    //flag to check if it loads or not
    bool success = true;
    gHelloWorld = SDL_LoadBMP("test.bmp");
    if(gHelloWorld == NULL)
    {
        std::cout<<"Unable to load image! SDL Error: "<<SDL_GetError()<<std::endl;
        success = false;
    }
    return success;
}

void close()
{
    //Deallocates stuff nd cleanup
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //destroy 
    SDL_DestroyWindow( gWindow);
    gWindow=NULL;
    SDL_Quit();
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
            SDL_BlitSurface(gHelloWorld,NULL,gScreenSurface,NULL);
            SDL_UpdateWindowSurface( gWindow );
            SDL_Event e;
            bool quit = false;
            while(!quit)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                        quit = true;
                }
            }  
        }
    }
    close();
    return 0;
}
    
