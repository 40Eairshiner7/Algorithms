(y2-y0)*(x1-x0)-(y1-y0)*(x2-x0)=0
(y4-y0)*(x3-x0)-(y3-y0)*(x4-x0)=0


=>  (y1-y2)x0+(x2-x1)y0+x1y2-x2y1=0
=>  (y3-y4)x0+(x4-x3)y0+x3y4-x4y3=0


a1=y1-y2  b1=x2-x1  c1=x1y2-x2y1
a2=y3-y4  b2=x4-x3  c2=x3y4-x4y3


=>  x=(c1*b2-c2*b1)/(a2*b1-a1*b2);
=>  y=(a2*c1-a1*c2)/(a1*b2-a2*b1);


double cross(point a,point b,point c,point d) {
	return (a.y-b.y)*(c.x-d.x)-(a.x-b.x)*(c.y-d.y);
}


double a1=p[0].y-p[1].y, b1=p[1].x-p[0].x, c1=p[0].x*p[1].y-p[1].x*p[0].y;
double a2=p[2].y-p[3].y, b2=p[3].x-p[2].x, c2=p[2].x*p[3].y-p[3].x*p[2].y;
double x=(c1*b2-c2*b1)/(a2*b1-a1*b2);
double y=(a2*c1-a1*c2)/(a1*b2-a2*b1);