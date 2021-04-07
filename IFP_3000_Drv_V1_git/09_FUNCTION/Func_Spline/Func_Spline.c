/**********************************************************
** Si(Xi)=ai*(X-Xi)^3+bi*(X-Xi)^2+ci*(X-Xi)+di
** 三次样条插值函数
** 进行自然边界，夹持边界，非扭结边界条件下的插值
** 
**  将函数从原来的需要至少4个插值点才能计算
**            扩展成只需要2个插值点就可以完成计算
**            其他一些改变
**  创建函数
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Func_Spline.h"

/* 三次样条求浓度 */
uint8_t pstuAlforithmSpline( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum )
{
	POINT p;
	COEFFICIENT *pCoefficient;
	double x[15]={0};
	double y[15]={0};
	double X1=0,X2=0,X3=0;
	double X123[3] = {0};
//	int n = 0;
	int i,j=0;
	int iCurve = 0;
	int iRecErr = 0;
	
//	double doutesta = 0;
//	double doutestb = 0;
	float fTempResult = 0;
	
#if DEBUH_UART1	
	myprintf( "Spline \r\n" );
#endif
	
	if( 0==fPesponse ){                        /* x在四参数中不能为0 */
		fPesponse = 0.01;
	}
	
	for( i=0;i<15;i++ ){
		if( (0!=pstuIdInfo->children_pesponse[i])||(0!=pstuIdInfo->children_density[i]) ){
//			x[j] = pstuIdInfo->children_pesponse[i];
//			y[j] = pstuIdInfo->children_density[i];
			x[j] = pstuIdInfo->children_density[i];
			y[j] = pstuIdInfo->children_pesponse[i];
			j++;
		}
	}
	
	pCoefficient = (COEFFICIENT *)malloc((j-1) * sizeof(COEFFICIENT));
	if (NULL == pCoefficient){
		return EXE_FAILED;
	}
	
	p.coe = pCoefficient;
	p.xCoordinate = x;
	p.yCoordinate = y;
	/* 下面两个参数f0和fn只在夹持条件下有效，其他条件下这两个值会被忽略 */
	p.f0 = 0;// 在夹持条件下的左边点的导数值
	p.fn = 0;// 在夹持条件下的右边点的导数值
	p.num = j;	
	p.con = NATURAL;
	
	/* 三次样条系数计算 */
#if 1
	splineA(&p);
#else
	splineB(&p);
#endif
//	iSplineDisCoe(pCoefficient, j);
//	fPesponse = 49;
	iCurve = iGetCurve(y, j, (double)fPesponse);
	
	/* 三次样条求浓度 */
	//fTempResult = (float)(((pCoefficient + iCurve)->a3)*pow((fPesponse - x[iCurve]), 3) + ((pCoefficient + iCurve)->b2)*pow((fPesponse - x[iCurve]), 2) + ((pCoefficient + iCurve)->c1)*(fPesponse - x[iCurve]) + ((pCoefficient + iCurve)->d0));
	iRecErr = UnivariateCubiceQuationShengjin( ((pCoefficient + iCurve)->a3), ((pCoefficient + iCurve)->b2), ((pCoefficient + iCurve)->c1), (((pCoefficient + iCurve)->d0) - fPesponse),&X1,&X2,&X3 );
	//iRecErr = UnivariateCubiceQuationShengjinA( ((pCoefficient + iCurve)->a3), ((pCoefficient + iCurve)->b2), ((pCoefficient + iCurve)->c1), (((pCoefficient + iCurve)->d0) - fPesponse),&X1,&X2,&X3 );
	if( EXE_SUCCEED<iRecErr ){		
		X123[0] = x[iCurve] + X1;		
		X123[1] = x[iCurve] + X2;
		X123[2] = x[iCurve] + X3;
		
#if STORT_STL
		qsort( (void *)X123, (sizeof(X123)/sizeof(double)), sizeof(double), cmpfuncintdoublemin);  /*排序函数*/
#else
		InsertionSortDouble( (double *)X123,(sizeof(X123)/sizeof(double)),SORT_MIN );
#endif
		
#if DEBUH_UART1		
		myprintf( "X1:%.2f X2:%.2f X3:%.2f \r\n",x[iCurve] + X1,x[iCurve] + X2,x[iCurve] + X3 );		
#endif
		if( j-2==iCurve ){
			if( (y[iCurve+1]<fPesponse) ){
				if( (x[iCurve+1]<X123[0]) ){		
					fTempResult = X123[0];	
				}else if( (x[iCurve+1]<X123[1]) ){
					fTempResult = X123[1];	
				}else if( (x[iCurve+1]<X123[2]) ){
					fTempResult = X123[2];	
				}else{
					//fTempResult = x[iCurve+1];
					//进入直线阶段 
					fTempResult = fResultLineEqu( x[iCurve],y[iCurve],x[iCurve+1],y[iCurve+1],fPesponse );
					if( !(fTempResult>ZERO) ){
						fTempResult = 0.01;
					}
				}
			}else{
				if( fabs(y[iCurve]-fPesponse)<ZERO ){
					fTempResult = x[iCurve];
				}else{
					if( (x[iCurve]<X123[0]) ){		
						fTempResult = X123[0];	
					}else if( (x[iCurve]<X123[1]) ){
						fTempResult = X123[1];	
					}else if( (x[iCurve]<X123[2]) ){
						fTempResult = X123[2];	
					}else{
						fTempResult = fResultLineEqu( x[iCurve],y[iCurve],x[iCurve+1],y[iCurve+1],fPesponse );
						if( !(fTempResult>ZERO) ){
							fTempResult = 0.01;
						}
					}
				}
			}
		}else if( 0!=x[iCurve+1] ){
			if( fabs(y[iCurve]-fPesponse)<ZERO ){
				fTempResult = x[iCurve];
			}else if( (y[iCurve]<fPesponse) ){
				if( (x[iCurve]<X123[0]) ){		
					fTempResult = X123[0];	
				}else if( (x[iCurve]<X123[1]) ){
					fTempResult = X123[1];	
				}else if( (x[iCurve]<X123[2]) ){
					fTempResult = X123[2];	
				}else{
					fTempResult = fResultLineEqu( x[iCurve],y[iCurve],x[iCurve+1],y[iCurve+1],fPesponse );
					if( !(fTempResult>ZERO) ){
						fTempResult = 0.01;
					}
				}
			}else{
				if( (x[iCurve]>X123[2])&&(X123[2]>ZERO) ){		
					fTempResult = X123[2];	
				}else if( (x[iCurve]>X123[1])&&(X123[1]>ZERO) ){
					fTempResult = X123[1];	
				}else if( (x[iCurve]>X123[0])&&(X123[0]>ZERO) ){
					fTempResult = X123[0];	
				}else{
					fTempResult = fResultLineEqu( x[iCurve],y[iCurve],x[iCurve+1],y[iCurve+1],fPesponse );
					if( !(fTempResult>ZERO) ){
						fTempResult = 0.01;
					}
				}
			}
		}else{
			fTempResult = 0.01;
		}
		
		if( 0!=fTempResult ){
			fTempResult = fChildrenCoefficient( pstuIdInfo,fTempResult );               /* 样本系数求解 */	
			pstuAlforithmResult( pstuAlg,uChildrenNum,fTempResult );			        /* 将结果放到对应的项目中 */
		}	
	}
	
	if( pCoefficient ){
		free(pCoefficient);
	}
			
	return EXE_SUCCEED;
}

