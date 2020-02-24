#pragma pack(push, 1)   //구조체를 1바이트 크기로 정렬

typedef struct _BITMAPFILEHEADER    //BMP 비트맵 파일 헤더 구조체
{
    unsigned short bfType;  //BMP 파일 매직 넘버
    unsigned int   bfSize;  //파일 크기
    unsigned short bfReserved1; //예약
    unsigned short bfReserved2; //예약
    unsigned int   bf0ffBits;   //비트맵 데이터의 시작 위치
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER  //BMP 비트맵 정보 헤더 구조체(DIB헤더)
{
    unsigned int   biSize;      //현재 구조체의 크기
    int            biWidth;     //비트맵 이미지의 가로 크기
    int            biHeight;    //비트맵 이미지의 세로 크기
    unsigned short biPlanes;    //사용하는 색상판의 수
    unsigned short biBitCount;  //픽셀 하나를 표현하는 비트 수
    unsigned int   biCompression;   //압축방식
    unsigned int   biSizeImage; //비트맵 이미지의 픽셀 데이터 크기
    int            biXPelsPerMeter; //그림의 가로 해상도(미터당 픽셀)
    int            biYPelsPerMeter; //그림의 세로 해상도(미터당 픽셀)
    unsigned int   biClrUsed;   //색상 테이블에서 실제 사용되는 색상 수
    unsigned int   biClrImportant;  //비트맵을 표현하는데 필요한 색상 인덱스 수
} BITMAPINFOHEADER;

typedef struct _RGBTRIPLE
{
    unsigned char rgbtBlue;
    unsigned char rgbtGreen;
    unsigned char rgbtRed;
} RGBTRIPLE;

#pragma pack(pop)

#define PIXEL_SIZE  3
#define PIXEL_ALIGN 4

int main()
{
    FILE *fpBmp;    //비트맵 파일 포인터
    FILE *fpTxt;    //텍스트 파일 포인터
    BITMAPFILEHEADER fileHeader;    //비트맵 파일 헤더 구조체 변수
    BITMAPINFOHEADER infoHeader;    //비트맵 정보 헤더 구조체 변수
    
    unsigned char *image;   //픽셀 데이터 포인터
    int size;   //픽셀 데이터 크기
    int width, height;  //비트맵 이미지의 가로, 세로 크기
    int padding;    //픽셀 데이터의 가로 크기가 4의 배수가 아닐 때 남는 공간의 크기

    char ascii[] = {'#','#','@','%','=','+','*',':','-','.',' '};
    //11개, 각 픽셀을 표현할 ASCII 문자. 인덱스가 높을수록 밝아지는 것을 표현

    fpBmp = fopen("Peppers80x80.bmp","rb"); //비트맵 파일을 바이너리 모드로 열기
    if (fpBmp == NULL)  //파일 열기에 실패하면
        return 0;       //프로그램 종료

    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBmp) < 1)
    {
        fclose(fpBmp);
        return 0;
        //비트맵 파일 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
    }

    if (fileHeader.bfType != 'MB')
    {
        fclose(fpBmp);
        return 0;
        //매직 넘버가 MB가 맞는지 확인(2바이트 크기의 BM을 리틀 엔디언으로 읽었으므로 MB가 됨)
        //매직 넘버가 맞지 않으면 프로그램 종료
    }

    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBmp) < 1)
    {
        fclose(fpBmp);
        return 0;
        //비트맵 정보 헤더 읽기. 읽기에 실패하면 파일 포인터를 닫고 프로그램 종료
    }

    if (infoHeader.biBitCount !=24)
    {
        fclose(fpBmp);
        return 0;
        //24비트 비트맵이 아니면 프로그램 종료
    }

    size = infoHeader.biSizeImage;  //픽셀 데이터 크기
    width = infoHeader.biWidth;     //비트맵 이미지의 가로 크기
    height = infoHeader.biHeight;   //비트맵 이미지의 세로 크기




}