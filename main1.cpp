// patient.cpp : 定义控制台应用程序的入口点。
//

#include "Convert.h"
#include "Feature.h"
#include <cv.h>
#include <highgui.h>

float model[20][120];
void fprintCoeff(XM::ColorLayoutDescriptor* cld,FILE *fp)
{
    int NY2, NC2;

    NY2 = cld->GetNumberOfYCoeff();
    NC2 = cld->GetNumberOfCCoeff();

    int *Y2, *Cb2, *Cr2;
    Y2 = cld->GetYCoeff();
    Cb2 = cld->GetCbCoeff();
    Cr2 = cld->GetCrCoeff();


    // first 3 values have higher weight
	fprintf(fp,"%f",1.41421*Y2[0]);
    for(int j = 1; j < 3; j++ )
    {
		fprintf(fp,",%f",1.414*Y2[j]);
    }
    for(int j = 3; j < NY2; j++ )
    {
		fprintf(fp,",%d",Y2[j]);
    }

    /// -- Cb --
	fprintf(fp,",%f",1.41421* Cb2[0]);
    for(int j = 1; j < NC2; j++ )
    {
			fprintf(fp,",%d",Cb2[j]);
	}

	fprintf(fp,",%f",2.0* Cr2[0]);
	fprintf(fp,",%f",1.41421* Cr2[1]);
	fprintf(fp,",%f",1.41421* Cr2[2]);

    for(int j = 3; j < NC2; j++ )
    {
			fprintf(fp,",%d", Cr2[j]);
    }
	fprintf(fp,"\n");
    return ;
}

int cal_distance(float* vector)
{
        int min = 0;
        float min_sum = 0; 
        for(int j=0;j<120;j++)
        {
                min_sum = min_sum + ((model[0][j] - vector[j]))*((model[0][j]-vector[j]));
        }

        for(int i=1;i<20;i++)
        {       float sum = 0;
                for (int j=0;j<120;j++)
                {
                        sum = sum + ((model[i][j] - vector[j]))*((model[i][j]-vector[j]));
                
                }
                if( min_sum > sum)
                {
                        min = i;
                        min_sum = sum ;
                }
        }
        return min;
}


void loadModel()
{
        FILE * infile;
        infile = fopen("center.txt","r");
        int cluster = 0;

        while (! feof(infile))
        {

                char str[10000];
                memset(str,0,10000*sizeof(char));
                fscanf(infile,"%s\n",str);
                int begin = 0,end = 0;
                int num = 0;

                while(str[end]!='\n' && str[end])
                {
                        while(str[end]!=',' && str[end]!='\n' &&str[end])

                                end++;
                        char temp[255];
                        memset(temp,0,255*sizeof(char));
                        for(int i=begin;i<end;i++)
                                temp[i-begin]= str[i];
                        int l=strlen(temp);
                        temp[l]=0;
                        model[cluster][num++]= atof(temp);

                        begin = end +1;
                        end ++;
                }

                /*for(int i=0;i<120;i++)
                        printf("%f,",model[cluster][i]);
                printf("\n");
                */
                cluster ++;
                //printf("%d\n",cluster);

       }

        fclose(infile);





}


int main(int argc, char* argv[])
{
	FILE *taskFileHandle = NULL;
	taskFileHandle = fopen(argv[1],"r");
	FILE* outfile;
        loadModel();
	int num = 0;
	int id = 0;

	while (! feof(taskFileHandle))
	{
		num ++;
		
		char image_file_name[255];


		fscanf(taskFileHandle,"%d,%s",&id,image_file_name);

		IplImage *test =cvLoadImage(image_file_name,-1);



                if (test == NULL || test->nChannels == 1)
                        continue;

		Frame* frame = new Frame(test->width, test->height, true, false, false );
		Mat imgMat(test);
		frame->setImage( imgMat);
		XM::ColorLayoutDescriptor* cl = Feature::getColorLayoutD(frame);
		//cl->Print();
			float vector[120];
                        memset(vector,0,120*sizeof(float));
			
			int NY,NC;
			int *Y, *Cb, *Cr;
			NY = cl->GetNumberOfYCoeff();
    			NC = cl->GetNumberOfCCoeff();

			Y = cl->GetYCoeff();
                        for( int i=0; i<3; i++)
				vector[i] = 1.41421 * Y[i];
                        for( int i=3; i<NY; i++)
                                vector[i] = Y[i];

			Cb = cl->GetCbCoeff();
			vector[NY] = 1.41421 * Cb[0];
			for( int i= NY+1;i< NC+NY;i++ )
				vector[i] = Cb[i-NY];
					
			Cr = cl->GetCrCoeff();
			vector[NY+NC] = Cr[0]*2;
			vector[NY+NC+1] = Cr[1]*1.41421;
			vector[NY+NC+2] = Cr[2]*1.41421;

 			for( int i= NC+NY+3;i< 2*NC+NY;i++ )
				vector[i] = Cr[i-NC-NY];

                        int bestOrder = cal_distance(vector);
                        printf("%d\n",bestOrder);
		cvReleaseImage(&test);
		delete cl;
		delete frame;
	}
	fclose(taskFileHandle);


	return 0;
}


