#include<math.h>
#include<iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define CV_EVENT_MOUSEMOVE 0             ·Æ°Ê
#define CV_EVENT_LBUTTONDOWN 1           ¥ªÁäÂIÀ»
#define CV_EVENT_RBUTTONDOWN 2           ¥kÁäÂIÀ»
#define CV_EVENT_MBUTTONDOWN 3           ¤¤ÁäÂIÀ»
#define CV_EVENT_LBUTTONUP 4             ¥ªÁä©ñ¶}
#define CV_EVENT_RBUTTONUP 5             ¥kÁä©ñ¶}
#define CV_EVENT_MBUTTONUP 6             ¤¤Áä©ñ¶}
#define CV_EVENT_LBUTTONDBLCLK 7         ¥ªÁäÂùÀ»
#define CV_EVENT_RBUTTONDBLCLK 8         ¥kÁäÂùÀ»
#define CV_EVENT_MBUTTONDBLCLK 9         ¤¤ÁäÂùÀ»
using namespace cv ;
using namespace std ;

typedef long long ll ;
double ballnum , width , height ;
Mat img(  900 , 900 , CV_8UC3, Scalar(255,255,255)  )  ;
Mat nxt(   900 ,  900 , CV_8UC3, Scalar(255,255,255)  )  ;
double cx = 450.0 , cy = 450.0 ;
double hwidth = 0.0 , hheight = 0.0 ;
double marginx = 0.0 , marginy =0.0 ;
struct ball
{
    double r , m , vx , vy , px , py ;
}balls[ 105 ] ;

void collide( ll a , ll b ) ;
ll resizew = 200 ;

int main( )
{
    cin>>ballnum>>width>>height  ;

    width *= 200 , height *= 200 ;
    if( height == 0.0 ) height = 320.0 ;
    hwidth = width / 2.0 , hheight = height / 2.0 ;
    for( ll i = 0 ; i < ballnum ; i++ )
    {
        cin>>balls[ i ].r>>balls[ i ].m>>balls[ i ].vx>>balls[ i ].vy>>balls[ i ].px>>balls[ i ].py ;
        balls[ i ].r *= resizew , balls[ i ].px *= resizew , balls[ i ].py *= resizew ;
        balls[ i ].vx *= 2.0 , balls[ i ].vy *= 2.0 ;
        if( balls[ i ].py == 0.0 ) balls[ i ].py =  450   ;
    }
    //balls[ 1 ].vx *= ( -1.0 ) ;
    width *= resizew , height *= resizew ;


    line( img , Point( cx - hwidth , cy - hheight ) , Point( cx + hwidth , cy - hheight ) , Scalar(0,0,255) , 2 ) ;
    line( img ,  Point(cx - hwidth , cy + hheight ) , Point( cx + hwidth , cy + hheight) , Scalar(0,0,255) ,  2 ) ;
    line( img , Point(cx - hwidth , cy - hheight) ,  Point(cx - hwidth , cy + hheight) , Scalar(0,0,255) , 2 ) ;
    line( img , Point(cx + hwidth , cy - hheight) , Point(cx + hwidth , cy + hheight) , Scalar(0,0,255) ,  2 ) ;
    circle(img, Point(cx - hwidth + balls[ 0 ].px , 450 + balls[ 0 ].py ), balls[ 0 ].r , Scalar(0,0,0), -1 );
    circle(img, Point(cx - hwidth + balls[ 1 ].px , 450 + balls[ 1 ].py ), balls[ 1 ].r , Scalar(0,0,0),-1 );

    namedWindow("WINDOW") ;
    imshow("WINDOW", img ) ;
    waitKey( 300 ) ;
    while( 1 )
    {

        collide( 0 , 1 ) ;
    }
    waitKey( 0 ) ;

    return 0 ;
}

double sid( double apx , double apy , double bpx , double bpy )
{
    double ans = 0.0 ;
    ans =   sqrt( pow( apx - bpx , 2  ) + pow( apy - bpy , 2  ) )   ;
    return ans ;
}