int UnivariateCubiceQuationShengjin(double a3, double b2, double c1, double d0, double *x1, double *x2, double *x3)
{
	double A = 0, B = 0, C = 0, ABC = 0;

	if (0 == (a3)){
		return EXE_SPECIAL_FAILED;
	}

	A = pow(fabs(b2), 2.0) - (3.0 * (a3)*(c1));
	B = (b2)*(c1) - (9.0 * (a3)*(d0));
	C = pow(fabs(c1), 2.0) - (3.0 * (b2)*(d0));
	ABC = pow(fabs(B), 2.0) - (4.0 * (A)*(C));

	if ((fabs(A)<ZERO) && (fabs(B)<ZERO)){
		if( !ISZERO(a3) ){
			*x1 = -1.0*(b2/(3.0*a3));
			*x2 = *x1;
			*x3 = *x1;
		}
		if( !ISZERO(b2) ){
			*x1 = -1.0*(c1 / b2);	
			*x2 = *x1;
			*x3 = *x1;
		}
		if( !ISZERO(c1) ){
			*x1 = -1.0*(d0 / c1);	
			*x2 = *x1;
			*x3 = *x1;
		}
		return ONE_SOLUTION;
	}
	else if (ZERO > fabs(ABC)){
		double K;
		
		if (ISZERO(A)){
			return EXE_SPECIAL_FAILED;
		}
		K = B / A;
		*x1 = (-1.0*(b2 / a3)) + K;
		*x2 = -1.0*(K / 2.0);
		*x3 = -1.0*(K / 2.0);
		
		return TWO_SOLUTION;
	}
	else if (ZERO < ABC){
		double Y1=0, Y2=0;
		double RY1=0, RY2=0;
		
#if COMPLEX_SLUTION		
		COMPLEX cX2;	
		COMPLEX cX3;
#endif
		Y1 = A*(b2) + 3.0 * (a3)*(((-B + pow(fabs(ABC), (double)(1.0 / 2.0))) / 2.0));
		Y2 = A*(b2) + 3.0 * (a3)*(((-B - pow(fabs(ABC), (double)(1.0 / 2.0))) / 2.0));
	
		RY1 = (Y1 / fabs(Y1))*pow(fabs(Y1), (double)(1.0 / 3.0));		
		RY2 = (Y2 / fabs(Y2))*pow(fabs(Y2), (double)(1.0 / 3.0));	

		*x1 = (-1.0*(b2 + RY1 + RY2))/(3.0 * a3);
		*x2 = 0;
		*x3 = 0;
#if COMPLEX_SLUTION
		//*x2 = (-(b2)+(1.0 / 2.0)*(RY1 + RY2) + (pow(3, 1.0 / 2.0) / 2 * (RY1 - RY2))) / 3 * (a3);      /* 共轭复数根 */
		//*x3 = (-(b2)+(1.0 / 2.0)*(RY1 + RY2) - (pow(3, 1.0 / 2.0) / 2 * (RY1 - RY2))) / 3 * (a3);
		cX2.real = (1.0 / (6.0 * a3)) * (-2.0 * b2 + RY1 + RY2);
		cX2.image = (1.0 / (6.0 * a3)) * sqrtf(3.0) * (RY1 - RY2);
		cX3.real = cX2.real;
		cX3.image = -1.0f * cX2.image;
#endif		
		return THR_SOLUTION;
	}
	else if (ZERO > ABC){
		double r = 0;
		double T = 0;
		
		T = (2.0 * A*(b2) - 3.0 * (a3)*B) / (2.0*A*pow(fabs(A), 1.0 / 2.0));

		r = acos(T);

		*x1 = (-1.0*(b2) - 2.0 * pow(fabs(A), 1.0 / 2.0)*cos(r / 3.0)) / (3.0 * (a3));  //
		*x2 = (-1.0*(b2) + pow(fabs(A), 1.0 / 2.0)*(cos(r / 3.0) + pow(3, 1.0 / 2.0)*sin(r / 3.0))) / (3.0 * (a3));  //
		*x3 = (-1.0*(b2) + pow(fabs(A), 1.0 / 2.0)*(cos(r / 3.0) - pow(3, 1.0 / 2.0)*sin(r / 3.0))) / (3.0 * (a3));  //
		
		return THR_SOLUTION;
	}
	else{
		return EXE_SPECIAL_FAILED;
	}
}

