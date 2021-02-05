def f01(x,y,x0,y0,x1,y1,x2,y2):
	return x * (y0-y1) + y * (x1-x0) + (x0*y1) - (y0*x1)
def f12(x,y,x0,y0,x1,y1,x2,y2):
	return x * (y1-y2) + y * (x2-x1) + (x1*y2) - (y1*x2)
def f20(x,y,x0,y0,x1,y1,x2,y2):
	return x * (y2-y0) + y * (x0-x2) + (x2*y0) - (y2*x0)


def mainf(x,y,x0,y0,x1,y1,x2,y2,c0x,c0y,c0z,c1x,c1y,c1z,c2x,c2y,c2z):
	alfa = f12(x,y,x0,y0,x1,y1,x2,y2)/float(f12(x0,y0,x0,y0,x1,y1,x2,y2))
	beta = f20(x,y,x0,y0,x1,y1,x2,y2)/float(f20(x1,y1,x0,y0,x1,y1,x2,y2))
	gama = f01(x,y,x0,y0,x1,y1,x2,y2)/float(f01(x2,y2,x0,y0,x1,y1,x2,y2))
	cx = alfa* (c0x+c1x+c2x)
	cy = beta* (c0y+c1y+c2y)
	cz = gama* (c0z+c1z+c2z)

	c = (cx , cy , cz)
	return c

#print(mainf(18,22,10,20,30,10,20,30,255,0,0 ,0,255,0 ,0,0,255))

def f(t):
	print t**3,t**2,t,1
f(0)
f(0.2262)
f(0.8816)
f(1)