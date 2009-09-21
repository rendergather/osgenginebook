/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * How to embed the viewer with Win32 API window
*/

#include <windows.h>
#include <process.h>
#include <osgViewer/Viewer>
#include <osgViewer/api/win32/GraphicsWindowWin32>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

osg::ref_ptr<osgViewer::Viewer> g_viewer;
bool g_finished;

void render( void* )
{
    while ( !g_viewer->done() )
        g_viewer->frame();
    g_finished = true;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch ( message )
    {
        case WM_CREATE:
        {
            osg::ref_ptr<osg::Referenced> windata =
                new osgViewer::GraphicsWindowWin32::WindowData( hwnd );
            
            osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
            traits->x = 0;
            traits->y = 0;
            traits->width = 800;
            traits->height = 600;
            traits->windowDecoration = false;
            traits->doubleBuffer = true;
            traits->inheritedWindowData = windata;
            
            osg::ref_ptr<osg::GraphicsContext> gc =
                osg::GraphicsContext::createGraphicsContext( traits.get() );
            
            osg::ref_ptr<osg::Camera> camera = new osg::Camera;
            camera->setGraphicsContext( gc );
            camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
            
            g_viewer = new osgViewer::Viewer;
            g_viewer->addSlave( camera.get() );
            g_viewer->setSceneData( osgDB::readNodeFile("cessna.osg") );
            g_viewer->setCameraManipulator( new osgGA::TrackballManipulator );
            g_viewer->setThreadingModel( osgViewer::Viewer::SingleThreaded );
            
            g_finished = false;
            _beginthread( render, 0, NULL );
            return 0;
        }
        case WM_DESTROY:
            g_viewer->setDone( true );
            while ( !g_finished ) Sleep(10);
            PostQuitMessage( 0 );
            return 0;
        default:
            break;
    }
    return DefWindowProc( hwnd, message, wParam, lParam );
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow )
{
    static TCHAR szAppName[] = TEXT("gui");
    
    WNDCLASS wndclass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    if ( !RegisterClass(&wndclass) )
        return 0;
    
    HWND hwnd = CreateWindow( szAppName, // window class name
                              TEXT ("OSG and Win32 API Window"), // window caption
                              WS_OVERLAPPEDWINDOW, // window style
                              100, // initial x position
                              100, // initial y position
                              800, // initial x size
                              600, // initial y size
                              NULL, // parent window handle
                              NULL, // window menu handle
                              hInstance, // program instance handle
                              NULL ); // creation parameters
    ShowWindow( hwnd, iCmdShow );
    UpdateWindow( hwnd );
    
    MSG msg;
    while ( GetMessage(&msg, NULL, 0, 0) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
    return (int)msg.wParam;
}