int UnivariateCubiceQuationShengjinA(RealNum rA, RealNum rB, RealNum rC, RealNum rD, RealNum* rX1, RealNum* rX2, RealNum* rX3)
{
	RealNum fDA = rB * rB - 3.0f * rA * rC;
	RealNum fDB = rB * rC - 9.0f * rA * rD;
	RealNum fDC = rC * rC - 3.0f * rB * rD;

	RealNum rTempA = ABSZERO;
	RealNum rTempB = ABSZERO;
	RealNum fDelta = fDB * fDB - 4.0f * fDA * fDC;
	if ((ISZERO(fDA) && ISZERO(fDB)))
	{
		if (!ISZERO(rA))
		{
			*rX1 = -1.0f * rB / (3.0f * rA);
		}
		else if (!ISZERO(rB))
		{
			*rX1 = -1.0f * rC / rB;
		}
		else if (!ISZERO(rC))
		{
			*rX1 = -1.0f * rD / rC;
		}
		else// if (!ISZERO(rD))
		{
			return 0;
		}
		*rX2 = *rX1;
		*rX3 = *rX1;
		return 1;
	}

	if (GREATERTHANZERO(fDelta))
	{
#if COMPLEX_SLUTION
		COMPLEX cX2;
		COMPLEX cX3;
#endif

		RealNum rY1 = fDA * rB + 3.0 * rA * (0.5f * (-1.0 * fDB + sqrt(fDelta)));
		RealNum rY2 = fDA * rB + 3.0 * rA * (0.5f * (-1.0 * fDB - sqrt(fDelta)));
		if (GREATERTHANZERO(rY1))
		{
			rTempA = pow(rY1, 1.0 / 3.0);
		}
		else
		{
			rTempA = -1.0 * pow(-1.0 * rY1, 1.0 / 3.0);
		}
		if (GREATERTHANZERO(rY2))
		{
			rTempB = pow(rY2, 1.0 / 3.0);
		}
		else
		{
			rTempB = -1.0 * pow(-1.0 * rY2, 1.0 / 3.0);
		}
		
		*rX1 = -1.0 * (rB + rTempA + rTempB) * (1.0 / (3.0 * rA));
		*rX2 = 0;
		*rX3 = 0;
#if COMPLEX_SLUTION	
		cX2.real = (1.0 / (6.0 * rA)) * (-2.0 * rB + rTempA + rTempB);
		cX2.image = (1.0 / (6.0 * rA)) * sqrtf(3.0) * (rTempA - rTempB);
		cX3.real = cX2.real;
		cX3.image = -1.0f * cX2.image;
#endif
		return 1;
	}
	else if (ISZERO(fDelta))
	{
		RealNum rK;
		if (ISZERO(fDA))
		{
			return 0;
		}
		
		rK = fDB / fDA;
		*rX1 = -1.0 * rB / rA + rK;
		*rX2 = -0.5 * rK;
		*rX3 = *rX2;
		return 2;
	}
	else
	{
		RealNum rT;
		RealNum rTheta;
		
		if (LESSTHANZERO(fDA))
		{
			return 0;
		}
		if (GREATERTHANZERO(fDA))
		{
			rTempA = pow(fDA, 3.0);
		}
		else
		{
			rTempA = -1.0 * pow(-1.0f * fDA, 3.0);
		}
		rT = (2.0 * fDA * rB - 3.0 * rA * fDB) / (2.0 * sqrt(rTempA));
		if ( !ISBETWEEN(rT, -1.0, 1.0) )
		{
			return 0;
		}
		rTheta = acos(rT);
		*rX1 = -1.0f * (rB + 2.0 * sqrt(fDA) * cos(rTheta / 3.0)) * (1.0f / (3.0f * rA));
		*rX2 = (-1.0f * rB + sqrt(fDA) * (cos(rTheta / 3.0) + sqrt(3.0) * sin(rTheta / 3.0))) * (1.0 / (3.0 * rA));
		*rX3 = (-1.0f * rB + sqrt(fDA) * (cos(rTheta / 3.0) - sqrt(3.0) * sin(rTheta / 3.0))) * (1.0 / (3.0 * rA));
		return 3;
	}
}