double dot( double ax ,  double ay , double bx , double by )
{
    double ans = 0.0 ;
    ans =  ax*bx + ay * by  ;
    return ans ;
}

void ball_col( struct ball &a , struct ball &b )
{
    double len = sid( a.px , a.py , b.px , b.py ) ;
    double normx = ( a.px - b.px ) / len ;
    double normy = ( a.py - b.py ) / len ;
    double vanorm = dot( a.vx , a.vy , normx , normy ) ;
    double vbnorm = dot( b.vx , b.vy , normx , normy ) ;
    double newva =  ( ( a.m - b.m )*vanorm + 2*b.m*vbnorm ) / ( a.m + b.m ) ;
    double newvb =   ( ( b.m - a.m )*vbnorm + 2*a.m*vanorm ) / ( a.m + b.m ) ;
    a.vx +=  ( newva - vanorm ) * normx ;
    a.vy +=  ( newva - vanorm ) * normy ;
    b.vx +=  ( newvb - vbnorm ) * normx ;
    b.vy += ( newvb - vbnorm ) * normy ;
}


void collide( ll a , ll b )
{
    if( abs( balls[ a ].py - balls[ b ].py ) < 1e-4 )
    {
        if( abs( balls[ a ].px - balls[ b ].px ) <= abs( balls[ a ].r + balls[ b ].r ) )//pow( balls[ a ].px - balls[ b ].px , 2  )  <= pow( balls[ a ].r + balls[ b ].r , 2 ) ) //abs( balls[ a ].px - balls[ b ].px ) <= abs( balls[ a ].r + balls[ b ].r ) )
        {
            balls[ 0 ].vx =  ( ( balls[ 0 ].m - balls[ 1 ].m )*balls[ 0 ].vx + 2*balls[ 1 ].vx*balls[ 1 ].m  ) /  (  balls[ 0 ].m + balls[ 1 ].m ) ;
            balls[ 1 ].vx = ( ( balls[ 1 ].m - balls[ 0 ].m )*balls[ 1 ].vx  + 2*balls[ 0 ].vx*balls[ 0 ].m  ) / (  balls[ 0 ].m + balls[ 1 ].m ) ;

            //cout<<balls[ 0 ].vx<<"||"<<balls[ 1 ].vx<<" " ;
            while(  abs( balls[ a ].px - balls[ b ].px ) <= abs( balls[ a ].r + balls[ b ].r ) )
            {
                balls[ 0 ].px  +=  balls[ 0 ].vx ;
                balls[ 0 ].py  +=  balls[ 0 ].vy ;
                balls[ 1 ].px  += balls[ 1 ].vx ;
                balls[ 1 ].py  += balls[ 1 ].vy ;
            }
        }
    }
    if( abs( balls[ a ].px - balls[ b ].px ) < 1e-4 )
    {
        if( abs( balls[ a ].py - balls[ b ].py ) <= abs( balls[ a ].r + balls[ b ].r ) ) //abs( balls[ a ].px - balls[ b ].px ) <= abs( balls[ a ].r + balls[ b ].r ) )
        {
            balls[ 0 ].vy =  ( ( balls[ 0 ].m - balls[ 1 ].m )*balls[ 0 ].vy + 2*balls[ 1 ].vy*balls[ 1 ].m  ) /  (  balls[ 0 ].m + balls[ 1 ].m ) ;
            balls[ 1 ].vy = ( ( balls[ 1 ].m - balls[ 0 ].m )*balls[ 1 ].vy  + 2*balls[ 0 ].vy*balls[ 0 ].m  ) / (  balls[ 0 ].m + balls[ 1 ].m ) ;

            //cout<<balls[ 0 ].vx<<"||"<<balls[ 1 ].vx<<" " ;
            while( abs( balls[ a ].py - balls[ b ].py ) <= abs( balls[ a ].r + balls[ b ].r ) )
            {
                balls[ 0 ].px  +=  balls[ 0 ].vx ;
                balls[ 0 ].py  +=  balls[ 0 ].vy ;
                balls[ 1 ].px  += balls[ 1 ].vx ;
                balls[ 1 ].py  += balls[ 1 ].vy ;
            }
        }
    }
    if( pow( balls[ a ].px - balls[ b ].px , 2  )  +  pow( balls[ a ].py - balls[ b ].py , 2  ) <= pow( balls[ a ].r + balls[ b ].r , 2 ) ) //abs( balls[ a ].px - balls[ b ].px ) <= abs( balls[ a ].r + balls[ b ].r ) )
    {

        ball_col( balls[ a ] , balls[ b ] ) ;
        cout<<balls[ 0 ].vx<<" "<<balls[ 0 ].vy<<"||"<<balls[ 1 ].vx<<" "<<balls[ 1 ].vy<<"\n" ;
        while( pow( balls[ a ].px - balls[ b ].px , 2  ) + pow( balls[ a ].py - balls[ b ].py , 2 ) <= pow( balls[ a ].r + balls[ b ].r , 2 ) )
        {
            balls[ 0 ].px  +=  balls[ 0 ].vx ;
            balls[ 0 ].py  +=  balls[ 0 ].vy ;
            balls[ 1 ].px  += balls[ 1 ].vx ;
            balls[ 1 ].py  += balls[ 1 ].vy ;
        }
    }

    if(  cx - hwidth + balls[ a ].px + balls[ a ].r >= cx + hwidth ||  cx - hwidth + balls[ a ].px -  balls[ a ].r  <= cx - hwidth )
    {
        balls[ a ].vx *= ( -1.0 ) ;
    }
    if( 450 + balls[ a ].py + balls[ a ].r >= cy + hheight   || 450 + balls[ a ].py - balls[ a ].r <= cy - hheight  )
    {
        balls[ a ].vy *= ( -1.0 ) ;
    }
    if( cx - hwidth + balls[ b ].px + balls[ b ].r >= cx + hwidth || cx - hwidth +  balls[ b ].px -  balls[ b ].r <= cx - hwidth  )
    {
        balls[ b ].vx *= ( -1.0 ) ;
    }
     if( 450 + balls[ b ].py + balls[ b ].r >= cy + hheight || 450 +balls[ b ].py - balls[ b ].r <= cy - hheight  )
    {
        balls[ b ].vy *= ( -1.0 ) ;
    }
    balls[ 0 ].px  +=  balls[ 0 ].vx ;
    balls[ 0 ].py  +=  balls[ 0 ].vy ;
    balls[ 1 ].px  += balls[ 1 ].vx ;
    balls[ 1 ].py  += balls[ 1 ].vy ;
    nxt.copyTo( img );

    line( img , Point( cx - hwidth , cy - hheight ) , Point( cx + hwidth , cy - hheight ) , Scalar(0,0,255) , 2 ) ;
    line( img ,  Point(cx - hwidth , cy + hheight ) , Point( cx + hwidth , cy + hheight) , Scalar(0,0,255) ,  2 ) ;
    line( img , Point(cx - hwidth , cy - hheight) ,  Point(cx - hwidth , cy + hheight) , Scalar(0,0,255) , 2 ) ;
    line( img , Point(cx + hwidth , cy - hheight) , Point(cx + hwidth , cy + hheight) , Scalar(0,0,255) ,  2 ) ;
    circle(img, Point(cx - hwidth + balls[ 0 ].px , 450  +balls[ 0 ].py), balls[ 0 ].r , Scalar(0,0,0), -1 );
    circle(img, Point(cx - hwidth + balls[ 1 ].px ,  450 +balls[ 1 ].py), balls[ 1 ].r , Scalar(0,0,0), -1 );


    imshow("WINDOW", img ) ;
    waitKey( 15 ) ;

}
