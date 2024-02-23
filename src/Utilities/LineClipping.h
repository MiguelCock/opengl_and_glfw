//Cohen Sutherland boundaries
#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

const double XMIN = 160;
const double XMAX = 480;
const double YMIN = 120;
const double YMAX = 360;

int ComputeOutCode(double x, double y)
{
	int code = INSIDE;

	if (x < XMIN) code |= LEFT;         // to the left of clip window
	else if (x > XMAX) code |= RIGHT;   // to the right of clip window
	if (y < YMIN) code |= BOTTOM;       // below the clip window
	else if (y > YMAX) code |= TOP;     // above the clip window

	return code;
}

bool CohenSutherlandLineClip(double* x0, double* y0, double* x1, double* y1){
	int outcode0 = ComputeOutCode(*x0, *y0);
	int outcode1 = ComputeOutCode(*x1, *y1);
	bool accept = false;

	while (true) {
		if (!(outcode0 | outcode1)) {
			accept = true;
			break;
		} else if (outcode0 & outcode1) {
			break;
		} else {

			double x, y;

			int outcodeOut = outcode1 > outcode0 ? outcode1 : outcode0;

			if (outcodeOut & TOP) {
				x = *x0 + (*x1 - *x0) * (YMAX - *y0) / (*y1 - *y0);
				y = YMAX;
			} else if (outcodeOut & BOTTOM) {
				x = *x0 + (*x1 - *x0) * (YMIN - *y0) / (*y1 - *y0);
				y = YMIN;
			} else if (outcodeOut & RIGHT) { 
				y = *y0 + (*y1 - *y0) * (XMAX - *x0) / (*x1 - *x0);
				x = XMAX;
			} else if (outcodeOut & LEFT) {
				y = *y0 + (*y1 - *y0) * (XMIN - *x0) / (*x1 - *x0);
				x = XMIN;
			}

			if (outcodeOut == outcode0) {
				*x0 = x;
				*y0 = y;
				outcode0 = ComputeOutCode(*x0, *y0);
			} else {
				*x1 = x;
				*y1 = y;
				outcode1 = ComputeOutCode(*x1, *y1);
			}
		}
	}
	return accept;
}