double UnivariateCubiceQuationSolute(double a, double b, double c, double d, double num)
{
	double x, x0, f, f1;
	int cnt = 0;

	x = num;

	do{
		x0 = x;
		f = ((a*x0 + b)*x0 + c)*x0 + d;
		f1 = (3 * a*x0 + 2 * b)*x0 + c;
		x = x0 - f / f1;
		cnt++;
	} while ((fabs(x - x0) > 1e-6)&&(cnt<ITERATIONS));

//	printf("the value is %.14f %d\r\n", x, cnt );

	if( cnt>=ITERATIONS ){
		return 0.01;
	}else{
		return x;
	}
}

/* The tridiagonal matrix algorithm (TDMA) 高斯消元 */
/*
求解如下多项式的解
b[0]m[0] + c[0]m[1] = x[0]
a[1]m[1] + b[1]m[2] + c[1]m[3] = x[1]
a[2]m[2] + b[2]m[3] + c[2]m[4] = x[2]
.
.
.
a[n-3]m[n-4] + b[n-3]m[n-3] + c[n-3]m[n-2] = x[n-3]
a[n-2]m[n-3] + b[n-2]m[n-2] + c[n-2]m[n-1] = x[n-2]
a[n-1]m[n-2] + b[n-1]m[n-1] = x[n-1]
x[] : 输入时为等式结果
N   : 输入等式个数 必须N=sizeof(x[])-1
a[] : 输入a[i]系数
b[] : 输入b[i]系数
c[] : 输入c[i]系数
|b[i]| > |a[i]| + |c[i]|
*/
int tdma(double x[], const unsigned int N, const double a[], const double b[], double c[])
{
	unsigned int n;
	double m;

	if ( (ABSOLUTE(b[1]) <= ABSOLUTE(a[1]) + ABSOLUTE(c[1]))||(N<2)){
		return -1;
	}

	/* b[0]*x1+c[0]*x2=x[0] x1+(c[0]/b[0])*x2=x[0]/b[0] */
	c[0] = c[0] / b[0];    /* c0' */
	x[0] = x[0] / b[0];    /* x0' */

	/* 经过此循环后c0~c(n-1) 变为c0’~c(n-1)' x0~x(n-1) 变为x0’~x(n-1)' */
	for (n = 1; n < N; n++) {                      /* 数学公式推导所得 c1'~cn'导数值 d1'~dn'导数值 */
		m = 1.0f / (b[n] - a[n] * c[n - 1]);       /* 1/(bi-(c(i-1)'*ai)) */
		c[n] = c[n] * m;                           /* ci/(bi-(c(i-1)'*ai)) */
		x[n] = (x[n] - a[n] * x[n - 1]) * m;       /* (xi-(x(i-1)'*ai))/(bi-(c(i-1)'*ai)) */
	}

	/* 经过此函数后 x0~x(n-1)变为m0~m(n-1)的解 */
	for (n = N - 1; n-- > 0;){                    /* 逆序求出m[i] m[i] = x[i-1]'-c[i]'x[i+1] */
		x[n] = x[n] - c[n] * x[n + 1];
	}

	/* 此函数返回的解在x[i]中 x[]在此函数中有三层含义 第一次含义为x[i]输入结果值
	第二次含义为存储x[i]'的导数 第三次含义为存储得到的m[i]的解  */
	return 0;
}

