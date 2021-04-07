#ifndef _FUNC_SPLINE_H_
#define _FUNC_SPLINE_H_

#include "Func_IFP_300_Drv.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

typedef double RealNum;

#define ITERATIONS (1000)
#define ABSOLUTE(p) ( ((p) > 0) ? (p) : -(p) )
#define SWAP(x, y, temp) (temp) = (y); (y) = (x); (x) = (temp);

#define	ABSZERO (0)
#define ZERO (1e-12)
#define ISZERO(Value) (((-1.0*ZERO) < (Value)) && ((Value) < (1.0*ZERO)))
#define LESSTHANZERO(Value) ((Value) < ZERO)
#define GREATERTHANZERO(Value) (ZERO < (Value))
#define GREATERTHAN(Value,Value1) ((Value)>(Value1))       
#define LESSTHAN(Value,Value1) ((Value)<(Value1))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ISBETWEEN(Value,Value1,Value2) (GREATERTHAN(Value, MIN(Value1, Value2)) && LESSTHAN(Value, MAX(Value1, Value2)))

#define COMPLEX_SLUTION   (0)

#define ONE_SOLUTION      (1)
#define TWO_SOLUTION      (2)
#define THR_SOLUTION      (3)

typedef struct tagComplex
{
	RealNum real;
	RealNum image;
}COMPLEX;

typedef enum _condition
{
    NATURAL=0, // 自然边界
    CLAMPED, // 夹持边界
    NOTAKNOT // 非扭结边界
}CONDITION;

typedef struct _coefficient
{
    double a3;
    double b2;
    double c1;
    double d0;
}COEFFICIENT;

typedef struct _point
{
	COEFFICIENT *coe;    // 插值结果系数矩阵
    double *xCoordinate; // 插值点横坐标
    double *yCoordinate; // 插值点纵坐标
    double f0;           // 在夹持条件下的最左边点的导数值
    double fn;           // 在夹持条件下的最右边点的导数值
    int num;             // 插值点数
	CONDITION con;       // 边界条件
}POINT;

//uint8_t pstuAlforithmSpline( UINTE_DATA_TYPE* pstuIdInfo,ALGORITHM_DATA_TYPE* pstuAlg,float fPesponse,uint8_t uChildrenNum );
int UnivariateCubiceQuationShengjin(double a3, double b2, double c1, double d0, double *x1, double *x2, double *x3);
int UnivariateCubiceQuationShengjinA(RealNum rA, RealNum rB, RealNum rC, RealNum rD, RealNum* rX1, RealNum* rX2, RealNum* rX3);
int tdma(double x[], const unsigned int N, const double a[], const double b[], double c[]);
double UnivariateCubiceQuationSolute(double a, double b, double c, double d, double num);
int splineA(POINT *point);
int splineB(POINT *point);
int iSplineDisCoe( COEFFICIENT* pCoe,int iSize );
int iGetCurve(double* pCoe,int iSize, double dValue);
float fResultLineEqu( float x1,float y1,float x2,float y2,float fTcValue );

#endif
	
