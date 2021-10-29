#include<stdio.h>
#include<conio.h>
#include<math.h>
#define size 100
int main() {
    int dimx,dimy;
    printf("controls : c control cursor with wasd\n");
    printf("q : start point\n");
    printf("e : end point\n");
    printf("x : change mode to create or delete obstacles\n");
    printf("f : finish path\n");
    printf("press a key to continue\n");
    getch();
    printf("enter size of matrix\n");
    scanf("%d %d",&dimx,&dimy);
    int a[size][size];
    //start coordinates
    int sx=-1,sy=-1;
    int ex=-1,ey=-1;
    int i,j;
    for(i=0; i<dimx; i++) {
        for(j=0; j<dimy; j++) {
            a[i][j]=0;
        }
    }
    int finish=0;
    int cx=0,cy=0;
    char way;
    int state=0;
    while(finish==0) {
        if(kbhit()) {
            way=getch();
            if(way=='a' && cy>0) {
                cy-=1;
            }
            if(way=='w'&& cx>0) {
                cx-=1;
            }
            if(way=='s' && cx<dimx-1) {
                cx+=1;
            }
            if(way=='d' && cy<dimy-1) {
                cy+=1;
            }
            if(way=='q') {
                sx=cx;
                sy=cy;
            }
            if(way=='e') {
                ex=cx;
                ey=cy;
            }
            if(way=='x') {
                state+=1;
            }
            if(state>2) {
                state=0;
            }
            if(state==1) {
                a[cx][cy]=-1;
            }
            if(state==2) {
                a[cx][cy]=0;
            }
            if(way=='f') {
                finish=1;
            }

            system("cls");
            for(i=0; i<dimx; i++) {
                for(j=0; j<dimy; j++) {
                    if(i==sx && j==sy) {
                        printf(" S");
                    }
                    else if(i==ex && j==ey) {
                        printf(" E");
                    }
                    else if(i==cx && j==cy) {
                        printf(" C");
                    }
                    else if(a[i][j]>=0) {
                        printf(" .");
                    }
                    else if(a[i][j]==-1) {
                        printf("[]");
                    }
                }
                printf("\n");
            }
        }
    }
    char eight='n';
    printf("Do you want to activate 8 way movement?\n");
    printf("y  or  n\n");
    eight=getch();

    int search=1;
    int b[size][size];
    for(i=0; i<dimx; i++) {
        for(j=0; j<dimy; j++) {
            b[i][j]=a[i][j];
        }
    }
    /////////////////////////////////////////////////
    if(a[sx-1][sy]==0 && sx>0) {
        a[sx-1][sy]=1;
    }
    if(a[sx+1][sy]==0 && sx<dimx) {
        a[sx+1][sy]=1;
    }
    if(a[sx][sy-1]==0 && sy>0) {
        a[sx][sy-1]=1;
    }
    if(a[sx][sy+1]==0 && sy<dimy) {
        a[sx][sy+1]=1;
    }
    if(eight=='y'){
    	if(a[sx-1][sy-1]==0 && sx>0 && sy>0) {
     	   a[sx-1][sy-1]=1;
   		}
    	if(a[sx+1][sy-1]==0 && sx<dimx && sy>0) {
        	a[sx+1][sy-1]=1;
    	}
    	if(a[sx+1][sy+1]==0 && sy<dimy && sx<dimx) {
    	    a[sx+1][sy+1]=1;
    	}
    	if(a[sx-1][sy+1]==0 && sy<dimy && sx>0) {
        	a[sx-1][sy+1]=1;
    	}	
	}
    //////////////////////////////////////////////////
    int count=0;
    while(a[ex][ey]==0 && count<(dimx*dimy)) {
        for(i=0; i<dimx; i++) {
            for(j=0; j<dimy; j++) {
                if(a[i][j]==search) {
                    if(a[i-1][j]==0 && i>0) {
                        a[i-1][j]=search+1;
                    }
                    if(a[i+1][j]==0 && i<dimx) {
                        a[i+1][j]=search+1;
                    }
                    if(a[i][j-1]==0 && j>0) {
                        a[i][j-1]=search+1;
                    }
                    if(a[i][j+1]==0 && j<dimy) {
                        a[i][j+1]=search+1;
                    }
                    if(eight=='y'){
                    	if(a[i-1][j-1]==0 && i>0 && j>0) {
                        	a[i-1][j-1]=search+1;
                   		}
                    	if(a[i+1][j-1]==0 && i<dimx && j>0) {
                    	    a[i+1][j-1]=search+1;
                    	}
                    	if(a[i-1][j+1]==0 && j<dimy && i>0) {
                        	a[i-1][j+1]=search+1;
                    	}
                    	if(a[i+1][j+1]==0 && j<dimy && i<dimx) {
                        	a[i+1][j+1]=search+1;
                    	}	
					}
                }
            }
        }
        search+=1;
        count+=1;
    }
    float dist,mindist;
    int px=ex,py=ex;
    int e1x=ex,e1y=ey;
    int cost;
    if(count<(dimx*dimy)) {
        search-=1;
        a[sx][sy]=0;
        int found;
        while(search>0) {
        	mindist=1000000;
            for(i=ex-1;i<=ex+1;i++){
            	for(j=ey-1;j<=ey+1;j++){
            		if(a[i][j]==search){
            			cost=(abs(ex-i))+(abs(ey-j));
            			dist=(sx-i)*(sx-i)+(sy-j)*(sy-j);
            			dist=sqrt(dist);
            			if(dist+cost<mindist){
            				mindist=dist+cost;
            				px=i;
            				py=j;
						}
					}
				}
			}
			b[px][py]=search;
			search-=1;
			ex=px;
			ey=py;
        }
        system("cls");
        for(i=0; i<dimx; i++) {
            for(j=0; j<dimy; j++) {
				if(i==sx && j==sy){
					printf(" S");
	            }else if(i==e1x && j==e1y){
	            	printf(" E");
				}else if(b[i][j]==0) {
                    printf(" .");
                }
                else if(b[i][j]>0) {
                    printf("%2d",b[i][j]);
                }
                else if(b[i][j]==-1) {
                    printf("[]");
                }
            }
            printf("\n");
        }
    } else {
        printf("path couldn't found\n");
    }
    char replay;
    printf("do you want to play again?\n");
    printf("y or n\n");
    replay=getchar();
    if(replay=='y'){
    	main();
	}else{
		return 0;
	}
}
