/*BMP转化程序——读入一行处理后存入实数矩阵*/
#include "math.h"
#include "stdlib.h"
#include "stdio.h"

#define R_N 2048
#define A_N 2048
struct comp {float re;float im;};
/****************************************************************/

int main()
{ 
	long i,j,jmax,imax;
	comp data[R_N],temp_cmp;
	
	double molde,max,min,dif,fact;
	unsigned char **B;

	FILE *fp_in,*fp_out;
/**********************************变换到频域及距离向压缩*********************/
    /*******************打开文件*****************/
    fp_in = fopen( "image.dat" , "rb" );
	fp_out = fopen( "image.bmp" , "wb" );
	
	/*读取复图像数据并求出峰值*/
	fread(&temp_cmp,sizeof(comp),1,fp_in);
	rewind(fp_in);
	max=min=(temp_cmp.re*temp_cmp.re+temp_cmp.im*temp_cmp.im);
	jmax=0;imax=0;
	for(i=0;i<A_N;i++)
	{
		fread(data,sizeof(comp),R_N,fp_in);		
		for(j=0;j<R_N;j++)
		{
			molde=(data[j].re*data[j].re+data[j].im*data[j].im);
			if(max<molde) {max=molde;jmax=j;imax=i;}
			if(min>molde) min=molde;
		}
	}
	printf("%d,%d",imax,jmax);
	rewind(fp_in);

/*******************************数据量化****************************/
	B=(unsigned char**)calloc(A_N,sizeof(unsigned char*));
	for(i=0;i<A_N;i++)
		B[i]=(unsigned char*)calloc(R_N,sizeof(unsigned char));
	max=max*0.0005;
//	max=max;
//	min=0.001*max;
	dif=(max-min);
	fact=dif/255.0;
	for(i=0;i<A_N;i++)
	{
		fread(data,sizeof(comp),R_N,fp_in);		
		for(j=0;j<R_N;j++)
		{
			molde=(data[j].re*data[j].re+data[j].im*data[j].im);
			if (molde<min)
				B[i][j]=0;
			else if (molde>max)
				B[i][j]=255;
			else
				B[i][j]=(unsigned char)(((molde)-min)/fact);
		}
	}
	fclose(fp_in);
/************************************转化成BMP文件*****************************/

	struct FileHeader
	{
		int	bfSize;
		short bfReserved1;
		short bfReserved2;
		int bfOffBytes;
	};

	struct BitmapHeader
	{
		int biSize;
		int biWidth;
		int biHeight;
		short biPlanes;
		short biBitCount;
		int bicompression;
		int biSizeImage;
		int biXPelsPerMeter;
		int biYPelsPerMeter;
		int	biClrUsed;
		int biClrColors;
	};

	struct ColorMap
	{
		unsigned char bmiRed;
		unsigned char bmiGreen;
		unsigned char bmiBlue;
		unsigned char bmiReserved;
	};

	struct FileHeader FileHead;
	struct BitmapHeader BMPHead;
	struct ColorMap ClrMap[256];


	/************* Define the File Header**********************/
	FileHead.bfSize=R_N*A_N+1024+54;
	FileHead.bfReserved1=0;
	FileHead.bfReserved2=0;
	FileHead.bfOffBytes=1024+54;

	/***************Define the Bitmap Header*******************/
	BMPHead.biSize=40;
	BMPHead.biWidth=R_N;
	BMPHead.biHeight=A_N;
	BMPHead.biPlanes=1;
	BMPHead.biBitCount=8;
	BMPHead.bicompression=0;
	BMPHead.biSizeImage=R_N*A_N;
	BMPHead.biXPelsPerMeter=0;
	BMPHead.biYPelsPerMeter=0;
	BMPHead.biClrUsed=0;
	BMPHead.biClrColors=0;

	/************************ Define the Color Map*************/
	for (i=0;i<256;i++)
	{
		ClrMap[i].bmiRed=(unsigned char)i;
		ClrMap[i].bmiGreen=(unsigned char)i;
		ClrMap[i].bmiBlue=(unsigned char)i;
		ClrMap[i].bmiReserved=0;
	}

	fprintf(fp_out,"%c",'B');
	fprintf(fp_out,"%c",'M');
	fwrite(&FileHead,sizeof(struct FileHeader),1,fp_out);
	fwrite(&BMPHead,sizeof(struct BitmapHeader),1,fp_out);
	fwrite(&ClrMap,sizeof(struct ColorMap),256,fp_out);
	
	for (i=0;i<A_N;i++)
//	for (i=(A_N)-1;i>=0;i--)
		fwrite(B[i],sizeof(char),R_N,fp_out);

	for(i=0;i<(A_N);i++)	free(B[i]);
	free(B);
	fclose(fp_out);
	
	return 0;
}

