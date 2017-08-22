#bouding box of pixel rect leftup(x1,y1) btdown(x2,y2) center(mx,my) w=x2-x1+1
int32 x1
int32 y1
int32 x2
int32 y2
int32 mx
int32 my
int32 w
int32 h
#bounding box of pointcloud leftup(fx1,fy1,fz1) btdown(fx2,fy2,fz2) center(cx,cy,cz)
float32 fx1
float32 fy1
float32 fz1
float32 fx2
float32 fy2
float32 fz2
float32 sx
float32 sy
float32 sz
float32 cx
float32 cy
float32 cz
float32 object_height
float32 object_width
#if rect are rotated,then its Rotation angle is rr_rot(radian),real center is (rr_cx,rr_cy,cz)
#real length is 2*rr_ly, real width is 2*rr_lx.  rr_z1 = fz1 rr_z2 = fz2
int32 rr_valid
float32 rr_rot
float32 rr_cx
float32 rr_cy
float32 rr_lx
float32 rr_ly 
float32 rr_z1
float32 rr_z2