/*
** 资源不足时函数返回 -1
** 插值点数小于2时，函数返回 -2
** 计算正确完成函数返回插值点的数量 n
*/
int splineA(POINT *point)
{
    double *x = (*point).xCoordinate, *y = (*point).yCoordinate;
    int n = (*point).num - 1;          /* 循环上限 */
    int i;                             /* 循环辅助变量 */
	COEFFICIENT *coe = (*point).coe;   /* 存储a3 b2 c1 d0 */
	CONDITION con = (*point).con;      /* 选择边界条件 */
    double *h, *d;                     /* h:为步长 d为微分 */
    double *a, *b, *c, *f, *m;         /* a b c 为方程系数 f 为方程结果 m为待求未知数(二次微分值)*/
    double temp;

    if (n < 1) {
		return -2;
	}

    h = (double *)malloc( (6 * n + 4) * sizeof(double) ); /* 0,       1,...,(n-1)          */
    if (h == NULL) {
		return -1;
	}
    d = h + n;                                            /* 0,       1,...,(n-1)          */
    a = d + n;                                            /* 特别使用,1,...,(n-1),       n */
    b = a + (n + 1);                                      /*        0,1,...,(n-1),       n */
    c = b + (n + 1);                                      /*        0,1,...,(n-1),特别使用 */
    f = c + (n + 1);                                      /*        0,1,...,(n-1),       n */
    m = b;

    /* 计算 h[] d[] */
    for (i = 0; i < n; i++)
    {
        h[i] = x[i + 1] - x[i];                          /* 存储步长及差值 */
        d[i] = (y[i + 1] - y[i]) / h[i];                 /* 存储微分 */
        /* printf("%f\t%f\n", h[i], d[i]); */
    }
    /**********************
    ** 初始化系数增广矩阵
    **********************/
    a[0] = (*point).f0;
    c[n] = (*point).fn;
    /* 计算 a[] b[] c[] f[] */
    switch(con)
    {
		case NATURAL:
			f[0] = 0;
			f[n] = 0;
			a[0] = 0;
			a[n] = 0;
			c[0] = 0;
			c[n] = 0;
			b[0] = 1;
			b[n] = 1;
			break;

		case CLAMPED:
			f[0] = 6 * (d[0] - a[0]);
			f[n] = 6 * (c[n] - d[n - 1]);
			a[0] = 0;
			c[n] = 0;
			c[0] = h[0];
			a[n] = h[n - 1];
			b[0] = 2 * h[0];
			b[n] = 2 * h[n - 1];
			break;

		case NOTAKNOT:
			f[0] = 0;
			f[n] = 0;
			a[0] = h[0];
			c[n] = h[n - 1];
			c[0] = -(h[0] + h[1]);
			a[n] = -(h[n - 2] + h[n - 1]);
			b[0] = h[1];
			b[n] = h[n - 2];
			break;
    }
	
	/* 构建矩阵方程 三对角矩阵 */
    for (i = 1; i < n; i++)
    {
        a[i] = h[i - 1];
        b[i] = 2 * (h[i - 1] + h[i]);
        c[i] = h[i];
        f[i] = 6 * (d[i] - d[i - 1]);
    }
    /* for (i = 0; i < n+1; i++){   printf("%f\n", c[i]); }*/

    /*************
    ** 高斯消元
    *************/
    if (n > 2)
    {
        /* 第0行到第(n-3)行的消元 */
        for(i = 0; i <= n - 3; i++)
        {
            /* 选主元 */
			if (ABSOLUTE(a[i + 1]) > ABSOLUTE(b[i]))
            {
                SWAP(a[i + 1], b[i], temp);
                SWAP(b[i + 1], c[i], temp);
                SWAP(c[i + 1], a[i], temp);
                SWAP(f[i + 1], f[i], temp);
            }
            temp = a[i + 1] / b[i];
            a[i + 1] = 0;
            b[i + 1] = b[i + 1] - temp * c[i];
            c[i + 1] = c[i + 1] - temp * a[i];
            f[i + 1] = f[i + 1] - temp * f[i];
        }
    }
    if (n >= 2)
    {
        /* 最后3行的消元 */
        /* 第(n-2)行的消元 */
        /* 选主元 */
		if (ABSOLUTE(a[n - 1]) > ABSOLUTE(b[n - 2]))
        {
            SWAP(a[n - 1], b[n - 2], temp);
            SWAP(b[n - 1], c[n - 2], temp);
            SWAP(c[n - 1], a[n - 2], temp);
            SWAP(f[n - 1], f[n - 2], temp);
        }
        /* 选主元 */
		if (ABSOLUTE(c[n]) > ABSOLUTE(b[n - 2]))
        {
            SWAP(c[n], b[n - 2], temp);
            SWAP(a[n], c[n - 2], temp);
            SWAP(b[n], a[n - 2], temp);
            SWAP(f[n], f[n - 2], temp);
        }
        /* 消元 */
        temp = a[n - 1] / b[n - 2];
        a[n - 1] = 0;
        b[n - 1] = b[n - 1] - temp * c[n - 2];
        c[n - 1] = c[n - 1] - temp * a[n - 2];
        f[n - 1] = f[n - 1] - temp * f[n - 2];
        /* 消元 */
        temp = c[n] / b[n - 2];
        c[n] = 0;
        a[n] = a[n] - temp * c[n - 2];
        b[n] = b[n] - temp * a[n - 2];
        f[n] = f[n] - temp * f[n - 2];
    }
    /* 最后2行的消元 */
    /* 第(n-1)行的消元 */
    /* 选主元 */
	if (ABSOLUTE(a[n]) > ABSOLUTE(b[n - 1]))
    {
        SWAP(a[n], b[n - 1], temp);
        SWAP(b[n], c[n - 1], temp);
        SWAP(f[n], f[n - 1], temp);
    }
    /* 消元 */
    temp = a[n] / b[n-1];
    a[n] = 0;
    b[n] = b[n] - temp * c[n - 1];
    f[n] = f[n] - temp * f[n - 1];

    /******************
    ** 回代求解 m[] = f[] / b[] 
    ******************/
    m[n] = f[n] / b[n];
    m[n - 1] = (f[n - 1] - c[n - 1] * m[n]) / b[n-1];
    for (i = n - 2; i >= 0; i--)
    {
        m[i] = ( f[i] - (m[i + 2] * a[i] + m[i + 1] * c[i]) ) / b[i];
    }
    /* for (i = 0; i < n+1; i++)   printf("%f\n", m[i]); */

    /***********************
    ** 计算插值函数所有参数
    ***********************/
    for (i = 0; i < n; i++)                                               /* 数学公式化简而得 */
    {
        coe[i].a3 = (m[i + 1] - m[i]) / (6 * h[i]);                       /* */
        coe[i].b2 = m[i] / 2;                                             /* */
        coe[i].c1 = d[i] - (h[i] / 6) * (2 * m[i] + m[i + 1]);			  /* */
        coe[i].d0 = y[i];                                                 /* d0 = y[i] */
    }
    free(h);
    // 计算正确完成返回插值点的数量
    return n + 1;
}

/*
** 资源不足时函数返回 -1
** 插值点数小于2时，函数返回 -2
** 计算正确完成函数返回插值点的数量 n
*/
int splineB(POINT *point)
{
	double *x = (*point).xCoordinate, *y = (*point).yCoordinate;
	int n = (*point).num - 1;          /* 循环上限 */
	int i;                             /* 循环辅助变量 */
	COEFFICIENT *coe = (*point).coe;   /* 存储a3 b2 c1 d0 */
	CONDITION con = (*point).con;      /* 选择边界条件 */
	double *h, *d;                     /* h:为步长 d为微分 */
	double *a, *b, *c, *f, *m;         /* a b c 为方程系数 f 为方程结果 m为待求未知数(二次微分值)*/

	if (n < 1) {
		return -2;
	}

	h = (double *)malloc((6 * n + 4) * sizeof(double)); /* 0,       1,...,(n-1)          */
	if (h == NULL) {
		return -1;
	}
	d = h + n;                                            /* 0,       1,...,(n-1)          */
	a = d + n;                                            /* 特别使用,1,...,(n-1),       n */
	b = a + (n + 1);                                      /*        0,1,...,(n-1),       n */
	c = b + (n + 1);                                      /*        0,1,...,(n-1),特别使用 */
	f = c + (n + 1);                                      /*        0,1,...,(n-1),       n */
	m = b;

	/* 计算 h[] d[] */
	for (i = 0; i < n; i++)
	{
		h[i] = x[i + 1] - x[i];                          /* 存储步长及差值 */
		d[i] = (y[i + 1] - y[i]) / h[i];                 /* 存储微分 */
		/* printf("%f\t%f\n", h[i], d[i]); */
	}
	/**********************
	** 初始化系数增广矩阵
	**********************/
	a[0] = (*point).f0;
	c[n] = (*point).fn;
	/* 计算 a[] b[] c[] f[] */
	switch (con)
	{
		case NATURAL:
			f[0] = 0;
			f[n] = 0;
			a[0] = 0;
			a[n] = 0;
			c[0] = 0;
			c[n] = 0;
			b[0] = 1;
			b[n] = 1;
			break;

		case CLAMPED:
			f[0] = 6 * (d[0] - a[0]);
			f[n] = 6 * (c[n] - d[n - 1]);
			a[0] = 0;
			c[n] = 0;
			c[0] = h[0];
			a[n] = h[n - 1];
			b[0] = 2 * h[0];
			b[n] = 2 * h[n - 1];
			break;

		case NOTAKNOT:
			f[0] = 0;
			f[n] = 0;
			a[0] = h[0];
			c[n] = h[n - 1];
			c[0] = -(h[0] + h[1]);
			a[n] = -(h[n - 2] + h[n - 1]);
			b[0] = h[1];
			b[n] = h[n - 2];
			break;
	}

	/* 构建矩阵方程 三对角矩阵 */
	for (i = 1; i < n; i++)
	{
		a[i] = h[i - 1];
		b[i] = 2 * (h[i - 1] + h[i]);
		c[i] = h[i];
		f[i] = 6 * (d[i] - d[i - 1]);
	}
	/* for (i = 0; i < n+1; i++){   printf("%f\n", c[i]); }*/
	
	//   /*************
	//   ** 高斯消元
	//   *************/
	if (tdma(f, n, a, b, c)<0){ 
		free(h);
		return -1;
	}
	memcpy( m, f, (n)*sizeof(double) );

	/***********************
	** 计算插值函数所有参数
	***********************/
	for (i = 0; i < n; i++)                                               /* 数学公式化简而得 */
	{
		coe[i].a3 = (m[i + 1] - m[i]) / (6 * h[i]);                       /* */
		coe[i].b2 = m[i] / 2;                                             /* */
		coe[i].c1 = d[i] - (h[i] / 6) * (2 * m[i] + m[i + 1]);			  /* */
		coe[i].d0 = y[i];                                                 /* d0 = y[i] */
	}
	free(h);
	// 计算正确完成返回插值点的数量
	return n + 1;
}

int iSplineDisCoe( COEFFICIENT* pCoe,int iSize )
{
	int i;

	printf("a:\t\tb:\t\tc:\t\td:\t\t\n");
	for (i = 0; i < iSize - 1; i++){
		printf("%f\t%f\t%f\t%f\n", pCoe[i].a3, pCoe[i].b2, pCoe[i].c1, pCoe[i].d0);
	}

	printf("\n");

	return i;
}

int iGetCurve(double* pCoe,int iSize, double dValue)
{
	int i;

	if ((pCoe[0] > dValue) ){
		return 0;
	}
	if ((pCoe[iSize-1] < dValue)){
		return iSize - 2;
	}
	for (i = 0; i < iSize-1; i++){
		if ((pCoe[i] <= dValue) && (pCoe[i+1] >= dValue))
		{
			return i;
		}
	}

	return -1;
}

float fResultLineEqu( float x1,float y1,float x2,float y2,float fTcValue )
{
	LINE_QUATION* pstuMylinEqu = NULL;
	float fTempResult = 0;

	pstuMylinEqu = (LINE_QUATION* )calloc( 1,sizeof(LINE_QUATION) );
	if(NULL == pstuMylinEqu){
		return EXE_SUCCEED;  /* 定义错误码 */
	}
	
	pstuMylinEqu->a = 1;
	pstuMylinEqu->b = 1;
	pstuMylinEqu->c = 0;	
	
	pstuMylinEqu = SolveLineearEquation( x1,y1,x2,y2, pstuMylinEqu );			
	fTempResult = uSolveLineearX(fTcValue,pstuMylinEqu);
	
	free( pstuMylinEqu );
	
#if DEBUH_UART1		
		myprintf( "LineEquValue:%.2f \r\n",fTempResult );		
#endif
	
	return fTempResult;
}

